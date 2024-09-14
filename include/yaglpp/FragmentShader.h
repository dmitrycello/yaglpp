#pragma once
#include "_Shader.h"
namespace gl {
// OpenGL fragment shader object class derived from <_Shader>
class FragmentShader : public _Shader
{
public:
	/*(1) Construct an empty shader object*/
	FragmentShader() {}

	/*(2) Constucts a shader object with <shareShader>*/
	FragmentShader(FragmentShader& shader)
	{
		shareShader(shader);
	}

	/*(3) Construct shader object with <shaderSource>*/
	FragmentShader(int rcid)
	{
		shaderSource(rcid);
	}

	/*(4) Construct shader object with <shaderSource>*/
	FragmentShader(_In_z_ const char* filepath)
	{
		shaderSource(filepath);
	}

	/*(5) Construct shader object with <shaderSource>*/
	FragmentShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		shaderSource(count, string, length);
	}

	/*Cleans up the valid shader object*/
	~FragmentShader()
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
		_attachShader(GL_FRAGMENT_SHADER, program);
	}

	/*Compiles a shader object*/
	void compileShader()
	{
		_compileShader(GL_FRAGMENT_SHADER);
	}

	/*Creates a shader object that was previously empty*/
	void createShader()
	{
		_object_gen(&_glCreateShader, GL_FRAGMENT_SHADER);
	}

	/*Detaches a shader object from a program object to which it is attached
	@param The shader program object*/
	void detachShader(Program& program)
	{
		_detachShader(GL_FRAGMENT_SHADER, program);
	}

	/*Gets shader compile status parameter. Used as a getter of <compileStatus> property
	@return True if the last compile operation on shader was successful, false otherwise*/
	GLboolean getCompileStatus()
	{
		return _getShader(GL_FRAGMENT_SHADER, GL_COMPILE_STATUS);
	}

	/*Gets shader delete status parameter. Used as a getter of <deleteStatus> property
	@return True if shader is currently flagged for deletion*/
	GLboolean getDeleteStatus()
	{
		return _getShader(GL_FRAGMENT_SHADER, GL_DELETE_STATUS);
	}

	/*Gets a symbolic constant indicating the mode of the derivative accuracy hint for fragment shaders
	@return The desired behavior hint. The initial value is <DontCare>*/
	static BehaviorHint getFragmentShaderDerivativeHint()
	{
		return (BehaviorHint)_getInteger(GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
	}

	/*Gets the number parameter of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned. Used as a getter of <infoLogLength> property
	@return The number of characters in the information log*/
	GLsizei getInfoLogLength()
	{
		return _getShader(GL_FRAGMENT_SHADER, GL_INFO_LOG_LENGTH);
	}

	/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a fragment shader
	@return The maximum fragment uniform components. The value must be at least 1024*/
	static GLint getMaxFragmentUniformComponents()
	{
		return _getInteger(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
	}

	/*(1) Returns the source code string from a shader object, or NULL if no code compiled
	@return The allocated string of a source code from a shader object, or NULL. Must be cleaned up after use*/
	_Ret_maybenull_ GLchar* getShaderSource()
	{
		return _getShaderSource(GL_FRAGMENT_SHADER);
	}

	/*(2) Returns the source code string from a shader object
	@param Specifies the size of the character buffer for storing the returned source code string
	@param [out] Pointer to store the length of the string returned in source (excluding the null terminator)
	@param [out] Pointer to array of characters that is used to return the source code string*/
	void getShaderSource(GLsizei bufSize, _Out_writes_(1) GLsizei* length, _Out_writes_(bufSize) GLchar* source)
	{
		_getShaderSource(GL_FRAGMENT_SHADER, bufSize, length, source);
	}

	/*Gets the length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer required to store the shader source). If no source code exists, 0 is returned. Used as a getter of <shaderSourceLength> property
	@return The length of the shader source for the shader*/
	GLsizei getShaderSourceLength()
	{
		return _getShader(GL_FRAGMENT_SHADER, GL_SHADER_SOURCE_LENGTH);
	}

	/*Determines via API the shader object type parameter. Used as a getter of <shaderType> property
	@return The basic shader type enumerator*/
	ShaderType getShaderType()
	{
		return (ShaderType)_getShader(GL_FRAGMENT_SHADER, GL_SHADER_TYPE);
	}

	/*Set the accuracy of the derivative calculation for the GL shading language fragment processing built-in functions: dFdx, dFdy, and fwidth
	@param Specifies a symbolic constant indicating the desired behavior*/
	static void setFragmentShaderDerivativeHint(BehaviorHint hint)
	{
		_hint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, (GLenum)hint);
	}

	/*(1) Replaces the source code in a shader object from the binary resource
	@param The source code resource id of <RCDATA> type*/
	void shaderSource(int rcid)
	{
		_shaderSource(GL_FRAGMENT_SHADER, rcid);
	}

	/*(2) Replaces the source code in a shader object from the file
	@param [in] Path to the source code file*/
	void shaderSource(_In_z_ const char* filepath)
	{
		_shaderSource(GL_FRAGMENT_SHADER, filepath);
	}

	/*(3) Replaces the source code in a shader object from the strings containing the source
	@param Specifies the number of elements in the string and length arrays
	@param [in] Specifies an array of pointers to strings containing the source code to be loaded into the shader
	@param [in] Specifies an array of string lengths*/
	void shaderSource(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length)
	{
		_shaderSource(GL_FRAGMENT_SHADER, count, string, length);
	}

	/*Set an empty shader object as a reference to the shader object from another context
	@param The shader object to share, must not be empty*/
	void shareShader(FragmentShader& shader)
	{
		_object_share((_Object&)shader);
	}

	/*Sets the creation state of the shader object, only if current state is opposite. Depending of the flag value, calls <createShader> or <deleteShader> functions. Used as a setter of <shader> property
	@param True to generate shader object name, false to delete shader object*/
	void setShader(GLboolean gen)
	{
		_setShader(GL_FRAGMENT_SHADER, gen);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for shader compile status parameter*/
	__declspec(property(get = getCompileStatus)) GLboolean compileStatus;

	/*Read-only property for shader delete status parameter*/
	__declspec(property(get = getDeleteStatus)) GLboolean deleteStatus;

	/*Read-only property for number parameter of characters in the information log for shader including the null termination character*/
	__declspec(property(get = getInfoLogLength)) GLsizei infoLogLength;

	/*Read-write property for creation state of the shader object*/
	__declspec(property(get = isShader, put = setShader)) GLboolean shader;

	/*Read-only property for length parameter of the concatenation of the source strings that make up the shader source for the shader, including the null termination character*/
	__declspec(property(get = getShaderSourceLength)) GLsizei shaderSourceLength;

	/*Read-only property for shader object type parameter*/
	__declspec(property(get = getShaderType)) ShaderType shaderType;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_1
	/*(3.1) Returns the maximum number of uniform blocks per fragment shader
	@return The maximum fragment uniform components. The value must be at least 12*/
	static GLint getMaxFragmentUniformBlocks()
	{
		return _getInteger(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
	}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) Returns the maximum number of components of the inputs read by the fragment shader
	@return The maximum fragment input components. The value must be at least 128*/
	static GLuint getMaxFragmentInputComponents()
	{
		return _getInteger(GL_MAX_FRAGMENT_INPUT_COMPONENTS);
	}
#endif // #ifdef GL_VERSION_3_2
}; // class FragmentShader : public _Shader
} // namespace gl
