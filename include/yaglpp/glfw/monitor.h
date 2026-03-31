#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_MONITOR_H
#define YAGLPP_MONITOR_H

namespace glfw {
/*(M) GLFW monitor object root class*/
class Monitor
{
	friend class Thread;

public:
	/*GLWF type of monitor connected callback routine
	@param The UTF-8 encoded name of the monitor*/
	typedef void (APIENTRY Connected)(const char* name);

	/*(1) Constructs an empty monitor object*/
	Monitor()
	{
		std::memset(&m_Data, 0, sizeof(MDATA));
	}

	/*(M) (2) Constructs monitor object with <Select>, 0u selects primary monitor*/
	Monitor(unsigned int mindex) : Monitor()
	{
		Select(mindex);
	}

	/*(M) (3) Constructs monitor object with <Select>*/
	Monitor(_In_z_ const char* name) : Monitor()
	{
		Select(name);
	}

	/*(M) (4) Constructs monitor object with <Select>*/
	Monitor(Window& window) : Monitor()
	{
		Select(window);
	}

	/*(M) Cleans up the valid monitor object*/
	~Monitor()
	{
		Deselect();
	}

	/*Unconditionally deselects monitor object*/
	void Deselect();

	/*Gets the last selected opaque monitor object
	@return The opaque GLFW monitor object*/
	_Ret_notnull_ GLFWmonitor* Get() const;

	/*(M) This function retrieves the current content scale for the selected monitor. The updated values could be then retreived with the inline <GetContentScaleX> and <GetContentScaleY> functions*/
	void GetContentScale();

	/*Retreives the monitor x-axis of the content scale after the <GetContentScale> call. MSVC getter for <contentScaleX> property
	@return Monitor content x-scale*/
	float GetContentScaleX() const
	{
		return m_Data.contentScaleX;
	}

	/*Retreives the monitor y-axis of the content scale after the <GetContentScale> call. MSVC getter for <contentScaleY> property
	@return Monitor content y-scale*/
	float GetContentScaleY() const
	{
		return m_Data.contentScaleY;
	}

	/*(M) Returns the current gamma ramp of the selected monitor. MSVC getter for <gammaRamp> property
	@param Current gamma ramp*/
	_Ret_notnull_ const GLFWgammaramp* GetGammaRamp();

	/*Retrieves the number of monitors available in the system
	@return The number of available monitors*/
	static int GetMonitorCount()
	{
		return s_Data.count;
	}

	/*Returns the name of selected monitor. The method is available during <OnDisconnect> event. MSVC getter for <name> property
	@return Name of selected monitor, or NULL if none selected*/
	_Ret_maybenull_ const char* GetName() const
	{
		return m_Data.name;
	}

	/*Retreives the physical width, in millimetres, of the display area of the selected monitor. MSVC getter for <physicalWidth> property
	@return Monitor physical width*/
	int GetPhysicalWidth() const
	{
		return m_Data.physicalWidth;
	}

	/*Retreives the physical height, in millimetres, of the display area of the selected monitor. MSVC getter for <physicalHeight> property
	@return Monitor physical height*/
	int GetPhysicalHeight() const
	{
		return m_Data.physicalHeight;
	}

	/*(M) This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the selected monitor. The updated values could be then retreived with the inline <getMonitorXpos> and <getMonitorYpos> functions*/
	void GetPos();

	/*Retreives the monitor x-coordinate of the upper-left corner of the work area after the <GetWorkarea> or <GetWorkarea> call. MSVC getter for <posX> property
	@return The x-coordinate of the upper-left corner of the work area*/
	int GetPosX() const
	{
		return m_Data.posX;
	}

	/*Retreives the monitor y-coordinate of the upper-left corner of the work area after the <GetWorkarea> or <GetWorkarea> call. MSVC getter for <posY> property
	@return The y-coordinate of the upper-left corner of the work area*/
	int GetPosY() const
	{
		return m_Data.posY;
	}

	/*(M) (1) Returns current mode of selected monitor
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* GetVideoMode();

	/*(M) (2) Returns video mode by index, compare if equal to current video mode
	@param The index of desired video mode
	@param [out] Points to boolean receiving true if equal to current video mode, ignored if NULL
	@return Pointer to video mode data*/
	_Ret_notnull_ const GLFWvidmode* GetVideoMode(unsigned int vindex, _Out_opt_ bool* current = nullptr);

	/*Retrieves the count of available video modes of selected monitor. MSVC getter for <videoModeCount> property
	@return The number of available video modes*/
	int GetVideoModeCount() const
	{
		return m_Data.vidcount;
	}

	/*Retreives the monitor width of the work area after the <GetWorkarea> call. MSVC getter for <width> property
	@return The width of the work area size*/
	int GetWidth() const
	{
		return m_Data.width;
	}

	/*Retreives the monitor height of the work area after the <GetWorkarea> call. MSVC getter for <height> property
	@return The height of the work area size*/
	int GetHeight() const
	{
		return m_Data.heigth;
	}

	/*(M) This function retreives the current position on the virtual desktop, in screen coordinates, of the upper-left corner of the work area of the selected monitor along with the work area size in screen coordinates. The updated values could be then retreived with the inline <getMonitorXpos>, <getMonitorYpos>, <GetWidth> and <GetHeight> functions*/
	void GetWorkarea();

	/*Checks if selected monitor is valid monitor object. MSVC getter for <monitor> property
	@return True if valid monitor object, false otherwise*/
	bool IsMonitor() const
	{
		return m_Data.monitor != nullptr;
	}

	/*(M) (1) Selects monitor by index and its current video mode. The index 0u selects primary monitor
	@param The monitor index, default 0u*/
	void Select(unsigned int mindex = 0u);

	/*(M) (2) Selects monitor by name and its current video mode
	@param [in] The monitor name*/
	void Select(_In_z_ const char* mname);

	/*(M) (3) Select current monitor and its current video mode of specified window object
	@param The window object currently in fullscreen mode*/
	void Select(Window& window);

	/*(M) (1) Selects current video mode*/
	void SelectVideoMode()
	{
		m_Data.vidmode = GetVideoMode();
	}

	/*(M) (2) Selects video mode by index
	@param Video mode index*/
	void SelectVideoMode(unsigned int vindex)
	{
		m_Data.vidmode = GetVideoMode(vindex);
	}

	/*(M) This function generates an appropriately sized gamma ramp from the specified exponent and then calls <SetGammaRamp> with it
	@param The desired exponent*/
	void SetGamma(float gamma);

	/*(M) This function sets the current gamma ramp for the specified monitor. Used as a setter of <gammaRamp> property
	@param [in] The gamma ramp to use*/
	void SetGammaRamp(_In_ const GLFWgammaramp* ramp);

	/*Sets the function for the monitor connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void SetConnectedCallback(Connected callback)
	{
		s_Data.callback = callback;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for monitor x-axis of the content scale after the <GetContentScale> call*/
	__declspec(property(get = GetContentScaleX)) float contentScaleX;

	/*Read-only property for monitor y-axis of the content scale after the <GetContentScale> call*/
	__declspec(property(get = GetContentScaleY)) float contentScaleY;

	/*(M) Read-write property for current gamma ramp of the specified monitor*/
	__declspec(property(get = GetGammaRamp, put = SetGammaRamp)) const GLFWgammaramp* gammaRamp;

	/*Read-only property to check if selected monitor is valid monitor object*/
	__declspec(property(get = IsMonitor)) bool monitor;

	/*Read-only property for name of selected monitor*/
	__declspec(property(get = GetName)) const char* name;

	/*Read-only property for physical width, in millimetres, of the display area of the selected monitor*/
	__declspec(property(get = GetPhysicalWidth)) int physicalWidth;

	/*Read-only property for physical height, in millimetres, of the display area of the selected monitor*/
	__declspec(property(get = GetPhysicalHeight)) int physicalHeight;

	/*Read-only property for monitor x-coordinate of the upper-left corner of the work area after the <GetWorkarea> or <GetWorkarea> call*/
	__declspec(property(get = GetPosX)) int posX;

	/*Read-only property for monitor y-coordinate of the upper-left corner of the work area after the <GetWorkarea> or <GetWorkarea> call*/
	__declspec(property(get = GetPosY)) int posY;

	/*Read-only property for count of available video modes of selected monitor*/
	__declspec(property(get = GetVideoModeCount)) int videoModeCount;

	/*Read-only property for monitor width of the work area after the <GetWorkarea> call*/
	__declspec(property(get = GetWidth)) int width;

	/*Read-only property for monitor height of the work area after the <GetWorkarea> call*/
	__declspec(property(get = GetHeight)) int height;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	/*Monitor disconnected event handler*/
	virtual void OnDisconnect() {}

private:
	// Monitor object member data structure
	struct MDATA {
		float contentScaleX; // Monitor x-scale
		float contentScaleY; // Monitor y-scale
		const char* name; // Monitor name
		int physicalWidth; // Monitor width in mm
		int physicalHeight; // Monitor height in mm
		int posX; // Monitor x-pos of work area
		int posY; // Monitor y-pos of work area
		int width; // Monitor width of work area
		int heigth; // Monitor height of work area
		int vidcount; // Video mode count
		const GLFWvidmode* vidmode; // Selected video mode
		const GLFWvidmode* vidmodes; // Available video modes
		GLFWmonitor* monitor; // Selected monitor object
	} m_Data;

	// Monitor object static data structure
	static struct SDATA {
		int count; // Monitor count
		GLFWmonitor** monitors; // Monitor array
		Connected* callback; // Monitor connected callback
		void initialize();
		void load_monitors()
		{
			monitors = glfwGetMonitors(&count);
		}
	} s_Data;

	static void monitor_callback(GLFWmonitor* monitor, int event);
	void select_monitor(GLFWmonitor* monitor);
}; // class Monitor
} // namespace glfw

//#include <yaglpp/glfw/thread.h>
namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
Monitor::SDATA Monitor::s_Data;
void Monitor::SDATA::initialize()
{
	callback = nullptr; // Initialize monitor data
	load_monitors();
	glfwSetMonitorCallback(&monitor_callback);
}

void Monitor::monitor_callback(GLFWmonitor* monitor, int event)
{
	s_Data.load_monitors();
	if (event == GLFW_DISCONNECTED)
	{
		Monitor* pClass = (Monitor*)glfwGetMonitorUserPointer(monitor);
		if (pClass != nullptr)
		{
			pClass->OnDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW monitor <" << pClass->m_Data.name << "> was disconnected" << std::endl;
#endif // #ifdef _DEBUG

			pClass->Deselect();
		}
	}
	if (event == GLFW_CONNECTED)
	{
		const char* pName = glfwGetMonitorName(monitor);

#ifdef _DEBUG
		std::cout << "GLFW monitor <" << pName << "> was connected" << std::endl;
#endif // #ifdef _DEBUG

		if (s_Data.callback != nullptr)
		{
			s_Data.callback(pName);
		}
	}
}

void Monitor::select_monitor(GLFWmonitor* monitor)
{
	Monitor* pClass = (Monitor*)glfwGetMonitorUserPointer(monitor);
	if (pClass)
	{
		pClass->Deselect();
	}
	m_Data.monitor = monitor;
	m_Data.name = glfwGetMonitorName(monitor);
	m_Data.vidmode = glfwGetVideoMode(monitor);
	m_Data.vidmodes = glfwGetVideoModes(monitor, &m_Data.vidcount);
	glfwGetMonitorContentScale(monitor, &m_Data.contentScaleX, &m_Data.contentScaleY);
	glfwGetMonitorPhysicalSize(monitor, &m_Data.physicalWidth, &m_Data.physicalHeight);
	glfwGetMonitorWorkarea(monitor, &m_Data.posX, &m_Data.posY, &m_Data.width, &m_Data.heigth);
	glfwSetMonitorUserPointer(monitor, this);
}

void Monitor::Deselect()
{
	if (m_Data.monitor != nullptr)
	{
		glfwSetMonitorUserPointer(m_Data.monitor, nullptr);
		std::memset(&m_Data, 0, sizeof(MDATA));
	}
}

_Ret_notnull_ const GLFWvidmode* Monitor::GetVideoMode(unsigned int vindex, _Out_opt_ bool* current)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// INVALID VIDEOMODE INDEX PARAMETER
	YAGLPP_ASSERT((int)vindex < m_Data.vidcount);

	const GLFWvidmode* pMode = &m_Data.vidmodes[vindex];
	if (current)
	{
		const GLFWvidmode* pCurrmode = glfwGetVideoMode(Get());
		*current = ((pMode->width == pCurrmode->width) && (pMode->height == pCurrmode->height) &&
			(pMode->redBits == pCurrmode->redBits) && (pMode->greenBits == pCurrmode->greenBits) &&
			(pMode->blueBits == pCurrmode->blueBits) && (pMode->refreshRate == pCurrmode->refreshRate));
	}
	return pMode;
}

void Monitor::Select(_In_z_ const char* mname)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// GLFW MONITOR OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsMonitor());

	for (int i = 0; i < s_Data.count; i++)
	{
		const char* zName = glfwGetMonitorName(s_Data.monitors[i]);
		if (std::strcmp(zName, mname) == 0)
		{
			select_monitor(s_Data.monitors[i]);
			return;
		}
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
_Ret_notnull_ GLFWmonitor* Monitor::Get() const
{
	// GLFW MONITOR WAS NOT SELECTED
	YAGLPP_ASSERT(IsMonitor());

	return m_Data.monitor;
}

void Monitor::GetContentScale()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetMonitorContentScale(Get(), &m_Data.contentScaleX, &m_Data.contentScaleY);
}

_Ret_notnull_ const GLFWgammaramp* Monitor::GetGammaRamp()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetGammaRamp(Get());
}

void Monitor::GetPos()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetMonitorPos(Get(), &m_Data.posX, &m_Data.posY);
}

_Ret_notnull_ const GLFWvidmode* Monitor::GetVideoMode()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwGetVideoMode(Get());
}

void Monitor::GetWorkarea()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwGetMonitorWorkarea(Get(), &m_Data.posX, &m_Data.posY, &m_Data.width, &m_Data.heigth);
}

void Monitor::Select(unsigned int mindex)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// GLFW MONITOR OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsMonitor());

	// INVALID MONITOR INDEX
	YAGLPP_ASSERT(mindex < (unsigned int)s_Data.count);

	select_monitor(s_Data.monitors[mindex]);
}

void Monitor::SetGamma(float gamma)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetGamma(Get(), gamma);
}

void Monitor::SetGammaRamp(_In_ const GLFWgammaramp* ramp)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	glfwSetGammaRamp(Get(), ramp);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline _Ret_notnull_ GLFWmonitor* Monitor::Get() const
{
	return m_Data.monitor;
}

inline void Monitor::GetContentScale()
{
	glfwGetMonitorContentScale(m_Data.monitor, &m_Data.contentScaleX, &m_Data.contentScaleY);
}

inline _Ret_notnull_ const GLFWgammaramp* Monitor::GetGammaRamp()
{
	return glfwGetGammaRamp(m_Data.monitor);
}

inline void Monitor::GetPos()
{
	glfwGetMonitorPos(m_Data.monitor, &m_Data.posX, &m_Data.posY);
}

inline _Ret_notnull_ const GLFWvidmode* Monitor::GetVideoMode()
{
	return glfwGetVideoMode(m_Data.monitor);
}

inline void Monitor::GetWorkarea()
{
	glfwGetMonitorWorkarea(m_Data.monitor, &m_Data.posX, &m_Data.posY, &m_Data.width, &m_Data.heigth);
}

inline void Monitor::Select(unsigned int mindex)
{
	select_monitor(s_Data.monitors[mindex]);
}

inline void Monitor::SetGamma(float gamma)
{
	glfwSetGamma(m_Data.monitor, gamma);
}

inline void Monitor::SetGammaRamp(_In_ const GLFWgammaramp* ramp)
{
	glfwSetGammaRamp(m_Data.monitor, ramp);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
#endif // #ifndef YAGLPP_MONITOR_H
