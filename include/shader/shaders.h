#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_SHADERS_H
#define YAGLPP_SHADERS_H

namespace gl {
/*OpenGL untyped shader object class derived from <Objects>. Can be used as a temporary asset before its reference is casted to any valid shader type*/
class Shaders : public Objects
{
public:
	using Objects::Objects;
	enum class Type : GLenum;
	/*Attaches a shader object to a program object
	@param The shader program object*/
	void Attach(Program& program);

	/*Compiles a shader object*/
	void Compile();

	/*Deletes valid OpenGL shader object name and sets the shader class object in empty state*/
	void Delete()
	{
		object_delete(gl_delete_shader);
	}

	/*Detaches a shader object from a program object to which it is attached
	@param The shader program object*/
	void Detach(Program& program);

	/*Gets shader compile status parameter. MSVC getter for <compileStatus> property
	@return True if the last compile operation on shader was successful, false otherwise*/
	GLboolean GetCompileStatus()
	{
		return get_shader(GL_COMPILE_STATUS);
	}

	/*Gets shader delete status parameter. MSVC getter for <deleteStatus> property
	@return True if shader is currently flagged for deletion*/
	GLboolean GetDeleteStatus()
	{
		return get_shader(GL_DELETE_STATUS);
	}

	/*Gets the number parameter of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned. MSVC getter for <infoLogLength> property
	@return The number of characters in the information log*/
	GLsizei GetInfoLogLength()
	{
		return get_shader(GL_INFO_LOG_LENGTH);
	}

	/*(1) Returns the source code string from a shader object, or NULL if no code compiled
	@return The allocated string of a source code from a shader object, or NULL. Must be cleaned up after use*/
	_Ret_maybenull_ GLchar* GetSource();

	/*(2) Returns the source code string from a shader object
	@param Specifies the size of the character buffer for storing the returned source code string
	@param [out] Pointer to store the length of the string returned in source (excluding the null terminator)
	@param [out] Pointer to array of characters that is used to return the source code string*/
	void GetSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source);

	/*Gets the length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer required to store the shader source). If no source code exists, 0 is returned. MSVC getter for <sourceLength> property
	@return The length of the shader source for the shader*/
	GLsizei GetSourceLength()
	{
		return get_shader(GL_SHADER_SOURCE_LENGTH);
	}

	/*Determines via API the shader object type parameter. MSVC getter for <type> property
	@return The basic shader type enumerator*/
	Type GetType()
	{
		return (Type)get_shader(GL_SHADER_TYPE);
	}

	/*Determines if a valid OpenGL shader object name corresponds to a shader object. MSVC getter for <shader> property
	@return True if active shader object, false otherwise*/
	GLboolean IsShader() const
	{
		return object_is(glIsShader);
	}

	/*Replaces the source code in a shader object from the strings containing the source
	@param Specifies the number of elements in the string and length arrays
	@param [in] Specifies an array of pointers to strings containing the source code to be loaded into the shader
	@param [in] Specifies an array of string lengths*/
	void Source(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length);

	/*Replaces the source code in a shader object from the file
	@param [in] Path to the source code file*/
	void SourceFromFile(_In_z_ const char* filepath);

	/*Replaces the source code in a shader object from the memory resource
	@param [in] The memory resource data location
	@param The memory resource data size*/
	void SourceFromMemory(_In_ unsigned char* data, unsigned int size);

#ifdef YAGLPP_MSVC
	/*Replaces the source code in a shader object from the binary resource (Windows only)
	@param The binary resource id of <RC_DATA> type*/
	void SourceFromResource(int rcid)
	{
		unsigned int s = 0; SourceFromMemory(yaglpp_load_resource(rcid, &s), s);
	}
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for shader compile status parameter*/
	__declspec(property(get = GetCompileStatus)) GLboolean compileStatus;

	/*Read-only property for shader delete status parameter*/
	__declspec(property(get = GetDeleteStatus)) GLboolean deleteStatus;

	/*Read-only property for number parameter of characters in the information log for shader including the null termination character*/
	__declspec(property(get = GetInfoLogLength)) GLsizei infoLogLength;

	/*Read-only property to check if active shader object*/
	__declspec(property(get = IsShader)) GLboolean shader;

	/*Read-only property for length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character*/
	__declspec(property(get = GetSourceLength)) GLsizei sourceLength;

	/*Read-only property for shader object type parameter*/
	__declspec(property(get = GetType)) Type type;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	GLint get_shader(GLenum pname);
	static void APIENTRY gl_create_fragment_shader(GLsizei unused, GLuint* id);
	static void APIENTRY gl_create_vertex_shader(GLsizei unused, GLuint* id);
	static void APIENTRY gl_delete_shader(GLsizei unused, const GLuint* id);
	void source(PFNGEN pfnGen, GLsizei count, const GLchar** string, const GLint* length);
	void source_from_file(PFNGEN pfnGen, const char* filepath);
	void source_from_memory(PFNGEN pfnGen, unsigned char* data, unsigned int size);

#ifdef YAGLPP_MSVC
	void source_from_resource(PFNGEN pfnGen, int rcid);
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_VERSION_3_2
	static void APIENTRY gl_create_geometry_shader(GLsizei unused, GLuint* id);
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class Shaders : public Object

/*GLAD basic shader type enumerator*/
enum class Shaders::Type : GLenum
{
	/*Fragment shader type. The shader stage that will process a Fragment generated by the Rasterization into a set of colors and a single depth value*/
	Fragment = GL_FRAGMENT_SHADER,

	/*Vertex shader type. The programmable shader stage in the rendering pipeline that handles the processing of individual vertices*/
	Vertex = GL_VERTEX_SHADER,

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Geometry shader type. The shader program written in GLSL that governs the processing of primitives*/
	Geometry = GL_GEOMETRY_SHADER,
#endif // #ifdef YAGLPP_VERSION_3_2
};

#ifdef YAGLPP_IMPLEMENTATION
void APIENTRY Shaders::gl_create_fragment_shader(GLsizei unused, GLuint* id)
{
	*id = glCreateShader(GL_FRAGMENT_SHADER);
}

void APIENTRY Shaders::gl_create_vertex_shader(GLsizei unused, GLuint* id)
{
	*id = glCreateShader(GL_VERTEX_SHADER);
}

void APIENTRY Shaders::gl_delete_shader(GLsizei unused, const GLuint* id)
{
	glDeleteShader(*id);
}

void Shaders::source(PFNGEN pfnGen, GLsizei count, const GLchar** string, const GLint* length)
{
	object_gen(pfnGen);
	Source(count, string, length);
	Compile();
}

void Shaders::source_from_file(PFNGEN pfnGen, const char* filepath)
{
	object_gen(pfnGen);
	SourceFromFile(filepath);
	Compile();
}

void Shaders::source_from_memory(PFNGEN pfnGen, unsigned char* data, unsigned int size)
{
	object_gen(pfnGen);
	SourceFromMemory(data, size);
	Compile();
}

_Ret_maybenull_ GLchar* Shaders::GetSource()
{
	GLint iSize;
	GLuint uId = object_id();
	glGetShaderiv(uId, GL_SHADER_SOURCE_LENGTH, &iSize);
	if (iSize == 0)
	{
		return nullptr;
	}
	GLchar* pBuffer = YAGLPP_MALLOC(GLchar, iSize);
	glGetShaderSource(uId, iSize, &iSize, pBuffer);
	YAGLPP_GLAD_ERROR;
	return pBuffer;
}

void Shaders::SourceFromFile(_In_z_ const char* filepath)
{
	int iSize = 0;
	const GLchar* pData = (GLchar*)yaglpp_load_file(filepath, &iSize, nullptr);
	Source(1, &pData, &iSize);
	YAGLPP_FREE((void*)pData);
}

void Shaders::SourceFromMemory(_In_ unsigned char* data, unsigned int size)
{
	GLint iLength = size; // lvalues
	const GLchar* pString = (const GLchar*)data;
	Source(1, &pString, &iLength);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#if defined (YAGLPP_MSVC) && defined (YAGLPP_IMPLEMENTATION)
void Shaders::source_from_resource(PFNGEN pfnGen, int rcid)
{
	object_gen(pfnGen);
	SourceFromResource(rcid);
	Compile();
}
#endif // #if defined (YAGLPP_MSVC) && defined (YAGLPP_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
void APIENTRY Shaders::gl_create_geometry_shader(GLsizei unused, GLuint* id)
{
	*id = glCreateShader(GL_GEOMETRY_SHADER);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint Shaders::get_shader(GLenum pname)
{
	GLint iResult;
	glGetShaderiv(object_id(), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void Shaders::Attach(Program& program)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glAttachShader(program.Get(), object_id());
	YAGLPP_GLAD_ERROR;
}

void Shaders::Compile()
{
	GLint iValue;
	GLuint uId = object_id();
	glCompileShader(uId);
	glGetShaderiv(uId, GL_COMPILE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetShaderiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = YAGLPP_MALLOC(GLchar, iValue);
		glGetShaderInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "YAGL++ GLAD shader id <" << uId << "> compilation error:\n" << pBuffer << std::endl;
		YAGLPP_FREE(pBuffer);

		// SHADER COMPILATION FAILED
		YAGLPP_ASSERT(0);
	}
	YAGLPP_GLAD_ERROR;
}

void Shaders::Detach(Program& program)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glDetachShader(program.Get(), object_id());
	YAGLPP_GLAD_ERROR;
}

void Shaders::GetSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source)
{
	glGetShaderSource(object_id(), bufSize, length, source);
	YAGLPP_GLAD_ERROR;
}

void Shaders::Source(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
{
	glShaderSource(object_id(), count, string, length);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint Shaders::get_shader(GLenum pname)
{
	GLint i; glGetShaderiv(object_id(), pname, &i); return i;
}

inline void Shaders::Attach(Program& program)
{
	glAttachShader(program.Get(), object_id());
}

inline void Shaders::Compile()
{
	glCompileShader(object_id());
}

inline void Shaders::Detach(Program& program)
{
	glDetachShader(program.Get(), object_id());
}

inline void Shaders::GetSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source)
{
	glGetShaderSource(object_id(), bufSize, length, source);
}

inline void Shaders::Source(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
{
	glShaderSource(object_id(), count, string, length);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/shader/vertex_shader.h>
#include <yaglpp/shader/fragment_shader.h>
#include <yaglpp/shader/geometry_shader.h>
#endif //#ifndef YAGLPP_SHADERS_H
