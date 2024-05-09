#define GLPP_BUILD_LIB
#include <glpp/Joystick.h>
#pragma comment(lib, GLPP_GLFW_LIB)
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
namespace glfw {
Joystick::_SDATA::_SDATA()
{
	m_pConnected = nullptr;
	glfwSetJoystickCallback(&_joystickCallback);
}

void Joystick::_init()
{
	m_iJid = 0;
	m_iAxes = 0;
	m_iButtons = 0;
	m_iHats = 0;
	m_pAxes = nullptr;
	m_pButtons = nullptr;
	m_pHats = nullptr;
	m_pGamepadName = nullptr;
	m_pGuid = nullptr;
	m_pName = nullptr;
	m_Gamepad = { 0 };
}

void Joystick::_joystickCallback(int jid, int event)
{
	if (event == GLFW_DISCONNECTED)
	{
		Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
		if (pClass != nullptr)
		{
			pClass->onDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW JOYSTICK <" << pClass->m_pName << "> WITH GUID <" << pClass->m_pGuid << "> ";
			if (pClass->m_pGamepadName)
			{
				std::cout << "WITH GANEPAD PRESENT <" << pClass->m_pGamepadName << "> ";
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
		const char* pGamepadName = glfwGetGamepadName(jid);

#ifdef _DEBUG
		std::cout << "GLFW JOYSTICK <" << pName << "> WITH GUID <" << pGuid << "> ";
		if (pGamepadName)
		{
			std::cout << "AND PRESENT GAMEPAD <" << pGamepadName << ">";
		}
		else
		{
			std::cout << "AND NO PRESENT GAMEPAD";
		}
		std::cout << " WAS CONNECTED" << std::endl;
#endif // #ifdef _DEBUG

		if (s_Data.m_pConnected)
		{
			s_Data.m_pConnected(pGuid, pName, pGamepadName);
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
	m_iJid = jid;
	m_pGuid = glfwGetJoystickGUID(jid);
	m_pName = glfwGetJoystickName(jid);
	m_pGamepadName = glfwGetGamepadName(jid);
	glfwSetJoystickUserPointer(jid, this);
}

void Joystick::deselectJoystick()
{
	glfwSetJoystickUserPointer(_jid(), nullptr);
	_init();
}

bool Joystick::getGamepadState()
{
	if (isJoystick())
	{
		return (bool)glfwGetGamepadState(m_iJid, &m_Gamepad);
	}
	return false;
}

void Joystick::getJoystickAxes()
{
	if (isJoystick())
	{
		m_pAxes = glfwGetJoystickAxes(m_iJid, &m_iAxes);
	}
}

void Joystick::getJoystickButtons()
{
	if (isJoystick())
	{
		m_pButtons = glfwGetJoystickButtons(m_iJid, &m_iButtons);
	}
}

void Joystick::getJoystickHats()
{
	if (isJoystick())
	{
		m_pHats = glfwGetJoystickHats(m_iJid, &m_iHats);
	}
}

bool Joystick::loadGamepadMappings(int rcid)
{
	int iSize;
	char* pData = (char*)_loadResource(rcid, &iSize);
	return (bool)glfwUpdateGamepadMappings(pData);
}

bool Joystick::loadGamepadMappings(_In_z_ const char* filepath)
{
	int iSize = 0;
	char* pData = (char*)_loadFile(filepath, &iSize);
	if (pData)
	{
		iSize = glfwUpdateGamepadMappings(pData);
		GLPP_FREE(pData);
	}
	return (bool)iSize;
}

void Joystick::selectJoystick()
{
	if (isJoystick()) deselectJoystick();
	for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwJoystickPresent(i))
		{
			_select(i);
			break;
		}
	}
}

void Joystick::selectJoystick(_In_z_ const char* jname)
{
	if (isJoystick()) deselectJoystick();
	for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwJoystickPresent(i))
		{
			const char* zName = glfwGetJoystickName(i);
			if (strcmp(zName, jname) == 0)
			{
				_select(i);
				break;
			}
		}
	}
}

void Joystick::selectJoystickGUID(_In_z_ const char* jguid)
{
	if (isJoystick()) deselectJoystick();
	for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwJoystickPresent(i))
		{
			const char* zGUID = glfwGetJoystickGUID(i);
			if (strcmp(zGUID, jguid) == 0)
			{
				_select(i);
				break;
			}
		}
	}
}

#ifdef _DEBUG
int Joystick::_jid()
{
	GLPP_ASSERT(isJoystick()); // NO JOYSTICK IN THE SYSTEM WERE FOUND
	return m_iJid;
}

float Joystick::getJoystickAxis(unsigned int index)
{
	GLPP_ASSERT((int)index < m_iAxes); // GLFW JOYSTICK AXIS INDEX IS INVALID
	return m_pAxes[index];
}

bool Joystick::getJoystickButton(unsigned int index)
{
	GLPP_ASSERT((int)index < m_iButtons); // GLFW JOYSTICK BUTTON INDEX IS INVALID
	return m_pButtons[index] == GLFW_PRESS;
}

_Ret_maybenull_ const char* Joystick::getGamepadName()
{
	GLPP_ASSERT(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return m_pGamepadName;
}

JoystickHat Joystick::getJoystickHat(unsigned int index)
{
	GLPP_ASSERT((int)index < m_iHats); // GLFW JOYSTICK HAT INDEX IS INVALID
	return (JoystickHat)m_pHats[index];
}

_Ret_z_ const char* Joystick::getJoystickGUID()
{
	GLPP_ASSERT(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return m_pGuid;
}

_Ret_z_ const char* Joystick::getJoystickName()
{
	GLPP_ASSERT(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return m_pName;
}
#endif // #ifdef _DEBUG
} // namespace glfw
