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
		MonitorConnectedCallback* m_pConnected = nullptr;
		_SDATA();
		void getMonitors()
		{
			m_pMonitors = glfwGetMonitors(&m_iMcount);
		}
	} s_Data;
	int m_iXpos = 0;							// Monitor x-pos of work area
	int m_iYpos = 0;							// Monitor y-pos of work area
	int m_iWidth = 0;							// Monitor width of work area
	int m_iHidth = 0;							// Monitor height of work area
	int m_iWidthMM = 0;							// Monitor width in mm
	int m_iHeightMM = 0;						// Monitor height in mm
	int m_iVidcount = 0;						// Video mode count
	float m_fXscale = 0.0f;						// Monitor x-scale
	float m_fYscale = 0.0f;						// Monitor y-scale
	const char* m_pName = nullptr;				// Monitor name
	GLFWmonitor* m_pMonitor = nullptr;			// Selected monitor
	const GLFWvidmode* m_pSelected = nullptr;	// Selected video mode
	const GLFWvidmode* m_pVidmodes = nullptr;	// Available video modes
	GLFWmonitor* _monitor() const;
	static void _monitorCallback(GLFWmonitor* monitor, int event);
	void _select(GLFWmonitor* monitor);

protected:
	/*Monitor disconnected event handler*/
	virtual void onDisconnect() {}

public:
	/*(1) Constructs an empty monitor object*/
	Monitor() {}

	/*(2) Constructs monitor object with <selectMonitor>, 0u selects primary monitor*/
	Monitor(unsigned int mindex)
	{
		selectMonitor(mindex);
	}

	/*(3) Constructs monitor object with <selectMonitor>*/
	Monitor(_In_z_ const char* name)
	{
		selectMonitor(name);
	}

	/*(4) Constructs monitor object with <selectMonitor>*/
	Monitor(Window& window)
	{
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

	/*Unconditionally deselects selected monitor*/
	void deselectMonitor();

	/*Returns the current gamma ramp of the selected monitor
	@param Current gamma ramp*/
	_Ret_notnull_ const GLFWgammaramp* getGammaRamp() const
	{
		return glfwGetGammaRamp(_monitor());
	}

	/*This function retrieves the current content scale for the selected monitor. The updated values could be then retreived with the inline <getMonitorContentScaleX> and <getMonitorContentScaleY> functions*/
	void getMonitorContentScale()
	{
		glfwGetMonitorContentScale(_monitor(), &m_fXscale, &m_fYscale);
	}

	/*Retreives monitor x-axis of the content scale, retreived since last call to the <getMonitorContentScale> function
	@return Monitor content x-scale*/
	float getMonitorContentScaleX() const
	{
		return m_fXscale;
	}

	/*Retreives monitor y-axis of the content scale, retreived since last call to the <getMonitorContentScale> function
	@return Monitor content y-scale*/
	float getMonitorContentScaleY() const
	{
		return m_fYscale;
	}

	/*Retrieves the number of monitors available in the system
	@return The number of available monitors*/
	static int getMonitorCount()
	{
		return s_Data.m_iMcount;
	}

	/*Returns the name of selected monitor. The method is available during <onDisconnect> event
	@return Name of selected monitor, or NULL if none selected*/
	_Ret_maybenull_ const char* getMonitorName() const
	{
		return m_pName;
	}

	/*This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the selected monitor. The updated values could be then retreived with the inline <getMonitorXpos> and <getMonitorYpos> functions*/
	void getMonitorPos()
	{
		glfwGetMonitorPos(_monitor(), &m_iXpos, &m_iYpos);
	}

	/*Retreives physical width, in millimetres, of the display area of the selected monitor
	@return Monitor physical width*/
	int getMonitorPhysicalWidth() const
	{
		return m_iWidthMM;
	}

	/*Retreives physical height, in millimetres, of the display area of the selected monitor
	@return Monitor physical height*/
	int getMonitorPhysicalHeight() const
	{
		return m_iHeightMM;
	}

	/*Retreives monitor x-coordinate of the upper-left corner of the work area retreived since last call of the <getMonitorWorkarea> or <getMonitorWorkarea> functions
	@return The x-coordinate of the upper-left corner of the work area*/
	int getMonitorXpos() const
	{
		return m_iXpos;
	}

	/*Retreives monitor y-coordinate of the upper-left corner of the work area retreived since last call of the <getMonitorWorkarea> or <getMonitorWorkarea> functions
	@return The y-coordinate of the upper-left corner of the work area*/
	int getMonitorYpos() const
	{
		return m_iYpos;
	}

	/*Retreives monitor width of the work area retreived since last call of the <getMonitorWorkarea> function
	@return The width of the work area size*/
	int getMonitorWidth() const
	{
		return m_iWidth;
	}
	
	/*Retreives monitor height of the work area retreived since last call of the <getMonitorWorkarea> function
	@return The height of the work area size*/
	int getMonitorHeight() const
	{
		return m_iHidth;
	}

	/*This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the work area of the selected monitor along with the work area size in screen coordinates. The updated values could be then retreived with the inline <getMonitorXpos>, <getMonitorYpos>, <getMonitorWidth> and <getMonitorHeight> functions*/
	void getMonitorWorkarea()
	{
		glfwGetMonitorWorkarea(_monitor(), &m_iXpos, &m_iYpos, &m_iWidth, &m_iHidth);
	}

	/*(1) Returns current mode of selected monitor
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode() const
	{
		return glfwGetVideoMode(_monitor());
	}

	/*(2) Returns video mode by index, compare if equal to current video mode
	@param The index of desired video mode
	@param [out] Pointer to boolean which is set to true if equal to current video mode, ignored if NULL
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode(unsigned int vindex, _Out_opt_ bool* current = nullptr);

	/*Retrieves count of available video modes of selected monitor
	@return The number of available video modes*/
	int getVideoModeCount() const
	{
		return m_iVidcount;
	}

	/*Checks if selected monitor is valid monitor object
	@return True if valid monitor object, false otherwise*/
	bool isMonitor() const
	{
		return m_pMonitor != nullptr;
	}

	/*(1) Selects monitor by index and its current video mode. The index 0u selects primary monitor
	@param The monitor index, default 0u*/
	void selectMonitor(unsigned int mindex = 0u);

	/*(2) Selects monitor by name and its current video mode
	@param [in] The monitor name*/
	void selectMonitor(_In_z_ const char* name);

	/*(3) Select current monitor and its current video mode of specified window object
	@param The window object currently in fullscreen mode*/
	void selectMonitor(Window& window);

	/*(1) Selects current video mode*/
	void selectVideoMode()
	{
		m_pSelected = getVideoMode();
	}

	/*(2) Selects video mode by index
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
inline GLFWmonitor* Monitor::_monitor() const
{
	return m_pMonitor;
}

inline void Monitor::selectMonitor(unsigned int mindex)
{
	_select(s_Data.m_pMonitors[mindex]);
}

inline void Monitor::selectMonitor(Window& window)
{
	_select(glfwGetWindowMonitor(window._window()));
}
#endif // #ifndef _DEBUG
} // namespace glfw
