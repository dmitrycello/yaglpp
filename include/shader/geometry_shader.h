#pragma once
#include <yaglpp/shader/_shader.h>
#ifdef YAGLPP_VERSION_3_2
namespace gl {
/*(3.2) OpenGL geometry shader object class derived from <_Shader>*/
class GeometryShader : public _Shader
{
public:
	/*(3.2) (1) Constructs an empty shader object*/
	GeometryShader() {}

	/*(3.2) (2) Constructs a copy of shader object*/
	GeometryShader(const GeometryShader& source)
	{
		_shader_dup((_Object&)source);
	}

	/*(3.2) (3) Constructs shader object from binary resource*/
	GeometryShader(int rcid)
	{
		_shaderSource(GL_GEOMETRY_SHADER, rcid);
	}

	/*(3.2) (4) Constructs shader object from file*/
	GeometryShader(_In_z_ const char* filepath)
	{
		_shaderSource(GL_GEOMETRY_SHADER, filepath);
	}

	/*(3.2) (5) Constructs shader object from strings containing the source*/
	GeometryShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		_shaderSource(GL_GEOMETRY_SHADER, count, string, length);
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

	/*(3.2) Explicitly generates OpenGL shader object*/
	void createShader()
	{
		_shader_gen(GL_GEOMETRY_SHADER);
	}

	/*(3.2) Detaches a shader object from a program object to which it is attached
	@param The shader program object*/
	void detachShader(Program& program)
	{
		_detachShader(GL_GEOMETRY_SHADER, program);
	}

	/*(3.2) Duplicates a shader object, increasing its reference count. The reference source object is being copied
	@param Specifies the source shader object*/
	void duplicateShader(const GeometryShader& source)
	{
		_shader_dup((_Object&)source);
	}

	/*(3.2) Gets shader compile status parameter. Used as a getter of <compileStatus> property
	@return True if the last compile operation on shader was successful, false otherwise*/
	GLboolean getCompileStatus()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_COMPILE_STATUS);
	}

	/*(3.2) Gets shader delete status parameter. Used as a getter of <deleteStatus> property
	@return True if shader is currently flagged for deletion*/
	GLboolean getDeleteStatus()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_DELETE_STATUS);
	}

	/*(3.2) Gets the number parameter of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned. Used as a getter of <infoLogLength> property
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

	/*(3.2) Gets the length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer required to store the shader source). If no source code exists, 0 is returned. Used as a getter of <shaderSourceLength> property
	@return The length of the shader source for the shader*/
	GLsizei getShaderSourceLength()
	{
		return _getShader(GL_GEOMETRY_SHADER, GL_SHADER_SOURCE_LENGTH);
	}

	/*(3.2) Determines via API the shader object type parameter. Used as a getter of <shaderType> property
	@return The basic shader type enumerator*/
	ShaderType getShaderType()
	{
		return (ShaderType)_getShader(GL_GEOMETRY_SHADER, GL_SHADER_TYPE);
	}

	/*(3.2) Checks if the source shader object is referencing the same OpenGL object
	@param Specifies the source shader object
	@return True if duplicate object*/
	GLboolean isDuplicate(const GeometryShader& source) const
	{
		return _object_is((_Object&)source);
	}

	/*(3.2) Creates a thread-safe reference object from the source shader object
	@param Specifies the source shader object*/
	void referShader(const GeometryShader& source)
	{
		_shader_refer((_Object&)source);
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

	/*(3.2) Sets the creation state of the shader object, only if current state is opposite. Depending of the flag value, calls <createShader> or <deleteShader> functions. Used as a setter of <shader> property
	@param True to generate shader object name, false to delete shader object*/
	void setShader(GLboolean gen)
	{
		_setShader(GL_GEOMETRY_SHADER, gen);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property for shader compile status parameter*/
	__declspec(property(get = getCompileStatus)) GLboolean compileStatus;

	/*(3.2) Read-only property for shader delete status parameter*/
	__declspec(property(get = getDeleteStatus)) GLboolean deleteStatus;

	/*(3.2) Read-only property for number parameter of characters in the information log for shader including the null termination character*/
	__declspec(property(get = getInfoLogLength)) GLsizei infoLogLength;

	/*(3.2) Read-write property for creation state of the shader object*/
	__declspec(property(get = isShader, put = setShader)) GLboolean shader;

	/*(3.2) Read-only property for length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character*/
	__declspec(property(get = getShaderSourceLength)) GLsizei shaderSourceLength;

	/*(3.2) Read-only property for shader object type parameter*/
	__declspec(property(get = getShaderType)) ShaderType shaderType;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class GeometryShader : public _Shader
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_2
