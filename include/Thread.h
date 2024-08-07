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

/*GLFW Windows-based thread object root class*/
class Thread
{
private:
    friend class Window;
    // Thread object static data structure
    static struct _SDATA {
        int iArgc; // Cmd-line argument count
        int iESize; // Event array size
        int iECount; // Event count
        char** pArgv; // Cmd-line argument array
        Thread* pMainThread; // Application main thread
        double dEventsTimeout; // Render loop idle timeout
        volatile LONG* pLocks; // Spinlock array
        volatile HANDLE* pEvents; // Event array
        bool initialize(Thread* thread);
        void syncEnter(int ref);
        void syncLeave(int ref);
        int syncRef();
        bool syncTry(int ref);
        void terminate();

#ifdef _DEBUG
        static void _errorCallback(int code, const char* description);
#endif // #ifdef _DEBUG
    } _s;

    // Thread object member data structure
    struct _MDATA {
        int iRef; // Sync reference
        int iSize; // Queue buffer size
        int iCount; // Queue message count
        int iIndex; // Queue dispatch position
        bool bAutoDetele; // Delete window flag
        DWORD nExitcode; // The thread exit code
        DWORD nThreadId; // Thread ID
        HANDLE hThread; // Thread handle
        Message* pQueue; // Queue buffer
        Window* pWindow; // Current window

#ifdef _DEBUG
        bool _bDispatch; // Dispatch flag
#endif // #ifdef _DEBUG
    } _m;

    HANDLE _handle() const;
    void _message(int msgid, Param x, Param y, Param z, Param w, LPVOID sender);
    static Thread** _tlsThread() { thread_local Thread* tls = nullptr; return &tls; }

#ifdef _DEBUG
    bool _dispatch();
#endif // #ifdef _DEBUG

protected:
    /*Thread exit event handler called at the thread termination. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately*/
    virtual void onExit() {}

    /*Thread idle event handler called at every iteration of the rendering loop after message processing, if events timeout is greater than zero. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately*/
    virtual void onIdle() {}

    /*Thread init event handler called at the thread initialization. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately*/
    virtual void onInit() {}

    /*Thread idle event handler called at the beginning at every iteration of the rendering loop. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately
    @param The time delta value since last iteration of the rendering loop*/
    virtual void onInput(double delta) {}

    /*Thread message event handler called at every iteration of the rendering loop after rendering stage, for every message added to the message queue. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately
    @param Message id number
    @param Additional message-specific data
    @param Additional message-specific data
    @param Additional message-specific data
    @param Additional message-specific data*/
    virtual void onMessage(int msgid, Param x, Param y, Param z, Param w, Thread* sender) {}

    /*Thread render event handler called at every iteration of the rendering loop after input processing. If after the function flow the <exitcode> property is set to non-zero, the thread exits immediately*/
    virtual void onRender() {}

    /*The thread working routine procedure. Overriding this function transforms the class object into the working thread, while taking all other features out of scope
    @return The thread exit code value*/
    virtual DWORD onRun();

public:
    /*(1) Constructs the empty thread object*/
    Thread();

    /*(2) Constructs the empty thread associated with <createThread>*/
    Thread(bool suspended) : Thread()
    {
        createThread(suspended);
    }

    /*Cleans up the valid thread object*/
    ~Thread();

    /*Close the handle of a specified thread object*/
    void closeHandle();

    /*Creates a thread for a specified Thread object to execute within the virtual address space of the calling process
    @param True to start the thread in suspended state, default false*/
    void createThread(bool suspended = false);

    /*Dispatches the first inter-thread message in the message queue of the calling thread. If the message is present, copies its data into <Message> structure, and removes it from the queue
    @param [out] Points to the message structure receiving the message data
    @return True if the message is dispatched, false otherwise*/
    bool dispatchMessage(_Out_ Message* msg);

    /*Unconditionally ends the current thread of the thread object. Must be called by the current thread, and should not be applied for a windowed thread
    @param The exit code for the thread*/
    void exitThread(DWORD exitcode);

    /*Gets the number of application command line arguments
    @return The number of command line arguments. Must be at least 1*/
    static int getArgCount()
    {
        return _s.iArgc;
    }

    /*Gets rhe specified command line argument
    @param The index of command line argument
    @return The null-terminating string of specified command line argument*/
    static _Ret_notnull_ const char* getArgValue(int index);

    /*Returns the window object currently associated with specified thread. Used as the setter of <context> property
    @return The associated window object*/
    _Ret_notnull_ Window* getContext() const;

    /*Retreives the pointer to the currently calling thread object
    @return Pointer to current thread object*/
    static _Ret_notnull_ Thread* getCurrentThread()
    {
        return *_tlsThread();
    }

    /*Gets the current thread's exit code value. Used as the getter of <exitcode> property
    @return The current thread's exit code value*/
    DWORD getExitcode() const
    {
        return _m.nExitcode;
    }
    
    /*Gets the wait events timeout interval value used by <waitEventsTimeout> function. Used as the getter of <eventsTimeout> property
    @return The wait events timeout interval value*/
    static double getEventsTimeout()
    {
        return _s.dEventsTimeout;
    }

    /*Retrieves the termination status of the specified thread. Applicable only for the secondary thread
    @return The thread termination status*/
    DWORD getExitCodeThread();

    /*Retreives the pointer to the main thread object
    @return Pointer to main thread object*/
    static _Ret_notnull_ Thread* getMainThread()
    {
        return _s.pMainThread;
    }

    /*Retrieves the id of currently running thread
    @return Running thread's id*/
    DWORD getThreadId() const;

    /*Retrieves the priority value for the specified thread. Used as the getter of <threadPriority> property
    @return Thread's priority level*/
    ThreadPriority getThreadPriority();

    /*Retrieves the priority boost control state of the specified thread. Used as the getter of <threadPriorityBoost> property
    @return True if dynamic boosting is disabled, false otherwise*/
    bool getThreadPriorityBoost();

    /*Checks if the window context has been made current on the specified thread
    @return True if the thread object has the window context*/
    bool hasContext() const;

    /*Checks if the thread object is currently calling thread
    @return True if current thread, false otherwise*/
    bool isCurrentThread() const
    {
        return *_tlsThread() == this;
    }

    /*Checks if the thread object is main thread
    @return True if main thread, false otherwise*/
    bool isMainThread() const
    {
        return _s.pMainThread == this;
    }

    /*Checks if the calling thread is the main application thread
    @return True if main thread is current, false otherwise*/
    static bool isMainThreadCurrent()
    {
        return *_tlsThread() == _s.pMainThread;
    }

    /*Checks if the thread did not exit
    @return True if thread is still alive, false otherwise*/
    bool isStillAlive()
    {
        return getExitCodeThread() == STILL_ACTIVE;
    }

    /*Checks if valid thread object
    @return True if valid thread object, false otherwise*/
    bool isThread() const
    {
        return _m.hThread != NULL;
    }

    /*Waits for the thread until its handle is in the signaled state*/
    void joinThread();

    /*Adds the custom message to specified thread object's message queue. The method should not be called from the current thread
    @param Message id number
    @param Additional message-specific data
    @param Additional message-specific data
    @param Additional message-specific data
    @param Additional message-specific data*/
    void postMessage(int msgid, Param x, Param y, Param z, Param w);

    /*Decrements a thread's suspend count. When the suspend count is decremented to zero, the execution of the thread is resumed
    @return The thread's previous suspend count*/
    int resumeThread();

    /*Associates the window object with specified thread. Could be called only once at thread initialization, and if called, the auto delete flag is set. Used as the setter of <context> property
    @param The window object being associated*/
    void setContext(_In_ Window* window);

    /*Sets the events timeout interval value used by <waitEventsTimeout> function in rendering loop. Could be called only once at application initialization. Used as the setter of <eventsTimeout> property
    @param The events timeout interval value, must be between 0.0 and 2.0*/
    static void setEventsTimeout(double timeout);

    /*Sets the thread's exit code to a non-zero value, which remains unchanged at the later calls. Used as the setter of <exitcode> property
    @return The current thread's exit code value*/
    void setExitcode(DWORD exitcode)
    {
        if (exitcode == 0) _m.nExitcode = exitcode;
    }

    /*Sets a preferred processor for a thread, the system schedules threads on their preferred processors whenever possible
    @param The number of the preferred processor for the thread
    @return The previous preferred processor*/
    int setThreadIdealProcessor(int processor);

    /*Sets the priority value for the specified thread. Used as the setter of <threadPriority> property
    @param The priority value for the thread*/
    void setThreadPriority(ThreadPriority priority);

    /*Disables or enables the ability of the system to temporarily boost the priority of a thread. Used as the setter of <threadPriorityBoost> property
    @param True to disable dynamic boosting*/
    void setThreadPriorityBoost(bool disable);

    /*Suspends the specified thread
    @return The thread's previous suspend count*/
    int suspendThread();

    /*Enters thread's synchronization section
    @param The thread's synchronization section reference number returned by <syncRef>*/
    static void syncEnter(int ref)
    {
        _s.syncEnter(ref);
    }

    /*Leaves thread's synchronization section
    @param The thread's synchronization section reference number returned by <syncRef>*/
    static void syncLeave(int ref)
    {
        _s.syncLeave(ref);
    }

    /*Initializes the new synchronization cell, retreiving its reference number
    @param The synchronization reference number*/
    static int syncRef()
    {
        return _s.syncRef();
    }

    /*Tries entering thread's synchronization section. If succeeded, the thread takes the ownership
    @param The thread's synchronization section reference number returned by <syncRef>
    @return True if the thread takes the ownership, false otherwise*/
    static bool syncTry(int ref)
    {
        return _s.syncTry(ref);
    }

    /*Terminates a thread with specified exit code. Emergency thread termination function, does not provide apprppriate cleanup
    @param The exit code for the thread*/
    void terminateThread(int exitcode);

    /*This function puts the calling thread to sleep until at least one event is available in the event queue, or until the timeout defined by <setTimeout> is reached*/
    static void waitEventsTimeout();

    /*Resumes the execution of the thread regardless of the thread suspension count*/
    void wakeThread();

#ifdef YAGLPP_CLASS_PROPERTIES
    /*Read-write property for window object currently associated with specified thread. Could be set only once*/
    __declspec(property(get = getContext, put = setContext)) Window* context;

    /*Read-write property for wait events timeout interval value. Could be set only once*/
    __declspec(property(get = getEventsTimeout, put = setEventsTimeout)) double eventsTimeout;

    /*Read-write property for specified thread's exit code value. Could be set only once*/
    __declspec(property(get = getExitcode, put = setExitcode)) DWORD exitcode;

    /*Read-write property for priority value of the specified thread*/
    __declspec(property(get = getThreadPriority, put = setThreadPriority)) ThreadPriority threadPriority;

    /*Read-write property for priority boost flag of the specified thread*/
    __declspec(property(get = getThreadPriorityBoost, put = setThreadPriorityBoost)) bool threadPriorityBoost;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_BUILD_LIB
    static DWORD WINAPI _thread(LPVOID lpParam);
#endif // #ifdef YAGLPP_BUILD_LIB
}; // class Thread

/*Dispatches the first inter-thread message in the message queue of the calling thread. If the message is present, copies its data into <Message> structure, and removes it from the queue
@param [out] Points to the message structure receiving the message data
@return True if the message is dispatched, false otherwise*/
inline bool dispatchMessage(_Out_ Message* message)
{
    return Thread::getCurrentThread()->dispatchMessage(message);
}

/*Retreives the pointer to the current thread object
@return Pointer to current thread object*/
inline _Ret_notnull_ Thread* getCurrentThread()
{
    return Thread::getCurrentThread();
}

/*Retreives the pointer to the main thread object
@return Pointer to main thread object*/
inline _Ret_notnull_ Thread* getMainThread()
{
    return Thread::getMainThread();
}

/*Checks if the calling thread is the main application thread
@return True if main thread is current, false otherwise*/
inline bool isMainThreadCurrent()
{
    return Thread::isMainThreadCurrent();
}

/*Enters thread's synchronization section
@param The thread's synchronization section reference number returned by <syncRef>*/
inline void syncEnter(int ref)
{
    Thread::syncEnter(ref);
}

/*Leaves thread's synchronization section
@param The thread's synchronization section reference number returned by <syncRef>*/
inline void syncLeave(int ref)
{
    Thread::syncLeave(ref);
}

/*Initializes the new synchronization cell, retreiving its reference number
@param The thread's synchronization section reference number*/
inline int syncRef()
{
    return Thread::syncRef();
}

/*Tries entering thread's synchronization section. If succeeded, the thread takes the ownership
@param The synchronization reference number returned by <syncRef>
@return True if the thread takes the ownership, false otherwise*/
inline bool syncTry(int ref)
{
    return Thread::syncTry(ref);
}

#ifndef _DEBUG
inline HANDLE Thread::_handle() const
{
    return _m.hThread;
}

inline void Thread::closeHandle()
{
    CloseHandle(_m.hThread); _m.hThread = NULL; _m.nThreadId = 0;
}

inline void Thread::exitThread(DWORD exitcode)
{
    ExitThread(exitcode);
}

inline _Ret_notnull_ const char* Thread::getArgValue(int index)
{
    return _s.pArgv[index];
}

inline _Ret_notnull_ Window* Thread::getContext() const
{
    return _m.pWindow;
}

inline DWORD Thread::getExitCodeThread()
{
    DWORD nExitCode; GetExitCodeThread(_handle(), &nExitCode); return nExitCode;
}

inline DWORD Thread::getThreadId() const
{
    return _m.nThreadId;
}

inline ThreadPriority Thread::getThreadPriority()
{
    return (ThreadPriority)GetThreadPriority(_handle());
}

inline bool Thread::getThreadPriorityBoost()
{
    BOOL bDisable; GetThreadPriorityBoost(_handle(), &bDisable); return bDisable;
}

inline void Thread::joinThread()
{
    WaitForSingleObject(_handle(), INFINITE);
}

inline void Thread::postMessage(int msgid, Param x, Param y, Param z, Param w)
{
    _message(msgid, x, y, z, w, *_tlsThread());
}

inline int Thread::resumeThread()
{
    return ResumeThread(_m.hThread);
}

inline void Thread::setContext(_In_ Window* window)
{
    _m.pWindow = window; _m.bAutoDetele = true;
}

inline void Thread::setEventsTimeout(double timeout)
{
    _s.dEventsTimeout = timeout;
}

inline int Thread::setThreadIdealProcessor(int processor)
{
    return SetThreadIdealProcessor(_handle(), processor);
}

inline void Thread::setThreadPriority(ThreadPriority priority)
{
    SetThreadPriority(_handle(), (int)priority);
}

inline void Thread::setThreadPriorityBoost(bool disable)
{
    SetThreadPriorityBoost(_handle(), disable);
}

inline int Thread::suspendThread()
{
    return SuspendThread(_m.hThread);
}

inline void Thread::terminateThread(int exitcode)
{
#pragma warning(push)
#pragma warning(disable : 6258)
    TerminateThread(_handle(), exitcode);
#pragma warning(pop)
}

inline void Thread::waitEventsTimeout()
{
    glfwWaitEventsTimeout(_s.dEventsTimeout);
}
#endif // #ifndef _DEBUG
} // namespace glfw
