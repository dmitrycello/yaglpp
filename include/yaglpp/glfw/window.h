#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_WINDOW_H
#define YAGLPP_WINDOW_H

namespace glfw {
/*GLFW window object root class*/
class Window
{
public:
	/*(1) Constructs an empty window object*/
	Window();

	/*(2) (M) Constructs window object with <Create>*/
	Window(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		create_window(width, height, title, nullptr, setting);
	}

	/*(3) (M) Constructs window object with <Create>*/
	Window(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		create_window(width, height, title, shared.Get(), setting);
	}

	/*(4) (M) Construct window object with <Create>*/
	Window(_In_z_ const char* title, Monitor& monitor, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		create_fullscreen(title, monitor, nullptr, setting);
	}

	/*(5) (M) Construct window object with <Create>*/
	Window(_In_z_ const char* title, Monitor& monitor, Window& shared, _In_opt_ ContextSetting* setting = nullptr) : Window()
	{
		create_fullscreen(title, monitor, shared.Get(), setting);
	}

	/*(M) Cleans up the valid window object*/
	~Window()
	{
		Destroy();
	}

	/*Resets autodelete flag of the dynamically allocated object, forcing manual clean up*/
	void CancelAutodelete()
	{
		m_Data.autodelete = false;
	}

	/*(1) (M) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void Create(int width, int height, _In_z_ const char* title, _In_opt_ ContextSetting* setting = nullptr)
	{
		create_window(width, height, title, nullptr, setting);
	}

	/*(2) (M) This function creates a window and its associated OpenGL or OpenGL ES context
	@param The desired width, in screen coordinates, of the window. This must be greater than zero
	@param The desired height, in screen coordinates, of the window. This must be greater than zero
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void Create(int width, int height, _In_z_ const char* title, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		create_window(width, height, title, shared.Get(), setting);
	}

	/*(3) (M) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor object to use for full screen mode
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void Create(_In_z_ const char* title, Monitor& monitor, _In_opt_ ContextSetting* setting = nullptr)
	{
		create_fullscreen(title, monitor, nullptr, setting);
	}

	/*(4) (M) This function creates a fullscreen window and its associated OpenGL or OpenGL ES context
	@param [in] The initial, UTF-8 encoded window title
	@param [in] The monitor oblect to use for full screen mode
	@param [in] The window object whose context to share resources with
	@param [in] Pointer to context setting structure, or NULL to use default setting*/
	void Create(_In_z_ const char* title, Monitor& monitor, Window& shared, _In_opt_ ContextSetting* setting = nullptr)
	{
		create_fullscreen(title, monitor, shared.Get(), setting);
	}

	/*(M) This function destroys the specified window and its context. On calling this function, no further callbacks will be called for that window. If the context of the specified window is current on the main thread, it is detached before being destroyed*/
	void Destroy();

	/*(M) This function brings the specified window to front and sets input focus. The window should already be visible and not iconified. By default, both windowed and full screen mode windows are focused when initially created*/
	void Focus();

	/*Gets the last created opaque window object handle
	@return The opaque GLFW window object*/
	_Ret_notnull_ GLFWwindow* Get() const;

	/*(M) Gets auto iconify window attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. MSVC getter for <attribAutoIconify> property
	@return Auto iconify attribute flag (default true)*/
	bool GetAttribAutoIconify()
	{
		return (bool)get_window_attrib(GLFW_AUTO_ICONIFY);
	}

	/*(M) Gets client API window attribute value. MSVC getter for <attribClientApi> property
	@return The client API window attribute enumerator, default <Opengl>*/
	ClientApi GetAttribClientApi()
	{
		return (ClientApi)get_window_attrib(GLFW_CLIENT_API);
	}

	/*(M) Gets context creation API window attribute value. MSVC getter for <attribContextCreationApi> property
	@return The context creation API window attribute enumerator, default <Native>*/
	ContextApi GetAttribContextCreationApi()
	{
		return (ContextApi)get_window_attrib(GLFW_CONTEXT_CREATION_API);
	}

	/*(M) Gets context no error window attribute flag. Specifies whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior. MSVC getter for <attribContextNoError> property
	@return Context no error window attribute flag, default false*/
	bool GetAttribContextNoError()
	{
		return (bool)get_window_attrib(GLFW_CONTEXT_NO_ERROR);
	}

	/*(M) Gets context release behavior window attribute value. MSVC getter for <attribContextReleaseBehavior> property
	@return The context release behavior window attribute enumerator, default <Any>*/
	ContextReleaseBehavior GetAttribContextReleaseBehavior()
	{
		return (ContextReleaseBehavior)get_window_attrib(GLFW_CONTEXT_RELEASE_BEHAVIOR);
	}

	/*(M) Gets context revision window attribute value. Indicate the client API revision version of the window's context. MSVC getter for <attribContextRevision> property
	@return Context revision window attribute value*/
	int GetAttribContextRevision()
	{
		return get_window_attrib(GLFW_CONTEXT_REVISION);
	}

	/*(M) Gets context robustness window attribute value. MSVC getter for <attribContextRobustness> property
	@return The context robustness window attribute enumerator, default <NoRobustness>*/
	ContextRobustness GetAttribContextRobustness()
	{
		return (ContextRobustness)get_window_attrib(GLFW_CONTEXT_ROBUSTNESS);
	}

	/*(M) Gets context version major window attribute value. Indicate the client API major version of the window's context. MSVC getter for <attribContextVersionMajor> property
	@return Context version major window attribute value, default 1*/
	int GetAttribContextVersionMajor()
	{
		return get_window_attrib(GLFW_CONTEXT_VERSION_MAJOR);
	}

	/*(M) Gets context version minor window attribute value. Indicate the client API minor version of the window's context. MSVC getter for <attribContextVersionMinor> property
	@return Context version minor window attribute value, default 0*/
	int GetAttribContextVersionMinor()
	{
		return get_window_attrib(GLFW_CONTEXT_VERSION_MINOR);
	}

	/*(M) Gets decorated window attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. MSVC getter for <attribDecorated> property
	@return Decorated attribute flag, default true*/
	bool GetAttribDecorated()
	{
		return (bool)get_window_attrib(GLFW_DECORATED);
	}

	/*(M) Gets floating window attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. MSVC getter for <attribFloating> property
	@return Floating attribute flag, default false*/
	bool GetAttribFloating()
	{
		return (bool)get_window_attrib(GLFW_FLOATING);
	}

	/*(M) Gets focused window attribute flag. Specifies whether the windowed mode window will be given input focus when created. This attribute is ignored for full screen and initially hidden windows. MSVC getter for <attribFocused> property
	@return Focused window attribute flag, default true*/
	bool GetAttribFocused()
	{
		return (bool)get_window_attrib(GLFW_FOCUSED);
	}

	/*(M) Gets focus on show window attribute flag. Indicates whether the window will be given input focus when <Show> is called. MSVC getter for <attribFocusOnShow> property
	@return Focus on show attribute flag, default true*/
	bool GetAttribFocusOnShow()
	{
		return (bool)get_window_attrib(GLFW_FOCUS_ON_SHOW);
	}

	/*(M) Gets hovered window attribute flag. Indicates whether the cursor is currently directly over the content area of the window, with no other windows between. MSVC getter for <attribHovered> property
	@return Hovered window attribute flag*/
	bool GetAttribHovered()
	{
		return (bool)get_window_attrib(GLFW_HOVERED);
	}

	/*(M) Gets iconified window attribute flag. Indicates whether the specified window is iconified. MSVC getter for <attribIconified> property
	@return Iconified window attribute flag*/
	bool GetAttribIconified()
	{
		return (bool)get_window_attrib(GLFW_ICONIFIED);
	}

	/*(M) Gets maximized window attribute flag. Specifies whether the windowed mode window will be maximized when created. This attribute is ignored for full screen windows. MSVC getter for <attribMaximized> property
	@return Maximized window attribute flag, default false*/
	bool GetAttribMaximized()
	{
		return (bool)get_window_attrib(GLFW_MAXIMIZED);
	}

	/*(M) Gets the OpenGL debug context window attribute flag. Specifies whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality. MSVC getter for <attribOpenglDebugContext> property
	@return OpenGL debug context window attribute flag, default false*/
	bool GetAttribOpenglDebugContext()
	{
		return (bool)get_window_attrib(GLFW_OPENGL_DEBUG_CONTEXT);
	}

	/*(M) Gets the OpenGL forward compatible window attribute flag. Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored. MSVC getter for <attribOpenglForwardCompat> property
	@return OpenGL forward compatible window attribute flag, default false*/
	bool GetAttribOpenglForwardCompat()
	{
		return (bool)get_window_attrib(GLFW_OPENGL_FORWARD_COMPAT);
	}

	/*(M) Gets the OpenGL profile window attribute value. MSVC getter for <attribOpenglProfile> property
	@return The OpenGL profile window attribute enumerator, default <Any>*/
	OpenglProfile GetAttribOpenglProfile()
	{
		return (OpenglProfile)get_window_attrib(GLFW_OPENGL_PROFILE);
	}

	/*(M) Gets resizable window attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This attribute is ignored for full screen and undecorated windows. MSVC getter for <attribResizable> property
	@return Resizable attribute flag, default true*/
	bool GetAttribResizable()
	{
		return (bool)get_window_attrib(GLFW_RESIZABLE);
	}

	/*(M) Gets the transparent framebuffer window attribute flag. Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel. MSVC getter for <attribTransparentFramebuffer> property
	@return Transparent framebuffer window attribute flag, default false*/
	bool GetAttribTransparentFramebuffer()
	{
		return (bool)get_window_attrib(GLFW_TRANSPARENT_FRAMEBUFFER);
	}

	/*(M) Gets visible window attribute flag. Specifies whether the windowed mode window will be initially visible. This attribute is ignored for full screen windows. MSVC getter for <attribVisible> property
	@return Visible window attribute flag, default true*/
	bool GetAttribVisible()
	{
		return (bool)get_window_attrib(GLFW_VISIBLE);
	}

	/*Gets the window autodelete flag
	return True if object was allocated dynamically, false otherwise*/
	bool GetAutodelete() const
	{
		return m_Data.autodelete;
	}

	/*Gets the Unicode code point of the character since last character event. MSVC getter for <charCodepoint> property
	@return The Unicode code point of the character*/
	unsigned int GetCharCodepoint() const
	{
		return m_Data.charCodepoint;
	}

	/*(M) This function returns the contents of the system clipboard, if it contains or is convertible to a UTF-8 encoded string. If the clipboard is empty or if its contents cannot be converted, NULL is returned and an error is generated. MSVC getter for <clipboardString> property
	@return The contents of the clipboard as a UTF-8 encoded string, or NULL*/
	_Ret_maybenull_z_ const char* GetClipboardString();

	/*(M) This function retrieves the content scale for the specified window. The content scale is the ratio between the current DPI and the platform's default DPI. This is especially important for text and any UI elements. If the pixel dimensions of your UI scaled by this look appropriate on your machine then it should appear at a reasonable size on other machines regardless of their DPI and scaling settings. This relies on the system DPI and scaling settings being somewhat correct. On systems where each monitors can have its own content scale, the window content scale will depend on which monitor the system considers the window to be on. The values are stored within the window object, and then could be asynchronously retrieved via <GetContentScaleX> and <GetContentScaleY> functions*/
	void GetContentScale();

	/*Retrieves window content x-scale since last window content scale event, or <GetContentScale> call. MSVC getter for <contentScaleX> property
	@return Window content x-scale*/
	float GetContentScaleX() const
	{
		return m_Data.contentScaleX;
	}

	/*Retrieves window content y-scale since last window content scale event, or <GetContentScale> call. MSVC getter for <contentScaleY> property
	@return Window content y-scale*/
	float GetContentScaleY() const
	{
		return m_Data.contentScaleY;
	}

	/*(M) This function gets the position of the cursor, in screen coordinates, relative to the upper-left corner of the content area of the specified window.
	The values are stored within the window object, and could be asynchronously retrieved via <GetCursorPosX> and <GetCursorPosY> functions
	The function immediatelly sets the window object internal data, which could be retrieved via <GetCursorPosX> and <GetCursorPosY> functions. This data is being updated at every cursor position event, so the function should be used only if the most recent values are required*/
	void GetCursorPos();

	/*Retrieves cursor x-position relative to window content area since last cursor position event, or <GetCursorPos> call. MSVC getter for <cursorPosX> property
	@return Cursor x-position value*/
	double GetCursorPosX() const
	{
		return m_Data.cursorPosX;
	}

	/*Retrieves cursor y-position relative to window content area since last cursor position event, or <GetCursorPos> call. MSVC getter for <cursorPosY> property
	@return Cursor y-position value*/
	double GetCursorPosY() const
	{
		return m_Data.cursorPosY;
	}

	/*(M) This function retrieves the size, in pixels, of the framebuffer of the specified window. The values are stored within the window object, and then could be asynchronously retrieved via <GetFramebufferWidth> and <GetFramebufferHeight> functions*/
	void GetFramebufferSize();

	/*Gets window framebuffer width since last framebuffer size event, or <GetFramebufferSize> call. MSVC getter for <framebufferWidth> property
	@return Framebuffer width value*/
	int GetFramebufferWidth() const
	{
		return m_Data.framebufferWidth;
	}

	/*Gets window framebuffer height since last framebuffer size event, or <GetFramebufferSize> call. MSVC getter for <framebufferHeight> property
	@return Framebuffer height value*/
	int GetFramebufferHeight() const
	{
		return m_Data.framebufferHeight;
	}

	/*(M) This function retrieves the size, in screen coordinates, of each edge of the frame of the specified window. This size includes the title bar, if the window has one. The size of the frame may vary depending on the window-related hints used to create it. The values are stored within the window object, and then could be asynchronously retrieved via <GetFrameLeft>, <GetFrameTop>, <GetFrameRight> and <GetFrameBottom> functions*/
	void GetFrameSize();

	/*Retrieves window left edge of the frame since last <GetFrameSize> call. MSVC getter for <frameLeft> property
	@return Window frame left edge*/
	int GetFrameLeft() const
	{
		return m_Data.frameLeft;
	}

	/*Retrieves window top edge of the frame since last <GetFrameSize> call. MSVC getter for <frameTop> property
	@return Window frame top edge*/
	int GetFrameTop() const
	{
		return m_Data.frameTop;
	}

	/*Retrieves window right edge of the frame since last <GetFrameSize> call. MSVC getter for <frameRight> property
	@return Window frame right edge*/
	int GetFrameRight() const
	{
		return m_Data.frameRight;
	}

	/*Retrieves window bottom edge of the frame since last <GetFrameSize> call. MSVC getter for <frameBottom> property
	@return Window frame bottom edge*/
	int GetFrameBottom() const
	{
		return m_Data.frameBottom;
	}

	/*(M) Gets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. MSVC getter for <inputCursorMode> property
	@return Cursor input mode enumerator, defult <CursorNormal>*/
	Cursor::Mode GetInputCursorMode()
	{
		return (Cursor::Mode)get_input_mode(GLFW_CURSOR);
	}

	/*(M) Gets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <CapsLock> bit set if Caps Lock was on when the event occurred and the <NumLock> bit set if Num Lock was on. MSVC getter for <inputLockKeyMods> property
	@return Lock key mods input mode flag, default false*/
	bool GetInputLockKeyMods()
	{
		return (bool)get_input_mode(GLFW_LOCK_KEY_MODS);
	}

	/*(M) Gets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. MSVC getter for <inputRawMouseMotion> property
	@return Raw mouse motion input mode flag, default false*/
	bool GetInputRawMouseMotion()
	{
		return (bool)get_input_mode(GLFW_RAW_MOUSE_MOTION);
	}

	/*(M) Gets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <GetKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. MSVC getter for <inputStickyKeys> property
	@return Sticky keys input mode flag, default false*/
	bool GetInputStickyKeys()
	{
		return (bool)get_input_mode(GLFW_STICKY_KEYS);
	}

	/*(M) Gets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <GetMouse>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. MSVC getter for <inputStickyMouseButtons> property
	@return Sticky mouse buttons input mode flag, default false*/
	bool GetInputStickyMouseButtons()
	{
		return (bool)get_input_mode(GLFW_STICKY_MOUSE_BUTTONS);
	}

	/*(M) This function returns the last state reported for the specified key to the specified window
	@param The desired keyboard key enumerator value. <Unknown> is not a valid key for this function
	@return The keyboard key action enumerator, except that its <Repeat> value is not returned*/
	Action GetKey(KeyCode key) const;

	/*Gets The keyboard key action since last key event. MSVC getter for <keyAction> property
	@return The keyboard key action enumerator*/
	Action GetKeyAction() const
	{
		return (Action)m_Data.keyAction;
	}

	/*Retrieves the keyboard key since last key event. MSVC getter for <keyCode> property
	@return The keyboard key enumerator value*/
	KeyCode GetKeyCode() const
	{
		return (KeyCode)m_Data.keyCode;
	}

	/*Retrieves the keyboard key modifier since last key event. MSVC getter for <keyMods> property
	@return The keyboard key modifier enumerator value*/
	KeyMod GetKeyMods() const
	{
		return (KeyMod)m_Data.keyMods;
	}

	/*Gets The keyboard key scancode since last key event. MSVC getter for <keyScancode> property
	@return The keyboard key scancode*/
	int GetKeyScancode() const
	{
		return m_Data.keyScancode;
	}

	/*(M) This function returns the last state reported for the specified mouse button to the specified window
	@param The requested mouse button enumerator
	@return The last state reported for the specified mouse button*/
	Action GetMouse(MouseButton button);

	/*Gets the mouse action since last mouse event. MSVC getter for <mouseAction> property
	@return The mouse action enumerator value*/
	Action GetMouseAction() const
	{
		return (Action)m_Data.mouseAction;
	}

	/*Gets mouse button since last mouse event. MSVC getter for <mouseButton> property
	@return The mouse button enumerator value*/
	MouseButton GetMouseButton() const
	{
		return (MouseButton)m_Data.mouseButton;
	}

	/*(M) This function returns the opacity of the window, including any decorations. The opacity (or alpha) value is a positive finite number between zero and one, where zero is fully transparent and one is fully opaque. If the system does not support whole window transparency, this function always returns one. The initial opacity value for newly created windows is one. MSVC getter for <opacity> property
	@return The opacity value of the specified window*/
	float GetOpacity();

	/*(M) This function retrieves the position, in screen coordinates, of the upper-left corner of the content area of the specified window. The values are stored within the window object, and then could be asynchronously retrieved via <GetPosX> and <GetPosY> functions*/
	void GetPos();

	/*Retrieves the window x-position of window content area since last window position event, or <GetPos> call. MSVC getter for <posX> property
	@return Window x-position, or zero in fullscreen mode*/
	int GetPosX() const
	{
		return (m_Data.vidmode) ? 0 : m_Data.posX;
	}

	/*Retrieves the window y-position of window content area since last window position event, or <GetPos> call. MSVC getter for <posY> property
	@return Window y-position, or zero in fullscreen mode*/
	int GetPosY() const
	{
		return (m_Data.vidmode) ? 0 : m_Data.posY;
	}

	/*Get the scroll offset along the x-axis since last scroll event. MSVC getter for <scrollOffsetX> property
	@param The scroll offset along the x-axis*/
	double GetScrollOffsetX() const
	{
		return m_Data.scrollOffsetX;
	}

	/*Get the scroll offset along the y-axis since last scroll event. MSVC getter for <scrollOffsetY> property
	@param The scroll offset along the y-axis*/
	double GetScrollOffsetY() const
	{
		return m_Data.scrollOffsetY;
	}

	/*(M) This function retrieves the size, in screen coordinates, of the content area of the specified window. If you wish to retrieve the size of the framebuffer of the window in pixels, see <GetFramebufferSize>. The values are stored within the window object, and then could be asynchronously retrieved via <GetWidth> and <GetHeight> functions*/
	void GetSize();

	/*Retrieves the width of window content area since last window size event, or <GetSize> call. MSVC getter for <width> property
	@return The window width value*/
	int GetWidth() const
	{
		return (m_Data.vidmode) ? m_Data.vidmode->width : m_Data.width;
	}

	/*Retrieves the height of window content area since last window size event, or <GetSize> call. MSVC getter for <height> property
	@return The window height value*/
	int GetHeight() const
	{
		return (m_Data.vidmode) ? m_Data.vidmode->height : m_Data.height;
	}

	/*(M) This function hides the specified window if it was previously visible. If the window is already hidden or is in full screen mode, this function does nothing*/
	void Hide();

	/*(M) This function iconifies (minimizes) the specified window if it was previously restored. If the window is already iconified, this function does nothing. If the specified window is a full screen window, GLFW restores the original video mode of the monitor. The window's desired video mode is set again when the window is restored*/
	void Iconify();

	/*Checks if context of the specified window has been made current. MSVC getter for <contextCurrent> property
	@return True if context current, false otherwise*/
	bool IsContextCurrent() const
	{
		return Get() == glfwGetCurrentContext();
	}

	/*Checks if the cursor is in window client area since last cursor enter event. MSVC getter for <cursorEntered> property
	@return True if mouse cursor is over the window client area, false otherwise*/
	bool IsCursorEntered() const
	{
		return (bool)m_Data.cursorEntered;
	}

	/*Checks if window receives focus since last window focus event. MSVC getter for <focused> property
	@return True if window is focused, false otherwise*/
	bool IsFocused() const
	{
		return (bool)m_Data.focused;
	}

	/*Checks if window is in fullscreen state since the creation or last monitor operation. MSVC getter for <fullscreen> property
	@return True if window in fullscreen mode, false otherwise*/
	bool IsFullscreen() const
	{
		return m_Data.vidmode != nullptr;
	}

	/*Checks the state of specified key modifier since last key or mouse event
	@param The desired key modifier enumerator
	@return True if specified key modifier was pressed since last key or mouse event, false otherwise*/
	bool IsKeyMod(KeyMod mod) const
	{
		return (bool)(m_Data.keyMods & (int)mod);
	}

	/*Checks if window is iconified since last window iconify event. MSVC getter for <iconified> property
	@return True if window is iconified, false otherwise*/
	bool IsIconified() const
	{
		return (bool)m_Data.iconified;
	}

	/*Checks if window is maximized since last window maximize event. MSVC getter for <maximized> property
	@return True if window maximized since last maximize event, false otherwise*/
	bool IsMaximized() const
	{
		return (bool)m_Data.maximized;
	}

	/*Checks if window is visible since the creation or last show/hide operation. MSVC getter for <visible> property
	@return True if window in fullscreen mode, false otherwise*/
	bool IsVisible() const
	{
		return (bool)m_Data.visible;
	}

	/*Check if valid window object. MSVC getter for <window> property
	@return True if window object, false otherwise*/
	bool IsWindow() const
	{
		return m_Data.window != nullptr;
	}

	/*This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. Associates the window object with the calling thread, at the first call initializes OpenGL*/
	void MakeContextCurrent();

	/*This function makes the OpenGL or OpenGL ES context non-current on the calling thread. Detaches the current context from the calling thread without making a new one current*/
	static void MakeContextNonCurrent()
	{
		glfwMakeContextCurrent(nullptr);
	}

	/*(M) This function maximizes the specified window if it was previously not maximized*/
	void Maximize();

	/*(M) This function requests user attention to the specified window. On platforms where this is not supported, attention is requested to the application as a whole*/
	void RequestAttention();

	/*(M) This function restores the specified window, if it was previously iconified/minimized or maximized*/
	void Restore();

	/*(M) This function sets the required aspect ratio of the content area of the specified window
	@param The numerator of the desired aspect ratio
	@param The denominator of the desired aspect ratio*/
	void SetAspectRatio(int numer, int denom);

	/*(M) Sets auto iconify writable attribute flag. Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This attribute is ignored for windowed mode windows. MSVC setter for <attribAutoIconify> property
	@param New auto iconify attribute flag, default true*/
	void SetAttribAutoIconify(bool flag)
	{
		set_window_attrib(GLFW_AUTO_ICONIFY, (int)flag);
	}

	/*(M) Gets decorated writable attribute flag. Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This attribute is ignored for full screen windows. MSVC setter for <attribDecorated> property
	@param New decorated attribute flag, default true*/
	void SetAttribDecorated(bool flag)
	{
		set_window_attrib(GLFW_DECORATED, (int)flag);
	}

	/*(M) Sets floating writable attribute flag. Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This attribute is ignored for full screen windows. MSVC setter for <attribFloating> property
	@param New floating attribute flag, default false*/
	void SetAttribFloating(bool flag)
	{
		set_window_attrib(GLFW_FLOATING, (int)flag);
	}

	/*(M) Sets focus on show writable attribute flag. Specifies whether the window will be given input focus when <Show> is called. MSVC setter for <attribFocusOnShow> property
	@param New focus on show attribute flag, default true*/
	void SetAttribFocusOnShow(bool flag)
	{
		set_window_attrib(GLFW_FOCUS_ON_SHOW, (int)flag);
	}

	/*(M) Sets resizable writable attribute flag. Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <SetSize> function. This attribute is ignored for full screen and undecorated windows. MSVC setter for <attribResizable> property
	@param New resizable attribute flag, default true*/
	void SetAttribResizable(bool flag)
	{
		set_window_attrib(GLFW_RESIZABLE, flag);
	}

	/*(M) This function sets the system clipboard to the specified, UTF-8 encoded string. MSVC setter for <clipboardString> property
	@param A UTF-8 encoded string*/
	void SetClipboardString(_In_z_ const char* string);

	/*(M) This function sets the cursor image to be used when the cursor is over the content area of the specified window
	@param [in] The cursor object to set*/
	void SetCursor(Cursor& cursor);

	/*(M) This function sets the position, in screen coordinates, of the cursor relative to the upper-left corner of the client area of the specified window
	@param The desired x-coordinate, relative to the left edge of the client area
	@param The desired y-coordinate, relative to the top edge of the client area*/
	void SetCursorPos(double xpos, double ypos);

	/*(M) (1) Set icon of specified window from STB image object. Does nothing if empty object
	@param [in] Stb image object*/
	void SetIcon(StbImage& stbImage);

	/*(M) (2) This function sets the icon of the specified window with an array of candidate images, from which the system selects the closest to the desired sizes
	@param The number of images in the specified array
	@param [in] The array of images to create the icon from*/
	void SetIcon(int count, _In_reads_(count) const GLFWimage* images);

	/*(M) Sets window cursor input mode value. The cursor input mode provides several cursor modes for special forms of mouse motion input. MSVC setter for <inputCursorMode> property
	@param New cursor input mode enumerator, default <CursorNormal>*/
	void SetInputCursorMode(Cursor::Mode cursorMode)
	{
		set_input_mode(GLFW_CURSOR, (int)cursorMode);
	}

	/*(M) Sets lock key mods input mode flag. When this input mode is enabled, any callback that receives modifier bits will have the <CapsLock> bit set if Caps Lock was on when the event occurred and the <NumLock> bit set if Num Lock was on. MSVC setter for <inputLockKeyMods> property
	@param New lock key mods input mode flag, default false*/
	void SetInputLockKeyMods(bool flag)
	{
		set_input_mode(GLFW_LOCK_KEY_MODS, (int)flag);
	}

	/*(M) Sets raw mouse motion input mode flag. When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available. Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse motion is only provided when the cursor is disabled. MSVC setter for <inputRawMouseMotion> property
	@param New raw mouse motion input mode flag, default false*/
	void SetInputRawMouseMotion(bool flag)
	{
		set_input_mode(GLFW_RAW_MOUSE_MOTION, (int)flag);
	}

	/*(M) Sets window sticky keys input mode flag. When sticky keys mode is enabled, the pollable state of a key will remain pressed (true) until the state of that key is polled with <GetKey>. Once it has been polled, if a key release event had been processed in the meantime, the state will reset to released (false), otherwise it will remain pressed. MSVC setter for <inputStickyKeys> property
	@param New sticky keys input mode flag, default false*/
	void SetInputStickyKeys(bool bFlag)
	{
		set_input_mode(GLFW_STICKY_KEYS, (int)bFlag);
	}

	/*(M) Sets window sticky mouse buttons input mode flag. When sticky mouse buttons mode is enabled, the pollable state of a mouse button will pressed (true) until the state of that button is polled with <GetMouse>. Once it has been polled, if a mouse button release event had been processed in the meantime, the state will reset to released (false), otherwise it will pressed. MSVC setter for <inputStickyMouseButtons> property
	@param New sticky mouse buttons input mode flag, default false*/
	void SetInputStickyMouseButtons(bool flag)
	{
		set_input_mode(GLFW_STICKY_MOUSE_BUTTONS, (int)flag);
	}

	/*(M) (1) This function sets the primary monitor that the window uses for full screen mode*/
	void SetMonitor()
	{
		Monitor monitor(0U); SetMonitor(monitor, 0, 0, 0, 0);
	}

	/*(M) (2) This function sets the given monitor that the window uses for full screen mode
	@param Monitor object with selected monitor and video mode*/
	void SetMonitor(Monitor& monitor)
	{
		SetMonitor(monitor, 0, 0, 0, 0);
	}

	/*(M) (3) This function sets the given monitor that the window uses for full screen mode, with
	@param Monitor object with selected monitor and video mode
	@param The fullscreen window x-position
	@param The fullscreen window y-position
	@param The fullscreen window width
	@param The fullscreen window height*/
	void SetMonitor(Monitor& monitor, int xpos, int ypos, int width, int height);

	/*(M) This function sets the opacity of the window, including any decorations. MSVC setter for <opacity> property
	@param The desired opacity of the specified window*/
	void SetOpacity(float opacity);

	/*(M) This function sets the position, in screen coordinates, of the upper-left corner of the content area of the specified windowed mode window. Ignored in fullscreen mode
	@param The x-coordinate of the upper-left corner of the content area
	@param The y-coordinate of the upper-left corner of the content area*/
	void SetPos(int xpos, int ypos);

	/*This function sets the value of the close flag of the specified window. MSVC setter for <shouldClose> property
	@param The new window close flag*/
	void SetShouldClose(bool close)
	{
		glfwSetWindowShouldClose(Get(), (int)close);
	}

	/*(M) This function sets the size, in screen coordinates, of the content area of the specified window
	@param The desired width, in screen coordinates, of the window content area
	@param The desired height, in screen coordinates, of the window content area*/
	void SetSize(int width, int height);

	/*(M) This function sets the size limits of the content area of the specified window. If the window is full screen, the size limits only take effect once it is made windowed. To specify only a minimum size or only a maximum one, set the other pair to GLFW_DONT_CARE
	@param The minimum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The minimum height, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum width, in screen coordinates, of the content area, or GLFW_DONT_CARE
	@param The maximum height, in screen coordinates, of the content area, or GLFW_DONT_CARE*/
	void SetSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight);

	/*(M) This function sets the window title, encoded as UTF-8, of the specified window. MSVC setter for <title> property
	@param [in] The UTF-8 encoded window title*/
	void SetTitle(_In_z_ const char* title);

	/*This function returns the value of the close flag of the specified window. MSVC getter for <shouldClose> property
	@return The window close flag*/
	bool ShouldClose();

	/*(M) This function makes the specified window visible if it was previously hidden*/
	void Show();

	/*This function swaps the front and back buffers of the specified window. If the swap interval is greater than zero, the GPU driver waits the specified number of screen updates before swapping the buffers. This function may be called from secondary threads*/
	void SwapBuffers()
	{
		glfwSwapBuffers(Get());
	}

	/*(M) This function disables the aspect ratio limit*/
	void UnsetAspectRatio();

	/*(M) Switch back to the default arrow cursor*/
	void UnsetCursor();

	/*(M) This function reverts the window to its default icon*/
	void UnsetIcon();

	/*(M) This function unsets the monitor that the window uses for full screen mode, setting it into windowed mode*/
	void UnsetMonitor();

	/*GLFW window object new operator returning allocated object
	@param The size in bytes of allocated object
	@return The pointer to allocated object*/
	static void* operator new(std::size_t count);

	/*Using the object's new operator is not allowed*/
	void* operator new[](std::size_t) = delete;

	/*Using the object's delete operator is not allowed*/
	void operator delete[](void*) = delete;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) Read-write property for auto iconify window attribute flag*/
	__declspec(property(get = GetAttribAutoIconify, put = SetAttribAutoIconify)) bool attribAutoIconify;

	/*(M) Read-only property for client API window attribute value*/
	__declspec(property(get = GetAttribClientApi)) ClientApi attribClientApi;

	/*(M) Read-only property for context creation API window attribute value*/
	__declspec(property(get = GetAttribContextCreationApi)) ContextApi attribContextCreationApi;

	/*(M) Read-only property for context no error window attribute flag*/
	__declspec(property(get = GetAttribContextNoError)) bool attribContextNoError;

	/*(M) Read-only property for context release behavior window attribute value*/
	__declspec(property(get = GetAttribContextReleaseBehavior)) ContextReleaseBehavior attribContextReleaseBehavior;

	/*(M) Read-only property for context revision window attribute value*/
	__declspec(property(get = GetAttribContextRevision)) int attribContextRevision;

	/*(M) Read-only property for context robustness window attribute value*/
	__declspec(property(get = GetAttribContextRobustness)) ContextRobustness attribContextRobustness;

	/*(M) Read-only property for context version major window attribute value*/
	__declspec(property(get = GetAttribContextVersionMajor)) int attribContextVersionMajor;

	/*(M) Read-only property for context version minor window attribute value*/
	__declspec(property(get = GetAttribContextVersionMinor)) int attribContextVersionMinor;

	/*(M) Read-write property for decorated window attribute flag*/
	__declspec(property(get = GetAttribDecorated, put = SetAttribDecorated)) bool attribDecorated;

	/*(M) Read-write property for floating window attribute flag*/
	__declspec(property(get = GetAttribFloating, put = SetAttribFloating)) bool attribFloating;

	/*(M) Read-only property for focused window attribute flag*/
	__declspec(property(get = GetAttribFocused)) bool attribFocused;

	/*(M) Read-write property for focus on show window attribute flag*/
	__declspec(property(get = GetAttribFocusOnShow, put = SetAttribFocusOnShow)) bool attribFocusOnShow;

	/*(M) Read-only property for hovered window attribute flag*/
	__declspec(property(get = GetAttribHovered)) bool attribHovered;

	/*(M) Read-only property for iconified window attribute flag*/
	__declspec(property(get = GetAttribIconified)) bool attribIconified;

	/*(M) Read-only property for maximized window attribute flag*/
	__declspec(property(get = GetAttribMaximized)) bool attribMaximized;

	/*(M) Read-only property for OpenGL debug context window attribute flag*/
	__declspec(property(get = GetAttribOpenglDebugContext)) bool attribOpenglDebugContext;

	/*(M) Read-only property for OpenGL forward compatible window attribute flag*/
	__declspec(property(get = GetAttribOpenglForwardCompat)) bool attribOpenglForwardCompat;

	/*(M) Read-only property for OpenGL profile window attribute value*/
	__declspec(property(get = GetAttribOpenglProfile)) OpenglProfile attribOpenglProfile;

	/*(M) Read-write property for resizable window attribute flag*/
	__declspec(property(get = GetAttribResizable, put = SetAttribResizable)) bool attribResizable;

	/*(M) Read-only property for transparent framebuffer window attribute flag*/
	__declspec(property(get = GetAttribTransparentFramebuffer)) bool attribTransparentFramebuffer;

	/*(M) Read-only property for visible window attribute flag*/
	__declspec(property(get = GetAttribVisible)) bool attribVisible;

	/*Read-only property for Unicode code point of the character since last character event*/
	__declspec(property(get = GetCharCodepoint)) unsigned int charCodepoint;

	/*(M) Read-write property for window's system clipboard string*/
	__declspec(property(get = GetClipboardString, put = SetClipboardString)) const char* clipboardString;

	/*Read-only property to check if context of the specified window has been made current*/
	__declspec(property(get = IsContextCurrent)) bool contextCurrent;

	/*Read-only property for window content x-scale since last window content scale event, or <GetContentScale> call*/
	__declspec(property(get = GetContentScaleX)) float contentScaleX;

	/*Read-only property for window content y-scale since last window content scale event, or <GetContentScale> call*/
	__declspec(property(get = GetContentScaleY)) float contentScaleY;

	/*Read-only property to check if the cursor is in window client area since last cursor enter event*/
	__declspec(property(get = IsCursorEntered)) bool cursorEntered;

	/*Read-only property for cursor x-position relative to window content area since last cursor position event, or <GetCursorPos> call*/
	__declspec(property(get = GetCursorPosX)) double cursorPosX;

	/*Read-only property for cursor y-position relative to window content area since last cursor position event, or <GetCursorPos> call*/
	__declspec(property(get = GetCursorPosY)) double cursorPosY;

	/*Read-only property to check if window receives focus since last window focus event*/
	__declspec(property(get = IsFocused)) bool focused;

	/*Read-only property for window framebuffer width since last framebuffer size event, or <GetFramebufferSize> call*/
	__declspec(property(get = GetFramebufferWidth)) int framebufferWidth;

	/*Read-only property for window framebuffer width since last framebuffer size event, or <GetFramebufferSize> call*/
	__declspec(property(get = GetFramebufferHeight)) int framebufferHeight;

	/*Read-only property for window left edge of the frame since last <GetFrameSize> call*/
	__declspec(property(get = GetFrameLeft)) int frameLeft;

	/*Read-only property for window top edge of the frame since last <GetFrameSize> call*/
	__declspec(property(get = GetFrameTop)) int frameTop;

	/*Read-only property for window right edge of the frame since last <GetFrameSize> call*/
	__declspec(property(get = GetFrameRight)) int frameRight;

	/*Read-only property for window bottom edge of the frame since last <GetFrameSize> call*/
	__declspec(property(get = GetFrameBottom)) int frameBottom;

	/*Read-only property for fullscreen state of the specified window*/
	__declspec(property(get = IsFullscreen)) bool fullscreen;

	/*Read-only property for iconified state of the specified window*/
	__declspec(property(get = IsIconified)) bool iconified;

	/*Read-only property for keyboard key action since last key event*/
	__declspec(property(get = GetKeyAction)) Action keyAction;

	/*Read-only property for keyboard key since last key event*/
	__declspec(property(get = GetKeyCode)) KeyCode keyCode;

	/*Read-only property for keyboard key modifier since last key event*/
	__declspec(property(get = GetKeyMods)) KeyMod keyMods;
	
	/*Read-only property for keyboard key scancode since last key event*/
	__declspec(property(get = GetKeyScancode)) int keyScancode;

	/*(M) Read-write property for cursor input mode flag*/
	__declspec(property(get = GetInputCursorMode, put = SetInputCursorMode)) Cursor::Mode inputCursorMode;

	/*(M) Read-write property for lock key mods input mode flag*/
	__declspec(property(get = GetInputLockKeyMods, put = SetInputLockKeyMods)) bool inputLockKeyMods;

	/*(M) Read-write property for raw mouse motion input mode flag*/
	__declspec(property(get = GetInputRawMouseMotion, put = SetInputRawMouseMotion)) bool inputRawMouseMotion;

	/*(M) Read-write property for window sticky keys input mode flag*/
	__declspec(property(get = GetInputStickyKeys, put = SetInputStickyKeys)) bool inputStickyKeys;

	/*(M) Read-write property for window sticky mouse buttons input mode flag*/
	__declspec(property(get = GetInputStickyMouseButtons, put = SetInputStickyMouseButtons)) bool inputStickyMouseButtons;

	/*Read-only property for maximized state of the specified window*/
	__declspec(property(get = IsMaximized)) bool maximized;

	/*Read-only property for mouse action since last mouse event*/
	__declspec(property(get = GetMouseAction)) Action mouseAction;

	/*Read-only property for mouse button since last mouse event*/
	__declspec(property(get = GetMouseButton)) MouseButton mouseButton;

	/*(M) Read-write property for window opacity value*/
	__declspec(property(get = GetOpacity, put = SetOpacity)) float opacity;

	/*Read-only property for window x-position of window content area since last window position event, or <GetPos> call*/
	__declspec(property(get = GetPosX)) int posX;

	/*Read-only property for window y-position of window content area since last window position event, or <GetPos> call*/
	__declspec(property(get = GetPosY)) int posY;

	/*Read-only property for scroll offset along the x-axis since last scroll event*/
	__declspec(property(get = GetScrollOffsetX)) double scrollOffsetX;

	/*Read-only property for scroll offset along the y-axis since last scroll event*/
	__declspec(property(get = GetScrollOffsetY)) double scrollOffsetY;

	/*Read-write property for close flag of the specified window*/
	__declspec(property(get = ShouldClose, put = SetShouldClose)) bool shouldClose;

	/*Read-only property for width of window content area since last window size event, or <GetSize> call*/
	__declspec(property(get = GetWidth)) int width;

	/*Read-only property for height of window content area since last window size event, or <GetSize> call*/
	__declspec(property(get = GetHeight)) int height;
	
	/*Read-only property for visible state of the specified window*/
	__declspec(property(get = IsVisible)) bool visible;

	/*Read-only property to check if valid window object*/
	__declspec(property(get = IsWindow)) bool window;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*(M) (3.4) Gets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. MSVC getter for <attribMousePassthrough> property
	@return Mouse passthrough attribute flag, default false*/
	bool GetAttribMousePassthrough()
	{
		return (bool)get_window_attrib(GLFW_MOUSE_PASSTHROUGH);
	}

	/*(M) (3.4) This function returns the window title, encoded as UTF-8, of the specified window, previously set by <Create> or <SetTitle>. MSVC getter for <title> property
	@return The UTF-8 encoded window title*/
	_Ret_maybenull_z_ const char* GetTitle();

	/*(M) (3.4) Sets mouse passthrough attribute flag. Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms. MSVC setter for <attribMousePassthrough> property
	@param New mouse passthrough attribute flag, default false*/
	void SetAttribMousePassthrough(bool flag)
	{
		set_window_attrib(GLFW_MOUSE_PASSTHROUGH, (int)flag);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) (3.4) Read-write property for mouse passthrough window attribute flag*/
	__declspec(property(get = GetAttribMousePassthrough, put = SetAttribMousePassthrough)) bool attribMousePassthrough;

	/*(M) (3.4) Read-write property for window title, encoded as UTF-8, of the specified window*/
	__declspec(property(get = GetTitle, put = SetTitle)) const char* title;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#elif defined(YAGLPP_CLASS_PROPERTIES) // #ifdef YAGLPP_NO_GLFW_LEGACY
	/*(M) Write-only property for window title, encoded as UTF-8, of the specified window*/
	__declspec(property(put = SetTitle)) const char* title;
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

protected:
	/*A Unicode character event handler
	@param The Unicode code point of the character*/
	virtual void OnChar(unsigned int codepoint) {}

	/*A window close event handler*/
	virtual void OnClose() {}

	/*A window content scale event handler
	@param The new x-axis content scale of the window
	@param The new y-axis content scale of the window*/
	virtual void OnContentScale(float xscale, float yscale) {}

	/*A cursor enter event handler
	@param True if the cursor entered the window's client area, false otherwise*/
	virtual void OnCursorEnter(bool entered) {}

	/*A cursor position event handler
	@param The new x-coordinate, in screen coordinates, of the cursor
	@param The new y-coordinate, in screen coordinates, of the cursor*/
	virtual void OnCursorPos(double xpos, double ypos) {}

	/*A window cleanup event handler, called before the window object is discarded*/
	virtual void OnDestroy() {}

	/*A file drop event handler
	@param The number of dropped files
	@param The UTF-8 encoded file and/or directory path names*/
	virtual void OnDrop(int pathcount, _In_reads_(pathcount) const char** paths) {}

	/*A window focus gain event handler
	@param True if the window was given input focus, false otherwise*/
	virtual void OnFocus(bool focused) {}

	/*A framebuffer size event handler
	@param The new width, in pixels, of the framebuffer
	@param The new height, in pixels, of the framebuffer*/
	virtual void OnFramebufferSize(int width, int height) {}

	/*A window iconify event handler
	@param True if the window was iconified, or false if it was restored*/
	virtual void OnIconify(bool iconified) {}

	/*A keyboard key event handler
	@param The keyboard key enumerator that was pressed, released or held down until repeated
	@param The system-specific scancode of the key
	@param The key action enumerator describing if the key was pressed, released or held down until repeated
	@param The key modifier enumerator describing which modifier keys were held down*/
	virtual void OnKey(KeyCode key, int scancode, Action action, KeyMod mods) {}

	/*A window maximize event handler, called only from the main thread
	@param True if the window was maximized, or false if it was restored*/
	virtual void OnMaximize(bool maximized) {}

	/*A mouse button event handler
	@param The mouse button enumerator that was pressed or released
	@param The mouse action enumerator describing if the mouse was pressed or released
	@param The key modifier enumerator describing which modifier keys were held down*/
	virtual void OnMouseButton(MouseButton button, Action action, KeyMod mods) {}

	/*A window position event handler
	@param The new x-coordinate, in screen coordinates, of the upper-left corner of the content area of the window
	@param The new y-coordinate, in screen coordinates, of the upper-left corner of the content area of the window*/
	virtual void OnPos(int xpos, int ypos) {}

	/*A window content refresh event handler*/
	virtual void OnRefresh() {}

	/*A scroll event handler
	@param The scroll offset along the x-axis
	@param The scroll offset along the y-axis*/
	virtual void OnScroll(double xoffset, double yoffset) {}

	/*A window size event handler
	@param The new width, in screen coordinates, of the window
	@param The new height, in screen coordinates, of the window*/
	virtual void OnSize(int width, int height) {}

private:
	// Window object member data structure
	struct MDATA {
		bool autodelete; // Allocated window flag
		unsigned int charCodepoint; // The Unicode code point of the character since last character event
		int close; // Close flag used to delay window closing until release of mods (FIX)
		float contentScaleX; // Window content X-scale since last window content scale event
		float contentScaleY; // Window content Y-scale since last window content scale event
		int cursorEntered; // Window hover flag since last cursor enter event
		double cursorPosX; // Cursor X-position relative to window content area since last cursor position event
		double cursorPosY; // Cursor Y-position relative to window content area since last cursor position event
		int focused; // Window focus flag since last window focus event
		int framebufferWidth; // Window framebuffer width since last framebuffer size event
		int framebufferHeight; // Window framebuffer height since last framebuffer size event
		int frameBottom; // The bottom edge of the window frame
		int frameLeft; // The left edge of the window frame
		int frameRight; // The right edge of the window frame
		int frameTop; // The top edge of the window frame
		int keyAction; // Keyboard key action since last key event
		int keyCode; // Keyboard key since last key event
		int keyMods; // Keyboard key modifier flags since last key or mouse event
		int keyScancode; // Keyboard key scancode since last key event
		int iconified; // Window iconify flag since last window iconify event
		int maximized; // Window maximize flag since last window maximize event
		int mouseAction; // Mouse action since last mouse event
		int mouseButton; // Mouse button since last mouse event
		int posX; // X-position of window content area since last window position event
		int posY; // Y-position of window content area since last window position event
		double scrollOffsetX; // Scroll offset along the x-axis since last scroll event
		double scrollOffsetY; // scroll offset along the y-axis since last scroll event
		const GLFWvidmode* vidmode; // Window fullscreen video mode
		int visible; // Window visible state flag
		int width; // Width of window content area since last window size event
		int height; // Height of window content area since last window size event
		GLFWwindow* window; // GLFW window object
	} m_Data;

	static void apply_setting(ContextSetting* setting);
	void bind_callback();
	static void callback_char(GLFWwindow* window, unsigned int codepoint);
	static void callback_cursor_enter(GLFWwindow* window, int entered);
	static void callback_cursor_pos(GLFWwindow* window, double xpos, double ypos);
	static void callback_drop(GLFWwindow* window, int pathcount, const char** paths);
	static void callback_framebuffer_size(GLFWwindow* window, int width, int height);
	static void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void callback_mouse_button(GLFWwindow* window, int button, int action, int mods);
	static void callback_scroll(GLFWwindow* window, double xoffset, double yoffset);
	static void callback_window_close(GLFWwindow* window);
	static void callback_window_content_scale(GLFWwindow* window, float xscale, float yscale);
	static void callback_window_focus(GLFWwindow* window, int focused);
	static void callback_window_iconify(GLFWwindow* window, int iconified);
	static void callback_window_maximize(GLFWwindow* window, int maximized);
	static void callback_window_pos(GLFWwindow* window, int xpos, int ypos);
	static void callback_window_refresh(GLFWwindow* window);
	static void callback_window_size(GLFWwindow* window, int width, int height);
	void create_fullscreen(const char* title, Monitor& fullscreen, GLFWwindow* shared, ContextSetting* setting);
	void create_window(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting);
	int get_input_mode(int mode);
	int get_window_attrib(int attrib);
	void set_input_mode(int mode, int value);
	void set_window_attrib(int attrib, int value);
}; // class Window

#ifdef YAGLPP_IMPLEMENTATION
Window::Window()
{
	std::memset(&m_Data, 0, sizeof(MDATA));
	m_Data.autodelete = Thread::GetAlloc();
}

void Window::apply_setting(ContextSetting* setting)
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

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
			OpenglProfile::Core : OpenglProfile::Any; // Force compatible setting
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

void Window::bind_callback()
{
	glfwGetCursorPos(m_Data.window, &m_Data.cursorPosX, &m_Data.cursorPosY);
	glfwGetFramebufferSize(m_Data.window, &m_Data.framebufferWidth, &m_Data.framebufferHeight);
	glfwGetWindowSize(m_Data.window, &m_Data.width, &m_Data.height);
	glfwGetWindowContentScale(m_Data.window, &m_Data.contentScaleX, &m_Data.contentScaleY);
	glfwGetWindowFrameSize(m_Data.window, &m_Data.frameLeft, &m_Data.frameTop, &m_Data.frameRight, &m_Data.frameBottom);
	glfwGetWindowPos(m_Data.window, &m_Data.posX, &m_Data.posY);

	m_Data.cursorEntered = GL_FALSE;
	m_Data.focused = glfwGetWindowAttrib(m_Data.window, GLFW_FOCUSED);
	m_Data.maximized = glfwGetWindowAttrib(m_Data.window, GLFW_MAXIMIZED);
	m_Data.visible = glfwGetWindowAttrib(m_Data.window, GLFW_VISIBLE);
	if ((m_Data.cursorPosX >= 0.0) || (m_Data.cursorPosY >= 0.0))
	{
		if (((int)m_Data.cursorPosX < m_Data.width) || ((int)m_Data.cursorPosY < m_Data.height))
		{
			m_Data.cursorEntered = GL_TRUE;
		}
	}

	glfwSetCharCallback(m_Data.window, &callback_char);
	glfwSetCursorEnterCallback(m_Data.window, &callback_cursor_enter);
	glfwSetCursorPosCallback(m_Data.window, &callback_cursor_pos);
	glfwSetDropCallback(m_Data.window, &callback_drop);
	glfwSetFramebufferSizeCallback(m_Data.window, &callback_framebuffer_size);
	glfwSetKeyCallback(m_Data.window, &callback_key);
	glfwSetMouseButtonCallback(m_Data.window, &callback_mouse_button);
	glfwSetScrollCallback(m_Data.window, &callback_scroll);
	glfwSetWindowCloseCallback(m_Data.window, &callback_window_close);
	glfwSetWindowContentScaleCallback(m_Data.window, &callback_window_content_scale);
	glfwSetWindowFocusCallback(m_Data.window, &callback_window_focus);
	glfwSetWindowIconifyCallback(m_Data.window, &callback_window_iconify);
	glfwSetWindowMaximizeCallback(m_Data.window, &callback_window_maximize);
	glfwSetWindowPosCallback(m_Data.window, &callback_window_pos);
	glfwSetWindowRefreshCallback(m_Data.window, &callback_window_refresh);
	glfwSetWindowSizeCallback(m_Data.window, &callback_window_size);
	glfwSetWindowUserPointer(m_Data.window, this);
}

void Window::callback_char(GLFWwindow* window, unsigned int codepoint)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnChar(codepoint);
	pWindow->m_Data.charCodepoint = codepoint;
}

void Window::callback_cursor_enter(GLFWwindow* window, int entered)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnCursorEnter(entered);
	pWindow->m_Data.cursorEntered = entered;
}

void Window::callback_cursor_pos(GLFWwindow* window, double xpos, double ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnCursorPos(xpos, ypos);
	pWindow->m_Data.cursorPosX = xpos;
	pWindow->m_Data.cursorPosY = ypos;
}

void Window::callback_drop(GLFWwindow* window, int pathcount, const char** paths)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnDrop(pathcount, paths);
}

void Window::callback_framebuffer_size(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (((width != 0) && (width != pWindow->m_Data.framebufferWidth)) ||
		((height != 0) && (height != pWindow->m_Data.framebufferHeight)))
	{
		pWindow->OnFramebufferSize(width, height);
		pWindow->m_Data.framebufferWidth = width;
		pWindow->m_Data.framebufferHeight = height;
	}
}

void Window::callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if ((pWindow->m_Data.close == GLFW_TRUE) && (action == GLFW_RELEASE) && (mods == 0))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE); // FIX: mods stuck on exit
	}
	pWindow->OnKey((KeyCode)key, scancode, (Action)action, (KeyMod)mods);
	pWindow->m_Data.keyCode = key;
	pWindow->m_Data.keyAction = action;
	pWindow->m_Data.keyScancode = scancode;
	pWindow->m_Data.keyMods = mods;
}

void Window::callback_mouse_button(GLFWwindow* window, int button, int action, int mods)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnMouseButton((MouseButton)button, (Action)action, (KeyMod)mods);
	pWindow->m_Data.mouseButton = button;
	pWindow->m_Data.mouseAction = action;
	pWindow->m_Data.keyMods = mods;
}

void Window::callback_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnScroll(xoffset, yoffset);
	pWindow->m_Data.scrollOffsetX = xoffset;
	pWindow->m_Data.scrollOffsetY = yoffset;
}

void Window::callback_window_close(GLFWwindow* window)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (pWindow->m_Data.keyMods != 0)
	{
		pWindow->m_Data.close = GLFW_TRUE; // FIX: mods stuck on exit
		glfwSetWindowShouldClose(window, GLFW_FALSE);
	}
	pWindow->OnClose();
}

void Window::callback_window_content_scale(GLFWwindow* window, float xscale, float yscale)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnContentScale(xscale, yscale);
	pWindow->m_Data.contentScaleX = xscale;
	pWindow->m_Data.contentScaleY = yscale;
}

void Window::callback_window_focus(GLFWwindow* window, int focused)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnFocus(focused);
	pWindow->m_Data.focused = focused;
}

void Window::callback_window_iconify(GLFWwindow* window, int iconified)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnIconify(iconified);
	pWindow->m_Data.iconified = iconified;
}

void Window::callback_window_maximize(GLFWwindow* window, int maximized)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnMaximize(maximized);
	pWindow->m_Data.maximized = maximized;
}

void Window::callback_window_pos(GLFWwindow* window, int xpos, int ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if ((pWindow->m_Data.vidmode == nullptr) &&
		(((xpos != -32000) && (xpos != pWindow->m_Data.posX)) ||
		((ypos != -32000) && (ypos != pWindow->m_Data.posY))))
	{
		pWindow->OnPos(xpos, ypos);
		pWindow->m_Data.posX = xpos;
		pWindow->m_Data.posY = ypos;
	}
}

void Window::callback_window_refresh(GLFWwindow* window)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->OnRefresh();
}

void Window::callback_window_size(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if ((pWindow->m_Data.vidmode == nullptr) &&
		(((width != 0) && (width != pWindow->m_Data.width)) ||
		((height != 0) && (height != pWindow->m_Data.height))))
	{
		pWindow->OnSize(width, height);
		pWindow->m_Data.width = width;
		pWindow->m_Data.height = height;
	}
}

void Window::create_fullscreen(const char* title, Monitor& monitor, GLFWwindow* shared, ContextSetting* setting)
{
	// GLFW WINDOW OBJECT MUST BE EMPTY
	YAGLPP_ASSERT(!IsWindow());

	apply_setting(setting);
	m_Data.vidmode = monitor.GetVideoMode();
	glfwWindowHint(GLFW_RED_BITS, m_Data.vidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, m_Data.vidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, m_Data.vidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, m_Data.vidmode->refreshRate);
	m_Data.window = glfwCreateWindow(m_Data.vidmode->width, m_Data.vidmode->height, title, monitor.Get(), shared);

	// FAILED TO CREATE GLFW WINDOW
	YAGLPP_ASSERT(IsWindow());

	bind_callback();
}

void Window::create_window(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting)
{
	// GLFW WINDOW OBJECT MUST BE EMPTY
	YAGLPP_ASSERT(!IsWindow());

	apply_setting(setting);
	m_Data.window = glfwCreateWindow(width, height, title, nullptr, shared);

	// FAILED TO CREATE GLFW WINDOW
	YAGLPP_ASSERT(IsWindow());

	bind_callback();
}

void Window::Destroy()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	if (m_Data.window)
	{
		OnDestroy();
		glfwDestroyWindow(m_Data.window);
		m_Data.window = nullptr;
	}
}

void Window::Hide()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	m_Data.visible = GLFW_FALSE;
	glfwHideWindow(Get());
}

void Window::MakeContextCurrent()
{
	static bool sGlad = false;
	glfwMakeContextCurrent(Get());
	if (!sGlad)
	{
		gl::yaglpp_glad_load(glfwGetProcAddress);
		sGlad = true;
	}
}

void Window::SetCursorPos(double xpos, double ypos)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetCursorPos(Get(), xpos, ypos);
	m_Data.cursorPosX = xpos;
	m_Data.cursorPosY = ypos;
}

void Window::SetIcon(StbImage& si)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// IVALID IMAGE PIXEL FORMAT
	YAGLPP_ASSERT(si.GetFormat() == StbImage::Format::RgbAlpha8);

	GLFWimage glfwImage = { si.GetWidth(), si.GetHeight(), si.GetPixels() };
	glfwSetWindowIcon(Get(), 1, &glfwImage);
}

void Window::SetMonitor(Monitor& monitor, int xpos, int ypos, int width, int height)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN WINDOWED MODE
	YAGLPP_ASSERT(!IsFullscreen());

	m_Data.vidmode = monitor.GetVideoMode();
	int iWidth = (width == 0) ? m_Data.vidmode->width : width;
	int iHeight = (height == 0) ? m_Data.vidmode->height : height;
	glfwWindowHint(GLFW_RED_BITS, m_Data.vidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, m_Data.vidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, m_Data.vidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, m_Data.vidmode->refreshRate);

	GLFWwindow* pWindow = Get();
	glfwGetWindowPos(pWindow, &m_Data.posX, &m_Data.posY);
	glfwGetWindowSize(pWindow, &m_Data.width, &m_Data.height);
	glfwSetWindowMonitor(pWindow, monitor.Get(), xpos, ypos, iWidth, iHeight, m_Data.vidmode->refreshRate);
}

bool Window::ShouldClose()
{
	bool bClose = (bool)glfwWindowShouldClose(Get());
	if (bClose && m_Data.autodelete && Thread::IsMainCurrent())
	{
		delete this;
	}
	return bClose;
}

void Window::Show()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	m_Data.visible = GLFW_TRUE;
	glfwShowWindow(Get());
}

void Window::UnsetMonitor()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN FULLSCREEN MODE
	YAGLPP_ASSERT(IsFullscreen());

	m_Data.vidmode = nullptr;
	glfwSetWindowMonitor(Get(), nullptr, m_Data.posX, m_Data.posY, m_Data.width, m_Data.height, GLFW_DONT_CARE);
}

void* Window::operator new(std::size_t count)
{
	Thread::SetAlloc();
	return YAGLPP_MALLOC(char, count);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
int Window::get_input_mode(int mode)
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetInputMode(Get(), mode);
}

int Window::get_window_attrib(int attrib)
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetWindowAttrib(Get(), attrib);
}

void Window::set_input_mode(int mode, int value)
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetInputMode(Get(), mode, value);
}

void Window::set_window_attrib(int attrib, int value)
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowAttrib(Get(), attrib, value);
}

void Window::Focus()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// WINDOW SHOULD BE VISIBLE AND NOT ICONIFIED
	YAGLPP_ASSERT(IsVisible() && !IsIconified());

	glfwFocusWindow(Get());
}

_Ret_notnull_ GLFWwindow* Window::Get() const
{
	// WINDOW OBJECT IS EMPTY
	YAGLPP_ASSERT(IsWindow());

	return m_Data.window;
}

_Ret_maybenull_z_ const char* Window::GetClipboardString()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetClipboardString(Get());
}

void Window::GetContentScale()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetWindowContentScale(Get(), &m_Data.contentScaleX, &m_Data.contentScaleY);
}

void Window::GetCursorPos()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetCursorPos(Get(), &m_Data.cursorPosX, &m_Data.cursorPosY);
}

void Window::GetFramebufferSize()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetFramebufferSize(Get(), &m_Data.framebufferWidth, &m_Data.framebufferHeight);
}

Action Window::GetKey(KeyCode key) const
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// KEYBOARD KEY CODE IS NOT ALLOWED
	YAGLPP_ASSERT(key != KeyCode::Unknown);

	return (Action)glfwGetKey(Get(), (int)key);
}

Action Window::GetMouse(MouseButton button)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return (Action)glfwGetMouseButton(Get(), (int)button);
}

void Window::GetFrameSize()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetWindowFrameSize(Get(), &m_Data.frameLeft, &m_Data.frameTop, &m_Data.frameRight, &m_Data.frameBottom);
}

float Window::GetOpacity()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetWindowOpacity(Get());
}

void Window::GetPos()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN WINDOWED MODE
	YAGLPP_ASSERT(!IsFullscreen());

	glfwGetWindowPos(Get(), &m_Data.posX, &m_Data.posY);
}

void Window::GetSize()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN WINDOWED MODE
	YAGLPP_ASSERT(!IsFullscreen());

	glfwGetWindowSize(Get(), &m_Data.width, &m_Data.height);
}

void Window::Iconify()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwIconifyWindow(Get());
}

void Window::Maximize()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwMaximizeWindow(Get());
}

void Window::RequestAttention()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwRequestWindowAttention(Get());
}

void Window::Restore()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwRestoreWindow(Get());
}

void Window::SetAspectRatio(int numer, int denom)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowAspectRatio(Get(), numer, denom);
}

void Window::SetClipboardString(_In_z_ const char* string)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetClipboardString(Get(), string);
}

void Window::SetCursor(Cursor& cursor)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetCursor(Get(), cursor.Get());
}

void Window::SetIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowIcon(Get(), count, images);
}

void Window::SetOpacity(float opacity)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowOpacity(Get(), opacity);
}

void Window::SetPos(int xpos, int ypos)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN WINDOWED MODE
	YAGLPP_ASSERT(!IsFullscreen());

	glfwSetWindowPos(Get(), xpos, ypos);
}

void Window::SetSize(int width, int height)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// MUST BE CALLED IN WINDOWED MODE
	YAGLPP_ASSERT(!IsFullscreen());

	glfwSetWindowSize(Get(), width, height);
}

void Window::SetSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowSizeLimits(Get(), minwidth, minheight, maxwidth, maxheight);
}

void Window::SetTitle(_In_z_ const char* title)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowTitle(Get(), title);
}

void Window::UnsetAspectRatio()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowAspectRatio(Get(), GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void Window::UnsetCursor()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetCursor(Get(), nullptr);
}

void Window::UnsetIcon()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetWindowIcon(Get(), 0, nullptr);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#if defined (YAGLPP_DEBUG_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)
_Ret_maybenull_z_ const char* Window::GetTitle()
{
	// MUST BE CALLED FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetWindowTitle(Get());
}
#endif // #if defined (YAGLPP_DEBUG_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline int Window::get_input_mode(int mode)
{
	return glfwGetInputMode(m_Data.window, mode);
}

inline int Window::get_window_attrib(int attrib)
{
	return glfwGetWindowAttrib(m_Data.window, attrib);
}

inline void Window::set_input_mode(int mode, int value)
{
	glfwSetInputMode(m_Data.window, mode, value);
}

inline void Window::set_window_attrib(int attrib, int value)
{
	glfwSetWindowAttrib(m_Data.window, attrib, value);
}

inline void Window::Focus()
{
	glfwFocusWindow(m_Data.window);
}

inline _Ret_notnull_ GLFWwindow* Window::Get() const
{
	return m_Data.window;
}

inline _Ret_maybenull_z_ const char* Window::GetClipboardString()
{
	return glfwGetClipboardString(m_Data.window);
}

inline void Window::GetCursorPos()
{
	glfwGetCursorPos(m_Data.window, &m_Data.cursorPosX, &m_Data.cursorPosY);
}

inline void Window::GetFramebufferSize()
{
	glfwGetFramebufferSize(m_Data.window, &m_Data.framebufferWidth, &m_Data.framebufferHeight);
}

inline Action Window::GetKey(KeyCode key) const
{
	return (Action)glfwGetKey(m_Data.window, (int)key);
}

inline Action Window::GetMouse(MouseButton button)
{
	return (Action)glfwGetMouseButton(m_Data.window, (int)button);
}

inline void Window::GetContentScale()
{
	glfwGetWindowContentScale(m_Data.window, &m_Data.contentScaleX, &m_Data.contentScaleY);
}

inline void Window::GetFrameSize()
{
	glfwGetWindowFrameSize(m_Data.window, &m_Data.frameLeft, &m_Data.frameTop, &m_Data.frameRight, &m_Data.frameBottom);
}

inline float Window::GetOpacity()
{
	return glfwGetWindowOpacity(m_Data.window);
}

inline void Window::GetPos()
{
	glfwGetWindowPos(m_Data.window, &m_Data.posX, &m_Data.posY);
}

inline void Window::GetSize()
{
	glfwGetWindowSize(m_Data.window, &m_Data.width, &m_Data.height);
}

inline void Window::Iconify()
{
	glfwIconifyWindow(m_Data.window);
}

inline void Window::Maximize()
{
	glfwMaximizeWindow(m_Data.window);
}

inline void Window::RequestAttention()
{
	glfwRequestWindowAttention(m_Data.window);
}

inline void Window::Restore()
{
	glfwRestoreWindow(m_Data.window);
}

inline void Window::SetClipboardString(_In_z_ const char* string)
{
	glfwSetClipboardString(m_Data.window, string);
}

inline void Window::SetCursor(Cursor& cursor)
{
	glfwSetCursor(m_Data.window, cursor.Get());
}

inline void Window::SetAspectRatio(int numer, int denom)
{
	glfwSetWindowAspectRatio(m_Data.window, numer, denom);
}

inline void Window::SetIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	glfwSetWindowIcon(m_Data.window, count, images);
}

inline void Window::SetOpacity(float opacity)
{
	glfwSetWindowOpacity(m_Data.window, opacity);
}

inline void Window::SetPos(int xpos, int ypos)
{
	glfwSetWindowPos(m_Data.window, xpos, ypos);
}

inline void Window::SetSize(int width, int height)
{
	glfwSetWindowSize(m_Data.window, width, height);
}

inline void Window::SetSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
{
	glfwSetWindowSizeLimits(m_Data.window, minwidth, minheight, maxwidth, maxheight);
}

inline void Window::SetTitle(_In_z_ const char* title)
{
	glfwSetWindowTitle(m_Data.window, title);
}

inline void Window::UnsetAspectRatio()
{
	glfwSetWindowAspectRatio(m_Data.window, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

inline void Window::UnsetCursor()
{
	glfwSetCursor(m_Data.window, nullptr);
}

inline void Window::UnsetIcon()
{
	glfwSetWindowIcon(m_Data.window, 0, nullptr);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_INLINE_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)
inline _Ret_maybenull_z_ const char* Window::GetTitle()
{
	return glfwGetWindowTitle(m_Data.window);
}
#endif // #if defined (YAGLPP_INLINE_IMPLEMENTATION) && defined (YAGLPP_NO_GLFW_LEGACY)
} // namespace glfw
#endif // #ifndef YAGLPP_WINDOW_H
