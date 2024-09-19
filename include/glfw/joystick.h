#pragma once
#include <yaglpp/glfw3pp.h>
namespace glfw {
/*GLFW gamepad axis enumerator*/
enum class GamepadAxis : int
{
	/*Gamepad left X axis*/
	GamepadAxisLeftX = GLFW_GAMEPAD_AXIS_LEFT_X,

	/*Gamepad left Y axis*/
	GamepadAxisLeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,

	/*Gamepad right X axis*/
	GamepadAxisRightX = GLFW_GAMEPAD_AXIS_RIGHT_X,

	/*Gamepad right Y axis*/
	GamepadAxisRightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,

	/*Gamepad left trigger axis*/
	GamepadAxisLeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,

	/*Gamepad right trigger axis*/
	GamepadAxisRightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,

	/*Gamepad last axis*/
	GamepadAxisLast = GLFW_GAMEPAD_AXIS_LAST,
};

/*GLFW gamepad button enumerator*/
enum class GamepadButton : int
{
	/*Gamepad A button*/
	GamepadButtonA = GLFW_GAMEPAD_BUTTON_A,

	/*Gamepad B button*/
	GamepadButtonB = GLFW_GAMEPAD_BUTTON_B,

	/*Gamepad X button*/
	GamepadButtonX = GLFW_GAMEPAD_BUTTON_X,

	/*Gamepad Y button*/
	GamepadButtonY = GLFW_GAMEPAD_BUTTON_Y,

	/*Gamepad cross button*/
	GamepadButtonCross = GLFW_GAMEPAD_BUTTON_CROSS,

	/*Gamepad circle button*/
	GamepadButtonCircle = GLFW_GAMEPAD_BUTTON_CIRCLE,

	/*Gamepad square button*/
	GamepadButtonSquare = GLFW_GAMEPAD_BUTTON_SQUARE,

	/*Gamepad triangle button*/
	GamepadButtonTriangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,

	/*Gamepad left bumper button*/
	GamepadButtonLeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,

	/*Gamepad right bumper button*/
	GamepadButtonRightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,

	/*Gamepad back button*/
	GamepadButtonBack = GLFW_GAMEPAD_BUTTON_BACK,

	/*Gamepad start button*/
	GamepadButtonStart = GLFW_GAMEPAD_BUTTON_START,

	/*Gamepad guide button*/
	GamepadButtonGuide = GLFW_GAMEPAD_BUTTON_GUIDE,

	/*Gamepad left thumb button*/
	GamepadButtonLeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,

	/*Gamepad right thumb button*/
	GamepadButtonRightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

	/*Gamepad d-pad up button*/
	GamepadButtonDpadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,

	/*Gamepad d-pad right button*/
	GamepadButtonDpadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,

	/*Gamepad d-pad down button*/
	GamepadButtonDpadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,

	/*Gamepad d-pad left button*/
	GamepadButtonDpadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

	/*Gamepad last button*/
	GamepadButtonLast = GLFW_GAMEPAD_BUTTON_LAST,
};

/*GLFW joystick hat enumerator*/
enum class JoystickHat : unsigned char
{
	/*No joystick hat pressed*/
	HatCentered = GLFW_HAT_CENTERED,

	/*Up joystick hat pressed*/
	HatUp = GLFW_HAT_UP,

	/*Right joystick hat pressed*/
	HatRight = GLFW_HAT_RIGHT,

	/*Down joystick hat pressed*/
	HatDown = GLFW_HAT_DOWN,

	/*Left joystick hat pressed*/
	HatLeft = GLFW_HAT_LEFT,

	/*Right and up joystick hats pressed*/
	HatRightUp = GLFW_HAT_RIGHT_UP,

	/*Right and down joystick hats pressed*/
	HatRightDown = GLFW_HAT_RIGHT_DOWN,

	/*Left and up joystick hats pressed*/
	HatLeftUp = GLFW_HAT_LEFT_UP,

	/*Left and down joystick hats pressed*/
	HatLeftDown = GLFW_HAT_LEFT_DOWN,
};

/*GLWF type of joystick connected callback routine
@param The UTF-8 encoded GUID of the joystick
@param The UTF-8 encoded name of the joystick
@param The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
typedef void (WINAPI JoystickConnectedCallback)(const char* guid, const char* name, const char* gamepad);

/*GLFW joystick object root class*/
class Joystick
{
private:
	friend class Thread;
	// Joystick object static data structure
	static struct _SDATA {
		int iJcount; // Joystick count
		int pJoysticks[GLFW_JOYSTICK_LAST + 1]; // Joystick array
		JoystickConnectedCallback* pJConnected; // Joystick connected callback
		void initialize();
		void loadJoysticks();
	} _s;

	// Joystick object member data structure
	struct _MDATA {
		int iJid; // Joystick id
		int iAxes; // Axes count
		int iHats; // Hat count
		int iButtons; // Button count
		const char* pGuid; // Joystick GUID
		const char* pName; // Joystick name
		const float* pAxes; // Axe array
		const char* pGamepad; // Gamepad name
		const unsigned char* pHats; // Hat array
		const unsigned char* pButtons; // Button array
		GLFWgamepadstate gamepadState; // Gamepad state structure
	} _m;

	int _jid() const;
	void _select(int jid);
	static void _joystickCallback(int jid, int event);

protected:
	/*Joystick disconnected event handler*/
	virtual void onDisconnect() {}

public:
	/*(1) Constructs an empty joystick object*/
	Joystick()
	{
		memset(&_m, 0, sizeof(_MDATA)); _m.iJid = -1;
	}

	/*(M) (2) Constructs joystick object with <selectJoystick>, 0u selects first joystick in the system*/
	Joystick(unsigned int jindex) : Joystick()
	{
		selectJoystick(jindex);
	}

	/*(M) (3) Constructs joystick object with <selectJoystick>*/
	Joystick(_In_z_ const char* name) : Joystick()
	{
		selectJoystick(name);
	}

	/*Cleans up the valid joystick object*/
	~Joystick()
	{
		if (isJoystick())
		{
			deselectJoystick();
		}
	}

	/*Unconditionally deselects specified joystick*/
	void deselectJoystick();

	/*Returns the joystick axis count after <getJoystickAxes> call. Used as a getter of <axisCount> property
	@return The number of axes, or 0 prior to mentionned calls*/
	int getAxisCount() const
	{
		return _m.iAxes;
	}

	/*Returns the joystick button count after <getJoystickButtons> call. Used as a getter of <buttonCount> property
	@return The number of buttons, or 0 prior to mentionned calls*/
	int getButtonCount() const
	{
		return _m.iButtons;
	}

	/*Gets specified gamepad axis state retrieved by <getGamepadState> call
	@param The gamepad axis
	@return The specified gamepad axis state value, must be between -1.0 and 1.0*/
	float getGamepadAxis(GamepadAxis axis) const
	{
		return _m.gamepadState.axes[(int)axis];
	}

	/*Gets specified gamepad button state retrieved by <getGamepadState> call
	@param The gamepad button
	@return True if specified gamepad button is pressed, false otherwise*/
	bool getGamepadButton(GamepadButton button) const
	{
		return (bool)_m.gamepadState.buttons[(int)button];
	}

	/*Returns the human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick. Used as a getter of <gamepadName> property
	@return The UTF-8 encoded name of the gamepad, or NULL if the joystick does not have a mapping*/
	_Ret_maybenull_ const char* getGamepadName() const;

	/*(M) Scans the gamepad states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped
	@return True if the gamepad state was loaded successfully, false otherwise*/
	bool getGamepadState();

	/*Returns the joystick hat count after <getJoystickHats> call. Used as a getter of <hatCount> property
	@return The number of hats, or 0 prior to mentionned calls*/
	int getHatCount() const
	{
		return _m.iHats;
	}

	/*(M) Scans the axes states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickAxes();

	/*Gets current joystick axis state retrieved by <getJoystickAxes> call
	@param The joystick axis index
	@return The joystick axis state value, must be between -1.0 and 1.0*/
	float getJoystickAxis(unsigned int index) const;

	/*Gets current joystick button state retrieved by <getJoystickButtons> call
	@param The joystick button index
	@return True if specified button is pressed, false otherwise*/
	bool getJoystickButton(unsigned int index) const;

	/*(M) Scans the buttons states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickButtons();

	/*Retrieves number of joysticks available in the system
	@return The number of available joysticks*/
	static int getJoystickCount()
	{
		return _s.iJcount;
	}

	/*Returns the SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick. Used as a getter of <joystickGUID> property
	@return The UTF-8 encoded GUID of the joystick*/
	_Ret_z_ const char* getJoystickGUID() const;

	/*Gets current joystick hat state retrieved by <getJoystickHats> call
	@param The joystick hat index
	@return The joystick hat state value*/
	JoystickHat getJoystickHat(unsigned int index) const;

	/*(M) Scans the hats states, and triggers the appropriate events if any changes occured since the last scan. The first scan is always skipped*/
	void getJoystickHats();

	/*This function returns the name, encoded as UTF-8, of the specified joystick. Used as a getter of <joystickName> property
	@return The UTF-8 encoded name of the joystick*/
	_Ret_z_ const char* getJoystickName() const;

	/*Checks if valid joystick object, must be called prior to any other calls. Validate the object. Used as a getter of <joystick> property
	@return True if valid joystick object, false otherwise*/
	bool isJoystick() const
	{
		return _m.iJid > -1;
	}

	/*(M) Returns whether the specified joystick is both present and has a gamepad mapping. Used as a getter of <joystickGamepad> property
	@return True if a joystick is both present and has a gamepad mapping, false otherwise*/
	bool joystickIsGamepad();

	/*(M) (1) Loads the binary resource and updates the internal list with any gamepad mappings it finds
	@param The binary resource id
	@return True if successful, false otherwise*/
	static bool loadGamepadMappings(int rcid);

	/*(M) (2) Loads the file and updates the internal list with any gamepad mappings it finds
	@param [in] The path to the file
	@return True if successful, false otherwise*/
	static bool loadGamepadMappings(_In_z_ const char* file);

	/*(M) (1) Selects joystick by its index. The index 0u selects first joystick in the system
	@param [in] The joystick index, default 0u*/
	void selectJoystick(unsigned int jindex = 0u);

	/*(M) (2) Selects joystick by its name in the system
	@param [in] The joystick name*/
	void selectJoystick(_In_z_ const char* jname);

	/*(M) Selects joystick by its GUID
	@param [in] The joystick GUID*/
	void selectJoystickGUID(_In_z_ const char* jguid);

	/*Sets the function for the joystick connected callback routine
	@param GLWF type of joystick connected callback routine*/
	static void setJoystickConnectedCallback(JoystickConnectedCallback callback)
	{
		_s.pJConnected = callback;
	}

	/*Parses the specified ASCII encoded string and updates the internal list with any gamepad mappings it finds
	@param [in]	The string containing the gamepad mappings
	@return True if successful, false otherwise*/
	static bool updateGamepadMappings(_In_z_ const char* string);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for joystick axis count after <getJoystickAxes> call*/
	__declspec(property(get = getAxisCount)) int axisCount;

	/*Read-only property for joystick button count after <getJoystickButtons> call*/
	__declspec(property(get = getButtonCount)) int buttonCount;

	/*Read-only property for human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick*/
	__declspec(property(get = getGamepadName)) const char* gamepadName;

	/*Read-only property for joystick hat count after <getJoystickHats> call*/
	__declspec(property(get = getHatCount)) int hatCount;

	/*Read-only property to check if valid joystick object*/
	__declspec(property(get = isJoystick)) bool joystick;

	/*Read-only property to check whether the specified joystick is both present and has a gamepad mapping*/
	__declspec(property(get = joystickIsGamepad)) bool joystickGamepad;

	/*Read-only property for SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick*/
	__declspec(property(get = getJoystickGUID)) const char* joystickGUID;

	/*Read-only property for name, encoded as UTF-8, of the specified joystick*/
	__declspec(property(get = getJoystickName)) const char* joystickName;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class Joystick

/*Sets the function for the joystick connected callback routine
@param GLWF type of joystick connected callback routine*/
inline void setJoystickConnectedCallback(JoystickConnectedCallback callback)
{
	Joystick::setJoystickConnectedCallback(callback);
}
} // namespace glfw

#include <yaglpp/glfw/thread.h>
namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
Joystick::_SDATA Joystick::_s;
void Joystick::_SDATA::initialize()
{
	pJConnected = nullptr; // Initialize joystick data
	loadJoysticks();
	glfwSetJoystickCallback(&_joystickCallback);
}

void Joystick::_SDATA::loadJoysticks()
{
	iJcount = 0;
	for (int jid = 0; jid < (GLFW_JOYSTICK_LAST + 1); jid++)
	{
		if (glfwJoystickPresent(jid))
		{
			pJoysticks[iJcount++] = jid;
		}
	}
}

void Joystick::_joystickCallback(int jid, int event)
{
	_s.loadJoysticks();
	if (event == GLFW_DISCONNECTED)
	{
		Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
		if (pClass != nullptr)
		{
			pClass->onDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW JOYSTICK <" << pClass->_m.pName << "> WITH GUID <" << pClass->_m.pGuid << "> ";
			if (pClass->_m.pGamepad)
			{
				std::cout << "WITH GANEPAD PRESENT <" << pClass->_m.pGamepad << "> ";
			}
			else
			{
				std::cout << "AND NO GAMEPAD PRESENT ";
			}
			std::cout << "WAS DISCONNECTED" << std::endl;
#endif // #ifdef _DEBUG

			pClass->deselectJoystick();
		}
	}
	if (event == GLFW_CONNECTED)
	{
		const char* pGuid = glfwGetJoystickGUID(jid);
		const char* pName = glfwGetJoystickName(jid);
		const char* pGamepad = glfwGetGamepadName(jid);

#ifdef _DEBUG
		std::cout << "GLFW JOYSTICK <" << pName << "> WITH GUID <" << pGuid << "> ";
		if (pGamepad)
		{
			std::cout << "AND PRESENT GAMEPAD <" << pGamepad << ">";
		}
		else
		{
			std::cout << "AND NO PRESENT GAMEPAD";
		}
		std::cout << " WAS CONNECTED" << std::endl;
#endif // #ifdef _DEBUG

		if (_s.pJConnected != nullptr)
		{
			_s.pJConnected(pGuid, pName, pGamepad);
		}
	}
}

void Joystick::_select(int jid)
{
	Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
	if (pClass)
	{
		pClass->deselectJoystick();
	}
	_m.iJid = jid;
	_m.pGuid = glfwGetJoystickGUID(jid);
	_m.pName = glfwGetJoystickName(jid);
	_m.pGamepad = glfwGetGamepadName(jid);
	glfwSetJoystickUserPointer(jid, this);
}

void Joystick::deselectJoystick()
{
	glfwSetJoystickUserPointer(_jid(), nullptr);
	memset(&_m, 0, sizeof(_MDATA));
	_m.iJid = -1;
}

bool Joystick::loadGamepadMappings(int rcid)
{
	int iTemp = 0;
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	const char* pData = (char*)_loadResource(rcid, &iTemp);
	return glfwUpdateGamepadMappings(pData) == GLFW_TRUE;
}

bool Joystick::loadGamepadMappings(_In_z_ const char* file)
{
	int iTemp = 0;
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	char* pData = (char*)_loadFile(file, &iTemp);
	if (pData)
	{
		iTemp = glfwUpdateGamepadMappings(pData);
		YAGLPP_FREE(pData);
	}
	return iTemp == GLFW_TRUE;
}

void Joystick::selectJoystick(_In_z_ const char* jname)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	for (int i = 0; i < _s.iJcount; i++)
	{
		int jid = _s.pJoysticks[i];
		const char* zName = glfwGetJoystickName(jid);
		if (strcmp(zName, jname) == 0)
		{
			_select(jid);
			break;
		}
	}
}

void Joystick::selectJoystickGUID(_In_z_ const char* jguid)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	for (int i = 0; i < _s.iJcount; i++)
	{
		int jid = _s.pJoysticks[i];
		const char* zGUID = glfwGetJoystickGUID(jid);
		if (strcmp(zGUID, jguid) == 0)
		{
			_select(jid);
			break;
		}
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
int Joystick::_jid() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.iJid;
}

_Ret_maybenull_ const char* Joystick::getGamepadName() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return _m.pGamepad;
}

bool Joystick::getGamepadState()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (bool)glfwGetGamepadState(_jid(), &_m.gamepadState);
}

void Joystick::getJoystickAxes()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pAxes = glfwGetJoystickAxes(_jid(), &_m.iAxes);
}

float Joystick::getJoystickAxis(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < _m.iAxes); // GLFW JOYSTICK AXIS INDEX IS INVALID
	return _m.pAxes[index];
}

bool Joystick::getJoystickButton(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < _m.iButtons); // GLFW JOYSTICK BUTTON INDEX IS INVALID
	return _m.pButtons[index] == GLFW_PRESS;
}

void Joystick::getJoystickButtons()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pButtons = glfwGetJoystickButtons(_jid(), &_m.iButtons);
}

JoystickHat Joystick::getJoystickHat(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < _m.iHats); // GLFW JOYSTICK HAT INDEX IS INVALID
	return (JoystickHat)_m.pHats[index];
}

void Joystick::getJoystickHats()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pHats = glfwGetJoystickHats(_jid(), &_m.iHats);
}

_Ret_z_ const char* Joystick::getJoystickGUID() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.pGuid;
}

_Ret_z_ const char* Joystick::getJoystickName() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.pName;
}

bool Joystick::joystickIsGamepad()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (bool)glfwJoystickIsGamepad(_jid());
}

void Joystick::selectJoystick(unsigned int jindex)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(jindex < (unsigned int)_s.iJcount); // JOYSTICK INDEX IS INVALID
	_select(_s.pJoysticks[jindex]);
}

bool Joystick::updateGamepadMappings(_In_z_ const char* string)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwUpdateGamepadMappings(string) == GLFW_TRUE;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline int Joystick::_jid() const
{
	return _m.iJid;
}

inline _Ret_maybenull_ const char* Joystick::getGamepadName() const
{
	return _m.pGamepad;
}

inline bool Joystick::getGamepadState()
{
	return (bool)glfwGetGamepadState(_m.iJid, &_m.gamepadState);
}

inline void Joystick::getJoystickAxes()
{
	_m.pAxes = glfwGetJoystickAxes(_m.iJid, &_m.iAxes);
}

inline float Joystick::getJoystickAxis(unsigned int index) const
{
	return _m.pAxes[index];
}

inline bool Joystick::getJoystickButton(unsigned int index) const
{
	return _m.pButtons[index] == GLFW_PRESS;
}

inline void Joystick::getJoystickButtons()
{
	_m.pButtons = glfwGetJoystickButtons(_m.iJid, &_m.iButtons);
}

inline _Ret_z_ const char* Joystick::getJoystickGUID() const
{
	return _m.pGuid;
}

inline JoystickHat Joystick::getJoystickHat(unsigned int index) const
{
	return (JoystickHat)_m.pHats[index];
}

inline void Joystick::getJoystickHats()
{
	_m.pHats = glfwGetJoystickHats(_m.iJid, &_m.iHats);
}

inline _Ret_z_ const char* Joystick::getJoystickName() const
{
	return _m.pName;
}

inline bool Joystick::joystickIsGamepad()
{
	return (bool)glfwJoystickIsGamepad(_m.iJid);
}

inline void Joystick::selectJoystick(unsigned int jindex)
{
	_select(_s.pJoysticks[jindex]);
}

inline bool Joystick::updateGamepadMappings(_In_z_ const char* string)
{
	return glfwUpdateGamepadMappings(string) == GLFW_TRUE;
}
#endif // #define YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
