#define YAGLPP_BUILD_LIB
#include <yaglpp/Thread.h>
#include <yaglpp/Window.h>
#include <yaglpp/Joystick.h>
#define YAGLPP_LOCK_LAST_BIT 29
#define YAGLPP_LOCK_EXIT_BIT 30
#define YAGLPP_LOCK_POST_BIT 31
#define YAGLPP_LOCK_SYNC_BIT 31
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
DWORD Thread::_thread(LPVOID param)
{
    Thread* pThread = (Thread*)param;
    *_tlsThread() = pThread;
    pThread->onInitThread();
    if (pThread->m_dwExitcode)
    {
        return pThread->m_dwExitcode;
    }
    pThread->onRunThread();
    pThread->onExitThread();
    return pThread->m_dwExitcode;
}

Thread::Thread()
{
    if (m_sMainThread == nullptr)
    {
        *_tlsThread() = this;
        m_sMainThread = this;
        m_iThreadId = GetCurrentThreadId();
        m_hThread = OpenThread(THREAD_SUSPEND_RESUME, TRUE, m_iThreadId);
    }
}

void Thread::createThread(bool suspended)
{
    DWORD dwThreadId;
    YAGLPP_ASSERT(!isThread()); // GLFW THREAD OBJECT HAS CURRENTLY RUNNING THREAD
    m_hThread = CreateThread(NULL, 0, &_threadProc, this, (suspended) ? CREATE_SUSPENDED : 0, &dwThreadId);
    YAGLPP_ASSERT(isThread()); // FAILED TO CREATE THREAD
    m_iThreadId = suspended ? -((int)dwThreadId) : dwThreadId;
}

bool Thread::dispatchMessage(_Out_ ThreadMessage* message)
{
    Thread* pThread = *_tlsThread();
    m_sThreadSync.enterLock(YAGLPP_LOCK_POST_BIT); // Start critical data
    if (pThread->m_pQueue != nullptr)
    {
        ThreadMessage* pFirst = pThread->m_pQueue->_next;
        if (pFirst == pThread->m_pQueue)
        {
            pThread->m_pQueue = nullptr;
        }
        else
        {
            pThread->m_pQueue->_next = pFirst->_next;
        }
        m_sThreadSync.leaveLock(YAGLPP_LOCK_POST_BIT); // End critical data
        message->msgid = pFirst->msgid;
        message->wparam = pFirst->wparam;
        message->lparam = pFirst->lparam;
        message->sender = pFirst->sender;
        YAGLPP_FREE(pFirst);
        return true;
    }
    else
    {
        m_sThreadSync.leaveLock(YAGLPP_LOCK_POST_BIT); // End critical data
        message->msgid = 0; // SAL requirement
        message->wparam = 0;
        message->lparam = 0;
        message->sender = nullptr;
        return false;
    }
}

void Thread::postMessage(int msgid, WPARAM wparam, LPARAM lparam)
{
    ThreadMessage* pMessage = (ThreadMessage*)YAGLPP_MALLOC(sizeof(ThreadMessage));
    YAGLPP_ASSERT(pMessage != nullptr); // FAILED TO ALLOCATE MEMORY
    pMessage->msgid = msgid;
    pMessage->wparam = wparam;
    pMessage->lparam = lparam;
    pMessage->sender = *_tlsThread();
    m_sThreadSync.enterLock(YAGLPP_LOCK_POST_BIT); // Start critical data
    if (m_pQueue == nullptr)
    {
        m_pQueue = pMessage;
        pMessage->_next = pMessage;
    }
    else
    {
        ThreadMessage* pFirst = m_pQueue->_next;
        m_pQueue->_next = pMessage;
        m_pQueue = pMessage;
        pMessage->_next = pFirst;
    }
    m_sThreadSync.leaveLock(YAGLPP_LOCK_POST_BIT); // End critical data
}

int Thread::resumeThread()
{
    YAGLPP_ASSERT(!isQueued()); // GLFW THREAD IS QUEUED
    DWORD dwCount = ResumeThread(_handle());
    YAGLPP_ASSERT(dwCount != (DWORD)-1); // FAILED TO RESUME THREAD
    if (dwCount == 1)
    {
        m_iThreadId = -(m_iThreadId);
    }
    return dwCount;
}

void Thread::setExitCode(int exitcode)
{
    m_sThreadSync.enterLock(YAGLPP_LOCK_EXIT_BIT); // Start critical data
    m_dwExitcode = exitcode;
    m_sThreadSync.leaveLock(YAGLPP_LOCK_EXIT_BIT); // End critical data
}

int Thread::suspendThread()
{
    YAGLPP_ASSERT(!isQueued()); // GLFW THREAD IS QUEUED
    if (m_iThreadId > 0)
    {
        m_iThreadId = -(m_iThreadId); // Toggle suspension flag
    }
    DWORD dwCount = SuspendThread(_handle());
    YAGLPP_ASSERT(dwCount != (DWORD)-1); // FAILED TO SUSPEND THREAD
    return dwCount;
}

void Thread::wakeThread()
{
    YAGLPP_ASSERT(!isQueued()); // GLFW THREAD IS QUEUED
    DWORD dwCount = 0;
    do
    {
        dwCount = ResumeThread(_handle());
        YAGLPP_ASSERT(dwCount != (DWORD)-1); // FAILED TO RESUME THREAD
    }
    while (dwCount > 1);
    m_iThreadId = -(m_iThreadId); // Toggle suspension flag
}

void ThreadSync::enterLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_SYNC_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    LONG nMask = 1 << bit;
    while (_interlockedbittestandset(&m_nSpinlock, bit))
    {
        while (m_nSpinlock & nMask);
    }
}

void ThreadSync::enterQueue(int bit)
{
    enterLock(bit); // Start critical data
    Thread *pCurrent = *Thread::_tlsThread(), *pLastsync = m_pLastsync[bit];
    YAGLPP_ASSERT(!pCurrent->isQueued()); // CURRENT THREAD OBJECT IS QUEUED
    m_pLastsync[bit] = pCurrent;
    pCurrent->m_pNextsync = pCurrent;
    if (pLastsync != nullptr)
    {
        pLastsync->m_pNextsync = pCurrent;
        if (pCurrent->m_iThreadId > 0)
        {
            pCurrent->m_iThreadId = -(pCurrent->m_iThreadId);
        }
        leaveLock(bit); // End critical data
        DWORD dwCount = SuspendThread(pCurrent->m_hThread);
        YAGLPP_ASSERT(dwCount == 0UL); // FAILED TO SUSPEND THREAD IN THE QUEUE
    }
    else leaveLock(bit); // End critical data
}

void ThreadSync::leaveQueue(int bit)
{
    enterLock(bit); // Start critical data
    Thread *pCurrent = *Thread::_tlsThread(), *pNextsync = pCurrent->m_pNextsync;
    YAGLPP_ASSERT(pCurrent->isQueued()); // CURRENT THREAD OBJECT IS NOT QUEUED
    pCurrent->m_pNextsync = nullptr;
    if (pNextsync == pCurrent)
    {
        m_pLastsync[bit] = nullptr; // End queue
        leaveLock(bit); // End critical data
    }
    else
    {
        pNextsync->m_iThreadId = -(pNextsync->m_iThreadId);
        leaveLock(bit); // End critical data
        DWORD dwCount = ResumeThread(pNextsync->m_hThread);
        YAGLPP_ASSERT(dwCount == 1UL); // FAILED TO RESUME THREAD FROM THE QUEUE
    }
}

bool ThreadSync::tryQueue(int bit)
{
    bool bResult;
    enterLock(bit); // Start critical data
    Thread* pCurrent = *Thread::_tlsThread();
    YAGLPP_ASSERT(!pCurrent->isQueued()); // CURRENT THREAD OBJECT IS QUEUED
    if (bResult = (m_pLastsync[bit] == nullptr))
    {
        m_pLastsync[bit] = pCurrent;
        pCurrent->m_pNextsync = pCurrent;
    }
    leaveLock(bit); // End critical data
    return bResult;
}

void WindowThread::onExitThread()
{
    if (isContextWindow())
    {
        delete m_pWindow;
        m_pWindow = nullptr;
    }
}

void WindowThread::onRunThread()
{
    ThreadMessage msg;
    Window* pWindow = getContextWindow();
    while (!pWindow->windowShouldClose())
    {
        onRenderWindow();
        if (getExitCode())
        {
            break;
        }
        pWindow->swapBuffers();
        pollEvents();
        while (dispatchMessage(&msg))
        {
            onPostMessage(msg.msgid, msg.wparam, msg.lparam, msg.sender);
        }
    }
}

#ifdef _DEBUG
HANDLE Thread::_handle() const
{
    YAGLPP_ASSERT(m_hThread != NULL); // GLFW THREAD OBJECT HAS NO RUNNING THREAD
    return m_hThread;
}

void Thread::enterLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    m_sThreadSync.enterLock(bit);
}

void Thread::enterQueue(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    m_sThreadSync.enterQueue(bit);
}

void Thread::exitThread(int exitcode)
{
    YAGLPP_ASSERT(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    ExitThread(exitcode);
}

_Ret_notnull_ const char* Thread::getArgValue(int index)
{
    YAGLPP_ASSERT((UINT)index < (UINT)m_sArgc); // INVALID COMMAND LINE ARGUMENT INDEX
    return m_sArgv[index];
}

_Ret_notnull_ Thread* Thread::getCurrentThread()
{
    YAGLPP_ASSERT(*_tlsThread() != nullptr); // GLFW THREAD OBJECT IS UNINITIALIZED
    return *_tlsThread();
}

int Thread::getExitCodeThread() const
{
    DWORD dwExitCode, dwResult = GetExitCodeThread(_handle(), &dwExitCode);
    YAGLPP_ASSERT(dwResult != 0); // FAILED TO GET THREAD EXIT CODE
    return dwExitCode;
}

_Ret_notnull_ Thread* Thread::getMainThread()
{
    YAGLPP_ASSERT(Thread::m_sMainThread != nullptr); // MAIN THREAD OBJECT IS UNINITIALIZED
    return Thread::m_sMainThread;
}

int Thread::getThreadId() const
{
    YAGLPP_ASSERT(isThread()); // GLFW THREAD OBJECT HAS NO RUNNING THREAD
    return (m_iThreadId < 0) ? -(m_iThreadId) : m_iThreadId;
}

ThreadPriority Thread::getThreadPriority() const
{
    int iPriority = GetThreadPriority(_handle());
    YAGLPP_ASSERT(iPriority != THREAD_PRIORITY_ERROR_RETURN); // FAILED TO GET THREAD PRIORITY
    return (ThreadPriority)iPriority;
}

bool Thread::getThreadPriorityBoost() const
{
    BOOL bDisable, bResult = GetThreadPriorityBoost(_handle(), &bDisable);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO GET THREAD PRIORITY BOOST
    return bDisable;
}

bool Thread::isCurrentThread() const
{
    YAGLPP_ASSERT(*_tlsThread() != nullptr); // GLFW THREAD OBJECT IS UNINITIALIZED
    return *_tlsThread() == this;
}

bool Thread::isQueued(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return m_sThreadSync.isQueued(bit);
}

bool Thread::isSuspended() const
{
    YAGLPP_ASSERT(isThread()); // GLFW THREAD OBJECT HAS NO RUNNING THREAD
    return m_iThreadId < 0;
}

void Thread::leaveLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    m_sThreadSync.leaveLock(bit);
}

void Thread::leaveQueue(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    m_sThreadSync.leaveQueue(bit);
}

int Thread::setThreadIdealProcessor(int processor) const
{
    YAGLPP_ASSERT((DWORD)processor < MAXIMUM_PROCESSORS); // INVALID INDEX OF IDEAL PROCESSOR FOR A THREAD OBJECT
    DWORD dwResult = SetThreadIdealProcessor(_handle(), processor);
    YAGLPP_ASSERT(dwResult != (DWORD)-1); // FAILED TO SET THREAD IDEAL PROCESSOR
    return dwResult;
}

void Thread::setThreadPriority(ThreadPriority priority) const
{
    BOOL bResult = SetThreadPriority(_handle(), (int)priority);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO SET THREAD PRIORITY
}

void Thread::setThreadPriorityBoost(bool disable) const
{
    BOOL bResult = SetThreadPriorityBoost(_handle(), disable);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO SET THREAD PRIORITY BOOST
}

void Thread::terminateThread(int exitcode) const
{
#pragma warning(push)
#pragma warning(disable : 6258)
    BOOL bResult = TerminateThread(_handle(), exitcode);
#pragma warning(pop)
    YAGLPP_ASSERT(bResult != 0); // FAILED TO TERMINATE THREAD
}

bool Thread::tryLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return m_sThreadSync.tryLock(bit);
}

bool Thread::tryQueue(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return m_sThreadSync.tryQueue(bit);
}

void Thread::waitForSingleObject() const
{
    DWORD dwResult = WaitForSingleObject(_handle(), INFINITE);
    YAGLPP_ASSERT(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR SINGLE OBJECT
}

bool ThreadSync::isQueued(int bit) const
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_SYNC_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return m_pLastsync[bit] != nullptr;
}

void ThreadSync::leaveLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_SYNC_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    _interlockedbittestandreset(&m_nSpinlock, bit);
}

bool ThreadSync::tryLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= YAGLPP_LOCK_SYNC_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return !_interlockedbittestandset(&m_nSpinlock, bit);
}

_Ret_notnull_ Window* WindowThread::getContextWindow() const
{
    YAGLPP_ASSERT(m_pWindow != nullptr); // NO OPENGL CONTEXT EXIST ON THE CALLING THREAD
    return m_pWindow;
}
#endif // #ifdef _DEBUG
} // namespace gl
