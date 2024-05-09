#pragma once
#include "glpp.h"
#include <GLFW/glfw3.h>
#ifdef GLPP_NO_GLFW_LEGACY
#if (GLFW_VERSION_MINOR < 4)
#error GLFW++: GLFW non-legacy version 3.4+ required
#endif // #if (GLFW_VERSION_MINOR < 4)
#else // #ifdef GLPP_NO_GLFW_LEGACY
#if (GLFW_VERSION_MINOR != 3) || (GLFW_VERSION_REVISION != 10)
#error GLFW++: GLFW legacy version 3.3.10 required
#endif // #if (GLFW_VERSION_MINOR != 3) || (GLFW_VERSION_REVISION != 10)
#endif // #ifdef GLPP_NO_GLFW_LEGACY

/*glpp GLFW library namespace*/
namespace glfw {
class Cursor;
class Joystick;
class Monitor;
class Thread;
class ThreadWnd;
class Window;
enum class CursorMode : int;
enum class CursorShape : int;
enum class GamepadAxis : int;
enum class GamepadButton : int;
enum class JoystickHat : unsigned char;
enum class KeyModifier : int;
enum class MouseButton : int;
enum class ThreadPriority : int;

/*GLFW context client API enumerator*/
enum class ClientApi : int
{
	/*No API value. Create the context without API. This is a hard constraint*/
	NoApi = GLFW_NO_API,

	/*Standard OpenGL API value (default). Create the context for the OpenGL client API. This is a hard constraint*/
	OpenglApi = GLFW_OPENGL_API,

	/*OpenGL ES API value. Create the context for the OpenGL ES client API. This is a hard constraint*/
	OpenglEsApi = GLFW_OPENGL_ES_API,
};

/*Context creation API enumerator*/
enum class ContextCreationApi : int
{
	/*Native context API value (default). Indicates that native context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	NativeContextApi = GLFW_NATIVE_CONTEXT_API,

	/*EGL context API value. Indicates that EGL context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	EglContextApi = GLFW_EGL_CONTEXT_API,

	/*OSMesa context API vakue. Indicates that OSMesa context API is used to create the context. This is a hard constraint. If no client API is requested, this hint is ignored*/
	OsmesaContextApi = GLFW_OSMESA_CONTEXT_API,
};

/*GLFW context release behavior enumerator*/
enum class ContextReleaseBehavior : int
{
	/*Any release behavior value (default). Indicates that the default behavior of the context creation API will be used*/
	AnyReleaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR,

	/*Release behavior flush value. Indicates that the pipeline will be flushed whenever the context is released from being the current one*/
	ReleaseBehaviorFlush = GLFW_RELEASE_BEHAVIOR_FLUSH,

	/*Release behavior none value. Indicates that the pipeline will not be flushed on release*/
	ReleaseBehaviorNone = GLFW_RELEASE_BEHAVIOR_NONE,
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

/*GLFW keyboard key enumerator*/
enum class KeyboardKey : int
{
	/*Keyboard key <Unknown>*/
	KeyUnknown = GLFW_KEY_UNKNOWN,

	/*Keyboard key <Space>*/
	KeySpace = GLFW_KEY_SPACE,

	/*Keyboard key <'>*/
	KeyApostrophe = GLFW_KEY_APOSTROPHE,

	/*Keyboard key <,>*/
	KeyComma = GLFW_KEY_COMMA,

	/*Keyboard key <->*/
	KeyMinus = GLFW_KEY_MINUS,

	/*Keyboard key <.>*/
	KeyPeriod = GLFW_KEY_PERIOD,

	/*Keyboard key </>*/
	KeySlash = GLFW_KEY_SLASH,

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
	KeySemicolon = GLFW_KEY_SEMICOLON,

	/*Keyboard key <=>*/
	KeyEqual = GLFW_KEY_EQUAL,

	/*Keyboard key <A>*/
	KeyA = GLFW_KEY_A,

	/*Keyboard key <B>*/
	KeyB = GLFW_KEY_B,

	/*Keyboard key <C>*/
	KeyC = GLFW_KEY_C,

	/*Keyboard key <D>*/
	KeyD = GLFW_KEY_D,

	/*Keyboard key <E>*/
	KeyE = GLFW_KEY_E,

	/*Keyboard key <F>*/
	KeyF = GLFW_KEY_F,

	/*Keyboard key <G>*/
	KeyG = GLFW_KEY_G,

	/*Keyboard key <H>*/
	KeyH = GLFW_KEY_H,

	/*Keyboard key <I>*/
	KeyI = GLFW_KEY_I,

	/*Keyboard key <J>*/
	KeyJ = GLFW_KEY_J,

	/*Keyboard key <K>*/
	KeyK = GLFW_KEY_K,

	/*Keyboard key <L>*/
	KeyL = GLFW_KEY_L,

	/*Keyboard key <M>*/
	KeyM = GLFW_KEY_M,

	/*Keyboard key <N>*/
	KeyN = GLFW_KEY_N,

	/*Keyboard key <O>*/
	KeyO = GLFW_KEY_O,

	/*Keyboard key <P>*/
	KeyP = GLFW_KEY_P,

	/*Keyboard key <Q>*/
	KeyQ = GLFW_KEY_Q,

	/*Keyboard key <R>*/
	KeyR = GLFW_KEY_R,

	/*Keyboard key <S>*/
	KeyS = GLFW_KEY_S,

	/*Keyboard key <T>*/
	KeyT = GLFW_KEY_T,

	/*Keyboard key <U>*/
	KeyU = GLFW_KEY_U,

	/*Keyboard key <V>*/
	KeyV = GLFW_KEY_V,

	/*Keyboard key <W>*/
	KeyW = GLFW_KEY_W,

	/*Keyboard key <X>*/
	KeyX = GLFW_KEY_X,

	/*Keyboard key <Y>*/
	KeyY = GLFW_KEY_Y,

	/*Keyboard key <Z>*/
	KeyZ = GLFW_KEY_Z,

	/*Keyboard key <[>*/
	KeyLeftBracket = GLFW_KEY_LEFT_BRACKET,

	/*Keyboard key <\>*/
	KeyBackslash = GLFW_KEY_BACKSLASH,

	/*Keyboard key <]>*/
	KeyRightBracket = GLFW_KEY_RIGHT_BRACKET,

	/*Keyboard key <`>*/
	KeyGraveAccent = GLFW_KEY_GRAVE_ACCENT,

	/*Keyboard key <World1>*/
	KeyWorld1 = GLFW_KEY_WORLD_1,

	/*Keyboard key <World2>*/
	KeyWorld2 = GLFW_KEY_WORLD_2,

	/*Keyboard key <Escape>*/
	KeyEscape = GLFW_KEY_ESCAPE,

	/*Keyboard key <Enter>*/
	KeyEnter = GLFW_KEY_ENTER,

	/*Keyboard key <Tab>*/
	KeyTab = GLFW_KEY_TAB,

	/*Keyboard key <Backspace>*/
	KeyBackspace = GLFW_KEY_BACKSPACE,

	/*Keyboard key <Insert>*/
	KeyInsert = GLFW_KEY_INSERT,

	/*Keyboard key <Delete>*/
	KeyDelete = GLFW_KEY_DELETE,

	/*Keyboard key <Right>*/
	KeyRight = GLFW_KEY_RIGHT,

	/*Keyboard key <Left>*/
	KeyLeft = GLFW_KEY_LEFT,

	/*Keyboard key <Down>*/
	KeyDown = GLFW_KEY_DOWN,

	/*Keyboard key <Up>*/
	KeyUp = GLFW_KEY_UP,

	/*Keyboard key <PageUp>*/
	KeyPageUp = GLFW_KEY_PAGE_UP,

	/*Keyboard key <PageDown>*/
	KeyPageDown = GLFW_KEY_PAGE_DOWN,

	/*Keyboard key <Home>*/
	KeyHome = GLFW_KEY_HOME,

	/*Keyboard key <End>*/
	KeyEnd = GLFW_KEY_END,

	/*Keyboard key <CapsLock>*/
	KeyCapsLock = GLFW_KEY_CAPS_LOCK,

	/*Keyboard key <ScrollLock>*/
	KeyScrollLock = GLFW_KEY_SCROLL_LOCK,

	/*Keyboard key <Numlock>*/
	KeyNumlock = GLFW_KEY_NUM_LOCK,

	/*Keyboard key <PrintScreen>*/
	KeyPrintScreen = GLFW_KEY_PRINT_SCREEN,

	/*Keyboard key <Pause>*/
	KeyPause = GLFW_KEY_PAUSE,

	/*Keyboard key <F1>*/
	KeyF1 = GLFW_KEY_F1,

	/*Keyboard key <F2>*/
	KeyF2 = GLFW_KEY_F2,

	/*Keyboard key <F3>*/
	KeyF3 = GLFW_KEY_F3,

	/*Keyboard key <F4>*/
	KeyF4 = GLFW_KEY_F4,

	/*Keyboard key <F5>*/
	KeyF5 = GLFW_KEY_F5,

	/*Keyboard key <F6>*/
	KeyF6 = GLFW_KEY_F6,

	/*Keyboard key <F7>*/
	KeyF7 = GLFW_KEY_F7,

	/*Keyboard key <F8>*/
	KeyF8 = GLFW_KEY_F8,

	/*Keyboard key <F9>*/
	KeyF9 = GLFW_KEY_F9,

	/*Keyboard key <F10>*/
	KeyF10 = GLFW_KEY_F10,

	/*Keyboard key <F11>*/
	KeyF11 = GLFW_KEY_F11,

	/*Keyboard key <F12>*/
	KeyF12 = GLFW_KEY_F12,

	/*Keyboard key <F13>*/
	KeyF13 = GLFW_KEY_F13,

	/*Keyboard key <F14>*/
	KeyF14 = GLFW_KEY_F14,

	/*Keyboard key <F15>*/
	KeyF15 = GLFW_KEY_F15,

	/*Keyboard key <F16>*/
	KeyF16 = GLFW_KEY_F16,

	/*Keyboard key <F17>*/
	KeyF17 = GLFW_KEY_F17,

	/*Keyboard key <F18>*/
	KeyF18 = GLFW_KEY_F18,

	/*Keyboard key <F19>*/
	KeyF19 = GLFW_KEY_F19,

	/*Keyboard key <F20>*/
	KeyF20 = GLFW_KEY_F20,

	/*Keyboard key <F21>*/
	KeyF21 = GLFW_KEY_F21,

	/*Keyboard key <F22>*/
	KeyF22 = GLFW_KEY_F22,

	/*Keyboard key <F23>*/
	KeyF23 = GLFW_KEY_F23,

	/*Keyboard key <F24>*/
	KeyF24 = GLFW_KEY_F24,

	/*Keyboard key <F25>*/
	KeyF25 = GLFW_KEY_F25,

	/*Keyboard key pad <0>*/
	KeyKp0 = GLFW_KEY_KP_0,

	/*Keyboard key pad <1>*/
	KeyKp1 = GLFW_KEY_KP_1,

	/*Keyboard key pad <2>*/
	KeyKp2 = GLFW_KEY_KP_2,

	/*Keyboard key pad <3>*/
	KeyKp3 = GLFW_KEY_KP_3,

	/*Keyboard key pad <4>*/
	KeyKp4 = GLFW_KEY_KP_4,

	/*Keyboard key pad <5>*/
	KeyKp5 = GLFW_KEY_KP_5,

	/*Keyboard key pad <6>*/
	KeyKp6 = GLFW_KEY_KP_6,

	/*Keyboard key pad <7>*/
	KeyKp7 = GLFW_KEY_KP_7,

	/*Keyboard key pad <8>*/
	KeyKp8 = GLFW_KEY_KP_8,

	/*Keyboard key pad <9>*/
	KeyKp9 = GLFW_KEY_KP_9,

	/*Keyboard key pad <Decimal>*/
	KeyKpDecimal = GLFW_KEY_KP_DECIMAL,

	/*Keyboard key pad <Divide>*/
	KeyKpDivide = GLFW_KEY_KP_DIVIDE,

	/*Keyboard key pad <Multiply>*/
	KeyKpMultiply = GLFW_KEY_KP_MULTIPLY,

	/*Keyboard key pad <Subtract>*/
	KeyKpSubtract = GLFW_KEY_KP_SUBTRACT,

	/*Keyboard key pad <Add>*/
	KeyKpAdd = GLFW_KEY_KP_ADD,

	/*Keyboard key pad <Enter>*/
	KeyKpEnter = GLFW_KEY_KP_ENTER,

	/*Keyboard key pad <Equal>*/
	KeyKpEqual = GLFW_KEY_KP_EQUAL,

	/*Keyboard key <LeftShift>*/
	KeyLeftShift = GLFW_KEY_LEFT_SHIFT,

	/*Keyboard key <LeftControl>*/
	KeyLeftControl = GLFW_KEY_LEFT_CONTROL,

	/*Keyboard key <LeftAlt>*/
	KeyLeftAlt = GLFW_KEY_LEFT_ALT,

	/*Keyboard key <LeftSuper>*/
	KeyLeftSuper = GLFW_KEY_LEFT_SUPER,

	/*Keyboard key <RightShift>*/
	KeyRightShift = GLFW_KEY_RIGHT_SHIFT,

	/*Keyboard key <RightControl>*/
	KeyRightControl = GLFW_KEY_RIGHT_CONTROL,

	/*Keyboard key <RightAlt>*/
	KeyRightAlt = GLFW_KEY_RIGHT_ALT,

	/*Keyboard key <RightSuper>*/
	KeyRightSuper = GLFW_KEY_RIGHT_SUPER,

	/*Keyboard key <Menu>*/
	KeyMenu = GLFW_KEY_MENU,

	/*Keyboard key <Last>*/
	KeyLast = GLFW_KEY_LAST,
};

/*GLFW context OpenGL profile enumerator*/
enum class OpenglProfile : int
{
	/*OpenGL any profile value (default). Indicates any OpenGL profile used by the context. This value is used if the context uses a known profile. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	OpenglAnyProfile = GLFW_OPENGL_ANY_PROFILE,

	/*OpenGL core profile value. Indicates the Core OpenGL profile used by the context. This value is used if the OpenGL profile is unknown or the context is an OpenGL ES context. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	OpenglCoreProfile = GLFW_OPENGL_CORE_PROFILE,

	/*OpenGL compatible profile value. Indicates the Compat OpenGL profile used by the context. This value is used if the context uses a known profile. Note that the returned profile may not match the profile bits of the context flags, as GLFW will try other means of detecting the profile when no bits are set*/
	OpenglCompatProfile = GLFW_OPENGL_COMPAT_PROFILE,
};

/*This function resets all window hints to their default values*/
inline void defaultWindowHints()
{
	glfwDefaultWindowHints();
}

/*This function returns whether the specified API extension is supported by the current OpenGL or OpenGL ES context
@param [in] The ASCII encoded name of the extension
@return True if the extension is available, or false otherwise*/
inline bool extensionSupported(_In_z_ const char* extension)
{
	return (bool)glfwExtensionSupported(extension);
}

/*(1) This function returns the name of the specified printable key by its scancode, encoded as UTF-8
@param The scancode of the printable key to query
@return The UTF-8 encoded, layout-specific name of the key string, or NULL*/
_Ret_maybenull_ inline const char* getKeyName(int scancode)
{
	return glfwGetKeyName(GLFW_KEY_UNKNOWN, scancode);
}

/*(2) This function returns the name of the specified printable key, encoded as UTF-8
@param The enumerator of the printable key to query
@return The UTF-8 encoded, layout-specific name of the key string, or NULL*/
_Ret_maybenull_ inline const char* getKeyName(KeyboardKey key)
{
	return glfwGetKeyName((int)key, 0);
}

/*This function returns the platform-specific scancode of the specified key. If the key is <KeyUnknown> or does not exist on the keyboard this method will return -1
@param Keyboard key enumerator
@return Keyboard key platform-specific scancode*/
inline int getKeyScancode(KeyboardKey key)
{
	return glfwGetKeyScancode((int)key);
}

/*This function returns the current GLFW time, in seconds
@return The current time, in seconds, or zero if an error occured*/
inline double getTime()
{
	return glfwGetTime();
}

/*This function returns the frequency, in Hz, of the raw timer
@return The frequency of the timer, in Hz, or zero if an error occurred*/
inline uint64_t getTimerFrequency()
{
	return glfwGetTimerFrequency();
}

/*This function returns the current value of the raw timer, measured in 1/frequency seconds. To get the frequency, call <getTimerFrequency>
@return The value of the timer, or zero if an error occurred*/
inline uint64_t getTimerValue()
{
	return glfwGetTimerValue();
}

/*Returns a string describing the compile-time configuration
@return The ASCII encoded GLFW version string*/
_Ret_z_ inline const char* getVersionString()
{
	return glfwGetVersionString();
}

/*This function processes only those events that are already in the event queue and then returns immediately*/
inline void pollEvents()
{
	glfwPollEvents();
}

/*This function posts an empty event from the current thread to the event queue, causing <waitEvents> or <waitEventsTimeout> to return*/
inline void postEmptyEvent()
{
	glfwPostEmptyEvent();
}

/*This function returns whether raw mouse motion is supported on the current system
@return True if raw mouse motion is supported on the current machine, false otherwise*/
inline bool rawMouseMotionSupported()
{
	return glfwRawMouseMotionSupported() == GLFW_TRUE;
}

/*Specifies alpha bits window hint value (default 8). Sets the desired bit depths of the alpha component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Alpha bits window hint value*/
inline void setAlphaBits(int value)
{
	glfwWindowHint(GLFW_ALPHA_BITS, value);
}

/*Specifies auto iconify window hint flag (default true). Sets whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. This hint is ignored for windowed mode windows
@param Auto iconify window hint flag*/
inline void setAutoIconify(bool flag)
{
	glfwWindowHint(GLFW_AUTO_ICONIFY, (int)flag);
}

/*Specifies blue bits window hint value (default 8). Sets the desired bit depths of the blue component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Blue bits window hint value*/
inline void setBlueBits(int value)
{
	glfwWindowHint(GLFW_BLUE_BITS, value);
}

/*Specifies center cursor window hint flag (default true). Sets whether the cursor should be centered over newly created full screen windows. This hint is ignored for windowed mode windows
@param Center cursor window hint flag*/
inline void setCenterCursor(bool flag)
{
	glfwWindowHint(GLFW_CENTER_CURSOR, (int)flag);
}

/*Specifies client API window hint value (default OpenglApi)
@param The client API window hint enumerator*/
inline void setClientApi(ClientApi value)
{
	glfwWindowHint(GLFW_CLIENT_API, (int)value);
}

/*Specifies cocoa frame name window hint (default ""). Sets the UTF-8 encoded name to use for autosaving the window frame, or if empty disables frame autosaving for the window. This is ignored on other platforms
@param Cocoa frame name window hint string*/
inline void setCocoaFrameName(_In_z_ const char* name)
{
	glfwWindowHintString(GLFW_COCOA_FRAME_NAME, name);
}

/*Specifies cocoa graphics switching window hint flag (default false). Sets whether to in Automatic Graphics Switching, i.e. to allow the system to choose the integrated GPU for the OpenGL context and move it between GPUs if necessary or whether to force it to always run on the discrete GPU. This only affects systems with both integrated and discrete GPUs. This is ignored on other platforms. Simpler programs and tools may want to enable this to save power, while games and other applications performing advanced rendering will want to leave it disabled
@param Cocoa graphics switching window hint flag*/
inline void setCocoaGraphicsSwitching(bool flag)
{
	glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, (int)flag);
}

/*Specifies cocoa retina framebuffer window hint flag (default true). Sets whether to use full resolution framebuffers on Retina displays. This is ignored on other platforms
@param Cocoa retina framebuffer window hint flag*/
inline void setCocoaRetinaFramebuffer(bool flag)
{
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, (int)flag);
}

/*Specifies context release behavior window hint value (default AnyReleaseBehavior)
@param The context release behavior window hint enumerator*/
inline void setContextReleaseBehavior(ContextReleaseBehavior value)
{
	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, (int)value);
}

/*Specifies context version major window hint value (default 1). Indicates the client API major version of the window's context
@param Context version major window hint value*/
inline void setContextVersionMajor(int value)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, value);
}

/*Specifies context version minor window hint value (default 0). Indicates the client API minor version of the window's context
@param Context version minor window hint value*/
inline void setContextVersionMinor(int value)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, value);
}

/*Specifies context creation API window hint value (defailt NativeContextApi)
@param The context creation API window hint enumerator*/
inline void setContextCreationApi(ContextCreationApi value)
{
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, (int)value);
}

/*Specifies context no error window hint flag (default false). Sets whether errors should be generated by the context. If enabled, situations that would have generated errors instead cause undefined behavior
@param Context no error window hint flag*/
inline void setContextNoError(bool flag)
{
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, (int)flag);
}

/*Specifies context robustness window hint value (default NoRobustness)
@param The context robustness window hint enumerator*/
inline void setContextRobustness(ContextRobustness value)
{
	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, (int)value);
}

/*Specifies decorated window hint flag (default true). Sets whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window will not be resizable by the user but will still allow the user to generate close events on some platforms. This hint is ignored for full screen windows
@param Decorated window hint flag*/
inline void setDecorated(bool flag)
{
	glfwWindowHint(GLFW_DECORATED, (int)flag);
}

/*Specifies depth bits window hint value (default 24). Sets the depth bits component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Depth bits window hint value*/
inline void setDepthBits(int value)
{
	glfwWindowHint(GLFW_DEPTH_BITS, value);
}

/*Specifies double buffer window hint flag (default true). Sets whether the framebuffer should be double buffered. You nearly always want to use double buffering. This is a hard constraint
@param Double buffer window hint flag*/
inline void setDoublebuffer(bool flag)
{
	glfwWindowHint(GLFW_DOUBLEBUFFER, (int)flag);
}

/*Specifies floating window hint flag (default false). Sets whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This hint is ignored for full screen windows
@param Floating window hint flag*/
inline void setFloating(bool flag)
{
	glfwWindowHint(GLFW_FLOATING, (int)flag);
}

/*Specifies focused window hint flag (default true). Sets whether the windowed mode window will be given input focus when created. This hint is ignored for full screen and initially hidden windows
@param Focused window hint flag*/
inline void setFocused(bool flag)
{
	glfwWindowHint(GLFW_FOCUSED, (int)flag);
}

/*Specifies focus on show window hint flag (default true). Sets whether the window will be given input focus when <showWindow> is called
@param Focus on show window hint flag*/
inline void setFocusOnShow(bool flag)
{
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, (int)flag);
}

/*Specifies green bits window hint value (default 8). Sets the desired bit depths of the green component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Green bits window hint value*/
inline void setGreenBits(int value)
{
	glfwWindowHint(GLFW_GREEN_BITS, value);
}

/*Specifies window hint flag (default false). Sets whether the windowed mode window will be maximized when created. This hint is ignored for full screen windows
@param Maximized window hint flag*/
inline void setMaximized(bool flag)
{
	glfwWindowHint(GLFW_MAXIMIZED, (int)flag);
}

/*Specifies OpenGL debug context window hint flag (default false). This is an alias to context debug flag for compatibility with earlier versions
@param OpenGL debug context window hint flag*/
inline void setOpenglDebugContext(bool flag)
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, (int)flag);
}

/*Specifies OpenGL forward compatible window hint flag (default false). Sets whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored
@param OpenGL forward compatible window hint flag*/
inline void setOpenglForwardCompat(bool flag)
{
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, (int)flag);
}

/*Specifies OpenGL profile window hint value (default OpenglAnyProfile)
@param The OpenGL profile window hint enumerator*/
inline void setOpenglProfile(OpenglProfile value)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, (int)value);
}

/*Specifies red bits window hint value (default 8). Sets the desired bit depths of the red component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Red bits window hint value*/
inline void setRedBits(int value)
{
	glfwWindowHint(GLFW_RED_BITS, value);
}

/*Specifies refresh rate window hint value (default GLFW_DONT_CARE). Sets the desired refresh rate for full screen windows. A value of GLFW_DONT_CARE means the highest available refresh rate will be used. This hint is ignored for windowed mode windows
@param Refresh rate window hint value*/
inline void setRefreshRate(int value)
{
	glfwWindowHint(GLFW_REFRESH_RATE, value);
}

/*Specifies resizable window hint flag (default true). Sets whether the windowed mode window will be resizable by the user. The window will still be resizable using the glfwSetWindowSize function. This hint is ignored for full screen and undecorated windows
@param Resizable window hint flag*/
inline void setResizable(bool flag)
{
	glfwWindowHint(GLFW_RESIZABLE, (int)flag);
}

/*Specifies samples window hint value (default 0). Sets the desired number of samples to use for multisampling. Zero disables multisampling. A value of GLFW_DONT_CARE means the application has no preference
@param Samples window hint value*/
inline void setSamples(int value)
{
	glfwWindowHint(GLFW_SAMPLES, value);
}

/*Sets whether the window content area should be resized based on the monitor content scale of any monitor it is placed on. This includes the initial placement when the window is created. This hint only has an effect on platforms where screen coordinates and pixels always map 1:1 such as Windows and X11.On platforms like macOS the resolution of the framebuffer is changed independently of the window size
@param Scale to monitor window hint flag*/
inline void setScaleToMonitor(bool flag)
{
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, (int)flag);
}

/*Specifies sRGB capable window hint flag (default false). Sets whether the framebuffer should be sRGB capable
@param sRGB capable window hint flag*/
inline void setSrgbCapable(bool flag)
{
	glfwWindowHint(GLFW_SRGB_CAPABLE, (int)flag);
}

/*Specifies stereo window hint  (default false). Sets whether to use OpenGL stereoscopic rendering. This is a hard constraint
@param Stereo window hint flag*/
inline void setStereo(bool flag)
{
	glfwWindowHint(GLFW_STEREO, (int)flag);
}

/*Specifies stencil bits window hint value (default 8). Sets the stencil bits component of the default framebuffer. A value of GLFW_DONT_CARE means the application has no preference
@param Stencil bits window hint value*/
inline void setStencilBits(int value)
{
	glfwWindowHint(GLFW_STENCIL_BITS, value);
}

/*This function sets the current GLFW time, in seconds. Must be less than or equal to 18446744073.0, which is approximately 584.5 years
@param The new value, in seconds*/
inline void setTime(double time)
{
	glfwSetTime(time);
}

/*Specifies transparent framebuffer window hint flag (default false). Indicates whether the specified window has a transparent framebuffer, i.e. the window contents is composited with the background using the window framebuffer alpha channel
@param Transparent framebuffer window hint flag*/
inline void setTransparentFramebuffer(bool flag)
{
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, (int)flag);
}

/*Specifies visible window hint flag (default true). Sets whether the windowed mode window will be initially visible. This hint is ignored for full screen windows
@param Visible window hint flag*/
inline void setVisible(bool flag)
{
	glfwWindowHint(GLFW_VISIBLE, (int)flag);
}

/*Specifies X11 class name window hint (default ""). Sets the desired ASCII encoded class part of the ICCCM WM_CLASS window property
@param X11 class name window hint string*/
inline void setX11ClassName(_In_z_ const char* name)
{
	glfwWindowHintString(GLFW_X11_CLASS_NAME, name);
}

/*Specifies X11 instance name window hint (default ""). Sets the desired ASCII encoded instance part of the ICCCM WM_CLASS window property
@param X11 instance name window hint string*/
inline void setX11InstanceName(_In_z_ const char* name)
{
	glfwWindowHintString(GLFW_X11_INSTANCE_NAME, name);
}

/*This function sets the swap interval for the current OpenGL or OpenGL ES context, i.e. the number of screen updates to wait from the time <swapBuffers> was called before swapping the buffers and returning
@param The minimum number of screen updates to wait for until the buffers are swapped by <swapBuffers>*/
inline void swapInterval(int interval)
{
	glfwSwapInterval(interval);
}

/*This function puts the calling thread to sleep until at least one event is available in the event queue. Once one or more events are available, it behaves exactly like <pollEvents>, i.e. the events in the queue are processed and the function then returns immediately*/
inline void waitEvents()
{
	void glfwWaitEvents();
}

/*This function puts the calling thread to sleep until at least one event is available in the event queue, or until the specified timeout is reached
@param The maximum amount of time, in seconds, to wait*/
inline void waitEventsTimeout(double timeout)
{
	glfwWaitEventsTimeout(timeout);
}

#ifdef GLPP_NO_GLFW_LEGACY
/*GLFW platform type (rendering backend) enumerator*/
enum class AnglePlatformType : int
{
	/*Specifies the None platform type (default) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeNone = GLFW_ANGLE_PLATFORM_TYPE_NONE,

	/*Specifies the OpenGL platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeOpengl = GLFW_ANGLE_PLATFORM_TYPE_OPENGL,

	/*Specifies the OpenGL ES platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeOpengles = GLFW_ANGLE_PLATFORM_TYPE_OPENGLES,

	/*Specifies the D3D9 platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeD3d9 = GLFW_ANGLE_PLATFORM_TYPE_D3D9,

	/*Specifies the D3D11 platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeD3d11 = GLFW_ANGLE_PLATFORM_TYPE_D3D11,

	/*Specifies the Vulkan platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeVulkan = GLFW_ANGLE_PLATFORM_TYPE_VULKAN,

	/*Specifies the Metal platform type to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformTypeMetal = GLFW_ANGLE_PLATFORM_TYPE_METAL,
};

/*GLFW platform selection enumerator*/
enum class Platform : int
{
	/*Automatic platform selection, default value*/
	AnyPlatform = GLFW_ANY_PLATFORM,

	/*Win32 platform selection*/
	PlatformWin32 = GLFW_PLATFORM_WIN32,

	/*Cocoa platform selection*/
	PlatformCocoa = GLFW_PLATFORM_COCOA,

	/*Wayland platform selection*/
	PlatformWayland = GLFW_PLATFORM_WAYLAND,

	/*X11 platform selection*/
	PlatformX11 = GLFW_PLATFORM_X11,

	/*Null platform selection, which is always supported but needs to be explicitly requested*/
	PlatformNull = GLFW_PLATFORM_NULL,
};

/*GLFW Wayland libdecor usage enumerator*/
enum class WaylandLibdecor : int
{
	/*Prefer to use libdecor for window decorations where available on Wayland platforms. This is ignored on other platforms*/
	WaylandPreferLibdecor = GLFW_WAYLAND_PREFER_LIBDECOR,

	/*Disable libdecor for window decorations on Wayland platforms. This is ignored on other platforms*/
	WaylandDisableLibdecor = GLFW_WAYLAND_DISABLE_LIBDECOR,
};

/*This function returns the platform that was selected during initialization (default AnyPlatform)
@return The currently selected platform enumerator*/
inline Platform getPlatform()
{
	return (Platform)glfwGetPlatform();
}

/*This function returns whether the library was compiled with support for the Cocoa platform
@return True if the Cocoa platform is supported, false otherwise*/
inline bool isCocoaPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_COCOA) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Null platform
@return True if the Null platform is supported, false otherwise*/
inline bool isNullPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_NULL) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Wayland platform
@return True if the Wayland platform is supported, false otherwise*/
inline bool isWaylandPlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the Win32 platform
@return True if the Win32 platform is supported, false otherwise*/
inline bool isWin32PlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_WIN32) == GLFW_TRUE;
}

/*This function returns whether the library was compiled with support for the X11 platform
@return True if the X11 platform is supported, false otherwise*/
inline bool isX11PlatformSupported()
{
	return glfwPlatformSupported(GLFW_PLATFORM_X11) == GLFW_TRUE;
}

/*Specifies angle platform type window hint value (default <AnglePlatformTypeNone>). Sets the platform type (rendering backend) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default
@param Angle platform type window hint value*/
inline void setAnglePlatformType(AnglePlatformType value)
{
	glfwWindowHint(GLFW_ANGLE_PLATFORM_TYPE, (int)value);
}

/*Specifies position y window hint value (default <GLFW_ANY_POSITION>). Specifies the desired initial y position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it
@param Position y window hint value*/
inline void setPositionY(int value)
{
	glfwWindowHint(GLFW_POSITION_Y, value);
}

/*Specifies position x window hint value (default <GLFW_ANY_POSITION>). Specifies the desired initial x position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it
@param Position x window hint value*/
inline void setPositionX(int value)
{
	glfwWindowHint(GLFW_POSITION_X, value);
}

/*Specifies OpenGL platform selection window hint value (default AnyPlatform)
@param The platform to create context for*/
inline void setPlatform(Platform value)
{
	glfwWindowHint(GLFW_PLATFORM, (int)value);
}

/*Specifies context debug window hint flag (default false). Sets whether the context should be created in debug mode, which may provide additional error and diagnostic reporting functionality
@param Context debug window hint flag*/
inline void setContextDebug(bool flag)
{
	glfwWindowHint(GLFW_CONTEXT_DEBUG, (int)flag);
}

/*Specifies scale framebuffer window hint flag (default true). Sets whether the framebuffer should be resized based on content scale changes. This can be because of a global user settings change or because the window was moved to a monitor with different scale settings
@param Scale framebuffer window hint value*/
inline void setScaleFramebuffer(bool flag)
{
	glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, (int)flag);
}

/*Specifies wayland libdecor window hint flag (default <WaylandPreferLibdecor>). Sets whether to use libdecor for window decorations where available on Wayland platforms. This is ignored on other platforms
@param Wayland libdecor window hint value*/
inline void setWaylandLibdecor(WaylandLibdecor value)
{
	glfwWindowHint(GLFW_WAYLAND_LIBDECOR, (int)value);
}

/*Specifies Win32 keyboard menu window hint flag (default false). Sets whether to allow access to the window menu via the Alt+Space and Alt-and-then-Space keyboard shortcuts on Windows OS. This is ignored on other platforms
@param Win32 keyboard menu window hint flag*/
inline void setWin32KeyboardMenu(bool flag)
{
	glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, (int)flag);
}

/*Specifies Win32 show default window hint flag (default false). Sets whether to show the window the way specified in the program's STARTUPINFO when it is shown for the first time. This is the same information as the Run option in the shortcut properties window. If this information was not specified when the program was started, GLFW behaves as if this hint was set to false
@param Win32 show default window hint flag*/
inline void setWin32Showdefault(bool flag)
{
	glfwWindowHint(GLFW_WIN32_SHOWDEFAULT, (int)flag);
}

/*Specifies X11 Vulkan XCB window hint flag (default true). Sets whether to prefer the <VK_KHR_xcb_surface> extension for creating Vulkan surfaces, or whether to use the <VK_KHR_xlib_surface> extension on X11 platforms. This is ignored on other platform
@param X11 Vulkan XCB window hint flag*/
inline void setX11XcbVulkanSurface(bool flag)
{
	glfwWindowHint(GLFW_X11_XCB_VULKAN_SURFACE, (int)flag);
}
#endif // #ifdef GLPP_NO_GLFW_LEGACY

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
	ContextCreationApi contextCreationApi;

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

	/*Specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using the <setWindowSize> function. This hint is ignored for full screenand undecorated windows*/
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

#ifdef GLPP_NO_GLFW_LEGACY
	/*Specifies the None platform type (rendering backend) to request when using OpenGL ES and EGL via ANGLE. If the requested platform type is unavailable, ANGLE will use its default*/
	AnglePlatformType anglePlatformType;

	/*Specifies whether the context should be created in debug mode, which may provide additional errorand diagnostic reporting functionality*/
	bool contextDebug;

	/*Specifies whether the window is transparent to mouse input, letting any mouse events pass through to whatever window is behind it. This is only supported for undecorated windows. Decorated windows with this enabled will behave differently between platforms*/
	bool mousePassthrough;

	/*Specifies which platform to create the context for*/
	Platform platform;

	/*Specifies the desired initial y position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it*/
	int positionY;

	/*Specifies the desired initial x position of the window. The window manager may modify or ignore these coordinates. If either or both of these hints are set to <GLFW_ANY_POSITION> then the window manager will position the window where it thinks the user will prefer it*/
	int positionX;

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
#endif // #ifdef GLPP_NO_GLFW_LEGACY
};
} // namespace glfw

#ifndef GLPP_BUILD_LIB
#include "Cursor.h"
#include "Joystick.h"
#include "Monitor.h"
#include "Thread.h"
#include "Window.h"
#endif // #ifdef GLPP_BUILD
