#define YAGLPP_BUILD_LIB
#include <yaglpp/Thread.h>
#include <yaglpp/Joystick.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
namespace glfw {
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
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	const char* pData = (char*)_loadResource(rcid, &iTemp);
	return glfwUpdateGamepadMappings(pData) == GLFW_TRUE;
}

bool Joystick::loadGamepadMappings(_In_z_ const char* file)
{
	int iTemp = 0;
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	char* pData = (char*)_loadFile(file, &iTemp);
	if (pData)
	{
		iTemp = glfwUpdateGamepadMappings(pData);
		_YAGLPP_FREE_(pData);
	}
	return iTemp == GLFW_TRUE;
}

void Joystick::selectJoystick(_In_z_ const char* jname)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
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
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
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

#ifdef _DEBUG
int Joystick::_jid() const
{
	_YAGLPP_ASSERT_(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.iJid;
}

_Ret_maybenull_ const char* Joystick::getGamepadName() const
{
	_YAGLPP_ASSERT_(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return _m.pGamepad;
}

bool Joystick::getGamepadState()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (bool)glfwGetGamepadState(_jid(), &_m.gamepadState);
}

void Joystick::getJoystickAxes()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pAxes = glfwGetJoystickAxes(_jid(), &_m.iAxes);
}

float Joystick::getJoystickAxis(unsigned int index) const
{
	_YAGLPP_ASSERT_((int)index < _m.iAxes); // GLFW JOYSTICK AXIS INDEX IS INVALID
	return _m.pAxes[index];
}

bool Joystick::getJoystickButton(unsigned int index) const
{
	_YAGLPP_ASSERT_((int)index < _m.iButtons); // GLFW JOYSTICK BUTTON INDEX IS INVALID
	return _m.pButtons[index] == GLFW_PRESS;
}

void Joystick::getJoystickButtons()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pButtons = glfwGetJoystickButtons(_jid(), &_m.iButtons);
}

JoystickHat Joystick::getJoystickHat(unsigned int index) const
{
	_YAGLPP_ASSERT_((int)index < _m.iHats); // GLFW JOYSTICK HAT INDEX IS INVALID
	return (JoystickHat)_m.pHats[index];
}

void Joystick::getJoystickHats()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_m.pHats = glfwGetJoystickHats(_jid(), &_m.iHats);
}

_Ret_z_ const char* Joystick::getJoystickGUID() const
{
	_YAGLPP_ASSERT_(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.pGuid;
}

_Ret_z_ const char* Joystick::getJoystickName() const
{
	_YAGLPP_ASSERT_(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return _m.pName;
}

bool Joystick::joystickIsGamepad()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return (bool)glfwJoystickIsGamepad(_jid());
}

void Joystick::selectJoystick(unsigned int jindex)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	_YAGLPP_ASSERT_(jindex < (unsigned int)_s.iJcount); // JOYSTICK INDEX IS INVALID
	_select(_s.pJoysticks[jindex]);
}

bool Joystick::updateGamepadMappings(_In_z_ const char* string)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	return glfwUpdateGamepadMappings(string) == GLFW_TRUE;
}
#endif // #ifdef _DEBUG
} // namespace glfw
