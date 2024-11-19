#pragma once
#include <yaglpp/glfw3pp.h>
#define YAGLPP_DESTROY_WINDOW				-100
#define YAGLPP_FOCUS_WINDOW					-110
#define YAGLPP_GET_CLIPBOARD_STRING			-120
#define YAGLPP_GET_CURSOR_POS				-130
#define YAGLPP_GET_FRAMEBUFFER_SIZE			-140
#define YAGLPP_GET_INPUT_MODE				-150
#define YAGLPP_GET_WINDOW_ATTRIB			-160
#define YAGLPP_GET_WINDOW_CONTENT_SCALE		-170
#define YAGLPP_GET_WINDOW_FRAME_SIZE		-180
#define YAGLPP_GET_WINDOW_OPACITY			-190
#define YAGLPP_GET_WINDOW_POS				-200
#define YAGLPP_GET_WINDOW_SIZE				-210
#define YAGLPP_HIDE_WINDOW					-220
#define YAGLPP_ICONIFY_WINDOW				-230
#define YAGLPP_MAXIMIZE_WINDOW				-240
#define YAGLPP_REQUEST_WINDOW_ATTENTION		-250
#define YAGLPP_RESTORE_WINDOW				-260
#define YAGLPP_SET_CLIPBOARD_STRING			-270
#define YAGLPP_SET_CURSOR_POS				-280
#define YAGLPP_SET_INPUT_MODE				-290
#define YAGLPP_SET_WINDOW_ASPECT_RATIO		-300
#define YAGLPP_SET_WINDOW_ATTRIB			-310
#define YAGLPP_SET_WINDOW_MONITOR			-320
#define YAGLPP_SET_WINDOW_OPACITY			-330
#define YAGLPP_SET_WINDOW_POS				-340
#define YAGLPP_SET_WINDOW_SIZE				-350
#define YAGLPP_SET_WINDOW_SIZE_LIMITS		-360
#define YAGLPP_SET_WINDOW_TITLE				-370
#define YAGLPP_SHOW_WINDOW					-380
#define YAGLPP_UNSET_CURSOR					-390
#define YAGLPP_UNSET_WINDOW_ASPECT_RATIO	-400
#define YAGLPP_UNSET_WINDOW_ICON			-410
#define YAGLPP_UNSET_WINDOW_MONITOR			-420
#ifdef YAGLPP_NO_GLFW_LEGACY
#define YAGLPP_GET_WINDOW_TITLE				-430
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
extern bool loadGL(void*);
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
	/*No modifier key were held down*/
	None = 0,

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

/*This function returns the pointer to window object whose OpenGL or OpenGL ES context is current on the calling thread
@return The pointer to current context window object, or NULL*/
inline _Ret_maybenull_ Window* getCurrentContext()
{
	//Thread* pThread = Thread::getCurrentThread();
	//return (pThread->isContextCurrent()) ? pThread->getContext() : nullptr;
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
		Thread* pThread; // Context thread
		GLFWwindow* pWindow; // GLFW window object
		const GLFWvidmode* pVidmode; // Window fullscreen state flag
		int iBlockTransfer; // Block api and callback window transfer feature
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
		int iWindowVisible; // Window visible state flag
	} _m;

#ifdef YAGLPP_NO_AFX_LAYOUT
	static Thread noAfxMainThread;
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT

	bool _apiCallback(int msgid, Param x, Param y, Param z, Param w);
	bool _apiTransfer(int msgid, Param x, Param y, Param z, Param w);
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
	virtual void onWindowTransfer(const Message* msg) {}

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

	/*Gets auto iconify window attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <autoIconify> property
	@return Auto iconify attribute flag (default true)*/
	bool getAutoIconify()
	{
		return (bool)_getWindowAttrib(GLFW_AUTO_ICONIFY);
	}

	/*Gets the Unicode code point of the character since last character event. Used as a getter of <charCodepoint> property
	@return The Unicode code point of the character*/
	unsigned int getCharCodepoint() const
	{
		return _m.uCharCodepoint;
	}

	/*Gets client API window attribute value. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <clientApi> property
	@return The client API window attribute enumerator, default <OpenglApi>*/
	ClientApi getClientApi()
	{
		return (ClientApi)_getWindowAttrib(GLFW_CLIENT_API);
	}
	
	/*This function returns the contents of the system clipboard, if it contains or is convertible to a UTF-8 encoded string. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <clipboardString> property
	@return The contents of the clipboard as a UTF-8 encoded string, or NULL*/
	_Ret_maybenull_z_ const char* getClipboardString();

	/*Gets context creation API window attribute value. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextCreationApi> property
	@return The context creation API window attribute enumerator, default <NativeContextApi>*/
	ContextCreationApi getContextCreationApi()
	{
		return (ContextCreationApi)_getWindowAttrib(GLFW_CONTEXT_CREATION_API);
	}

	/*Gets context no error window attribute flag. Specifies whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextNoError> property
	@return Context no error window attribute flag, default false*/
	bool getContextNoError()
	{
		return (bool)_getWindowAttrib(GLFW_CONTEXT_NO_ERROR);
	}

	/*Gets context release behavior window attribute value. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextReleaseBehavior> property
	@return The context release behavior window attribute enumerator, default <AnyReleaseBehavior>*/
	ContextReleaseBehavior getContextReleaseBehavior()
	{
		return (ContextReleaseBehavior)_getWindowAttrib(GLFW_CONTEXT_RELEASE_BEHAVIOR);
	}

	/*Gets context revision window attribute value. Indicate the client API revision version of the window's context. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextRevision> property
	@return Context revision window attribute value*/
	int getContextRevision()
	{
		return _getWindowAttrib(GLFW_CONTEXT_REVISION);
	}

	/*Gets context robustness window attribute value. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextRobustness> property
	@return The context robustness window attribute enumerator, default <NoRobustness>*/
	ContextRobustness getContextRobustness()
	{
		return (ContextRobustness)_getWindowAttrib(GLFW_CONTEXT_ROBUSTNESS);
	}

	/*Retreives the thread object on which the context of specified window has been made current. Used as a getter of <contextThread> property
	@return The current context's thread object, or NULL*/
	_Ret_maybenull_ Thread* getContextThread() const
	{
		return _m.pThread;
	}

	/*Gets context version major window attribute value. Indicate the client API major version of the window's context. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextVersionMajor> property
	@return Context version major window attribute value, default 1*/
	int getContextVersionMajor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MAJOR);
	}

	/*Gets context version minor window attribute value. Indicate the client API minor version of the window's context. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <contextVersionMinor> property
	@return Context version minor window attribute value, default 0*/
	int getContextVersionMinor()
	{
		return _getWindowAttrib(GLFW_CONTEXT_VERSION_MINOR);
	}

	/*Checks if the cursor is in window client area since last cursor enter event. Used as a getter of <cursorEntered> property
	@return True if mouse cursor is over the window client area, false otherwise*/
	bool getCursorEntered() const
	{
		return (bool)_m.iCursorEntered;
	}

	/*Gets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <cursorMode> property
	@return Cursor input mode enumerator, defult <CursorNormal>*/
	CursorMode getCursorMode()
	{
		return (CursorMode)_getInputMode(GLFW_CURSOR);
	}

	/*This function gets the immediate position of the cursor, in screen coordinates, relative to the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getCursorPosX> and <getCursorPosY> calls. When called from the secondary thread, performs the API transfer to the main thread*/
	void getCursorPos();

	/*Retrieves cursor x-position relative to window content area since last cursor position event, or <getCursorPos> call. Used as a getter of <cursorPosX> property
	@return Cursor x-position value*/
	double getCursorPosX() const
	{
		return _m.dCursorPosX;
	}

	/*Retrieves cursor y-position relative to window content area since last cursor position event, or <getCursorPos> call. Used as a getter of <cursorPosY> property
	@return Cursor y-position value*/
	double getCursorPosY() const
	{
		return _m.dCursorPosY;
	}

	/*Gets decorated window attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <decorated> property
	@return Decorated attribute flag, default true*/
	bool getDecorated()
	{
		return (bool)_getWindowAttrib(GLFW_DECORATED);
	}

	/*Gets floating window attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <floating> property
	@return Floating attribute flag, default false*/
	bool getFloating()
	{
		return (bool)_getWindowAttrib(GLFW_FLOATING);
	}

	/*Gets focused window attribute flag. Specifies whether the windowed mode window will be given input focus when created. This attribute is ignored for full screen and initially hidden windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <focused> property
	@return Focused window attribute flag, default true*/
	bool getFocused()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUSED);
	}

	/*Gets focus on show window attribute flag. Indicates whether the window will be given input focus when <showWindow> is called. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <focusOnShow> property
	@return Focus on show attribute flag, default true*/
	bool getFocusOnShow()
	{
		return (bool)_getWindowAttrib(GLFW_FOCUS_ON_SHOW);
	}

	/*This function gets the immediate size, in pixels, of the framebuffer of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getFramebufferSizeWidth> and <getFramebufferSizeHeight> calls. When called from the secondary thread, performs the API transfer to the main thread*/
	void getFramebufferSize();

	/*Retrieves window framebuffer width since last framebuffer size event, or <getFramebufferSize> call. Used as a getter of <framebufferWidth> property
	@return Framebuffer width value*/
	int getFramebufferWidth() const
	{
		return _m.iFramebufferWidth;
	}

	/*Retrieves window framebuffer height since last framebuffer size event, or <getFramebufferSize> call. Used as a getter of <framebufferHeight> property
	@return Framebuffer height value*/
	int getFramebufferHeight() const
	{
		return _m.iFramebufferHeight;
	}

	/*Gets hovered window attribute flag. Indicates whether the cursor is currently directly over the content area of the window, with no other windows between. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <hovered> property
	@return Hovered window attribute flag*/
	bool getHovered()
	{
		return (bool)_getWindowAttrib(GLFW_HOVERED);
	}

	/*Gets iconified window attribute flag. Indicates whether the specified window is iconified. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <iconified> property
	@return Iconified window attribute flag*/
	bool getIconified()
	{
		return (bool)_getWindowAttrib(GLFW_ICONIFIED);
	}

	/*(M) This function returns the last state reported for the specified key to the specified window
	@param The desired keyboard key enumerator value. <KeyUnknown> is not a valid key for this function
	@return The keyboard key action enumerator, except that its <Repeat> value is not returned*/
	KeyAction getKey(KeyboardKey key) const;

	/*Gets The keyboard key action since last key event. Used as a getter of <keyAction> property
	@return The keyboard key action enumerator*/
	KeyAction getKeyAction() const
	{
		return (KeyAction)_m.iKeyAction;
	}

	/*Retrieves the keyboard key since last key event. Used as a getter of <keyboardKey> property
	@return The keyboard key enumerator value*/
	KeyboardKey getKeyboardKey() const
	{
		return (KeyboardKey)_m.iKeyboardKey;
	}

	/*Gets The keyboard key scancode since last key event. Used as a getter of <keyScancode> property
	@return The keyboard key scancode*/
	int getKeyScancode() const
	{
		return _m.iKeyScancode;
	}

	/*Gets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <lockKeyMods> property
	@return Lock key mods input mode flag, default false*/
	bool getLockKeyMods()
	{
		return (bool)_getInputMode(GLFW_LOCK_KEY_MODS);
	}

	/*Gets maximized window attribute flag. Specifies whether the windowed mode window will be maximized when created. This attribute is ignored for full screen windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <maximized> property
	@return Maximized window attribute flag, default false*/
	bool getMaximized()
	{
		return (bool)_getWindowAttrib(GLFW_MAXIMIZED);
	}

	/*Gets the mouse action since last mouse event. Used as a getter of <mouseAction> property
	@return The mouse action enumerator value*/
	MouseAction getMouseAction() const
	{
		return (MouseAction)_m.iMouseAction;
	}

	/*(1) Gets mouse button since last mouse event. Used as a getter of <mouseButton> property
	@return The mouse button enumerator value*/
	MouseButton getMouseButton() const
	{
		return (MouseButton)_m.iMouseButton;
	}

	/*(M) (2) This function returns the last state reported for the specified mouse button to the specified window
	@param The requested mouse button enumerator
	@return True if the requested mouse button is pressed, false otherwise*/
	MouseAction getMouseButton(MouseButton button);

	/*Gets the OpenGL debug context window attribute flag. Specifies whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <openglDebugContext> property
	@return OpenGL debug context window attribute flag, default false*/
	bool getOpenglDebugContext()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_DEBUG_CONTEXT);
	}

	/*Gets the OpenGL forward compatible window attribute flag. Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <openglForwardCompat> property
	@return OpenGL forward compatible window attribute flag, default false*/
	bool getOpenglForwardCompat()
	{
		return (bool)_getWindowAttrib(GLFW_OPENGL_FORWARD_COMPAT);
	}

	/*Gets the OpenGL profile window attribute value. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <openglProfile> property
	@return The OpenGL profile window attribute enumerator, <default OpenglAnyProfile>*/
	OpenglProfile getOpenglProfile()
	{
		return (OpenglProfile)_getWindowAttrib(GLFW_OPENGL_PROFILE);
	}

	/*Get the scroll offset along the x-axis since last scroll event. Used as a getter of <scrollOffsetX> property
	@param The scroll offset along the x-axis*/
	double getScrollOffsetX() const
	{
		return _m.dScrollOffsetX;
	}

	/*Get the scroll offset along the y-axis since last scroll event. Used as a getter of <scrollOffsetY> property
	@param The scroll offset along the y-axis*/
	double getScrollOffsetY() const
	{
		return _m.dScrollOffsetY;
	}

	/*Gets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <rawMouseMotion> property
	@return Raw mouse motion input mode flag, default false*/
	bool getRawMouseMotion()
	{
		return (bool)_getInputMode(GLFW_RAW_MOUSE_MOTION);
	}

	/*Gets resizable window attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This attribute is ignored for full screen and undecorated windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <resizable> property
	@return Resizable attribute flag, default true*/
	bool getResizable()
	{
		return (bool)_getWindowAttrib(GLFW_RESIZABLE);
	}

	/*Gets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <stickyKeys> property
	@return Sticky keys input mode flag, default false*/
	bool getStickyKeys()
	{
		return (bool)_getInputMode(GLFW_STICKY_KEYS);
	}

	/*Gets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <stickyMouseButtons> property
	@return Sticky mouse buttons input mode flag, default false*/
	bool getStickyMouseButtons()
	{
		return (bool)_getInputMode(GLFW_STICKY_MOUSE_BUTTONS);
	}

	/*Gets the transparent framebuffer window attribute flag. Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <transparentFramebuffer> property
	@return Transparent framebuffer window attribute flag, default false*/
	bool getTransparentFramebuffer()
	{
		return (bool)_getWindowAttrib(GLFW_TRANSPARENT_FRAMEBUFFER);
	}

	/*Gets visible window attribute flag. Specifies whether the windowed mode window will be initially visible. This attribute is ignored for full screen windows. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <visible> property
	@return Visible window attribute flag, default true*/
	bool getVisible()
	{
		return (bool)_getWindowAttrib(GLFW_VISIBLE);
	}

	/*This function gets the immediate content scale of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowContentScaleX> and <getWindowContentScaleY> calls. When called from the secondary thread, performs the API transfer to the main thread*/
	void getWindowContentScale();

	/*Retrieves window content x-scale since last window content scale event, or <getWindowContentScale> call. Used as a getter of <windowContentScaleX> property
	@return Window content x-scale*/
	float getWindowContentScaleX() const
	{
		return _m.fWindowContentScaleX;
	}

	/*Retrieves window content y-scale since last window content scale event, or <getWindowContentScale> call. Used as a getter of <windowContentScaleY> property
	@return Window content y-scale*/
	float getWindowContentScaleY() const
	{
		return _m.fWindowContentScaleY;
	}

	/*This function gets the immediate size, in screen coordinates, of each edge of the frame of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowFrameBottom>, <getWindowFrameLeft>, <getWindowFrameRight> and <getWindowFrameTop> calls. When called from the secondary thread, performs the API transfer to the main thread*/
	void getWindowFrameSize();

	/*Retrieves window left edge of the frame since last <getWindowFrameSize> call. Used as a getter of <windowFrameLeft> property
	@return Window frame left edge*/
	int getWindowFrameLeft() const
	{
		return _m.iWindowFrameLeft;
	}

	/*Retrieves window top edge of the frame since last <getWindowFrameSize> call. Used as a getter of <windowFrameTop> property
	@return Window frame top edge*/
	int getWindowFrameTop() const
	{
		return _m.iWindowFrameTop;
	}

	/*Retrieves window right edge of the frame since last <getWindowFrameSize> call. Used as a getter of <windowFrameRight> property
	@return Window frame right edge*/
	int getWindowFrameRight() const
	{
		return _m.iWindowFrameRight;
	}

	/*Retrieves window bottom edge of the frame since last <getWindowFrameSize> call. Used as a getter of <windowFrameBottom> property
	@return Window frame bottom edge*/
	int getWindowFrameBottom() const
	{
		return _m.iWindowFrameBottom;
	}

	/*(M) This function retrieves the monitor object that the specified window is in full screen on
	@param [out] The empty monitor object used in full screen mode*/
	void getWindowMonitor(Monitor& monitor);

	/*This function returns the opacity of the window, including any decorations. When called from the secondary thread, returns zero value, and performs the API transfer to the main thread. Used as a getter of <windowOpacity> property
	@return The opacity of the specified window*/
	float getWindowOpacity();

	/*This function gets the immediate position, in screen coordinates, of the upper-left corner of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowPosX> and <getWindowPosY> calls. Ignored in fullscreen mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void getWindowPos();

	/*Retrieves the window x-position of window content area since last window position event, or <getWindowPos> call. Used as a getter of <windowPosX> property
	@return Window x-position, or zero in fullscreen mode*/
	int getWindowPosX() const
	{
		return (_m.pVidmode) ? 0 : _m.iWindowPosX;
	}

	/*Retrieves the window y-position of window content area since last window position event, or <getWindowPos> call. Used as a getter of <windowPosY> property
	@return Window y-position, or zero in fullscreen mode*/
	int getWindowPosY() const
	{
		return (_m.pVidmode) ? 0 : _m.iWindowPosY;
	}

	/*This function returns the value of the close flag of the specified window. Used as a getter of <windowShouldClose> property
	@return The window close flag*/
	bool getWindowShouldClose();

	/*This function gets the immediate size, in screen coordinates, of the content area of the specified window. It uses direct GLFW API call and saves the result in window object, which can be retreived via <getWindowSizeWidth> and <getWindowSizeHeight> calls. Ignored in fullscreen mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void getWindowSize();

	/*Retrieves the width of window content area since last window size event, or <getWindowSize> call. Used as a getter of <windowWidth> property
	@return The window width value*/
	int getWindowWidth() const
	{
		return (_m.pVidmode) ? _m.pVidmode->width : _m.iWindowWidth;
	}

	/*Retrieves the height of window content area since last window size event, or <getWindowSize> call. Used as a getter of <windowHeight> property
	@return The window height value*/
	int getWindowHeight() const
	{
		return (_m.pVidmode) ? _m.pVidmode->height : _m.iWindowHeight;
	}

	/*This function hides the specified window if it was previously visible. When called from the secondary thread, performs the API transfer to the main thread*/
	void hideWindow();

	/*This function iconifies/minimizes the specified window, if it was previously restored. When called from the secondary thread, performs the API transfer to the main thread*/
	void iconifyWindow();

	/*Checks if the block transfer flag of the specified window is set. Used as a getter of <blockTransfer> property
	@return True if window transfer feature is blocked, false otherwise*/
	bool isBlockTransfer() const
	{
		return (bool)_m.iBlockTransfer;
	}

	/*Checks if context of the specified window has been made current. Used as a getter of <contextCurrent> property
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

	/*Check if valid window object. Used as a getter of <window> property
	@return True if window object, false otherwise*/
	bool isWindow() const
	{
		return _m.pWindow != nullptr;
	}

	/*Checks if window receives focus since last window focus event. Used as a getter of <windowFocused> property
	@return True if window is focused, false otherwise*/
	bool isWindowFocused() const
	{
		return (bool)_m.iWindowFocused;
	}

	/*Checks if window is in fullscreen state since the creation or last monitor operation. Used as a getter of <windowFullscreen> property
	@return True if window in fullscreen mode, false otherwise*/
	bool isWindowFullscreen() const
	{
		return _m.pVidmode != nullptr;
	}

	/*Checks if window is iconified since last window iconify event. Used as a getter of <windowIconified> property
	@return True if window is iconified, false otherwise*/
	bool isWindowIconified() const
	{
		return (bool)_m.iWindowIconified;
	}

	/*Checks if window is maximized since last window maximize event. Used as a getter of <windowMaximized> property
	@return True if window maximized since last maximize event, false otherwise*/
	bool isWindowMaximized() const
	{
		return (bool)_m.iWindowMaximized;
	}

	/*Checks if window is visible since the creation or last show/hide operation. Used as a getter of <windowVisible> property
	@return True if window in fullscreen mode, false otherwise*/
	bool isWindowVisible() const
	{
		return (bool)_m.iWindowVisible;
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

	/*Sets auto iconify writable attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <autoIconify> property
	@param New auto iconify attribute flag, default true*/
	void setAutoIconify(bool flag)
	{
		_setWindowAttrib(GLFW_AUTO_ICONIFY, (int)flag);
	}

	/*Sets the block transfer flag of the specified window, which remains unchanged at the later calls. Used as a setter of <blockTransfer> property
	@param The formal boolean value, ignored*/
	void setBlockTransfer(bool flag)
	{
		if (_m.iBlockTransfer == 0) _m.iBlockTransfer = GLFW_TRUE;
	}

	/*This function sets the system clipboard to the specified, UTF-8 encoded string. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <clipboardString> property
	@param A UTF-8 encoded string*/
	void setClipboardString(_In_z_ const char* string);

	/*(M) This function sets the cursor image to be used when the cursor is over the content area of the specified window
	@param [in] The cursor object to set*/
	void setCursor(Cursor& cursor);

	/*Sets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <cursorMode> property
	@param New cursor input mode enumerator, <defult CursorNormal>*/
	void setCursorMode(CursorMode cursorMode)
	{
		_setInputMode(GLFW_CURSOR, (int)cursorMode);
	}

	/*This function sets the position, in screen coordinates, of the cursor relative to the upper-left corner of the client area of the specified window. When called from the secondary thread, performs the API transfer to the main thread
	@param The desired x-coordinate, relative to the left edge of the client area
	@param The desired y-coordinate, relative to the top edge of the client area*/
	void setCursorPos(double xpos, double ypos);

	/*Gets decorated writable attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <decorated> property
	@param New decorated attribute flag, default true*/
	void setDecorated(bool flag)
	{
		_setWindowAttrib(GLFW_DECORATED, (int)flag);
	}

	/*Sets floating writable attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <floating> property
	@param New floating attribute flag, default false*/
	void setFloating(bool flag)
	{
		_setWindowAttrib(GLFW_FLOATING, (int)flag);
	}

	/*Sets focus on show writable attribute flag. Specifies whether the window will be given input focus when <showWindow> is called. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <focusOnShow> property
	@param New focus on show attribute flag, default true*/
	void setFocusOnShow(bool flag)
	{
		_setWindowAttrib(GLFW_FOCUS_ON_SHOW, (int)flag);
	}

	/*Sets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <KeyModifier::ModCapsLock> bit set if Caps Lock was on when the event occurred and the <KeyModifier::ModNumLock> bit set if Num Lock was on. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <lockKeyMods> property
	@param New lock key mods input mode flag, default false*/
	void setLockKeyMods(bool flag)
	{
		_setInputMode(GLFW_LOCK_KEY_MODS, (int)flag);
	}

	/*Sets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <rawMouseMotion> property
	@param New raw mouse motion input mode flag, default false*/
	void setRawMouseMotion(bool flag)
	{
		_setInputMode(GLFW_RAW_MOUSE_MOTION, (int)flag);
	}

	/*Sets resizable writable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <setWindowSize> function. This attribute is ignored for full screen and undecorated windows. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <resizable> property
	@param New resizable attribute flag, default true*/
	void setResizable(bool flag)
	{
		_setWindowAttrib(GLFW_RESIZABLE, flag);
	}

	/*Sets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <getKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <stickyKeys> property
	@param New sticky keys input mode flag, default false*/
	void setStickyKeys(bool bFlag)
	{
		_setInputMode(GLFW_STICKY_KEYS, (int)bFlag);
	}

	/*Sets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <getMouseButton>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <stickyMouseButtons> property
	@param New sticky mouse buttons input mode flag, default false*/
	void setStickyMouseButtons(bool flag)
	{
		_setInputMode(GLFW_STICKY_MOUSE_BUTTONS, (int)flag);
	}

	/*This function sets the required aspect ratio of the content area of the specified window. When called from the secondary thread, performs the API transfer to the main thread
	@param The numerator of the desired aspect ratio
	@param The denominator of the desired aspect ratio*/
	void setWindowAspectRatio(int numer, int denom);

	/*Sets the fullscreen state of the specified window, only if current state is opposite. Depending of the flag value, calls <setWindowMonitor> or <unsetWindowMonitor> functions. Used as a setter of <windowFullscreen> property
	@param True to set the window into fullscreen state, false otherwise*/
	void setWindowFullscreen(bool fullscreen);

	/*(M) This function sets the icon of the specified window with an array of candidate images, from which the system selects the closest to the desired sizes
	@param The number of images in the specified array
	@param [in] The array of images to create the icon from*/
	void setWindowIcon(int count, _In_reads_(count) const GLFWimage* images);

	/*(M) (STB) Set icon of specified window from image object. Does nothing if empty object
	@param [in] Stb image object*/
	void setWindowIcon(StbImage& stbImage);

	/*Sets the iconified state of the specified window, only if current state is opposite. Depending of the flag value, calls <iconifyWindow> or <restoreWindow> functions. Used as a setter of <windowIconified> property
	@param True to set the window into iconified state, false otherwise*/
	void setWindowIconified(bool visible);

	/*Sets the maximized state of the specified window, only if current state is opposite. Depending of the flag value, calls <maximizeWindow> or <restoreWindow> functions. Used as a setter of <windowMaximize> property
	@param True to set the window into maximized state, false otherwise*/
	void setWindowMaximize(bool maximized);

	/*(1) This function sets the primary monitor that the window uses for full screen mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void setWindowMonitor();

	/*(M) (2) This function sets the monitor that the window uses for full screen mode. It also sets selected video mode parameters via window hints
	@param Monitor object with selected monitor and video mode*/
	void setWindowMonitor(Monitor& monitor);

	/*This function sets the opacity of the window, including any decorations. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <windowOpacity> property
	@param The desired opacity of the specified window*/
	void setWindowOpacity(float opacity);

	/*This function sets the position, in screen coordinates, of the upper-left corner of the content area of the specified windowed mode window. Ignored in fullscreen mode. When called from the secondary thread, performs the API transfer to the main thread
	@param The x-coordinate of the upper-left corner of the content area
	@param The y-coordinate of the upper-left corner of the content area*/
	void setWindowPos(int xpos, int ypos);

	/*This function sets the value of the close flag of the specified window. Used as a setter of <windowShouldClose> property
	@param The new window close flag*/
	void setWindowShouldClose(bool close)
	{
		glfwSetWindowShouldClose(_window(), (int)close);
	}

	/*This function sets the size, in screen coordinates, of the content area of the specified window. When called from the secondary thread, performs the API transfer to the main thread. Ignored in fullscreen mode. When called from the secondary thread, performs the API transfer to the main thread
	@param The desired width, in screen coordinates, of the window content area
	@param The desired height, in screen coordinates, of the window content area*/
	void setWindowSize(int width, int height);

	/*This function sets the size limits of the content area of the specified window. If the window is full screen, the size limits only take effect once it is made windowed. To specify only a minimum size or only a maximum one, set the other pair to GLFW_DONT_CARE. When called from the secondary thread, performs the API transfer to the main thread
	@param The minimum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The minimum height, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum height, in screen coordinates, of the content area, or GLFW_DONT_CARE*/
	void setWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight);

	/*This function sets the window title, encoded as UTF-8, of the specified window. When called from the secondary thread, performs the API transfer to the main thread. Used as a setter of <windowTitle> property
	@param [in] The UTF-8 encoded window title*/
	void setWindowTitle(_In_z_ const char* title);

	/*Sets the visible state of the specified window, only if current state is opposite. Depending of the flag value, calls <showWindow> or <hideWindow> functions. Used as a setter of <windowVisible> property
	@param True to set the window into visible state, false otherwise*/
	void setWindowVisible(bool visible);

	/*This function makes the specified window visible if it was previously hidden. When called from the secondary thread, performs the API transfer to the main thread*/
	void showWindow();

	/*This function swaps the front and back buffers of the specified window. If the swap interval is greater than zero, the GPU driver waits the specified number of screen updates before swapping the buffers. This function may be called from secondary threads*/
	void swapBuffers()
	{
		glfwSwapBuffers(_window());
	}

	/*Checks dispatched inter-thread message of the calling thread, and perform appropriate calls for a specific window messages
	@param [in-out] Points to the message structure containing the message data
	@return True if the specific message found, false otherwise*/
	static bool translateMessage(_Inout_ Message* msg);

	/*Switch back to the default arrow cursor. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetCursor();

	/*This function disables the aspect ratio limit. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowAspectRatio();

	/*This function reverts the window to its default icon. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowIcon();

	/*This function unsets the monitor that the window uses for full screen mode, setting it into windowed mode. When called from the secondary thread, performs the API transfer to the main thread*/
	void unsetWindowMonitor();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) Read-write property for auto iconify window attribute flag*/
	__declspec(property(get = getAutoIconify, put = setAutoIconify)) bool autoIconify;

	/*Read-write property for block transfer flag of the specified window*/
	__declspec(property(get = isBlockTransfer, put = setBlockTransfer)) bool blockTransfer;

	/*Read-only property for Unicode code point of the character since last character event*/
	__declspec(property(get = getCharCodepoint)) unsigned int charCodepoint;

	/*(M) Read-only property for client API window attribute value*/
	__declspec(property(get = getClientApi)) ClientApi clientApi;

	/*(M) Read-write property for window's system clipboard string. Could be set via API transfer*/
	__declspec(property(get = getClipboardString, put = setClipboardString)) const char* clipboardString;

	/*(M) Read-only property for context creation API window attribute value*/
	__declspec(property(get = getContextCreationApi)) ContextCreationApi contextCreationApi;

	/*Read-only property to check if context of the specified window has been made current*/
	__declspec(property(get = isContextCurrent)) bool contextCurrent;

	/*(M) Read-only property for context no error window attribute flag*/
	__declspec(property(get = getContextNoError)) bool contextNoError;

	/*(M) Read-only property for context release behavior window attribute value*/
	__declspec(property(get = getContextReleaseBehavior)) ContextReleaseBehavior contextReleaseBehavior;

	/*(M) Read-only property for context revision window attribute value*/
	__declspec(property(get = getContextRevision)) int contextRevision;

	/*(M) Read-only property for context robustness window attribute value*/
	__declspec(property(get = getContextRobustness)) ContextRobustness contextRobustness;

	/*Read-only property for thread object on which the context of specified window has been made current*/
	__declspec(property(get = getContextThread)) Thread* contextThread;

	/*(M) Read-only property for context version major window attribute value*/
	__declspec(property(get = getContextVersionMajor)) int contextVersionMajor;

	/*(M) Read-only property for context version minor window attribute value*/
	__declspec(property(get = getContextVersionMinor)) int contextVersionMinor;

	/*Read-only property to check if the cursor is in window client area since last cursor enter event*/
	__declspec(property(get = getCursorEntered)) bool cursorEntered;

	/*(M) Read-write property for cursor input mode flag*/
	__declspec(property(get = getCursorMode, put = setCursorMode)) CursorMode cursorMode;

	/*Read-only property for cursor x-position relative to window content area since last cursor position event, or <getCursorPos> call*/
	__declspec(property(get = getCursorPosX)) double cursorPosX;

	/*Read-only property for cursor y-position relative to window content area since last cursor position event, or <getCursorPos> call*/
	__declspec(property(get = getCursorPosY)) double cursorPosY;

	/*(M) Read-write property for decorated window attribute flag*/
	__declspec(property(get = getDecorated, put = setDecorated)) bool decorated;

	/*(M) Read-write property for floating window attribute flag*/
	__declspec(property(get = getFloating, put = setFloating)) bool floating;

	/*(M) Read-only property for focused window attribute flag*/
	__declspec(property(get = getFocused)) bool focused;

	/*(M) Read-write property for focus on show window attribute flag*/
	__declspec(property(get = getFocusOnShow, put = setFocusOnShow)) bool focusOnShow;

	/*Read-only property for window framebuffer width since last framebuffer size event, or <getFramebufferSize> call*/
	__declspec(property(get = getFramebufferHeight)) int framebufferHeight;

	/*Read-only property for window framebuffer width since last framebuffer size event, or <getFramebufferSize> call*/
	__declspec(property(get = getFramebufferWidth)) int framebufferWidth;

	/*(M) Read-only property for hovered window attribute flag*/
	__declspec(property(get = getHovered)) bool hovered;

	/*(M) Read-only property for iconified window attribute flag*/
	__declspec(property(get = getIconified)) bool iconified;

	/*Read-only property for keyboard key action since last key event*/
	__declspec(property(get = getKeyAction)) KeyAction keyAction;

	/*Read-only property for keyboard key since last key event*/
	__declspec(property(get = getKeyboardKey)) KeyboardKey keyboardKey;

	/*Read-only property for keyboard key scancode since last key event*/
	__declspec(property(get = getKeyScancode)) int keyScancode;

	/*(M) Read-write property for lock key mods input mode flag*/
	__declspec(property(get = getLockKeyMods, put = setLockKeyMods)) bool lockKeyMods;

	/*(M) Read-only property for maximized window attribute flag*/
	__declspec(property(get = getMaximized)) bool maximized;

	/*Read-only property for mouse action since last mouse event*/
	__declspec(property(get = getMouseAction)) MouseAction mouseAction;

	/*Read-only property for mouse button since last mouse event*/
	__declspec(property(get = getMouseButton)) MouseButton mouseButton;

	/*(M) Read-only property for OpenGL debug context window attribute flag*/
	__declspec(property(get = getOpenglDebugContext)) bool openglDebugContext;

	/*(M) Read-only property for OpenGL forward compatible window attribute flag*/
	__declspec(property(get = getOpenglForwardCompat)) bool openglForwardCompat;

	/*(M) Read-only property for OpenGL profile window attribute value*/
	__declspec(property(get = getOpenglProfile)) OpenglProfile openglProfile;

	/*(M) Read-write property for raw mouse motion input mode flag*/
	__declspec(property(get = getRawMouseMotion, put = setRawMouseMotion)) bool rawMouseMotion;

	/*(M) Read-write property for resizable window attribute flag*/
	__declspec(property(get = getResizable, put = setResizable)) bool resizable;

	/*Read-only property for scroll offset along the x-axis since last scroll event*/
	__declspec(property(get = getScrollOffsetX)) double scrollOffsetX;

	/*Read-only property for scroll offset along the y-axis since last scroll event*/
	__declspec(property(get = getScrollOffsetY)) double scrollOffsetY;

	/*(M) Read-write property for window sticky keys input mode flag*/
	__declspec(property(get = getStickyKeys, put = setStickyKeys)) bool stickyKeys;

	/*(M) Read-write property for window sticky mouse buttons input mode flag*/
	__declspec(property(get = getStickyMouseButtons, put = setStickyMouseButtons)) bool stickyMouseButtons;

	/*(M) Read-only property for transparent framebuffer window attribute flag*/
	__declspec(property(get = getTransparentFramebuffer)) bool transparentFramebuffer;

	/*(M) Read-only property for visible window attribute flag*/
	__declspec(property(get = getVisible)) bool visible;

	/*Read-only property to check if valid window object*/
	__declspec(property(get = isWindow)) bool window;

	/*Read-only property for window content x-scale since last window content scale event, or <getWindowContentScale> call*/
	__declspec(property(get = getWindowContentScaleX)) float windowContentScaleX;

	/*Read-only property for window content y-scale since last window content scale event, or <getWindowContentScale> call*/
	__declspec(property(get = getWindowContentScaleY)) float windowContentScaleY;

	/*Read-only property for window left edge of the frame since last <getWindowFrameSize> call*/
	__declspec(property(get = getWindowFrameLeft)) int windowFrameLeft;

	/*Read-only property for window top edge of the frame since last <getWindowFrameSize> call*/
	__declspec(property(get = getWindowFrameTop)) int windowFrameTop;

	/*Read-only property for window right edge of the frame since last <getWindowFrameSize> call*/
	__declspec(property(get = getWindowFrameRight)) int windowFrameRight;

	/*Read-only property for window bottom edge of the frame since last <getWindowFrameSize> call*/
	__declspec(property(get = getWindowFrameBottom)) int windowFrameBottom;

	/*Read-only property to check if window receives focus since last window focus event*/
	__declspec(property(get = isWindowFocused)) bool windowFocused;

	/*Read-write property for fullscreen state of the specified window*/
	__declspec(property(get = isWindowFullscreen, put = setWindowFullscreen)) bool windowFullscreen;

	/*Read-write property for iconified state of the specified window*/
	__declspec(property(get = isWindowIconified, put = setWindowIconified)) bool windowIconified;

	/*Read-write property for maximized state of the specified window*/
	__declspec(property(get = isWindowMaximized, put = setWindowMaximize)) bool windowMaximized;

	/*(M) Read-write property for window opacity value. Could be set via API transfer*/
	__declspec(property(get = getWindowOpacity, put = setWindowOpacity)) float windowOpacity;

	/*Read-only property for window x-position of window content area since last window position event, or <getWindowPos> call*/
	__declspec(property(get = getWindowPosX)) int windowPosX;

	/*Read-only property for window y-position of window content area since last window position event, or <getWindowPos> call*/
	__declspec(property(get = getWindowPosY)) int windowPosY;

	/*Read-only property for width of window content area since last window size event, or <getWindowSize> call*/
	__declspec(property(get = getWindowWidth)) int windowWidth;

	/*Read-only property for height of window content area since last window size event, or <getWindowSize> call*/
	__declspec(property(get = getWindowHeight)) int windowHeight;

	/*Read-write property for close flag of the specified window*/
	__declspec(property(get = getWindowShouldClose, put = setWindowShouldClose)) bool windowShouldClose;

	/*Read-write property for visible state of the specified window*/
	__declspec(property(get = isWindowVisible, put = setWindowVisible)) bool windowVisible;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*(M) (3.4) Gets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. Used as a getter of <mousePassthrough> property
	@return Mouse passthrough attribute flag, default false*/
	bool getMousePassthrough()
	{
		return (bool)_getWindowAttrib(GLFW_MOUSE_PASSTHROUGH);
	}

	/*(M) (3.4) This function returns the window title, encoded as UTF-8, of the specified window, previously set by <createWindow> or <setWindowTitle>. Used as a getter of <windowTitle> property
	@return The UTF-8 encoded window title*/
	_Ret_maybenull_z_ const char* getWindowTitle();

	/*(M) (3.4) Sets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. Used as a setter of <mousePassthrough> property
	@param New mouse passthrough attribute flag, default false*/
	void setMousePassthrough(bool flag)
	{
		_setWindowAttrib(GLFW_MOUSE_PASSTHROUGH, (int)flag);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) (3.4) Read-write property for mouse passthrough window attribute flag*/
	__declspec(property(get = getMousePassthrough, put = setMousePassthrough)) bool mousePassthrough;

	/*(M) (3.4) Read-write property for window title, encoded as UTF-8, of the specified window*/
	__declspec(property(get = getWindowTitle, put = setWindowTitle)) const char* windowTitle;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#elif defined(YAGLPP_CLASS_PROPERTIES) // #ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) Write-only property for window title, encoded as UTF-8, of the specified window*/
	__declspec(property(put = setWindowTitle)) const char* windowTitle;
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

#include <yaglpp/glfw/thread.h>
#include <yaglpp/glfw/cursor.h>
#include <yaglpp/glfw/monitor.h>
#include <yaglpp/stb_image.h>
namespace glfw {
#if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_NO_AFX_LAYOUT)
Thread Window::noAfxMainThread; // Definition
#endif // #if defined (YAGLPP_IMPLEMENTATION) && !defined (YAGLPP_NO_AFX_LAYOUT)

#if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)
_Ret_maybenull_z_ const char* Window::getWindowTitle()
{
	if (isMainThreadCurrent())
	{
		return glfwGetWindowTitle(_window());
	}
	_apiTransfer(YAGLPP_GET_WINDOW_TITLE, 0, 0, 0, 0);
	return nullptr;
}
#endif // #if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)

#ifdef YAGLPP_IMPLEMENTATION
#define YAGLPP_CHAR						-500
#define YAGLPP_CURSOR_ENTER				-510
#define YAGLPP_CURSOR_POS				-520
#define YAGLPP_DROP						-530
#define YAGLPP_FRAMEBUFFER_SIZE			-540
#define YAGLPP_KEY						-550
#define YAGLPP_MOUSE_BUTTON				-560
#define YAGLPP_SCROLL					-570
#define YAGLPP_WINDOW_CLOSE				-580
#define YAGLPP_WINDOW_CONTENT_SCALE		-590
#define YAGLPP_WINDOW_FOCUS				-600
#define YAGLPP_WINDOW_ICONIFY			-610
#define YAGLPP_WINDOW_MAXIMIZE			-620
#define YAGLPP_WINDOW_POS				-630
#define YAGLPP_WINDOW_REFRESH			-640
#define YAGLPP_WINDOW_SIZE				-650
#define YAGLPP_WINDOW_TRANSFER			-660

void _dropFree(int pathcount, const char** paths)
{
	for (int i = 0; i < pathcount; i++)
	{
		_deallocate((void*)paths[i], nullptr);
	}
	_deallocate((void*)paths, nullptr);
}

bool Window::_apiCallback(int msgid, Param x, Param y, Param z, Param w)
{
	Thread* pThread = _m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread) && !isBlockTransfer())
	{
		Message msg = { msgid, x, y, z, w, pThread };
		return pThread->_message(&msg);
	}
	return false;
}

bool Window::_apiTransfer(int msgid, Param x, Param y, Param z, Param w)
{
	Thread* pThread = _m.pThread;
	if ((pThread != nullptr) && !isBlockTransfer())
	{
		Message msg = { msgid, x, y, z, w, pThread };
		return Thread::_s.pMainThread->_message(&msg);
	}
	return false;
}

void Window::_applySetting(ContextSetting* setting)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	if (setting == nullptr)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, YAGLPP_CONTEXT_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, YAGLPP_CONTEXT_VERSION_MINOR);

#if (YAGLPP_CONTEXT_VERSION_MAJOR <= 3) && (YAGLPP_CONTEXT_VERSION_MINOR <= 1)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#else // #if (YAGLPP_CONTEXT_VERSION_MAJOR <= 3) && (YAGLPP_CONTEXT_VERSION_MINOR <= 1)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR <= 3) && (YAGLPP_CONTEXT_VERSION_MINOR <= 1)
	}
	else
	{
		setting->openglProfile = ((setting->contextVersionMajor == 3) && (setting->contextVersionMinor >= 2)) ?
			OpenglProfile::OpenglCoreProfile : OpenglProfile::OpenglAnyProfile; // Force compatible setting
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_ALPHA_BITS, setting->alphaBits);
		glfwWindowHint(GLFW_AUTO_ICONIFY, (int)setting->autoIconify);
		glfwWindowHint(GLFW_BLUE_BITS, setting->blueBits);
		glfwWindowHint(GLFW_CENTER_CURSOR, (int)setting->centerCursor);
		glfwWindowHint(GLFW_CLIENT_API, (int)setting->clientApi);
		glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, (int)setting->cocoaGraphicsSwitching);
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, (int)setting->cocoaRetinaFramebuffer);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, (int)setting->contextCreationApi);
		glfwWindowHint(GLFW_CONTEXT_NO_ERROR, (int)setting->contextNoError);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, (int)setting->contextReleaseBehavior);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, (int)setting->contextRobustness);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, setting->contextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, setting->contextVersionMinor);
		glfwWindowHint(GLFW_DECORATED, (int)setting->decorated);
		glfwWindowHint(GLFW_DEPTH_BITS, setting->depthBits);
		glfwWindowHint(GLFW_DOUBLEBUFFER, (int)setting->doublebuffer);
		glfwWindowHint(GLFW_GREEN_BITS, setting->greenBits);
		glfwWindowHint(GLFW_FLOATING, (int)setting->floating);
		glfwWindowHint(GLFW_FOCUSED, (int)setting->focused);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, (int)setting->focusOnShow);
		glfwWindowHint(GLFW_MAXIMIZED, (int)setting->maximized);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, (int)setting->openglDebugContext);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, (int)setting->openglForwardCompat);
		glfwWindowHint(GLFW_OPENGL_PROFILE, (int)setting->openglProfile);
		glfwWindowHint(GLFW_RED_BITS, setting->redBits);
		glfwWindowHint(GLFW_REFRESH_RATE, setting->refreshRate);
		glfwWindowHint(GLFW_RESIZABLE, (int)setting->resizable);
		glfwWindowHint(GLFW_SAMPLES, setting->samples);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, (int)setting->scaleToMonitor);
		glfwWindowHint(GLFW_SRGB_CAPABLE, (int)setting->srgbCapable);
		glfwWindowHint(GLFW_STENCIL_BITS, setting->stencilBits);
		glfwWindowHint(GLFW_STEREO, (int)setting->stereo);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, (int)setting->transparentFramebuffer);
		glfwWindowHint(GLFW_VISIBLE, (int)setting->visible);
		glfwWindowHintString(GLFW_COCOA_FRAME_NAME, setting->cocoaFrameName);
		glfwWindowHintString(GLFW_X11_CLASS_NAME, setting->x11ClassName);
		glfwWindowHintString(GLFW_X11_INSTANCE_NAME, setting->x11InstanceName);

#ifdef YAGLPP_NO_GLFW_LEGACY
		glfwWindowHint(GLFW_CONTEXT_DEBUG, (int)setting->contextDebug);
		glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, (int)setting->mousePassthrough);
		glfwWindowHint(GLFW_PLATFORM, (int)setting->platform);
		glfwWindowHint(GLFW_POSITION_Y, (int)setting->positionY);
		glfwWindowHint(GLFW_POSITION_X, (int)setting->positionX);
		glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, (int)setting->scaleFramebuffer);
		glfwWindowHint(GLFW_WAYLAND_LIBDECOR, (int)setting->waylandLibdecor);
		glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, (int)setting->win32KeyboardMenu);
		glfwWindowHint(GLFW_WIN32_SHOWDEFAULT, (int)setting->win32Showdefault);
		glfwWindowHint(GLFW_X11_XCB_VULKAN_SURFACE, (int)setting->x11XcbVulkanSurface);
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Window::_bindCallback()
{
	double dCursorX, dCursorY; // Calculate initial hovered attribute
	_m.iCursorEntered = GL_FALSE;
	glfwGetCursorPos(_m.pWindow, &dCursorX, &dCursorY);
	if ((dCursorX >= 0.0) || (dCursorY >= 0.0))
	{
		int iWidth, iHeight;
		glfwGetWindowSize(_m.pWindow, &iWidth, &iHeight);
		if ((dCursorX < iWidth) || (dCursorY < iHeight))
		{
			_m.iCursorEntered = GL_TRUE;
		}
	}
	_m.iWindowFocused = glfwGetWindowAttrib(_m.pWindow, GLFW_FOCUSED);
	_m.iWindowMaximized = glfwGetWindowAttrib(_m.pWindow, GLFW_MAXIMIZED);
	_m.iWindowVisible = glfwGetWindowAttrib(_m.pWindow, GLFW_VISIBLE);
	getCursorPos();
	getFramebufferSize();
	getWindowContentScale();
	getWindowFrameSize();
	getWindowPos();
	getWindowSize();
	glfwSetCharCallback(_m.pWindow, &_charCallback);
	glfwSetCursorEnterCallback(_m.pWindow, &_cursorEnterCallback);
	glfwSetCursorPosCallback(_m.pWindow, &_cursorPosCallback);
	glfwSetDropCallback(_m.pWindow, &_dropCallback);
	glfwSetFramebufferSizeCallback(_m.pWindow, &_framebufferSizeCallback);
	glfwSetKeyCallback(_m.pWindow, &_keyCallback);
	glfwSetMouseButtonCallback(_m.pWindow, &_mouseButtonCallback);
	glfwSetScrollCallback(_m.pWindow, &_scrollCallback);
	glfwSetWindowCloseCallback(_m.pWindow, &_windowCloseCallback);
	glfwSetWindowContentScaleCallback(_m.pWindow, &_windowContentScaleCallback);
	glfwSetWindowFocusCallback(_m.pWindow, &_windowFocusCallback);
	glfwSetWindowIconifyCallback(_m.pWindow, &_windowIconifyCallback);
	glfwSetWindowMaximizeCallback(_m.pWindow, &_windowMaximizeCallback);
	glfwSetWindowPosCallback(_m.pWindow, &_windowPosCallback);
	glfwSetWindowRefreshCallback(_m.pWindow, &_windowRefreshCallback);
	glfwSetWindowSizeCallback(_m.pWindow, &_windowSizeCallback);
	glfwSetWindowUserPointer(_m.pWindow, this);
}

void Window::_charCallback(GLFWwindow* window, unsigned int codepoint)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.uCharCodepoint = codepoint;
	pWindow->onChar(codepoint);
	pWindow->_apiCallback(YAGLPP_CHAR, codepoint, 0, 0, 0);
}

void Window::_create(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting)
{
	YAGLPP_ASSERT(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	_applySetting(setting);
	_m.pWindow = glfwCreateWindow(width, height, title, nullptr, shared);
	YAGLPP_ASSERT(isWindow()); // FAILED TO CREATE GLFW WINDOW
	_bindCallback();
}

void Window::_createFullscreen(const char* title, Monitor& monitor, GLFWwindow* shared, ContextSetting* setting)
{
	YAGLPP_ASSERT(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	_applySetting(setting);
	_m.pVidmode = monitor.getVideoMode();
	glfwWindowHint(GLFW_RED_BITS, _m.pVidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, _m.pVidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, _m.pVidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, _m.pVidmode->refreshRate);
	_m.pWindow = glfwCreateWindow(_m.pVidmode->width, _m.pVidmode->height, title, monitor._monitor(), shared);
	YAGLPP_ASSERT(isWindow()); // FAILED TO CREATE GLFW WINDOW
	_bindCallback();
}

void Window::_cursorEnterCallback(GLFWwindow* window, int entered)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iCursorEntered = entered;
	pWindow->onCursorEnter(entered);
	pWindow->_apiCallback(YAGLPP_CURSOR_ENTER, entered, 0, 0, 0);
}

void Window::_cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.dCursorPosX = xpos;
	pWindow->_m.dCursorPosY = ypos;
	pWindow->onCursorPos(xpos, ypos);
	pWindow->_apiCallback(YAGLPP_CURSOR_POS, xpos, ypos, 0, 0);
}

void Window::_dropCallback(GLFWwindow* window, int pathcount, const char** paths)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->onDrop(pathcount, paths);
	const char** pPaths = (const char**)_allocate(sizeof(WPARAM) * pathcount, nullptr);
	for (int i = 0; i < pathcount; i++)
	{
		pPaths[i] = _copyString(paths[i], nullptr);
	}
	if (!pWindow->_apiCallback(YAGLPP_DROP, pathcount, pPaths, 0, 0))
	{
		_dropFree(pathcount, pPaths); // Cleanup if message blocked
	}
}

void Window::_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iFramebufferWidth = width;
	pWindow->_m.iFramebufferHeight = height;
	pWindow->onFramebufferSize(width, height);
	pWindow->_apiCallback(YAGLPP_FRAMEBUFFER_SIZE, width, height, 0, 0);
}

int Window::_getInputMode(int mode)
{
	if (isMainThreadCurrent())
	{
		return glfwGetInputMode(_window(), mode);
	}
	_apiTransfer(YAGLPP_GET_INPUT_MODE, mode, 0, 0, 0);
	return 0;
}

int Window::_getWindowAttrib(int attrib)
{
	if (isMainThreadCurrent())
	{
		return glfwGetWindowAttrib(_window(), attrib);
	}
	_apiTransfer(YAGLPP_GET_WINDOW_ATTRIB, attrib, 0, 0, 0);
	return 0;
}

void Window::_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iKeyboardKey = key;
	pWindow->_m.iKeyScancode = scancode;
	pWindow->_m.iKeyAction = action;
	pWindow->_m.iKeyMods = mods;
	if ((pWindow->_m.iWindowClose == GLFW_TRUE) && (action == GLFW_RELEASE) && (mods == 0))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE); // Mods stuck on exit FIX
	}
	pWindow->onKey((KeyboardKey)key, scancode, (KeyAction)action, (KeyModifier)mods);
	pWindow->_apiCallback(YAGLPP_KEY, key, scancode, action, mods);
}

void Window::_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iMouseButton = button;
	pWindow->_m.iMouseAction = action;
	pWindow->_m.iKeyMods = mods;
	pWindow->onMouseButton((MouseButton)button, (MouseAction)action, (KeyModifier)mods);
	pWindow->_apiCallback(YAGLPP_MOUSE_BUTTON, button, action, mods, 0);
}

void Window::_scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.dScrollOffsetX = xoffset;
	pWindow->_m.dScrollOffsetY = yoffset;
	pWindow->onScroll(xoffset, yoffset);
	pWindow->_apiCallback(YAGLPP_SCROLL, xoffset, yoffset, 0, 0);
}

void Window::_setInputMode(int mode, int value)
{
	if (isMainThreadCurrent())
	{
		glfwSetInputMode(_window(), mode, value);
	}
	else _apiTransfer(YAGLPP_SET_INPUT_MODE, mode, value, 0, 0);
}

void Window::_setWindowAttrib(int attrib, int value)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowAttrib(_window(), attrib, value);
	}
	else _apiTransfer(YAGLPP_SET_WINDOW_ATTRIB, attrib, value, 0, 0);
}

void Window::_windowCloseCallback(GLFWwindow* window)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (pWindow->_m.iKeyMods != 0)
	{
		pWindow->_m.iWindowClose = GLFW_TRUE; // Wait for exit flag
		glfwSetWindowShouldClose(window, GLFW_FALSE);
	}
	pWindow->onWindowClose();
	pWindow->_apiCallback(YAGLPP_WINDOW_CLOSE, 0, 0, 0, 0);
}

void Window::_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.fWindowContentScaleX = xscale;
	pWindow->_m.fWindowContentScaleY = yscale;
	pWindow->onWindowContentScale(xscale, yscale);
	pWindow->_apiCallback(YAGLPP_WINDOW_CONTENT_SCALE, xscale, yscale, 0, 0);
}

void Window::_windowFocusCallback(GLFWwindow* window, int focused)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowFocused = focused;
	pWindow->onWindowFocus(focused);
	Thread* pThread = pWindow->_m.pThread;
	pWindow->_apiCallback(YAGLPP_WINDOW_FOCUS, focused, 0, 0, 0);
}

void Window::_windowIconifyCallback(GLFWwindow* window, int iconified)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowIconified = iconified;
	pWindow->onWindowIconify(iconified);
	Thread* pThread = pWindow->_m.pThread;
	pWindow->_apiCallback(YAGLPP_WINDOW_ICONIFY, iconified, 0, 0, 0);
}

void Window::_windowMaximizeCallback(GLFWwindow* window, int maximized)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowMaximized = maximized;
	pWindow->onWindowMaximize(maximized);
	pWindow->_apiCallback(YAGLPP_WINDOW_MAXIMIZE, maximized, 0, 0, 0);
}

void Window::_windowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (!pWindow->isWindowFullscreen())
	{
		pWindow->_m.iWindowPosX = xpos;
		pWindow->_m.iWindowPosY = ypos;
		pWindow->onWindowPos(xpos, ypos);
		pWindow->_apiCallback(YAGLPP_WINDOW_POS, xpos, ypos, 0, 0);
	}
}

void Window::_windowRefreshCallback(GLFWwindow* window)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->onWindowRefresh();
	pWindow->_apiCallback(YAGLPP_WINDOW_REFRESH, 0, 0, 0, 0);
}

void Window::_windowSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (!pWindow->isWindowFullscreen())
	{
		pWindow->_m.iWindowWidth = width;
		pWindow->_m.iWindowHeight = height;
		pWindow->onWindowPos(width, height);
		pWindow->_apiCallback(YAGLPP_WINDOW_SIZE, width, height, 0, 0);
	}
}

void Window::destroyWindow()
{
	if (isMainThreadCurrent())
	{
		glfwDestroyWindow(_window());
		_m.pWindow = nullptr;
	}
	else _apiTransfer(YAGLPP_DESTROY_WINDOW, 0, 0, 0, 0);
}

void Window::focusWindow()
{
	if (isMainThreadCurrent())
	{
		YAGLPP_ASSERT(isWindowVisible() && !isWindowIconified()); // WINDOW SHOULD BE VISIBLE AND NOT ICONIFIEd
		glfwFocusWindow(_window());
		_m.iWindowFocused = GLFW_TRUE;
	}
	else _apiTransfer(YAGLPP_FOCUS_WINDOW, 0, 0, 0, 0);
}

_Ret_maybenull_z_ const char* Window::getClipboardString()
{
	if (isMainThreadCurrent())
	{
		return glfwGetClipboardString(_window());
	}
	_apiTransfer(YAGLPP_GET_CLIPBOARD_STRING, 0, 0, 0, 0);
	return nullptr;
}

void Window::getCursorPos()
{
	if (isMainThreadCurrent())
	{
		glfwGetCursorPos(_window(), &_m.dCursorPosX, &_m.dCursorPosY);
	}
	else _apiTransfer(YAGLPP_GET_CURSOR_POS, 0, 0, 0, 0);
}

void Window::getFramebufferSize()
{
	if (isMainThreadCurrent())
	{
		glfwGetFramebufferSize(_window(), &_m.iFramebufferWidth, &_m.iFramebufferHeight);
	}
	else _apiTransfer(YAGLPP_GET_FRAMEBUFFER_SIZE, 0, 0, 0, 0);
}

void Window::getWindowContentScale()
{
	if (isMainThreadCurrent())
	{
		glfwGetWindowContentScale(_window(), &_m.fWindowContentScaleX, &_m.fWindowContentScaleY);
	}
	else _apiTransfer(YAGLPP_GET_WINDOW_CONTENT_SCALE, 0, 0, 0, 0);
}

void Window::getWindowFrameSize()
{
	if (isMainThreadCurrent())
	{
		glfwGetWindowFrameSize(_window(), &_m.iWindowFrameLeft, &_m.iWindowFrameTop, &_m.iWindowFrameRight, &_m.iWindowFrameBottom);
	}
	else _apiTransfer(YAGLPP_GET_WINDOW_FRAME_SIZE, 0, 0, 0, 0);
}

void Window::getWindowMonitor(Monitor& monitor)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(_window());
	YAGLPP_ASSERT(pMonitor == nullptr); // GLFW WINDOW OBJECT IS NOT IN FULLSCREEN MODE
	monitor._select(pMonitor);
}

float Window::getWindowOpacity()
{
	if (isMainThreadCurrent())
	{
		return glfwGetWindowOpacity(_window());
	}
	_apiTransfer(YAGLPP_GET_WINDOW_OPACITY, 0, 0, 0, 0);
	return 0.0f;
}

void Window::getWindowPos()
{
	if (!isWindowFullscreen())
	{
		if (isMainThreadCurrent())
		{
			glfwGetWindowPos(_window(), &_m.iWindowPosX, &_m.iWindowPosY);
		}
		else _apiTransfer(YAGLPP_GET_WINDOW_POS, 0, 0, 0, 0);
	}
}

bool Window::getWindowShouldClose()
{
	YAGLPP_ASSERT(getCurrentThread()->_dispatch()); // DISPATCH MISSING FOR A THREAD RECEIVING MESSAGES
	if (isWindow())
	{
		if (glfwWindowShouldClose(_window()))
		{
			return true;
		}
	}
	return false;
}

void Window::getWindowSize()
{
	if (!isWindowFullscreen())
	{
		if (isMainThreadCurrent())
		{
			glfwGetWindowSize(_window(), &_m.iWindowWidth, &_m.iWindowHeight);
		}
		else _apiTransfer(YAGLPP_GET_WINDOW_SIZE, 0, 0, 0, 0);
	}
}

void Window::hideWindow()
{
	if (isMainThreadCurrent())
	{
		glfwHideWindow(_window());
		_m.iWindowVisible = GLFW_FALSE;
	}
	else _apiTransfer(YAGLPP_HIDE_WINDOW, 0, 0, 0, 0);
}

void Window::iconifyWindow()
{
	if (isMainThreadCurrent())
	{
		glfwIconifyWindow(_window());
		_m.iWindowIconified = GLFW_TRUE;
	}
	else _apiTransfer(YAGLPP_ICONIFY_WINDOW, 0, 0, 0, 0);
}

void Window::makeContextCurrent()
{
	static bool bLoaded = false;
	YAGLPP_ASSERT(_m.pThread == nullptr); // WINDOW'S CONTEXT HAS BEEN MADE CURRENT
	Thread* pThread = getCurrentThread();
	if (pThread->_m.pWindow)
	{
		pThread->_m.pWindow->_m.pThread = nullptr;
	}
	_m.pThread = pThread;
	pThread->_m.pWindow = this;
	glfwMakeContextCurrent(_window());
	if (bLoaded == false)
	{
		bLoaded = yaglpp_loadGL(glfwGetProcAddress);
		YAGLPP_ASSERT(bLoaded); // FAILED TO LOAD OPENGL CONTEXT
	}
}

void Window::makeContextNonCurrent()
{
	Thread* pThread = getCurrentThread();
	YAGLPP_ASSERT(pThread == _m.pThread); // WINDOW'S CONTEXT HAS NOT BEEN MADE CURRENT
	_m.pThread = nullptr;
	glfwMakeContextCurrent(nullptr);
}

void Window::maximizeWindow()
{
	if (isMainThreadCurrent())
	{
		glfwMaximizeWindow(_window());
		_m.iWindowMaximized = GLFW_TRUE;
	}
	else _apiTransfer(YAGLPP_MAXIMIZE_WINDOW, 0, 0, 0, 0);
}

void Window::requestWindowAttention()
{
	if (isMainThreadCurrent())
	{
		glfwRequestWindowAttention(_window());
	}
	else _apiTransfer(YAGLPP_REQUEST_WINDOW_ATTENTION, 0, 0, 0, 0);
}

void Window::restoreWindow()
{
	if (isMainThreadCurrent())
	{
		glfwRestoreWindow(_window());
		_m.iWindowIconified = GLFW_FALSE;
		_m.iWindowMaximized = GLFW_FALSE;
	}
	else _apiTransfer(YAGLPP_RESTORE_WINDOW, 0, 0, 0, 0);
}

void Window::setClipboardString(_In_z_ const char* string)
{
	if (isMainThreadCurrent())
	{
		glfwSetClipboardString(_window(), string);
	}
	else
	{
		char* pString = _copyString(string, nullptr);
		if (!_apiTransfer(YAGLPP_SET_CLIPBOARD_STRING, pString, 0, 0, 0))
		{
			_deallocate(pString, nullptr); // Cleanup if message blocked
		}
	}
}

void Window::setCursorPos(double xpos, double ypos)
{
	if (isMainThreadCurrent())
	{
		glfwSetCursorPos(_window(), xpos, ypos);
		_m.dCursorPosX = xpos;
		_m.dCursorPosY = ypos;
	}
	else _apiTransfer(YAGLPP_SET_CURSOR_POS, xpos, ypos, 0, 0);
}

void Window::setWindowAspectRatio(int numer, int denom)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowAspectRatio(_window(), numer, denom);
	}
	else _apiTransfer(YAGLPP_SET_WINDOW_ASPECT_RATIO, numer, denom, 0, 0);
}

void Window::setWindowFullscreen(bool fullscreen)
{
	if (isWindowFullscreen())
	{
		if (fullscreen == false)
		{
			unsetWindowMonitor();
		}
	}
	else if (fullscreen == true)
	{
		setWindowMonitor();
	}
}

void Window::setWindowIcon(StbImage& si)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	glfwSetWindowIcon(_window(), 1, &glfwImage);
}

void Window::setWindowIconified(bool iconified)
{
	if (isWindowIconified())
	{
		if (iconified == false)
		{
			restoreWindow();
		}
	}
	else if (iconified == true)
	{
		iconifyWindow();
	}
}

void Window::setWindowMaximize(bool maximized)
{
	if (isWindowMaximized())
	{
		if (maximized == false)
		{
			restoreWindow();
		}
	}
	else if (maximized == true)
	{
		maximizeWindow();
	}
}

void Window::setWindowMonitor()
{
	if (isMainThreadCurrent())
	{
		Monitor monitor(0U);
		getWindowPos();
		getWindowSize();
		setWindowMonitor(monitor);
	}
	else _apiTransfer(YAGLPP_SET_WINDOW_MONITOR, 0, 0, 0, 0);
}

void Window::setWindowMonitor(Monitor& monitor)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD

	_m.pVidmode = monitor.getVideoMode();
	glfwWindowHint(GLFW_RED_BITS, _m.pVidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, _m.pVidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, _m.pVidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, _m.pVidmode->refreshRate);
	glfwSetWindowMonitor(_window(), monitor._monitor(), 0, 0, _m.pVidmode->width, _m.pVidmode->height, _m.pVidmode->refreshRate);
}

void Window::setWindowOpacity(float opacity)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowOpacity(_window(), opacity);
	}
	else _apiTransfer(YAGLPP_SET_WINDOW_OPACITY, opacity, 0, 0, 0);
}

void Window::setWindowPos(int xpos, int ypos)
{
	if (!isWindowFullscreen())
	{
		if (isMainThreadCurrent())
		{
			glfwSetWindowPos(_window(), xpos, ypos);
			_m.iWindowPosX = xpos;
			_m.iWindowPosY = ypos;
		}
		else _apiTransfer(YAGLPP_SET_WINDOW_POS, xpos, ypos, 0, 0);
	}
}

void Window::setWindowSize(int width, int height)
{
	if (!isWindowFullscreen())
	{
		if (isMainThreadCurrent())
		{
			glfwSetWindowSize(_window(), width, height);
			_m.iWindowWidth = width;
			_m.iWindowHeight = height;
		}
		else _apiTransfer(YAGLPP_SET_WINDOW_SIZE, width, height, 0, 0);
	}
}

void Window::setWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowSizeLimits(_window(), minwidth, minheight, maxwidth, maxheight);
	}
	else _apiTransfer(YAGLPP_SET_WINDOW_SIZE_LIMITS, minwidth, minheight, maxwidth, maxheight);
}

void Window::setWindowTitle(_In_z_ const char* title)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowTitle(_window(), title);
	}
	else
	{
		char* pString = _copyString(title, nullptr);
		if (!_apiTransfer(YAGLPP_SET_WINDOW_TITLE, pString, 0, 0, 0))
		{
			_deallocate(pString, nullptr); // Cleanup if message blocked
		}
	}
}

void Window::setWindowVisible(bool visible)
{
	if (isWindowVisible())
	{
		if (visible == false)
		{
			hideWindow();
		}
	}
	else if (visible == true)
	{
		showWindow();
	}
}

void Window::showWindow()
{
	if (isMainThreadCurrent())
	{
		glfwShowWindow(_window());
		_m.iWindowVisible = GLFW_TRUE;
	}
	else _apiTransfer(YAGLPP_SHOW_WINDOW, 0, 0, 0, 0);
}

bool Window::translateMessage(_Inout_ Message* msg)
{
	if ((msg->msgid >= 0) || !msg->sender->isContextCurrent())
	{
		return false; // Custom msg or no context window
	}
	Window* pWindow = msg->sender->getContext();

	// Main thread window API transfer
	if (isMainThreadCurrent())
	{
		bool bCleanup = false;
		switch (msg->msgid)
		{
		case YAGLPP_DESTROY_WINDOW:
			pWindow->destroyWindow();
			break;

		case YAGLPP_FOCUS_WINDOW:
			pWindow->focusWindow();
			break;

		case YAGLPP_GET_CLIPBOARD_STRING:
			bCleanup = true;
			msg->x.p = (void*)_copyString(pWindow->getClipboardString(), nullptr);
			break;

		case YAGLPP_GET_CURSOR_POS:
			pWindow->getCursorPos();
			msg->x.d = pWindow->_m.dCursorPosX;
			msg->y.d = pWindow->_m.dCursorPosY;
			break;

		case YAGLPP_GET_FRAMEBUFFER_SIZE:
			pWindow->getFramebufferSize();
			msg->x.d = pWindow->_m.iFramebufferWidth;
			msg->y.d = pWindow->_m.iFramebufferHeight;
			break;

		case YAGLPP_GET_INPUT_MODE:
			msg->y.i = pWindow->_getInputMode(msg->x.i);
			break;

		case YAGLPP_GET_WINDOW_ATTRIB:
			msg->y.i = pWindow->_getWindowAttrib(msg->x.i);
			break;

		case YAGLPP_GET_WINDOW_CONTENT_SCALE:
			pWindow->getWindowContentScale();
			msg->x.f = pWindow->_m.fWindowContentScaleX;
			msg->y.f = pWindow->_m.fWindowContentScaleY;
			break;

		case YAGLPP_GET_WINDOW_FRAME_SIZE:
			pWindow->getWindowFrameSize();
			msg->x.i = pWindow->_m.iWindowFrameLeft;
			msg->y.i = pWindow->_m.iWindowFrameTop;
			msg->z.i = pWindow->_m.iWindowFrameRight;
			msg->w.i = pWindow->_m.iWindowFrameBottom;
			break;

		case YAGLPP_GET_WINDOW_OPACITY:
			msg->x.f = pWindow->getWindowOpacity();
			break;

		case YAGLPP_GET_WINDOW_POS:
			pWindow->getWindowPos();
			msg->x.i = pWindow->_m.iWindowPosX;
			msg->y.i = pWindow->_m.iWindowPosY;
			break;

		case YAGLPP_GET_WINDOW_SIZE:
			pWindow->getWindowSize();
			msg->x.i = pWindow->_m.iWindowWidth;
			msg->y.i = pWindow->_m.iWindowHeight;
			break;

#ifdef YAGLPP_NO_GLFW_LEGACY
		case YAGLPP_GET_WINDOW_TITLE:
			bCleanup = true;
			msg->x.p = (void*)_copyString(pWindow->getWindowTitle(), nullptr);
			break;
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

		case YAGLPP_HIDE_WINDOW:
			pWindow->hideWindow();
			break;

		case YAGLPP_ICONIFY_WINDOW:
			pWindow->iconifyWindow();
			break;

		case YAGLPP_MAXIMIZE_WINDOW:
			pWindow->maximizeWindow();
			break;

		case YAGLPP_REQUEST_WINDOW_ATTENTION:
			pWindow->requestWindowAttention();
			break;

		case YAGLPP_RESTORE_WINDOW:
			pWindow->restoreWindow();
			break;

		case YAGLPP_SET_CLIPBOARD_STRING:
			bCleanup = true;
			pWindow->setClipboardString((char*)msg->x.p);
			break;

		case YAGLPP_SET_CURSOR_POS:
			pWindow->setCursorPos(msg->x.d, msg->y.d);
			break;

		case YAGLPP_SET_INPUT_MODE:
			pWindow->_setInputMode(msg->x.i, msg->y.i);
			break;

		case YAGLPP_SET_WINDOW_ASPECT_RATIO:
			pWindow->setWindowAspectRatio(msg->x.i, msg->y.i);
			break;

		case YAGLPP_SET_WINDOW_ATTRIB:
			pWindow->_setWindowAttrib(msg->x.i, msg->y.i);
			break;

		case YAGLPP_SET_WINDOW_MONITOR:
			pWindow->setWindowMonitor();
			break;

		case YAGLPP_SET_WINDOW_OPACITY:
			pWindow->setWindowOpacity(msg->x.f);
			break;

		case YAGLPP_SET_WINDOW_POS:
			pWindow->setWindowPos(msg->x.i, msg->y.i);
			break;

		case YAGLPP_SET_WINDOW_SIZE:
			pWindow->setWindowSize(msg->x.i, msg->y.i);
			break;

		case YAGLPP_SET_WINDOW_SIZE_LIMITS:
			pWindow->setWindowSizeLimits(msg->x.i, msg->y.i, msg->z.i, msg->w.i);
			break;

		case YAGLPP_SET_WINDOW_TITLE:
			bCleanup = true;
			pWindow->setWindowTitle((char*)msg->x.p);
			break;

		case YAGLPP_SHOW_WINDOW:
			pWindow->showWindow();
			break;

		case YAGLPP_UNSET_CURSOR:
			pWindow->unsetCursor();
			break;

		case YAGLPP_UNSET_WINDOW_ASPECT_RATIO:
			pWindow->unsetWindowAspectRatio();
			break;

		case YAGLPP_UNSET_WINDOW_ICON:
			pWindow->unsetWindowIcon();
			break;

		case YAGLPP_UNSET_WINDOW_MONITOR:
			pWindow->unsetWindowMonitor();
			break;

		default:
			YAGLPP_ASSERT(false); // UNKNOWN API MESSAGE
		}
		pWindow->onWindowTransfer(msg);
		Thread* pThread = pWindow->_m.pThread;
		if (pThread != nullptr)
		{
			if (!pThread->_message(msg) && bCleanup)
			{
				_deallocate(msg->x.p, nullptr); // Cleanup if message blocked
			}
		}
		return true;
	}

	// Secondary thread api message transfer
	switch (msg->msgid)
	{
	case YAGLPP_CHAR:
		pWindow->onChar(msg->x.ui);
		return true;

	case YAGLPP_CURSOR_ENTER:
		pWindow->onCursorEnter(msg->x.b);
		return true;

	case YAGLPP_CURSOR_POS:
		pWindow->onCursorPos(msg->x.d, msg->y.d);
		return true;

	case YAGLPP_DROP:
		pWindow->onDrop(msg->x.i, (const char**)msg->y.p);
		_dropFree(msg->x.i, (const char**)msg->y.p);
		return true;

	case YAGLPP_FRAMEBUFFER_SIZE:
		pWindow->onFramebufferSize(msg->x.i, msg->y.i);
		return true;

	case YAGLPP_KEY:
		pWindow->onKey((KeyboardKey)msg->x.i, msg->y.i, (KeyAction)msg->z.i, (KeyModifier)msg->w.i);
		return true;

	case YAGLPP_MOUSE_BUTTON:
		pWindow->onMouseButton((MouseButton)msg->x.i, (MouseAction)msg->y.i, (KeyModifier)msg->z.i);
		return true;

	case YAGLPP_SCROLL:
		pWindow->onScroll(msg->x.d, msg->y.d);
		return true;

	case YAGLPP_WINDOW_CLOSE:
		pWindow->onWindowClose();
		return true;

	case YAGLPP_WINDOW_CONTENT_SCALE:
		pWindow->onWindowContentScale(msg->x.f, msg->y.f);
		return true;

	case YAGLPP_WINDOW_FOCUS:
		pWindow->onWindowFocus(msg->x.b);
		return true;

	case YAGLPP_WINDOW_ICONIFY:
		pWindow->onWindowIconify(msg->x.b);
		return true;

	case YAGLPP_WINDOW_MAXIMIZE:
		pWindow->onWindowMaximize(msg->x.b);
		return true;

	case YAGLPP_WINDOW_POS:
		pWindow->onWindowPos(msg->x.i, msg->y.i);
		return true;

	case YAGLPP_WINDOW_REFRESH:
		pWindow->onWindowRefresh();
		return true;

	case YAGLPP_WINDOW_SIZE:
		pWindow->onWindowSize(msg->x.i, msg->y.i);
		return true;
	}

	// Secondary thread window API transfer
	pWindow->onWindowTransfer(msg);
	if (
#ifdef YAGLPP_NO_GLFW_LEGACY
	(msg->msgid == YAGLPP_GET_WINDOW_TITLE) ||
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

		(msg->msgid == YAGLPP_SET_WINDOW_TITLE) ||
		(msg->msgid == YAGLPP_GET_CLIPBOARD_STRING) ||
		(msg->msgid == YAGLPP_SET_CLIPBOARD_STRING))
	{
		_deallocate(msg->x.p, nullptr); // Cleanup string
	}
	return true;
}

void Window::unsetCursor()
{
	if (isMainThreadCurrent())
	{
		glfwSetCursor(_window(), nullptr);
	}
	else _apiTransfer(YAGLPP_UNSET_CURSOR, 0, 0, 0, 0);
}

void Window::unsetWindowAspectRatio()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowAspectRatio(_window(), GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
	else _apiTransfer(YAGLPP_UNSET_WINDOW_ASPECT_RATIO, 0, 0, 0, 0);
}

void Window::unsetWindowIcon()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowIcon(_window(), 0, nullptr);
	}
	else _apiTransfer(YAGLPP_UNSET_WINDOW_ICON, 0, 0, 0, 0);
}

void Window::unsetWindowMonitor()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowMonitor(_window(), nullptr, _m.iWindowPosX, _m.iWindowPosY, _m.iWindowWidth, _m.iWindowHeight, GLFW_DONT_CARE);
		_m.pVidmode = nullptr;
	}
	else _apiTransfer(YAGLPP_UNSET_WINDOW_MONITOR, 0, 0, 0, 0);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLFWwindow* Window::_window() const
{
	YAGLPP_ASSERT(isWindow()); // GLFW WINDOW OBJECT IS EMPTY
	return _m.pWindow;
}

KeyAction Window::getKey(KeyboardKey key) const
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (KeyAction)glfwGetKey(_window(), (int)key);
}

MouseAction Window::getMouseButton(MouseButton button)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (MouseAction)glfwGetMouseButton(_window(), (int)button);
}

void Window::setCursor(Cursor& cursor)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetCursor(_window(), cursor._cursor());
}

void Window::setWindowIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetWindowIcon(_window(), count, images);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLFWwindow* Window::_window() const
{
	return _m.pWindow;
}

inline KeyAction Window::getKey(KeyboardKey key) const
{
	return (KeyAction)glfwGetKey(_m.pWindow, (int)key);
}

inline MouseAction Window::getMouseButton(MouseButton button)
{
	return (MouseAction)glfwGetMouseButton(_m.pWindow, (int)button);
}

inline void Window::setCursor(Cursor& cursor)
{
	glfwSetCursor(_m.pWindow, cursor._mpCursor);
}

inline void Window::setWindowIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	glfwSetWindowIcon(_m.pWindow, count, images);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
