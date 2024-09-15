#pragma once
#include <yaglpp/glad/_object.h>
namespace gl {
/*GLAD active attribute info structure used by <getActiveAttrib>*/
struct ActiveAttribInfo
{
	/*The size of the attribute variable*/
	GLint size;

	/*The data type of the attribute variable*/
	ActiveAttribType type;

	/*The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*The null terminated string containing the name of the uniform variable*/
	GLchar name[MAX_PATH];
};

/*GLAD active uniform info structure used by <getActiveUniform>*/
struct ActiveUniformInfo
{
	/*The size of the uniform variable*/
	GLint size;

	/*The data type of the uniform variable*/
	ActiveUniformType type;

	/*The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*The null terminated string containing the name of the uniform variable*/
	GLchar name[MAX_PATH];
};

#ifdef GL_VERSION_3_1
/*(3.1) GLAD active uniform block info structure used by <getActiveUniformBlock>*/
struct ActiveUniformBlockInfo
{
	/*(3.1) The number of active uniforms in the uniform block*/
	GLsizei uniformBlockActiveUniforms;

	/*(3.1) The last selected index of the uniform buffer binding point*/
	GLuint uniformBlockBinding;

	/*(3.1) The implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block*/
	GLsizei uniformBlockDataSize;

	/*(3.1) The total length (including the nul terminator) of the name of the uniform block*/
	GLsizei uniformBlockNameLength;

	/*(3.1) True if the uniform block is referenced by the fragment programming stage*/
	GLboolean uniformBlockReferencedByFragmentShader;

	/*(3.1) True if the uniform block is referenced by the vertex programming stage*/
	GLboolean uniformBlockReferencedByVertexShader;

#ifdef GL_VERSION_3_2
	/*(3.2) True if the uniform block is referenced by the geometry programming stage*/
	GLboolean uniformBlockReferencedByGeometryShader;
#endif // #ifdef GL_VERSION_3_2

	/*(3.1) The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*(3.1) The null terminated string containing the name of the uniform variable*/
	GLchar name[MAX_PATH];
};
#endif // #ifdef GL_VERSION_3_1

/*OpenGL shader program object class derived from <_Object>*/
class Program : public _Object
{
private:
	friend class _Shader;
	friend class Uniform;
	friend class UniformBlock;
	friend class VertexAttrib;
	static void WINAPI _glCreateProgram(GLsizei unused, GLuint* id);
	static void WINAPI _glDeleteProgram(GLsizei unused, const GLuint* id);
	GLint _getProgram(GLenum pname);
	GLuint _program_id()
	{
		return _object_id(&_glCreateProgram);
	}

public:
	/*(1) Constructs an empty program object*/
	Program() {}

	/*(2) Constucts a program object with <shareShader>*/
	Program(Program& program)
	{
		shareProgram(program);
	}

	/*(3) Constructs program object with <attachShaders>*/
	Program(VertexShader& vs, FragmentShader& fs)
	{
		attachShaders(vs, fs);
	}

	/*Cleans up the valid program object*/
	~Program()
	{
		if (isProgram())
		{
			deleteProgram();
		}
	}

	/*(1) Attaches vertex and fragment shader objects to specified program
	@param Vertex shader object
	@param Fragment shader object*/
	void attachShaders(VertexShader& vs, FragmentShader& fs);

	/*Creates a program object that was previously empty*/
	void createProgram()
	{
		_object_gen(&_glCreateProgram);
	}

	/*Deletes the program object that was previously created*/
	void deleteProgram()
	{
		_object_delete(&_glDeleteProgram);
	}

	/*Detaches all attached shader objects from specified program*/
	void detachShaders();

	/*Returns information about a currenntly active attribute variable for the specified program object into the <ActiveAttribInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the active attribute variable to be queried, must be less than the value returned by <getActiveAttributes>
	@param [out] Pointer to the <ActiveAttribInfo> structure receiving the active attribute info*/
	void getActiveAttrib(GLuint index, _Out_ ActiveAttribInfo* info);

	/*Gets the number of active attributes program parameter. Used as a getter of <activeAttributes> property
	@return The number of currently active attribute variables for program*/
	GLuint getActiveAttributes()
	{
		return _getProgram(GL_ACTIVE_ATTRIBUTES);
	}

	/*Gets the active attribute maximum length program parameter. Returns the length of the longest active attribute name for program, including the null termination character (i.e., the size of the character buffer required to store the longest attribute name). If no active attributes exist, 0 is returned. Used as a getter of <activeAttributeMaxLength> property
	@return The length of the longest active attribute name*/
	GLsizei getActiveAttributeMaxLength()
	{
		return _getProgram(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	/*Returns information about a currenntly active uniform variable for the specified program object into the <ActiveUniformInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the active uniform variable to be queried, must be less than the value returned by <getActiveUniforms>
	@param [out] Pointer to the <ActiveUniformInfo> structure receiving the active uniform info*/
	void getActiveUniform(GLuint index, _Out_ ActiveUniformInfo* info);

	/*Gets the number of active uniforms program parameter. Used as a getter of <activeUniforms> property
	@return The number of currently active uniform variables for program*/
	GLuint getActiveUniforms()
	{
		return _getProgram(GL_ACTIVE_UNIFORMS);
	}

	/*Gets the active uniform max length program parameter. Returns the length of the longest active uniform variable name for program, including the null termination character (i.e., the size of the character buffer required to store the longest uniform variable name). If no active uniform variables exist, 0 is returned. Used as a getter of <activeUniformMaxLength> property
	@return The length of the longest currenntly active uniform variable name*/
	GLsizei getActiveUniformMaxLength()
	{
		return _getProgram(GL_ACTIVE_UNIFORM_MAX_LENGTH);
	}

	/*Gets the number of attached shaders program parameter. Used as a getter of <attachedShaders> property
	@return The number of shader objects attached to program*/
	GLint getAttachedShaders()
	{
		return _getProgram(GL_ATTACHED_SHADERS);
	}

	/*Returns a VertexAttrib object representing program vertex attribute by its name
	@param [in] Vertex attribute name
	@return Vertex attribute object*/
	VertexAttrib getAttribLocation(_In_z_ const GLchar* name);

	/*Gets the delete status program parameter. Used as a getter of <deleteStatus> property
	@return True if program is currently flagged for deletion, and false otherwise*/
	GLboolean getDeleteStatus()
	{
		return _getProgram(GL_DELETE_STATUS);
	}

	/*Gets the info log length program parameter. Returns the number of characters in the information log for program including the null termination character (i.e., the size of the character buffer required to store the information log). If program has no information log, a value of 0 is returned. Used as a getter of <infoLogLength> property
	@return Number of characters in the information log*/
	GLsizei getInfoLogLength()
	{
		return _getProgram(GL_INFO_LOG_LENGTH);
	}

	/*Gets the link status program parameter. Returns the flag if the last link operation on program was successful. Used as a getter of <linkStatus> property
	@return True if the last link operation on program was successful, and false otherwise*/
	GLboolean getLinkStatus()
	{
		return _getProgram(GL_LINK_STATUS);
	}

	/*Gets the validate status program parameter. Returns the flag if the last validation operation on program was successful. Used as a getter of <validateStatus> property
	@return True or if the last validation operation on program was successful, false otherwise*/
	GLboolean getValidateStatus()
	{
		return _getProgram(GL_VALIDATE_STATUS);
	}

	/*Returns a Uniform object representing program uniform variable by its name
	@param [in] Uniform variable name
	@return Uniform variable object*/
	Uniform getUniformLocation(_In_z_ const GLchar* name);

	/*Check if the program object is currently active. Used as a getter of <currentProgram> property
	@return True if currently active program object, false otherwise*/
	GLboolean isCurrentProgram()
	{
		return _object_id() == _getInteger(GL_CURRENT_PROGRAM);
	}

	/*Determines if a name corresponds to a program object. Used as a getter of <program> property
	@return True if valid program object, false otherwise*/
	GLboolean isProgram()
	{
		return glIsProgram(_object_id());
	}

	/*Links a program object. The status of the link operation will be stored as part of the program object's state*/
	void linkProgram();

	/*Set an empty program object as a reference to the program object from another context
	@param The program object to share, must not be empty*/
	void shareProgram(Program& program)
	{
		_object_share((_Object&)program);
	}

	/*Sets the creation state of the program object, only if current state is opposite. Depending of the flag value, calls <createProgram> or <deleteProgram> functions. Used as a setter of <program> property
	@param True to generate program object name, false to delete program object*/
	void setProgram(GLboolean gen);

	/*Installs a program object as part of current rendering state*/
	void useProgram();

	/*Validates a program object, to see whether the executables contained in program can execute given the current OpenGL state*/
	void validateProgram();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for number of active attributes program parameter*/
	__declspec(property(get = getActiveAttributes)) GLuint activeAttributes;

	/*Read-only property for length of the longest active attribute name for program, including the null termination character*/
	__declspec(property(get = getActiveAttributeMaxLength)) GLsizei activeAttributeMaxLength;

	/*Read-only property for number of active uniforms program parameter*/
	__declspec(property(get = getActiveUniforms)) GLuint activeUniforms;

	/*Read-only property for length of the longest active uniform variable name for program, including the null termination character*/
	__declspec(property(get = getActiveUniformMaxLength)) GLsizei activeUniformMaxLength;

	/*Read-only property for number of attached shaders program parameter*/
	__declspec(property(get = getAttachedShaders)) GLint attachedShaders;

	/*Read-only property to check if the program object is currently active*/
	__declspec(property(get = isCurrentProgram)) GLboolean currentProgram;

	/*Read-only property for delete status program parameter*/
	__declspec(property(get = getDeleteStatus)) GLboolean deleteStatus;

	/*Read-only property for number of characters in the information log for program including the null termination character*/
	__declspec(property(get = getInfoLogLength)) GLsizei infoLogLength;

	/*Read-only property for link status program parameter*/
	__declspec(property(get = getLinkStatus)) GLboolean linkStatus;

	/* Read-write property for creation state of the program object*/
	__declspec(property(get = isProgram, put = setProgram)) GLboolean program;

	/*Read-only property for validate status program parameter*/
	__declspec(property(get = getValidateStatus)) GLboolean validateStatus;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_0
	/*(3.0) Binds a user-defined varying out variable to a fragment shader color number prior to program linking
	@param The color number to bind the user-defined varying out variable to
	@param [in] The name of the user-defined varying out variable whose binding to modify*/
	void bindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name);

	/*(3.0) Queries the bindings of color numbers to user-defined varying out variables of the previously linked program
	@param [in] The name of the user-defined varying out variable whose binding to query*/
	ColorNumber getFragDataLocation(_In_z_ const GLchar* name);

	/*(3.0) Returns information about varying variable currently selected for transform feedback into the <ActiveAttribInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the varying variable to be queried, must be less than the value returned by <getTransformFeedbackVaryings>
	@param [out] Pointer to the <ActiveAttribInfo> structure receiving the varying variable info*/
	void getTransformFeedbackVarying(GLuint index, _Out_ ActiveAttribInfo* info);

	/*(3.0) Gets transform feedback varyings program parameter. Returns the number of varying variables to capture in transform feedback mode for the program. Used as a getter of <transformFeedbackVaryings> property
	@return The number of varying variables selected for transform feedback*/
	GLuint getTransformFeedbackVaryings()
	{
		return _getProgram(GL_TRANSFORM_FEEDBACK_VARYINGS);
	}

	/*(3.0) Gets transform feedback varying max length program parameter. Returns the length of the longest variable name to be used for transform feedback, including the null-terminator. Used as a getter of <transformFeedbackVaryingMaxLength> property
	@return The maximum transform feedback varying's length*/
	GLsizei getTransformFeedbackVaryingMaxLength()
	{
		return _getProgram(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
	}

	/*(3.0) Gets transform feedback buffer mode program parameter. Returns a symbolic constant indicating the buffer mode used when transform feedback is active. Used as a getter of <transformFeedbackBufferMode> property
	@return Transform feedback buffer mode enumerator*/
	TransformFeedbackBufferMode getTransformFeedbackBufferMode()
	{
		return (TransformFeedbackBufferMode)_getProgram(GL_TRANSFORM_FEEDBACK_BUFFER_MODE);
	}

	/*(3.0) Specifies the names of the vertex or geometry shader outputs to be recorded in transform feedback mode, must be called prior to program linking
	@param The number of varying variables used for transform feedback
	@param [in] An array of count zero-terminated strings specifying the names of the varying variables to use for transform feedback
	@param Identifies the mode used to capture the varying variables when transform feedback is active*/
	void setTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property for number of varying variables to capture in transform feedback mode for the program*/
	__declspec(property(get = getTransformFeedbackVaryings)) GLuint transformFeedbackVaryings;

	/*(3.0) Read-only property for length of the longest variable name to be used for transform feedback, including the null-terminator*/
	__declspec(property(get = getTransformFeedbackVaryingMaxLength)) GLsizei transformFeedbackVaryingMaxLength;

	/*(3.0) Read-only property for symbolic constant indicating the buffer mode used when transform feedback is active*/
	__declspec(property(get = getTransformFeedbackBufferMode)) TransformFeedbackBufferMode transformFeedbackBufferMode;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	/*(3.1) Returns information about an active uniform block into the <ActiveUniformBlockInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the uniform block to be queried, must be less than the value returned by <getActiveUniformBlocks>
	@param [out] Pointer to the <ActiveUniformBlockInfo> structure receiving the uniform block info*/
	void getActiveUniformBlock(GLuint index, _Out_ ActiveUniformBlockInfo* info);

	/*(3.1) Gets active uniform blocks program parameter. Returns the number of currently active uniform blocks for program containing active uniforms. Used as a getter of <activeUniformBlocks> property
	@return Active uniform blocks number*/
	GLuint getActiveUniformBlocks()
	{
		return _getProgram(GL_ACTIVE_UNIFORM_BLOCKS);
	}

	/*(3.1) Gets active uniform block maximum name length program parameter. Returns the length of the longest active uniform block name for program, including the null termination character (i.e., the size of the character buffer required to store the longest uniform block name). If no active uniform blocks exist, the value is zero. Used as a getter of <activeUniformBlockMaxNameLength> property
	@return Active uniform block max name length*/
	GLsizei getActiveUniformBlockMaxNameLength()
	{
		return _getProgram(GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH);
	}

	/*(3.1) Returns the name of an active uniform block for the specified program object into the <ActiveUniformBlockInfo> structure, setting only its <name> and <length> fields. The function is used in monitoring purposes
	@param Specifies the index of the currently active uniform block to be queried, must be less than the value returned by <getActiveUniformBlocks>
	@param [out] Pointer to the <ActiveUniformBlockInfo> structure receiving the currently active uniform block info*/
	void getActiveUniformBlockName(GLuint index, _Out_ ActiveUniformBlockInfo* info);

	/*(3.1) Returns the name of an active uniform variable for the specified program object into the <ActiveUniformInfo> structure, setting only its <name> and <length> fields. The function is used in monitoring purposes
	@param Specifies the index of the currently active uniform variable to be queried, must be less than the value returned by <getActiveUniforms>
	@param [out] Pointer to the <ActiveUniformInfo> structure receiving the currently active uniform info*/
	void getActiveUniformName(GLuint index, _Out_ ActiveUniformInfo* info);

	/*(3.1) Gets the maximum number of uniform blocks per program. The value must be at least 70
	@return The maximum combined uniform blocks*/
	static GLuint getMaxCombinedUniformBlocks()
	{
		return _getInteger(GL_MAX_COMBINED_UNIFORM_BLOCKS);
	}

	/*(3.1) Returns a UniformBlock object representing program uniform block by its name
	@param [in] Uniform block name
	@return Uniform block object*/
	UniformBlock getUniformBlockIndex(_In_z_ const GLchar* name);

	/*(3.1) Retrieves the indices of a number of uniforms within program object
	@param Specifies the number of uniforms whose indices to query
	@param [in] Specifies the address of an array of pointers to buffers containing the names of the queried uniforms
	@param [out] Specifies the address of an array that will receive the indices of the uniforms*/
	void getUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-only property for active uniform blocks program parameter*/
	__declspec(property(get = getActiveUniformBlocks)) GLuint activeUniformBlocks;

	/*(3.1) Read-only property for length of the longest active uniform block name for program, including the null termination character*/
	__declspec(property(get = getActiveUniformBlockMaxNameLength)) GLsizei activeUniformBlockMaxNameLength;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) (4) Constructs program object with <attachShaders>*/
	Program(VertexShader& vs, GeometryShader& gs, FragmentShader& fs)
	{
		attachShaders(vs, gs, fs);
	}

	/*(3.2) (2) Attaches vertex, geometry and fragment shader objects to specified program
	@param Vertex shader object
	@param Geometry shader object
	@param Fragment shader object*/
	void attachShaders(VertexShader& vs, GeometryShader& gs, FragmentShader& fs);

	/*(3.2) Gets geometry input type parameter value. Returns a symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program. Used as a getter of <geometryInputType> property
	@return Primitive type enumerator*/
	PrimitiveMode getGeometryInputType()
	{
		return (PrimitiveMode)_getProgram(GL_GEOMETRY_INPUT_TYPE);
	}

	/*(3.2) Gets geometry output type parameter value. Returns a symbolic constant indicating the primitive type that will be output by the geometry shader contained in program. Used as a getter of <geometryOutputType> property
	@return Primitive type enumerator*/
	PrimitiveMode getGeometryOutputType()
	{
		return (PrimitiveMode)_getProgram(GL_GEOMETRY_OUTPUT_TYPE);
	}

	/*(3.2) Gets geometry vertices out parameter value. Returns the maximum number of vertices that the geometry shader in program will output. Used as a getter of <geometryVerticesOut> property
	@return Geometry vertices maximum output number*/
	GLint getGeometryVerticesOut()
	{
		return _getProgram(GL_GEOMETRY_VERTICES_OUT);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property for symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program*/
	__declspec(property(get = getGeometryInputType)) PrimitiveMode geometryInputType;

	/*(3.2) Read-only property for symbolic constant indicating the primitive type that will be output by the geometry shader contained in program*/
	__declspec(property(get = getGeometryOutputType)) PrimitiveMode geometryOutputType;

	/*(3.2) Read-only property for maximum number of vertices that the geometry shader in program will output*/
	__declspec(property(get = getGeometryVerticesOut)) GLint geometryVerticesOut;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_2

#ifdef GL_VERSION_3_3
	/*(3.3) Binds a user-defined varying out variable to a fragment shader color number and index prior to program linking
	@param The color number to bind the user-defined varying out variable to
	@param The index of the color input to bind the user-defined varying out variable to
	@param [in] The name of the user-defined varying out variable whose binding to modify*/
	void bindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name);

	/*(3.3) Returns the index of the fragment color to which the user-defined varying out variable was bound when the program was linked
	@param [in] The name of the user-defined varying out variable whose index to query*/
	GLint getFragDataIndex(_In_z_ const GLchar* name);
#endif // #ifdef GL_VERSION_3_3
}; // class Program
} // namespace gl

#include <yaglpp/glad/uniform.h>
#include <yaglpp/glad/uniform_block.h>
#include <yaglpp/glad/vertex_attrib.h>
#include <yaglpp/shader/vertex_shader.h>
#include <yaglpp/shader/fragment_shader.h>
#include <yaglpp/shader/geometry_shader.h>
namespace gl {
inline void Program::attachShaders(VertexShader& vs, FragmentShader& fs)
{
	vs.attachShader(*this);
	fs.attachShader(*this);
}

inline VertexAttrib Program::getAttribLocation(_In_z_ const GLchar* name)
{
	return VertexAttrib(*this, name);
}

inline Uniform Program::getUniformLocation(_In_z_ const GLchar* name)
{
	return Uniform(*this, name);
}

#ifdef YAGLPP_IMPLEMENTATION
void Program::detachShaders()
{
	GLint iCount; GLuint uId = _program_id();
	glGetProgramiv(uId, GL_ATTACHED_SHADERS, &iCount);
	if (iCount)
	{
		GLuint* pShaders = (GLuint*)YAGLPP_MALLOC(iCount * sizeof(GLuint));
		glGetAttachedShaders(uId, iCount, &iCount, pShaders);
		for (GLint i = 0; i < iCount; i++)
		{
			glDetachShader(uId, pShaders[i]);
		}
		YAGLPP_FREE(pShaders);
	}
	YAGLPP_GLAD_ERROR;
}

void Program::setProgram(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			_object_delete(&_glDeleteProgram);
		}
	}
	else if (gen == GL_TRUE)
	{
		_object_gen(&_glCreateProgram);
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint Program::_getProgram(GLenum pname)
{
	GLint iResult;
	glGetProgramiv(_program_id(), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void WINAPI Program::_glCreateProgram(GLsizei unused, GLuint* id)
{
	*id = glCreateProgram();
	YAGLPP_GLAD_ERROR;
}

void WINAPI Program::_glDeleteProgram(GLsizei unused, const GLuint* id)
{
	glDeleteProgram(*id);
	YAGLPP_GLAD_ERROR;
}

void Program::getActiveAttrib(GLuint index, _Out_ ActiveAttribInfo* info)
{
	YAGLPP_ASSERT(index < getActiveAttributes()); // THE OPENGL ACTIVE ATTRIBUTE INDEX IS INVALID
	glGetActiveAttrib(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::getActiveUniform(GLuint index, _Out_ ActiveUniformInfo* info)
{
	YAGLPP_ASSERT(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniform(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::linkProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glLinkProgram(uId);
	glGetProgramiv(uId, GL_LINK_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)YAGLPP_MALLOC(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> LINK ERROR:" << std::endl << pBuffer << std::endl;
		YAGLPP_FREE(pBuffer);
		YAGLPP_ASSERT(false); // PROGRAM LINKING FAILED
}
	YAGLPP_GLAD_ERROR;
}

void Program::useProgram()
{
	glUseProgram(_program_id());
	YAGLPP_GLAD_ERROR;
}

void Program::validateProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glValidateProgram(uId);
	glGetProgramiv(uId, GL_VALIDATE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)YAGLPP_MALLOC(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> VALIDATION ERROR:" << std::endl << pBuffer << std::endl;
		YAGLPP_FREE(pBuffer);
		YAGLPP_ASSERT(false); // PROGRAM VALIDATION FAILED
	}
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint Program::_getProgram(GLenum pname)
{
	GLint i; glGetProgramiv(_program_id(), pname, &i); return i;
}

inline void WINAPI Program::_glCreateProgram(GLsizei unused, GLuint* id)
{
	*id = glCreateProgram();
}

inline void WINAPI Program::_glDeleteProgram(GLsizei unused, const GLuint* id)
{
	glDeleteProgram(*id);
}

inline void Program::getActiveAttrib(GLuint index, _Out_ ActiveAttribInfo* info)
{
	glGetActiveAttrib(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::getActiveUniform(GLuint index, _Out_ ActiveUniformInfo* info)
{
	glGetActiveUniform(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::linkProgram()
{
	glLinkProgram(_program_id());
}

inline void Program::useProgram()
{
	glUseProgram(_program_id());
}

inline void Program::validateProgram()
{
	glValidateProgram(_program_id());
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (GL_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::bindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(_program_id(), (GLuint)colorNumber, name);
	YAGLPP_GLAD_ERROR;
}

ColorNumber Program::getFragDataLocation(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataLocation(_program_id(), name);
	YAGLPP_GLAD_ERROR;
	return (ColorNumber)iData;
}

void Program::getTransformFeedbackVarying(GLuint index, _Out_ ActiveAttribInfo* info)
{
	YAGLPP_ASSERT(index < getTransformFeedbackVaryings()); // THE OPENGL VARYING VARIABLE INDEX IS INVALID
	glGetTransformFeedbackVarying(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::setTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(_program_id(), count, varyings, (GLenum)bufferMode);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (GL_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (GL_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Program::bindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(_program_id(), (GLuint)colorNumber, name);
}

inline ColorNumber Program::getFragDataLocation(_In_z_ const GLchar* name)
{
	return (ColorNumber)glGetFragDataLocation(_program_id(), name);;
}

void Program::getTransformFeedbackVarying(GLuint index, _Out_ ActiveAttribInfo* info)
{
	glGetTransformFeedbackVarying(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::setTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(_program_id(), count, varyings, (GLenum)bufferMode);
}
#endif // #if defined (GL_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef GL_VERSION_3_1
inline UniformBlock Program::getUniformBlockIndex(_In_z_ const GLchar* name)
{
	return UniformBlock(*this, name);
}
#endif // #ifdef GL_VERSION_3_1

#if defined (GL_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)
void Program::getActiveUniformBlock(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	GLuint uId = _program_id();
	YAGLPP_ASSERT(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &info->uniformBlockActiveUniforms);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_BINDING, (GLint*)&info->uniformBlockBinding);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_DATA_SIZE, &info->uniformBlockDataSize);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_NAME_LENGTH, &info->uniformBlockNameLength);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, (GLint*)&info->uniformBlockReferencedByFragmentShader);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, (GLint*)&info->uniformBlockReferencedByVertexShader);
	glGetActiveUniformBlockName(uId, index, MAX_PATH, &info->length, info->name);

#if defined GL_VERSION_3_2
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, (GLint*)&info->uniformBlockReferencedByGeometryShader);
#endif // #if defined GL_VERSION_3_2
}
#endif // #if defined (GL_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)

#if defined (GL_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::getActiveUniformBlockName(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	YAGLPP_ASSERT(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	glGetActiveUniformBlockName(_program_id(), index, MAX_PATH, &info->length, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::getActiveUniformName(GLuint index, _Out_ ActiveUniformInfo* info)
{
	YAGLPP_ASSERT(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniformName(_program_id(), index, MAX_PATH, &info->length, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::getUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(_program_id(), uniformCount, uniformNames, uniformIndices);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (GL_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (GL_VERSION_3_1) && defined (YAGLPP_INLINEG_IMPLEMENTATION)
inline void Program::getActiveUniformBlockName(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	glGetActiveUniformBlockName(_program_id(), index, MAX_PATH, &info->length, info->name);
}

inline void Program::getActiveUniformName(GLuint index, _Out_ ActiveUniformInfo* info)
{
	glGetActiveUniformName(_program_id(), index, MAX_PATH, &info->length, info->name);
}

inline void Program::getUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(_program_id(), uniformCount, uniformNames, uniformIndices);
}
#endif // #if defined (GL_VERSION_3_1) && defined (YAGLPP_INLINEG_IMPLEMENTATION)

#ifdef GL_VERSION_3_2
inline void Program::attachShaders(VertexShader& vs, GeometryShader& gs, FragmentShader& fs)
{
	vs.attachShader(*this);
	gs.attachShader(*this);
	fs.attachShader(*this);
}
#endif // #ifdef GL_VERSION_3_2

#if defined (GL_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::bindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(_program_id(), colorNumber, index, name);
	YAGLPP_GLAD_ERROR;
}

GLint Program::getFragDataIndex(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataIndex(_program_id(), name);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined (GL_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (GL_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Program::bindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(_program_id(), colorNumber, index, name);
}

inline GLint Program::getFragDataIndex(_In_z_ const GLchar* name)
{
	return glGetFragDataIndex(_program_id(), name);
}
#endif // #if defined (GL_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
