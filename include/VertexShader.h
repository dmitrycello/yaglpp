#pragma once
#include "gladpp.h"
#include "_Shader.h"
namespace gl {
/*OpenGL vertex shader object class derived from <_Shader>*/
class VertexShader : public _Shader
{
public:
	/*(1) Construct an empty shader object*/
	VertexShader() : _Shader() {}

	/*(2) Constucts a shader object with <shareShader>*/
	VertexShader(VertexShader& shader)
	{
		shareShader(shader);
	}

	/*(3) Construct shader object with <shaderSource>*/
	VertexShader(int rcid)
	{
		shaderSource(rcid);
	}

	/*(4) Construct shader object with <shaderSource>*/
	VertexShader(_In_z_ const char* filepath)
	{
		shaderSource(filepath);
	}

	/*(5) Construct shader object with <shaderSource>*/
	VertexShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		shaderSource(count, string, length);
	}

	/*Cleans up the valid shader object*/
	~VertexShader()
	{
		if (isShader())
		{
			deleteShader();
		}
	}

	/*Attaches a shader object to a program object
	@param The shader program object*/
	void attachShader(Program& program)
	{
		_attachShader(GL_VERTEX_SHADER, program);
	}

	/*Compiles a shader object*/
	void compileShader()
	{
		_compileShader(GL_VERTEX_SHADER);
	}

	/*Creates a shader object that was previously empty*/
	void createShader()
	{
		_object_gen(&_glCreateShader, GL_VERTEX_SHADER);
	}

	/*Detaches a shader object from a program object to which it is attached
	@param The shader program object*/
	void detachShader(Program& program)
	{
		_detachShader(GL_VERTEX_SHADER, program);
	}

	/*Gets shader compile status parameter
	@return True if the last compile operation on shader was successful, false otherwise*/
	GLboolean getCompileStatus()
	{
		return _getShader(GL_VERTEX_SHADER, GL_COMPILE_STATUS);
	}

	/*Gets shader delete status parameter
	@return True if shader is currently flagged for deletion*/
	GLboolean getDeleteStatus()
	{
		return _getShader(GL_VERTEX_SHADER, GL_DELETE_STATUS);
	}

	/*Gets the number parameter of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned
	@return The number of characters in the information log*/
	GLsizei getInfoLogLength()
	{
		return _getShader(GL_VERTEX_SHADER, GL_INFO_LOG_LENGTH);
	}

	/*Returns the maximum number of 4-component generic vertex attributes accessible to a vertex shader
	@return The maximum vertex attributes. The value must be at least 16*/
	static GLuint getMaxVertexAttribs()
	{
		return _getInteger(GL_MAX_VERTEX_ATTRIBS);
	}

	/*Returns the maximum supported texture image units that can be used to access texture maps from the vertex shader
	@return The maximum vertex texture image units. The value may be at least 16*/
	static GLuint getMaxVertexTextureImageUnits()
	{
		return _getInteger(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	}

	/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a vertex shader
	@return The maximum vertex uniform components. The value must be at least 1024*/
	static GLuint getMaxVertexUniformComponents()
	{
		return _getInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
	}

	/*(1) Returns the source code string from a shader object, or NULL if no code compiled
	@return The allocated string of a source code from a shader object, or NULL. Must be cleaned up after use*/
	_Ret_maybenull_ GLchar* getShaderSource()
	{
		return _getShaderSource(GL_VERTEX_SHADER);
	}

	/*(2) Returns the source code string from a shader object
	@param Specifies the size of the character buffer for storing the returned source code string
	@param [out] Pointer to store the length of the string returned in source (excluding the null terminator)
	@param [out] Pointer to array of characters that is used to return the source code string*/
	void getShaderSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source)
	{
		_getShaderSource(GL_VERTEX_SHADER, bufSize, length, source);
	}

	/*Gets the length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer required to store the shader source). If no source code exists, 0 is returned
	@return The length of the shader source for the shader*/
	GLsizei getShaderSourceLength()
	{
		return _getShader(GL_VERTEX_SHADER, GL_SHADER_SOURCE_LENGTH);
	}

	/*Determines via API the shader object type parameter
	@return The basic shader type enumerator*/
	ShaderType getShaderType()
	{
		return (ShaderType)_getShader(GL_VERTEX_SHADER, GL_SHADER_TYPE);
	}

	/*(1) Replaces the source code in a shader object from the binary resource
	@param The source code resource id of <RCDATA> type*/
	void shaderSource(int rcid)
	{
		_shaderSource(GL_VERTEX_SHADER, rcid);
	}
	
	/*(2) Replaces the source code in a shader object from the file
	@param [in] Path to the source code file*/
	void shaderSource(_In_z_ const char* filepath)
	{
		_shaderSource(GL_VERTEX_SHADER, filepath);
	}

	/*(3) Replaces the source code in a shader object from the strings containing the source
	@param Specifies the number of elements in the string and length arrays
	@param [in] Specifies an array of pointers to strings containing the source code to be loaded into the shader
	@param [in] Specifies an array of string lengths*/
	void shaderSource(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		_shaderSource(GL_VERTEX_SHADER, count, string, length);
	}

	/*Set an empty shader object as a reference to the shader object from another context
	@param The shader object to share, must not be empty*/
	void shareShader(VertexShader& shader)
	{
		_object_share((_Object&)shader);
	}
#ifdef GL_VERSION_3_1
	/*(3.1) Returns the maximum number of uniform blocks per vertex shader
	@return The maximum vertex uniform components. The value must be at least 12*/
	static GLuint getMaxVertexUniformBlocks()
	{
		return _getInteger(GL_MAX_VERTEX_UNIFORM_BLOCKS);
	}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) Returns the maximum number of components of output written by a vertex shader
	@return The maximum vertex output components. The value must be at least 64*/
	static GLuint getMaxVertexOutputComponents()
	{
		return _getInteger(GL_MAX_VERTEX_OUTPUT_COMPONENTS);
	}
#endif // #ifdef GL_VERSION_3_2
}; // class VertexShader : public _Shader
} // namespace gl
