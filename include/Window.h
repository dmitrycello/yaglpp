#pragma once
#include "glfw3pp.h"
#include "Thread.h"
namespace glfw {
/*GLFW cursor input mode enumerator*/
enum class CursorMode : int
{
	/*Normal cursor value (default). Makes the cursor visible and behaving normally*/
	CursorNormal = GLFW_CURSOR_NORMAL,

	/*Hidden cursor value. Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving*/
	CursorHidden = GLFW_CURSOR_HIDDEN,

	/*Disabled cursor value. Hides and grabs the cursor, providing virtual and unlimited cursor movement. This is useful for implementing for example 3D camera controls*/
	CursorDisabled = GLFW_CURSOR_DISABLED,
	
#ifdef YAGLPP_NO_GLFW_LEGACY
	/*Captured cursor value. Makes the cursor visible but confined to the content area of the window*/
	CursorCaptured = GLFW_CURSOR_CAPTURED,
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
};

/*GLFW key modifier enumerator*/
enum class KeyModifier : int
{
	/*If this bit is set, one or more Shift keys were held down*/
	ModShift = GLFW_MOD_SHIFT,

	/*If this bit is set, one or more Control keys were held down*/
	ModControl = GLFW_MOD_CONTROL,

	/*If this bit is set, one or more Alt keys were held down*/
	ModAlt = GLFW_MOD_ALT,

	/*If this bit is set, one or more Super keys were held down*/
	ModSuper = GLFW_MOD_SUPER,

	/*If this bit is set, the Caps Lock key is enabled and <LockKeyMods> input mode is set*/
	ModCapsLock = GLFW_MOD_CAPS_LOCK,

	/*If this bit is set, the Num Lock key is enabled and the <LockKeyMods> input mode is set*/
	ModNumLock = GLFW_MOD_NUM_LOCK,
};

/*GLFW mouse button enumerator*/
enum class MouseButton : int
{
	/*Mouse button 1 value. Left mouse button on most of the hardware*/
	MouseButton1 = GLFW_MOUSE_BUTTON_1,

	/*Mouse button 2 value. Right mouse button on most of the hardware*/
	MouseButton2 = GLFW_MOUSE_BUTTON_2,

	/*Mouse button 3 value. Middle mouse button on most of the hardware*/
	MouseButton3 = GLFW_MOUSE_BUTTON_3,

	/*Mouse button 4 value. Back mouse button on most of the hardware*/
	MouseButton4 = GLFW_MOUSE_BUTTON_4,

	/*Mouse button 5 value. Forward mouse button on most of the hardware*/
	MouseButton5 = GLFW_MOUSE_BUTTON_5,

	/*Mouse button 6 value. Auxiliary mouse button on the modern hardware*/
	MouseButton6 = GLFW_MOUSE_BUTTON_6,

	/*Mouse button 7 value. Auxiliary mouse button on the modern hardware*/
	MouseButton7 = GLFW_MOUSE_BUTTON_7,

	/*Mouse button 8 value. Last available mouse button on the modern hardware*/
	MouseButton8 = GLFW_MOUSE_BUTTON_8,

	/*Left mouse button value*/
	MouseButtonLeft = GLFW_MOUSE_BUTTON_LEFT,

	/*Right mouse button value*/
	MouseButtonRight = GLFW_MOUSE_BUTTON_RIGHT,

	/*Middle mouse button value*/
	MouseButtonMiddle = GLFW_MOUSE_BUTTON_MIDDLE,

	/*Last available mouse button value*/
	MouseButtonLast = GLFW_MOUSE_BUTTON_LAST,
};

/*GLFW window object root class*/
class Window
{
private:
	friend class Monitor;
	static struct _SDATA {
		_SDATA();
		~_SDATA()
		{
			glfwTerminate(); // De-initialize GLFW
		}

#ifdef YAGLPP_NO_AFX_LAYOUT
		Thread s_NoAfxMainThread;
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT
	} s_Data;

	Thread* m_pThread; // Window context
	GLFWwindow* m_pWindow; // Window handle
	bool m_bWindowFullscreen; // Window fullscreen mode flag
	double m_dCursorPosX; // Cursor X-position relative to window content area since last cursor position event
	double m_dCursorPosY; // Cursor Y-position relative to window content area since last cursor position event
	double m_dMouseClickX; // Cursor X-position since last mouse-down event, used to detect click event
	double m_dMouseClickY; // Cursor Y-position since last mouse-down event, used to detect click event
	double m_dMouseDblClickTime; // Double-click timeout since last mouse-up event, used to detect dblclick event
	double m_dMouseDblClickX; // Cursor X-position since last mouse-up event, used to detect dblclick event
	double m_dMouseDblClickY; // Cursor Y-position since last mouse-up event, used to detect dblclick event
	float m_fXscale; // Window content X-scale since last window content scale event
	float m_fYscale; // Window content Y-scale since last window content scale event
	int m_iFramebufferHeight; // Window framebuffer height since last framebuffer size event
	int m_iFramebufferWidth; // Window framebuffer width since last framebuffer size event
	int m_iKeyMods; // Modifier flags since last key or mouse event
	int m_iMouseCaptureButton; // Button captured at mouse-down event
	int m_iMouseCaptureMods; // Modifier flags used while capturing button at mouse-down event
	int m_iMouseClickButton; // Last mouse button used to detect click event
	int m_iMouseDblClickButton; // Last mouse button used to detect dblclick event
	int m_iWindowClose; // Close flag used to delay window closing until release of mods (FIX)
	int m_iWindowFrameBottom; // The bottom edge of the window frame
	int m_iWindowFrameLeft; // The left edge of the window frame
	int m_iWindowFrameRight; // The right edge of the window frame
	int m_iWindowFrameTop; // The top edge of the window frame
	int m_iWindowFocused; // Window focus flag since last window focus event
	int m_iWindowHovered; // Window hover flag since last cursor enter event
	int m_iWindowIconified; // Window iconify flag since last window iconify event
	int m_iWindowMaximized; // Window maximize flag since last window maximize event
	int m_iWindowPosX; // X-position of window content area since last window position event
	int m_iWindowPosY; // Y-position of window content area since last window position event
	int m_iWindowSizeHeight; // Height of window content area since last window size event
	int m_iWindowSizeWidth; // Width of window content area since last window size event

	static void _charCallback(GLFWwindow* window, unsigned int codepoint)
	{
		((Window*)glfwGetWindowUserPointer(window))->onChar(codepoint);
	}

	static void _dropCallback(GLFWwindow* window, int pathcount, const char** paths)
	{
		((Window*)glfwGetWindowUserPointer(window))->onDrop(pathcount, paths);
	}

	static void _framebufferSizeCallback(GLFWwindow* window, int width, int height);

	int _getInputMode(int mode)
	{
		return glfwGetInputMode(_window(), mode);
	}

	int _getWindowAttrib(int attrib)
	{
		return glfwGetWindowAttrib(_window(), attrib);
	}

	static void _scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		((Window*)glfwGetWindowUserPointer(window))->onScroll(xoffset, yoffset);
	}

	void _setInputMode(int mode, int value)
	{
		glfwSetInputMode(_window(), mode, value);
	}

	void _setWindowAttrib(int attrib, int value)
	{
		glfwSetWindowAttrib(_window(), attrib, value);
	}

	static void _windowRefreshCallback(GLFWwindow* window)
	{
		((Window*)glfwGetWindowUserPointer(window))->onRefresh();
	}

	static void _applySetting(ContextSetting* setting);
	void _bindCallback();
	bool _create(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting);
	bool _createFullscreen(const char* title, Monitor& fullscreen, GLFWwindow* shared, ContextSetting* setting);
	static void _cursorEnterCallback(GLFWwindow* window, int entered);
	static void _cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void _init();
	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void _mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	GLFWwindow* _window();
	static void _windowCloseCallback(GLFWwindow* window);
	static void _windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
	static void _windowFocusCallback(GLFWwindow* window, int focused);
	static void _windowIconifyCallback(GLFWwindow* window, int iconified);
	static void _windowMaximizeCallback(GLFWwindow* window, int maximized);
	static void _windowPosCallback(GLFWwindow* window, int xpos, int ypos);
	static void _windowSizeCallback(GLFWwindow* window, int width, int height);

#ifdef _DEBUG
	static void _errorCallback(int code, const char* description);
#endif // #ifdef _DEBUG

protected:
	/*A window focus lost event handler*/
	virtual void onBlur() {}

	/*A Unicode character event handler
	@param The Unicode code point of the character*/
	virtual void onChar(unsigned int codepoint) {}

	/*A window close event handler*/
	virtual void onClose() {}

	/*A window content scale event handler
	@param The new x-axis content scale of the window
	@param The new y-axis content scale of the window*/
	virtual void onContentScale(float fXscale, float fYscale) {}

	/*A file drop event handler
	@param The number of dropped files
	@param The UTF-8 encoded file and/or directory path names*/
	virtual void onDrop(int count, _In_reads_(count) const char** paths) {}

	/*A window focus gain event handler*/
	virtual void onFocus() {}

	/*A framebuffer resize event handler
	@param The new width, in pixels, of the framebuffer
	@param The new height, in pixels, of the framebuffer*/
	virtual void onFramebuffer(int width, int height) {}

	/*A window iconify event handler*/
	virtual void onIconify() {}

	/*A keyboard key down event handler
	@param The enumerator of the keyboard key that was pressed
	@param The system-specific scancode of the key*/
	virtual void onKeyDown(KeyboardKey key, int scancode) {}

	/*A keyboard key repeat event handler
	@param The enumerator of the keyboard key that was hold and repeated
	@param The system-specific scancode of the key*/
	virtual void onKeyRepeat(KeyboardKey key, int scancode) {}

	/*A keyboard key up event handler
	@param The enumerator of the keyboard key that was released
	@param The system-specific scancode of the key*/
	virtual void onKeyUp(KeyboardKey key, int scancode) {}

	/*A window maximize event handler*/
	virtual void onMaximize() {}

	/*A mouse button capture event handler
	@param The enumerator of the mouse button that was pressed
	@return The overridden function must return true to start capture, false otherwise*/
	virtual bool onMouseCapture(MouseButton button) { return false; }

	/*A mouse button click event handler
	@param The enumerator of the mouse button that was clicked
	@param Current double click event flag*/
	virtual void onMouseClick(MouseButton button, bool dblclick) {}

	/*A mouse button double click event handler
	@param The enumerator of the mouse button that was double clicked*/
	virtual void onMouseDblClick(MouseButton button) {}

	/*A mouse button down event handler
	@param The enumerator of the mouse button that was pressed*/
	virtual void onMouseDown(MouseButton button) {}

	/*A mouse button drag event handler
	@param The enumerator of the mouse button that is being captured
	@param The new x-coordinate, in screen coordinates, of the cursor
	@param The new y-coordinate, in screen coordinates, of the cursor*/
	virtual void onMouseDrag(MouseButton button, double xpos, double ypos) {}

	/*A mouse cursor enter event handler*/
	virtual void onMouseEnter() {}

	/*A mouse cursor leave event handler*/
	virtual void onMouseLeave() {}

	/*A mouse cursor move event handler
	@param The new x-coordinate, in screen coordinates, of the cursor
	@param The new y-coordinate, in screen coordinates, of the cursor
	@param The current mouse capture flag*/
	virtual void onMouseMove(double xpos, double ypos, bool captured) {}

	/*A mouse button release event handler
	@param The enumerator of the released mouse button, after it was captured*/
	virtual void onMouseRelease(MouseButton button) {}

	/*A mouse button up event handler
	@param The enumerator of the mouse button that was released*/
	virtual void onMouseUp(MouseButton button) {}

	/*A window position event handler
	@param The new x-coordinate, in screen coordinates, of the upper-left corner of the content area of the window
	@param The new y-coordinate, in screen coordinates, of the upper-left corner of the content area of the window*/
	virtual void onPosition(int xpos, int ypos) {}

	/*A window content refresh event handler*/
	virtual void onRefresh() {}

	/*A window size event handler
	@param The new width, in screen coordinates, of the window
	@param The new height, in screen coordinates, of the window*/
	virtual void onResize(int width, int height) {}

	/*A window restore event handler, after it was iconified or (3.3) maximized*/
	virtual void onRestore() {}

	/*A scroll event handler
	@param The scroll offset along the x-axis
	@param The scroll offset along the y-axis*/
	virtual void onScroll(double xoffset, double yoffset) {}

public:
	/*(1) Construct an empty window object*/
	Window()
	{
		_init();
	}

	/*(2) Construct window object with <createWindow>*/
	Window(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr)
	{
		_init();
		_create(width, height, title, nullptr, setting);
	}

	/*(3) Construct window object with <createWindow>*/
	Window(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		_init();
		_create(width, height, title, shared._window(), setting);
	}

	/*(4) Construct window object with <createWindow>*/
	Window(_In_z_ const char* title, Monitor& fullscreen, _In_opt_ ContextSetting* setting = nullptr)
	{
		_init();
		_createFullscreen(title, fullscreen, nullptr, setting);
	}

	/*(5) Construct window object with <createWindow>*/
	Window(_In_z_ const char* title, Monitor& fullscreen, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		_init();
		_createFullscreen(title, fullscreen, shared._window(), setting);
	}

	/*Cleans up the valid window object*/
	~Window()
	{
		if (isWindow())
		{
			destroyWindow();
		}
	}

	/*(1) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] Pointer to context setting structure, or NULL to use default setting
	@return True if window and its context created successfully, false otherwise*/
	bool createWindow(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr)
	{
		return _create(width, height, title, nullptr, setting);
	}

	/*(2) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting
	@return True if window and its context created successfully, false otherwise*/
	bool createWindow(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		return _create(width, height, title, shared._window(), setting);
	}

	/*(3) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor object to use for full screen mode
	@param [in] Pointer to context setting structure, or NULL to use default setting
	@return True if window and its context created successfully, false otherwise*/
	bool createWindow(_In_z_ const char* title, Monitor& fullscreen, _In_opt_ ContextSetting* setting = nullptr)
	{
		return _createFullscreen(title, fullscreen, nullptr, setting);
	}

	/*(4) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor oblect to use for full screen mode
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting
	@return True if window and its context created successfully, false otherwise*/
	bool createWindow(_In_z_ const char* title, Monitor& fullscreen, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		return _createFullscreen(title, fullscreen, shared._window(), setting);
	}

	/*Clears window object, destroys the associated window and its context*/
	void destroyWindow()
	{
		glfwDestroyWindow(_window());
		m_pWindow = nullptr;
	}

	/*This function brings the specified window to front and sets input focus. The window should already be visible and not iconified*/
	void focusWindow()
	{
		glfwFocusWindow(_window());
	}

	/*Gets auto iconify attribute flag (default true). Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows
	@return Auto iconify attribute flag*/
	bool getAutoIconify()
	{
		return (bool)_getWindowAttrib(GLFW_AUTO_ICONIFY);
	}

	/*Gets client API attribute value
	@return The client API attribute enumerator, default <OpenglApi>*/
	ClientApi getClientApi()
	{
		return (ClientApi)_getWindowAttrib(GLFW_CLIENT_API);
	}

	/*This function returns the contents of the system clipboard, if it contains or is convertible to a UTF-8 encoded string
	@return The contents of the clipboard as a UTF-8 encoded string, or NULL*/
	_Ret_maybenull_z_ const char* getClipboardString()
	{
		return glfwGetClipboardString(_window());
	}

	/*Gets context creation API attribute value
	@return The context creation API attribute enumerator, default <NativeContextApi>*/
	ContextCreationApi getContextCreationApi()
	{
		return (ContextCreationApi)_getWindowAttrib(GLFW_CONTEXT_CREATION_API);
	}

	/*Gets context no error attribute flag. Specifies whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior
	@return Context no error attribute flag, default false*/
	bool getContextNoError()
	{
		return (bool)_getWindowAttrib(GLFW_CONTEXT_NO_ERROR);
	}

	/*Gets context release behavior attribute value
	@return The context release behavior attribute enumerator, default <AnyReleaseBehavior>*/
	ContextReleaseBehavior getContextReleaseBehavior()
	{
		return (ContextReleaseBehavior)_getWindowAttrib(GLFW_CONTEXT_RELEASE_BEHAVIOR);
	}

	/*Gets context revision attribute value. Indicate the client API revision version of the window's context
	@return Context revision attribute value*/
	int getContextRevision()
	{
		return _getWindowAttrib(GLFW_CONTEXT_REVISION);
	}

	/*Gets context robustness attribute value
	@return The context robustness attribute enumerator, default <NoRobustness>*/
	ContextRobustness getContextRobustness()
	{
		return (ContextRobustness)_getWindowAttrib(GLFW_CONTEXT_ROBUSTNESS);
	}

	/*Gets the calling thread on which the context of the specified window were made current
	@return Pointer to the context thread*/
	_Ret_notnull_ Thread* getContextThread();

	/*Gets context version major attribute value. Indicate the client API major version of the window's context
	@return Context version major attribute value, default 1*/
	int getContextVersionMajor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MAJOR);
	}

	/*Gets context version minor attribute value. Indicate the client API minor version of the window's context
	@return Context version minor attribute value, default 0*/
	int getContextVersionMinor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MINOR);
	}

	/*Gets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input
	@return Cursor input mode enumerator, defult <CursorNormal>*/
	CursorMode getCursorMode()
	{
		return (CursorMode)_getInputMode(GLFW_CURSOR);
	}

	/*This function gets the immediate position of the cursor, in screen coordinates, relative to the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getCursorPosX> and <getCursorPosY> calls*/
	void getCursorPos()
	{
		glfwGetCursorPos(_window(), &m_dCursorPosX, &m_dCursorPosY);
	}

	/*Retrieves cursor x-position relative to window content area since last cursor position event, or <getCursorPos> call
	@return Cursor x-position value*/
	double getCursorPosX()
	{
		return m_dCursorPosX;
	}

	/*Retrieves cursor y-position relative to window content area since last cursor position event, or <getCursorPos> call
	@return Cursor y-position value*/
	double getCursorPosY()
	{
		return m_dCursorPosY;
	}

	/*Gets decorated attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows
	@return Decorated attribute flag, default true*/
	bool getDecorated()
	{
		return (bool)_getWindowAttrib(GLFW_DECORATED);
	}

	/*Gets floating attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows
	@return Floating attribute flag, default false*/
	bool getFloating()
	{
		return (bool)_getWindowAttrib(GLFW_FLOATING);
	}

	/*Gets focused attribute flag. Specifies whether the windowed mode window will be given input focus when created. This attribute is ignored for full screen and initially hidden windows
	@return Focused attribute flag, default true*/
	bool getFocused()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUSED);
	}

	/*Gets focus on show attribute flag. Indicates whether the window will be given input focus when <showWindow> is called
	@return Focus on show attribute flag, default true*/
	bool getFocusOnShow()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUS_ON_SHOW);
	}

	/*This function gets the immediate size, in pixels, of the framebuffer of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getFramebufferSizeWidth> and <getFramebufferSizeHeight> calls*/
	void getFramebufferSize()
	{
		glfwGetFramebufferSize(_window(), &m_iFramebufferWidth, &m_iFramebufferHeight);
	}

	/*Retrieves window framebuffer height since last framebuffer size event, or <getFramebufferSize> call
	@return Framebuffer height value*/
	int getFramebufferSizeHeight()
	{
		return m_iFramebufferHeight;
	}

	/*Retrieves window framebuffer width since last framebuffer size event, or <getFramebufferSize> call
	@return Framebuffer width value*/
	int getFramebufferSizeWidth()
	{
		return m_iFramebufferWidth;
	}

	/*Gets hovered attribute flag. Indicates whether the cursor is currently directly over the content area of the window, with no other windows between
	@return Hovered attribute flag*/
	bool getHovered()
	{
		return (bool)_getWindowAttrib(GLFW_HOVERED);
	}

	/*Gets iconified attribute flag. Indicates whether the specified window is iconified
	@return Iconified attribute flag*/
	bool getIconified()
	{
		return (bool)_getWindowAttrib(GLFW_ICONIFIED);
	}

	/*This function returns the last state reported for the specified key to the specified window
	@param The desired keyboard key enumerator value. <KeyUnknown> is not a valid key for this function
	@return True if the desired keyboard key is pressed, false otherwise*/
	bool getKey(KeyboardKey key)
	{
		return (bool)glfwGetKey(_window(), (int)key);
	}

	/*Gets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on
	@return Lock key mods input mode flag, default false*/
	bool getLockKeyMods()
	{
		return (bool)_getInputMode(GLFW_LOCK_KEY_MODS);
	}

	/*Gets maximized attribute flag. Specifies whether the windowed mode window will be maximized when created. This attribute is ignored for full screen windows
	@return Maximized attribute flag, default false*/
	bool getMaximized()
	{
		return (bool)_getWindowAttrib(GLFW_MAXIMIZED);
	}

	/*This function returns the last state reported for the specified mouse button to the specified window
	@param The desired mouse button enumerator
	@return True if the desired mouse button is pressed, false otherwise*/
	bool getMouseButton(MouseButton button)
	{
		return (bool)_getWindowAttrib((int)button);
	}

	/*Gets OpenGL debug context attribute flag. Specifies whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality
	@return OpenGL debug context attribute flag, default false*/
	bool getOpenglDebugContext()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_DEBUG_CONTEXT);
	}

	/*Gets OpenGL forward compatible attribute flag. Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored
	@return OpenGL forward compatible attribute flag, default false*/
	bool getOpenglForwardCompat()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_FORWARD_COMPAT);
	}

	/*Gets OpenGL profile attribute value
	@return The OpenGL profile attribute enumerator, <default OpenglAnyProfile>*/
	OpenglProfile getOpenglProfile()
	{
		return (OpenglProfile)_getWindowAttrib(GLFW_OPENGL_PROFILE);
	}

	/*Gets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled
	@return Raw mouse motion input mode flag, default false*/
	bool getRawMouseMotion()
	{
		return (bool)_getInputMode(GLFW_RAW_MOUSE_MOTION);
	}

	/*Gets resizable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This attribute is ignored for full screen and undecorated windows
	@return Resizable attribute flag, default true*/
	bool getResizable()
	{
		return (bool)_getWindowAttrib(GLFW_RESIZABLE);
	}

	/*Gets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed
	@return Sticky keys input mode flag, default false*/
	bool getStickyKeys()
	{
		return (bool)(GLFW_STICKY_KEYS);
	}

	/*Gets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed
	@return Sticky mouse buttons input mode flag, default false*/
	bool getStickyMouseButtons()
	{
		return (bool)_getInputMode(GLFW_STICKY_MOUSE_BUTTONS);
	}

	/*Gets transparent framebuffer attribute flag. Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel
	@return Transparent framebuffer attribute flag, default false*/
	bool getTransparentFramebuffer()
	{
		return (bool)_getWindowAttrib(GLFW_TRANSPARENT_FRAMEBUFFER);
	}

	/*Gets visible attribute flag. Specifies whether the windowed mode window will be initially visible. This attribute is ignored for full screen windows
	@return Visible attribute flag, default true*/
	bool getVisible()
	{
		return (bool)_getWindowAttrib(GLFW_VISIBLE);
	}

	/*This function gets the immediate content scale of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowContentScaleX> and <getWindowContentScaleY> calls*/
	void getWindowContentScale()
	{
		glfwGetWindowContentScale(_window(), &m_fXscale, &m_fYscale);
	}

	/*Retrieves window content x-scale since last window content scale event, or <getWindowContentScale> call
	@return Window content x-scale*/
	float getWindowContentScaleX()
	{
		return m_fXscale;
	}

	/*Retrieves window content y-scale since last window content scale event, or <getWindowContentScale> call
	@return Window content y-scale*/
	float getWindowContentScaleY()
	{
		return m_fYscale;
	}

	/*This function gets the immediate size, in screen coordinates, of each edge of the frame of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowFrameBottom>, <getWindowFrameLeft>, <getWindowFrameRight> and <getWindowFrameTop> calls*/
	void getWindowFrameSize()
	{
		glfwGetWindowFrameSize(_window(), &m_iWindowFrameLeft, &m_iWindowFrameTop, &m_iWindowFrameRight, &m_iWindowFrameBottom);
	}

	/*Retrieves window bottom edge of the frame since last <getWindowContentScale> call
	@return Window frame bottom edge*/
	int getWindowFrameBottom()
	{
		return m_iWindowFrameBottom;
	}

	/*Retrieves window left edge of the frame since last <getWindowContentScale> call
	@return Window frame left edge*/
	int getWindowFrameLeft()
	{
		return m_iWindowFrameLeft;
	}

	/*Retrieves window right edge of the frame since last <getWindowContentScale> call
	@return Window frame right edge*/
	int getWindowFrameRight()
	{
		return m_iWindowFrameRight;
	}

	/*Retrieves window top edge of the frame since last <getWindowContentScale> call
	@return Window frame top edge*/
	int getWindowFrameTop()
	{
		return m_iWindowFrameTop;
	}

	/*This function retrieves the monitor object that the specified window is in full screen on
	@param [out] The empty monitor object used in full screen mode*/
	void getWindowMonitor(Monitor& monitor);

	/*This function returns the opacity of the window, including any decorations
	@return The opacity of the specified window*/
	float getWindowOpacity()
	{
		return glfwGetWindowOpacity(_window());
	}

	/*This function gets the immediate position, in screen coordinates, of the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowPosX> and <getWindowPosY> calls*/
	void getWindowPos()
	{
		glfwGetWindowPos(_window(), &m_iWindowPosX, &m_iWindowPosY);
	}

	/*Retrieves window x-position of window content area since last window position event, or <getWindowPos> call
	@return Window x-position*/
	int getWindowPosX()
	{
		return m_iWindowPosX;
	}

	/*Retrieves window y-position of window content area since last window position event, or <getWindowPos> call
	@return Window y-position*/
	int getWindowPosY()
	{
		return m_iWindowPosY;
	}

	/*This function gets the immediate size, in screen coordinates, of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowSizeHeight> and <getWindowSizeWidth> calls*/
	void getWindowSize()
	{
		glfwGetWindowSize(_window(), &m_iWindowSizeWidth, &m_iWindowSizeHeight);
	}

	/*Retrieves height of window content area since last window size event, or <getWindowSize> call
	@return The window height value*/
	int getWindowSizeHeight()
	{
		return m_iWindowSizeHeight;
	}

	/*Retrieves width of window content area since last window size event, or <getWindowSize> call
	@return The window width value*/
	int getWindowSizeWidth()
	{
		return m_iWindowSizeWidth;
	}

	/*This function hides the specified window if it was previously visible*/
	void hideWindow()
	{
		glfwHideWindow(_window());
	}

	/*This function iconifies/minimizes the specified window, if it was previously restored*/
	void iconifyWindow()
	{
		glfwIconifyWindow(_window());
	}

	/*Check if context of the specified window has been made current
	@return True if context is current, false otherwise*/
	bool isContextCurrent()
	{
		return m_pThread != nullptr;
	}

	/*Checks the state of specified key modifier since last key or mouse event
	@param The desired key modifier enumerator
	@return True if specified key modifier was pressed since last key or mouse event, false otherwise*/
	bool isKeyModifier(KeyModifier mod)
	{
		return (bool)(m_iKeyMods & (int)mod);
	}

	/*Checks if any key modifier was pressed since last key or mouse event
	@return True if any key modifier is pressed, false otherwise*/
	bool isModifierPressed()
	{
		return m_iKeyMods != 0;
	}

	/*Checks if mouse is in captured mode since last mouse event
	@return True if mouse is captured, false otherwise*/
	bool isMouseCaptured()
	{
		return m_iMouseCaptureButton != GLFW_DONT_CARE;
	}

	/*Check if valid window object
	@return True if window object, false otherwise*/
	bool isWindow()
	{
		return m_pWindow != nullptr;
	}

	/*Checks if window receives focus since last window focus event
	@return True if window is focused, false otherwise*/
	bool isWindowFocused()
	{
		return m_iWindowFocused == GLFW_TRUE;
	}

	/*Checks via API if window in fullscreen mode since creation or last monitor operation
	@return True if window in fullscreen mode, false otherwise*/
	bool isWindowFullscreen();

	/*Checks if mouse cursor in window client area since last cursor enter event
	@return True if mouse cursor is over the window client area, false otherwise*/
	bool isWindowHovered()
	{
		return m_iWindowHovered == GLFW_TRUE;
	}

	/*Checks if window is iconified since last window iconify event
	@return True if window is iconified, false otherwise*/
	bool isWindowIconified()
	{
		return m_iWindowIconified == GLFW_TRUE;
	}

	/*Checks if window is maximized since last window maximize event
	@return True if window maximized since last maximize event, false otherwise*/
	bool isWindowMaximized()
	{
		return m_iWindowMaximized == GLFW_TRUE;
	}

	/*(1) This function makes the OpenGL or OpenGL ES context of the specified window current on the main thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. Associates the window with the calling thread, at the first call initializes OpenGL*/
	void makeContextCurrent()
	{
		makeContextCurrent(Thread::getMainThread());
	}

	/*(2) This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. Associates the window with the calling thread, at the first call initializes OpenGL
	@param [in] The pointer to thread object on which the context is to be made current*/
	void makeContextCurrent(_In_ Thread* thread);

	/*This function makes the OpenGL or OpenGL ES context non-current on the calling thread. Dissociates the window from the calling thread*/
	void makeContextNonCurrent();

	/*This function maximizes the specified window if it was previously not maximized*/
	void maximizeWindow()
	{
		glfwMaximizeWindow(_window());
	}

	/*This function requests user attention to the specified window. On platforms where this is not supported, attention is requested to the application as a whole*/
	void requestWindowAttention()
	{
		glfwRequestWindowAttention(_window());
	}

	/*This function restores the specified window, if it was previously iconified/minimized or maximized*/
	void restoreWindow()
	{
		glfwRestoreWindow(_window());
	}

	/*Sets auto iconify writable attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows
	@param New auto iconify attribute flag, default true*/
	void setAutoIconify(bool flag)
	{
		_setWindowAttrib(GLFW_AUTO_ICONIFY, (int)flag);
	}

	/*This function sets the system clipboard to the specified, UTF-8 encoded string
	@param A UTF-8 encoded string*/
	void setClipboardString(_In_z_ const char* string)
	{
		glfwSetClipboardString(_window(), string);
	}

	/*This function sets the cursor image to be used when the cursor is over the content area of the specified window
	@param [in] The cursor object to set*/
	void setCursor(Cursor& cursor);

	/*Sets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input
	@param New cursor input mode enumerator, <defult CursorNormal>*/
	void setCursorMode(CursorMode cursorMode)
	{
		_setInputMode(GLFW_CURSOR, (int)cursorMode);
	}

	/*This function sets the position, in screen coordinates, of the cursor relative to the upper-left corner of the client area of the specified window
	@param The desired x-coordinate, relative to the left edge of the client area
	@param The desired y-coordinate, relative to the top edge of the client area*/
	void setCursorPos(double xpos, double ypos)
	{
		glfwSetCursorPos(_window(), xpos, ypos);
	}

	/*Sets decorated writable attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows
	@param New decorated attribute flag, default true*/
	void setDecorated(bool flag)
	{
		_setWindowAttrib(GLFW_DECORATED, (int)flag);
	}

	/*Sets floating writable attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows
	@param New floating attribute flag, default false*/
	void setFloating(bool flag)
	{
		_setWindowAttrib(GLFW_FLOATING, (int)flag);
	}

	/*Sets focus on show writable attribute flag. Specifies whether the window will be given input focus when <showWindow> is called
	@param New focus on show attribute flag, default true*/
	void setFocusOnShow(bool flag)
	{
		_setWindowAttrib(GLFW_FOCUS_ON_SHOW, (int)flag);
	}

	/*Sets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on
	@param New lock key mods input mode flag, default false*/
	void setLockKeyMods(bool flag)
	{
		_setInputMode(GLFW_LOCK_KEY_MODS, (int)flag);
	}

	/*Sets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled
	@param New raw mouse motion input mode flag, default false*/
	void setRawMouseMotion(bool flag)
	{
		_setInputMode(GLFW_RAW_MOUSE_MOTION, (int)flag);
	}

	/*Sets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed
	@param New sticky keys input mode flag, default false*/
	void setStickyKeys(bool bFlag)
	{
		_setInputMode(GLFW_STICKY_KEYS, (int)bFlag);
	}

	/*Sets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed
	@param New sticky mouse buttons input mode flag, default false*/
	void setStickyMouseButtons(bool flag)
	{
		_setInputMode(GLFW_STICKY_MOUSE_BUTTONS, (int)flag);
	}

	/*Sets resizable writable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <setWindowSize> function. This attribute is ignored for full screen and undecorated windows
	@param New resizable attribute flag, default true*/
	void setResizable(bool flag)
	{
		_setWindowAttrib(GLFW_RESIZABLE, flag);
	}

	/*This function sets the required aspect ratio of the content area of the specified window
	@param The numerator of the desired aspect ratio
	@param The denominator of the desired aspect ratio*/
	void setWindowAspectRatio(int numer, int denom)
	{
		glfwSetWindowAspectRatio(_window(), numer, denom);
	}

	/*This function sets the icon of the specified window with an array of candidate images, from which the system selects the closest to the desired sizes
	@param The number of images in the specified array
	@param [in] The array of images to create the icon from*/
	void setWindowIcon(int count, _In_reads_(count) const GLFWimage* images)
	{
		glfwSetWindowIcon(_window(), count, images);
	}

	/*(STB) Set icon of specified window from image object. Does nothing if empty object
	@param [in] Stb image object*/
	void setWindowIcon(StbImage& stbImage);

#ifndef YAGLPP_NO_FREEIMAGE
	/*(FI) Set icon of specified window from free image object. Does nothing if empty object
	@param [in] Free image object*/
	void setWindowIcon(FreeImage& freeImage);

	/*(FI) Set icon of specified window from binary resource. Does nothing if invalid resource
	@param The icon resource id of <RCDATA> type*/
	void setWindowIcon(int rcid);

	/*(FI) Set icon of specified window from the icon file. Does nothing if invalid file
	@param [in] Path to the icon file*/
	void setWindowIcon(_In_z_ const char* filepath);
#endif // #ifndef YAGLPP_NO_FREEIMAGE

	/*(1) This function sets the primary monitor that the window uses for full screen mode*/
	void setWindowMonitor();

	/*(2) This function sets the monitor that the window uses for full screen mode. It also sets selected video mode parameters via window hints
	@param Monitor object with selected monitor and video mode*/
	void setWindowMonitor(Monitor& monitor);

	/*This function sets the opacity of the window, including any decorations
	@param The desired opacity of the specified window*/
	void setWindowOpacity(float opacity)
	{
		glfwSetWindowOpacity(_window(), opacity);
	}

	/*This function sets the position, in screen coordinates, of the upper-left corner of the content area of the specified windowed mode window
	@param The x-coordinate of the upper-left corner of the content area
	@param The y-coordinate of the upper-left corner of the content area*/
	void setWindowPos(int xpos, int ypos)
	{
		glfwSetWindowPos(_window(), xpos, ypos);
	}

	/*This function sets the value of the close flag of the specified window
	@param The new window close flag*/
	void setWindowShouldClose(bool close)
	{
		glfwSetWindowShouldClose(_window(), (int)close);
	}

	/*This function sets the size, in screen coordinates, of the content area of the specified window
	@param The desired width, in screen coordinates, of the window content area
	@param The desired height, in screen coordinates, of the window content area*/
	void setWindowSize(int width, int height)
	{
		glfwSetWindowSize(_window(), width, height);
	}

	/*This function sets the size limits of the content area of the specified window. If the window is full screen, the size limits only take effect once it is made windowed. To specify only a minimum size or only a maximum one, set the other pair to GLFW_DONT_CARE
	@param The minimum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The minimum height, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum height, in screen coordinates, of the content area, or GLFW_DONT_CARE*/
	void setWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
	{
		glfwSetWindowSizeLimits(_window(), minwidth, minheight, maxwidth, maxheight);
	}

	/*This function sets the window title, encoded as UTF-8, of the specified window
	@param [in] The UTF-8 encoded window title*/
	void setWindowTitle(_In_z_ const char* title)
	{
		glfwSetWindowTitle(_window(), title);
	}

	/*This function makes the specified window visible if it was previously hidden*/
	void showWindow()
	{
		glfwShowWindow(_window());
	}

	/*This function swaps the front and back buffers of the specified window. If the swap interval is greater than zero, the GPU driver waits the specified number of screen updates before swapping the buffers*/
	void swapBuffers()
	{
		glfwSwapBuffers(_window());
	}

	/*Switch back to the default arrow cursor*/
	void unsetCursor()
	{
		glfwSetCursor(_window(), nullptr);
	}

	/*This function disables the aspect ratio limit*/
	void unsetWindowAspectRatio()
	{
		glfwSetWindowAspectRatio(_window(), GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	/*This function reverts the window to its default icon*/
	void unsetWindowIcon()
	{
		glfwSetWindowIcon(_window(), 0, nullptr);
	}

	/*This function unsets the monitor that the window uses for full screen mode, setting it into windowed mode*/
	void unsetWindowMonitor()
	{
		m_bWindowFullscreen = false;
		glfwSetWindowMonitor(_window(), nullptr, m_iWindowPosX, m_iWindowPosY, m_iWindowSizeWidth, m_iWindowSizeHeight, GLFW_DONT_CARE);
	}

	/*This function returns the value of the close flag of the specified window
	@return The window close flag*/
	bool windowShouldClose()
	{
		return (bool)glfwWindowShouldClose(_window());
	}

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*Gets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms
	@return Mouse passthrough attribute flag, default false*/
	bool getMousePassthrough()
	{
		return (bool)_getWindowAttrib(GLFW_MOUSE_PASSTHROUGH);
	}

	/*This function returns the window title, encoded as UTF-8, of the specified window, previously set by <createWindow> or <setWindowTitle>
	@return The UTF-8 encoded window title*/
	_Ret_z_ const char* getWindowTitle()
	{
		return glfwGetWindowTitle(_window());
	}

	/*Sets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms
	@param New mouse passthrough attribute flag, default false*/
	void setMousePassthrough(bool flag)
	{
		_setWindowAttrib(GLFW_MOUSE_PASSTHROUGH, (int)flag);
	}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
}; // class Window
} // namespace glfw

#include "Cursor.h"
#include "Monitor.h"
namespace glfw {
inline void Window::setCursor(Cursor& cursor)
{
	glfwSetCursor(_window(), cursor._cursor());
}

inline void Window::setWindowMonitor()
{
	glfw::Monitor m(true); setWindowMonitor(m);
}

#ifndef _DEBUG
inline GLFWwindow* Window::_window()
{
	return m_pWindow;
}

inline _Ret_notnull_ Thread* Window::getContextThread()
{
	return m_pThread;
}
#endif // #ifdef _DEBUG
} // namespace glfw
