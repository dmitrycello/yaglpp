#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_THREAD_H
#define YAGLPP_THREAD_H

#ifndef YAGLPP_NO_AFX_LAYOUT
    int main(int, char**);
#endif

namespace glfw {
/*GLFW implementation-based thread object root class*/
class Thread
{
#ifndef YAGLPP_NO_AFX_LAYOUT
    friend int ::main(int, char**);
#endif

public:
    /*Constructs the empty thread object*/
    Thread(bool autostart = true);

    /*Resets autodelete flag of the dynamically allocated object, forcing manual clean up*/
    void CancelAutodelete()
    {
        m_Autodelete = false;
    }

    /*Separates the thread of execution from the thread object, allowing execution to continue independently. Any allocated resources will be freed once the thread exits*/
    void Detach();

    /*Get and reset the thread-safe alloc flag, used in object's constructor to detect dynamic allocation*/
    static bool GetAlloc();

    /*Gets the number of application command line arguments. Can be used only in afx-alike layout
    @return The number of command line arguments. Always zero in no-afx-alike layout*/
    static int GetArgCount()
    {
        return s_Data.argC;
    }

    /*Gets rhe specified command line argument. Can be used only in afx-alike layout
    @param The index of command line argument
    @return The null-terminating string of specified command line argument*/
    static _Ret_notnull_ const char* GetArgValue(int index);

    /*Gets the thread autodelete flag
    return True if object was allocated dynamically, false otherwise*/
    bool GetAutodelete() const
    {
        return m_Autodelete;
    }

    /*Retreives the pointer to the calling thread object
    @return Pointer to current thread object*/
    static _Ret_notnull_ Thread* GetCurrent()
    {
        return *thread_current();
    }

    /*Gets the wait events timeout interval value used by <WaitEventsTimeout> function. MSVC getter for <eventsTimeout> property
    @return The wait events timeout interval value*/
    static double GetEventsTimeout()
    {
        return s_Data.eventTimeout;
    }

    /*Gets the exit code of current thread. Once being set, the thread state remain unchanged allowing to record only the first value. MSVC getter for <exitcode> property
    @return The thread exit code*/
    int GetExitcode() const
    {
        return m_Exitcode;
    }

    /*Returns a value identifying the thread associated with an object
    return Lightweight, trivially copyable class that serves as a unique identifier of an object*/
    std::thread::id GetId() const
    {
        return m_Thread.get_id();
    }

    /*Retreives the pointer to the main thread object
    @return Pointer to main thread object*/
    static _Ret_notnull_ Thread* GetMain()
    {
        return s_Data.mainThread;
    }

    /*Returns the number of concurrent threads supported by the implementation. The value should be considered only as a hint*/
    static unsigned int HardwareConcurrency()
    {
        return std::thread::hardware_concurrency();
    }

    /*Checks if the thread object represents currently calling (self) thread. MSVC getter for <current> property
    @return True if current thread, false otherwise*/
    bool IsCurrent() const
    {
        return this == *thread_current();
    }

    /*Checks if the thread object represents main thread. MSVC getter for <main> property
    @return True if main thread, false otherwise*/
    bool IsMain() const
    {
        return this == s_Data.mainThread;
    }

    /*Checks if the calling thread is the main application thread
    @return True if main thread is current, false otherwise*/
    static bool IsMainCurrent()
    {
        return s_Data.mainThread == *thread_current();
    }

    /*Checks if the std::thread object identifies an active thread of execution. Always false for main thread object
    @return True if the thread object identifies an active thread of execution, false otherwise*/
    bool IsThread() const
    {
        return m_Thread.joinable();
    }

    /*Blocks the current thread until the thread objects's thread finishes its execution*/
    void Join();

    /*Pops the first inter-thread message out of the message queue of calling thread. If the message is present, copies its data into <Message> structure, and removes it from the queue, otherwise clears the stucture
    @param [out] Points to the message structure receiving the message data
    @return True if the message data was received, false otherwise*/
    static bool PopMessage(_Out_ Message* msg);

    /*Pushes the inter-thread message into the message queue of specified thread object. Must be called by the non-current (not self) thread
    @param [in] Points to the message data structure*/
    void PushMessage(_In_ Message* msg);

    /*Provides a hint to the implementation to relinquish control of the current running thread, and sending it to the end of the running queue, of the same scheduling priority, allowing other threads to run*/
    static void Relinquish()
    {
        std::this_thread::yield();
    }

    /*Set the thread-safe alloc flag, used in object's overloaded operator new to detect dynamic allocation*/
    static void SetAlloc()
    {
        *thread_alloc() = true;
    }

    /*Sets the wait events timeout interval value used by <WaitEventsTimeout> function. Could be called only once from the main thread. Used as a setter of <eventsTimeout> property
    @return The wait events timeout interval value in seconds, must be between 0.0 and 2.0*/
    static void SetEventsTimeout(double timeout);

    /*Sets the exit code of current thread. Once being set, the thread state remain unchanged allowing to record only the first value. Used as a setter of <exitcode> property
    @param The current thread exit code*/
    void SetExitcode(int exitcode);

    /*Checks the calling thread exitcode and the state of its context window
    @param [out] Points to the GLFW window handler variable
    @return True if the thread should exit, false otherwise*/
    static bool ShouldExit(_Out_ GLFWwindow** context);

    /*Blocks the execution of the current thread for at least the specified time duration
    @param Time duration to sleep in seconds*/
    static void Sleep(double sec)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds((int64_t)(sec * 1e9)));
    }

    /*Creates a thread for a specified Thread object to execute within the virtual address space of the calling process. The object should not be the main thread, and must have no running thread*/
    void Start();

    /*Exchanges the underlying handles of two thread objects
    @param The thread to swap with*/
    void Swap(Thread& other)
    {
        m_Thread.swap(other.m_Thread);
    }

    /*Blocks the execution of the calling thread with empty message queue until the new message is received. Should not be used with main thread*/
    static void WaitMessage();

    /*Blocks the execution of the calling thread with empty message queue until the new message is received, or the specified duration elapses. Should not be used with main thread
    @param Time duration to wait in seconds*/
    static void WaitMessageTimeout(double timeout);

    /*GLFW thread object new operator returning allocated object
    @param The size in bytes of allocated object
    @return The pointer to allocated object*/
    static void* operator new(std::size_t count);

    /*Using the object's new operator is not allowed*/
    void* operator new[](std::size_t) = delete;

    /*Using the object's delete operator is not allowed*/
    void operator delete[](void*) = delete;

#ifdef YAGLPP_CLASS_PROPERTIES
    /*Read-only property to check if the thread object is currently calling thread*/
    __declspec(property(get = IsCurrent)) bool current;

    /*Read-write property for thread exit code value. Could be set only once from current thread*/
    __declspec(property(get = GetExitcode, put = SetExitcode)) int exitcode;

    /*Read-only property to check if the thread object is main thread*/
    __declspec(property(get = IsMain)) bool main;

    /*Read-only property to check if valid thread object*/
    __declspec(property(get = IsThread)) bool thread;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
    /*Thread exit event handler called at the thread termination. The value of <exitcode> property is then returned as thread exit code, where as the main thread exit code is the application exit code*/
    virtual void OnExit() {}

    /*Thread idle event handler called at every iteration of the rendering loop after message processing, if events timeout is greater than zero. If after the function flow the <exitcode> property is set to non-zero, the thread message loop exits*/
    virtual void OnIdle() {}

    /*Thread init event handler called at the thread initialization. If after the function flow the <exitcode> property is set to non-zero, the thread message loop exits*/
    virtual void OnInit() {}

    /*Thread idle event handler called at the beginning at every iteration of the rendering loop. If after the function flow the <exitcode> property is set to non-zero, the thread message loop exits
    @param The time delta value since last iteration of the rendering loop*/
    virtual void OnInput(double delta) {}

    /*Thread message event handler called at every iteration of the rendering loop after rendering stage, for every message added to the message queue. If after the function flow the <exitcode> property is set to non-zero, the thread message loop exits
    @param [in] Points to the message structure containing the message data*/
    virtual void OnMessage(const Message* msg) {}

    /*Thread render event handler called at every iteration of the rendering loop after input processing. If after the function flow the <exitcode> property is set to non-zero, the thread message loop exits*/
    virtual void OnRender() {}

    /*The thread working routine procedure. Overriding this function transforms the class object into the working thread, while taking all other features out of the execution flow
    @return The thread exit code value*/
    virtual int OnRun();

private:
    bool m_Autodelete;
    int m_Exitcode;
    std::mutex m_Mutex;
    std::thread m_Thread;
    std::queue<Message> m_Queue;
    std::condition_variable m_Sync;
    static int thread_proc(Thread* param);

    static bool* thread_alloc()
    {
        thread_local bool tls = false; return &tls;
    }

    static Thread** thread_current()
    {
        thread_local Thread* tls = nullptr; return &tls;
    }

    static struct SDATA
    {
        int argC; // Cmd-line argument count
        char** argV; // Cmd-line argument vector
        Thread* mainThread; // Application main thread
        double eventTimeout; // Main loop event eventTimeout
        bool initialize(Thread* main); // Initialize structure
        SDATA();
        ~SDATA();
    } s_Data;
}; // class Thread
} // namespace glfw

#if defined (YAGLPP_IMPLEMENTATION) && !defined (YAGLPP_NO_AFX_LAYOUT)
#ifdef YAGLPP_MSVC
    #pragma message("YAGL++: Compiling with AFX-alike layout support...")
#endif
int main(int argc, char** argv)
{
    // AFX-ALIKE THREAD VARIABLE NOT DEFINED
    YAGLPP_ASSERT(glfw::Thread::s_Data.mainThread);

    glfw::Thread::s_Data.argC = argc;
    glfw::Thread::s_Data.argV = argv;
    return glfw::Thread::thread_proc(glfw::Thread::s_Data.mainThread);
}
#endif // #if defined (YAGLPP_IMPLEMENTATION) && !defined (YAGLPP_NO_AFX_LAYOUT)

namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
Thread::SDATA Thread::s_Data;
Thread::SDATA::SDATA()
{
    std::memset(this, 0, sizeof(Thread::SDATA));
    int iResult = std::atexit(yaglpp_atexit_handler);

    // FAILED TO LOAD ATEXIT HANDLER
    YAGLPP_ASSERT(!iResult);

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
    GLFWallocator allocator = { yaglpp_allocate, yaglpp_reallocate, yaglpp_deallocate, nullptr };
    glfwInitAllocator(&allocator);
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

    iResult = glfwInit();

    // FAILED TO LOAD GLFW
    YAGLPP_ASSERT(iResult);

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
    glfwSetErrorCallback(
        [](int code, const char* description)
        {
            std::cout << "YAGL++ GLFW error " << code << ": " << description << std::endl;

            // YAGLPP GLFW ERROR
            YAGLPP_ASSERT(0);
        }
    );
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_NO_AFX_LAYOUT
    static Thread no_afx_thread;
    *thread_current() = &no_afx_thread;
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT
}

Thread::SDATA::~SDATA()
{
    gl::yaglpp_glad_free();
    glfwTerminate();
}

Thread::Thread(bool autostart)
{
    m_Exitcode = 0;
    m_Autodelete = GetAlloc();
    if (s_Data.initialize(this) && autostart)
    {
        m_Thread = std::thread(Thread::thread_proc, this);
    }
}

int Thread::thread_proc(Thread* param)
{
    *thread_current() = param;
    int iExitcode = param->OnRun();
    if (param->GetAutodelete() && !param->IsThread())
    {
        // clean up main or detached thread
        delete param;
    }
    return iExitcode;
}

bool Thread::GetAlloc()
{
    bool bAlloc = *thread_alloc();
    *thread_alloc() = false;
    return bAlloc;
}

int Thread::OnRun()
{
    Message msg;
    GLFWwindow* pContext;
    bool bMain = IsMain();
    double dLastInput = glfwGetTime();

    // init thread processing
    OnInit();

    while (!ShouldExit(&pContext))
    {
        // input processing, main thread only
        if (bMain)
        {
            double dNewInput = glfwGetTime();
            OnInput(dNewInput - dLastInput);
            if (ShouldExit(&pContext)) break;
            dLastInput = dNewInput;
        }

        // window renedering and buffer swapping
        OnRender();
        if (ShouldExit(&pContext)) break;
        glfwSwapBuffers(pContext);

        // inter-thread message processing
        while (PopMessage(&msg))
        {
            OnMessage(&msg);
            if (ShouldExit(&pContext)) break;
        }

        // window event processing, main thread only
        if (bMain)
        {
            if (GetEventsTimeout() > 0.0)
            {
                // idle thread processing
                OnIdle();
                if (ShouldExit(&pContext)) break;
                glfwWaitEventsTimeout(GetEventsTimeout());
            }
            else glfwPollEvents();
        }
    }

    // exit thread processing
    OnExit();
    return GetExitcode();
}

void Thread::Join()
{
    // THREAD OBJECT COULD NOT BE JOINED
    YAGLPP_ASSERT(m_Thread.joinable());

    m_Thread.join();
    if (m_Autodelete)
    {
        // clean up joined thread (not main nor detached)
        delete this;
    }
}

bool Thread::PopMessage(_Out_ Message* msg)
{
    Thread* pCurrent = *thread_current();
    bool bResult = false;
    {
        std::lock_guard<std::mutex> lock(pCurrent->m_Mutex);
        if (!pCurrent->m_Queue.empty())
        {
            *msg = pCurrent->m_Queue.front();
            pCurrent->m_Queue.pop();
            bResult = true;
        }
        else msg->clear();
    }
    return bResult;
}

void Thread::PushMessage(_In_ Message* msg)
{
    // COULD NOT BE USED FROM CURRENT THREAD
    YAGLPP_ASSERT(!IsCurrent());
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        msg->sender = *thread_current();
        m_Queue.push(*msg);
    }
    if (!IsMain())
    {
        m_Sync.notify_one();
    }
}

void Thread::WaitMessage()
{
    // COULD NOT BE USED FROM MAIN THREAD
    YAGLPP_ASSERT(!IsMainCurrent());

    Thread* pCurrent = *thread_current();
    do
    {
        std::unique_lock<std::mutex> lock(pCurrent->m_Mutex);
        if (pCurrent->m_Queue.size() > 0) break;
        pCurrent->m_Sync.wait(lock);
    } while (true);
}

void Thread::WaitMessageTimeout(double sec)
{
    // COULD NOT BE USED FROM MAIN THREAD
    YAGLPP_ASSERT(!IsMainCurrent());

    Thread* pCurrent = *thread_current();
    do
    {
        std::unique_lock<std::mutex> lock(pCurrent->m_Mutex);
        if (pCurrent->m_Queue.size() > 0) break;
        pCurrent->m_Sync.wait_for(lock, std::chrono::nanoseconds((int64_t)(sec * 1e9)));
    } while (true);
}

void* Thread::operator new(std::size_t count)
{
    SetAlloc();
    return YAGLPP_MALLOC(char, count);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Thread::Detach()
{
    // THREAD OBJECT COULD NOT BE DETACHED
    YAGLPP_ASSERT(m_Thread.joinable());

    m_Thread.detach();
}

_Ret_notnull_ const char* Thread::GetArgValue(int index)
{
    // INVALID ARGUMENT INDEX PARAMETER
    YAGLPP_ASSERT((index >= 0) && (index < GetArgCount()));

    return s_Data.argV[index];
}

void Thread::SetEventsTimeout(double timeout)
{
    // MUST BE CALLED ONLY FROM THE MAIN THREAD
    YAGLPP_ASSERT(IsMainCurrent());

    if (s_Data.eventTimeout == 0.0)
    {
        // TIMEOUT VALUE IS OUT OF RANGE
        YAGLPP_ASSERT((timeout >= 0.0) && (timeout <= 2.0));

        s_Data.eventTimeout = timeout;
    }
}

void Thread::SetExitcode(int exitcode)
{
    // METHOD COULD NOT BE CALLED FROM ANOTHER THREAD
    YAGLPP_ASSERT(IsCurrent());

    if (m_Exitcode == 0) m_Exitcode = exitcode;
}

void Thread::Start()
{
    // THREAD OBJECT COULD NOT START NEW THREAD
    YAGLPP_ASSERT(!IsMain() && !m_Thread.joinable());

    m_Thread = std::thread(Thread::thread_proc, this);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Thread::Detach()
{
    m_Thread.detach();
}

inline _Ret_notnull_ const char* Thread::GetArgValue(int index)
{
    return s_Data.argV[index];
}

inline void Thread::SetEventsTimeout(double timeout)
{
    if (s_Data.eventTimeout == 0.0) s_Data.eventTimeout = timeout;
}

inline void Thread::SetExitcode(int exitcode)
{
    if (m_Exitcode == 0) m_Exitcode = exitcode;
}

inline void Thread::Start()
{
    m_Thread = std::thread(Thread::thread_proc, this);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
#endif // #ifndef YAGLPP_THREAD_H
