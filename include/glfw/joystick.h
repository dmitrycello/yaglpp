#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_JOYSTICK_H
#define YAGLPP_JOYSTICK_H

namespace glfw {
/*GLFW joystick object root class*/
class Joystick
{
	friend class Thread;

public:
	enum class Axis : int;
	enum class Button : int;
	enum class Hat : unsigned char;

	/*GLWF type of callback routine called when joystick connected
	@param The UTF-8 encoded GUID of the joystick
	@param The UTF-8 encoded name of the joystick
	@param The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
	typedef void (APIENTRY Connected)(const char* guid, const char* name, const char* gamepad);

public:
	/*(1) Constructs an empty joystick object*/
	Joystick()
	{
		std::memset(&m_Data, 0, sizeof(MDATA)); m_Data.joystick = -1;
	}

	/*(M) (2) Constructs joystick object with <Select>, 0u selects first joystick in the system*/
	Joystick(unsigned int jindex) : Joystick()
	{
		Select(jindex);
	}

	/*(M) (3) Constructs joystick object with <Select>*/
	Joystick(_In_z_ const char* name) : Joystick()
	{
		Select(name);
	}

	/*Cleans up the valid joystick object*/
	~Joystick()
	{
		Deselect();
	}

	/*Unconditionally deselects joystick object*/
	void Deselect();

	/*Gets the last selected joystick id
	@return The GLFW joystick id*/
	int Get() const;

	/*(M) Scans the axes states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void GetAxes();

	/*Gets current joystick axis state retrieved by <GetAxes> call
	@param The joystick axis index
	@return The joystick axis state value, must be between -1.0 and 1.0*/
	float GetAxis(unsigned int index) const;

	/*Returns the joystick axis count after <GetAxes> call. MSVC getter for <axisCount> property
	@return The number of axes, or 0 prior to mentionned calls*/
	int GetAxisCount() const
	{
		return m_Data.axeCount;
	}

	/*Gets current joystick button state retrieved by <GetButtons> call
	@param The joystick button index
	@return True if specified button is pressed, false otherwise*/
	Action GetButton(unsigned int index) const;

	/*Returns the joystick button count after <GetButtons> call. MSVC getter for <buttonCount> property
	@return The number of buttons, or 0 prior to mentionned calls*/
	int GetButtonCount() const
	{
		return m_Data.buttonCount;
	}

	/*(M) Scans the buttons states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void GetButtons();

	/*Gets specified gamepad axis state retrieved by <GetGamepadState> call
	@param The gamepad axis
	@return The specified gamepad axis state value, must be between -1.0 and 1.0*/
	float GetGamepadAxis(Axis axis) const
	{
		return m_Data.gamepadState.axes[(int)axis];
	}

	/*Gets specified gamepad button state retrieved by <GetGamepadState> call
	@param The gamepad button
	@return True if specified gamepad button is pressed, false otherwise*/
	bool GetGamepadButton(Button button) const
	{
		return (bool)m_Data.gamepadState.buttons[(int)button];
	}

	/*Returns the human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick. MSVC getter for <gamepadName> property
	@return The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
	_Ret_maybenull_ const char* GetGamepadName() const;

	/*(M) Scans the gamepad states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped
	@return True if the gamepad state was loaded successfully, false otherwise*/
	bool GetGamepadState();

	/*Gets current joystick hat state retrieved by <GetHats> call
	@param The joystick hat index
	@return The joystick hat state value*/
	Hat GetHat(unsigned int index) const;

	/*Returns the joystick hat count after <GetHats> call. MSVC getter for <hatCount> property
	@return The number of hats, or 0 prior to mentionned calls*/
	int GetHatCount() const
	{
		return m_Data.hatCount;
	}

	/*(M) Scans the hats states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void GetHats();

	/*Retrieves number of joysticks available in the system
	@return The number of available joysticks*/
	static int GetJoystickCount()
	{
		return s_Data.count;
	}

	/*Returns the SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick. MSVC getter for <guid> property
	@return The UTF-8 encoded GUID of the joystick*/
	_Ret_z_ const char* GetGUID() const;

	/*This function returns the name, encoded as UTF-8, of the specified joystick. MSVC getter for <name> property
	@return The UTF-8 encoded name of the joystick*/
	_Ret_z_ const char* GetName() const;

	/*(M) Returns whether the specified joystick is both present and has a gamepad mapping. MSVC getter for <gamepad> property
	@return True if a joystick is both present and has a gamepad mapping, false otherwise*/
	bool IsGamepad();

	/*Checks if valid joystick object, must be called prior to any other calls. Validate the object. MSVC getter for <joystick> property
	@return True if valid joystick object, false otherwise*/
	bool IsJoystick() const
	{
		return m_Data.joystick > -1;
	}

	/*(M) (1) Selects joystick by its index. The index 0u selects first joystick in the system
	@param [in] The joystick index, default 0u*/
	void Select(unsigned int jindex = 0u);

	/*(M) (2) Selects joystick by its name in the system
	@param [in] The joystick name*/
	void Select(_In_z_ const char* jname);

	/*(M) Selects joystick by its GUID
	@param [in] The joystick GUID*/
	void SelectGUID(_In_z_ const char* jguid);

	/*Sets the function for the joystick connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void SetConnectedCallback(Connected callback)
	{
		s_Data.callback = callback;
	}

	/*(M) Parses the specified ASCII encoded zero terminated string and updates the internal list with any gamepad mappings it finds. String must be ended up by null-terminating byte
	@param [in]	The string containing the gamepad mappings
	@return True if successful, false otherwise*/
	static bool UpdateGamepadMappings(_In_z_ const char* string);

	/*(M) Loads the file, parses it as the zero terminated string and updates the internal list with any gamepad mappings it finds. File must be ended up by null-terminating byte
	@param [in] The path to the file containing the gamepad mappings
	@return True if successful, false otherwise*/
	static bool UpdateGamepadMappingsFromFile(_In_z_ const char* file);

#ifdef YAGLPP_MSVC
	/*(M) Loads the string binary resource and updates the internal list with any gamepad mappings it finds (Windows only). Resource must be ended up by null-terminating byte
	@param The binary resource id of <RC_DATA> type containing the gamepad mappings
	@return True if successful, false otherwise*/
	static bool UpdateGamepadMappingsFromResource(int rcid)
	{
		unsigned int s = 0; UpdateGamepadMappings((char*)yaglpp_load_resource(rcid, &s));
	}
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for joystick axis count after <GetAxes> call*/
	__declspec(property(get = GetAxisCount)) int axisCount;

	/*Read-only property for joystick button count after <GetButtons> call*/
	__declspec(property(get = GetButtonCount)) int buttonCount;

	/*Read-only property to check whether the specified joystick is both present and has a gamepad mapping*/
	__declspec(property(get = IsGamepad)) bool gamepad;

	/*Read-only property for human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick*/
	__declspec(property(get = GetGamepadName)) const char* gamepadName;

	/*Read-only property for SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick*/
	__declspec(property(get = GetGUID)) const char* guid;

	/*Read-only property for joystick hat count after <GetHats> call*/
	__declspec(property(get = GetHatCount)) int hatCount;

	/*Read-only property to check if valid joystick object*/
	__declspec(property(get = IsJoystick)) bool joystick;

	/*Read-only property for name, encoded as UTF-8, of the specified joystick*/
	__declspec(property(get = GetName)) const char* name;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	/*Joystick disconnected event handler*/
	virtual void OnDisconnect() {}

private:
	// Joystick object member data structure
	struct MDATA {
		int joystick; // Joystick id
		int axeCount; // Axes count
		int hatCount; // Hat count
		int buttonCount; // Button count
		const float* joystickAxes; // Axe array
		const unsigned char* joystickHats; // Hat array
		const unsigned char* joystickButtons; // Button array
		const char* joystickGuid; // Joystick GUID
		const char* joystickName; // Joystick name
		const char* gamepadName; // Gamepad name
		GLFWgamepadstate gamepadState; // Gamepad state structure
	} m_Data;

	// Joystick object static data structure
	static struct SDATA {
		int count; // Joystick count
		int joysticks[GLFW_JOYSTICK_LAST + 1]; // Joystick array
		Connected* callback; // Joystick connected callback
		void initialize();
		void load_joysticks();
	} s_Data;

	void select_joystick(int jid);
	static void joystick_callback(int jid, int event);
}; // class Joystick

/*GLFW gamepad axis enumerator*/
enum class Joystick::Axis : int
{
	/*Gamepad left X axis*/
	LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,

	/*Gamepad left Y axis*/
	LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,

	/*Gamepad right X axis*/
	RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,

	/*Gamepad right Y axis*/
	RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,

	/*Gamepad left trigger axis*/
	LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,

	/*Gamepad right trigger axis*/
	RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,

	/*Gamepad last axis*/
	Last = GLFW_GAMEPAD_AXIS_LAST,
};

/*GLFW gamepad button enumerator*/
enum class Joystick::Button : int
{
	/*Gamepad A button*/
	A = GLFW_GAMEPAD_BUTTON_A,

	/*Gamepad B button*/
	B = GLFW_GAMEPAD_BUTTON_B,

	/*Gamepad X button*/
	X = GLFW_GAMEPAD_BUTTON_X,

	/*Gamepad Y button*/
	Y = GLFW_GAMEPAD_BUTTON_Y,

	/*Gamepad cross button*/
	Cross = GLFW_GAMEPAD_BUTTON_CROSS,

	/*Gamepad circle button*/
	Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,

	/*Gamepad square button*/
	Square = GLFW_GAMEPAD_BUTTON_SQUARE,

	/*Gamepad triangle button*/
	Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,

	/*Gamepad left bumper button*/
	LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,

	/*Gamepad right bumper button*/
	RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,

	/*Gamepad back button*/
	Back = GLFW_GAMEPAD_BUTTON_BACK,

	/*Gamepad start button*/
	Start = GLFW_GAMEPAD_BUTTON_START,

	/*Gamepad guide button*/
	Guide = GLFW_GAMEPAD_BUTTON_GUIDE,

	/*Gamepad left thumb button*/
	LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,

	/*Gamepad right thumb button*/
	RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

	/*Gamepad d-pad up button*/
	DpadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,

	/*Gamepad d-pad right button*/
	DpadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,

	/*Gamepad d-pad down button*/
	DpadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,

	/*Gamepad d-pad left button*/
	DpadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

	/*Gamepad last button*/
	Last = GLFW_GAMEPAD_BUTTON_LAST,
};

/*GLFW joystick hat enumerator*/
enum class Joystick::Hat : unsigned char
{
	/*No joystick hat pressed*/
	Centered = GLFW_HAT_CENTERED,

	/*Up joystick hat pressed*/
	Up = GLFW_HAT_UP,

	/*Right joystick hat pressed*/
	Right = GLFW_HAT_RIGHT,

	/*Down joystick hat pressed*/
	Down = GLFW_HAT_DOWN,

	/*Left joystick hat pressed*/
	Left = GLFW_HAT_LEFT,

	/*Right and up joystick hats pressed*/
	RightUp = GLFW_HAT_RIGHT_UP,

	/*Right and down joystick hats pressed*/
	RightDown = GLFW_HAT_RIGHT_DOWN,

	/*Left and up joystick hats pressed*/
	LeftUp = GLFW_HAT_LEFT_UP,

	/*Left and down joystick hats pressed*/
	LeftDown = GLFW_HAT_LEFT_DOWN,
};
} // namespace glfw

//#include <yaglpp/glfw/thread.h>
namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
Joystick::SDATA Joystick::s_Data;
void Joystick::SDATA::initialize()
{
	callback = nullptr; // Initialize joystick data
	load_joysticks();
	glfwSetJoystickCallback(&joystick_callback);
}

void Joystick::SDATA::load_joysticks()
{
	count = 0;
	for (int jid = 0; jid < (GLFW_JOYSTICK_LAST + 1); jid++)
	{
		if (glfwJoystickPresent(jid))
		{
			joysticks[count++] = jid;
		}
	}
}

void Joystick::joystick_callback(int jid, int event)
{
	s_Data.load_joysticks();
	if (event == GLFW_DISCONNECTED)
	{
		Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
		if (pClass != nullptr)
		{
			pClass->OnDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW joystick <" << pClass->m_Data.joystickName;
			std::cout << "> with guid <" << pClass->m_Data.joystickGuid << "> ";
			if (pClass->m_Data.gamepadName)
			{
				std::cout << "with gamepad present <" << pClass->m_Data.gamepadName << "> ";
			}
			else
			{
				std::cout << "and no gamepad present ";
			}
			std::cout << "was disconnected" << std::endl;
#endif // #ifdef _DEBUG

			pClass->Deselect();
		}
	}
	if (event == GLFW_CONNECTED)
	{
		const char* pGuid = glfwGetJoystickGUID(jid);
		const char* pName = glfwGetJoystickName(jid);
		const char* pGamepad = glfwGetGamepadName(jid);

#ifdef _DEBUG
		std::cout << "GLFW joystick <" << pName << "> with guid <" << pGuid << "> ";
		if (pGamepad)
		{
			std::cout << "and present gamepad <" << pGamepad << ">";
		}
		else
		{
			std::cout << "and no present gamepad";
		}
		std::cout << " was connected" << std::endl;
#endif // #ifdef _DEBUG

		if (s_Data.callback != nullptr)
		{
			s_Data.callback(pGuid, pName, pGamepad);
		}
	}
}

void Joystick::select_joystick(int jid)
{
	Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
	if (pClass)
	{
		pClass->Deselect();
	}
	m_Data.joystick = jid;
	m_Data.joystickGuid = glfwGetJoystickGUID(jid);
	m_Data.joystickName = glfwGetJoystickName(jid);
	m_Data.gamepadName = glfwGetGamepadName(jid);
	glfwSetJoystickUserPointer(jid, this);
}

void Joystick::Deselect()
{
	if (m_Data.joystick > -1)
	{
		glfwSetJoystickUserPointer(m_Data.joystick, nullptr);
		std::memset(&m_Data, 0, sizeof(MDATA));
		m_Data.joystick = -1;
	}
}

void Joystick::Select(_In_z_ const char* jname)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());
	
	// GLFW JOYSTICK OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsJoystick());

	for (int i = 0; i < s_Data.count; i++)
	{
		int jid = s_Data.joysticks[i];
		const char* zName = glfwGetJoystickName(jid);
		if (std::strcmp(zName, jname) == 0)
		{
			select_joystick(jid);
			break;
		}
	}
}

void Joystick::SelectGUID(_In_z_ const char* jguid)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// GLFW JOYSTICK OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsJoystick());
	for (int i = 0; i < s_Data.count; i++)
	{
		int jid = s_Data.joysticks[i];
		const char* zGUID = glfwGetJoystickGUID(jid);
		if (std::strcmp(zGUID, jguid) == 0)
		{
			select_joystick(jid);
			break;
		}
	}
}

bool Joystick::UpdateGamepadMappingsFromFile(_In_z_ const char* file)
{
	int iUnused;
	char* pData = (char*)yaglpp_load_file(file, &iUnused, nullptr);
	bool bResult = UpdateGamepadMappings(pData);
	YAGLPP_FREE(pData);
	return bResult;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
int Joystick::Get() const
{
	// GLFW JOYSTICK WAS NOT SELECTED
	YAGLPP_ASSERT(IsJoystick());

	return m_Data.joystick;
}

void Joystick::GetAxes()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	m_Data.joystickAxes = glfwGetJoystickAxes(Get(), &m_Data.axeCount);
}

float Joystick::GetAxis(unsigned int index) const
{
	// GLFW JOYSTICK AXIS INDEX IS INVALID
	YAGLPP_ASSERT((int)index < m_Data.axeCount);

	return m_Data.joystickAxes[index];
}

Action Joystick::GetButton(unsigned int index) const
{
	// GLFW JOYSTICK BUTTON INDEX IS INVALID
	YAGLPP_ASSERT((int)index < m_Data.buttonCount);

	return (Action)m_Data.joystickButtons[index];
}

void Joystick::GetButtons()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	m_Data.joystickButtons = glfwGetJoystickButtons(Get(), &m_Data.buttonCount);
}

_Ret_maybenull_ const char* Joystick::GetGamepadName() const
{
	// GLFW JOYSTICK IS UNAVAILABLE
	YAGLPP_ASSERT(IsJoystick());

	return m_Data.gamepadName;
}

bool Joystick::GetGamepadState()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return (bool)glfwGetGamepadState(Get(), &m_Data.gamepadState);
}

_Ret_z_ const char* Joystick::GetGUID() const
{
	// GLFW JOYSTICK WAS NOT SELECTED
	YAGLPP_ASSERT(IsJoystick());

	return m_Data.joystickGuid;
}

Joystick::Hat Joystick::GetHat(unsigned int index) const
{
	// GLFW JOYSTICK HAT INDEX IS INVALID
	YAGLPP_ASSERT((int)index < m_Data.hatCount);

	return (Hat)m_Data.joystickHats[index];
}

void Joystick::GetHats()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	m_Data.joystickHats = glfwGetJoystickHats(Get(), &m_Data.hatCount);
}

_Ret_z_ const char* Joystick::GetName() const
{
	// GLFW JOYSTICK WAS NOT SELECTED
	YAGLPP_ASSERT(IsJoystick());

	return m_Data.joystickName;
}

bool Joystick::IsGamepad()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return (bool)glfwJoystickIsGamepad(Get());
}

void Joystick::Select(unsigned int jindex)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	// GLFW JOYSTICK OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(!IsJoystick());

	// JOYSTICK INDEX IS INVALID
	YAGLPP_ASSERT(jindex < (unsigned int)s_Data.count);

	select_joystick(s_Data.joysticks[jindex]);
}

bool Joystick::UpdateGamepadMappings(_In_z_ const char* string)
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	return glfwUpdateGamepadMappings(string) == GLFW_TRUE;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline int Joystick::Get() const
{
	return m_Data.joystick;
}

inline void Joystick::GetAxes()
{
	m_Data.joystickAxes = glfwGetJoystickAxes(m_Data.joystick, &m_Data.axeCount);
}

inline float Joystick::GetAxis(unsigned int index) const
{
	return m_Data.joystickAxes[index];
}

inline Action Joystick::GetButton(unsigned int index) const
{
	return (Action)m_Data.joystickButtons[index];
}

inline void Joystick::GetButtons()
{
	m_Data.joystickButtons = glfwGetJoystickButtons(m_Data.joystick, &m_Data.buttonCount);
}

inline _Ret_maybenull_ const char* Joystick::GetGamepadName() const
{
	return m_Data.gamepadName;
}

inline bool Joystick::GetGamepadState()
{
	return (bool)glfwGetGamepadState(m_Data.joystick, &m_Data.gamepadState);
}

inline _Ret_z_ const char* Joystick::GetGUID() const
{
	return m_Data.joystickGuid;
}

inline Joystick::Hat Joystick::GetHat(unsigned int index) const
{
	return (Hat)m_Data.joystickHats[index];
}

inline void Joystick::GetHats()
{
	m_Data.joystickHats = glfwGetJoystickHats(m_Data.joystick, &m_Data.hatCount);
}

inline _Ret_z_ const char* Joystick::GetName() const
{
	return m_Data.joystickName;
}

inline bool Joystick::IsGamepad()
{
	return (bool)glfwJoystickIsGamepad(m_Data.joystick);
}

inline void Joystick::Select(unsigned int jindex)
{
	select_joystick(s_Data.joysticks[jindex]);
}

inline bool Joystick::UpdateGamepadMappings(_In_z_ const char* string)
{
	return glfwUpdateGamepadMappings(string) == GLFW_TRUE;
}
#endif // #define YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw

#endif // #ifndef YAGLPP_JOYSTICK_H
