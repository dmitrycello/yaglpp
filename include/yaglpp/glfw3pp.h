#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_GLFW3PP_H
#define YAGLPP_GLFW3PP_H
#include <GLFW/glfw3.h>

#ifdef YAGLPP_NO_GLFW_LEGACY
	#if (GLFW_VERSION_MINOR < 4)
		#error "GLFW non-legacy version 3.4+ required"
	#endif
#else
	#if (GLFW_VERSION_MINOR != 3) || (GLFW_VERSION_REVISION != 10)
		#error "GLFW legacy version 3.3.10 required"
	#endif
	#if defined(YAGLPP_MSVC) && defined(YAGLPP_IMPLEMENTATION)
		#pragma message("YAGL++: Compiling with GLFW 3.3.10 legacy version support...")
	#endif
#endif

/*YAGL++ GLFW library namespace*/
namespace glfw {
class Thread;
class Cursor;
class Monitor;
class Joystick;
class Window;
void window_hint(int hint, int value);
void window_hint_string(int hint, const char* value);

/*GLFW joystick, key or mouse action enumerator*/
enum class Action : int
{
	/*The joystick, key or mouse button was released*/
	Release = GLFW_RELEASE,

	/*The joystick, key or mouse button was pressed*/
	Press = GLFW_PRESS,

	/*The key was held down until it repeated*/
	Repeat = GLFW_REPEAT,
};

/*GLFW context client API enumerator*/
enum class ClientApi : int
{
	/*No API value. Create the context without API. This is a hard constraint*/
	NoApi = GLFW_NO_API,

	/*Standard OpenGL API value (default). Create the context for the OpenGL client API. This is a hard constraint*/
	Opengl = GLFW_OPENGL_API,

	/*OpenGL ES API value. Create the context for the OpenGL ES client API. This is a hard constraint*/
	OpenglEs = GLFW_OPENGL_ES_API,
};

/*Context creation API enumerator*/
enum class ContextApi : int
{
	/*Native context API value (default). Indicates that native context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	Native = GLFW_NATIVE_CONTEXT_API,

	/*EGL context API value. Indicates that EGL context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	Egl = GLFW_EGL_CONTEXT_API,

	/*OSMesa context API vakue. Indicates that OSMesa context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	Osmesa = GLFW_OSMESA_CONTEXT_API,
};

/*GLFW  context robustness strategy enumerator*/
enum class ContextRobustness : int
{
	/*Lose context on reset value. Imply robustness strategy used by the context with recovery from hardware errors*/
	LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET,

	/*No reset notification value. Imply robustness strategy used by the context without recovery from hardware errors*/
	NoResetNotification = GLFW_NO_RESET_NOTIFICATION,

	/*No robustness value (default). No robustness strategy is used by the context*/
	NoRobustness = GLFW_NO_ROBUSTNESS,
};

/*GLFW keyboard key code enumerator*/
enum class KeyCode : int
{
	/*Keyboard key <Unknown>*/
	Unknown = GLFW_KEY_UNKNOWN,

	/*Keyboard key <Space>*/
	Space = GLFW_KEY_SPACE,

	/*Keyboard key <'>*/
	Apostrophe = GLFW_KEY_APOSTROPHE,

	/*Keyboard key <,>*/
	Comma = GLFW_KEY_COMMA,

	/*Keyboard key <->*/
	Minus = GLFW_KEY_MINUS,

	/*Keyboard key <.>*/
	Period = GLFW_KEY_PERIOD,

	/*Keyboard key </>*/
	Slash = GLFW_KEY_SLASH,

	/*Keyboard key <0>*/
	Key0 = GLFW_KEY_0,

	/*Keyboard key <1>*/
	Key1 = GLFW_KEY_1,

	/*Keyboard key <2>*/
	Key2 = GLFW_KEY_2,

	/*Keyboard key <3>*/
	Key3 = GLFW_KEY_3,

	/*Keyboard key <4>*/
	Key4 = GLFW_KEY_4,

	/*Keyboard key <5>*/
	Key5 = GLFW_KEY_5,

	/*Keyboard key <6>*/
	Key6 = GLFW_KEY_6,

	/*Keyboard key <7>*/
	Key7 = GLFW_KEY_7,

	/*Keyboard key <8>*/
	Key8 = GLFW_KEY_8,

	/*Keyboard key <9>*/
	Key9 = GLFW_KEY_9,

	/*Keyboard key <:>*/
	Semicolon = GLFW_KEY_SEMICOLON,

	/*Keyboard key <=>*/
	Equal = GLFW_KEY_EQUAL,

	/*Keyboard key <A>*/
	A = GLFW_KEY_A,

	/*Keyboard key <B>*/
	B = GLFW_KEY_B,

	/*Keyboard key <C>*/
	C = GLFW_KEY_C,

	/*Keyboard key <D>*/
	D = GLFW_KEY_D,

	/*Keyboard key <E>*/
	E = GLFW_KEY_E,

	/*Keyboard key <F>*/
	F = GLFW_KEY_F,

	/*Keyboard key <G>*/
	G = GLFW_KEY_G,

	/*Keyboard key <H>*/
	H = GLFW_KEY_H,

	/*Keyboard key <I>*/
	I = GLFW_KEY_I,

	/*Keyboard key <J>*/
	J = GLFW_KEY_J,

	/*Keyboard key <K>*/
	K = GLFW_KEY_K,

	/*Keyboard key <L>*/
	L = GLFW_KEY_L,

	/*Keyboard key <M>*/
	M = GLFW_KEY_M,

	/*Keyboard key <N>*/
	N = GLFW_KEY_N,

	/*Keyboard key <O>*/
	O = GLFW_KEY_O,

	/*Keyboard key <P>*/
	P = GLFW_KEY_P,

	/*Keyboard key <Q>*/
	Q = GLFW_KEY_Q,

	/*Keyboard key <R>*/
	R = GLFW_KEY_R,

	/*Keyboard key <S>*/
	S = GLFW_KEY_S,

	/*Keyboard key <T>*/
	T = GLFW_KEY_T,

	/*Keyboard key <U>*/
	U = GLFW_KEY_U,

	/*Keyboard key <V>*/
	V = GLFW_KEY_V,

	/*Keyboard key <W>*/
	W = GLFW_KEY_W,

	/*Keyboard key <X>*/
	X = GLFW_KEY_X,

	/*Keyboard key <Y>*/
	Y = GLFW_KEY_Y,

	/*Keyboard key <Z>*/
	Z = GLFW_KEY_Z,

	/*Keyboard key <[>*/
	LeftBracket = GLFW_KEY_LEFT_BRACKET,

	/*Keyboard key <\>*/
	Backslash = GLFW_KEY_BACKSLASH,

	/*Keyboard key <]>*/
	RightBracket = GLFW_KEY_RIGHT_BRACKET,

	/*Keyboard key <`>*/
	GraveAccent = GLFW_KEY_GRAVE_ACCENT,

	/*Keyboard key <World1>*/
	World1 = GLFW_KEY_WORLD_1,

	/*Keyboard key <World2>*/
	World2 = GLFW_KEY_WORLD_2,

	/*Keyboard key <Escape>*/
	Escape = GLFW_KEY_ESCAPE,

	/*Keyboard key <Enter>*/
	Enter = GLFW_KEY_ENTER,

	/*Keyboard key <Tab>*/
	Tab = GLFW_KEY_TAB,

	/*Keyboard key <Backspace>*/
	Backspace = GLFW_KEY_BACKSPACE,

	/*Keyboard key <Insert>*/
	Insert = GLFW_KEY_INSERT,

	/*Keyboard key <Delete>*/
	Delete = GLFW_KEY_DELETE,

	/*Keyboard key <Right>*/
	Right = GLFW_KEY_RIGHT,

	/*Keyboard key <Left>*/
	Left = GLFW_KEY_LEFT,

	/*Keyboard key <Down>*/
	Down = GLFW_KEY_DOWN,

	/*Keyboard key <Up>*/
	Up = GLFW_KEY_UP,

	/*Keyboard key <PageUp>*/
	PageUp = GLFW_KEY_PAGE_UP,

	/*Keyboard key <PageDown>*/
	PageDown = GLFW_KEY_PAGE_DOWN,

	/*Keyboard key <Home>*/
	Home = GLFW_KEY_HOME,

	/*Keyboard key <End>*/
	End = GLFW_KEY_END,

	/*Keyboard key <CapsLock>*/
	CapsLock = GLFW_KEY_CAPS_LOCK,

	/*Keyboard key <ScrollLock>*/
	ScrollLock = GLFW_KEY_SCROLL_LOCK,

	/*Keyboard key <Numlock>*/
	NumLock = GLFW_KEY_NUM_LOCK,

	/*Keyboard key <PrintScreen>*/
	PrintScreen = GLFW_KEY_PRINT_SCREEN,

	/*Keyboard key <Pause>*/
	Pause = GLFW_KEY_PAUSE,

	/*Keyboard key <F1>*/
	F1 = GLFW_KEY_F1,

	/*Keyboard key <F2>*/
	F2 = GLFW_KEY_F2,

	/*Keyboard key <F3>*/
	F3 = GLFW_KEY_F3,

	/*Keyboard key <F4>*/
	F4 = GLFW_KEY_F4,

	/*Keyboard key <F5>*/
	F5 = GLFW_KEY_F5,

	/*Keyboard key <F6>*/
	F6 = GLFW_KEY_F6,

	/*Keyboard key <F7>*/
	F7 = GLFW_KEY_F7,

	/*Keyboard key <F8>*/
	F8 = GLFW_KEY_F8,

	/*Keyboard key <F9>*/
	F9 = GLFW_KEY_F9,

	/*Keyboard key <F10>*/
	F10 = GLFW_KEY_F10,

	/*Keyboard key <F11>*/
	F11 = GLFW_KEY_F11,

	/*Keyboard key <F12>*/
	F12 = GLFW_KEY_F12,

	/*Keyboard key <F13>*/
	F13 = GLFW_KEY_F13,

	/*Keyboard key <F14>*/
	F14 = GLFW_KEY_F14,

	/*Keyboard key <F15>*/
	F15 = GLFW_KEY_F15,

	/*Keyboard key <F16>*/
	F16 = GLFW_KEY_F16,

	/*Keyboard key <F17>*/
	F17 = GLFW_KEY_F17,

	/*Keyboard key <F18>*/
	F18 = GLFW_KEY_F18,

	/*Keyboard key <F19>*/
	F19 = GLFW_KEY_F19,

	/*Keyboard key <F20>*/
	F20 = GLFW_KEY_F20,

	/*Keyboard key <F21>*/
	F21 = GLFW_KEY_F21,

	/*Keyboard key <F22>*/
	F22 = GLFW_KEY_F22,

	/*Keyboard key <F23>*/
	F23 = GLFW_KEY_F23,

	/*Keyboard key <F24>*/
	F24 = GLFW_KEY_F24,

	/*Keyboard key <F25>*/
	F25 = GLFW_KEY_F25,

	/*Keyboard key pad <0>*/
	Kp0 = GLFW_KEY_KP_0,

	/*Keyboard key pad <1>*/
	Kp1 = GLFW_KEY_KP_1,

	/*Keyboard key pad <2>*/
	Kp2 = GLFW_KEY_KP_2,

	/*Keyboard key pad <3>*/
	Kp3 = GLFW_KEY_KP_3,

	/*Keyboard key pad <4>*/
	Kp4 = GLFW_KEY_KP_4,

	/*Keyboard key pad <5>*/
	Kp5 = GLFW_KEY_KP_5,

	/*Keyboard key pad <6>*/
	Kp6 = GLFW_KEY_KP_6,

	/*Keyboard key pad <7>*/
	Kp7 = GLFW_KEY_KP_7,

	/*Keyboard key pad <8>*/
	Kp8 = GLFW_KEY_KP_8,

	/*Keyboard key pad <9>*/
	Kp9 = GLFW_KEY_KP_9,

	/*Keyboard key pad <Decimal>*/
	KpDecimal = GLFW_KEY_KP_DECIMAL,

	/*Keyboard key pad <Divide>*/
	KpDivide = GLFW_KEY_KP_DIVIDE,

	/*Keyboard key pad <Multiply>*/
	KpMultiply = GLFW_KEY_KP_MULTIPLY,

	/*Keyboard key pad <Subtract>*/
	KpSubtract = GLFW_KEY_KP_SUBTRACT,

	/*Keyboard key pad <Add>*/
	KpAdd = GLFW_KEY_KP_ADD,

	/*Keyboard key pad <Enter>*/
	KpEnter = GLFW_KEY_KP_ENTER,

	/*Keyboard key pad <Equal>*/
	KpEqual = GLFW_KEY_KP_EQUAL,

	/*Keyboard key <LeftShift>*/
	LeftShift = GLFW_KEY_LEFT_SHIFT,

	/*Keyboard key <LeftControl>*/
	LeftControl = GLFW_KEY_LEFT_CONTROL,

	/*Keyboard key <LeftAlt>*/
	LeftAlt = GLFW_KEY_LEFT_ALT,

	/*Keyboard key <LeftSuper>*/
	LeftSuper = GLFW_KEY_LEFT_SUPER,

	/*Keyboard key <RightShift>*/
	RightShift = GLFW_KEY_RIGHT_SHIFT,

	/*Keyboard key <RightControl>*/
	RightControl = GLFW_KEY_RIGHT_CONTROL,

	/*Keyboard key <RightAlt>*/
	RightAlt = GLFW_KEY_RIGHT_ALT,

	/*Keyboard key <RightSuper>*/
	RightSuper = GLFW_KEY_RIGHT_SUPER,

	/*Keyboard key <Menu>*/
	Menu = GLFW_KEY_MENU,

	/*Keyboard key <Last>*/
	Last = GLFW_KEY_LAST,
};

/*GLFW keyboard key modifier enumerator*/
enum class KeyMod : int
{
	/*No modifier key were held down*/
	None = 0,

	/*If this bit is set, one or more Shift keys were held down*/
	Shift = GLFW_MOD_SHIFT,

	/*If this bit is set, one or more Control keys were held down*/
	Control = GLFW_MOD_CONTROL,

	/*If this bit is set, one or more Alt keys were held down*/
	Alt = GLFW_MOD_ALT,

	/*If this bit is set, one or more Super keys were held down*/
	Super = GLFW_MOD_SUPER,

	/*If this bit is set, the Caps Lock key is enabled and <LockKeyMods> input mode is set*/
	CapsLock = GLFW_MOD_CAPS_LOCK,

	/*If this bit is set, the Num Lock key is enabled and the <LockKeyMods> input mode is set*/
	NumLock = GLFW_MOD_NUM_LOCK,
};

/*GLFW mouse button enumerator*/
enum class MouseButton : int
{
	/*Mouse button 1 value. Left mouse button on most of the hardware*/
	Button1 = GLFW_MOUSE_BUTTON_1,

	/*Mouse button 2 value. Right mouse button on most of the hardware*/
	Button2 = GLFW_MOUSE_BUTTON_2,

	/*Mouse button 3 value. Middle mouse button on most of the hardware*/
	Button3 = GLFW_MOUSE_BUTTON_3,

	/*Mouse button 4 value. Back mouse button on most of the hardware*/
	Button4 = GLFW_MOUSE_BUTTON_4,

	/*Mouse button 5 value. Forward mouse button on most of the hardware*/
	Button5 = GLFW_MOUSE_BUTTON_5,

	/*Mouse button 6 value. Auxiliary mouse button on the modern hardware*/
	Button6 = GLFW_MOUSE_BUTTON_6,

	/*Mouse button 7 value. Auxiliary mouse button on the modern hardware*/
	Button7 = GLFW_MOUSE_BUTTON_7,

	/*Mouse button 8 value. Last available mouse button on the modern hardware*/
	Button8 = GLFW_MOUSE_BUTTON_8,

	/*Left mouse button value*/
	Left = GLFW_MOUSE_BUTTON_LEFT,

	/*Right mouse button value*/
	Right = GLFW_MOUSE_BUTTON_RIGHT,

	/*Middle mouse button value*/
	Middle = GLFW_MOUSE_BUTTON_MIDDLE,

	/*Last available mouse button value*/
	Last = GLFW_MOUSE_BUTTON_LAST,
};

/*GLFW context OpenGL profile enumerator*/
enum class OpenglProfile : int
{
	/*OpenGL any profile value (default). Indicates any OpenGL profile used by the context. This value is used if the context uses a known profile. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	Any = GLFW_OPENGL_ANY_PROFILE,

	/*OpenGL core profile value. Indicates the Core OpenGL profile used by the context. This value is used if the OpenGL profile is unknown or the context is an OpenGL ES context. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	Core = GLFW_OPENGL_CORE_PROFILE,

	/*OpenGL compatible profile value. Indicates the Compat OpenGL profile used by the context. This value is used if the context uses a known profile. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	Compat = GLFW_OPENGL_COMPAT_PROFILE,
};

/*GLFW context release behavior enumerator*/
enum class ContextReleaseBehavior : int
{
	/*Any release behavior value (default). Indicates that the default behavior of the context creation API will be used*/
	Any = GLFW_ANY_RELEASE_BEHAVIOR,

	/*Release behavior flush value. Indicates that the pipeline will be flushed whenever the context is released from being the current one*/
	Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,

	/*Release behavior none value. Indicates that the pipeline will not be flushed on release*/
	None = GLFW_RELEASE_BEHAVIOR_NONE,
};

#ifdef YAGLPP_NO_GLFW_LEGACY
/*GLFW platform type (rendering backend) enumerator*/
enum class AnglePlatformType : int
{
	/*Specifies the None platform type (default) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	None = GLFW_ANGLE_PLATFORM_TYPE_NONE,

	/*Specifies the OpenGL platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	Opengl = GLFW_ANGLE_PLATFORM_TYPE_OPENGL,

	/*Specifies the OpenGL ES platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	Opengles = GLFW_ANGLE_PLATFORM_TYPE_OPENGLES,

	/*Specifies the D3D9 platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	D3d9 = GLFW_ANGLE_PLATFORM_TYPE_D3D9,

	/*Specifies the D3D11 platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	D3d11 = GLFW_ANGLE_PLATFORM_TYPE_D3D11,

	/*Specifies the Vulkan platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	Vulkan = GLFW_ANGLE_PLATFORM_TYPE_VULKAN,

	/*Specifies the Metal platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	Metal = GLFW_ANGLE_PLATFORM_TYPE_METAL,
};

/*GLFW platform selection enumerator*/
enum class Platform : int
{
	/*Automatic platform selection, default value*/
	Any = GLFW_ANY_PLATFORM,

	/*Win32 platform selection*/
	Win32 = GLFW_PLATFORM_WIN32,

	/*Cocoa platform selection*/
	Cocoa = GLFW_PLATFORM_COCOA,

	/*Wayland platform selection*/
	Wayland = GLFW_PLATFORM_WAYLAND,

	/*X11 platform selection*/
	X11 = GLFW_PLATFORM_X11,

	/*Null platform selection, which is always supported but needs to be explicitly requested*/
	Null = GLFW_PLATFORM_NULL,
};

/*GLFW Wayland libdecor usage enumerator*/
enum class WaylandLibdecor : int
{
	/*Prefer to use libdecor for window decorations where available on Wayland platforms. This is ignored on other platforms*/
	Prefer = GLFW_WAYLAND_PREFER_LIBDECOR,

	/*Disable libdecor for window decorations on Wayland platforms. This is ignored on other platforms*/
	Disable = GLFW_WAYLAND_DISABLE_LIBDECOR,
};
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

/*Constant expression <KeyMod> bitwise OR operator combining multiple key modifiers into mod mask
@param Key modifier enumerator 1
@param Key modifier enumerator 2
@return Resulting key modifier enumerator*/
constexpr KeyMod operator | (KeyMod mod1, KeyMod mod2)
{
	return (KeyMod)((int)mod1 | (int)mod2);
}

/*Constant expression <KeyMod> bitwise AND operator verifying if mod exists in the mod mask
@param Key modifier enumerator
@param Key modifier mask enumerator
@return True if key modifier exists in the key modifier mask, false otherwise*/
constexpr bool operator & (KeyMod mod, KeyMod mask)
{
	return (bool)((int)mod & (int)mask);
}

/*(M) This function resets all window hints to their default values. This function must only be called from the main thread*/
void DefaultWindowHints();

/*This function returns whether the specified API extension is supported by the current OpenGL or OpenGL ES context. This function may be called from any thread
@param [in] The ASCII encoded name of the extension
@return True if the extension is available, or false otherwise*/
inline bool ExtensionSupported(_In_z_ const char* extension)
{
	return glfwExtensionSupported(extension) == GLFW_TRUE;
}

/*This function returns the pointer to window object whose OpenGL or OpenGL ES context is current on the calling thread
@return The pointer to current context window object, or NULL*/
_Ret_maybenull_ Window* GetCurrentContext();

/*(M) (1) This function returns the name of the specified printable key by its scancode, encoded as UTF-8. This function must only be called from the main thread
@param The scancode of the printable key to query
@return The UTF-8 encoded, layout-specific name of the key string, or NULL*/
_Ret_maybenull_ const char* GetKeyName(int scancode);

/*(M) (2) This function returns the name of the specified printable key, encoded as UTF-8. This function must only be called from the main thread
@param The enumerator of the printable key to query
@return The UTF-8 encoded, layout-specific name of the key string, or NULL*/
_Ret_maybenull_ const char* GetKeyName(KeyCode key);

/*This function returns the platform-specific scancode of the specified key. If the key is <Unknown> or does not exist on the keyboard this method will return -1. This function may be called from any thread
@param Keyboard key enumerator
@return Keyboard key platform-specific scancode*/
inline int GetKeyScancode(KeyCode key)
{
	return glfwGetKeyScancode((int)key);
}

/*This function returns the current GLFW time, in seconds, elapsed since GLFW was initialized, or since last call to <SetTime>. This function may be called from secondary threads
@return The current time, in seconds, or zero if an error occured*/
inline double GetTime()
{
	return glfwGetTime();
}

/*This function returns the time delta, in microseconds, elapsed since last function call. This function may be called from secondary threads
@return The time delta, in seconds. Initial value is 0.0*/
double GetTimeDelta();

/*This function returns the frequency, in Hz, of the raw timer. This function may be called from any thread
@return The frequency of the timer, in Hz, or zero if an error occurred*/
inline uint64_t GetTimerFrequency()
{
	return glfwGetTimerFrequency();
}

/*This function returns the current value of the raw timer, measured in 1/frequency seconds. To get the frequency, call <GetTimerFrequency>. This function may be called from any thread
@return The value of the timer, or zero if an error occurred*/
inline uint64_t GetTimerValue()
{
	return glfwGetTimerValue();
}

/*Returns a string describing the compile-time configuration. This function may be called from any thread
@return The ASCII encoded GLFW version string*/
_Ret_z_ inline const char* GetVersionString()
{
	return glfwGetVersionString();
}

/*Checks if any window's OpenGL or OpenGL ES context is current on the calling thread
@return True if any context window on the calling thread, false otherwise*/
inline bool IsCurrectContext()
{
	return glfwGetCurrentContext() != nullptr;
}

/*(M) This function returns whether raw mouse motion is supported on the current system. This function must only be called from the main thread
@return True if raw mouse motion is supported on the current machine, false otherwise*/
bool IsRawMouseMotionSupported();

/*(M) This function processes only those events that are already in the event queue and then returns immediately. This function must not be called from a callback, and must only be called from the main thread*/
void PollEvents();

/*This function posts an empty event from the current thread to the event queue, causing <WaitEvents> or <WaitEventsTimeout> to return. This function may be called from any thread*/
inline void PostEmptyEvent()
{
	glfwPostEmptyEvent();
}

/*(M) Specifies alpha bits window hint value (default 8). Sets the desired bit depths of the alpha component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Alpha bits window hint value*/
inline void SetAlphaBits(int value)
{
	window_hint(GLFW_ALPHA_BITS, value);
}

/*(M) Specifies auto iconify window hint flag (default true). Sets whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This hint is ignored for windowed mode windows. This function must only be called from the main thread
@param Auto iconify window hint flag*/
inline void SetAutoIconify(bool flag)
{
	window_hint(GLFW_AUTO_ICONIFY, (int)flag);
}

/*(M) Specifies blue bits window hint value (default 8). Sets the desired bit depths of the blue component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Blue bits window hint value*/
inline void SetBlueBits(int value)
{
	window_hint(GLFW_BLUE_BITS, value);
}

/*(M) Specifies center cursor window hint flag (default true). Sets whether the cursor should be centered over newly created full screen windows. This hint is ignored for windowed mode windows. This function must only be called from the main thread
@param Center cursor window hint flag*/
inline void SetCenterCursor(bool flag)
{
	window_hint(GLFW_CENTER_CURSOR, (int)flag);
}

/*(M) Specifies client API window hint value, default <Opengl>. This function must only be called from the main thread
@param The client API window hint enumerator*/
inline void SetClientApi(ClientApi value)
{
	window_hint(GLFW_CLIENT_API, (int)value);
}

/*(M) Specifies cocoa frame name window hint (default ""). Sets the UTF-8 encoded name to use for autosaving the window frame, or if empty disables frame autosaving for the window. This is ignored on other platforms. This function must only be called from the main thread
@param Cocoa frame name window hint string*/
inline void SetCocoaFrameName(_In_z_ const char* name)
{
	window_hint_string(GLFW_COCOA_FRAME_NAME, name);
}

/*(M) Specifies cocoa graphics switching window hint flag (default false). Sets whether to in Automatic Graphics Switching, i.e. to allow the system to choose the integrated GPU for the OpenGL context and move it between GPUs if necessary or whether to force it to always run on the discrete GPU. This only affects systems with both integrated and discrete GPUs. This is ignored on other platforms. Simpler programs and tools may want to enable this to save power, while games and other applications performing advanced rendering will want to leave it disabled. This function must only be called from the main thread
@param Cocoa graphics switching window hint flag*/
inline void SetCocoaGraphicsSwitching(bool flag)
{
	window_hint(GLFW_COCOA_GRAPHICS_SWITCHING, (int)flag);
}

/*(M) Specifies cocoa retina framebuffer window hint flag (default true). Sets whether to use full resolution framebuffers on Retina displays. This is ignored on other platforms. This function must only be called from the main thread
@param Cocoa retina framebuffer window hint flag*/
inline void SetCocoaRetinaFramebuffer(bool flag)
{
	window_hint(GLFW_COCOA_RETINA_FRAMEBUFFER, (int)flag);
}

/*(M) Specifies context release behavior window hint value, default <Any>. This function must only be called from the main thread
@param The context release behavior window hint enumerator*/
inline void SetContextReleaseBehavior(ContextReleaseBehavior value)
{
	window_hint(GLFW_CONTEXT_RELEASE_BEHAVIOR, (int)value);
}

/*(M) Specifies context version major window hint value (default 1). Indicates the client API major version of the window's context. This function must only be called from the main thread
@param Context version major window hint value*/
inline void SetContextVersionMajor(int value)
{
	window_hint(GLFW_CONTEXT_VERSION_MAJOR, value);
}

/*(M) Specifies context version minor window hint value (default 0). Indicates the client API minor version of the window's context. This function must only be called from the main thread
@param Context version minor window hint value*/
inline void SetContextVersionMinor(int value)
{
	window_hint(GLFW_CONTEXT_VERSION_MINOR, value);
}

/*(M) Specifies context creation API window hint value, defailt <Native>. This function must only be called from the main thread
@param The context creation API window hint enumerator*/
inline void SetContextCreationApi(ContextApi value)
{
	window_hint(GLFW_CONTEXT_CREATION_API, (int)value);
}

/*(M) Specifies context no error window hint flag (default false). Sets whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior. This function must only be called from the main thread
@param Context no error window hint flag*/
inline void SetContextNoError(bool flag)
{
	window_hint(GLFW_CONTEXT_NO_ERROR, (int)flag);
}

/*(M) Specifies context robustness window hint value (default NoRobustness). This function must only be called from the main thread
@param The context robustness window hint enumerator*/
inline void SetContextRobustness(ContextRobustness value)
{
	window_hint(GLFW_CONTEXT_ROBUSTNESS, (int)value);
}

/*(M) Specifies decorated window hint flag (default true). Sets whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This hint is ignored for full screen windows. This function must only be called from the main thread
@param Decorated window hint flag*/
inline void SetDecorated(bool flag)
{
	window_hint(GLFW_DECORATED, (int)flag);
}

/*(M) Specifies depth bits window hint value (default 24). Sets the depth bits component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Depth bits window hint value*/
inline void SetDepthBits(int value)
{
	window_hint(GLFW_DEPTH_BITS, value);
}

/*(M) Specifies double buffer window hint flag (default true). Sets whether the framebuffer should be double buffered. You nearly always want to use double buffering. This is a hard constraint. This function must only be called from the main thread
@param Double buffer window hint flag*/
inline void SetDoublebuffer(bool flag)
{
	window_hint(GLFW_DOUBLEBUFFER, (int)flag);
}

/*(M) Specifies floating window hint flag (default false). Sets whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This hint is ignored for full screen windows. This function must only be called from the main thread
@param Floating window hint flag*/
inline void SetFloating(bool flag)
{
	window_hint(GLFW_FLOATING, (int)flag);
}

/*(M) Specifies focused window hint flag (default true). Sets whether the windowed mode window will be given input focus when created. This hint is ignored for full screen and initially hidden windows. This function must only be called from the main thread
@param Focused window hint flag*/
inline void SetFocused(bool flag)
{
	window_hint(GLFW_FOCUSED, (int)flag);
}

/*(M) Specifies focus on show window hint flag (default true). Sets whether the window will be given input focus when <Show> is called. This function must only be called from the main thread
@param Focus on show window hint flag*/
inline void SetFocusOnShow(bool flag)
{
	window_hint(GLFW_FOCUS_ON_SHOW, (int)flag);
}

/*(M) Specifies green bits window hint value (default 8). Sets the desired bit depths of the green component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Green bits window hint value*/
inline void SetGreenBits(int value)
{
	window_hint(GLFW_GREEN_BITS, value);
}

/*(M) Specifies window hint flag (default false). Sets whether the windowed mode window will be maximized when created. This hint is ignored for full screen windows. This function must only be called from the main thread
@param Maximized window hint flag*/
inline void SetMaximized(bool flag)
{
	window_hint(GLFW_MAXIMIZED, (int)flag);
}

/*(M) Specifies OpenGL debug context window hint flag (default false). This is an alias to context debug flag for compatibility with earlier versions. This function must only be called from the main thread
@param OpenGL debug context window hint flag*/
inline void SetOpenglDebugContext(bool flag)
{
	window_hint(GLFW_OPENGL_DEBUG_CONTEXT, (int)flag);
}

/*(M) Specifies OpenGL forward compatible window hint flag (default false). Sets whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored. This function must only be called from the main thread
@param OpenGL forward compatible window hint flag*/
inline void SetOpenglForwardCompat(bool flag)
{
	window_hint(GLFW_OPENGL_FORWARD_COMPAT, (int)flag);
}

/*(M) Specifies OpenGL profile window hint value (default OpenglAnyProfile). This function must only be called from the main thread
@param The OpenGL profile window hint enumerator*/
inline void SetOpenglProfile(OpenglProfile value)
{
	window_hint(GLFW_OPENGL_PROFILE, (int)value);
}

/*(M) Specifies red bits window hint value (default 8). Sets the desired bit depths of the red component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Red bits window hint value*/
inline void SetRedBits(int value)
{
	window_hint(GLFW_RED_BITS, value);
}

/*(M) Specifies refresh rate window hint value (default GLFW_DONT_CARE). Sets the desired refresh rate for full screen windows. A value of GLFW_DONT_CARE means the highest available refresh rate will be used. This hint is ignored for windowed mode windows. This function must only be called from the main thread
@param Refresh rate window hint value*/
inline void SetRefreshRate(int value)
{
	window_hint(GLFW_REFRESH_RATE, value);
}

/*(M) Specifies resizable window hint flag (default true). Sets whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This hint is ignored for full screen and undecorated windows. This function must only be called from the main thread
@param Resizable window hint flag*/
inline void SetResizable(bool flag)
{
	window_hint(GLFW_RESIZABLE, (int)flag);
}

/*(M) Specifies samples window hint value (default 0). Sets the desired number of samples to use for multisampling. Zero disables multisampling. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Samples window hint value*/
inline void SetSamples(int value)
{
	window_hint(GLFW_SAMPLES, value);
}

/*(M) Sets whether the window content area should be resized based on the monitor content scale of any monitor it is placed on. This includes the initial placement when the window is created. This hint only has an effect on platforms where screen coordinates and pixels always map 1:1 such as Windows and X11.On platforms like macOS the resolution of the framebuffer is changed independently of the window size. This function must only be called from the main thread
@param Scale to monitor window hint flag*/
inline void SetScaleToMonitor(bool flag)
{
	window_hint(GLFW_SCALE_TO_MONITOR, (int)flag);
}

/*(M) Specifies sRGB capable window hint flag (default false). Sets whether the framebuffer should be sRGB capable. This function must only be called from the main thread
@param sRGB capable window hint flag*/
inline void SetSrgbCapable(bool flag)
{
	window_hint(GLFW_SRGB_CAPABLE, (int)flag);
}

/*(M) Specifies stereo window hint  (default false). Sets whether to use OpenGL stereoscopic rendering. This is a hard constraint. This function must only be called from the main thread
@param Stereo window hint flag*/
inline void SetStereo(bool flag)
{
	window_hint(GLFW_STEREO, (int)flag);
}

/*(M) Specifies stencil bits window hint value (default 8). Sets the stencil bits component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference. This function must only be called from the main thread
@param Stencil bits window hint value*/
inline void SetStencilBits(int value)
{
	window_hint(GLFW_STENCIL_BITS, value);
}

/*This function sets the current GLFW time, in seconds. Must be less than or equal to 18446744073.0, which is approximately 584.5 years. This function must only be called from the main thread
@param The new value, in seconds*/
inline void SetTime(double time)
{
	glfwSetTime(time);
}

/*(M) Specifies transparent framebuffer window hint flag (default false). Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel. This function must only be called from the main thread
@param Transparent framebuffer window hint flag*/
inline void SetTransparentFramebuffer(bool flag)
{
	window_hint(GLFW_TRANSPARENT_FRAMEBUFFER, (int)flag);
}

/*(M) Specifies visible window hint flag (default true). Sets whether the windowed mode window will be initially visible. This hint is ignored for full screen windows. This function must only be called from the main thread
@param Visible window hint flag*/
inline void SetVisible(bool flag)
{
	window_hint(GLFW_VISIBLE, (int)flag);
}

/*(M) Specifies X11 class name window hint (default ""). Sets the desired ASCII encoded class part of the ICCCM WM_CLASS window property. This function must only be called from the main thread
@param X11 class name window hint string*/
inline void SetX11ClassName(_In_z_ const char* name)
{
	window_hint_string(GLFW_X11_CLASS_NAME, name);
}

/*(M) Specifies X11 instance name window hint (default ""). Sets the desired ASCII encoded instance part of the ICCCM WM_CLASS window property. This function must only be called from the main thread
@param X11 instance name window hint string*/
inline void SetX11InstanceName(_In_z_ const char* name)
{
	window_hint_string(GLFW_X11_INSTANCE_NAME, name);
}

/*This function sets the swap interval for the current OpenGL or OpenGL ES context, i.e. the number of screen updates to wait from the time <SwapBuffers> was called before swapping the buffers and returning. This function may be called from any thread
@param The minimum number of screen updates to wait for until the buffers are swapped by <SwapBuffers>*/
inline void SwapInterval(int interval)
{
	glfwSwapInterval(interval);
}

/*(M) This function puts the calling thread to sleep until at least one event is available in the event queue. Once one or more events are available, it behaves exactly like <PollEvents>, i.e. the events in the queue are processed and the function then returns immediately. This function must only be called from the main thread*/
inline void WaitEvents();

/*(M) This function puts the calling thread to sleep until at least one event is available in the event queue, or until the specified timeout is reached. This function must only be called from the main thread
@param The maximum amount of time, in seconds, to wait*/
inline void WaitEventsTimeout(double timeout);

#ifdef YAGLPP_NO_GLFW_LEGACY
/*This function returns the platform that was selected during initialization, default <Any>
@return The currently selected platform enumerator*/
inline Platform GetPlatform()
{
	return (Platform)glfwGetPlatform();
}

/*This function returns whether the library was compiled with support for the Cocoa platform
@return True if the Cocoa platform is supported, false otherwise*/
inline bool IsCocoaPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_COCOA) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Null platform
@return True if the Null platform is supported, false otherwise*/
inline bool IsNullPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_NULL) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Wayland platform
@return True if the Wayland platform is supported, false otherwise*/
inline bool IsWaylandPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Win32 platform
@return True if the Win32 platform is supported, false otherwise*/
inline bool IsWin32PlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_WIN32) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the X11 platform
@return True if the X11 platform is supported, false otherwise*/
inline bool IsX11PlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_X11) == GLFW_TRUE;
}

/*(M) Specifies angle platform type window hint value (default <AnglePlatformTypeNone>). Sets the platform type (rendering backend) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default
@param Angle platform type window hint value*/
inline void SetAnglePlatformType(AnglePlatformType value)
{
	window_hint(GLFW_ANGLE_PLATFORM_TYPE, (int)value);
}

/*(M) Specifies position y window hint value (default <GLFW_ANY_POSITION>). Specifies the desired initial y position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it
@param Position y window hint value*/
inline void SetPositionY(int value)
{
	window_hint(GLFW_POSITION_Y, value);
}

/*(M) Specifies position x window hint value (default <GLFW_ANY_POSITION>). Specifies the desired initial x position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it
@param Position x window hint value*/
inline void SetPositionX(int value)
{
	window_hint(GLFW_POSITION_X, value);
}

/*(M) Specifies OpenGL platform selection window hint value, default <Any>
@param The platform to create context for*/
inline void SetPlatform(Platform value)
{
	window_hint(GLFW_PLATFORM, (int)value);
}

/*(M) Specifies context debug window hint flag (default false). Sets whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality
@param Context debug window hint flag*/
inline void SetContextDebug(bool flag)
{
	window_hint(GLFW_CONTEXT_DEBUG, (int)flag);
}

/*(M) Specifies scale framebuffer window hint flag (default true). Sets whether the framebuffer should be resized based on content scale changes. This can be because of a global user settings change or because the window was moved to a monitor with different scale settings
@param Scale framebuffer window hint value*/
inline void SetScaleFramebuffer(bool flag)
{
	window_hint(GLFW_SCALE_FRAMEBUFFER, (int)flag);
}

/*(M) Specifies wayland libdecor window hint flag, default <Prefer>. Sets whether to use libdecor for window decorations where available on Wayland platforms. This is ignored on other platforms
@param Wayland libdecor window hint value*/
inline void SetWaylandLibdecor(WaylandLibdecor value)
{
	window_hint(GLFW_WAYLAND_LIBDECOR, (int)value);
}

/*(M) Specifies Win32 keyboard menu window hint flag (default false). Sets whether to allow access to the window menu via the Alt+Space and Alt-and-then-Space keyboard shortcuts on Windows OS. This is ignored on other platforms
@param Win32 keyboard menu window hint flag*/
inline void SetWin32KeyboardMenu(bool flag)
{
	window_hint(GLFW_WIN32_KEYBOARD_MENU, (int)flag);
}

/*(M) Specifies Win32 show default window hint flag (default false). Sets whether to show the window the way specified in the program's STARTUPINFO when it is shown for the first time. This is the same information as the Run option in the shortcut properties window. If this information was not specified when the program was started, GLFW behaves as if this hint was set to false
@param Win32 show default window hint flag*/
inline void SetWin32Showdefault(bool flag)
{
	window_hint(GLFW_WIN32_SHOWDEFAULT, (int)flag);
}

/*(M) Specifies X11 Vulkan XCB window hint flag (default true). Sets whether to prefer the <VK_KHR_xcb_surface> extension for creating Vulkan surfaces, or whether to use the <VK_KHR_xlib_surface> extension on X11 platforms. This is ignored on other platform
@param X11 Vulkan XCB window hint flag*/
inline void SetX11XcbVulkanSurface(bool flag)
{
	window_hint(GLFW_X11_XCB_VULKAN_SURFACE, (int)flag);
}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

/*GLFW volatile data type union*/
union Param
{
	/*Boolean data type*/
	bool b;

	/*Signed char 8-bit integer data type*/
	char c;

	/*Unsigned char 8-bit integer data type*/
	unsigned char uc;

	/*Signed short 16-bit integer data type*/
	short s;

	/*Unsigned short 16-bit integer data type*/
	unsigned short us;

	/*Signed int 32-bit integer type*/
	int i;

	/*Unsigned int 32-bit integer data type*/
	unsigned int ui;

	/*Signed long long 64-bit integer data type*/
	long long l;

	/*Unsigned long long 64-bit integer data type*/
	unsigned long long ul;

	/*Float 32-bit floating point data type*/
	float f;

	/*Double 64-bit floating point data type*/
	double d;

	/*Data pointer of void type*/
	void* p;

	/*(1) Constructs boolean data type*/
	Param(bool data)
	{
		b = data;
	}

	/*(2) Constructs signed char 8-bit integer data type*/
	Param(char data)
	{
		c = data;
	}

	/*(3) Constructs unsigned char 8-bit integer data type*/
	Param(unsigned char data)
	{
		uc = data;
	}

	/*(4) Constructs signed short 16-bit integer data type*/
	Param(short data)
	{
		s = data;
	}

	/*(5) Constructs unsigned short 16-bit integer data type*/
	Param(unsigned short data)
	{
		us = data;
	}

	/*(6) Constructs signed int 32-bit integer type*/
	Param(int data)
	{
		i = data;
	}

	/*(7) Constructs unsigned int 32-bit integer data type*/
	Param(unsigned int data)
	{
		ui = data;
	}

	/*(8) Constructs signed long long 64-bit integer data type*/
	Param(long long data)
	{
		l = data;
	}

	/*(9) Constructs unsigned long long 64-bit integer data type*/
	Param(unsigned long long data)
	{
		ul = data;
	}

	/*(10) Constructs float 32-bit floating point data type*/
	Param(float data)
	{
		f = data;
	}

	/*(11) Constructs double 64-bit floating point data type*/
	Param(double data)
	{
		d = data;
	}

	/*(12) Constructs data pointer of type void*/
	Param(void* data)
	{
		p = data;
	}

	/*(1) Assigns boolean data type*/
	Param& operator = (bool data)
	{
		b = data; return *this;
	}

	/*(2) Assigns signed char 8-bit integer data type*/
	Param& operator = (char data)
	{
		c = data; return *this;
	}

	/*(3) Assigns unsigned char 8-bit integer data type*/
	Param& operator = (unsigned char data)
	{
		uc = data; return *this;
	}

	/*(4) Assigns signed short 16-bit integer data type*/
	Param& operator = (short data)
	{
		s = data; return *this;
	}

	/*(5) Assigns unsigned short 16-bit integer data type*/
	Param& operator = (unsigned short data)
	{
		us = data; return *this;
	}

	/*(6) Assigns signed int 32-bit integer type*/
	Param& operator = (int data)
	{
		i = data; return *this;
	}

	/*(7) Assigns unsigned int 32-bit integer data type*/
	Param& operator = (unsigned int data)
	{
		ui = data; return *this;
	}

	/*(8) Assigns signed long long 64-bit integer data type*/
	Param& operator = (long long data)
	{
		l = data; return *this;
	}

	/*(9) Assigns unsigned long long 64-bit integer data type*/
	Param& operator = (unsigned long long data)
	{
		ul = data; return *this;
	}

	/*(10) Assigns float 32-bit floating point data type*/
	Param& operator = (float data)
	{
		f = data; return *this;
	}

	/*(11) Assigns double 64-bit floating point data type*/
	Param& operator = (double data)
	{
		d = data; return *this;
	}

	/*(12) Assigns data pointer of type void*/
	Param& operator = (void* data)
	{
		p = data; return *this;
	}
};

/*GLFW inter-thread message structure*/
struct Message
{
	/*Message id number*/
	int msgid = 0;

	/*The message specific x value*/
	Param x = 0;

	/*The message specific y value*/
	Param y = 0;

	/*The message specific z value*/
	Param z = 0;

	/*The message specific w value*/
	Param w = 0;

	/*The sender thread object*/
	Thread* sender = nullptr;

	/*Clears the structure content*/
	void clear()
	{
		std::memset(this, 0, sizeof(Message));
	}
};

/*GLFW context creation hints structure*/
struct ContextSetting
{
	/*Specifies the desired bit depths of the alpha component of the default framebuffer*/
	int alphaBits;

	/*Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This hint is ignored for windowed mode windows*/
	bool autoIconify;

	/*Specifies the desired bit depths of the blue component of the default framebuffer*/
	int blueBits;

	/*Specifies whether the cursor should be centered over newly created full screen windows. This hint is ignored for windowed mode windows*/
	bool centerCursor;

	/*Specifies which client API to create the context for. This is a hard constraint*/
	ClientApi clientApi;

	/*Specifies whether to in Automatic Graphics Switching, i.e. to allow the system to choose the integrated GPU for the OpenGL contextand move it between GPUs if necessary or whether to force it to always run on the discrete GPU. This only affects systems with both integrated and discrete GPUs. This is ignored on other platforms than MacOS*/
	bool cocoaGraphicsSwitching;

	/*Specifies the UTF-8 encoded name to use for autosaving the window frame, or if empty disables frame autosaving for the window. This is ignored on other platforms than MacOS*/
	const char* cocoaFrameName;

	/*Specifies whether to use full resolution framebuffers on Retina displays. This is ignored on other platforms than MacOS*/
	bool cocoaRetinaFramebuffer;

	/*Specifies which context creation API to use to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	ContextApi contextCreationApi;

	/*Specifies whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior*/
	bool contextNoError;

	/*Specifies the release behavior to be used by the context*/
	ContextReleaseBehavior contextReleaseBehavior;

	/*Specifies the robustness strategy to be used by the context*/
	ContextRobustness contextRobustness;

	/*Indicates the client API major version of the window's context*/
	int contextVersionMajor;

	/*Indicates the client API minor version of the window's context*/
	int contextVersionMinor;

	/*Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This hint is ignored for full screen windows*/
	bool decorated;

	/*Specifies the desired bit depths of the depth component of the default framebuffer*/
	int depthBits;

	/*Specifies whether the framebuffer should be double buffered. You nearly always want to use double buffering. This is a hard constraint*/
	bool doublebuffer;

	/*Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposesand cannot be used to implement proper full screen windows. This hint is ignored for full screen windows*/
	bool floating;

	/*Specifies whether the windowed mode window will be given input focus when created. This hint is ignored for full screenand initially hidden windows*/
	bool focused;

	/*Specifies whether the window will be given input focus when glfwShowWindow is called*/
	bool focusOnShow;

	/*Specifies the desired bit depths of the green component of the default framebuffer*/
	int greenBits;

	/*Specifies whether the windowed mode window will be maximized when created. This hint is ignored for full screen windows*/
	bool maximized;

	/*Specifies OpenGL context debug flag. This is an alias to context debug flag for compatibility with earlier versions*/
	bool openglDebugContext;

	/*Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored*/
	bool openglForwardCompat;

	/*Specifies which OpenGL profile to create the context for*/
	OpenglProfile openglProfile;

	/*Specifies the desired bit depths of the red component of the default framebuffer*/
	int redBits;

	/*Specifies the desired refresh rate for full screen windows. This hint is ignored for windowed mode windows*/
	int refreshRate;

	/*Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <SetSize> function. This hint is ignored for full screenand undecorated windows*/
	bool resizable;

	/*Specifies the desired number of samples to use for multisampling. Zero disables multisampling*/
	int samples;

	/*Specifies whether the window content area should be resized based on the monitor content scale of any monitor it is placed on. This includes the initial placement when the window is created. This hint only has an effect on platforms where screen coordinatesand pixels always map 1:1 such as Windows and X11. On platforms like macOS the resolution of the framebuffer is changed independently of the window size*/
	bool scaleToMonitor;

	/*Specifies whether the framebuffer should be sRGB capable*/
	bool srgbCapable;

	/*Specifies the desired bit depths of the stencil component of the default framebuffer*/
	int stencilBits;

	/*Specifies whether to use OpenGL stereoscopic rendering. This is a hard constraint*/
	bool stereo;

	/*Specifies whether the window framebuffer will be transparent. If enabledand supported by the system, the window framebuffer alpha channel will be used to combine the framebuffer with the background. This does not affect window decorations.*/
	bool transparentFramebuffer;

	/*Specifies whether the windowed mode window will be initially visible. This hint is ignored for full screen windows*/
	bool visible;

	/*Specifies the desired ASCII encoded class part of the ICCCM WM_CLASS window property*/
	const char* x11ClassName;

	/*Specifies the desired ASCII encoded instance part of the ICCCM WM_CLASS window property*/
	const char* x11InstanceName;

	/*Sets up context setting structure*/
	ContextSetting();

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*Specifies the None platform type (rendering backend) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformType anglePlatformType;

	/*Specifies whether the context should be created in debug mode, which may provide additional errorand diagnostic reporting functionality*/
	bool contextDebug;

	/*Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms*/
	bool mousePassthrough;

	/*Specifies which platform to create the context for*/
	Platform platform;

	/*Specifies the desired initial x position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it*/
	int positionX;

	/*Specifies the desired initial y position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it*/
	int positionY;

	/*Specifies whether the framebuffer should be resized based on content scale changes. This can be because of a global user settings change or because the window was moved to a monitor with different scale settings*/
	bool scaleFramebuffer;

	/*Specifies whether to use libdecor for window decorations where available on Wayland platforms. This is ignored on other platforms*/
	WaylandLibdecor waylandLibdecor;

	/*Specifies whether to allow access to the window menu via the Alt+Space and Alt-and-then-Space keyboard shortcuts on Windows OS. This is ignored on other platforms*/
	bool win32KeyboardMenu;

	/*Specifies whether to show the window the way specified in the program's STARTUPINFO when it is shown for the first time. This is the same information as the Run option in the shortcut properties window. If this information was not specified when the program was started, GLFW behaves as if this hint was set to false*/
	bool win32Showdefault;

	/*Specifies whether to prefer the <VK_KHR_xcb_surface> extension for creating Vulkan surfaces, or whether to use the <VK_KHR_xlib_surface> extension on X11 platforms. This is ignored on other platform*/
	bool x11XcbVulkanSurface;
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
};

#ifdef YAGLPP_IMPLEMENTATION
double GetTimeDelta()
{
	static uint64_t uTimerValue = 0;
	static double dTimerFrequency = 0.0;
	if (uTimerValue == 0)
	{
		uTimerValue = glfwGetTimerValue();
		dTimerFrequency = 1000000.0 / glfwGetTimerFrequency();
	}
	uint64_t uNew = glfwGetTimerValue();
	uint64_t uResult = uNew - uTimerValue;
	uTimerValue = uNew;
	return uResult * dTimerFrequency;
}

ContextSetting::ContextSetting()
{
	alphaBits = 8;
	autoIconify = true;
	blueBits = 8;
	centerCursor = true;
	clientApi = ClientApi::Opengl;
	cocoaGraphicsSwitching = false;
	cocoaFrameName = "";
	cocoaRetinaFramebuffer = true;
	contextCreationApi = ContextApi::Native;
	contextNoError = false;
	contextReleaseBehavior = ContextReleaseBehavior::Any;
	contextRobustness = ContextRobustness::NoRobustness;
	contextVersionMajor = YAGLPP_CONTEXT_VERSION_MAJOR;
	contextVersionMinor = YAGLPP_CONTEXT_VERSION_MINOR;
	decorated = true;
	depthBits = 24;
	doublebuffer = true;
	greenBits = 8;
	floating = false;
	focused = true;
	focusOnShow = true;
	maximized = false;
	openglDebugContext = false;
	openglForwardCompat = false;
	redBits = 8;
	refreshRate = GLFW_DONT_CARE;
	resizable = true;
	samples = 0;
	scaleToMonitor = false;
	srgbCapable = false;
	stencilBits = 8;
	stereo = false;
	transparentFramebuffer = false;
	visible = true;
	x11ClassName = "";
	x11InstanceName = "";

#if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
	openglProfile = OpenglProfile::Core;
#else // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
	openglProfile = OpenglProfile::Any;
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)

#ifdef YAGLPP_NO_GLFW_LEGACY
	anglePlatformType = AnglePlatformType::None;
	contextDebug = false;
	mousePassthrough = false;
	platform = Platform::Any;
	positionY = GLFW_ANY_POSITION;
	positionX = GLFW_ANY_POSITION;
	scaleFramebuffer = true;
	waylandLibdecor = WaylandLibdecor::Prefer;
	win32KeyboardMenu = false;
	win32Showdefault = false;
	x11XcbVulkanSurface = true;
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
}
#endif // YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void window_hint(int hint, int value)
{
	glfwWindowHint(hint, value);
}

inline void window_hint_string(int hint, const char* value)
{
	glfwWindowHintString(hint, value);
}

inline void DefaultWindowHints()
{
	glfwDefaultWindowHints();
}

inline _Ret_maybenull_ const char* GetKeyName(int scancode)
{
	return glfwGetKeyName(GLFW_KEY_UNKNOWN, scancode);
}

inline _Ret_maybenull_ const char* GetKeyName(KeyCode key)
{
	return glfwGetKeyName((int)key, 0);
}

inline bool IsRawMouseMotionSupported()
{
	return glfwRawMouseMotionSupported() == GLFW_TRUE;
}

inline void PollEvents()
{
	glfwPollEvents();
}

inline void WaitEvents()
{
	void glfwWaitEvents();
}

inline void WaitEventsTimeout(double timeout)
{
	glfwWaitEventsTimeout(timeout);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw

#include <yaglpp/glfw/thread.h>
#include <yaglpp/glfw/cursor.h>
#include <yaglpp/glfw/monitor.h>
#include <yaglpp/glfw/joystick.h>
#include <yaglpp/glfw/window.h>

namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
bool Thread::SDATA::initialize(Thread* main)
{
	if (mainThread != nullptr) return true;
	mainThread = main;
	Monitor::s_Data.initialize();
	Joystick::s_Data.initialize();
	return false;
}

bool Thread::ShouldExit(_Out_ GLFWwindow** context)
{
	*context = glfwGetCurrentContext();
	if (*context == nullptr) return true;
	Window* pWindow = (Window*)glfwGetWindowUserPointer(*context);

	// NON-LIBRARY CREATED WINDOW OBJECT
	YAGLPP_ASSERT(pWindow != nullptr);

	if (GetCurrent()->GetExitcode() != 0) pWindow->SetShouldClose(true);
	return pWindow->ShouldClose();
}

void Monitor::Select(Window& window)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// GLFW MONITOR OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsMonitor());

	GLFWmonitor* pMonitor = glfwGetWindowMonitor(window.Get());

	// GLFW WINDOW IS NOT IN FULLSCREEN MODE
	YAGLPP_ASSERT(pMonitor == nullptr);

	select_monitor(pMonitor);
}

_Ret_maybenull_ Window* GetCurrentContext()
{
	GLFWwindow* pContext = glfwGetCurrentContext();
	if (!pContext)
	{
		return nullptr;
	}
	Window* pWindow = (Window*)glfwGetWindowUserPointer(pContext);

	// MUST BE USED ONLY WITH LIBRARY'S WINDOW OBJECT
	YAGLPP_ASSERT(pWindow != nullptr);

	return pWindow;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void window_hint(int hint, int value)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwWindowHint(hint, value);
}

void window_hint_string(int hint, const char* value)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwWindowHintString(hint, value);
}

void DefaultWindowHints()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwDefaultWindowHints();
}

_Ret_maybenull_ const char* GetKeyName(int scancode)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetKeyName(GLFW_KEY_UNKNOWN, scancode);
}

_Ret_maybenull_ const char* GetKeyName(KeyCode key)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetKeyName((int)key, 0);
}

bool IsRawMouseMotionSupported()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwRawMouseMotionSupported() == GLFW_TRUE;
}

void PollEvents()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwPollEvents();
}

void WaitEvents()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	void glfwWaitEvents();
}

void WaitEventsTimeout(double timeout)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwWaitEventsTimeout(timeout);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION
} // namespace glfw {
#endif // #ifndef YAGLPP_GLFW3PP_H
