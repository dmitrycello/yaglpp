#define GLPP_BUILD_LIB
#include <glpp/_Shader.h>
#pragma comment(lib, "opengl32.lib")
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
namespace gl {
GLchar* _Shader::_getShaderSource(GLenum shaderType)
{
	GLint iSize;
	GLuint uId = _shader_id(shaderType);
	glGetShaderiv(uId, GL_SHADER_SOURCE_LENGTH, &iSize);
	if (iSize == 0)
	{
		return nullptr;
	}
	GLchar* pBuffer = (GLchar*)GLPP_MALLOC(iSize); // sizeof GLchar = 1
	glGetShaderSource(uId, iSize, &iSize, pBuffer);
	GLPP_GLAD_ERROR;
	return pBuffer;
}

void _Shader::_shaderSource(GLenum shaderType, int rcid)
{
	int iSize;
	const GLchar* pData = (GLchar*)_loadResource(rcid, &iSize);
	glShaderSource(_shader_id(shaderType), 1, &pData, &iSize);
	GLPP_GLAD_ERROR;
}

void _Shader::_shaderSource(GLenum shaderType, const char* filepath)
{
	int iSize;
	GLchar* pData = (GLchar*)_loadFile(filepath, &iSize);
	glShaderSource(_shader_id(shaderType), 1, &pData, &iSize);
	GLPP_GLAD_ERROR;
	GLPP_FREE(pData);
}

#ifdef _DEBUG
void _Shader::_attachShader(GLenum shaderType, Program& program)
{
	glAttachShader(program._program_id(), _shader_id(shaderType));
	GLPP_GLAD_ERROR;
}

void _Shader::_compileShader(GLenum shaderType)
{
	GLint iValue;
	GLuint uId = _shader_id(shaderType);
	glCompileShader(uId);
	glGetShaderiv(uId, GL_COMPILE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetShaderiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)GLPP_MALLOC(iValue); //sizeof GLchar = 1
		glGetShaderInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD SHADER ID <" << uId << "> COMPILATION ERROR:" << std::endl << pBuffer << std::endl;
		GLPP_FREE(pBuffer); // SHADER COMPILATION FAILED
		GLPP_ASSERT(false);
	}
	GLPP_GLAD_ERROR;
}

void _Shader::_createShader(GLenum shaderType)
{
	GLPP_ASSERT(m_uShader == 0); // OPENGL SHADER OBJECT MUST BE EMPTY
	m_uShader = glCreateShader(shaderType);
	GLPP_GLAD_ERROR;
}

void _Shader::_deleteShader(GLenum shaderType)
{
	GLPP_ASSERT(m_uShader != 0); // OPENGL SHADER OBJECT IS EMPTY
	glDeleteShader(m_uShader);
	m_uShader = 0;
	GLPP_GLAD_ERROR;
}

void _Shader::_detachShader(GLenum shaderType, Program& program)
{
	glDetachShader(program._program_id(), _shader_id(shaderType));
	GLPP_GLAD_ERROR;
}

GLint _Shader::_getShader(GLenum shaderType, GLenum pname)
{
	GLint iResult;
	glGetShaderiv(_shader_id(shaderType), pname, &iResult);
	GLPP_GLAD_ERROR;
	return iResult;
}

void _Shader::_getShaderSource(GLenum shaderType, GLsizei bufSize, GLsizei* length, GLchar* source)
{
	glGetShaderSource(_shader_id(shaderType), bufSize, length, source);
	GLPP_GLAD_ERROR;
}

void _Shader::_shaderSource(GLenum shaderType, GLsizei count, const GLchar** string, const GLint* length)
{
	glShaderSource(_shader_id(shaderType), count, string, length);
	GLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG
} // namespace gl
