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

/*GLFW key action enumerator*/
enum class KeyAction : int
{
	/*The key was released*/
	Release = GLFW_RELEASE,

	/*The key was pressed*/
	Press = GLFW_PRESS,

	/*The key was held down until it repeated*/
	Repeat = GLFW_REPEAT,
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

/*GLFW mouse action enumerator*/
enum class MouseAction : int
{
	/*The mouse button was released*/
	Release = GLFW_RELEASE,

	/*The mouse button was pressed*/
	Press = GLFW_PRESS,
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

/*Constant expression KeyModifier bitwise OR operator combining multiple KeyModifiers into mod mask
@param KeyModifier mod 1 enumerator
@param KeyModifier mod 2 enumerator
@return Resulting KeyModifier mask enumerator*/
constexpr KeyModifier operator | (KeyModifier mod1, KeyModifier mod2)
{
	return (KeyModifier)((int)mod1 | (int)mod2);
}

/*Constant expression KeyModifier bitwise AND operator verifying if mod exists in the mod mask
@param KeyModifier mod enumerator
@param KeyModifier mod mask enumerator
@return True if mod exists in the mod mask, false otherwise*/
constexpr bool operator & (KeyModifier mod, KeyModifier mask)
{
	return (bool)((int)mod & (int)mask);
}

/*This function returns via API the pointer to window object whose OpenGL or OpenGL ES context is current on the calling thread
@return The pointer to current context window object, or NULL*/
inline _Ret_maybenull_ Window* getCurrentContext()
{
	GLFWwindow* pContext = glfwGetCurrentContext();
	return (pContext != nullptr) ? (Window*)glfwGetWindowUserPointer(pContext) : nullptr;
}

/*GLFW window object root class*/
class Window
{
private:
	friend class Thread;
	friend class Monitor;

	// Window object member data structure
	struct _MDATA {
		int iCursorEntered; // Window hover flag since last cursor enter event
		unsigned int uCharCodepoint; // The Unicode code point of the character since last character event
		double dCursorPosX; // Cursor X-position relative to window content area since last cursor position event
		double dCursorPosY; // Cursor Y-position relative to window content area since last cursor position event
		int iFramebufferWidth; // Window framebuffer width since last framebuffer size event
		int iFramebufferHeight; // Window framebuffer height since last framebuffer size event
		int iKeyAction; // Keyboard key action since last key event
		int iKeyboardKey; // Keyboard key since last key event
		int iKeyMods; // Keyboard key modifier flags since last key or mouse event
		int iKeyScancode; // Keyboard key scancode since last key event
		int iMouseAction; // Mouse action since last mouse event
		int iMouseButton; // Mouse button since last mouse event
		double dScrollOffsetX; // Scroll offset along the x-axis since last scroll event
		double dScrollOffsetY; // scroll offset along the y-axis since last scroll event
		int iWindowClose; // Close flag used to delay window closing until release of mods (FIX)
		float fWindowContentScaleX; // Window content X-scale since last window content scale event
		float fWindowContentScaleY; // Window content Y-scale since last window content scale event
		int iWindowFocused; // Window focus flag since last window focus event
		int iWindowIconified; // Window iconify flag since last window iconify event
		int iWindowMaximized; // Window maximize flag since last window maximize event
		int iWindowPosX; // X-position of window content area since last window position event
		int iWindowPosY; // Y-position of window content area since last window position event
		int iWindowWidth; // Width of window content area since last window size event
		int iWindowHeight; // Height of window content area since last window size event
		int iWindowFrameBottom; // The bottom edge of the window frame
		int iWindowFrameLeft; // The left edge of the window frame
		int iWindowFrameRight; // The right edge of the window frame
		int iWindowFrameTop; // The top edge of the window frame
		int iWindowFullscreen; // Window fullscreen state flag
		int iWindowVisible; // Window visible state flag
		GLFWwindow* pWindow; // GLFW window object
		Thread* pThread; // Context thread
	} _m;

#ifdef YAGLPP_NO_AFX_LAYOUT
	static Thread noAfxMainThread;
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT

	static void _applySetting(ContextSetting* setting);
	void _bindCallback();
	static void _charCallback(GLFWwindow* window, unsigned int codepoint);
	void _create(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting);
	void _createFullscreen(const char* title, Monitor& fullscreen, GLFWwindow* shared, ContextSetting* setting);
	static void _cursorEnterCallback(GLFWwindow* window, int entered);
	static void _cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void _dropCallback(GLFWwindow* window, int pathcount, const char** paths);
	static void _framebufferSizeCallback(GLFWwindow* window, int width, int height);
	int _getInputMode(int mode);
	int _getWindowAttrib(int attrib);
	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void _mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void _scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void _setInputMode(int mode, int value);
	void _setWindowAttrib(int attrib, int value);
	GLFWwindow* _window() const;
	static void _windowCloseCallback(GLFWwindow* window);
	static void _windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
	static void _windowFocusCallback(GLFWwindow* window, int focused);
	static void _windowIconifyCallback(GLFWwindow* window, int iconified);
	static void _windowMaximizeCallback(GLFWwindow* window, int maximized);
	static void _windowPosCallback(GLFWwindow* window, int xpos, int ypos);
	static void _windowRefreshCallback(GLFWwindow* window);
	static void _windowSizeCallback(GLFWwindow* window, int width, int height);

#ifdef _DEBUG
	static void _errorCallback(int code, const char* description);
#endif // #ifdef _DEBUG

protected:
	/*A Unicode character event handler
	@param The Unicode code point of the character*/
	virtual void onChar(unsigned int codepoint) {}

	/*A cursor enter event handler
	@param True if the cursor entered the window's client area, false otherwise*/
	virtual void onCursorEnter(bool entered) {}

	/*A cursor position event handler
	@param The new x-coordinate, in screen coordinates, of the cursor
	@param The new y-coordinate, in screen coordinates, of the cursor*/
	virtual void onCursorPos(double xpos, double ypos) {}

	/*A file drop event handler
	@param The number of dropped files
	@param The UTF-8 encoded file and/or directory path names*/
	virtual void onDrop(int pathcount, _In_reads_(pathcount) const char** paths) {}

	/*A framebuffer size event handler
	@param The new width, in pixels, of the framebuffer
	@param The new height, in pixels, of the framebuffer*/
	virtual void onFramebufferSize(int width, int height) {}

	/*A keyboard key event handler
	@param The keyboard key enumerator that was pressed, released or held down until repeated
	@param The system-specific scancode of the key
	@param The key action enumerator describing if the key was pressed, released or held down until repeated
	@param The key modifier enumerator describing which modifier keys were held down*/
	virtual void onKey(KeyboardKey key, int scancode, KeyAction action, KeyModifier mods) {}

	/*A mouse button event handler
	@param The mouse button enumerator that was pressed or released
	@param The mouse action enumerator describing if the mouse was pressed or released
	@param The key modifier enumerator describing which modifier keys were held down*/
	virtual void onMouseButton(MouseButton button, MouseAction action, KeyModifier mods) {}

	/*A scroll event handler
	@param The scroll offset along the x-axis
	@param The scroll offset along the y-axis*/
	virtual void onScroll(double xoffset, double yoffset) {}

	/*A window close event handler*/
	virtual void onWindowClose() {}

	/*A window content scale event handler
	@param The new x-axis content scale of the window
	@param The new y-axis content scale of the window*/
	virtual void onWindowContentScale(float xscale, float yscale) {}

	/*A window focus gain event handler
	@param True if the window was given input focus, false otherwise*/
	virtual void onWindowFocus(bool focused) {}

	/*A window iconify event handler
	@param True if the window was iconified, or false if it was restored*/
	virtual void onWindowIconify(bool iconified) {}

	/*A window maximize event handler, called only from the main thread
	@param True if the window was maximized, or false if it was restored*/
	virtual void onWindowMaximize(bool maximized) {}

	/*A window position event handler
	@param The new x-coordinate, in screen coordinates, of the upper-left corner of the content area of the window
	@param The new y-coordinate, in screen coordinates, of the upper-left corner of the content area of the window*/
	virtual void onWindowPos(int xpos, int ypos) {}

	/*A window content refresh event handler*/
	virtual void onWindowRefresh() {}

	/*A window size event handler
	@param The new width, in screen coordinates, of the window
	@param The new height, in screen coordinates, of the window*/
	virtual void onWindowSize(int width, int height) {}

	/*A window API transfer complete event handler*/
	virtual void onWindowTransfer() {}

public:
	/*(1) Constructs an empty window object*/
	Window()
	{
		memset(&_m, 0, sizeof(_MDATA));
	}

	/*(2) (M) Constructs window object with <createWindow>*/
	Window(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		_create(width, height, title, nullptr, setting);
	}

	/*(3) (M) Constructs window object with <createWindow>*/
	Window(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		_create(width, height, title, shared._window(), setting);
	}

	/*(4) (M) Construct window object with <createWindow>*/
	Window(_In_z_ const char* title, Monitor& monitor, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		_createFullscreen(title, monitor, nullptr, setting);
	}

	/*(5) (M) Construct window object with <createWindow>*/
	Window(_In_z_ const char* title, Monitor& monitor, Window& shared, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		_createFullscreen(title, monitor, shared._window(), setting);
	}

	/*Cleans up the valid window object*/
	~Window()
	{
		if (isWindow())
		{
			destroyWindow();
		}
	}

	/*(1) (M) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void createWindow(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr)
	{
		_create(width, height, title, nullptr, setting);
	}

	/*(2) (M) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void createWindow(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		_create(width, height, title, shared._window(), setting);
	}

	/*(3) (M) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor object to use for full screen mode
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void createWindow(_In_z_ const char* title, Monitor& monitor, _In_opt_ ContextSetting* setting = nullptr)
	{
		_createFullscreen(title, monitor, nullptr, setting);
	}

	/*(4) (M) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor oblect to use for full screen mode
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void createWindow(_In_z_ const char* title, Monitor& monitor, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		_createFullscreen(title, monitor, shared._window(), setting);
	}

	/*Clears window object, destroys the associated window and its context. When called from the secondary thread, performs the API transfer to the main thread*/
	void destroyWindow();

	/*This function brings the specified window to front and sets input focus. The window should already be visible and not iconified. When called from the secondary thread, performs the API transfer to the main thread*/
	void focusWindow();

	/*(M) Gets auto iconify attribute flag (default true). Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. Used as the getter of <autoIconify> property
	@return Auto iconify attribute flag*/
	bool getAutoIconify()
	{
		return (bool)_getWindowAttrib(GLFW_AUTO_ICONIFY);
	}

	/*Gets the Unicode code point of the character since last character event
	@return The Unicode code point of the character*/
	unsigned int getCharCodepoint() const
	{
		return _m.uCharCodepoint;
	}

	/*(M) Gets client API attribute value
	@return The client API attribute enumerator, default <OpenglApi>*/
	ClientApi getClientApi()
	{
		return (ClientApi)_getWindowAttrib(GLFW_CLIENT_API);
	}

	/*(M) This function returns the contents of the system clipboard, if it contains or is convertible to a UTF-8 encoded string. Used as the getter of <clipboardString> property
	@return The contents of the clipboard as a UTF-8 encoded string, or NULL*/
	_Ret_maybenull_z_ const char* getClipboardString();

	/*(M) Gets context creation API attribute value
	@return The context creation API attribute enumerator, default <NativeContextApi>*/
	ContextCreationApi getContextCreationApi()
	{
		return (ContextCreationApi)_getWindowAttrib(GLFW_CONTEXT_CREATION_API);
	}

	/*(M) Gets context no error attribute flag. Specifies whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior
	@return Context no error attribute flag, default false*/
	bool getContextNoError()
	{
		return (bool)_getWindowAttrib(GLFW_CONTEXT_NO_ERROR);
	}

	/*Gets context release behavior attribute value. When called from the secondary thread, performs the API transfer to the main thread
	@return The context release behavior attribute enumerator, default <AnyReleaseBehavior>*/
	ContextReleaseBehavior getContextReleaseBehavior()
	{
		return (ContextReleaseBehavior)_getWindowAttrib(GLFW_CONTEXT_RELEASE_BEHAVIOR);
	}

	/*(M) Gets context revision attribute value. Indicate the client API revision version of the window's context
	@return Context revision attribute value*/
	int getContextRevision()
	{
		return _getWindowAttrib(GLFW_CONTEXT_REVISION);
	}

	/*(M) Gets context robustness attribute value
	@return The context robustness attribute enumerator, default <NoRobustness>*/
	ContextRobustness getContextRobustness()
	{
		return (ContextRobustness)_getWindowAttrib(GLFW_CONTEXT_ROBUSTNESS);
	}

	/*Retreives the thread object on which the context of specified window has been made current
	@return The current context's thread object, or NULL*/
	_Ret_maybenull_ Thread* getContextThread() const
	{
		return _m.pThread;
	}

	/*(M) Gets context version major attribute value. Indicate the client API major version of the window's context
	@return Context version major attribute value, default 1*/
	int getContextVersionMajor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MAJOR);
	}

	/*(M) Gets context version minor attribute value. Indicate the client API minor version of the window's context
	@return Context version minor attribute value, default 0*/
	int getContextVersionMinor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MINOR);
	}

	/*Checks if the cursor is in window client area since last cursor enter event
	@return True if mouse cursor is over the window client area, false otherwise*/
	bool getCursorEntered() const
	{
		return _m.iCursorEntered == GLFW_TRUE;
	}

	/*(M) Gets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. Used as the getter of <cursorMode> property
	@return Cursor input mode enumerator, defult <CursorNormal>*/
	CursorMode getCursorMode()
	{
		return (CursorMode)_getInputMode(GLFW_CURSOR);
	}

	/*(M) This function gets the immediate position of the cursor, in screen coordinates, relative to the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getCursorPosX> and <getCursorPosY> calls*/
	void getCursorPos();

	/*Retrieves cursor x-position relative to window content area since last cursor position event, or <getCursorPos> call
	@return Cursor x-position value*/
	double getCursorPosX() const
	{
		return _m.dCursorPosX;
	}

	/*Retrieves cursor y-position relative to window content area since last cursor position event, or <getCursorPos> call
	@return Cursor y-position value*/
	double getCursorPosY() const
	{
		return _m.dCursorPosY;
	}

	/*(M) Gets decorated attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. Used as the getter of <decorated> property
	@return Decorated attribute flag, default true*/
	bool getDecorated()
	{
		return (bool)_getWindowAttrib(GLFW_DECORATED);
	}

	/*(M) Gets floating attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. Used as the getter of <floating> property
	@return Floating attribute flag, default false*/
	bool getFloating()
	{
		return (bool)_getWindowAttrib(GLFW_FLOATING);
	}

	/*(M) Gets focused attribute flag. Specifies whether the windowed mode window will be given input focus when created. This attribute is ignored for full screen and initially hidden windows
	@return Focused attribute flag, default true*/
	bool getFocused()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUSED);
	}

	/*(M) Gets focus on show attribute flag. Indicates whether the window will be given input focus when <showWindow> is called. Used as the getter of <focusOnShow> property
	@return Focus on show attribute flag, default true*/
	bool getFocusOnShow()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUS_ON_SHOW);
	}

	/*This function gets the immediate size, in pixels, of the framebuffer of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getFramebufferSizeWidth> and <getFramebufferSizeHeight> calls*/
	void getFramebufferSize();

	/*Retrieves window framebuffer height since last framebuffer size event, or <getFramebufferSize> call
	@return Framebuffer height value*/
	int getFramebufferHeight() const
	{
		return _m.iFramebufferHeight;
	}

	/*Retrieves window framebuffer width since last framebuffer size event, or <getFramebufferSize> call
	@return Framebuffer width value*/
	int getFramebufferWidth() const
	{
		return _m.iFramebufferWidth;
	}

	/*(M) Gets hovered attribute flag. Indicates whether the cursor is currently directly over the content area of the window, with no other windows between
	@return Hovered attribute flag*/
	bool getHovered()
	{
		return (bool)_getWindowAttrib(GLFW_HOVERED);
	}

	/*(M) Gets iconified attribute flag. Indicates whether the specified window is iconified
	@return Iconified attribute flag*/
	bool getIconified()
	{
		return (bool)_getWindowAttrib(GLFW_ICONIFIED);
	}

	/*(M) This function returns the last state reported for the specified key to the specified window
	@param The desired keyboard key enumerator value. <KeyUnknown> is not a valid key for this function
	@return The keyboard key action enumerator, except that its <Repeat> value is not returned*/
	KeyAction getKey(KeyboardKey key) const;

	/*Gets The keyboard key action since last key event
	@return The keyboard key action enumerator*/
	KeyAction getKeyAction() const
	{
		return (KeyAction)_m.iKeyAction;
	}

	/*Retrieves the keyboard key since last key event
	@return The keyboard key enumerator value*/
	KeyboardKey getKeyboardKey() const
	{
		return (KeyboardKey)_m.iKeyboardKey;
	}

	/*Gets The keyboard key scancode since last key event
	@return The keyboard key scancode*/
	int getKeyScancode() const
	{
		return _m.iKeyScancode;
	}

	/*(M) Gets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on. Used as the getter of <lockKeyMods> property
	@return Lock key mods input mode flag, default false*/
	bool getLockKeyMods()
	{
		return (bool)_getInputMode(GLFW_LOCK_KEY_MODS);
	}

	/*(M) Gets maximized attribute flag. Specifies whether the windowed mode window will be maximized when created. This attribute is ignored for full screen windows
	@return Maximized attribute flag, default false*/
	bool getMaximized()
	{
		return (bool)_getWindowAttrib(GLFW_MAXIMIZED);
	}

	/*Gets the mouse action since last mouse event
	@return The mouse action enumerator value*/
	MouseAction getMouseAction() const
	{
		return (MouseAction)_m.iMouseAction;
	}

	/*(1) Gets mouse button since last mouse event
	@return The mouse button enumerator value*/
	MouseButton getMouseButton() const
	{
		return (MouseButton)_m.iMouseButton;
	}

	/*(M) (2) This function returns the last state reported for the specified mouse button to the specified window
	@param The requested mouse button enumerator
	@return True if the requested mouse button is pressed, false otherwise*/
	MouseAction getMouseButton(MouseButton button);

	/*(M) Gets OpenGL debug context attribute flag. Specifies whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality
	@return OpenGL debug context attribute flag, default false*/
	bool getOpenglDebugContext()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_DEBUG_CONTEXT);
	}

	/*(M) Gets OpenGL forward compatible attribute flag. Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored
	@return OpenGL forward compatible attribute flag, default false*/
	bool getOpenglForwardCompat()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_FORWARD_COMPAT);
	}

	/*(M) Gets OpenGL profile attribute value
	@return The OpenGL profile attribute enumerator, <default OpenglAnyProfile>*/
	OpenglProfile getOpenglProfile()
	{
		return (OpenglProfile)_getWindowAttrib(GLFW_OPENGL_PROFILE);
	}

	/*Get scroll offset along the x-axis since last scroll event
	@param The scroll offset along the x-axis*/
	double getScrollOffsetX() const
	{
		return _m.dScrollOffsetX;
	}

	/*Get scroll offset along the y-axis since last scroll event
	@param The scroll offset along the y-axis*/
	double getScrollOffsetY() const
	{
		return _m.dScrollOffsetY;
	}

	/*(M) Gets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. Used as the getter of <rawMouseMotion> property
	@return Raw mouse motion input mode flag, default false*/
	bool getRawMouseMotion()
	{
		return (bool)_getInputMode(GLFW_RAW_MOUSE_MOTION);
	}

	/*(M) Gets resizable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This attribute is ignored for full screen and undecorated windows. Used as the getter of <resizable> property
	@return Resizable attribute flag, default true*/
	bool getResizable()
	{
		return (bool)_getWindowAttrib(GLFW_RESIZABLE);
	}

	/*(M) Gets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. Used as the getter of <stickyKeys> property
	@return Sticky keys input mode flag, default false*/
	bool getStickyKeys()
	{
		return (bool)_getInputMode(GLFW_STICKY_KEYS);
	}

	/*(M) Gets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. Used as the getter of <stickyMouseButtons> property
	@return Sticky mouse buttons input mode flag, default false*/
	bool getStickyMouseButtons()
	{
		return (bool)_getInputMode(GLFW_STICKY_MOUSE_BUTTONS);
	}

	/*(M) Gets transparent framebuffer attribute flag. Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel
	@return Transparent framebuffer attribute flag, default false*/
	bool getTransparentFramebuffer()
	{
		return (bool)_getWindowAttrib(GLFW_TRANSPARENT_FRAMEBUFFER);
	}

	/*(M) Gets visible attribute flag. Specifies whether the windowed mode window will be initially visible. This attribute is ignored for full screen windows
	@return Visible attribute flag, default true*/
	bool getVisible()
	{
		return (bool)_getWindowAttrib(GLFW_VISIBLE);
	}

	/*(M) This function gets the immediate content scale of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowContentScaleX> and <getWindowContentScaleY> calls*/
	void getWindowContentScale();

	/*Retrieves window content x-scale since last window content scale event, or <getWindowContentScale> call
	@return Window content x-scale*/
	float getWindowContentScaleX() const
	{
		return _m.fWindowContentScaleX;
	}

	/*Retrieves window content y-scale since last window content scale event, or <getWindowContentScale> call
	@return Window content y-scale*/
	float getWindowContentScaleY() const
	{
		return _m.fWindowContentScaleY;
	}

	/*(M) This function gets the immediate size, in screen coordinates, of each edge of the frame of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowFrameBottom>, <getWindowFrameLeft>, <getWindowFrameRight> and <getWindowFrameTop> calls*/
	void getWindowFrameSize();

	/*Retrieves window left edge of the frame since last <getWindowFrameSize> call
	@return Window frame left edge*/
	int getWindowFrameLeft() const
	{
		return _m.iWindowFrameLeft;
	}

	/*Retrieves window top edge of the frame since last <getWindowContentScale> call
	@return Window frame top edge*/
	int getWindowFrameTop() const
	{
		return _m.iWindowFrameTop;
	}

	/*Retrieves window right edge of the frame since last <getWindowFrameSize> call
	@return Window frame right edge*/
	int getWindowFrameRight() const
	{
		return _m.iWindowFrameRight;
	}

	/*Retrieves window bottom edge of the frame since last <getWindowFrameSize> call
	@return Window frame bottom edge*/
	int getWindowFrameBottom() const
	{
		return _m.iWindowFrameBottom;
	}

	/*(M) This function retrieves the monitor object that the specified window is in full screen on
	@param [out] The empty monitor object used in full screen mode*/
	void getWindowMonitor(Monitor& monitor);

	/*(M) This function returns the opacity of the window, including any decorations
	@return The opacity of the specified window*/
	float getWindowOpacity();

	/*(M) This function gets the immediate position, in screen coordinates, of the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowPosX> and <getWindowPosY> calls. Should not be used in fullscreen mode*/
	void getWindowPos();

	/*Retrieves window x-position of window content area since last window position event, or <getWindowPos> call
	@return Window x-position*/
	int getWindowPosX() const
	{
		return _m.iWindowPosX;
	}

	/*Retrieves window y-position of window content area since last window position event, or <getWindowPos> call
	@return Window y-position*/
	int getWindowPosY() const
	{
		return _m.iWindowPosY;
	}

	/*(M) This function gets the immediate size, in screen coordinates, of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowSizeHeight> and <getWindowSizeWidth> calls. Should not be used in fullscreen mode*/
	void getWindowSize();

	/*Retrieves width of window content area since last window size event, or <getWindowSize> call
	@return The window width value*/
	int getWindowWidth() const
	{
		return _m.iWindowWidth;
	}

	/*Retrieves height of window content area since last window size event, or <getWindowSize> call
	@return The window height value*/
	int getWindowHeight() const
	{
		return _m.iWindowHeight;
	}

	/*This function hides the specified window if it was previously visible. When called from the secondary thread, performs the API transfer to the main thread*/
	void hideWindow();

	/*This function iconifies/minimizes the specified window, if it was previously restored. When called from the secondary thread, performs the API transfer to the main thread*/
	void iconifyWindow();

	/*Checks if context of the specified window has been made current on any thread
	@return True if context current, false otherwise*/
	bool isContextCurrent() const
	{
		return _m.pThread != nullptr;
	}

	/*Checks the state of specified key modifier since last key or mouse event
	@param The desired key modifier enumerator
	@return True if specified key modifier was pressed since last key or mouse event, false otherwise*/
	bool isKeyModifier(KeyModifier mod) const
	{
		return (bool)(_m.iKeyMods & (int)mod);
	}

	/*Checks if window receives focus since last window focus event
	@return True if window is focused, false otherwise*/
	bool isWindowFocused() const
	{
		return (bool)_m.iWindowFocused;
	}

	/*Checks if window in fullscreen state since the creation or last monitor operation
	@return True if window in fullscreen mode, false otherwise*/
	bool isWindowFullscreen() const
	{
		return (bool)_m.iWindowFullscreen;
	}

	/*Checks if window is iconified since last window iconify event
	@return True if window is iconified, false otherwise*/
	bool isWindowIconified() const
	{
		return (bool)_m.iWindowIconified;
	}

	/*Checks if window is visible since the creation or last show/hide operation
	@return True if window in fullscreen mode, false otherwise*/
	bool isWindowVisible() const
	{
		return (bool)_m.iWindowVisible;
	}

	/*Checks if window is maximized since last window maximize event
	@return True if window maximized since last maximize event, false otherwise*/
	bool isWindowMaximized() const
	{
		return (bool)_m.iWindowMaximized;
	}

	/*Check if valid window object
	@return True if window object, false otherwise*/
	bool isWindow() const
	{
		return _m.pWindow != nullptr;
	}

	/*This function makes the OpenGL or OpenGL ES context of the specified window current on the main thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. Associates the window with the calling thread, at the first call initializes OpenGL*/
	void makeContextCurrent();

	/*This function makes the OpenGL or OpenGL ES context non-current on the calling thread. Detaches the current context from the calling thread without making a new one current*/
	void makeContextNonCurrent();

	/*This function maximizes the specified window if it was previously not maximized. When called from the secondary thread, performs the API transfer to the main thread*/
	void maximizeWindow();

	/*This function requests user attention to the specified window. On platforms where this is not supported, attention is requested to the application as a whole. When called from the secondary thread, performs the API transfer to the main thread*/
	void requestWindowAttention();

	/*This function restores the specified window, if it was previously iconified/minimized or maximized. When called from the secondary thread, performs the API transfer to the main thread*/
	void restoreWindow();

	/*(M) Sets auto iconify writable attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. Used as the setter of <autoIconify> property
	@param New auto iconify attribute flag, default true*/
	void setAutoIconify(bool flag)
	{
		_setWindowAttrib(GLFW_AUTO_ICONIFY, (int)flag);
	}

	/*This function sets the system clipboard to the specified, UTF-8 encoded string. When called from the secondary thread, performs the API transfer to the main thread. Used as the setter of <clipboardString> property
	@param A UTF-8 encoded string*/
	void setClipboardString(_In_z_ const char* string);

	/*(M) This function sets the cursor image to be used when the cursor is over the content area of the specified window
	@param [in] The cursor object to set*/
	void setCursor(Cursor& cursor);

	/*(M) Sets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. Used as the setter of <cursorMode> property
	@param New cursor input mode enumerator, <defult CursorNormal>*/
	void setCursorMode(CursorMode cursorMode)
	{
		_setInputMode(GLFW_CURSOR, (int)cursorMode);
	}

	/*This function sets the position, in screen coordinates, of the cursor relative to the upper-left corner of the client area of the specified window. When called from the secondary thread, performs the API transfer to the main thread
	@param The desired x-coordinate, relative to the left edge of the client area
	@param The desired y-coordinate, relative to the top edge of the client area*/
	void setCursorPos(double xpos, double ypos);

	/*(M) Gets decorated writable attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. Used as the setter of <decorated> property
	@param New decorated attribute flag, default true*/
	void setDecorated(bool flag)
	{
		_setWindowAttrib(GLFW_DECORATED, (int)flag);
	}

	/*(M) Sets floating writable attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. Used as the setter of <floating> property
	@param New floating attribute flag, default false*/
	void setFloating(bool flag)
	{
		_setWindowAttrib(GLFW_FLOATING, (int)flag);
	}

	/*(M) Sets focus on show writable attribute flag. Specifies whether the window will be given input focus when <showWindow> is called. Used as the setter of <focusOnShow> property
	@param New focus on show attribute flag, default true*/
	void setFocusOnShow(bool flag)
	{
		_setWindowAttrib(GLFW_FOCUS_ON_SHOW, (int)flag);
	}

	/*(M) Sets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on. Used as the setter of <lockKeyMods> property
	@param New lock key mods input mode flag, default false*/
	void setLockKeyMods(bool flag)
	{
		_setInputMode(GLFW_LOCK_KEY_MODS, (int)flag);
	}

	/*(M) Sets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. Used as the setter of <rawMouseMotion> property
	@param New raw mouse motion input mode flag, default false*/
	void setRawMouseMotion(bool flag)
	{
		_setInputMode(GLFW_RAW_MOUSE_MOTION, (int)flag);
	}

	/*(M) Sets resizable writable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <setWindowSize> function. This attribute is ignored for full screen and undecorated windows. Used as the setter of <resizable> property
	@param New resizable attribute flag, default true*/
	void setResizable(bool flag)
	{
		_setWindowAttrib(GLFW_RESIZABLE, flag);
	}

	/*(M) Sets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. Used as the setter of <stickyKeys> property
	@param New sticky keys input mode flag, default false*/
	void setStickyKeys(bool bFlag)
	{
		_setInputMode(GLFW_STICKY_KEYS, (int)bFlag);
	}

	/*(M) Sets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. Used as the setter of <stickyMouseButtons> property
	@param New sticky mouse buttons input mode flag, default false*/
	void setStickyMouseButtons(bool flag)
	{
		_setInputMode(GLFW_STICKY_MOUSE_BUTTONS, (int)flag);
	}

	/*This function sets the required aspect ratio of the content area of the specified window. When called from the secondary thread, performs the API transfer to the main thread
	@param The numerator of the desired aspect ratio
	@param The denominator of the desired aspect ratio*/
	void setWindowAspectRatio(int numer, int denom);

	/*(M) This function sets the icon of the specified window with an array of candidate images, from which the system selects the closest to the desired sizes
	@param The number of images in the specified array
	@param [in] The array of images to create the icon from*/
	void setWindowIcon(int count, _In_reads_(count) const GLFWimage* images);

	/*(M) (STB) Set icon of specified window from image object. Does nothing if empty object
	@param [in] Stb image object*/
	void setWindowIcon(StbImage& stbImage);

#ifndef YAGLPP_NO_FREEIMAGE
	/*(M) (FI) Set icon of specified window from free image object. Does nothing if empty object
	@param [in] Free image object*/
	void setWindowIcon(FreeImage& freeImage);

	/*(M) (FI) Set icon of specified window from binary resource. Does nothing if invalid resource
	@param The icon resource id of <RCDATA> type*/
	void setWindowIcon(int rcid);

	/*(M) (FI) Set icon of specified window from the icon file. Does nothing if invalid file
	@param [in] Path to the icon file*/
	void setWindowIcon(_In_z_ const char* filepath);
#endif // #ifndef YAGLPP_NO_FREEIMAGE

	/*(1) This function sets the primary monitor that the window uses for full screen mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void setWindowMonitor();

	/*(M) (2) This function sets the monitor that the window uses for full screen mode. It also sets selected video mode parameters via window hints
	@param Monitor object with selected monitor and video mode*/
	void setWindowMonitor(Monitor& monitor);

	/*This function sets the opacity of the window, including any decorations. When called from the secondary thread, performs the API transfer to the main thread
	@param The desired opacity of the specified window*/
	void setWindowOpacity(float opacity);

	/*This function sets the position, in screen coordinates, of the upper-left corner of the content area of the specified windowed mode window. When called from the secondary thread, performs the API transfer to the main thread. Should not be used in fullscreen mode
	@param The x-coordinate of the upper-left corner of the content area
	@param The y-coordinate of the upper-left corner of the content area*/
	void setWindowPos(int xpos, int ypos);

	/*This function sets the value of the close flag of the specified window
	@param The new window close flag*/
	void setWindowShouldClose(bool close)
	{
		glfwSetWindowShouldClose(_window(), (int)close);
	}

	/*This function sets the size, in screen coordinates, of the content area of the specified window. When called from the secondary thread, performs the API transfer to the main thread. Should not be used in fullscreen mode
	@param The desired width, in screen coordinates, of the window content area
	@param The desired height, in screen coordinates, of the window content area*/
	void setWindowSize(int width, int height);

	/*This function sets the size limits of the content area of the specified window. If the window is full screen, the size limits only take effect once it is made windowed. To specify only a minimum size or only a maximum one, set the other pair to GLFW_DONT_CARE. When called from the secondary thread, performs the API transfer to the main thread
	@param The minimum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The minimum height, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum height, in screen coordinates, of the content area, or GLFW_DONT_CARE*/
	void setWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight);

	/*This function sets the window title, encoded as UTF-8, of the specified window. When called from the secondary thread, performs the API transfer to the main thread
	@param [in] The UTF-8 encoded window title*/
	void setWindowTitle(_In_z_ const char* title);

	/*This function makes the specified window visible if it was previously hidden. When called from the secondary thread, performs the API transfer to the main thread*/
	void showWindow();

	/*This function swaps the front and back buffers of the specified window. If the swap interval is greater than zero, the GPU driver waits the specified number of screen updates before swapping the buffers. This function may be called from secondary threads*/
	void swapBuffers()
	{
		glfwSwapBuffers(_window());
	}

	/*Checks dispatched inter-thread message of the calling thread, and calls window event handler for a specific window message
	@param [in] Points to the message structure containing the message data
	@return True if the specific message found, false otherwise*/
	static bool translateMessage(_In_ Message* msg);

	/*Switch back to the default arrow cursor. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetCursor();

	/*This function disables the aspect ratio limit. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowAspectRatio();

	/*This function reverts the window to its default icon. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowIcon();

	/*This function unsets the monitor that the window uses for full screen mode, setting it into windowed mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowMonitor();

	/*This function returns the value of the close flag of the specified window
	@return The window close flag*/
	bool windowShouldClose();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) Read-write property for auto iconify window attribute flag*/
	__declspec(property(get = getAutoIconify, put = setAutoIconify)) bool autoIconify;

	/*(M) Read-write property for window's system clipboard string. Could be set via API transfer*/
	__declspec(property(get = getClipboardString, put = setClipboardString)) const char* clipboardString;

	/*(M) Read-write property for cursor input mode flag*/
	__declspec(property(get = getCursorMode, put = setCursorMode)) CursorMode cursorMode;

	/*(M) Read-write property for decorated window attribute flag*/
	__declspec(property(get = getDecorated, put = setDecorated)) bool decorated;

	/*(M) Read-write property for floating window attribute flag*/
	__declspec(property(get = getFloating, put = setFloating)) bool floating;

	/*(M) Read-write property for focus on show window attribute flag*/
	__declspec(property(get = getFocusOnShow, put = setFocusOnShow)) bool focusOnShow;

	/*(M) Read-write property for lock key mods input mode flag*/
	__declspec(property(get = getLockKeyMods, put = setLockKeyMods)) bool lockKeyMods;

	/*(M) Read-write property for raw mouse motion input mode flag*/
	__declspec(property(get = getRawMouseMotion, put = setRawMouseMotion)) bool rawMouseMotion;

	/*(M) Read-write property for resizable window attribute flag*/
	__declspec(property(get = getResizable, put = setResizable)) bool resizable;

	/*(M) Read-write property for window sticky keys input mode flag*/
	__declspec(property(get = getStickyKeys, put = setStickyKeys)) bool stickyKeys;

	/*(M) Read-write property for window sticky mouse buttons input mode flag*/
	__declspec(property(get = getStickyMouseButtons, put = setStickyMouseButtons)) bool stickyMouseButtons;

	/*(M) Read-write property for window opacity value. Could be set via API transfer*/
	__declspec(property(get = getWindowOpacity, put = setWindowOpacity)) float windowOpacity;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*(M) (3.4) Gets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. Used as the getter of <mousePassthrough> property
	@return Mouse passthrough attribute flag, default false*/
	bool getMousePassthrough()
	{
		return (bool)_getWindowAttrib(GLFW_MOUSE_PASSTHROUGH);
	}

	/*(M) (3.4) This function returns the window title, encoded as UTF-8, of the specified window, previously set by <createWindow> or <setWindowTitle>
	@return The UTF-8 encoded window title*/
	_Ret_maybenull_z_ const char* getWindowTitle() const;

	/*(M) (3.4) Sets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. Used as the setter of <mousePassthrough> property
	@param New mouse passthrough attribute flag, default false*/
	void setMousePassthrough(bool flag)
	{
		_setWindowAttrib(GLFW_MOUSE_PASSTHROUGH, (int)flag);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) (3.4) Read-write property for mouse passthrough window attribute flag*/
	__declspec(property(get = getMousePassthrough, put = setMousePassthrough)) bool mousePassthrough;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
}; // class Window

/*Checks dispatched inter-thread message of the calling thread, and performs an action for a specific message
@param [in] Points to the message structure containing the message data
@return True if the specific message found, false otherwise*/
inline bool translateMessage(_In_ Message* msg)
{
	return Window::translateMessage(msg);
}
} // namespace glfw

#include "Cursor.h"
namespace glfw {
#ifndef _DEBUG
inline int Window::_getInputMode(int mode)
{
	return glfwGetInputMode(_m.pWindow, mode);
}

inline int Window::_getWindowAttrib(int attrib)
{
	return glfwGetWindowAttrib(_m.pWindow, attrib);
}

inline void Window::_setInputMode(int mode, int value)
{
	glfwSetInputMode(_m.pWindow, mode, value);
}

inline void Window::_setWindowAttrib(int attrib, int value)
{
	glfwSetWindowAttrib(_m.pWindow, attrib, value);
}

inline GLFWwindow* Window::_window() const
{
	return _m.pWindow;
}

inline _Ret_maybenull_z_ const char* Window::getClipboardString()
{
	return glfwGetClipboardString(_m.pWindow);
}

inline void Window::getCursorPos()
{
	glfwGetCursorPos(_m.pWindow, &_m.dCursorPosX, &_m.dCursorPosY);
}

inline void Window::getFramebufferSize()
{
	glfwGetFramebufferSize(_m.pWindow, &_m.iFramebufferWidth, &_m.iFramebufferHeight);
}

inline KeyAction Window::getKey(KeyboardKey key) const
{
	return (KeyAction)glfwGetKey(_m.pWindow, (int)key);
}

inline MouseAction Window::getMouseButton(MouseButton button)
{
	return (MouseAction)glfwGetMouseButton(_m.pWindow, (int)button);
}

inline void Window::getWindowFrameSize()
{
	glfwGetWindowFrameSize(_m.pWindow, &_m.iWindowFrameLeft, &_m.iWindowFrameTop, &_m.iWindowFrameRight, &_m.iWindowFrameBottom);
}

inline void Window::getWindowContentScale()
{
	glfwGetWindowContentScale(_m.pWindow, &_m.fWindowContentScaleX, &_m.fWindowContentScaleY);
}

inline float Window::getWindowOpacity()
{
	return glfwGetWindowOpacity(_m.pWindow);
}

inline void Window::getWindowPos()
{
	glfwGetWindowPos(_window(), &_m.iWindowPosX, &_m.iWindowPosY);
}

inline void Window::getWindowSize()
{
	glfwGetWindowSize(_window(), &_m.iWindowWidth, &_m.iWindowHeight);
}

inline void Window::setCursor(Cursor& cursor)
{
	glfwSetCursor(_m.pWindow, cursor._mpCursor);
}

inline void Window::setWindowIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	glfwSetWindowIcon(_m.pWindow, count, images);
}

#ifdef YAGLPP_NO_GLFW_LEGACY
inline _Ret_maybenull_z_ const char* Window::getWindowTitle() const
{
	return glfwGetWindowTitle(_m.pWindow);
}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
#endif // #ifdef _DEBUG
} // namespace glfw
