#pragma once
#include "glfw3pp.h"
namespace glfw {
/*GLWF type of monitor connected callback routine
@param The UTF-8 encoded name of the monitor*/
typedef void (WINAPI MonitorConnectedCallback)(const char* name);

/*Sets the function for the monitor connected callback routine
@param GLWF type of monitor connected callback routine*/
void setMonitorkConnectedCallback(MonitorConnectedCallback callback);

/*GLFW monitor object root class*/
class Monitor
{
private:
	friend class Window;
	static struct _SDATA {
		int m_iMcount;
		GLFWmonitor** m_pMonitors;
		MonitorConnectedCallback* m_pConnected;
		_SDATA();
		void getMonitors()
		{
			m_pMonitors = glfwGetMonitors(&m_iMcount);
		}
	} s_Data;
	float m_fXscale; // Monitor x-scale
	float m_fYscale; // Monitor y-scale
	int m_iWidthMM; // Monitor width in mm
	int m_iHeightMM; // Monitor height in mm
	int m_iVidcount; // Video mode count
	const char* m_pName; // Monitor name
	GLFWmonitor* m_pMonitor; // Selected monitor
	const GLFWvidmode* m_pSelected; // Selected video mode
	const GLFWvidmode* m_pVidmodes; // Available video modes
	void _init();
	GLFWmonitor* _monitor();
	static void _monitorCallback(GLFWmonitor* monitor, int event);
	void _select(GLFWmonitor* monitor);

protected:
	/*Monitor disconnected event handler*/
	virtual void onDisconnect() {}

public:
	/*(1) Constructs an empty monitor object*/
	Monitor()
	{
		_init();
	}

	/*(2) Constructs monitor object with <selectMonitor>*/
	Monitor(_In_z_ const char* name)
	{
		m_pMonitor = nullptr;
		selectMonitor(name);
	}

	/*(3) Constructs monitor object with <selectMonitor>*/
	Monitor(Window& window)
	{
		m_pMonitor = nullptr;
		selectMonitor(window);
	}

	/*Cleans up the valid monitor object*/
	~Monitor()
	{
		if (isMonitor())
		{
			deselectMonitor();
		}
	}

	/*Unconditionally deselect specified monitor*/
	void deselectMonitor()
	{
		glfwSetMonitorUserPointer(_monitor(), nullptr);
		_init();
	}

	/*Returns the current gamma ramp of the specified monitor
	@param Current gamma ramp*/
	_Ret_notnull_ const GLFWgammaramp* getGammaRamp()
	{
		return glfwGetGammaRamp(_monitor());
	}

	/*Retreives monitor x-axis content scale
	@return Monitor content x-scale*/
	float getMonitorContentScaleX()
	{
		return m_fXscale;
	}

	/*Retreives monitor y-axis content scale
	@return Monitor content y-scale*/
	float getMonitorContentScaleY()
	{
		return m_fYscale;
	}

	/*Retrieve number of available monitors
	@return The number of available monitors*/
	static int getMonitorCount()
	{
		return s_Data.m_iMcount;
	}

	/*Return name of selected monitor. The method is available during <onDisconnect> event
	@return Name of selected monitor, or NULL if none selected*/
	_Ret_maybenull_ const char* getMonitorName()
	{
		return m_pName;
	}

	/*Retreives monitor physical width, in millimetres, of the display area of the specified monitor
	@return Monitor physical width*/
	int getMonitorPhysicalWidth()
	{
		return m_iWidthMM;
	}

	/*Retreives monitor physical height, in millimetres, of the display area of the specified monitor
	@return Monitor physical height*/
	int getMonitorPhysicalHeight()
	{
		return m_iHeightMM;
	}

	/*This function returns the position, in screen coordinates, of the upper-left corner of the selected monitor
	@param [out] Pointer to store the monitor x-coordinate, or NULL
	@param [out] Pointer to store the monitor y-coordinate, or NULL*/
	void getMonitorPos(_Out_opt_ int* xpos, _Out_opt_ int* ypos)
	{
		glfwGetMonitorPos(_monitor(), xpos, ypos);
	}

	/*This function returns the position, in screen coordinates, of the upper-left corner of the work area of the specified monitor along with the work area size in screen coordinates
	@param [out] Pointer to store the monitor x-coordinate, or NULL
	@param [out] Pointer to store the monitor y-coordinate, or NULL
	@param [out] Pointer to store the monitor width, or NULL
	@param [out] Pointer to store the monitor height, or NULL*/
	void getMonitorWorkarea(_Out_opt_ int* xpos, _Out_opt_ int* ypos, _Out_opt_ int* width, _Out_opt_ int* height)
	{
		glfwGetMonitorWorkarea(_monitor(), xpos, ypos, width, height);
	}

	/*(1) Return current mode of selected monitor
	@return Video mode structure*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode()
	{
		return glfwGetVideoMode(_monitor());
	}

	/*(2) Return video mode by index, compare if equal to current video mode
	@param The index of desired video mode
	@param [out] Pointer to boolean which is set to true if equal to current video mode, ignored if NULL
	@return Video mode structure*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode(unsigned int vindex, _Out_opt_ bool* current = nullptr);

	/*Retrieve count of available video modes of selected monitor
	@return The number of available video modes*/
	int getVideoModeCount()
	{
		return m_iVidcount;
	}

	/*Check if selected monitor is valid monitor object
	@return True if valid monitor object, false otherwise*/
	bool isMonitor()
	{
		return m_pMonitor != nullptr;
	}

	/*(1) Select primary monitor and its current video mode*/
	void selectMonitor()
	{
		_select(glfwGetPrimaryMonitor());
	}

	/*(2) Select monitor by name and its current video mode
	@param [in] The monitor name*/
	void selectMonitor(_In_z_ const char* name);

	/*(3) Select current monitor of specified window object
	@param The window object currently in fullscreen mode*/
	void selectMonitor(Window& window);

	/*(1) Re-select current video mode*/
	void selectVideoMode()
	{
		m_pSelected = getVideoMode();
	}

	/*(2) Select video mode by index
	@param Video mode index*/
	void selectVideoMode(unsigned int vindex)
	{
		m_pSelected = getVideoMode(vindex);
	}

	/*This function generates an appropriately sized gamma ramp from the specified exponent and then calls <setGammaRamp> with it
	@param The desired exponent*/
	void setGamma(float gamma)
	{
		glfwSetGamma(_monitor(), gamma);
	}

	/*This function sets the current gamma ramp for the specified monitor
	@param [in] The gamma ramp to use*/
	void setGammaRamp(_In_ const GLFWgammaramp* ramp)
	{
		glfwSetGammaRamp(_monitor(), ramp);
	}

	/*Sets the function for the monitor connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void setMonitorkConnectedCallback(MonitorConnectedCallback callback)
	{
		s_Data.m_pConnected = callback;
	}
}; // class Monitor

inline void setMonitorkConnectedCallback(MonitorConnectedCallback callback)
{
	Monitor::setMonitorkConnectedCallback(callback);
}
} // namespace glfw

#include "Window.h"
namespace glfw {
#ifndef _DEBUG
inline GLFWmonitor* Monitor::_monitor()
{
	if (m_pMonitor == nullptr) selectMonitor();
	return m_pMonitor;
}

inline void Monitor::selectMonitor(Window& window)
{
	_select(glfwGetWindowMonitor(window._window()));
}
#endif // #ifndef _DEBUG
} // namespace glfw
