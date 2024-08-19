#pragma once
#include "glfw3pp.h"
namespace glfw {
/*GLWF type of monitor connected callback routine
@param The UTF-8 encoded name of the monitor*/
typedef void (WINAPI MonitorConnectedCallback)(const char* name);

/*(M) GLFW monitor object root class*/
class Monitor
{
private:
	friend class Thread;
	friend class Window;
	// Monitor object static data structure
	static struct _SDATA {
		int iMcount; // Monitor count
		GLFWmonitor** pMonitors; // Monitor array
		MonitorConnectedCallback* pMConnected; // Monitor connected callback
		void initialize();
		void loadMonitors()
		{
			pMonitors = glfwGetMonitors(&iMcount);
		}
	} _s;

	// Monitor object member data structure
	struct _MDATA {
		float fMonitorContentScaleX; // Monitor x-scale
		float fMonitorContentScaleY; // Monitor y-scale
		int iMonitorPosX; // Monitor x-pos of work area
		int iMonitorPosY; // Monitor y-pos of work area
		int iMonitorPhysicalWidth; // Monitor width in mm
		int iMonitorPhysicalHeight; // Monitor height in mm
		int iMonitorWidth; // Monitor width of work area
		int iMonitorHidth; // Monitor height of work area
		int iVidcount; // Video mode count
		GLFWmonitor* pMonitor; // Selected monitor
		const char* pName; // Monitor name
		const GLFWvidmode* pSelected; // Selected video mode
		const GLFWvidmode* pVidmodes; // Available video modes
	} _m;

	GLFWmonitor* _monitor() const;
	static void _monitorCallback(GLFWmonitor* monitor, int event);
	void _select(GLFWmonitor* monitor);

protected:
	/*Monitor disconnected event handler*/
	virtual void onDisconnect() {}

public:
	/*(1) Constructs an empty monitor object*/
	Monitor()
	{
		memset(&_m, 0, sizeof(_MDATA));
	}

	/*(M) (2) Constructs monitor object with <selectMonitor>, 0u selects primary monitor*/
	Monitor(unsigned int mindex) : Monitor()
	{
		selectMonitor(mindex);
	}

	/*(M) (3) Constructs monitor object with <selectMonitor>*/
	Monitor(_In_z_ const char* name) : Monitor()
	{
		selectMonitor(name);
	}

	/*(M) (4) Constructs monitor object with <selectMonitor>*/
	Monitor(Window& window) : Monitor()
	{
		selectMonitor(window);
	}

	/*(M) Cleans up the valid monitor object*/
	~Monitor()
	{
		if (isMonitor())
		{
			deselectMonitor();
		}
	}

	/*Unconditionally deselects selected monitor*/
	void deselectMonitor()
	{
		glfwSetMonitorUserPointer(_monitor(), nullptr);
		memset(&_m, 0, sizeof(_MDATA));
	}

	/*(M) Returns the current gamma ramp of the selected monitor. Used as a getter of <gammaRamp> property
	@param Current gamma ramp*/
	_Ret_notnull_ const GLFWgammaramp* getGammaRamp();

	/*(M) This function retrieves the current content scale for the selected monitor. The updated values could be then retreived with the inline <getMonitorContentScaleX> and <getMonitorContentScaleY> functions*/
	void getMonitorContentScale();

	/*Retreives the monitor x-axis of the content scale after the <getMonitorContentScale> call. Used as a getter of <monitorContentScaleX> property
	@return Monitor content x-scale*/
	float getMonitorContentScaleX() const
	{
		return _m.fMonitorContentScaleX;
	}

	/*Retreives the monitor y-axis of the content scale after the <getMonitorContentScale> call. Used as a getter of <monitorContentScaleY> property
	@return Monitor content y-scale*/
	float getMonitorContentScaleY() const
	{
		return _m.fMonitorContentScaleY;
	}

	/*Retrieves the number of monitors available in the system
	@return The number of available monitors*/
	static int getMonitorCount()
	{
		return _s.iMcount;
	}

	/*Returns the name of selected monitor. The method is available during <onDisconnect> event. Used as a getter of <monitorName> property
	@return Name of selected monitor, or NULL if none selected*/
	_Ret_maybenull_ const char* getMonitorName() const
	{
		return _m.pName;
	}

	/*(M) This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the selected monitor. The updated values could be then retreived with the inline <getMonitorXpos> and <getMonitorYpos> functions*/
	void getMonitorPos();

	/*Retreives the monitor x-coordinate of the upper-left corner of the work area after the <getMonitorWorkarea> or <getMonitorWorkarea> call. Used as a getter of <monitorPosX> property
	@return The x-coordinate of the upper-left corner of the work area*/
	int getMonitorPosX() const
	{
		return _m.iMonitorPosX;
	}

	/*Retreives the monitor y-coordinate of the upper-left corner of the work area after the <getMonitorWorkarea> or <getMonitorWorkarea> call. Used as a getter of <monitorPosY> property
	@return The y-coordinate of the upper-left corner of the work area*/
	int getMonitorPosY() const
	{
		return _m.iMonitorPosY;
	}

	/*Retreives the physical width, in millimetres, of the display area of the selected monitor. Used as a getter of <monitorPhysicalWidth> property
	@return Monitor physical width*/
	int getMonitorPhysicalWidth() const
	{
		return _m.iMonitorPhysicalWidth;
	}

	/*Retreives the physical height, in millimetres, of the display area of the selected monitor. Used as a getter of <monitorPhysicalHeight> property
	@return Monitor physical height*/
	int getMonitorPhysicalHeight() const
	{
		return _m.iMonitorPhysicalHeight;
	}

	/*Retreives the monitor width of the work area after the <getMonitorWorkarea> call. Used as a getter of <monitorWidth> property
	@return The width of the work area size*/
	int getMonitorWidth() const
	{
		return _m.iMonitorWidth;
	}
	
	/*Retreives the monitor height of the work area after the <getMonitorWorkarea> call. Used as a getter of <monitorHeight> property
	@return The height of the work area size*/
	int getMonitorHeight() const
	{
		return _m.iMonitorHidth;
	}

	/*(M) This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the work area of the selected monitor along with the work area size in screen coordinates. The updated values could be then retreived with the inline <getMonitorXpos>, <getMonitorYpos>, <getMonitorWidth> and <getMonitorHeight> functions*/
	void getMonitorWorkarea();

	/*(M) (1) Returns current mode of selected monitor
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode();

	/*(M) (2) Returns video mode by index, compare if equal to current video mode
	@param The index of desired video mode
	@param [out] Pointer to boolean which is set to true if equal to current video mode, ignored if NULL
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* getVideoMode(unsigned int vindex, _Out_opt_ bool* current = nullptr);

	/*Retrieves the count of available video modes of selected monitor. Used as a getter of <videoModeCount> property
	@return The number of available video modes*/
	int getVideoModeCount() const
	{
		return _m.iVidcount;
	}

	/*Checks if selected monitor is valid monitor object. Used as a getter of <monitor> property
	@return True if valid monitor object, false otherwise*/
	bool isMonitor() const
	{
		return _m.pMonitor != nullptr;
	}

	/*(M) (1) Selects monitor by index and its current video mode. The index 0u selects primary monitor
	@param The monitor index, default 0u*/
	void selectMonitor(unsigned int mindex = 0u);

	/*(M) (2) Selects monitor by name and its current video mode
	@param [in] The monitor name*/
	void selectMonitor(_In_z_ const char* name);

	/*(M) (3) Select current monitor and its current video mode of specified window object
	@param The window object currently in fullscreen mode*/
	void selectMonitor(Window& window);

	/*(M) (1) Selects current video mode*/
	void selectVideoMode()
	{
		_m.pSelected = getVideoMode();
	}

	/*(M) (2) Selects video mode by index
	@param Video mode index*/
	void selectVideoMode(unsigned int vindex)
	{
		_m.pSelected = getVideoMode(vindex);
	}

	/*(M) This function generates an appropriately sized gamma ramp from the specified exponent and then calls <setGammaRamp> with it
	@param The desired exponent*/
	void setGamma(float gamma);

	/*(M) This function sets the current gamma ramp for the specified monitor. Used as a setter of <gammaRamp> property
	@param [in] The gamma ramp to use*/
	void setGammaRamp(_In_ const GLFWgammaramp* ramp);

	/*Sets the function for the monitor connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void setMonitorkConnectedCallback(MonitorConnectedCallback callback)
	{
		_s.pMConnected = callback;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(M) Read-write property for current gamma ramp of the specified monitor*/
	__declspec(property(get = getGammaRamp, put = setGammaRamp)) const GLFWgammaramp* gammaRamp;

	/*Read-only property to check if selected monitor is valid monitor object*/
	__declspec(property(get = isMonitor)) bool monitor;

	/*Read-only property for name of selected monitor*/
	__declspec(property(get = getMonitorName)) const char* monitorName;

	/*Read-only property for monitor x-axis of the content scale after the <getMonitorContentScale> call*/
	__declspec(property(get = getMonitorContentScaleX)) float monitorContentScaleX;

	/*Read-only property for monitor y-axis of the content scale after the <getMonitorContentScale> call*/
	__declspec(property(get = getMonitorContentScaleY)) float monitorContentScaleY;

	/*Read-only property for physical width, in millimetres, of the display area of the selected monitor*/
	__declspec(property(get = getMonitorPhysicalWidth)) int monitorPhysicalWidth;

	/*Read-only property for physical height, in millimetres, of the display area of the selected monitor*/
	__declspec(property(get = getMonitorPhysicalHeight)) int monitorPhysicalHeight;

	/*Read-only property for monitor x-coordinate of the upper-left corner of the work area after the <getMonitorWorkarea> or <getMonitorWorkarea> call*/
	__declspec(property(get = getMonitorPosX)) int monitorPosX;

	/*Read-only property for monitor y-coordinate of the upper-left corner of the work area after the <getMonitorWorkarea> or <getMonitorWorkarea> call*/
	__declspec(property(get = getMonitorPosY)) int monitorPosY;

	/*Read-only property for monitor width of the work area after the <getMonitorWorkarea> call*/
	__declspec(property(get = getMonitorWidth)) int monitorWidth;

	/*Read-only property for monitor height of the work area after the <getMonitorWorkarea> call*/
	__declspec(property(get = getMonitorHeight)) int monitorHeight;

	/*Read-only property for count of available video modes of selected monitor*/
	__declspec(property(get = getVideoModeCount)) int videoModeCount;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class Monitor

/*Sets the function for the monitor connected callback routine
@param GLWF type of monitor connected callback routine*/
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
	return _m.pMonitor;
}

inline _Ret_notnull_ const GLFWgammaramp* Monitor::getGammaRamp()
{
	return glfwGetGammaRamp(_m.pMonitor);
}

inline void Monitor::getMonitorContentScale()
{
	glfwGetMonitorContentScale(_m.pMonitor, &_m.fMonitorContentScaleX, &_m.fMonitorContentScaleY);
}

inline void Monitor::getMonitorPos()
{
	glfwGetMonitorPos(_m.pMonitor, &_m.iMonitorPosX, &_m.iMonitorPosY);
}

inline void Monitor::getMonitorWorkarea()
{
	glfwGetMonitorWorkarea(_m.pMonitor, &_m.iMonitorPosX, &_m.iMonitorPosY, &_m.iMonitorWidth, &_m.iMonitorHidth);
}

inline _Ret_notnull_ const GLFWvidmode* Monitor::getVideoMode()
{
	return glfwGetVideoMode(_m.pMonitor);
}

inline void Monitor::selectMonitor(unsigned int mindex)
{
	_select(_s.pMonitors[mindex]);
}

inline void Monitor::selectMonitor(Window& window)
{
	_select(glfwGetWindowMonitor(window._m.pWindow));
}

inline void Monitor::setGamma(float gamma)
{
	glfwSetGamma(_m.pMonitor, gamma);
}

inline void Monitor::setGammaRamp(_In_ const GLFWgammaramp* ramp)
{
	glfwSetGammaRamp(_m.pMonitor, ramp);
}
#endif // #ifndef _DEBUG
} // namespace glfw
