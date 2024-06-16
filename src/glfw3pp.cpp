#define YAGLPP_BUILD_LIB
#include <yaglpp/glfw3pp.h>
#include <yaglpp/Window.h>
#include <yaglpp/Thread.h>
#include <yaglpp/Monitor.h>
#include <yaglpp/Joystick.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
#ifdef YAGLPP_NO_GLFW_LEGACY
#pragma message("glfw3pp.cpp: Compiling with GLFW version 3.4 nonlegacy support...")
#else // #ifdef YAGLPP_NO_GLFW_LEGACY
#pragma message("glfw3pp.cpp: Compiling with GLFW version 3.3.10 Windows XP legacy support...")
#endif

namespace glfw {
int Thread::m_sArgc;
char** Thread::m_sArgv;
Thread* Thread::m_sMainThread;
ThreadSync Thread::m_sThreadSync;
Window::_SDATA Window::s_Data;
Monitor::_SDATA Monitor::s_Data;
Joystick::_SDATA Joystick::s_Data;
ContextSetting::ContextSetting()
{
	alphaBits = 8;
	autoIconify = true;
	blueBits = 8;
	centerCursor = true;
	clientApi = ClientApi::OpenglApi;
	cocoaGraphicsSwitching = false;
	cocoaFrameName = "";
	cocoaRetinaFramebuffer = true;
	contextCreationApi = ContextCreationApi::NativeContextApi;
	contextNoError = false;
	contextReleaseBehavior = ContextReleaseBehavior::AnyReleaseBehavior;
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
	openglProfile = OpenglProfile::OpenglCoreProfile;
#else // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
	openglProfile = OpenglProfile::OpenglAnyProfile;
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)

#ifdef YAGLPP_NO_GLFW_LEGACY
	anglePlatformType = AnglePlatformType::AnglePlatformTypeNone;
	contextDebug = false;
	mousePassthrough = false;
	platform = Platform::AnyPlatform;
	positionY = GLFW_ANY_POSITION;
	positionX = GLFW_ANY_POSITION;
	scaleFramebuffer = true;
	waylandLibdecor = WaylandLibdecor::WaylandPreferLibdecor;
	win32KeyboardMenu = false;
	win32Showdefault = false;
	x11XcbVulkanSurface = true;
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
}
} // namespace glfw
