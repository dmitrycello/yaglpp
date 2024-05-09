#pragma once
#include "glfw3pp.h"
namespace glfw {
class Thread;
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
};

/*Retreives the pointer to the main thread object
@return Pointer to main thread object*/
_Ret_notnull_ Thread* getMainThread();

/*GLFW OS Windows based application thread object root class*/
class Thread
{
private:
    typedef struct _PACK {
        _PACK* next;    // Next package
        int msgid;      // Message id
        WPARAM wparam;  // Message data
        LPARAM lparam;  // Message data
        Thread* sender; // Sender thread
    } *_LPPACK;

    bool m_bError; // Error flag
    DWORD m_dwThreadId; // Thread id
    DWORD m_dwExitcode; // Exit code
    HANDLE m_hThread; // Thread handle
    _LPPACK m_lpLast; // Last-in package
    _LPPACK m_lpFirst; // First-out package
    static int m_sArgc; // Cmdline arg number
    static char** m_sArgv; // Cmdline arg values
    static Thread* m_sMainThread; // Main thread
    volatile LONG m_nSpinlock; // Spinlock data
    void _lockBit(int bit);
    HANDLE _handle();
    void _unlockBit(int bit)
    {
        _interlockedbittestandreset(&m_nSpinlock, bit);
    }

protected:
    /*An exit thread event handler, triggered when the thread is at the exit stage*/
    virtual void onExitThread() {}

    /*An init thread event handler, triggered when the thread is at the initialization stage. The thread non-zero exit code forces the thread to exit*/
    virtual void onInitThread() {}

    /*A run thread event handler, triggered when the thread is at the run stage*/
    virtual void onRunThread() {}

public:
    Thread();

    /*Creates a thread for a specified Thread object to execute within the virtual address space of the calling process. Sets the last error flag
    @param True to start the thread in suspended state, default false*/
    void createThread(bool suspended = false);

    /*Dispatches the first inter-thread message in the message queue of the calling thread. If the message is present, copies the message data into <ThreadMessage> structure and then removes it from the message queue
    @param [out] Points to the thread message structure receiving the message data
    @return True if the message is dispatched, false otherwise*/
    bool dispatchMessage(_Out_ ThreadMessage* message);

    /*Enters thread object's data synchronization spinlock
    @param The spinlock bit number, must be from 0 to 29*/
    void enterLock(int bit);

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

    /*Retreives the current exit code of the thread object
    @return The current thread object exit code*/
    DWORD getExitCode()
    {
        return m_dwExitcode;
    }

    /*Retrieves the termination status of the specified thread. Sets the last error flag
    @return The thread termination status*/
    int getExitCodeThread();

    /*Retreives the pointer to the main thread object
    @return Pointer to main thread object*/
    static _Ret_notnull_ Thread* getMainThread();

    /*Retrieves the id of currently running thread
    @return Running thread's id*/
    int getThreadId();

    /*Retrieves the priority value for the specified thread. Sets the last error flag
    @return Thread's priority level*/
    ThreadPriority getThreadPriority();

    /*Retrieves the priority boost control state of the specified thread. Sets the last error flag
    @return True if dynamic boosting is disabled, false otherwise*/
    bool getThreadPriorityBoost();

    /*Checks if the thread object is currently calling thread
    @return True if current thread, false otherwise*/
    bool isCurrentThread()
    {
        return getThreadId() == m_dwThreadId;
    }

    /*Checks if last thread specific operation failed
    @return True if last operation has failed, false otherwise*/
    bool isLastError()
    {
        return m_bError;
    }

    /*Checks if the thread did not exit. Sets the last error flag
    @return True if thread is still alive, false otherwise*/
    bool isStillAlive()
    {
        return getExitCodeThread() == STILL_ACTIVE;
    }

    /*Checks if valid thread object
    @return True if valid thread object, false otherwise*/
    bool isThread()
    {
        return m_hThread != NULL;
    }

    /*Releases thread object's data synchronization spinlock
    @param The spinlock bit number, must be from 0 to 29*/
    void leaveLock(int bit);

    /*Adds the message to specified thread object's message queue. The method should not be called from the current thread
    @param Message id number
    @param Additional message-specific information
    @param Additional message-specific information
    @param The sender thread object, default NULL*/
    void postMessage(int msgid, WPARAM wparam, LPARAM lparam, _In_opt_ Thread* sender = nullptr);

    /*Decrements a thread's suspend count. When the suspend count is decremented to zero, the execution of the thread is resumed. Sets the last error flag
    @return The thread's previous suspend count*/
    int resumeThread();

    /*Set thread object's internal exit code value
    @param Current object exit code value*/
    void setExitCode(int exitcode);

    /*Sets a preferred processor for a thread, the system schedules threads on their preferred processors whenever possible. Sets the last error flag
    @param The number of the preferred processor for the thread
    @return The previous preferred processor*/
    int setThreadIdealProcessor(int processor);

    /*Sets the priority value for the specified thread. Sets the last error flag
    @param The priority value for the thread*/
    void setThreadPriority(ThreadPriority priority);

    /*Disables or enables the ability of the system to temporarily boost the priority of a thread. Sets the last error flag
    @param True to disable dynamic boosting*/
    void setThreadPriorityBoost(bool disable);

    /*Suspends the specified thread. Sets the last error flag
    @return The thread's previous suspend count*/
    int suspendThread();

    /*Terminates a thread with specified exit code. Does not provide apprppriate cleanup. Sets the last error flag
    @param The exit code for the thread*/
    void terminateThread(int exitcode);

    /*Try enter the thread object's data synchronization spinlock. If succeeded, the thread takes the ownership
    @param The spinlock bit number, must be from 0 to 29
    @return True if the spinlock bit was unlocked, false otherwise*/
    bool tryLock(int bit);

    /*Waits until the specified object is in the signaled state. Sets the last error flag*/
    void waitForSingleObject();

#ifdef GLPP_BUILD_LIB
    static DWORD _thread(LPVOID param);
    static int _main(int argc, char** argv)
    {
        m_sArgc = argc; m_sArgv = argv;
        return _thread(getMainThread());
    }
#endif // #ifdef GLPP_BUILD_LIB
}; // class Thread

inline _Ret_notnull_ Thread* getMainThread()
{
    return Thread::getMainThread();
}

/*GLFW windowed application thread object class derived from <Thread>*/
class ThreadWnd : public Thread
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
    ThreadWnd()
    {
        m_pWindow = nullptr;
    }

    /*Check if the thread's window is associated with current context
    @return True if current context exist, false otherwise*/
    bool isContextWindow()
    {
        return m_pWindow != nullptr;
    }

    /*Gets the current context's window object associated with specified thread
    @return The current context's window object*/
    _Ret_notnull_ Window* getContextWindow();
}; // class WindowThread : public Thread

#ifndef _DEBUG
inline HANDLE Thread::_handle()
{
    return m_hThread;
}

inline void Thread::enterLock(int bit)
{
    _lockBit(bit);
}

inline void Thread::exitThread(int exitcode)
{
    ExitThread(exitcode);
}

inline _Ret_notnull_ const char* Thread::getArgValue(int index)
{
    return m_sArgv[index];
}

inline _Ret_notnull_ Thread* Thread::getMainThread()
{
    return Thread::m_sMainThread;
}

inline int Thread::getThreadId()
{
    return m_dwThreadId;
}

inline void Thread::leaveLock(int bit)
{
    _unlockBit(bit);
}

inline bool Thread::tryLock(int bit)
{
    return !_interlockedbittestandset(&m_nSpinlock, bit);
}

inline _Ret_notnull_ Window* ThreadWnd::getContextWindow()
{
    return m_pWindow;
}
#endif // #ifndef _DEBUG
} // namespace gl
