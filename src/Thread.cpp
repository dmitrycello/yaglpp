#define YAGLPP_BUILD_LIB
#include <yaglpp/Thread.h>
#include <yaglpp/Window.h>
#include <yaglpp/Joystick.h>
#define _LOCK_LAST_BIT 29
#define _LOCK_POST_BIT 30
#define _LOCK_EXIT_BIT 31
#ifndef YAGLPP_NO_AFX_LAYOUT
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
void Thread::_lockBit(int bit)
{
    LONG nMask = 1 << bit;
    while (_interlockedbittestandset(&m_nSpinlock, bit))
    {
        while (m_nSpinlock & nMask); // Read-only spin
    }
}

DWORD Thread::_thread(LPVOID param)
{
    Thread* pThread = (Thread*)param;
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
    m_nSpinlock = 0;
    m_dwThreadId = 0;
    m_dwExitcode = 0;
    m_bError = false;
    m_hThread = NULL;
    m_lpLast = nullptr;
    m_lpFirst = nullptr;
    if (m_sMainThread == nullptr)
    {
        m_sMainThread = this;
        m_hThread = GetCurrentThread();
        m_dwThreadId = GetCurrentThreadId();
    }
}

void Thread::createThread(bool suspended)
{
    YAGLPP_ASSERT(!isThread()); // GLFW THREAD OBJECT HAS CURRENTLY RUNNING THREAD
    m_hThread = CreateThread(NULL, 0, &_threadProc, this, (suspended) ? CREATE_SUSPENDED : 0, &m_dwThreadId);
    m_bError = (m_hThread == NULL);
}

bool Thread::dispatchMessage(_Out_ ThreadMessage* message)
{
    bool bResult;
    YAGLPP_ASSERT(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    _LPPACK lpPack = m_lpFirst;
    _lockBit(_LOCK_POST_BIT); // Start critical data
    if (bResult = (lpPack != nullptr))
    {
        m_lpFirst = lpPack->next;
    }
    _unlockBit(_LOCK_POST_BIT); // End critical data
    if (bResult)
    {
        message->msgid = lpPack->msgid;
        message->wparam = lpPack->wparam;
        message->lparam = lpPack->lparam;
        message->sender = lpPack->sender;
        YAGLPP_FREE(lpPack);
    }
    else
    {
        message->msgid = 0; // SAL requirement
        message->wparam = 0;
        message->lparam = 0;
        message->sender = nullptr;
    }
    return bResult;
}

int Thread::getExitCodeThread()
{
    DWORD dwExitCode;
    BOOL bResult = GetExitCodeThread(_handle(), &dwExitCode);
    m_bError = (bResult == 0);
    return dwExitCode;
}

ThreadPriority Thread::getThreadPriority()
{
    int iPriority = GetThreadPriority(_handle());
    m_bError = (iPriority == THREAD_PRIORITY_ERROR_RETURN);
    return (ThreadPriority)iPriority;
}

bool Thread::getThreadPriorityBoost()
{
    BOOL bDisable;
    BOOL bResult = GetThreadPriorityBoost(_handle(), &bDisable);
    m_bError = (bResult == 0);
    return bDisable;
}

void Thread::postMessage(int msgid, WPARAM wparam, LPARAM lparam, _In_opt_ Thread* sender)
{
    YAGLPP_ASSERT(!isCurrentThread()); // METHOD IS CALLED BY THE CURRENT THREAD
    _LPPACK lpPack = (_LPPACK)YAGLPP_MALLOC(sizeof(_PACK));
    lpPack->next = nullptr;
    lpPack->msgid = msgid;
    lpPack->wparam = wparam;
    lpPack->lparam = lparam;
    lpPack->sender = sender;
    _lockBit(_LOCK_POST_BIT); // Start critical data
    if (m_lpFirst)
    {
        m_lpLast->next = lpPack;
    }
    else
    {
        m_lpFirst = lpPack;
    }
    m_lpLast = lpPack;
    _unlockBit(_LOCK_POST_BIT); // End critical data
}

int Thread::resumeThread()
{
    DWORD dwSuspend = ResumeThread(_handle());
    m_bError = (dwSuspend == (DWORD)-1);
    return dwSuspend;
}

void Thread::setExitCode(int exitcode)
{
    _lockBit(_LOCK_EXIT_BIT); // Start critical data
    m_dwExitcode = exitcode;
    _unlockBit(_LOCK_EXIT_BIT); // End critical data
}

int Thread::setThreadIdealProcessor(int processor)
{
    YAGLPP_ASSERT((DWORD)processor < MAXIMUM_PROCESSORS); // INVALID INDEX OF IDEAL PROCESSOR FOR A THREAD OBJECT
    DWORD dwResult = SetThreadIdealProcessor(_handle(), processor);
    m_bError = (dwResult == (DWORD)-1);
    return dwResult;
}

void Thread::setThreadPriority(ThreadPriority priority)
{
    BOOL bResult = SetThreadPriority(_handle(), (int)priority);
    m_bError = (bResult == 0);
}

void Thread::setThreadPriorityBoost(bool disable)
{
    BOOL bResult = SetThreadPriorityBoost(_handle(), disable);
    m_bError = (bResult == 0);
}

int Thread::suspendThread()
{
    DWORD dwSuspend = SuspendThread(_handle());
    m_bError = (dwSuspend == (DWORD)-1);
    return dwSuspend;
}

void Thread::terminateThread(int exitcode)
{
#pragma warning(push)
#pragma warning(disable : 6258)
    m_bError = (TerminateThread(_handle(), exitcode) == 0);
#pragma warning(pop)
}

void Thread::waitForSingleObject()
{
    DWORD dwResult = WaitForSingleObject(_handle(), INFINITE);
    m_bError = (dwResult == WAIT_FAILED);
}

void ThreadWnd::onExitThread()
{
    if (isContextWindow())
    {
        delete m_pWindow;
        m_pWindow = nullptr;
    }
}

void ThreadWnd::onRunThread()
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
HANDLE Thread::_handle()
{
    YAGLPP_ASSERT(m_hThread != NULL); // GLFW THREAD OBJECT HAS NO RUNNING THREAD
    return m_hThread;
}

void Thread::enterLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= _LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    _lockBit(bit); // Start critical data
}

void Thread::exitThread(int exitcode)
{
    YAGLPP_ASSERT(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    ExitThread(exitcode);
}

_Ret_notnull_ const char* Thread::getArgValue(int index)
{
    YAGLPP_ASSERT((unsigned int)index < (unsigned int)m_sArgc); // INVALID COMMAND LINE ARGUMENT INDEX
    return m_sArgv[index];
}

_Ret_notnull_ Thread* Thread::getMainThread()
{
    YAGLPP_ASSERT(Thread::m_sMainThread != nullptr); // MAIN THREAD OBJECT IS UNINITIALIZED
    return Thread::m_sMainThread;
}

int Thread::getThreadId()
{
    YAGLPP_ASSERT(isThread()); // GLFW THREAD OBJECT HAS NO RUNNING THREAD
    return m_dwThreadId;
}

void Thread::leaveLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= _LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    _unlockBit(bit); // End critical data
}

bool Thread::tryLock(int bit)
{
    YAGLPP_ASSERT((UINT)bit <= _LOCK_LAST_BIT); // THE SPINLOCK BIT NUMBER IS INVALID
    return !_interlockedbittestandset(&m_nSpinlock, bit);
}

_Ret_notnull_ Window* ThreadWnd::getContextWindow()
{
    YAGLPP_ASSERT(m_pWindow != nullptr); // NO OPENGL CONTEXT EXIST ON THE CALLING THREAD
    return m_pWindow;
}
#endif // #ifdef _DEBUG
} // namespace gl
