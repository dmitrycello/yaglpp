#define YAGLPP_BUILD_LIB
#include <yaglpp/Window.h>
#include <yaglpp/Monitor.h>
#include <yaglpp/StbImage.h>
#include <yaglpp/FreeImage.h>

#define YAGLPP_CHAR							-100
#define YAGLPP_CURSOR_ENTER					-110
#define YAGLPP_CURSOR_POS					-120
#define YAGLPP_DROP							-130
#define YAGLPP_FRAMEBUFFER_SIZE				-140
#define YAGLPP_KEY							-150
#define YAGLPP_MOUSE_BUTTON					-160
#define YAGLPP_SCROLL						-170
#define YAGLPP_WINDOW_CLOSE					-180
#define YAGLPP_WINDOW_CONTENT_SCALE			-190
#define YAGLPP_WINDOW_FOCUS					-200
#define YAGLPP_WINDOW_ICONIFY				-210
#define YAGLPP_WINDOW_MAXIMIZE				-220
#define YAGLPP_WINDOW_POS					-230
#define YAGLPP_WINDOW_REFRESH				-240
#define YAGLPP_WINDOW_SIZE					-250
#define YAGLPP_WINDOW_TRANSFER				-260

#define YAGLPP_DESTROY_WINDOW				-300
#define YAGLPP_FOCUS_WINDOW					-310
#define YAGLPP_HIDE_WINDOW					-320
#define YAGLPP_ICONIFY_WINDOW				-330
#define YAGLPP_MAXIMIZE_WINDOW				-340
#define YAGLPP_REQUEST_WINDOW_ATTENTION		-350
#define YAGLPP_RESTORE_WINDOW				-360
#define YAGLPP_SET_CLIPBOARD_STRING			-400
#define YAGLPP_SET_CURSOR_POS				-410
#define YAGLPP_SET_WINDOW_ASPECT_RATIO		-420
#define YAGLPP_SET_WINDOW_MONITOR			-430
#define YAGLPP_SET_WINDOW_OPACITY			-440
#define YAGLPP_SET_WINDOW_POS				-450
#define YAGLPP_SET_WINDOW_SIZE				-460
#define YAGLPP_SET_WINDOW_SIZE_LIMITS		-470
#define YAGLPP_SET_WINDOW_TITLE				-480
#define YAGLPP_SHOW_WINDOW					-500
#define YAGLPP_UNSET_CURSOR					-510
#define YAGLPP_UNSET_WINDOW_ASPECT_RATIO	-520
#define YAGLPP_UNSET_WINDOW_ICON			-530
#define YAGLPP_UNSET_WINDOW_MONITOR			-540

#pragma comment(lib, YAGLPP_GLFW_LIB)
extern int _loadGL(void* proc);
extern char* _copyString(const char*);
namespace glfw {
#ifdef YAGLPP_NO_AFX_LAYOUT
Thread Window::noAfxMainThread; // Definition
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT

void Window::_applySetting(ContextSetting* setting)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	if (setting == nullptr)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, YAGLPP_CONTEXT_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, YAGLPP_CONTEXT_VERSION_MINOR);

#if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR >= 2)
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
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_CHAR, codepoint, 0, 0, 0, pWindow);
	}
}

void Window::_create(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting)
{
	_YAGLPP_ASSERT_(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	_applySetting(setting);
	_m.pWindow = glfwCreateWindow(width, height, title, nullptr, shared);
	_YAGLPP_ASSERT_(isWindow()); // FAILED TO CREATE GLFW WINDOW
	_bindCallback();
}

void Window::_createFullscreen(const char* title, Monitor& monitor, GLFWwindow* shared, ContextSetting* setting)
{
	_YAGLPP_ASSERT_(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	_applySetting(setting);
	_m.iWindowFullscreen = GLFW_TRUE;
	const GLFWvidmode* pVidmode = monitor.getVideoMode();
	glfwWindowHint(GLFW_RED_BITS, pVidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, pVidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, pVidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, pVidmode->refreshRate);
	_m.pWindow = glfwCreateWindow(pVidmode->width, pVidmode->height, title, monitor._monitor(), shared);
	_YAGLPP_ASSERT_(isWindow()); // FAILED TO CREATE GLFW WINDOW
	_bindCallback();
}

void Window::_cursorEnterCallback(GLFWwindow* window, int entered)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iCursorEntered = entered;
	pWindow->onCursorEnter(entered);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_CURSOR_ENTER, entered, 0, 0, 0, pWindow);
	}
}

void Window::_cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.dCursorPosX = xpos;
	pWindow->_m.dCursorPosY = ypos;
	pWindow->onCursorPos(xpos, ypos);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_CURSOR_POS, xpos, ypos, 0, 0, pWindow);
	}
}

void Window::_dropCallback(GLFWwindow* window, int pathcount, const char** paths)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->onDrop(pathcount, paths);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		const char** pPaths = (const char**)_YAGLPP_MALLOC_(sizeof(WPARAM) * pathcount);
		for (int i = 0; i < pathcount; i++)
		{
			pPaths[i] = _copyString(paths[i]);
		}
		pThread->_message(YAGLPP_DROP, pathcount, pPaths, 0, 0, pWindow);
	}
}

void Window::_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iFramebufferWidth = width;
	pWindow->_m.iFramebufferHeight = height;
	pWindow->onFramebufferSize(width, height);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_FRAMEBUFFER_SIZE, width, height, 0, 0, pWindow);
	}
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
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_KEY, key, scancode, action, mods, pWindow);
	}
}

void Window::_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iMouseButton = button;
	pWindow->_m.iMouseAction = action;
	pWindow->_m.iKeyMods = mods;
	pWindow->onMouseButton((MouseButton)button, (MouseAction)action, (KeyModifier)mods);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_MOUSE_BUTTON, button, action, mods, 0, pWindow);
	}
}

void Window::_scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.dScrollOffsetX = xoffset;
	pWindow->_m.dScrollOffsetY = yoffset;
	pWindow->onScroll(xoffset, yoffset);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_SCROLL, xoffset, yoffset, 0, 0, pWindow);
	}
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
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_CLOSE, 0, 0, 0, 0, pWindow);
	}
}

void Window::_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.fWindowContentScaleX = xscale;
	pWindow->_m.fWindowContentScaleY = yscale;
	pWindow->onWindowContentScale(xscale, yscale);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_CONTENT_SCALE, xscale, yscale, 0, 0, pWindow);
	}
}

void Window::_windowFocusCallback(GLFWwindow* window, int focused)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowFocused = focused;
	pWindow->onWindowFocus(focused);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_FOCUS, focused, 0, 0, 0, pWindow);
	}
}

void Window::_windowIconifyCallback(GLFWwindow* window, int iconified)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowIconified = iconified;
	pWindow->onWindowIconify(iconified);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_ICONIFY, iconified, 0, 0, 0, pWindow);
	}
}

void Window::_windowMaximizeCallback(GLFWwindow* window, int maximized)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->_m.iWindowMaximized = maximized;
	pWindow->onWindowMaximize(maximized);
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_MAXIMIZE, maximized, 0, 0, 0, pWindow);
	}
}

void Window::_windowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (pWindow->_m.iWindowFullscreen == GLFW_FALSE)
	{
		pWindow->_m.iWindowPosX = xpos;
		pWindow->_m.iWindowPosY = ypos;
		pWindow->onWindowPos(xpos, ypos);
		Thread* pThread = pWindow->_m.pThread;
		if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
		{
			pThread->_message(YAGLPP_WINDOW_POS, xpos, ypos, 0, 0, pWindow);
		}
	}
}

void Window::_windowRefreshCallback(GLFWwindow* window)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	pWindow->onWindowRefresh();
	Thread* pThread = pWindow->_m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		pThread->_message(YAGLPP_WINDOW_REFRESH, 0, 0, 0, 0, pWindow);
	}
}

void Window::_windowSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pWindow = (Window*)glfwGetWindowUserPointer(window);
	if (pWindow->_m.iWindowFullscreen == GLFW_FALSE)
	{
		pWindow->_m.iWindowWidth = width;
		pWindow->_m.iWindowHeight = height;
		pWindow->onWindowPos(width, height);
		Thread* pThread = pWindow->_m.pThread;
		if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
		{
			pThread->_message(YAGLPP_WINDOW_SIZE, width, height, 0, 0, pWindow);
		}
	}
}

void Window::destroyWindow()
{
	if (isMainThreadCurrent())
	{
		glfwDestroyWindow(_window());
		_m.pWindow = nullptr;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_DESTROY_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::focusWindow()
{
	if (isMainThreadCurrent())
	{
		glfwFocusWindow(_window());
		_m.iWindowFocused = GLFW_TRUE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_FOCUS_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::getWindowMonitor(Monitor& monitor)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(_window());
	_YAGLPP_ASSERT_(pMonitor == nullptr); // GLFW WINDOW OBJECT IS NOT IN FULLSCREEN MODE
	monitor._select(pMonitor);
}

void Window::hideWindow()
{
	if (isMainThreadCurrent())
	{
		glfwHideWindow(_window());
		_m.iWindowVisible = GLFW_FALSE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_HIDE_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::iconifyWindow()
{
	if (isMainThreadCurrent())
	{
		glfwIconifyWindow(_window());
		_m.iWindowIconified = GLFW_TRUE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_ICONIFY_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::makeContextCurrent()
{
	static int sLoaded = GLFW_FALSE;
	_YAGLPP_ASSERT_(_m.pThread == nullptr); // WINDOW'S CONTEXT HAS BEEN MADE CURRENT
	Thread* pThread = getCurrentThread();
	if (pThread->_m.pWindow)
	{
		pThread->_m.pWindow->_m.pThread = nullptr;
	}
	_m.pThread = pThread;
	pThread->_m.pWindow = this;
	glfwMakeContextCurrent(_window());
	if (sLoaded == 0)
	{
		sLoaded = _loadGL(glfwGetProcAddress);
		_YAGLPP_ASSERT_(sLoaded == GLFW_TRUE); // FAILED TO LOAD OPENGL CONTEXT
	}
}

void Window::makeContextNonCurrent()
{
	Thread* pThread = getCurrentThread();
	_YAGLPP_ASSERT_(pThread == _m.pThread); // WINDOW'S CONTEXT HAS NOT BEEN MADE CURRENT
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
	else Thread::_s.pMainThread->_message(YAGLPP_MAXIMIZE_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::requestWindowAttention()
{
	if (isMainThreadCurrent())
	{
		glfwRequestWindowAttention(_window());
	}
	else Thread::_s.pMainThread->_message(YAGLPP_REQUEST_WINDOW_ATTENTION, 0, 0, 0, 0, (LPVOID)this);
}

void Window::restoreWindow()
{
	if (isMainThreadCurrent())
	{
		glfwRestoreWindow(_window());
		_m.iWindowIconified = GLFW_FALSE;
		_m.iWindowMaximized = GLFW_FALSE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_RESTORE_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

void Window::setClipboardString(_In_z_ const char* string)
{
	if (isMainThreadCurrent())
	{
		glfwSetClipboardString(_window(), string);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_CLIPBOARD_STRING, _copyString(string), 0, 0, 0, (LPVOID)this);
}

void Window::setCursorPos(double xpos, double ypos)
{
	if (isMainThreadCurrent())
	{
		glfwSetCursorPos(_window(), xpos, ypos);
		_m.dCursorPosX = xpos;
		_m.dCursorPosY = ypos;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_CURSOR_POS, xpos, ypos, 0, 0, (LPVOID)this);
}

void Window::setWindowAspectRatio(int numer, int denom)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowAspectRatio(_window(), numer, denom);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_ASPECT_RATIO, numer, denom, 0, 0, (LPVOID)this);
}

void Window::setWindowIcon(StbImage& si)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	glfwSetWindowIcon(_window(), 1, &glfwImage);
}

#ifndef YAGLPP_NO_FREEIMAGE
void Window::setWindowIcon(FreeImage& freeImage)
{
	GLFWimage glfwImage;
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwImage.pixels = freeImage.allocateImage(&glfwImage.width, &glfwImage.height, freeImage.findLargestPage());
	if (glfwImage.pixels)
	{
		glfwSetWindowIcon(_window(), 1, &glfwImage);
		_YAGLPP_FREE_(glfwImage.pixels);
	}
}

void Window::setWindowIcon(int rcid)
{
	FreeImage freeImage;
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	if (freeImage.loadIcon(rcid) > 0) setWindowIcon(freeImage);
}

void Window::setWindowIcon(_In_z_ const char* filepath)
{
	FreeImage freeImage;
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	if (freeImage.loadIcon(filepath) > 0) setWindowIcon(freeImage);
}
#endif // #ifndef YAGLPP_NO_FREEIMAGE

void Window::setWindowMonitor()
{
	if (isMainThreadCurrent())
	{
		Monitor monitor(0U);
		getWindowPos();
		getWindowSize();
		setWindowMonitor(monitor);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_MONITOR, 0, 0, 0, 0, (LPVOID)this);
}

void Window::setWindowMonitor(Monitor& monitor)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.iWindowFullscreen = GLFW_TRUE;
	const GLFWvidmode* pVidmode = monitor.getVideoMode();
	glfwWindowHint(GLFW_RED_BITS, pVidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, pVidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, pVidmode->blueBits);
	glfwSetWindowMonitor(_window(), monitor._monitor(), 0, 0, pVidmode->width, pVidmode->height, pVidmode->refreshRate);
}

void Window::setWindowOpacity(float opacity)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowOpacity(_window(), opacity);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_OPACITY, opacity, 0, 0, 0, (LPVOID)this);
}

void Window::setWindowPos(int xpos, int ypos)
{
	if (isMainThreadCurrent())
	{
		_YAGLPP_ASSERT_(_m.iWindowFullscreen == GLFW_FALSE); // MUST NOT BE USED IN FULLSCREEN MODE
		glfwSetWindowPos(_window(), xpos, ypos);
		_m.iWindowPosX = xpos;
		_m.iWindowPosY = ypos;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_POS, xpos, ypos, 0, 0, (LPVOID)this);
}

void Window::setWindowSize(int width, int height)
{
	if (isMainThreadCurrent())
	{
		_YAGLPP_ASSERT_(_m.iWindowFullscreen == GLFW_FALSE); // MUST NOT BE USED IN FULLSCREEN MODE
		glfwSetWindowSize(_window(), width, height);
		_m.iWindowWidth = width;
		_m.iWindowHeight = height;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_SIZE, width, height, 0, 0, (LPVOID)this);
}

void Window::setWindowSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowSizeLimits(_window(), minwidth, minheight, maxwidth, maxheight);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_SIZE_LIMITS, minwidth, minheight, maxwidth, maxheight, (LPVOID)this);
}

void Window::setWindowTitle(_In_z_ const char* title)
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowTitle(_window(), title);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SET_WINDOW_TITLE, _copyString(title), 0, 0, 0, (LPVOID)this);
}

void Window::showWindow()
{
	if (isMainThreadCurrent())
	{
		glfwShowWindow(_window());
		_m.iWindowVisible = GLFW_TRUE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_SHOW_WINDOW, 0, 0, 0, 0, (LPVOID)this);
}

bool Window::translateMessage(_In_ Message* msg)
{
	Window* pWindow = (Window*)msg->sender;
	if (isMainThreadCurrent())
	{
		switch (msg->msgid)
		{
		case YAGLPP_DESTROY_WINDOW:
			pWindow->destroyWindow();
			break;

		case YAGLPP_FOCUS_WINDOW:
			pWindow->focusWindow();
			break;

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
			pWindow->setClipboardString((char*)msg->x.v);
			_YAGLPP_FREE_(msg->x.v);
			break;

		case YAGLPP_SET_CURSOR_POS:
			pWindow->setCursorPos(msg->x.d, msg->y.d);
			break;

		case YAGLPP_SET_WINDOW_ASPECT_RATIO:
			pWindow->setWindowAspectRatio(msg->x.i, msg->y.i);
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
			pWindow->setWindowTitle((char*)msg->x.v);
			_YAGLPP_FREE_(msg->x.v);
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
			return false;
		}
		pWindow->onWindowTransfer();
		Thread* pThread = pWindow->_m.pThread;
		if (pThread != nullptr)
		{
			pThread->_message(YAGLPP_WINDOW_TRANSFER, 0, 0, 0, 0, pWindow);
		}
		return true;
	}

	const char** pDrop;
	switch (msg->msgid)
	{
	case YAGLPP_CHAR:
		pWindow->onChar(msg->x.ui);
		break;

	case YAGLPP_CURSOR_ENTER:
		pWindow->onCursorEnter(msg->x.b);
		break;

	case YAGLPP_CURSOR_POS:
		pWindow->onCursorPos(msg->x.d, msg->y.d);
		break;

	case YAGLPP_DROP:
		pDrop = (const char**)msg->y.v;
		pWindow->onDrop(msg->x.i, pDrop);
		for (int i = 0; i < msg->x.i; i++)
		{
			_YAGLPP_FREE_((void*)pDrop[i]);
		}
		_YAGLPP_FREE_((void*)pDrop);
		break;

	case YAGLPP_FRAMEBUFFER_SIZE:
		pWindow->onFramebufferSize(msg->x.i, msg->y.i);
		break;

	case YAGLPP_KEY:
		pWindow->onKey((KeyboardKey)msg->x.i, msg->y.i, (KeyAction)msg->z.i, (KeyModifier)msg->w.i);
		break;

	case YAGLPP_MOUSE_BUTTON:
		pWindow->onMouseButton((MouseButton)msg->x.i, (MouseAction)msg->y.i, (KeyModifier)msg->z.i);
		break;

	case YAGLPP_SCROLL:
		pWindow->onScroll(msg->x.d, msg->y.d);
		break;

	case YAGLPP_WINDOW_CLOSE:
		pWindow->onWindowClose();
		break;

	case YAGLPP_WINDOW_CONTENT_SCALE:
		pWindow->onWindowContentScale(msg->x.f, msg->y.f);
		break;

	case YAGLPP_WINDOW_FOCUS:
		pWindow->onWindowFocus(msg->x.b);
		break;

	case YAGLPP_WINDOW_ICONIFY:
		pWindow->onWindowIconify(msg->x.b);
		break;

	case YAGLPP_WINDOW_MAXIMIZE:
		pWindow->onWindowMaximize(msg->x.b);
		break;

	case YAGLPP_WINDOW_POS:
		pWindow->onWindowPos(msg->x.i, msg->y.i);
		break;

	case YAGLPP_WINDOW_REFRESH:
		pWindow->onWindowRefresh();
		break;

	case YAGLPP_WINDOW_SIZE:
		pWindow->onWindowSize(msg->x.i, msg->y.i);
		break;

	case YAGLPP_WINDOW_TRANSFER:
		pWindow->onWindowTransfer();
		break;
		
	default:
		return false;
	}
	return true;
}

void Window::unsetCursor()
{
	if (isMainThreadCurrent())
	{
		glfwSetCursor(_window(), nullptr);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_UNSET_CURSOR, 0, 0, 0, 0, (LPVOID)this);
}

void Window::unsetWindowAspectRatio()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowAspectRatio(_window(), GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_UNSET_WINDOW_ASPECT_RATIO, 0, 0, 0, 0, (LPVOID)this);
}

void Window::unsetWindowIcon()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowIcon(_window(), 0, nullptr);
	}
	else Thread::_s.pMainThread->_message(YAGLPP_UNSET_WINDOW_ICON, 0, 0, 0, 0, (LPVOID)this);
}

void Window::unsetWindowMonitor()
{
	if (isMainThreadCurrent())
	{
		glfwSetWindowMonitor(_window(), nullptr, _m.iWindowPosX, _m.iWindowPosY, _m.iWindowWidth, _m.iWindowHeight, GLFW_DONT_CARE);
		_m.iWindowFullscreen = GLFW_FALSE;
	}
	else Thread::_s.pMainThread->_message(YAGLPP_UNSET_WINDOW_MONITOR, 0, 0, 0, 0, (LPVOID)this);
}

bool Window::windowShouldClose()
{
	_YAGLPP_ASSERT_(!getCurrentThread()->_dispatch()); // DISPATCH IS MISSING FOR A THREAD WITH NON-EMPTY QUEUE
	return isWindow() ? (bool)glfwWindowShouldClose(_window()) : true;
}

#ifdef _DEBUG
int Window::_getInputMode(int mode)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetInputMode(_window(), mode);
}

int Window::_getWindowAttrib(int attrib)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetWindowAttrib(_window(), attrib);
}

void Window::_errorCallback(int code, const char* description)
{
	std::cout << "GLFW ERROR OCCURED WITH THE CODE <" << code << ">: " << description << std::endl;
	_YAGLPP_ASSERT_(false); // GLFW LIBRARY ERROR
}

void Window::_setInputMode(int mode, int value)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetInputMode(_window(), mode, value);
}

void Window::_setWindowAttrib(int attrib, int value)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetWindowAttrib(_window(), attrib, value);
}

GLFWwindow* Window::_window() const
{
	_YAGLPP_ASSERT_(isWindow()); // GLFW WINDOW OBJECT IS EMPTY
	return _m.pWindow;
}

_Ret_maybenull_z_ const char* Window::getClipboardString()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetClipboardString(_window());
}

void Window::getCursorPos()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetCursorPos(_window(), &_m.dCursorPosX, &_m.dCursorPosY);
}

void Window::getFramebufferSize()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetFramebufferSize(_window(), &_m.iFramebufferWidth, &_m.iFramebufferHeight);
}

KeyAction Window::getKey(KeyboardKey key) const
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (KeyAction)glfwGetKey(_window(), (int)key);
}

MouseAction Window::getMouseButton(MouseButton button)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (MouseAction)glfwGetMouseButton(_window(), (int)button);
}

void Window::getWindowContentScale()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetWindowContentScale(_window(), &_m.fWindowContentScaleX, &_m.fWindowContentScaleY);
}

void Window::getWindowFrameSize()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetWindowFrameSize(_window(), &_m.iWindowFrameLeft, &_m.iWindowFrameTop, &_m.iWindowFrameRight, &_m.iWindowFrameBottom);
}

float Window::getWindowOpacity()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetWindowOpacity(_window());
}

void Window::getWindowPos()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(_m.iWindowFullscreen == GLFW_FALSE); // MUST NOT BE USED IN FULLSCREEN MODE
	glfwGetWindowPos(_window(), &_m.iWindowPosX, &_m.iWindowPosY);
}

void Window::getWindowSize()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(_m.iWindowFullscreen == GLFW_FALSE); // MUST NOT BE USED IN FULLSCREEN MODE
	glfwGetWindowSize(_window(), &_m.iWindowWidth, &_m.iWindowHeight);
}

void Window::setCursor(Cursor& cursor)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetCursor(_window(), cursor._cursor());
}

void Window::setWindowIcon(int count, _In_reads_(count) const GLFWimage* images)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetWindowIcon(_window(), count, images);
}

#ifdef YAGLPP_NO_GLFW_LEGACY
_Ret_maybenull_z_ const char* Window::getWindowTitle() const
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetWindowTitle(_window());
}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
#endif // #ifdef _DEBUG
} // namespace glfw
