#define YAGLPP_BUILD_LIB
#include <yaglpp/Monitor.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
namespace glfw {
Monitor::_SDATA::_SDATA()
{
	memset(this, 0, sizeof(_SDATA));
	getMonitors();
	glfwSetMonitorCallback(&_monitorCallback);
}

void Monitor::_monitorCallback(GLFWmonitor* monitor, int event)
{
	s.getMonitors();
	if (event == GLFW_DISCONNECTED)
	{
		Monitor* pClass = (Monitor*)glfwGetMonitorUserPointer(monitor);
		if (pClass != nullptr)
		{
			pClass->onDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW MONITOR <" << pClass->m.pName << "> WAS DISCONNECTED" << std::endl;
#endif // #ifdef _DEBUG

			pClass->deselectMonitor();
		}
	}
	if (event == GLFW_CONNECTED)
	{
		const char* pName = glfwGetMonitorName(monitor);

#ifdef _DEBUG
		std::cout << "GLFW MONITOR <" << pName << "> WAS CONNECTED" << std::endl;
#endif // #ifdef _DEBUG

		if (s.pConnected != nullptr)
		{
			s.pConnected(pName);
		}
	}
}

void Monitor::_select(GLFWmonitor* monitor)
{
	Monitor* pClass = (Monitor*)glfwGetMonitorUserPointer(monitor);
	if (pClass)
	{
		pClass->deselectMonitor();
	}
	m.pMonitor = monitor;
	m.pName = glfwGetMonitorName(monitor);
	m.pSelected = glfwGetVideoMode(monitor);
	m.pVidmodes = glfwGetVideoModes(monitor, &m.iVidcount);
	glfwGetMonitorContentScale(monitor, &m.fMonitorContentScaleX, &m.fMonitorContentScaleY);
	glfwGetMonitorPhysicalSize(monitor, &m.iMonitorPhysicalWidth, &m.iMonitorPhysicalHeight);
	glfwGetMonitorWorkarea(monitor, &m.iMonitorPosX, &m.iMonitorPosY, &m.iMonitorWidth, &m.iMonitorHidth);
	glfwSetMonitorUserPointer(monitor, this);
}

_Ret_notnull_ const GLFWvidmode* Monitor::getVideoMode(unsigned int vindex, _Out_opt_ bool* current)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_((int)vindex < m.iVidcount); // INVALID VIDEOMODE INDEX PARAMETER
	const GLFWvidmode* pMode = &m.pVidmodes[vindex];
	if (current)
	{
		const GLFWvidmode* pCurrmode = glfwGetVideoMode(_monitor());
		*current = ((pMode->width == pCurrmode->width) && (pMode->height == pCurrmode->height) &&
			(pMode->redBits == pCurrmode->redBits) && (pMode->greenBits == pCurrmode->greenBits) &&
			(pMode->blueBits == pCurrmode->blueBits) && (pMode->refreshRate == pCurrmode->refreshRate));
	}
	return pMode;
}

void Monitor::selectMonitor(_In_z_ const char* name)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	for (int i = 0; i < s.iMcount; i++)
	{
		const char* zName = glfwGetMonitorName(s.pMonitors[i]);
		if (strcmp(zName, name) == 0)
		{
			_select(s.pMonitors[i]);
			return;
		}
	}
}

#ifdef _DEBUG
GLFWmonitor* Monitor::_monitor() const
{
	_YAGLPP_ASSERT_(isMonitor()); // GLFW MONITOR WAS NOT SELECTED
	return m.pMonitor;
}

_Ret_notnull_ const GLFWgammaramp* Monitor::getGammaRamp()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetGammaRamp(_monitor());
}

void Monitor::getMonitorContentScale()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetMonitorContentScale(_monitor(), &m.fMonitorContentScaleX, &m.fMonitorContentScaleY);
}

void Monitor::getMonitorPos()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetMonitorPos(_monitor(), &m.iMonitorPosX, &m.iMonitorPosY);
}

void Monitor::getMonitorWorkarea()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwGetMonitorWorkarea(_monitor(), &m.iMonitorPosX, &m.iMonitorPosY, &m.iMonitorWidth, &m.iMonitorHidth);
}

_Ret_notnull_ const GLFWvidmode* Monitor::getVideoMode()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwGetVideoMode(_monitor());
}

void Monitor::selectMonitor(unsigned int mindex)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	_YAGLPP_ASSERT_(mindex < (unsigned int)s.iMcount); // MONITOR INDEX IS INVALID
	_select(s.pMonitors[mindex]);
}

void Monitor::selectMonitor(Window& window)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(window._window());
	_YAGLPP_ASSERT_(pMonitor == nullptr); // GLFW WINDOW IS NOT IN FULLSCREEN MODE
	_select(pMonitor);
}

void Monitor::setGamma(float gamma)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetGamma(_monitor(), gamma);
}

void Monitor::setGammaRamp(_In_ const GLFWgammaramp* ramp)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	glfwSetGammaRamp(_monitor(), ramp);
}
#endif // #ifdef _DEBUG
} // namespace glfw
