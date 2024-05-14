#define YAGLPP_BUILD_LIB
#include <yaglpp/Monitor.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
namespace glfw {
Monitor::_SDATA::_SDATA()
{
	getMonitors();
	m_pConnected = nullptr;
	glfwSetMonitorCallback(&_monitorCallback);
}

void Monitor::_init()
{
	m_fXscale = 0;
	m_fYscale = 0;
	m_iWidthMM = 0;
	m_iHeightMM = 0;
	m_iVidcount = 0;
	m_pName = nullptr;
	m_pMonitor = nullptr;
	m_pSelected = nullptr;
	m_pVidmodes = nullptr;
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
	YAGLPP_ASSERT(m_pMonitor == nullptr); // GLFW MONITOR OBJECT MUST BE DESELECTED
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
	glfwSetMonitorUserPointer(monitor, this);
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
	for (int i = 0; i < s_Data.m_iMcount; i++)
	{
		const char* zName = glfwGetMonitorName(s_Data.m_pMonitors[i]);
		if (strcmp(zName, name) == 0)
		{
			_select(s_Data.m_pMonitors[i]);
			return;
		}
	}
	if (isMonitor()) deselectMonitor();
}

#ifdef _DEBUG
GLFWmonitor* Monitor::_monitor()
{
	if (m_pMonitor == nullptr)
	{
		selectMonitor();
		YAGLPP_ASSERT(isMonitor()); // NO MONITORS IN THE SYSTEM WERE FOUND
	}
	return m_pMonitor;
}

void Monitor::selectMonitor(Window& window)
{
	GLFWmonitor* pMonitor = glfwGetWindowMonitor(window._window());
	YAGLPP_ASSERT(pMonitor == nullptr); // GLFW WINDOW OBJECT IS NOT IN FULLSCREEN MODE
	_select(pMonitor);
}
#endif // #ifdef _DEBUG
} // namespace glfw
