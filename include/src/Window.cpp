#define YAGLPP_BUILD_LIB
#include <yaglpp/Window.h>
#include <yaglpp/Monitor.h>
#include <yaglpp/StbImage.h>
#include <yaglpp/FreeImage.h>
#define YAGLPP_CHAR							-500
#define YAGLPP_CURSOR_ENTER					-510
#define YAGLPP_CURSOR_POS					-520
#define YAGLPP_DROP							-530
#define YAGLPP_FRAMEBUFFER_SIZE				-540
#define YAGLPP_KEY							-550
#define YAGLPP_MOUSE_BUTTON					-560
#define YAGLPP_SCROLL						-570
#define YAGLPP_WINDOW_CLOSE					-580
#define YAGLPP_WINDOW_CONTENT_SCALE			-590
#define YAGLPP_WINDOW_FOCUS					-600
#define YAGLPP_WINDOW_ICONIFY				-610
#define YAGLPP_WINDOW_MAXIMIZE				-620
#define YAGLPP_WINDOW_POS					-630
#define YAGLPP_WINDOW_REFRESH				-640
#define YAGLPP_WINDOW_SIZE					-650
#define YAGLPP_WINDOW_TRANSFER				-660
#pragma comment(lib, YAGLPP_GLFW_LIB)
extern int _loadGL(void*);
extern char* _copyString(const char*);

namespace glfw {
#ifdef YAGLPP_NO_AFX_LAYOUT
Thread Window::noAfxMainThread; // Definition
#endif // #ifdef YAGLPP_NO_AFX_LAYOUT

void _dropFree(int pathcount, const char** paths)
{
	for (int i = 0; i < pathcount; i++)
	{
		_YAGLPP_FREE_((void*)paths[i]);
	}
	_YAGLPP_FREE_((void*)paths);
}

bool Window::_apiCallback(int msgid, Param x, Param y, Param z, Param w)
{
	Thread* pThread = _m.pThread;
	if ((pThread != nullptr) && (pThread != Thread::_s.pMainThread))
	{
		Message msg = { msgid, x, y, z, w, pThread };
		return pThread->_message(&msg);
	}
	return false;
}

bool Window::_apiTransfer(int msgid, Param x, Param y, Param z, Param w)
{
	Thread* pThread = _m.pThread;
	if (pThread != nullptr)
	{
		Message msg = { msgid, x, y, z, w, pThread };
		return Thread::_s.pMainThread->_message(&msg);
	}
	return false;
}

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
	pWindow->_apiCallback(YAGLPP_CHAR, codepoint, 0, 0, 0);
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
	const char** pPaths = (const char**)_YAGLPP_MALLOC_(sizeof(WPARAM) * pathcount);
	for (int i = 0; i < pathcount; i++)
	{
		pPaths[i] = _copyString(paths[i]);
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
	if (pWindow->_m.iWindowFullscreen == GLFW_FALSE)
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
	if (pWindow->_m.iWindowFullscreen == GLFW_FALSE)
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
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(_window());
	_YAGLPP_ASSERT_(pMonitor == nullptr); // GLFW WINDOW OBJECT IS NOT IN FULLSCREEN MODE
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
	if (_m.iWindowFullscreen == GLFW_FALSE)
	{
		if (isMainThreadCurrent())
		{
			glfwGetWindowPos(_window(), &_m.iWindowPosX, &_m.iWindowPosY);
		}
		else _apiTransfer(YAGLPP_GET_WINDOW_POS, 0, 0, 0, 0);
	}
}

void Window::getWindowSize()
{
	if (_m.iWindowFullscreen == GLFW_FALSE)
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
		char* pString = _copyString(string);
		if (!_apiTransfer(YAGLPP_SET_CLIPBOARD_STRING, pString, 0, 0, 0))
		{
			_YAGLPP_FREE_(pString); // Cleanup if message blocked
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
	else _apiTransfer(YAGLPP_SET_WINDOW_MONITOR, 0, 0, 0, 0);
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
	else _apiTransfer(YAGLPP_SET_WINDOW_OPACITY, opacity, 0, 0, 0);
}

void Window::setWindowPos(int xpos, int ypos)
{
	if (_m.iWindowFullscreen == GLFW_FALSE)
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
	if (_m.iWindowFullscreen == GLFW_FALSE)
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
		char* pString = _copyString(title);
		if (!_apiTransfer(YAGLPP_SET_WINDOW_TITLE, pString, 0, 0, 0))
		{
			_YAGLPP_FREE_(pString); // Cleanup if message blocked
		}
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
			msg->x.p = (void*)_copyString(pWindow->getClipboardString());
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
			msg->x.p = (void*)_copyString(pWindow->getWindowTitle());
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
			_YAGLPP_ASSERT_(false); // UNKNOWN API MESSAGE
		}
		pWindow->onWindowTransfer(msg);
		Thread* pThread = pWindow->_m.pThread;
		if (pThread != nullptr)
		{
			if (!pThread->_message(msg) && bCleanup)
			{
				_YAGLPP_FREE_(msg->x.p); // Cleanup if message blocked
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
		_YAGLPP_FREE_(msg->x.p); // Cleanup string
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
		_m.iWindowFullscreen = GLFW_FALSE;
	}
	else _apiTransfer(YAGLPP_UNSET_WINDOW_MONITOR, 0, 0, 0, 0);
}

bool Window::windowShouldClose()
{
	//_YAGLPP_ASSERT_(!getCurrentThread()->_dispatch()); // DISPATCH IS MISSING FOR A THREAD WITH NON-EMPTY QUEUE
	if (isWindow())
	{
		if (glfwWindowShouldClose(_window()))
		{
			return true;
		}
	}
	return false;
}

#ifdef YAGLPP_NO_GLFW_LEGACY
_Ret_maybenull_z_ const char* Window::getWindowTitle()
{
	if (isMainThreadCurrent())
	{
		return glfwGetWindowTitle(_window());
	}
	_apiTransfer(YAGLPP_GET_WINDOW_TITLE, 0, 0, 0, 0);
	return nullptr;
}
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY

#ifdef _DEBUG
void Window::_errorCallback(int code, const char* description)
{
	std::cout << "GLFW ERROR OCCURED WITH THE CODE <" << code << ">: " << description << std::endl;
	_YAGLPP_ASSERT_(false); // GLFW LIBRARY ERROR
}

GLFWwindow* Window::_window() const
{
	_YAGLPP_ASSERT_(isWindow()); // GLFW WINDOW OBJECT IS EMPTY
	return _m.pWindow;
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
#endif // #ifdef _DEBUG
} // namespace glfw
