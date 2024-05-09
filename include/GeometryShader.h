#pragma once
#include "gladpp.h"
#include "_Shader.h"
#ifdef GL_VERSION_3_2
namespace gl {
/*(3.2) OpenGL geometry shader object class derived from <_Shader>*/
class GeometryShader : public _Shader
{
public:
	/*(3.2) (1) Construct an empty shader object*/
	GeometryShader() : _Shader() {}

	/*(3.2) (2) Constucts a shader object with <shareShader>*/
	GeometryShader(GeometryShader& shader)
	{
		shareShader(shader);
	}

	/*(3.2) (3) Construct shader object with <shaderSource>*/
	GeometryShader(int rcid)
	{
		shaderSource(rcid);
	}

	/*(3.2) (4) Construct shader object with <shaderSource>*/
	GeometryShader(_In_z_ const char* filepath)
	{
		shaderSource(filepath);
	}

	/*(3.2) (5) Construct shader object with <shaderSource>*/
	GeometryShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		shaderSource(count, string, length);
	}

	/*Cleans up the valid shader object*/
	~GeometryShader()
	{
		if (isShader())
		{
			deleteShader();
		}
	}

	/*(3.2) Attaches a shader object to a program object
	@param The shader program object*/
	void attachShader(Program& program)
	{
		_attachShader(GL_GEOMETRY_SHADER, program);
	}

	/*(3.2) Compiles a shader object*/
	void compileShader()
	{
		_compileShader(GL_GEOMETRY_SHADER);
	}

	/*(3.2) Creates a shader object that was previously empty*/
	void createShader()
	{
		_object_gen(&_glCreateShader, GL_GEOMETRY_SHADER);
	}

	/*(3.2) Detaches a shader object from a program object to which it is attached
	@param The shader program object*/
	void detachShader(Program& program)
	{
		_detachShader(GL_GEOMETRY_SHADER, program);
	}

	/*(3.2) Gets shader compile status parameter
	@return True if the last compile operation on shader was successful, false otherwise*/
	GLboolean getCompileStatus()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_COMPILE_STATUS);
	}

	/*(3.2) Gets shader delete status parameter
	@return True if shader is currently flagged for deletion*/
	GLboolean getDeleteStatus()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_DELETE_STATUS);
	}

	/*(3.2) Gets the number parameter of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned
	@return The number of characters in the information log*/
	GLsizei getInfoLogLength()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_INFO_LOG_LENGTH);
	}

	/*(3.2) Returns the maximum number of components of inputs read by a geometry shader
	@return The maximum geometry input components. The value must be at least 64*/
	static GLuint getMaxGeometryInputComponents()
	{
		return _getInteger(GL_MAX_GEOMETRY_INPUT_COMPONENTS);
	}

	/*(3.2) Returns the maximum number of components of outputs written by a geometry shader
	@return The maximum geometry output components. The value must be at least 128*/
	static GLuint getMaxGeometryOutputComponents()
	{
		return _getInteger(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS);
	}

	/*(3.2) Returns the maximum supported texture image units that can be used to access texture maps from the geometry shader
	@return The maximum geometry texture image units. The value must be at least 16*/
	static GLuint getMaxGeometryTextureImageUnits()
	{
		return _getInteger(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS);
	}

	/*(3.2) Returns the maximum number of uniform blocks per geometry shader
	@return The maximum geometry uniform blocks. The value must be at least 12*/
	static GLuint getMaxGeometryUniformBlocks()
	{
		return _getInteger(GL_MAX_GEOMETRY_UNIFORM_BLOCKS);
	}

	/*(3.2) Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a geometry shader
	@return The maximum geometry uniform components. The value must be at least 1024*/
	static GLuint getMaxGeometryUniformComponents()
	{
		return _getInteger(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS);
	}

	/*(3.2) (1) Returns the source code string from a shader object, or NULL if no code compiled
	@return The allocated string of a source code from a shader object, or NULL. Must be cleaned up after use*/
	_Ret_maybenull_ GLchar* getShaderSource()
	{
		return _getShaderSource(GL_GEOMETRY_SHADER);
	}

	/*(3.2) (2) Returns the source code string from a shader object
	@param Specifies the size of the character buffer for storing the returned source code string
	@param [out] Pointer to store the length of the string returned in source (excluding the null terminator)
	@param [out] Pointer to array of characters that is used to return the source code string*/
	void getShaderSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source)
	{
		_getShaderSource(GL_GEOMETRY_SHADER, bufSize, length, source);
	}

	/*(3.2) Gets the length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer required to store the shader source). If no source code exists, 0 is returned
	@return The length of the shader source for the shader*/
	GLsizei getShaderSourceLength()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_SHADER_SOURCE_LENGTH);
	}

	/*Determines via API the shader object type parameter
	@return The basic shader type enumerator*/
	ShaderType getShaderType()
	{
		return (ShaderType)_getShader(GL_GEOMETRY_SHADER, GL_SHADER_TYPE);
	}

	/*(3.2) (1) Replaces the source code in a shader object from the binary resource
	@param The source code resource id of <RCDATA> type*/
	void shaderSource(int rcid)
	{
		_shaderSource(GL_GEOMETRY_SHADER, rcid);
	}

	/*(3.2) (2) Replaces the source code in a shader object from the file
	@param [in] Path to the source code file*/
	void shaderSource(_In_z_ const char* filepath)
	{
		_shaderSource(GL_GEOMETRY_SHADER, filepath);
	}

	/*(3.2) (3) Replaces the source code in a shader object from the strings containing the source
	@param Specifies the number of elements in the string and length arrays
	@param [in] Specifies an array of pointers to strings containing the source code to be loaded into the shader
	@param [in] Specifies an array of string lengths*/
	void shaderSource(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		_shaderSource(GL_GEOMETRY_SHADER, count, string, length);
	}

	/*(3.2) Set an empty shader object as a reference to the shader object from another context
	@param The shader object to share, must not be empty*/
	void shareShader(GeometryShader& shader)
	{
		_object_share((_Object&)shader);
	}
}; // class GeometryShader : public _Shader
} // namespace gl
#endif // #ifdef GL_VERSION_3_2
