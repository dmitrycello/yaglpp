#pragma once
#include "glfw3pp.h"
namespace glfw {
/*GLFW thread priority enumerator*/
enum class ThreadPriority : int
{
    /*Base priority of 1 for all classes, and of 16 for <RealtimePriorityClass> processes*/
    ThreadPriorityIdle = THREAD_PRIORITY_IDLE,

    /*Priority 2 points below the priority class*/
    ThreadPriorityLowest = THREAD_PRIORITY_LOWEST,

    /*Priority 1 point below the priority class*/
    ThreadPriorityBelowNormal = THREAD_PRIORITY_BELOW_NORMAL,

    /*Normal priority for the priority class*/
    ThreadPriorityNormal = THREAD_PRIORITY_NORMAL,

    /*Priority 1 point above the priority class*/
    ThreadPriorityAboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,

    /*Priority 2 points above the priority class*/
    ThreadPriorityHighest = THREAD_PRIORITY_HIGHEST,

    /*Base priority of 15 for all classes, and of 31 for <RealtimePriorityClass> processes*/
    ThreadPriorityTimeCritical = THREAD_PRIORITY_TIME_CRITICAL,

    /*Begin background processing mode. The system lowers the resource scheduling priorities of the thread so that it can perform background work without significantly affecting activity in the foreground. This value can be specified only if hThread is a handle to the current thread. The function fails if the thread is already in background processing mode*/
    ThreadModeBackgroundBegin = THREAD_MODE_BACKGROUND_BEGIN,

    /*End background processing mode. The system restores the resource scheduling priorities of the thread as they were before the thread entered background processing mode. This value can be specified only if hThread is a handle to the current thread. The function fails if the thread is not in background processing mode*/
    ThreadModeBackgroundEnd = THREAD_MODE_BACKGROUND_END,
};

/*GLFW inter-thread message structure*/
struct ThreadMessage
{
    /*Message id number*/
    int msgid;

    /*Additional message-specific information*/
    WPARAM wparam;

    /*Additional message-specific information*/
    LPARAM lparam;

    /*The sender thread object*/
    Thread* sender;

private:
    friend Thread;
    ThreadMessage* _next; // Reference to next message
};

/*Retreives the pointer to the current thread object
@return Pointer to current thread object*/
_Ret_notnull_ Thread* getCurrentThread();

/*Retreives the pointer to the main thread object
@return Pointer to main thread object*/
_Ret_notnull_ Thread* getMainThread();

/*GLFW Windows-based thread object root class*/
class Thread
{
private:
    friend ThreadSync;
    int m_iThreadId = 0;                // Thread id
    DWORD m_dwExitcode = 0;             // Exit code
    HANDLE m_hThread = nullptr;         // Thread handle
    Thread* m_pNextsync = nullptr;      // Next thread in sync queue
    ThreadMessage* m_pQueue = nullptr;  // Circular message queue (last)
    static int m_sArgc;                 // Cmdline arg number
    static char** m_sArgv;              // Cmdline arg values
    static Thread* m_sMainThread;       // Main thread
    static ThreadSync m_sThreadSync;    // Built-in sync object
    HANDLE _handle() const;
    static Thread** _tlsThread()
    {
        thread_local Thread* tls = 0; return &tls;
    }

protected:
    /*An exit thread event handler, triggered when the thread is at the exit stage*/
    virtual void onExitThread() {}

    /*An init thread event handler, triggered when the thread is at the initialization stage. The thread non-zero exit code forces the thread to exit*/
    virtual void onInitThread() {}

    /*A run thread event handler, triggered when the thread is at the run stage*/
    virtual void onRunThread() {}

public:
    /*(1) Constructs the Windows thread object*/
    Thread();

    /*(2) Constructs the Windows thread object with <createThread>*/
    Thread(bool suspended)
    {
        createThread(suspended);
    }

    /*Creates a thread for a specified Thread object to execute within the virtual address space of the calling process
    @param True to start the thread in suspended state, default false*/
    void createThread(bool suspended = false);

    /*Dispatches the first inter-thread message in the message queue of the calling thread. If the message is present, copies the message data into <ThreadMessage> structure and then removes it from the message queue
    @param [out] Points to the thread message structure receiving the message data
    @return True if the message is dispatched, false otherwise*/
    static bool dispatchMessage(_Out_ ThreadMessage* message);

    /*Enters thread's built-in synchronization spinlock
    @param The spinlock bit number, must be from 0 to 29*/
    static void enterLock(int bit);

    /*Enters thread's built-in synchronization queue. Suspends the current thread if the queue is not empty
    @param The spinlock bit number, must be from 0 to 29*/
    static void enterQueue(int bit);

    /*Unconditionally ends the current thread of the thread object. Must be called by the current thread
    @param The exit code for the thread*/
    void exitThread(int exitcode);

    /*Gets the number of application command line arguments
    @return The number of command line arguments. Must be at least 1*/
    static int getArgCount()
    {
        return m_sArgc;
    }

    /*Gets rhe specified command line argument
    @param The index of command line argument
    @return The null-terminating string of specified command line argument*/
    static _Ret_notnull_ const char* getArgValue(int index);

    /*Retreives the pointer to the current thread object
    @return Pointer to current thread object*/
    static _Ret_notnull_ Thread* getCurrentThread();

    /*Retreives the current exit code of the thread object
    @return The current thread object exit code*/
    DWORD getExitCode() const
    {
        return m_dwExitcode;
    }

    /*Retrieves the termination status of the specified thread
    @return The thread termination status*/
    int getExitCodeThread() const;

    /*Retreives the pointer to the main thread object
    @return Pointer to main thread object*/
    static _Ret_notnull_ Thread* getMainThread();

    /*Retrieves the id of currently running thread
    @return Running thread's id*/
    int getThreadId() const;

    /*Retrieves the priority value for the specified thread
    @return Thread's priority level*/
    ThreadPriority getThreadPriority() const;

    /*Retrieves the priority boost control state of the specified thread
    @return True if dynamic boosting is disabled, false otherwise*/
    bool getThreadPriorityBoost() const;

    /*Checks if the thread object is currently calling thread
    @return True if current thread, false otherwise*/
    bool isCurrentThread() const;

    /*(1) Checks if the thread object is in the syncronization queue
    @return True if thread object is in the queue, false otherwise*/
    bool isQueued() const
    {
        return m_pNextsync != nullptr;
    }

    /*(2) Checks if thread's built-in sync object bit is in the syncronization queue
    @return True if sync object bit is in the queue, false otherwise*/
    static bool isQueued(int bit);

    /*Checks if the thread did not exit
    @return True if thread is still alive, false otherwise*/
    bool isStillAlive() const
    {
        return getExitCodeThread() == STILL_ACTIVE;
    }

    /*Checks if thread object is currently suspended
    @return True if thread object is suspended, false otherwise*/
    bool isSuspended() const;

    /*Checks if valid thread object
    @return True if valid thread object, false otherwise*/
    bool isThread() const
    {
        return m_hThread != NULL;
    }

    /*Releases thread's built-in synchronization spinlock
    @param The spinlock bit number, must be from 0 to 29*/
    static void leaveLock(int bit);

    /*Leaves thread's built-in synchronization queue. Resumes the next thread if the queue is not empty
    @param The spinlock bit number, must be from 0 to 29*/
    static void leaveQueue(int bit);

    /*Adds the message to specified thread object's message queue. The method should not be called from the current thread
    @param Message id number
    @param Additional message-specific information
    @param Additional message-specific information*/
    void postMessage(int msgid, WPARAM wparam, LPARAM lparam);

    /*Decrements a thread's suspend count. When the suspend count is decremented to zero, the execution of the thread is resumed
    @return The thread's previous suspend count*/
    int resumeThread();

    /*Set thread object's internal exit code value
    @param Current object exit code value*/
    void setExitCode(int exitcode);

    /*Sets a preferred processor for a thread, the system schedules threads on their preferred processors whenever possible
    @param The number of the preferred processor for the thread
    @return The previous preferred processor*/
    int setThreadIdealProcessor(int processor) const;

    /*Sets the priority value for the specified thread
    @param The priority value for the thread*/
    void setThreadPriority(ThreadPriority priority) const;

    /*Disables or enables the ability of the system to temporarily boost the priority of a thread
    @param True to disable dynamic boosting*/
    void setThreadPriorityBoost(bool disable) const;

    /*Suspends the specified thread
    @return The thread's previous suspend count*/
    int suspendThread();

    /*Terminates a thread with specified exit code. Does not provide apprppriate cleanup
    @param The exit code for the thread*/
    void terminateThread(int exitcode) const;

    /*Tries entering thread's built-in synchronization spinlock. If succeeded, the thread takes the ownership
    @param The spinlock bit number, must be from 0 to 29
    @return True if the spinlock bit was unlocked, false otherwise*/
    static bool tryLock(int bit);

    /*Tries entering thread's built-in synchronization queue. Returns immediatelly, if the queue is not empty, the thread takes the ownership
    @param The spinlock bit number, must be from 0 to 29
    @return True if current thread has entered synchronization queue, false otherwise*/
    static bool tryQueue(int bit);

    /*Waits until the specified object is in the signaled state*/
    void waitForSingleObject() const;

    /*Resumes the execution of the thread regardless of the thread suspension count*/
    void wakeThread();

#ifdef YAGLPP_BUILD_LIB
    static DWORD _thread(LPVOID param);
    static int _main(int argc, char** argv)
    {
        m_sArgc = argc; m_sArgv = argv;
        return _thread(getMainThread());
    }
#endif // #ifdef YAGLPP_BUILD_LIB
}; // class Thread

/*GLFW thread synchronization object root class*/
class ThreadSync
{
private:
    volatile LONG m_nSpinlock = 0;  // Spinlock data
    Thread* m_pLastsync[32] = { nullptr };  // Last thread

public:
    /*Enters thread synchronization spinlock
    @param The spinlock bit number, must be from 0 to 31*/
    void enterLock(int bit);

    /*Enters thread synchronization queue. Suspends the current thread if the queue is not empty
    @param The spinlock bit number, must be from 0 to 31*/
    void enterQueue(int bit);

    /*Checks if thread sync object bit is in the syncronization queue
    @return True if sync object bit is in the queue, false otherwise*/
    bool isQueued(int bit) const;

    /*Releases thread synchronization spinlock
    @param The spinlock bit number, must be from 0 to 31*/
    void leaveLock(int bit);

    /*Leaves thread synchronization queue. Resumes the next thread if the queue is not empty
    @param The spinlock bit number, must be from 0 to 31*/
    void leaveQueue(int bit);

    /*Tries entering thread synchronization spinlock. If succeeded, the thread takes the ownership
    @param The spinlock bit number, must be from 0 to 31
    @return True if the spinlock bit was unlocked, false otherwise*/
    bool tryLock(int bit);

    /*Tries entering thread synchronization queue. Returns immediatelly, if the queue is not empty, the thread takes the ownership
    @param The spinlock bit number, must be from 0 to 31
    @return True if current thread has entered synchronization queue, false otherwise*/
    bool tryQueue(int bit);
};

/*GLFW windowed application thread object class derived from <Thread>*/
class WindowThread : public Thread
{
protected:
    Window* m_pWindow; // Thread's window

    /*An exit thread event handler, triggered when the thread is at the exit stage*/
    virtual void onExitThread();

    /*A post message event handler, triggered when the thread dispatches posted message
    @param Message id number
    @param Additional message-specific information
    @param Additional message-specific information
    @param The sender thread object, or NULL*/
    virtual void onPostMessage(int msgid, WPARAM wParam, LPARAM lParam, Thread* sender) {}

    /*A render window event handler, triggered at every iteration of GLFW window rendering loop. The thread non-zero exit code forces the rendering loop to exit, before buffer swap and message processing occure*/
    virtual void onRenderWindow() {}

    /*A run thread event handler, triggered when the thread is at the run stage*/
    virtual void onRunThread();

public:
    WindowThread()
    {
        m_pWindow = nullptr;
    }

    /*Check if the thread's window is associated with current context
    @return True if current context exist, false otherwise*/
    bool isContextWindow() const
    {
        return m_pWindow != nullptr;
    }

    /*Gets the current context's window object associated with specified thread
    @return The current context's window object*/
    _Ret_notnull_ Window* getContextWindow() const;
}; // class WindowThread : public Thread

inline _Ret_notnull_ Thread* getCurrentThread()
{
    return Thread::getCurrentThread();
}

inline _Ret_notnull_ Thread* getMainThread()
{
    return Thread::getMainThread();
}

#ifndef _DEBUG
inline HANDLE Thread::_handle() const
{
    return m_hThread;
}

inline void Thread::enterLock(int bit)
{
    m_sThreadSync.enterLock(bit);
}

inline void Thread::enterQueue(int bit)
{
    m_sThreadSync.enterQueue(bit);
}

inline void Thread::exitThread(int exitcode)
{
    ExitThread(exitcode);
}

inline _Ret_notnull_ const char* Thread::getArgValue(int index)
{
    return m_sArgv[index];
}

inline _Ret_notnull_ Thread* Thread::getCurrentThread()
{
    return *_tlsThread();
}

inline int Thread::getExitCodeThread() const
{
    DWORD dwExitCode; GetExitCodeThread(_handle(), &dwExitCode); return dwExitCode;
}

inline _Ret_notnull_ Thread* Thread::getMainThread()
{
    return Thread::m_sMainThread;
}

inline int Thread::getThreadId() const
{
    return (m_iThreadId < 0) ? -(m_iThreadId) : m_iThreadId;
}

inline ThreadPriority Thread::getThreadPriority() const
{
    return (ThreadPriority)GetThreadPriority(_handle());
}

inline bool Thread::getThreadPriorityBoost() const
{
    BOOL bDisable; GetThreadPriorityBoost(_handle(), &bDisable); return bDisable;
}

inline bool Thread::isCurrentThread() const
{
    return *_tlsThread() == this;
}

inline bool Thread::isQueued(int bit)
{
    m_sThreadSync.isQueued(bit);
}

inline bool Thread::isSuspended() const
{
    return m_iThreadId < 0;
}

inline void Thread::leaveLock(int bit)
{
    m_sThreadSync.leaveLock(bit);
}

inline void Thread::leaveQueue(int bit)
{
    m_sThreadSync.leaveQueue(bit);
}

inline int Thread::setThreadIdealProcessor(int processor) const
{
    return SetThreadIdealProcessor(_handle(), processor);
}

inline void Thread::setThreadPriority(ThreadPriority priority) const
{
    SetThreadPriority(_handle(), (int)priority);
}

inline void Thread::setThreadPriorityBoost(bool disable) const
{
    SetThreadPriorityBoost(_handle(), disable);
}

inline void Thread::terminateThread(int exitcode) const
{
#pragma warning(push)
#pragma warning(disable : 6258)
    TerminateThread(_handle(), exitcode);
#pragma warning(pop)
}

inline bool Thread::tryLock(int bit)
{
    return m_sThreadSync.tryLock(bit);
}

inline bool Thread::tryQueue(int bit)
{
    return m_sThreadSync.tryQueue(bit);
}

inline void Thread::waitForSingleObject() const
{
    WaitForSingleObject(_handle(), INFINITE);
}

inline bool ThreadSync::isQueued(int bit) const
{
    return m_pLastsync[bit] != nullptr;
}

inline void ThreadSync::leaveLock(int bit)
{
    _interlockedbittestandreset(&m_nSpinlock, bit);
}

inline bool ThreadSync::tryLock(int bit)
{
    return !_interlockedbittestandset(&m_nSpinlock, bit);
}

inline _Ret_notnull_ Window* WindowThread::getContextWindow() const
{
    return m_pWindow;
}
#endif // #ifndef _DEBUG
} // namespace gl
