#pragma once
#include <yaglpp/glad/_object.h>
namespace gl {
/*GLAD basic shader type enumerator*/
enum class ShaderType : GLenum
{
	/*Fragment shader type. The shader stage that will process a Fragment generated by the Rasterization into a set of colors and a single depth value*/
	FragmentShader = GL_FRAGMENT_SHADER,

	/*Vertex shader type. The programmable shader stage in the rendering pipeline that handles the processing of individual vertices*/
	VertexShader = GL_VERTEX_SHADER,

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Geometry shader type. The shader program written in GLSL that governs the processing of primitives*/
	GeometryShader = GL_GEOMETRY_SHADER,
#endif // #ifdef YAGLPP_VERSION_3_2
};

/*OpenGL shader object abstract class derived from <_Object>*/
class _Shader : public _Object
{
protected:
	void _shader_delete() {
		_object_delete(_glDeleteShader);
	}
	void _shader_dup(_Object& source) {
		_object_dup(_glDeleteShader, source);
	}
	void _shader_gen(GLenum shaderType) {
		_object_gen(_glCreateShader, _glDeleteShader, shaderType);
	}
	GLuint _shader_id(GLenum shaderType) {
		return _object_id(_glCreateShader, shaderType);
	}
	void _shader_ref(_Object& source) {
		_object_ref(_glDeleteShader, source);
	}
	void _attachShader(GLenum shaderType, Program& program);
	void _compileShader(GLenum shaderType);
	void _detachShader(GLenum shaderType, Program& program);
	GLint _getShader(GLenum shaderType, GLenum pname);
	GLchar* _getShaderSource(GLenum shaderType);
	void _getShaderSource(GLenum shaderType, GLsizei bufSize, GLsizei* length, GLchar* source);
	static void WINAPI _glCreateShader(GLsizei shaderType, GLuint* id);
	static void WINAPI _glDeleteShader(GLsizei unused, const GLuint* id);
	void _setShader(GLenum type, GLboolean gen);
	void _shaderSource(GLenum shaderType, int rcid);
	void _shaderSource(GLenum shaderType, const char* filepath);
	void _shaderSource(GLenum shaderType, GLsizei count, const GLchar** string, const GLint* length);

public:
	/*Cleans up the valid shader object*/
	~_Shader()
	{
		_shader_delete();
	}

	/*Explicitly deletes previously generated shader object*/
	void deleteShader()
	{
		_shader_delete();
	}

	/*Determines if a name corresponds to a shader object. Used as a getter of <shader> property
	@return True if valid shader object, false otherwise*/
	GLboolean isShader()
	{
		return glIsShader(_object_id());
	}
}; // class _Shader
} // namespace gl

#include <yaglpp/glad/program.h>
namespace gl {
#ifdef YAGLPP_IMPLEMENTATION
GLchar* _Shader::_getShaderSource(GLenum shaderType)
{
	GLint iSize;
	GLuint uId = _shader_id(shaderType);
	glGetShaderiv(uId, GL_SHADER_SOURCE_LENGTH, &iSize);
	if (iSize == 0)
	{
		return nullptr;
	}
	GLchar* pBuffer = (GLchar*)_allocate(iSize, nullptr);
	glGetShaderSource(uId, iSize, &iSize, pBuffer);
	YAGLPP_GLAD_ERROR;
	return pBuffer;
}

void _Shader::_setShader(GLenum type, GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			_shader_delete();
		}
	}
	else if (gen == GL_TRUE)
	{
		_shader_gen(type);
	}
}

void _Shader::_shaderSource(GLenum shaderType, int rcid)
{
	int iSize;
	const GLchar* pData = (GLchar*)_loadResource(rcid, &iSize);
	glShaderSource(_shader_id(shaderType), 1, &pData, &iSize);
	YAGLPP_GLAD_ERROR;
}

void _Shader::_shaderSource(GLenum shaderType, const char* filepath)
{
	int iSize = 0; // header bytes
	GLchar* pData = (GLchar*)_loadFile(filepath, &iSize, nullptr);
	glShaderSource(_shader_id(shaderType), 1, &pData, &iSize);
	YAGLPP_GLAD_ERROR;
	_deallocate(pData, nullptr);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void _Shader::_attachShader(GLenum shaderType, Program& program)
{
	glAttachShader(program._program_id(), _shader_id(shaderType));
	YAGLPP_GLAD_ERROR;
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
		GLchar* pBuffer = (GLchar*)_allocate(iValue, nullptr);
		glGetShaderInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD SHADER ID <" << uId << "> COMPILATION ERROR:" << std::endl << pBuffer << std::endl;
		_deallocate(pBuffer, nullptr);
		YAGLPP_ASSERT(false); // SHADER COMPILATION FAILED
	}
	YAGLPP_GLAD_ERROR;
}

void _Shader::_detachShader(GLenum shaderType, Program& program)
{
	glDetachShader(program._program_id(), _shader_id(shaderType));
	YAGLPP_GLAD_ERROR;
}

GLint _Shader::_getShader(GLenum shaderType, GLenum pname)
{
	GLint iResult;
	glGetShaderiv(_shader_id(shaderType), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void _Shader::_getShaderSource(GLenum shaderType, GLsizei bufSize, GLsizei* length, GLchar* source)
{
	glGetShaderSource(_shader_id(shaderType), bufSize, length, source);
	YAGLPP_GLAD_ERROR;
}

void WINAPI _Shader::_glCreateShader(GLsizei shaderType, GLuint* id)
{
	*id = glCreateShader((GLenum)shaderType);
	YAGLPP_GLAD_ERROR;
}

void WINAPI _Shader::_glDeleteShader(GLsizei unused, const GLuint* id)
{
	glDeleteShader(*id);
	YAGLPP_GLAD_ERROR;
}

void _Shader::_shaderSource(GLenum shaderType, GLsizei count, const GLchar** string, const GLint* length)
{
	glShaderSource(_shader_id(shaderType), count, string, length);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void _Shader::_attachShader(GLenum shaderType, Program& program)
{
	glAttachShader(program._program_id(), _shader_id(shaderType));
}

inline void _Shader::_compileShader(GLenum shaderType)
{
	glCompileShader(_shader_id(shaderType));
}

inline void _Shader::_detachShader(GLenum shaderType, Program& program)
{
	glDetachShader(program._program_id(), _shader_id(shaderType));
}

inline GLint _Shader::_getShader(GLenum shaderType, GLenum pname)
{
	GLint i; glGetShaderiv(_shader_id(shaderType), pname, &i); return i;
}

inline void _Shader::_getShaderSource(GLenum shaderType, GLsizei bufSize, GLsizei* length, GLchar* source)
{
	glGetShaderSource(_shader_id(shaderType), bufSize, length, source);
}

inline void WINAPI _Shader::_glCreateShader(GLsizei shaderType, GLuint* id)
{
	*id = glCreateShader((GLenum)shaderType);
}

inline void WINAPI _Shader::_glDeleteShader(GLsizei unused, const GLuint* id)
{
	glDeleteShader(*id);
}

inline void _Shader::_shaderSource(GLenum shaderType, GLsizei count, const GLchar** string, const GLint* length)
{
	glShaderSource(_shader_id(shaderType), count, string, length);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/shader/vertex_shader.h>
#include <yaglpp/shader/fragment_shader.h>
#include <yaglpp/shader/geometry_shader.h>
