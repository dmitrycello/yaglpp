#define GLPP_BUILD_LIB
#include <glpp/Window.h>
#include <glpp/StbImage.h>
#include <glpp/FreeImage.h>
#pragma comment(lib, GLPP_GLFW_LIB)
extern int _loadGL(void* proc);
namespace glfw {
Window::_SDATA::_SDATA()
{
#ifndef GLPP_COCOA_CHDIR_RESOURCES
	glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
#endif // #ifndef GLPP_COCOA_CHDIR_RESOURCES

#ifndef GLPP_COCOA_MENUBAR
	glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
#endif // #ifndef GLPP_COCOA_MENUBAR

#ifndef GLPP_JOYSTICK_HAT_BUTTONS
	glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
#endif // #ifndef GLPP_JOYSTICK_HAT_BUTTONS

	if (!glfwInit()) // Initialize GLFW
	{
		exit(-1);
	}

#ifdef _DEBUG
	glfwSetErrorCallback(&_errorCallback);
#endif // #ifdef _DEBUG
}

void Window::_applySetting(ContextSetting* setting)
{
	if (setting == nullptr)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLPP_CONTEXT_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLPP_CONTEXT_VERSION_MINOR);

#if (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR >= 2)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else // #if (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR >= 2)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif // #if (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR >= 2)
	}
	else
	{
		setting->openglProfile = ((setting->contextVersionMajor == 3) || (setting->contextVersionMinor >= 2)) ?
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

#ifdef GLPP_NO_GLFW_LEGACY
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
#endif // #ifdef GLPP_NO_GLFW_LEGACY
	}
}

void Window::_bindCallback()
{
	double dCursorX, dCursorY; // Calculate initial hovered attribute
	m_iWindowHovered = GL_FALSE;
	glfwGetCursorPos(m_pWindow, &dCursorX, &dCursorY);
	if ((dCursorX >= 0.0) || (dCursorY >= 0.0))
	{
		int iWidth, iHeight;
		glfwGetWindowSize(m_pWindow, &iWidth, &iHeight);
		if ((dCursorX < iWidth) || (dCursorY < iHeight))
		{
			m_iWindowHovered = GL_TRUE;
		}
	}
	m_iWindowFocused = glfwGetWindowAttrib(m_pWindow, GLFW_FOCUSED);
	m_iWindowMaximized = glfwGetWindowAttrib(m_pWindow, GLFW_MAXIMIZED);
	getWindowContentScale();
	getCursorPos();
	getWindowFrameSize();
	getWindowPos();
	getWindowSize();
	glfwSetDropCallback(m_pWindow, &_dropCallback);
	glfwSetCharCallback(m_pWindow, &_charCallback);
	glfwSetCursorEnterCallback(m_pWindow, &_cursorEnterCallback);
	glfwSetCursorPosCallback(m_pWindow, &_cursorPosCallback);
	glfwSetFramebufferSizeCallback(m_pWindow, &_framebufferSizeCallback);
	glfwSetKeyCallback(m_pWindow, &_keyCallback);
	glfwSetMouseButtonCallback(m_pWindow, &_mouseButtonCallback);
	glfwSetScrollCallback(m_pWindow, &_scrollCallback);
	glfwSetWindowCloseCallback(m_pWindow, &_windowCloseCallback);
	glfwSetWindowContentScaleCallback(m_pWindow, &_windowContentScaleCallback);
	glfwSetWindowFocusCallback(m_pWindow, &_windowFocusCallback);
	glfwSetWindowIconifyCallback(m_pWindow, &_windowIconifyCallback);
	glfwSetWindowMaximizeCallback(m_pWindow, &_windowMaximizeCallback);
	glfwSetWindowPosCallback(m_pWindow, &_windowPosCallback);
	glfwSetWindowRefreshCallback(m_pWindow, &_windowRefreshCallback);
	glfwSetWindowSizeCallback(m_pWindow, &_windowSizeCallback);
	glfwSetWindowUserPointer(m_pWindow, this);
}

bool Window::_create(int width, int height, const char* title, GLFWwindow* shared, ContextSetting* setting)
{
	GLPP_ASSERT(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	_applySetting(setting);
	if (m_pWindow = glfwCreateWindow(width, height, title, nullptr, shared))
	{
		_bindCallback();
	}
	return isWindow();
}

bool Window::_createFullscreen(const char* title, Monitor& fullscreen, GLFWwindow* shared, ContextSetting* setting)
{
	GLPP_ASSERT(!isWindow()); // GLFW WINDOW OBJECT MUST BE EMPTY
	m_bWindowFullscreen = true;
	const GLFWvidmode* pVidmode = fullscreen.getVideoMode();
	if (setting == nullptr)
	{
		_applySetting(setting);
		glfwWindowHint(GLFW_RED_BITS, pVidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, pVidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, pVidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, pVidmode->refreshRate);
	}
	else
	{
		setting->redBits = pVidmode->redBits;
		setting->greenBits = pVidmode->greenBits;
		setting->blueBits = pVidmode->blueBits;
		setting->refreshRate = pVidmode->refreshRate;
		_applySetting(setting);
	}
	if (m_pWindow = glfwCreateWindow(pVidmode->width, pVidmode->height, title, fullscreen._monitor(), shared))
	{
		_bindCallback();
	}
	return isWindow();
}

void Window::_cursorEnterCallback(GLFWwindow* window, int entered)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iWindowHovered = entered;
	if (entered)
	{
		pThis->onMouseEnter();
	}
	else
	{
		pThis->onMouseLeave();
	}
}

void Window::_cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_dCursorPosX = xpos;
	pThis->m_dCursorPosY = ypos;
	int iMouseCaptureButton = pThis->m_iMouseCaptureButton;
	bool bCaptured = iMouseCaptureButton != GLFW_DONT_CARE;
	pThis->onMouseMove(xpos, ypos, bCaptured); // Mouse move
	if (bCaptured)
	{
		pThis->onMouseDrag((MouseButton)iMouseCaptureButton, xpos, ypos); // Mouse drag
	}
}

void Window::_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iFramebufferWidth = width;
	pThis->m_iFramebufferHeight = height;
	pThis->onFramebuffer(width, height);
}

void Window::_init()
{
	m_pThread = nullptr;
	m_pWindow = nullptr;
	m_bWindowFullscreen = false;
	m_dCursorPosX = 0.0;
	m_dCursorPosY = 0.0;
	m_dMouseClickX = 0.0;
	m_dMouseClickY = 0.0;
	m_dMouseDblClickTime = 0.0;
	m_dMouseDblClickX = 0.0;
	m_dMouseDblClickY = 0.0;
	m_fXscale = 0.0f;
	m_fYscale = 0.0f;
	m_iFramebufferHeight = 0;
	m_iFramebufferWidth = 0;
	m_iKeyMods = 0;
	m_iMouseCaptureButton = GLFW_DONT_CARE;
	m_iMouseCaptureMods = 0;
	m_iMouseClickButton = GLFW_DONT_CARE;
	m_iMouseDblClickButton = GLFW_DONT_CARE;
	m_iWindowClose = 0;
	m_iWindowFrameBottom = 0;
	m_iWindowFrameLeft = 0;
	m_iWindowFrameRight = 0;
	m_iWindowFrameTop = 0;
	m_iWindowFocused = 0;
	m_iWindowHovered = 0;
	m_iWindowIconified = 0;
	m_iWindowMaximized = 0;
	m_iWindowPosX = 0;
	m_iWindowPosY = 0;
	m_iWindowSizeHeight = 0;
	m_iWindowSizeWidth = 0;
}

void Window::_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iKeyMods = mods; // Save new key mods
	int iMouseCaptureMods = pThis->m_iMouseCaptureMods;
	int iMouseCaptureButton = pThis->m_iMouseCaptureButton;
	if ((iMouseCaptureButton != GLFW_DONT_CARE) && (iMouseCaptureMods != mods)) // Release capture if mods changed
	{
		pThis->m_iMouseCaptureButton = GLFW_DONT_CARE;
		pThis->onMouseRelease((MouseButton)iMouseCaptureButton);
	}
	switch (action)
	{
	case GLFW_REPEAT:
		pThis->onKeyRepeat((KeyboardKey)key, scancode);
		break;
	case GLFW_PRESS:
		pThis->onKeyDown((KeyboardKey)key, scancode);
		break;
	case GLFW_RELEASE:
		pThis->onKeyUp((KeyboardKey)key, scancode);
	}
	if ((pThis->m_iWindowClose == GLFW_TRUE) && (action == GLFW_RELEASE) && (mods == 0))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE); // Mods stuck on exit FIX
	}
}

void Window::_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	static double sDblClick = GetDoubleClickTime() / 1000.0; // System double click delay
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iKeyMods = mods; // Save key mods
	int iMouseCaptureButton = pThis->m_iMouseCaptureButton; // Check captured state
	if (iMouseCaptureButton != GLFW_DONT_CARE)
	{
		if (glfwGetMouseButton(window, iMouseCaptureButton) == GLFW_PRESS)
		{
			return; // No events if captured button currently active
		}
		pThis->m_iMouseCaptureButton = GLFW_DONT_CARE;
		pThis->onMouseRelease((MouseButton)iMouseCaptureButton); // Release capture
	}

	double dX, dY, dTime = glfwGetTime();
	glfwGetCursorPos(window, &dX, &dY); // Cursor current coordinates
	if (action == GLFW_RELEASE)
	{
		pThis->onMouseUp((MouseButton)button); // Mouse up
		if ((pThis->m_iMouseClickButton == button) && (pThis->m_dMouseClickX == dX) && (pThis->m_dMouseClickY == dY))
		{
			bool bDblClick = (pThis->m_iMouseDblClickButton == button) && (pThis->m_dMouseDblClickX == dX) &&
				(pThis->m_dMouseDblClickY == dY) && (pThis->m_dMouseDblClickTime > dTime);
			pThis->onMouseClick((MouseButton)button, bDblClick); // Mouse click (Down->Up at same cursor position)
			if (bDblClick)
			{
				pThis->onMouseDblClick((MouseButton)button); // Mouse dblclick (Up->Up at same cursor position within delay)
				pThis->m_dMouseDblClickTime = 0.0;
			}
			else
			{
				pThis->m_dMouseDblClickX = dX;
				pThis->m_dMouseDblClickY = dY;
				pThis->m_iMouseDblClickButton = button;
				pThis->m_dMouseDblClickTime = dTime + sDblClick;
			}
		}
	}
	else if (action == GLFW_PRESS)
	{
		pThis->onMouseDown((MouseButton)button); // Mouse down
		pThis->m_dMouseClickX = dX;
		pThis->m_dMouseClickY = dY;
		pThis->m_iMouseClickButton = button;
		if (pThis->onMouseCapture((MouseButton)button)) // Capture mouse if event handler returns true
		{
			pThis->m_iMouseCaptureMods = mods;
			pThis->m_iMouseCaptureButton = button;
		}
	}
}

void Window::_windowCloseCallback(GLFWwindow* window)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->onClose();
	if (pThis->m_iKeyMods)
	{
		pThis->m_iWindowClose = GLFW_TRUE; // Wait for exit flag
		glfwSetWindowShouldClose(window, GLFW_FALSE);
	}
}

void Window::_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_fXscale = xscale;
	pThis->m_fYscale = yscale;
	pThis->onContentScale(xscale, yscale);
}

void Window::_windowFocusCallback(GLFWwindow* window, int focused)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iWindowFocused = focused;
	if (focused)
	{
		pThis->onFocus();
	}
	else
	{
		pThis->onBlur();
	}
}

void Window::_windowIconifyCallback(GLFWwindow* window, int iconified)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iWindowIconified = iconified;
	if (iconified)
	{
		pThis->onIconify();
	}
	else
	{
		pThis->onRestore();
	}
}

void Window::_windowMaximizeCallback(GLFWwindow* window, int maximized)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	pThis->m_iWindowMaximized = maximized;
	if (maximized)
	{
		pThis->onMaximize();
	}
	else
	{
		pThis->onRestore();
	}
}

void Window::_windowPosCallback(GLFWwindow* window, int xpos, int ypos)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	if (!pThis->isWindowFullscreen())
	{
		pThis->m_iWindowPosX = xpos;
		pThis->m_iWindowPosY = ypos;
	}
	pThis->onPosition(xpos, ypos);
}

void Window::_windowSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* pThis = (Window*)glfwGetWindowUserPointer(window);
	if (!pThis->isWindowFullscreen())
	{
		pThis->m_iWindowSizeWidth = width;
		pThis->m_iWindowSizeHeight = height;
	}
	pThis->onResize(width, height);
}

void Window::getWindowMonitor(Monitor& monitor)
{
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(_window());
	GLPP_ASSERT(pMonitor == nullptr); // GLFW WINDOW OBJECT IS NOT IN FULLSCREEN MODE
	monitor._select(pMonitor);
}

bool Window::isWindowFullscreen()
{
	if (m_bWindowFullscreen)
	{
		m_bWindowFullscreen = (glfwGetWindowMonitor(_window()) != nullptr);
	}
	return m_bWindowFullscreen;
}

void Window::makeContextCurrent(_In_ Thread* thread)
{
	static int sLoaded = 0;
	GLPP_ASSERT(!isContextCurrent()); // GLFW WINDOW OBJECT HAS CURRENT CONTEXT
	GLPP_ASSERT(thread->isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
	glfwMakeContextCurrent(_window());
	if (sLoaded == 0)
	{
		sLoaded = _loadGL(glfwGetProcAddress);
		GLPP_ASSERT(sLoaded != 0); // FAILED TO LOAD OPENGL CONTEXT
	}
	m_pThread = thread;
}

void Window::makeContextNonCurrent()
{
	GLPP_ASSERT(getContextThread()->isCurrentThread()); // METHOD IS CALLED BY ANOTHER THREAD
	glfwMakeContextCurrent(nullptr);
	m_pThread = nullptr;
}

void Window::setWindowIcon(StbImage& si)
{
	GLPP_ASSERT(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	glfwSetWindowIcon(_window(), 1, &glfwImage);
}

#ifdef GLPP_FREEIMAGE_LIB
void Window::setWindowIcon(FreeImage& freeImage)
{
	GLFWimage glfwImage;
	glfwImage.pixels = freeImage.allocateImage(&glfwImage.width, &glfwImage.height, freeImage.findLargestPage());
	if (glfwImage.pixels)
	{
		glfwSetWindowIcon(_window(), 1, &glfwImage);
		GLPP_FREE(glfwImage.pixels);
	}
}

void Window::setWindowIcon(int rcid)
{
	FreeImage freeImage;
	if (freeImage.loadIcon(rcid) > 0) setWindowIcon(freeImage);
}

void Window::setWindowIcon(_In_z_ const char* filepath)
{
	FreeImage freeImage;
	if (freeImage.loadIcon(filepath) > 0) setWindowIcon(freeImage);
}
#endif // #ifdef GLPP_FREEIMAGE_LIB

void Window::setWindowMonitor(Monitor& fullscreen)
{
	m_bWindowFullscreen = true;
	const GLFWvidmode* pVidmode = fullscreen.getVideoMode();
	glfwWindowHint(GLFW_RED_BITS, pVidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, pVidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, pVidmode->blueBits);
	glfwSetWindowMonitor(_window(), fullscreen._monitor(), 0, 0, pVidmode->width, pVidmode->height, pVidmode->refreshRate);
}

#ifdef _DEBUG
void Window::_errorCallback(int code, const char* description)
{
	std::cout << "GLFW ERROR OCCURED WITH THE CODE <" << code << ">: " << description << std::endl;
	GLPP_ASSERT(false); // GLFW LIBRARY ERROR
}

GLFWwindow* Window::_window()
{
	GLPP_ASSERT(m_pWindow != nullptr); // GLFW WINDOW OBJECT IS EMPTY
	return m_pWindow;
}

_Ret_notnull_ Thread* Window::getContextThread()
{
	GLPP_ASSERT(m_pThread != nullptr); // GLFW WINDOW OBJECT HAS NO CURRENT CONTEXT
	return m_pThread;
}
#endif // #ifdef _DEBUG
} // namespace glfw
