#define YAGLPP_BUILD_LIB
#include <yaglpp/Joystick.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
namespace glfw {
Joystick::_SDATA::_SDATA()
{
	getJoysticks();
	glfwSetJoystickCallback(&_joystickCallback);
}

void Joystick::_SDATA::getJoysticks()
{
	m_iJcount = 0;
	for (int jid = 0; jid < (GLFW_JOYSTICK_LAST + 1); jid++)
	{
		if (glfwJoystickPresent(jid))
		{
			m_pJoysticks[m_iJcount++] = jid;
		}
	}
}

void Joystick::_joystickCallback(int jid, int event)
{
	s_Data.getJoysticks();
	if (event == GLFW_DISCONNECTED)
	{
		Joystick* pClass = (Joystick*)glfwGetJoystickUserPointer(jid);
		if (pClass != nullptr)
		{
			pClass->onDisconnect();

#ifdef _DEBUG
			std::cout << "GLFW JOYSTICK <" << pClass->m_pName << "> WITH GUID <" << pClass->m_pGuid << "> ";
			if (pClass->m_pGamepad)
			{
				std::cout << "WITH GANEPAD PRESENT <" << pClass->m_pGamepad << "> ";
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

		if (s_Data.m_pConnected != nullptr)
		{
			s_Data.m_pConnected(pGuid, pName, pGamepad);
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
	m_pGamepad = glfwGetGamepadName(jid);
	glfwSetJoystickUserPointer(jid, this);
}

void Joystick::deselectJoystick()
{
	glfwSetJoystickUserPointer(_jid(), nullptr);
	memset(this, 0, sizeof(Joystick));
}

bool Joystick::loadGamepadMappings(int rcid)
{
	int iSize = 0;
	const char* pData = (char*)_loadResource(rcid, &iSize);
	return (bool)glfwUpdateGamepadMappings(pData);
}

bool Joystick::loadGamepadMappings(_In_z_ const char* file)
{
	int iSize = 0;
	char* pData = (char*)_loadFile(file, &iSize);
	if (pData)
	{
		iSize = glfwUpdateGamepadMappings(pData);
		YAGLPP_FREE(pData);
	}
	return (bool)iSize;
}

void Joystick::selectJoystick(_In_z_ const char* jname)
{
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	for (int i = 0; i < s_Data.m_iJcount; i++)
	{
		int jid = s_Data.m_pJoysticks[i];
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
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	for (int i = 0; i < s_Data.m_iJcount; i++)
	{
		int jid = s_Data.m_pJoysticks[i];
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
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return m_iJid;
}

_Ret_maybenull_ const char* Joystick::getGamepadName() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK IS UNAVAILABLE
	return m_pGamepad;
}

float Joystick::getJoystickAxis(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < m_iAxes); // GLFW JOYSTICK AXIS INDEX IS INVALID
	return m_pAxes[index];
}

bool Joystick::getJoystickButton(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < m_iButtons); // GLFW JOYSTICK BUTTON INDEX IS INVALID
	return m_pButtons[index] == GLFW_PRESS;
}

JoystickHat Joystick::getJoystickHat(unsigned int index) const
{
	YAGLPP_ASSERT((int)index < m_iHats); // GLFW JOYSTICK HAT INDEX IS INVALID
	return (JoystickHat)m_pHats[index];
}

_Ret_z_ const char* Joystick::getJoystickGUID() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return m_pGuid;
}

_Ret_z_ const char* Joystick::getJoystickName() const
{
	YAGLPP_ASSERT(isJoystick()); // GLFW JOYSTICK WAS NOT SELECTED
	return m_pName;
}

void Joystick::selectJoystick(unsigned int jindex)
{
	YAGLPP_ASSERT(!isJoystick()); // GLFW JOYSTICK OBJECT MUST BE DESELECTED
	YAGLPP_ASSERT(jindex < (unsigned int)s_Data.m_iJcount); // JOYSTICK INDEX IS INVALID
	_select(s_Data.m_pJoysticks[jindex]);
}
#endif // #ifdef _DEBUG
} // namespace glfw
