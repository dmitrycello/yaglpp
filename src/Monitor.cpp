#define YAGLPP_BUILD_LIB
#include <yaglpp/Monitor.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
namespace glfw {
Monitor::_SDATA::_SDATA()
{
	getMonitors();
	glfwSetMonitorCallback(&_monitorCallback);
}

void Monitor::_monitorCallback(GLFWmonitor* monitor, int event)
{
	s_Data.getMonitors();
	if (event == GLFW_DISCONNECTED)
	{
		Monitor* pClass = (Monitor*)glfwGetMonitorUserPointer(monitor);
		if (pClass != nullptr)
		{
			pClass->onDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW MONITOR <" << pClass->m_pName << "> WAS DISCONNECTED" << std::endl;
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

		if (s_Data.m_pConnected != nullptr)
		{
			s_Data.m_pConnected(pName);
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
	m_pMonitor = monitor;
	m_pName = glfwGetMonitorName(monitor);
	m_pSelected = glfwGetVideoMode(monitor);
	m_pVidmodes = glfwGetVideoModes(monitor, &m_iVidcount);
	glfwGetMonitorContentScale(monitor, &m_fXscale, &m_fYscale);
	glfwGetMonitorPhysicalSize(monitor, &m_iWidthMM, &m_iHeightMM);
	glfwGetMonitorWorkarea(monitor, &m_iXpos, &m_iYpos, &m_iWidth, &m_iHidth);
	glfwSetMonitorUserPointer(monitor, this);
}

void Monitor::deselectMonitor()
{
	glfwSetMonitorUserPointer(_monitor(), nullptr);
	memset(this, 0, sizeof(Monitor));
}

_Ret_notnull_ const GLFWvidmode* Monitor::getVideoMode(unsigned int vindex, _Out_opt_ bool* current)
{
	YAGLPP_ASSERT((int)vindex < m_iVidcount); // INVALID VIDEOMODE INDEX PARAMETER
	const GLFWvidmode* pMode = &m_pVidmodes[vindex];
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
	YAGLPP_ASSERT(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	for (int i = 0; i < s_Data.m_iMcount; i++)
	{
		const char* zName = glfwGetMonitorName(s_Data.m_pMonitors[i]);
		if (strcmp(zName, name) == 0)
		{
			_select(s_Data.m_pMonitors[i]);
			return;
		}
	}
}

#ifdef _DEBUG
GLFWmonitor* Monitor::_monitor() const
{
	YAGLPP_ASSERT(isMonitor()); // GLFW MONITOR WAS NOT SELECTED
	return m_pMonitor;
}

void Monitor::selectMonitor(unsigned int mindex)
{
	YAGLPP_ASSERT(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(mindex < (unsigned int)s_Data.m_iMcount); // MONITOR INDEX IS INVALID
	_select(s_Data.m_pMonitors[mindex]);
}

void Monitor::selectMonitor(Window& window)
{
	YAGLPP_ASSERT(!isMonitor()); // GLFW MONITOR OBJECT MUST BE DESELECTED
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(window._window());
	YAGLPP_ASSERT(pMonitor == nullptr); // GLFW WINDOW IS NOT IN FULLSCREEN MODE
	_select(pMonitor);
}
#endif // #ifdef _DEBUG
} // namespace glfw
