#pragma once
#include <yaglpp/glfw3pp.h>
#define YAGLPP_INIT_SIZE 32
namespace glfw {
DWORD WINAPI _threadProc(LPVOID lpParam);
//extern int main(int argc, char** argv);

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
    friend DWORD WINAPI _threadProc(LPVOID lpParam);
    friend class Window;
    // Thread object static data structure
    static struct _SDATA {
        int iArgc; // Cmd-line argument count
        char** pArgv; // Cmd-line argument array
        int iEventSize; // Event array size
        int iEventCount; // Event count
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
    } _s;

    // Thread object member data structure
    struct _MDATA {
        int iRef; // Sync reference
        int iSize; // Queue buffer size
        int iCount; // Queue message count
        int iIndex; // Queue dispatch position
        bool bAutoDetele; // Delete window flag
        bool bBlockMessage; // Block message flag
        DWORD nExitcode; // The thread exit code
        DWORD nThreadId; // Thread ID
        HANDLE hThread; // Thread handle
        Message* pQueue; // Queue buffer
        Window* pWindow; // Current window

#ifdef _DEBUG
        int _iDispatch; // Dispatch flag
#endif // #ifdef _DEBUG
    } _m;

    HANDLE _handle() const;
    bool _message(const Message* msg);
    static Thread** _tlsThread() {
        thread_local Thread* tls = nullptr; return &tls;
    }

#ifdef _DEBUG
    bool _dispatch(); // Dispatch flag
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
    @param [in] Points to the message structure containing the message data*/
    virtual void onMessage(const Message* msg) {}

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

    /*Gets the thread object block message flag of the specified thread. Used as a getter of <blockMessage> property
    @param True if thread messages are blocked, false otherwise*/
    bool getBlockMessage() const
    {
        return _m.bBlockMessage;
    }

    /*Returns the window object currently associated with specified thread. Used as a setter of <context> property
    @return The associated window object*/
    _Ret_notnull_ Window* getContext() const;

    /*Retreives the pointer to the currently calling thread object
    @return Pointer to current thread object*/
    static _Ret_notnull_ Thread* getCurrentThread()
    {
        return *_tlsThread();
    }

    /*Gets the current thread's exit code value. Used as a getter of <exitcode> property
    @return The current thread's exit code value*/
    DWORD getExitcode() const
    {
        return _m.nExitcode;
    }
    
    /*Gets the wait events timeout interval value used by <waitEventsTimeout> function. Used as a getter of <eventsTimeout> property
    @return The wait events timeout interval value*/
    static double getEventsTimeout()
    {
        return _s.dEventsTimeout;
    }

    /*Retrieves the termination status of the specified thread. Applicable only for the secondary thread, after it exits
    @return The thread termination status*/
    DWORD getExitCodeThread();

    /*Retreives the pointer to the main thread object
    @return Pointer to main thread object*/
    static _Ret_notnull_ Thread* getMainThread()
    {
        return _s.pMainThread;
    }

    /*Retrieves the id of currently running thread. Used as a getter of <threadId> property
    @return Running thread's id*/
    DWORD getThreadId() const;

    /*Retrieves the priority value for the specified thread. Used as a getter of <threadPriority> property
    @return Thread's priority level*/
    ThreadPriority getThreadPriority();

    /*Retrieves the priority boost control state of the specified thread. Used as a getter of <threadPriorityBoost> property
    @return True if dynamic boosting is disabled, false otherwise*/
    bool getThreadPriorityBoost();

    /*Checks if the window context has been made current on the specified thread object. Used as a getter of <contextCurrent> property
    @return True if the thread object has the window context*/
    bool isContextCurrent() const;

    /*Checks if the thread object is currently calling thread. Used as a getter of <currentThread> property
    @return True if current thread, false otherwise*/
    bool isCurrentThread() const
    {
        return *_tlsThread() == this;
    }

    /*Checks if the thread object is main thread. Used as a getter of <mainThread> property
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

    /*Checks if the thread did not exit. Used as a getter of <stillAlive> property
    @return True if thread is still alive, false otherwise*/
    bool isStillAlive()
    {
        return getExitCodeThread() == STILL_ACTIVE;
    }

    /*Checks if valid thread object. Used as a getter of <thread> property
    @return True if valid thread object, false otherwise*/
    bool isThread() const
    {
        return _m.hThread != NULL;
    }

    /*Waits for the thread until its handle is in the signaled state*/
    void joinThread();

    /*Adds the custom message to specified thread object's message queue. The method should not be called from the current thread
    @param Message id number
    @param The message specific x value
    @param The message specific y value
    @param The message specific z value
    @param The message specific w value
    @return True if message was added to message queue, false otherwise*/
    bool postMessage(int msgid, Param x, Param y, Param z, Param w);

    /*Decrements a thread's suspend count. When the suspend count is decremented to zero, the execution of the thread is resumed
    @return The thread's previous suspend count*/
    int resumeThread();

    /*Associates the window object with specified thread. Could be called only once at thread initialization, and if called, the auto delete flag is set. Used as a setter of <context> property
    @param The window object being associated*/
    void setContext(_In_ Window* window);

    /*Sets the events timeout interval value used by <waitEventsTimeout> function in rendering loop. Could be called only once at application initialization. Used as a setter of <eventsTimeout> property
    @param The events timeout interval value, must be between 0.0 and 2.0*/
    static void setEventsTimeout(double timeout);

    /*Sets the thread's exit code to a non-zero value, which remains unchanged at the later calls. Used as a setter of <exitcode> property
    @return The current thread's exit code value*/
    void setExitcode(DWORD code)
    {
        if (_m.nExitcode == 0) _m.nExitcode = code;
    }

    /*Sets the block message flag. When set, the message can no longer be added to the queue. Should be called only from the host thread. Used as a setter of <blockMessage> property
    @param The block message flag, default false*/
    void setBlockMessage(bool block);

    /*Sets a preferred processor for a thread, the system schedules threads on their preferred processors whenever possible
    @param The number of the preferred processor for the thread
    @return The previous preferred processor*/
    int setThreadIdealProcessor(int processor);

    /*Sets the priority value for the specified thread. Used as a setter of <threadPriority> property
    @param The priority value for the thread*/
    void setThreadPriority(ThreadPriority priority);

    /*Disables or enables the ability of the system to temporarily boost the priority of a thread. Used as a setter of <threadPriorityBoost> property
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
    /*Read-writ property for block message flag of the specified thread*/
    __declspec(property(get = getBlockMessage, put = setBlockMessage)) bool blockMessage;

    /*Read-write property for window object currently associated with specified thread. Could be set only once*/
    __declspec(property(get = getContext, put = setContext)) Window* context;

    /*Read-write property to check if the window context has been made current on the specified thread*/
    __declspec(property(get = isContextCurrent)) bool contextCurrent;

    /*Read-write property to check if the thread object is currently calling thread*/
    __declspec(property(get = isCurrentThread)) bool currentThread;

    /*Read-write property for wait events timeout interval value. Could be set only once*/
    __declspec(property(get = getEventsTimeout, put = setEventsTimeout)) double eventsTimeout;

    /*Read-write property for specified thread's exit code value. Could be set only once*/
    __declspec(property(get = getExitcode, put = setExitcode)) DWORD exitcode;

    /*Read-write property to check if the thread object is main thread*/
    __declspec(property(get = isMainThread)) bool mainThread;

    /*Read-write property to check if the thread did not exit*/
    __declspec(property(get = isStillAlive)) bool stillAlive;

    /*Read-write property to check if valid thread object*/
    __declspec(property(get = isThread)) bool thread;

    /*Read-write property for id of currently running thread*/
    __declspec(property(get = getThreadId)) DWORD threadId;

    /*Read-write property for priority value of the specified thread*/
    __declspec(property(get = getThreadPriority, put = setThreadPriority)) ThreadPriority threadPriority;

    /*Read-write property for priority boost flag of the specified thread*/
    __declspec(property(get = getThreadPriorityBoost, put = setThreadPriorityBoost)) bool threadPriorityBoost;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
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
} // namespace glfw

#include <yaglpp/glfw/window.h>
#include <yaglpp/glfw/joystick.h>
#if defined (YAGLPP_IMPLEMENTATION) && !defined (YAGLPP_NO_AFX_LAYOUT)
#pragma message("YAGL++: Compiling with AFX-alike layout support...")
int main(int argc, char** argv)
{
    glfw::_threadProc(glfw::Thread::getMainThread());
}
#endif // #if defined (YAGLPP_IMPLEMENTATION) && !defined (YAGLPP_NO_AFX_LAYOUT)

namespace glfw {
#ifdef YAGLPP_DEBUG_IMPLEMENTATION
bool Thread::_dispatch()
{
    if ((_m.bBlockMessage == false) && (_m.iCount > 0))
    {
        return _m._iDispatch++ < YAGLPP_INIT_SIZE;
    }
    else return true;
}

void _errorCallback(int code, const char* description)
{
    std::cout << "GLFW ERROR OCCURED WITH THE CODE <" << code << ">: " << description << std::endl;
    YAGLPP_ASSERT(false); // GLFW LIBRARY ERROR
}

HANDLE Thread::_handle() const
{
    YAGLPP_ASSERT(_m.hThread != NULL); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return _m.hThread;
}

void Thread::closeHandle()
{
    BOOL bResult = CloseHandle(_handle());
    YAGLPP_ASSERT(bResult != 0); // FAILED TO CLOSE THREAD HANDLE
    _m.hThread = NULL;
}

void Thread::exitThread(DWORD exitcode)
{
    YAGLPP_ASSERT(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
    YAGLPP_ASSERT(_m.pWindow == nullptr); // SHOULD NOT BE USED WITH A WINDOWED THREAD
    ExitThread(exitcode);
}

_Ret_notnull_ const char* Thread::getArgValue(int index)
{
    YAGLPP_ASSERT((UINT)index < (UINT)_s.iArgc); // INVALID COMMAND LINE ARGUMENT INDEX
    return _s.pArgv[index];
}

_Ret_notnull_ Window* Thread::getContext() const
{
    YAGLPP_ASSERT(_m.pWindow != nullptr); // THREAD OBJECT HAS NO ASSOCIATED WINDOW
    return _m.pWindow;
}

DWORD Thread::getExitCodeThread()
{
    DWORD nExitCode;
    YAGLPP_ASSERT(!isMainThread()); // MAIN THREAD IS NOT APPLICABLE
    BOOL bResult = GetExitCodeThread(_handle(), &nExitCode);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO GET THREAD EXIT CODE
    return nExitCode;
}

DWORD Thread::getThreadId() const
{
    YAGLPP_ASSERT(isThread()); // GLFW THREAD OBJECT HAS NO VALID THREAD
    return _m.nThreadId;
}

ThreadPriority Thread::getThreadPriority()
{
    int iPriority = GetThreadPriority(_handle());
    YAGLPP_ASSERT(iPriority != THREAD_PRIORITY_ERROR_RETURN); // FAILED TO GET THREAD PRIORITY
    return (ThreadPriority)iPriority;
}

bool Thread::getThreadPriorityBoost()
{
    BOOL bDisable, bResult = GetThreadPriorityBoost(_handle(), &bDisable);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO GET THREAD PRIORITY BOOST
    return bDisable;
}

void Thread::joinThread()
{
    DWORD dwResult = WaitForSingleObject(_handle(), INFINITE);
    YAGLPP_ASSERT(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR SINGLE OBJECT
}

bool Thread::postMessage(int msgid, Param x, Param y, Param z, Param w)
{
    YAGLPP_ASSERT(msgid >= 0); // MESSAGE ID MUST NOT BE NEGATIVE
    Message msg = { msgid, x, y, z, w, *_tlsThread() };
    return _message(&msg);
}

int Thread::resumeThread()
{
    DWORD nCount = ResumeThread(_handle());
    YAGLPP_ASSERT(nCount != (DWORD)-1); // FAILED TO RESUME THREAD
    return nCount;
}

void Thread::setContext(_In_ Window* window)
{
    YAGLPP_ASSERT(_m.pWindow == nullptr); // WINDOW OBJECT HAS BEEN ALREADY SET
    _m.pWindow = window;
    _m.bAutoDetele = true;
}

int Thread::setThreadIdealProcessor(int processor)
{
    YAGLPP_ASSERT((DWORD)processor < MAXIMUM_PROCESSORS); // INVALID INDEX OF IDEAL PROCESSOR FOR A THREAD OBJECT
    DWORD dwResult = SetThreadIdealProcessor(_handle(), processor);
    YAGLPP_ASSERT(dwResult != (DWORD)-1); // FAILED TO SET THREAD IDEAL PROCESSOR
    return dwResult;
}

void Thread::setThreadPriority(ThreadPriority priority)
{
    BOOL bResult = SetThreadPriority(_handle(), (int)priority);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO SET THREAD PRIORITY
}

void Thread::setThreadPriorityBoost(bool disable)
{
    BOOL bResult = SetThreadPriorityBoost(_handle(), disable);
    YAGLPP_ASSERT(bResult != 0); // FAILED TO SET THREAD PRIORITY BOOST
}

void Thread::setEventsTimeout(double timeout)
{
    YAGLPP_ASSERT(_s.dEventsTimeout == 0.0); // TIMEOUT VALUE HAS BEEN ALREADY SET
    YAGLPP_ASSERT((timeout >= 0.0) && (timeout <= 2.0)); // TIMEOUT VALUE IS OUT OF RANGE
    _s.dEventsTimeout = timeout;
}

int Thread::suspendThread()
{
    DWORD nCount = SuspendThread(_handle());
    YAGLPP_ASSERT(nCount != (DWORD)-1); // FAILED TO SUSPEND THREAD
    return nCount;
}

void Thread::terminateThread(int exitcode)
{
#pragma warning(push)
#pragma warning(disable : 6258)
    BOOL bResult = TerminateThread(_handle(), exitcode);
#pragma warning(pop)
    YAGLPP_ASSERT(bResult != 0); // FAILED TO TERMINATE THREAD
}

void Thread::waitEventsTimeout()
{
    YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
    glfwWaitEventsTimeout(_s.dEventsTimeout);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_IMPLEMENTATION
Thread::_SDATA Thread::_s;
DWORD WINAPI _threadProc(LPVOID lpParam)
{
    Thread* pThread = (Thread*)lpParam;
    *Thread::_tlsThread() = pThread;
    return pThread->onRun();
}

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
    YAGLPP_ASSERT(bInitialized); // FAILED TO INITIALIZE GLFW

#ifdef _DEBUG
    glfwSetErrorCallback(&_errorCallback);
#endif // #ifdef _DEBUG

    iArgc = 0; // Thread sync data
    iEventSize = YAGLPP_INIT_SIZE;
    iEventCount = 1; // [0] reserved for sync event
    dEventsTimeout = 0.0;
    pMainThread = thread;
    pLocks = (LONG*)_callocate((YAGLPP_INIT_SIZE >> 5) * sizeof(LONG), nullptr);
    pEvents = (HANDLE*)_callocate(YAGLPP_INIT_SIZE * sizeof(HANDLE), nullptr);
    pEvents[0] = CreateEventA(NULL, TRUE, TRUE, NULL); // sync event
    YAGLPP_ASSERT(pEvents[0] != NULL); // FAILED TO CREATE EVENT OBJECT

    char* pCmdA = GetCommandLineA(); // Command line arguments
    int iLen = (int)strlen(pCmdA) + 1;
    WCHAR* pCmdW = (WCHAR*)_allocate(iLen * sizeof(WCHAR), nullptr);
    int iResult = MultiByteToWideChar(CP_ACP, 0, pCmdA, iLen, pCmdW, iLen);
    YAGLPP_ASSERT(iResult != 0); // FAILED TO CONVERT CHAR TO WIDE
    WCHAR** pArrW = CommandLineToArgvW(pCmdW, &iArgc);
    YAGLPP_ASSERT(pArrW != NULL); // FAILED TO PARSE COMMAND LINE
    _deallocate(pCmdW, nullptr);
    pArgv = (char**)_allocate(iArgc * sizeof(char*), nullptr);
    for (int i = 0; i < iArgc; i++)
    {
        iLen = (int)wcslen(pArrW[i]) + 1;
        pArgv[i] = (char*)_allocate(sizeof(char) * iLen, nullptr);
        iResult = WideCharToMultiByte(CP_ACP, 0, pArrW[i], iLen, pArgv[i], iLen, NULL, NULL);
        YAGLPP_ASSERT(iResult != 0); // FAILED TO CONVERT WIDE TO CHAR
    }
    LocalFree(pArrW);
    return bInitialized;
}

void Thread::_SDATA::syncEnter(int ref)
{
    YAGLPP_ASSERT((UINT)ref < (UINT)iEventCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    while (_interlockedbittestandset(&pLocks[lIndex], lBit))
    {
        DWORD dwResult = WaitForSingleObject(pEvents[ref], INFINITE);
        YAGLPP_ASSERT(dwResult != WAIT_FAILED); // FAILED TO WAIT FOR EVENT OBJECT
    }
    BOOL bResult = ResetEvent(pEvents[ref]);
    YAGLPP_ASSERT(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
}

void Thread::_SDATA::syncLeave(int ref)
{
    YAGLPP_ASSERT((UINT)ref < (UINT)iEventCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    BOOLEAN bBit = _interlockedbittestandreset(&pLocks[lIndex], lBit);
    YAGLPP_ASSERT(bBit != FALSE); // SYNC BIT WAS ALREADY UNSET
    BOOL bResult = SetEvent(pEvents[ref]);
    YAGLPP_ASSERT(bResult != FALSE); // FAILED TO SET EVENT OBJECT
}

int Thread::_SDATA::syncRef()
{
    _s.syncEnter(0);
    int iEvent = iEventCount++;
    if (iEvent == iEventSize)
    {
        int iNewLock = iEventSize >> 4;
        int iOldLock = iEventSize >> 5;
        int iOldSize = iEventSize;
        iEventSize <<= 1; // x2
        volatile LONG* pOldLocks = pLocks;
        volatile HANDLE* pOldEvents = pEvents;
        pLocks = (LONG*)_callocate(iNewLock * sizeof(LONG), nullptr);
        pEvents = (HANDLE*)_callocate(iEventSize * sizeof(HANDLE), nullptr);
        memcpy((void*)pLocks, (const void*)pOldLocks, iOldLock * sizeof(LONG));
        memcpy((void*)pEvents, (const void*)pOldEvents, iOldSize * sizeof(HANDLE));
        _deallocate((void*)pOldLocks, nullptr);
        _deallocate((void*)pOldEvents, nullptr);
    }
    pEvents[iEvent] = CreateEventA(NULL, TRUE, TRUE, NULL);
    YAGLPP_ASSERT(pEvents[iEvent] != NULL); // FAILED TO CREATE EVENT OBJECT
    _s.syncLeave(0);
    return iEvent;
}

bool Thread::_SDATA::syncTry(int ref)
{
    YAGLPP_ASSERT((UINT)ref < (UINT)iEventCount); // INVALID SYNC REFERENCE NUMBER
    LONG lIndex = ref >> 5, lBit = ref & 0x1F;
    if (_interlockedbittestandset(&pLocks[lIndex], lBit)) return false;
    BOOL bResult = ResetEvent(pEvents[ref]);
    YAGLPP_ASSERT(bResult != FALSE); // FAILED TO RESET EVENT OBJECT
    return true;
}

void Thread::_SDATA::terminate()
{
    for (int i = 0; i < iEventCount; i++) // Cleanup sync
    {
        CloseHandle(pEvents[i]);
    }
    _deallocate((void*)pLocks, nullptr);
    _deallocate((void*)pEvents, nullptr);
    for (int i = 0; i < iArgc; i++) // Cleanup command line
    {
        _deallocate(pArgv[i], nullptr);
    }
    _deallocate(pArgv, nullptr);
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
        _m.pQueue = (Message*)_reallocate(_m.pQueue, _m.iSize * sizeof(Message), nullptr);
        YAGLPP_ASSERT(_m.pQueue); // FAILED TO REALLOCATE MEMORY
    }
    memcpy(&_m.pQueue[_m.iCount], msg, sizeof(Message));

    _m.iCount++; // post-increment
    _s.syncLeave(_m.iRef);
    if (isMainThread() && _s.dEventsTimeout > 0.0)
    {
        glfwPostEmptyEvent(); // Wake up main thread, if idled
    }
    return true;
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
    _m.pQueue = (Message*)_allocate(YAGLPP_INIT_SIZE * sizeof(Message), nullptr);
    _m.iRef = syncRef();
}

Thread::~Thread()
{
    if (isThread())
    {
        closeHandle();
    }
    _deallocate(_m.pQueue, nullptr);
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
    YAGLPP_ASSERT(!isThread()); // GLFW THREAD OBJECT HAS VALID THREAD
    _m.hThread = CreateThread(NULL, 0, &_threadProc, this, (suspended) ? CREATE_SUSPENDED : 0, &_m.nThreadId);
    YAGLPP_ASSERT(isThread()); // FAILED TO CREATE THREAD
}

bool Thread::dispatchMessage(_Out_ Message* msg)
{
    YAGLPP_ASSERT(isCurrentThread()); // DISPATCH IS ALLOWED ONLY BY THE HOST THREAD
    _s.syncEnter(_m.iRef);
    if (_m.iIndex < _m.iCount)
    {
        memcpy(msg, &_m.pQueue[_m.iIndex], sizeof(Message));

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
    YAGLPP_ASSERT(isContextCurrent()); // THE CONTEXT HAS NOT BEEN MADE CURRENT
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
    YAGLPP_ASSERT(isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
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
        YAGLPP_ASSERT(nCount != (DWORD)-1); // FAILED TO RESUME THREAD
    } while (nCount > 1);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline HANDLE Thread::_handle() const
{
    return _m.hThread;
}

inline void Thread::closeHandle()
{
    CloseHandle(_m.hThread); _m.hThread = NULL;
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

inline bool Thread::postMessage(int msgid, Param x, Param y, Param z, Param w)
{
    Message msg = { msgid, x, y, z, w, *_tlsThread() }; return _message(&msg);
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
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
