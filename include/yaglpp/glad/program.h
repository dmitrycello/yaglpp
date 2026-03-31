#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_PROGRAM_H
#define YAGLPP_PROGRAM_H

namespace gl {
/*OpenGL shader program object class derived from <Objects>*/
class Program : public Objects
{
public:
	using Objects::Objects;
	struct AttribInfo;
	struct UniformInfo;
	enum class AttribType : GLenum;
	enum class UniformType : GLenum;
	/*(1) Constructs default program object*/
	Program() : Objects() {}

	/*(2) Constructs program object with <AttachShaders>*/
	Program(VertexShader& vs, FragmentShader& fs);

	/*(1) Attaches vertex and fragment shader objects to specified program, link the program, and then discard shader objects in one function call
	@param Vertex shader object discarded after program linking
	@param Fragment shader object discarded after program linking*/
	void AttachShaders(VertexShader& vs, FragmentShader& fs);

	/*Creates OpenGL program object name in an empty class object*/
	void Create()
	{
		object_gen(gl_create_program);
	}

	/*Deletes valid OpenGL program object name and sets the program class object in empty state*/
	void Delete()
	{
		object_delete(gl_delete_program);
	}

	/*Detaches all attached shader objects from specified program*/
	void DetachShaders();

	/*Returns information about a currenntly active attribute variable for the specified program object into the <AttribInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the active attribute variable to be queried, must be less than the value returned by <GetActiveAttributes>
	@param [out] Pointer to the <AttribInfo> structure receiving the active attribute info*/
	void GetActiveAttrib(GLuint index, _Out_ AttribInfo* info);

	/*Gets the number of active attributes program parameter. MSVC getter for <activeAttributes> property
	@return The number of currently active attribute variables for program*/
	GLuint GetActiveAttributes()
	{
		return get_program(GL_ACTIVE_ATTRIBUTES);
	}

	/*Gets the active attribute maximum length program parameter. Returns the length of the longest active attribute name for program, including the null termination character (i.e., the size of the character buffer required to store the longest attribute name). If no active attributes exist, 0 is returned. MSVC getter for <activeAttributeMaxLength> property
	@return The length of the longest active attribute name*/
	GLsizei GetActiveAttributeMaxLength()
	{
		return get_program(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	/*Returns information about a currenntly active uniform variable for the specified program object into the <UniformInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the active uniform variable to be queried, must be less than the value returned by <GetActiveUniforms>
	@param [out] Pointer to the <UniformInfo> structure receiving the active uniform info*/
	void GetActiveUniform(GLuint index, _Out_ UniformInfo* info);

	/*Gets the number of active uniforms program parameter. MSVC getter for <activeUniforms> property
	@return The number of currently active uniform variables for program*/
	GLuint GetActiveUniforms()
	{
		return get_program(GL_ACTIVE_UNIFORMS);
	}

	/*Gets the active uniform max length program parameter. Returns the length of the longest active uniform variable name for program, including the null termination character (i.e., the size of the character buffer required to store the longest uniform variable name). If no active uniform variables exist, 0 is returned. MSVC getter for <activeUniformMaxLength> property
	@return The length of the longest currenntly active uniform variable name*/
	GLsizei GetActiveUniformMaxLength()
	{
		return get_program(GL_ACTIVE_UNIFORM_MAX_LENGTH);
	}

	/*Gets the number of attached shaders program parameter. MSVC getter for <attachedShaders> property
	@return The number of shader objects attached to program*/
	GLint GetAttachedShaders()
	{
		return get_program(GL_ATTACHED_SHADERS);
	}

	/*Returns a VertexAttrib object representing program vertex attribute by its name
	@param [in] Vertex attribute name
	@return Vertex attribute object*/
	VertexAttrib GetVertexAttrib(_In_z_ const GLchar* name);

	/*Returns a reference program object that is currently active
	@return The reference program object, or empty object*/
	static Program GetCurrent()
	{
		return Program(yaglpp_glad_integer(GL_CURRENT_PROGRAM));
	}

	/*Gets the delete status program parameter. MSVC getter for <deleteStatus> property
	@return True if program is currently flagged for deletion, and false otherwise*/
	GLboolean GetDeleteStatus()
	{
		return get_program(GL_DELETE_STATUS);
	}

	/*Gets the info log length program parameter. Returns the number of characters in the information log for program including the null termination character (i.e., the size of the character buffer required to store the information log). If program has no information log, a value of 0 is returned. MSVC getter for <infoLogLength> property
	@return Number of characters in the information log*/
	GLsizei GetInfoLogLength()
	{
		return get_program(GL_INFO_LOG_LENGTH);
	}

	/*Gets the link status program parameter. Returns the flag if the last link operation on program was successful. MSVC getter for <linkStatus> property
	@return True if the last link operation on program was successful, and false otherwise*/
	GLboolean GetLinkStatus()
	{
		return get_program(GL_LINK_STATUS);
	}

	/*Gets the validate status program parameter. Returns the flag if the last validation operation on program was successful. MSVC getter for <validateStatus> property
	@return True or if the last validation operation on program was successful, false otherwise*/
	GLboolean GetValidateStatus()
	{
		return get_program(GL_VALIDATE_STATUS);
	}

	/*Returns a Uniform object representing program uniform variable by its name
	@param [in] Uniform variable name
	@return Uniform variable object*/
	Uniform GetUniform(_In_z_ const GLchar* name);

	/*Check if the program object is currently active. MSVC getter for <current> property
	@return True if currently active program object, false otherwise*/
	GLboolean IsCurrent() const
	{
		return object_binding(GL_CURRENT_PROGRAM, Get());
	}

	/*Determines if a name corresponds to a program object. MSVC getter for <program> property
	@return True if valid program object, false otherwise*/
	GLboolean IsProgram() const
	{
		return object_is(glIsProgram);
	}

	/*Links a program object. The status of the link operation will be stored as part of the program object's state*/
	void Link();

	/*Installs a program object as part of current rendering state*/
	void Use();

	/*Validates a program object, to see whether the executables contained in program can execute given the current OpenGL state*/
	void Validate();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for number of active attributes program parameter*/
	__declspec(property(get = GetActiveAttributes)) GLuint activeAttributes;

	/*Read-only property for length of the longest active attribute name for program, including the null termination character*/
	__declspec(property(get = GetActiveAttributeMaxLength)) GLsizei activeAttributeMaxLength;

	/*Read-only property for number of active uniforms program parameter*/
	__declspec(property(get = GetActiveUniforms)) GLuint activeUniforms;

	/*Read-only property for length of the longest active uniform variable name for program, including the null termination character*/
	__declspec(property(get = GetActiveUniformMaxLength)) GLsizei activeUniformMaxLength;

	/*Read-only property for number of attached shaders program parameter*/
	__declspec(property(get = GetAttachedShaders)) GLint attachedShaders;

	/*Read-only property to check if the program object is currently active*/
	__declspec(property(get = IsCurrent)) GLboolean current;

	/*Read-only property for delete status program parameter*/
	__declspec(property(get = GetDeleteStatus)) GLboolean deleteStatus;

	/*Read-only property for number of characters in the information log for program including the null termination character*/
	__declspec(property(get = GetInfoLogLength)) GLsizei infoLogLength;

	/*Read-only property for link status program parameter*/
	__declspec(property(get = GetLinkStatus)) GLboolean linkStatus;

	/*Read-only property to check if active program object*/
	__declspec(property(get = IsProgram)) GLboolean program;

	/*Read-only property for validate status program parameter*/
	__declspec(property(get = GetValidateStatus)) GLboolean validateStatus;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Binds a user-defined varying out variable to a fragment shader color number prior to program linking
	@param The color number to bind the user-defined varying out variable to
	@param [in] The name of the user-defined varying out variable whose binding to modify*/
	void BindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name);

	/*(3.0) Queries the bindings of color numbers to user-defined varying out variables of the previously linked program
	@param [in] The name of the user-defined varying out variable whose binding to query*/
	ColorNumber GetFragDataLocation(_In_z_ const GLchar* name);

	/*(3.0) Returns information about varying variable currently selected for transform feedback into the <AttribInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the varying variable to be queried, must be less than the value returned by <GetTransformFeedbackVaryings>
	@param [out] Pointer to the <AttribInfo> structure receiving the varying variable info*/
	void GetTransformFeedbackVarying(GLuint index, _Out_ AttribInfo* info);

	/*(3.0) Gets transform feedback varyings program parameter. Returns the number of varying variables to capture in transform feedback mode for the program. MSVC getter for <transformFeedbackVaryings> property
	@return The number of varying variables selected for transform feedback*/
	GLuint GetTransformFeedbackVaryings()
	{
		return get_program(GL_TRANSFORM_FEEDBACK_VARYINGS);
	}

	/*(3.0) Gets transform feedback varying max length program parameter. Returns the length of the longest variable name to be used for transform feedback, including the null-terminator. MSVC getter for <transformFeedbackVaryingMaxLength> property
	@return The maximum transform feedback varying's length*/
	GLsizei GetTransformFeedbackVaryingMaxLength()
	{
		return get_program(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
	}

	/*(3.0) Gets transform feedback buffer mode program parameter. Returns a symbolic constant indicating the buffer mode used when transform feedback is active. MSVC getter for <transformFeedbackBufferMode> property
	@return Transform feedback buffer mode enumerator*/
	TransformFeedbackBufferMode GetTransformFeedbackBufferMode()
	{
		return (TransformFeedbackBufferMode)get_program(GL_TRANSFORM_FEEDBACK_BUFFER_MODE);
	}

	/*(3.0) Specifies the names of the vertex or geometry shader outputs to be recorded in transform feedback mode, must be called prior to program linking
	@param The number of varying variables used for transform feedback
	@param [in] An array of count zero-terminated strings specifying the names of the varying variables to use for transform feedback
	@param Identifies the mode used to capture the varying variables when transform feedback is active*/
	void SetTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode);
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.0) Read-only property for number of varying variables to capture in transform feedback mode for the program*/
	__declspec(property(get = GetTransformFeedbackVaryings)) GLuint transformFeedbackVaryings;

	/*(3.0) Read-only property for length of the longest variable name to be used for transform feedback, including the null-terminator*/
	__declspec(property(get = GetTransformFeedbackVaryingMaxLength)) GLsizei transformFeedbackVaryingMaxLength;

	/*(3.0) Read-only property for symbolic constant indicating the buffer mode used when transform feedback is active*/
	__declspec(property(get = GetTransformFeedbackBufferMode)) TransformFeedbackBufferMode transformFeedbackBufferMode;
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_1
	struct UniformBlockInfo;
	/*(3.1) Returns information about an active uniform block into the <UniformBlockInfo> structure. The function is used in monitoring purposes
	@param Specifies the index of the uniform block to be queried, must be less than the value returned by <GetActiveUniformBlocks>
	@param [out] Pointer to the <UniformBlockInfo> structure receiving the uniform block info*/
	void GetActiveUniformBlock(GLuint index, _Out_ UniformBlockInfo* info);

	/*(3.1) Gets active uniform blocks program parameter. Returns the number of currently active uniform blocks for program containing active uniforms. MSVC getter for <activeUniformBlocks> property
	@return Active uniform blocks number*/
	GLuint GetActiveUniformBlocks()
	{
		return get_program(GL_ACTIVE_UNIFORM_BLOCKS);
	}

	/*(3.1) Gets active uniform block maximum name length program parameter. Returns the length of the longest active uniform block name for program, including the null termination character (i.e., the size of the character buffer required to store the longest uniform block name). If no active uniform blocks exist, the value is zero. MSVC getter for <activeUniformBlockMaxNameLength> property
	@return Active uniform block max name length*/
	GLsizei GetActiveUniformBlockMaxNameLength()
	{
		return get_program(GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH);
	}

	/*(3.1) Returns the name of an active uniform block for the specified program object into the <UniformBlockInfo> structure, setting only its <name> and <length> fields. The function is used in monitoring purposes
	@param Specifies the index of the currently active uniform block to be queried, must be less than the value returned by <GetActiveUniformBlocks>
	@param [out] Pointer to the <UniformBlockInfo> structure receiving the currently active uniform block info*/
	void GetActiveUniformBlockName(GLuint index, _Out_ UniformBlockInfo* info);

	/*(3.1) Returns the name of an active uniform variable for the specified program object into the <UniformInfo> structure, setting only its <name> and <length> fields. The function is used in monitoring purposes
	@param Specifies the index of the currently active uniform variable to be queried, must be less than the value returned by <GetActiveUniforms>
	@param [out] Pointer to the <UniformInfo> structure receiving the currently active uniform info*/
	void GetActiveUniformName(GLuint index, _Out_ UniformInfo* info);

	/*(3.1) Returns a UniformBlock object representing program uniform block by its name
	@param [out] The destination uniform block object
	@param [in] Uniform block name
	@return Uniform block object*/
	void GetUniformBlock(UniformBlock& uniformBlock, _In_z_ const GLchar* name);

	/*(3.1) Retrieves the indices of a number of uniforms within program object
	@param Specifies the number of uniforms whose indices to query
	@param [in] Specifies the address of an array of pointers to buffers containing the names of the queried uniforms
	@param [out] Specifies the address of an array that will receive the indices of the uniforms*/
	void GetUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices);
#endif // #ifdef YAGLPP_VERSION_3_1

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.1) Read-only property for active uniform blocks program parameter*/
	__declspec(property(get = GetActiveUniformBlocks)) GLuint activeUniformBlocks;

	/*(3.1) Read-only property for length of the longest active uniform block name for program, including the null termination character*/
	__declspec(property(get = GetActiveUniformBlockMaxNameLength)) GLsizei activeUniformBlockMaxNameLength;
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) (4) Constructs program object with <AttachShaders>*/
	Program(VertexShader& vs, GeometryShader& gs, FragmentShader& fs);

	/*(3.2) (2) Attaches vertex, geometry and fragment shader objects to specified program, link the program, and then discard shader objects in one function call
	@param Vertex shader object discarded after program linking
	@param Geometry shader object discarded after program linking
	@param Fragment shader object discarded after program linking*/
	void AttachShaders(VertexShader& vs, GeometryShader& gs, FragmentShader& fs);

	/*(3.2) Gets geometry input type parameter value. Returns a symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program. MSVC getter for <geometryInputType> property
	@return Primitive type enumerator*/
	PrimitiveMode GetGeometryInputType()
	{
		return (PrimitiveMode)get_program(GL_GEOMETRY_INPUT_TYPE);
	}

	/*(3.2) Gets geometry output type parameter value. Returns a symbolic constant indicating the primitive type that will be output by the geometry shader contained in program. MSVC getter for <geometryOutputType> property
	@return Primitive type enumerator*/
	PrimitiveMode GetGeometryOutputType()
	{
		return (PrimitiveMode)get_program(GL_GEOMETRY_OUTPUT_TYPE);
	}

	/*(3.2) Gets geometry vertices out parameter value. Returns the maximum number of vertices that the geometry shader in program will output. MSVC getter for <geometryVerticesOut> property
	@return Geometry vertices maximum output number*/
	GLint GetGeometryVerticesOut()
	{
		return get_program(GL_GEOMETRY_VERTICES_OUT);
	}
#endif // #ifdef YAGLPP_VERSION_3_2

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.2) Read-only property for symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program*/
	__declspec(property(get = GetGeometryInputType)) PrimitiveMode geometryInputType;

	/*(3.2) Read-only property for symbolic constant indicating the primitive type that will be output by the geometry shader contained in program*/
	__declspec(property(get = GetGeometryOutputType)) PrimitiveMode geometryOutputType;

	/*(3.2) Read-only property for maximum number of vertices that the geometry shader in program will output*/
	__declspec(property(get = GetGeometryVerticesOut)) GLint geometryVerticesOut;
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Binds a user-defined varying out variable to a fragment shader color number and index prior to program linking
	@param The color number to bind the user-defined varying out variable to
	@param The index of the color input to bind the user-defined varying out variable to
	@param [in] The name of the user-defined varying out variable whose binding to modify*/
	void BindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name);

	/*(3.3) Returns the index of the fragment color to which the user-defined varying out variable was bound when the program was linked
	@param [in] The name of the user-defined varying out variable whose index to query*/
	GLint GetFragDataIndex(_In_z_ const GLchar* name);
#endif // #ifdef YAGLPP_VERSION_3_3

protected:
	GLint get_program(GLenum pname);
	static void APIENTRY gl_create_program(GLsizei unused, GLuint* id);
	static void APIENTRY gl_delete_program(GLsizei unused, const GLuint* id);
}; // class Program : public Object

/*GLAD program active attribute info structure used by <GetActiveAttrib>*/
struct Program::AttribInfo
{
	/*The size of the attribute variable*/
	GLint size;

	/*The data type of the attribute variable*/
	AttribType type;

	/*The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*The null terminated string containing the name of the uniform variable*/
	GLchar name[FILENAME_MAX];
};

/*GLAD program active attribute type enumerator*/
enum class Program::AttribType : GLenum
{
	/*Attribute of float type*/
	Float = GL_FLOAT,

	/*Attribute of vec2 type*/
	FloatVec2 = GL_FLOAT_VEC2,

	/*Attribute of vec3 type*/
	FloatVec3 = GL_FLOAT_VEC3,

	/*Attribute of vec4 type*/
	FloatVec4 = GL_FLOAT_VEC4,

	/*Attribute of mat2 type*/
	FloatMat2 = GL_FLOAT_MAT2,

	/*Attribute of mat3 type*/
	FloatMat3 = GL_FLOAT_MAT3,

	/*Attribute of mat4 type*/
	FloatMat4 = GL_FLOAT_MAT4,

	/*Attribute of double type*/
	Double = GL_DOUBLE,

	/*Attribute of int type*/
	Int = GL_INT,

	/*Attribute of ivec2 type*/
	IntVec2 = GL_INT_VEC2,

	/*Attribute of ivec3 type*/
	IntVec3 = GL_INT_VEC3,

	/*Attribute of ivec4 type*/
	IntVec4 = GL_INT_VEC4,

	/*Attribute of uint type*/
	UnsignedInt = GL_UNSIGNED_INT,

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) Attribute of mat2x3 type*/
	FloatMat2x3 = GL_FLOAT_MAT2x3,

	/*(2.1) Attribute of mat2x4 type*/
	FloatMat2x4 = GL_FLOAT_MAT2x4,

	/*(2.1) Attribute of mat3x2 type*/
	FloatMat3x2 = GL_FLOAT_MAT3x2,

	/*(2.1) Attribute of mat4x3 type*/
	FloatMat3x4 = GL_FLOAT_MAT3x4,

	/*(2.1) Attribute of mat4x2 type*/
	FloatMat4x2 = GL_FLOAT_MAT4x2,

	/*(2.1) Attribute of mat4x3 type*/
	FloatMat4x3 = GL_FLOAT_MAT4x3,
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Attribute of uvec2 type*/
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,

	/*(3.0) Attribute of uvec3 type*/
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,

	/*(3.0) Attribute of uvec4 type*/
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD program active uniform info structure used by <GetActiveUniform>*/
struct Program::UniformInfo
{
	/*The size of the uniform variable*/
	GLint size;

	/*The data type of the uniform variable*/
	UniformType type;

	/*The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*The null terminated string containing the name of the uniform variable*/
	GLchar name[FILENAME_MAX];
};

/*GLAD program active uniform type enumerator*/
enum class Program::UniformType : GLenum
{
	/*Uniform of float type*/
	Float = GL_FLOAT,

	/*Uniform of vec2 type*/
	FloatVec2 = GL_FLOAT_VEC2,

	/*Uniform of vec3 type*/
	FloatVec3 = GL_FLOAT_VEC3,

	/*Uniform of vec4 type*/
	FloatVec4 = GL_FLOAT_VEC4,

	/*Uniform of double type*/
	Double = GL_DOUBLE,

	/*Uniform of int type*/
	Int = GL_INT,

	/*Uniform of ivec2 type*/
	IntVec2 = GL_INT_VEC2,

	/*Uniform of ivec3 type*/
	IntVec3 = GL_INT_VEC3,

	/*Uniform of ivec4 type*/
	IntVec4 = GL_INT_VEC4,

	/*Uniform of uint type*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Uniform of bool type*/
	Bool = GL_BOOL,

	/*Uniform of bvec2 type*/
	BoolVec2 = GL_BOOL_VEC2,

	/*Uniform of bvec3 type*/
	BoolVec3 = GL_BOOL_VEC3,

	/*Uniform of bvec4 type*/
	BoolVec4 = GL_BOOL_VEC4,

	/*Uniform of mat2 type*/
	FloatMat2 = GL_FLOAT_MAT2,

	/*Uniform of mat3 type*/
	FloatMat3 = GL_FLOAT_MAT3,

	/*Uniform of mat4 type*/
	FloatMat4 = GL_FLOAT_MAT4,

	/*Uniform of sampler 1D type*/
	Sampler1D = GL_SAMPLER_1D,

	/*Uniform of sampler 2D type*/
	Sampler2D = GL_SAMPLER_2D,

	/*Uniform of sampler 3D type*/
	Sampler3D = GL_SAMPLER_3D,

	/*Uniform of sampler cube type*/
	SamplerCube = GL_SAMPLER_CUBE,

	/*Uniform of sampler 1D shadow type*/
	Sampler1DShadow = GL_SAMPLER_1D_SHADOW,

	/*Uniform of sampler 2D shadow type*/
	Sampler2DShadow = GL_SAMPLER_2D_SHADOW,

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) Uniform of mat2x3 type*/
	FloatMat2x3 = GL_FLOAT_MAT2x3,

	/*(2.1) Uniform of mat2x4 type*/
	FloatMat2x4 = GL_FLOAT_MAT2x4,

	/*(2.1) Uniform of mat3x2 type*/
	FloatMat3x2 = GL_FLOAT_MAT3x2,

	/*(2.1) Uniform of mat3x4 type*/
	FloatMat3x4 = GL_FLOAT_MAT3x4,

	/*(2.1) Uniform of mat4x2 type*/
	FloatMat4x2 = GL_FLOAT_MAT4x2,

	/*(2.1) Uniform of mat4x3 type*/
	FloatMat4x3 = GL_FLOAT_MAT4x3,
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Uniform of uvec2 type*/
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,

	/*(3.0) Uniform of uvec3 type*/
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,

	/*(3.0) Uniform of uvec4 type*/
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,

	/*(3.0) Uniform of sampler 1D array type*/
	Sampler1DArray = GL_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of sampler 2D array type*/
	Sampler2DArray = GL_SAMPLER_2D_ARRAY,

	/*(3.0) Uniform of sampler 1D array shadow type*/
	Sampler1DArrayShadow = GL_SAMPLER_1D_ARRAY_SHADOW,

	/*(3.0) Uniform of sampler 2D array shadow type*/
	Sampler2DArrayShadow = GL_SAMPLER_2D_ARRAY_SHADOW,

	/*(3.0) Uniform of sampler cube shadow type*/
	SamplerCubeShadow = GL_SAMPLER_CUBE_SHADOW,

	/*(3.0) Uniform of isampler 1D type*/
	IntSampler1D = GL_INT_SAMPLER_1D,

	/*(3.0) Uniform of isampler 2D type*/
	IntSampler2D = GL_INT_SAMPLER_2D,

	/*(3.0) Uniform of isampler3D type*/
	IntSampler3D = GL_INT_SAMPLER_3D,

	/*(3.0) Uniform of isampler cube type*/
	IntSamplerCube = GL_INT_SAMPLER_CUBE,

	/*(3.0) Uniform of  isampler 1D array type*/
	IntSampler1DArray = GL_INT_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of isampler 2D array type*/
	IntSampler2DArray = GL_INT_SAMPLER_2D_ARRAY,

	/*(3.0) Uniform of usampler 1D type*/
	UnsignedIntSampler1D = GL_UNSIGNED_INT_SAMPLER_1D,

	/*(3.0) Uniform of usampler 2D type*/
	UnsignedIntSampler2D = GL_UNSIGNED_INT_SAMPLER_2D,

	/*(3.0) Uniform of usampler 3D type*/
	UnsignedIntSampler3D = GL_UNSIGNED_INT_SAMPLER_3D,

	/*(3.0) Uniform of usampler cube type*/
	UnsignedIntSamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,

	/*(3.0) Uniform of usampler 1D array type*/
	UnsignedIntSampler1DArray = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of usampler 2D array type*/
	UnsignedIntSampler2DArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) Uniform of sampler buffer type*/
	SamplerBuffer = GL_SAMPLER_BUFFER,

	/*(3.1) Uniform of sampler 2D rectangle type*/
	Sampler2DRect = GL_SAMPLER_2D_RECT,

	/*(3.1) Uniform of sampler 2D rectangle shadow type*/
	Sampler2DRectShadow = GL_SAMPLER_2D_RECT_SHADOW,

	/*(3.1) Uniform of isampler 2D rectangle type*/
	IntSampler2DRect = GL_INT_SAMPLER_2D_RECT,

	/*(3.1) Uniform of isampler buffer type*/
	IntSamplerBuffer = GL_INT_SAMPLER_BUFFER,

	/*(3.1) Uniform of usampler 2D rectangle type*/
	UnsignedIntSampler2DRect = GL_UNSIGNED_INT_SAMPLER_2D_RECT,

	/*(3.1) Uniform of usampler buffer type*/
	UnsignedIntSamplerBuffer = GL_UNSIGNED_INT_SAMPLER_BUFFER,
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Uniform of sampler 2D multisample type*/
	Sampler2DMultisample = GL_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of sampler 2D multisample array type*/
	Sampler2DMultisampleArray = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,

	/*(3.2) Uniform of isampler 2D multisample type*/
	IntSampler2DMultisample = GL_INT_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of isampler 2D multisample array type*/
	IntSampler2DMultisampleArray = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,

	/*(3.2) Uniform of usampler 2D multisample type*/
	UnsignedIntSampler2DMultisample = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of usampler 2D multisample array type*/
	UnsignedIntSampler2DMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
#endif // #ifdef YAGLPP_VERSION_3_2
};

#ifdef YAGLPP_IMPLEMENTATION
void APIENTRY Program::gl_create_program(GLsizei unused, GLuint* id)
{
	*id = glCreateProgram();
}

void APIENTRY Program::gl_delete_program(GLsizei unused, const GLuint* id)
{
	glDeleteProgram(*id);
}

void Program::DetachShaders()
{
	GLint iCount; GLuint uId = object_id();
	glGetProgramiv(uId, GL_ATTACHED_SHADERS, &iCount);
	if (iCount)
	{
		GLuint* pShaders = YAGLPP_MALLOC(GLuint, iCount);
		glGetAttachedShaders(uId, iCount, &iCount, pShaders);
		for (GLint i = 0; i < iCount; i++)
		{
			glDetachShader(uId, pShaders[i]);
		}
		YAGLPP_FREE(pShaders);
	}
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint Program::get_program(GLenum pname)
{
	GLint iResult;
	glGetProgramiv(object_id(), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void Program::GetActiveAttrib(GLuint index, _Out_ AttribInfo* info)
{
	// OPENGL ACTIVE ATTRIBUTE INDEX IS INVALID
	YAGLPP_ASSERT(index < GetActiveAttributes());

	glGetActiveAttrib(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::GetActiveUniform(GLuint index, _Out_ UniformInfo* info)
{
	// OPENGL ACTIVE UNIFORM INDEX IS INVALID
	YAGLPP_ASSERT(index < GetActiveUniforms());

	glGetActiveUniform(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::Link()
{
	GLint iValue;
	GLuint uId = object_id();
	glLinkProgram(uId);
	glGetProgramiv(uId, GL_LINK_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = YAGLPP_MALLOC(GLchar, iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "YAGL++ GLAD program id <" << uId << "> link error:\n" << pBuffer << std::endl;
		YAGLPP_FREE(pBuffer);

		// PROGRAM LINKING FAILED
		YAGLPP_ASSERT(0);
	}
	YAGLPP_GLAD_ERROR;
}

void Program::Use()
{
	glUseProgram(object_id());
	YAGLPP_GLAD_ERROR;
}

void Program::Validate()
{
	GLint iValue;
	GLuint uId = object_id();
	glValidateProgram(uId);
	glGetProgramiv(uId, GL_VALIDATE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = YAGLPP_MALLOC(GLchar, iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "YAGL++ GLAD program id <" << uId << "> validation error:\n" << pBuffer << std::endl;
		YAGLPP_FREE(pBuffer);

		// PROGRAM VALIDATION FAILED
		YAGLPP_ASSERT(0);
	}
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint Program::get_program(GLenum pname)
{
	GLint i; glGetProgramiv(object_id(), pname, &i); return i;
}

inline void Program::GetActiveAttrib(GLuint index, _Out_ AttribInfo* info)
{
	glGetActiveAttrib(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::GetActiveUniform(GLuint index, _Out_ UniformInfo* info)
{
	glGetActiveUniform(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::Link()
{
	glLinkProgram(object_id());
}

inline void Program::Use()
{
	glUseProgram(object_id());
}

inline void Program::Validate()
{
	glValidateProgram(object_id());
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::BindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(object_id(), (GLuint)colorNumber, name);
	YAGLPP_GLAD_ERROR;
}

ColorNumber Program::GetFragDataLocation(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataLocation(object_id(), name);
	YAGLPP_GLAD_ERROR;
	return (ColorNumber)iData;
}

void Program::GetTransformFeedbackVarying(GLuint index, _Out_ AttribInfo* info)
{
	// THE OPENGL VARYING VARIABLE INDEX IS INVALID
	YAGLPP_ASSERT(index < GetTransformFeedbackVaryings());

	glGetTransformFeedbackVarying(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::SetTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(object_id(), count, varyings, (GLenum)bufferMode);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Program::BindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(object_id(), (GLuint)colorNumber, name);
}

inline ColorNumber Program::GetFragDataLocation(_In_z_ const GLchar* name)
{
	return (ColorNumber)glGetFragDataLocation(object_id(), name);;
}

inline void Program::GetTransformFeedbackVarying(GLuint index, _Out_ AttribInfo* info)
{
	glGetTransformFeedbackVarying(object_id(), index, FILENAME_MAX, &info->length, &info->size, (GLenum*)&info->type, info->name);
}

inline void Program::SetTransformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(object_id(), count, varyings, (GLenum)bufferMode);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_1
/*(3.1) GLAD program active uniform block info structure used by <GetActiveUniformBlock>*/
struct Program::UniformBlockInfo
{
	/*(3.1) The number of active uniforms in the uniform block*/
	GLsizei activeUniforms;

	/*(3.1) The last selected index of the uniform buffer binding point*/
	GLuint binding;

	/*(3.1) The implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block*/
	GLsizei dataSize;

	/*(3.1) The total length (including the nul terminator) of the name of the uniform block*/
	GLsizei nameLength;

	/*(3.1) True if the uniform block is referenced by the fragment programming stage*/
	GLboolean referencedByFragmentShader;

	/*(3.1) True if the uniform block is referenced by the vertex programming stage*/
	GLboolean referencedByVertexShader;

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) True if the uniform block is referenced by the geometry programming stage*/
	GLboolean referencedByGeometryShader;
#endif // #ifdef YAGLPP_VERSION_3_2

	/*(3.1) The number of characters actually written by OpenGL in the string indicated by <name>, excluding the null terminator*/
	GLsizei length;

	/*(3.1) The null terminated string containing the name of the uniform variable*/
	GLchar name[FILENAME_MAX];
};
#endif // #ifdef YAGLPP_VERSION_3_1

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)
void Program::GetActiveUniformBlock(GLuint index, _Out_ UniformBlockInfo* info)
{
	// THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	YAGLPP_ASSERT(index < GetActiveUniformBlocks());

	GLuint uId = object_id();
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &info->activeUniforms);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_BINDING, (GLint*)&info->binding);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_DATA_SIZE, &info->dataSize);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_NAME_LENGTH, &info->nameLength);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, (GLint*)&info->referencedByFragmentShader);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, (GLint*)&info->referencedByVertexShader);
	glGetActiveUniformBlockName(uId, index, FILENAME_MAX, &info->length, info->name);

#if defined YAGLPP_VERSION_3_2
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, (GLint*)&info->referencedByGeometryShader);
#endif // #if defined YAGLPP_VERSION_3_2
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::GetActiveUniformBlockName(GLuint index, _Out_ UniformBlockInfo* info)
{
	// THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	YAGLPP_ASSERT(index < GetActiveUniformBlocks());

	glGetActiveUniformBlockName(object_id(), index, FILENAME_MAX, &info->length, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::GetActiveUniformName(GLuint index, _Out_ UniformInfo* info)
{
	// THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	YAGLPP_ASSERT(index < GetActiveUniforms());

	glGetActiveUniformName(object_id(), index, FILENAME_MAX, &info->length, info->name);
	YAGLPP_GLAD_ERROR;
}

void Program::GetUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(object_id(), uniformCount, uniformNames, uniformIndices);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Program::GetActiveUniformBlockName(GLuint index, _Out_ UniformBlockInfo* info)
{
	glGetActiveUniformBlockName(object_id(), index, FILENAME_MAX, &info->length, info->name);
}

inline void Program::GetActiveUniformName(GLuint index, _Out_ UniformInfo* info)
{
	glGetActiveUniformName(object_id(), index, FILENAME_MAX, &info->length, info->name);
}

inline void Program::GetUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(object_id(), uniformCount, uniformNames, uniformIndices);
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINEG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Program::BindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(object_id(), colorNumber, index, name);
	YAGLPP_GLAD_ERROR;
}

GLint Program::GetFragDataIndex(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataIndex(object_id(), name);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Program::BindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(object_id(), colorNumber, index, name);
}

inline GLint Program::GetFragDataIndex(_In_z_ const GLchar* name)
{
	return glGetFragDataIndex(object_id(), name);
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_PROGRAM_H
