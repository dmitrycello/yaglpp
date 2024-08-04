#define YAGLPP_BUILD_LIB
#include <yaglpp/Thread.h>
#include <yaglpp/Window.h>
#include <yaglpp/Joystick.h>
#define YAGLPP_INIT_SIZE 32
#ifndef YAGLPP_NO_AFX_LAYOUT
#pragma message("Thread.cpp: Compiling with AFX-alike layout support...")
int main(int argc, char** argv)
{
    return glfw::Thread::_main(argc, argv);
}
#endif // #ifndef YAGLPP_NO_AFX_LAYOUT

DWORD WINAPI _threadProc(LPVOID lpParam)
{
    return glfw::Thread::_thread(lpParam);
}

namespace glfw {
Thread::_SDATA::_SDATA()
{
    iArgc = 0;
    iSize = YAGLPP_INIT_SIZE;
    iCount = 1; // [0] reserved for sync event
    pArgv = nullptr;
    dEventsTimeout = 0.0;
    pMainThread = nullptr;
    pLocks = (LONG*)_YAGLPP_CALLOC_((YAGLPP_INIT_SIZE >> 5) * sizeof(LONG));
    pEvents = (HANDLE*)_YAGLPP_CALLOC_(YAGLPP_INIT_SIZE * sizeof(HANDLE));
    pEvents[0] = CreateEventA(NULL, TRUE, TRUE, NULL); // sync event
    _YAGLPP_ASSERT_(pEvents[0] != NULL); // FAILED TO CREATE EVENT OBJECT
}

Thread::_SDATA::~_SDATA()
{
    for (int i = 0; i < iCount; i++)
    {
        CloseHandle(pEvents[i]);
    }
    _YAGLPP_FREE_((void*)pLocks);
    _YAGLPP_FREE_((void*)pEvents);
}

void Thread::_message(int msgid, Param x, Param y, Param z, Param w, LPVOID sender)
{
    syncEnter(m.iRef);
    if (m.iCount == m.iSize)
    {
        m.iSize <<= 1;
        m.pQueue = (Message*)_YAGLPP_REALLOC_(m.pQueue, m.iSize);
    }
    m.pQueue[m.iCount].msgid = msgid;
    m.pQueue[m.iCount].x = x;
    m.pQueue[m.iCount].y = y;
    m.pQueue[m.iCount].z = z;
    m.pQueue[m.iCount].w = w;
    m.pQueue[m.iCount].sender = (Thread*)sender;

    m.iCount++; // post-increment
    syncLeave(m.iRef);
    if (isMainThread())
    {
        glfwPostEmptyEvent(); // Wake up main thread, if idled
    }
}

DWORD Thread::_thread(LPVOID param)
{
    Thread* pThread = (Thread*)param;
    *_tlsThread() = pThread;
    return pThread->onRun();
}

Thread::Thread()
{
    memset(&m, 0, sizeof(_MDATA));
    m.iRef = syncRef();
    m.iSize = YAGLPP_INIT_SIZE;
    m.pQueue = (Message*)_YAGLPP_MALLOC_(YAGLPP_INIT_SIZE * sizeof(Message));
    if (s.pMainThread == nullptr)
    {
        *_tlsThread() = this;
        s.pMainThread = this;
        m.nThreadId = GetCurrentThreadId();
        m.hThread = OpenThread(THREAD_SUSPEND_RESUME, TRUE, m.nThreadId);
    }
}

Thread::~Thread()
{
    _YAGLPP_FREE_(m.pQueue);
    if (m.hThread != nullptr)
    {
        CloseHandle(m.hThread);
    }
}

void Thread::createThread(bool suspended)
{
    _YAGLPP_ASSERT_(!isThread()); // GLFW THREAD OBJECT HAS VALID THREAD
    m.hThread = CreateThread(NULL, 0, &_threadProc, this, (suspended) ? CREATE_SUSPENDED : 0, &m.nThreadId);
    _YAGLPP_ASSERT_(isThread()); // FAILED TO CREATE THREAD
}

bool Thread::dispatchMessage(_Out_ Message* msg)
{
    _YAGLPP_ASSERT_(*_tlsThread() == this); // DISPATCH IS ALLOWED ONLY BY THE HOST THREAD
    syncEnter(m.iRef);
    if (m.iIndex < m.iCount)
    {
        memcpy(msg, &m.pQueue[m.iIndex], sizeof(Message));
        m.iIndex++; // post-increment
        syncLeave(m.iRef);
        return true;
    }
    m.iCount = 0; // Reset queue
    m.iIndex = 0;
    syncLeave(m.iRef);

#ifdef _DEBUG
    m._bDispatch = false;
#endif // #ifdef _DEBUG

    memset(msg, 0, sizeof(Message)); // SAL requirment
    return false;
}

bool Thread::hasContext() const
{
    if (m.pWindow != nullptr)
    {
        return m.pWindow->m.pThread != nullptr;
    }
    else return false;
}

DWORD Thread::onRun()
{
    Message msg;
    bool bMainThread = isMainThread();
    getContext()->makeContextCurrent();
    onInit();
    if (getExitcode() > 0) return getExitcode();
    double dLast = glfwGetTime();
    while (!getContext()->windowShouldClose())
    {
        if (bMainThread) // input processing
        {
            double dNew = glfwGetTime();
            onInput(dNew - dLast);
            if (getExitcode() > 0) return getExitcode();
            dLast = dNew;
        }

        onRender(); // window renedering loop
        if (getExitcode() > 0) return getExitcode();

        while (dispatchMessage(&msg)) // thread event processing
        {
            if (!translateMessage(&msg))
            {
                onMessage(msg.msgid, msg.x, msg.y, msg.z, msg.w, msg.sender);
                if (getExitcode() > 0) return getExitcode();
            }
        }
        getContext()->swapBuffers(); // window event processing
        if (bMainThread)
        {
            if (getEventsTimeout() > 0.0)
            {
                onIdle(); // idle thread processing
                if (getExitcode() > 0) return getExitcode();
                waitEventsTimeout();
            }
            else pollEvents();
        }
    }
    onExit(); // exit thread processing
    if (getExitcode() > 0) return getExitcode();
    getContext()->makeContextNonCurrent();
    while (dispatchMessage(&msg)) // thread event processing
    {
        if (!translateMessage(&msg))
        {
            onMessage(msg.msgid, msg.x, msg.y, msg.z, msg.w, msg.sender);
        }
    }
    return getExitcode();
}

int Thread::resumeThread()
{
    DWORD nCount = ResumeThread(_handle());
    _YAGLPP_ASSERT_(nCount != (DWORD)-1); // FAILED TO RESUME THREAD
    return nCount;
}

int Thread::suspendThread()
{
    DWORD nCount = SuspendThread(_handle());
    _YAGLPP_ASSERT_(nCount != (DWORD)-1); // FAILED TO SUSPEND THREAD
    return nCount;
}

void Thread::syncEnter(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)s.iCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    while (_interlockedbittestandset(&s.pLocks[lIndex], lBit))
    {
        DWORD dwResult = WaitForSingleObject(s.pEvents[ref], INFINITE);
        _YAGLPP_ASSERT_(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR EVENT OBJECT
    }
    BOOL bResult = ResetEvent(s.pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
}

void Thread::syncLeave(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)s.iCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    BOOLEAN bBit = _interlockedbittestandreset(&s.pLocks[lIndex], lBit);
    _YAGLPP_ASSERT_(bBit != FALSE); // SYNC BIT WAS ALREADY UNSET
    BOOL bResult = SetEvent(s.pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO SET EVENT OBJECT
}

int Thread::syncRef()
{
    syncEnter(0);
    int iEvent = s.iCount++;
    if (iEvent == s.iSize)
    {
        int iNewLock = s.iSize >> 4;
        int iOldLock = s.iSize >> 5;
        int iOldSize = s.iSize;
        s.iSize <<= 1; // x2
        volatile LONG* pOldLocks = s.pLocks;
        volatile HANDLE* pOldEvents = s.pEvents;
        s.pLocks = (LONG*)_YAGLPP_CALLOC_(iNewLock * sizeof(LONG));
        s.pEvents = (HANDLE*)_YAGLPP_CALLOC_(s.iSize * sizeof(HANDLE));
        memcpy((void*)s.pLocks, (const void*)pOldLocks, iOldLock * sizeof(LONG));
        memcpy((void*)s.pEvents, (const void*)pOldEvents, iOldSize * sizeof(HANDLE));
        _YAGLPP_FREE_((void*)pOldLocks);
        _YAGLPP_FREE_((void*)pOldEvents);
    }
    s.pEvents[iEvent] = CreateEventA(NULL, TRUE, TRUE, NULL);
    _YAGLPP_ASSERT_(s.pEvents[iEvent] != NULL); // FAILED TO CREATE EVENT OBJECT
    syncLeave(0);
    return iEvent;
}

bool Thread::syncTry(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)s.iCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    if (_interlockedbittestandset(&s.pLocks[lIndex], lBit)) return false;
    BOOL bResult = ResetEvent(s.pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
    return true;
}

void Thread::wakeThread()
{
    DWORD nCount = 0;
    do
    {
        nCount = ResumeThread(_handle());
        _YAGLPP_ASSERT_(nCount != (DWORD)-1); // FAILED TO RESUME THREAD
    }
    while (nCount > 1);
}

#ifdef _DEBUG
bool Thread::_dispatch()
{
    bool bResult = m._bDispatch && (m.iCount > 0);
    m._bDispatch = true;
    return bResult;
}

HANDLE Thread::_handle() const
{
    _YAGLPP_ASSERT_(m.hThread != NULL); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return m.hThread;
}

void Thread::exitThread(DWORD exitcode)
{
    _YAGLPP_ASSERT_(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    ExitThread(exitcode);
}

_Ret_notnull_ const char* Thread::getArgValue(int index)
{
    _YAGLPP_ASSERT_((UINT)index < (UINT)s.iArgc); // INVALID COMMAND LINE ARGUMENT INDEX
    return s.pArgv[index];
}

_Ret_notnull_ Window* Thread::getContext() const
{
    _YAGLPP_ASSERT_(m.pWindow != nullptr); // THREAD OBJECT HAS NO ASSOCIATED WINDOW
    return m.pWindow;
}

DWORD Thread::getExitCodeThread()
{
    DWORD nExitCode;
    BOOL bResult = GetExitCodeThread(_handle(), &nExitCode);
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO GET THREAD EXIT CODE
    return nExitCode;
}

DWORD Thread::getThreadId() const
{
    _YAGLPP_ASSERT_(isThread()); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return m.nThreadId;
}

ThreadPriority Thread::getThreadPriority()
{
    int iPriority = GetThreadPriority(_handle());
    _YAGLPP_ASSERT_(iPriority != THREAD_PRIORITY_ERROR_RETURN); // FAILED TO GET THREAD PRIORITY
    return (ThreadPriority)iPriority;
}

bool Thread::getThreadPriorityBoost()
{
    BOOL bDisable, bResult = GetThreadPriorityBoost(_handle(), &bDisable);
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO GET THREAD PRIORITY BOOST
    return bDisable;
}

void Thread::joinThread()
{
    DWORD dwResult = WaitForSingleObject(_handle(), INFINITE);
    _YAGLPP_ASSERT_(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR SINGLE OBJECT
}

void Thread::postMessage(int msgid, Param x, Param y, Param z, Param w)
{
    _YAGLPP_ASSERT_(msgid >= 0); // MESSAGE ID MUST NOT BE NEGATIVE
    _message(msgid, x, y, z, w, *_tlsThread());
}

int Thread::setThreadIdealProcessor(int processor)
{
    _YAGLPP_ASSERT_((DWORD)processor < MAXIMUM_PROCESSORS); // INVALID INDEX OF IDEAL PROCESSOR FOR A THREAD OBJECT
    DWORD dwResult = SetThreadIdealProcessor(_handle(), processor);
    _YAGLPP_ASSERT_(dwResult != (DWORD)-1); // FAILED TO SET THREAD IDEAL PROCESSOR
    return dwResult;
}

void Thread::setThreadPriority(ThreadPriority priority)
{
    BOOL bResult = SetThreadPriority(_handle(), (int)priority);
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO SET THREAD PRIORITY
}

void Thread::setThreadPriorityBoost(bool disable)
{
    BOOL bResult = SetThreadPriorityBoost(_handle(), disable);
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO SET THREAD PRIORITY BOOST
}

void Thread::setContext(_In_ Window* window)
{
    _YAGLPP_ASSERT_(m.pWindow == nullptr); // WINDOW OBJECT HAS BEEN ALREADY SET
    m.pWindow = window;
}

void Thread::setEventsTimeout(double timeout)
{
    _YAGLPP_ASSERT_(s.dEventsTimeout == 0.0); // TIMEOUT VALUE HAS BEEN ALREADY SET
    _YAGLPP_ASSERT_((timeout >= 0.0) && (timeout <= 2.0)); // TIMEOUT VALUE IS OUT OF RANGE
    s.dEventsTimeout = timeout;
}

void Thread::terminateThread(int exitcode)
{
#pragma warning(push)
#pragma warning(disable : 6258)
    BOOL bResult = TerminateThread(_handle(), exitcode);
#pragma warning(pop)
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO TERMINATE THREAD
}

void Thread::waitEventsTimeout()
{
    _YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
    glfwWaitEventsTimeout(s.dEventsTimeout);
}
#endif // #ifdef _DEBUG
} // namespace glfw
