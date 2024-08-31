#define YAGLPP_BUILD_LIB
#include <yaglpp/Thread.h>
#include <yaglpp/Window.h>
#include <yaglpp/Joystick.h>
#include <yaglpp/Monitor.h>
#define YAGLPP_INIT_SIZE 32
#ifndef YAGLPP_NO_AFX_LAYOUT
#pragma message("Thread.cpp: Compiling with AFX-alike layout support...")
int main(int argc, char** argv)
{
    return glfw::Thread::_thread(glfw::Thread::getMainThread());
}
#endif // #ifndef YAGLPP_NO_AFX_LAYOUT

#ifdef YAGLPP_NO_GLFW_LEGACY
void* _allocate(size_t size, void* user)
{
    return _YAGLPP_MALLOC_(size);
}

void* _reallocate(void* block, size_t size, void* user)
{
    return _YAGLPP_REALLOC_(block, size);
}

void _deallocate(void* block, void* user)
{
    _YAGLPP_FREE_(block);
}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

#ifdef _DEBUG
void _errorCallback(int code, const char* description)
{
    std::cout << "GLFW ERROR OCCURED WITH THE CODE <" << code << ">: " << description << std::endl;
    _YAGLPP_ASSERT_(false); // GLFW LIBRARY ERROR
}
#endif // #ifdef _DEBUG

namespace glfw {
Thread::_SDATA Thread::_s;
bool Thread::_SDATA::initialize(Thread* thread)
{
    static bool bInitialized = false;
    if (bInitialized) return false;

#ifndef YAGLPP_COCOA_CHDIR_RESOURCES // Initialize GLFW
    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
#endif // #ifndef YAGLPP_COCOA_CHDIR_RESOURCES

#ifndef YAGLPP_COCOA_MENUBAR
    glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
#endif // #ifndef YAGLPP_COCOA_MENUBAR

#ifndef YAGLPP_JOYSTICK_HAT_BUTTONS
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
#endif // #ifndef YAGLPP_JOYSTICK_HAT_BUTTONS

#ifdef YAGLPP_NO_GLFW_LEGACY
    GLFWallocator allocator = { _allocate, _reallocate, _deallocate, nullptr };
    glfwInitAllocator(&allocator);
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

    bInitialized = (bool)glfwInit();
    _YAGLPP_ASSERT_(bInitialized); // FAILED TO INITIALIZE GLFW

#ifdef _DEBUG
    glfwSetErrorCallback(&_errorCallback);
#endif // #ifdef _DEBUG

    iArgc = 0; // Thread sync data
    iESize = YAGLPP_INIT_SIZE;
    iECount = 1; // [0] reserved for sync event
    dEventsTimeout = 0.0;
    pMainThread = thread;
    pLocks = (LONG*)_YAGLPP_CALLOC_((YAGLPP_INIT_SIZE >> 5) * sizeof(LONG));
    pEvents = (HANDLE*)_YAGLPP_CALLOC_(YAGLPP_INIT_SIZE * sizeof(HANDLE));
    pEvents[0] = CreateEventA(NULL, TRUE, TRUE, NULL); // sync event
    _YAGLPP_ASSERT_(pEvents[0] != NULL); // FAILED TO CREATE EVENT OBJECT

    char* pCmdA = GetCommandLineA(); // Command line arguments
    int iLen = (int)strlen(pCmdA) + 1;
    WCHAR* pCmdW = (WCHAR*)_YAGLPP_MALLOC_(iLen * sizeof(WCHAR));
    int iResult = MultiByteToWideChar(CP_ACP, 0, pCmdA, iLen, pCmdW, iLen);
    _YAGLPP_ASSERT_(iResult != 0); // FAILED TO CONVERT CHAR TO WIDE
    WCHAR** pArrW = CommandLineToArgvW(pCmdW, &iArgc);
    _YAGLPP_ASSERT_(pArrW != NULL); // FAILED TO PARSE COMMAND LINE
    _YAGLPP_FREE_(pCmdW);
    pArgv = (char**)_YAGLPP_MALLOC_(iArgc * sizeof(char*));
    for (int i = 0; i < iArgc; i++)
    {
        iLen = (int)wcslen(pArrW[i]) + 1;
        pArgv[i] = (char*)_YAGLPP_MALLOC_(sizeof(char) * iLen);
        iResult = WideCharToMultiByte(CP_ACP, 0, pArrW[i], iLen, pArgv[i], iLen, NULL, NULL);
        _YAGLPP_ASSERT_(iResult != 0); // FAILED TO CONVERT WIDE TO CHAR
    }
    LocalFree(pArrW);
    return bInitialized;
}

void Thread::_SDATA::syncEnter(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)iECount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    while (_interlockedbittestandset(&pLocks[lIndex], lBit))
    {
        DWORD dwResult = WaitForSingleObject(pEvents[ref], INFINITE);
        _YAGLPP_ASSERT_(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR EVENT OBJECT
    }
    BOOL bResult = ResetEvent(pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
}

void Thread::_SDATA::syncLeave(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)iECount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    BOOLEAN bBit = _interlockedbittestandreset(&pLocks[lIndex], lBit);
    _YAGLPP_ASSERT_(bBit != FALSE); // SYNC BIT WAS ALREADY UNSET
    BOOL bResult = SetEvent(pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO SET EVENT OBJECT
}

int Thread::_SDATA::syncRef()
{
    _s.syncEnter(0);
    int iEvent = iECount++;
    if (iEvent == iESize)
    {
        int iNewLock = iESize >> 4;
        int iOldLock = iESize >> 5;
        int iOldSize = iESize;
        iESize <<= 1; // x2
        volatile LONG* pOldLocks = pLocks;
        volatile HANDLE* pOldEvents = pEvents;
        pLocks = (LONG*)_YAGLPP_CALLOC_(iNewLock * sizeof(LONG));
        pEvents = (HANDLE*)_YAGLPP_CALLOC_(iESize * sizeof(HANDLE));
        memcpy((void*)pLocks, (const void*)pOldLocks, iOldLock * sizeof(LONG));
        memcpy((void*)pEvents, (const void*)pOldEvents, iOldSize * sizeof(HANDLE));
        _YAGLPP_FREE_((void*)pOldLocks);
        _YAGLPP_FREE_((void*)pOldEvents);
    }
    pEvents[iEvent] = CreateEventA(NULL, TRUE, TRUE, NULL);
    _YAGLPP_ASSERT_(pEvents[iEvent] != NULL); // FAILED TO CREATE EVENT OBJECT
    _s.syncLeave(0);
    return iEvent;
}

bool Thread::_SDATA::syncTry(int ref)
{
    _YAGLPP_ASSERT_((UINT)ref < (UINT)iECount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    if (_interlockedbittestandset(&pLocks[lIndex], lBit)) return false;
    BOOL bResult = ResetEvent(pEvents[ref]);
    _YAGLPP_ASSERT_(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
    return true;
}

void Thread::_SDATA::terminate()
{
    for (int i = 0; i < iECount; i++) // Cleanup sync
    {
        CloseHandle(pEvents[i]);
    }
    _YAGLPP_FREE_((void*)pLocks);
    _YAGLPP_FREE_((void*)pEvents);
    for (int i = 0; i < iArgc; i++) // Cleanup command line
    {
        _YAGLPP_FREE_(pArgv[i]);
    }
    _YAGLPP_FREE_(pArgv);
    glfwTerminate();
}

bool Thread::_message(const Message* msg)
{
    _s.syncEnter(_m.iRef);
    if (_m.bBlockMessage)
    {
        _s.syncLeave(_m.iRef);
        return false;
    }
    if (_m.iCount == _m.iSize)
    {
        _m.iSize <<= 1; // x2
        _m.pQueue = (Message*)_YAGLPP_REALLOC_(_m.pQueue, _m.iSize * sizeof(Message));
    }
    _m.pQueue[_m.iCount].msgid = msg->msgid;
    _m.pQueue[_m.iCount].x = msg->x;
    _m.pQueue[_m.iCount].y = msg->y;
    _m.pQueue[_m.iCount].z = msg->z;
    _m.pQueue[_m.iCount].w = msg->w;
    _m.pQueue[_m.iCount].sender = msg->sender;
    //memcpy(&_m.pQueue[_m.iCount], msg, sizeof(Message));

    _m.iCount++; // post-increment
    _s.syncLeave(_m.iRef);
    if (isMainThread() && _s.dEventsTimeout > 0.0)
    {
        glfwPostEmptyEvent(); // Wake up main thread, if idled
    }
    return true;
}

DWORD WINAPI Thread::_thread(LPVOID lpParam)
{
    Thread* pThread = (Thread*)lpParam;
    *_tlsThread() = pThread;
    return pThread->onRun();
}

Thread::Thread()
{
    memset(&_m, 0, sizeof(_MDATA));
    if (_s.initialize(this))
    {
        *_tlsThread() = this;
        _m.nThreadId = GetCurrentThreadId();
        _m.hThread = OpenThread(THREAD_SUSPEND_RESUME, TRUE, _m.nThreadId);
        Joystick::_s.initialize();
        Monitor::_s.initialize();
    }
    _m.iSize = YAGLPP_INIT_SIZE;
    _m.pQueue = (Message*)_YAGLPP_MALLOC_(YAGLPP_INIT_SIZE * sizeof(Message));
    _m.iRef = syncRef();
}

Thread::~Thread()
{
    if (isThread())
    {
        closeHandle();
    }
    _YAGLPP_FREE_(_m.pQueue);
    if (_m.bAutoDetele && (_m.pWindow != nullptr))
    {
        delete _m.pWindow;
    }
    if (_s.pMainThread == this)
    {
        _s.terminate();
    }
}

void Thread::createThread(bool suspended)
{
    _YAGLPP_ASSERT_(!isThread()); // GLFW THREAD OBJECT HAS VALID THREAD
    _m.hThread = CreateThread(NULL, 0, &_thread, this, (suspended) ? CREATE_SUSPENDED : 0, &_m.nThreadId);
    _YAGLPP_ASSERT_(isThread()); // FAILED TO CREATE THREAD
}

bool Thread::dispatchMessage(_Out_ Message* msg)
{
    _YAGLPP_ASSERT_(isCurrentThread()); // DISPATCH IS ALLOWED ONLY BY THE HOST THREAD
    _s.syncEnter(_m.iRef);
    if (_m.iIndex < _m.iCount)
    {
        msg->msgid = _m.pQueue[_m.iIndex].msgid;
        msg->x = _m.pQueue[_m.iIndex].x;
        msg->y = _m.pQueue[_m.iIndex].y;
        msg->z = _m.pQueue[_m.iIndex].z;
        msg->w = _m.pQueue[_m.iIndex].w;
        msg->sender = _m.pQueue[_m.iIndex].sender;
        //memcpy(msg, &_m.pQueue[_m.iIndex], sizeof(Message));

        _m.iIndex++; // post-increment
        _s.syncLeave(_m.iRef);
        return true;
    }
    _m.iCount = 0; // Reset queue
    _m.iIndex = 0;
    _s.syncLeave(_m.iRef);

#ifdef _DEBUG
    _m._iDispatch = 0;
#endif // #ifdef _DEBUG

    memset(msg, 0, sizeof(Message)); // SAL requirment
    return false;
}

bool Thread::isContextCurrent() const
{
    if (_m.pWindow != nullptr)
    {
        return _m.pWindow->_m.pThread == this;
    }
    return false;
}

DWORD Thread::onRun()
{
    Message msg;
    onInit(); // init thread processing
    if (getExitcode() > 0) return getExitcode();
    _YAGLPP_ASSERT_(isContextCurrent()); // THE CONTEXT HAS NOT BEEN MADE CURRENT
    bool bMain = isMainThread();
    double dLast = getTime();
    while (!getContext()->getWindowShouldClose())
    {
        if (bMain) // input processing
        {
            double dNew = getTime();
            onInput(dNew - dLast);
            if (getExitcode() > 0) return getExitcode();
            dLast = dNew;
        }
        onRender(); // window renedering loop and swap buffers
        if (getExitcode() > 0) return getExitcode();
        getContext()->swapBuffers();
        while (dispatchMessage(&msg)) // thread event processing
        {
            if (!translateMessage(&msg))
            {
                onMessage(&msg);
                if (getExitcode() > 0) return getExitcode();
            }
        }
        if (bMain) // window event processing
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
    setBlockMessage(true); // void thread message queue and exit
    while (dispatchMessage(&msg))
    {
        if (!translateMessage(&msg))
        {
            onMessage(&msg);
            if (getExitcode() > 0) return getExitcode();
        }
    }
    onExit();
    return getExitcode();
}

void Thread::setBlockMessage(bool block)
{
    _YAGLPP_ASSERT_(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    _s.syncEnter(_m.iRef);
    _m.bBlockMessage = block;
    _s.syncLeave(_m.iRef);
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
    if (_m.bBlockMessage == false)
    {
        return _m._iDispatch++ < YAGLPP_INIT_SIZE;
    }
    return true;
}

HANDLE Thread::_handle() const
{
    _YAGLPP_ASSERT_(_m.hThread != NULL); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return _m.hThread;
}

void Thread::closeHandle()
{
    BOOL bResult = CloseHandle(_handle());
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO CLOSE THREAD HANDLE
    _m.hThread = NULL;
}

void Thread::exitThread(DWORD exitcode)
{
    _YAGLPP_ASSERT_(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    _YAGLPP_ASSERT_(_m.pWindow == nullptr); // SHOULD NOT BE USED WITH A WINDOWED THREAD
    ExitThread(exitcode);
}

_Ret_notnull_ const char* Thread::getArgValue(int index)
{
    _YAGLPP_ASSERT_((UINT)index < (UINT)_s.iArgc); // INVALID COMMAND LINE ARGUMENT INDEX
    return _s.pArgv[index];
}

_Ret_notnull_ Window* Thread::getContext() const
{
    _YAGLPP_ASSERT_(_m.pWindow != nullptr); // THREAD OBJECT HAS NO ASSOCIATED WINDOW
    return _m.pWindow;
}

DWORD Thread::getExitCodeThread()
{
    DWORD nExitCode;
    _YAGLPP_ASSERT_(!isMainThread()); // MAIN THREAD IS NOT APPLICABLE
    BOOL bResult = GetExitCodeThread(_handle(), &nExitCode);
    _YAGLPP_ASSERT_(bResult != 0); // FAILED TO GET THREAD EXIT CODE
    return nExitCode;
}

DWORD Thread::getThreadId() const
{
    _YAGLPP_ASSERT_(isThread()); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return _m.nThreadId;
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

bool Thread::postMessage(int msgid, Param x, Param y, Param z, Param w)
{
    _YAGLPP_ASSERT_(msgid >= 0); // MESSAGE ID MUST NOT BE NEGATIVE
    Message msg = { msgid, x, y, z, w, *_tlsThread() };
    return _message(&msg);
}

int Thread::resumeThread()
{
    DWORD nCount = ResumeThread(_handle());
    _YAGLPP_ASSERT_(nCount != (DWORD)-1); // FAILED TO RESUME THREAD
    return nCount;
}

void Thread::setContext(_In_ Window* window)
{
    _YAGLPP_ASSERT_(_m.pWindow == nullptr); // WINDOW OBJECT HAS BEEN ALREADY SET
    _m.pWindow = window;
    _m.bAutoDetele = true;
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

void Thread::setEventsTimeout(double timeout)
{
    _YAGLPP_ASSERT_(_s.dEventsTimeout == 0.0); // TIMEOUT VALUE HAS BEEN ALREADY SET
    _YAGLPP_ASSERT_((timeout >= 0.0) && (timeout <= 2.0)); // TIMEOUT VALUE IS OUT OF RANGE
    _s.dEventsTimeout = timeout;
}

int Thread::suspendThread()
{
    DWORD nCount = SuspendThread(_handle());
    _YAGLPP_ASSERT_(nCount != (DWORD)-1); // FAILED TO SUSPEND THREAD
    return nCount;
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
    glfwWaitEventsTimeout(_s.dEventsTimeout);
}
#endif // #ifdef _DEBUG
} // namespace glfw
