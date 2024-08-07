#pragma once
#include "gladpp.h"
namespace gl {
/*GLAD active uniform type enumerator*/
enum class ActiveUniformType : GLenum
{
	/*Uniform of <float> type*/
	Float = GL_FLOAT,

	/*Uniform of <vec2> type*/
	FloatVec2 = GL_FLOAT_VEC2,

	/*Uniform of <vec3> type*/
	FloatVec3 = GL_FLOAT_VEC3,

	/*Uniform of <vec4> type*/
	FloatVec4 = GL_FLOAT_VEC4,

	/*Uniform of <double> type*/
	Double = GL_DOUBLE,

	/*Uniform of <int> type*/
	Int = GL_INT,

	/*Uniform of <ivec2> type*/
	IntVec2 = GL_INT_VEC2,

	/*Uniform of <ivec3> type*/
	IntVec3 = GL_INT_VEC3,

	/*Uniform of <ivec4> type*/
	IntVec4 = GL_INT_VEC4,

	/*Uniform of <unsigned int> type*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Uniform of <bool> type*/
	Bool = GL_BOOL,

	/*Uniform of <bvec2> type*/
	BoolVec2 = GL_BOOL_VEC2,

	/*Uniform of <bvec3> type*/
	BoolVec3 = GL_BOOL_VEC3,

	/*Uniform of <bvec4> type*/
	BoolVec4 = GL_BOOL_VEC4,

	/*Uniform of <mat2> type*/
	FloatMat2 = GL_FLOAT_MAT2,

	/*Uniform of <mat3> type*/
	FloatMat3 = GL_FLOAT_MAT3,

	/*Uniform of <mat4> type*/
	FloatMat4 = GL_FLOAT_MAT4,

	/*Uniform of <sampler1D> type*/
	Sampler1D = GL_SAMPLER_1D,

	/*Uniform of <sampler2D> type*/
	Sampler2D = GL_SAMPLER_2D,

	/*Uniform of <sampler3D> type*/
	Sampler3D = GL_SAMPLER_3D,

	/*Uniform of <samplerCube> type*/
	SamplerCube = GL_SAMPLER_CUBE,

	/*Uniform of <sampler1DShadow> type*/
	Sampler1DShadow = GL_SAMPLER_1D_SHADOW,

	/*Uniform of <sampler2DShadow> type*/
	Sampler2DShadow = GL_SAMPLER_2D_SHADOW,

#ifdef GL_VERSION_2_1
	/*(2.1) Uniform of <mat2x3> type*/
	FloatMat2x3 = GL_FLOAT_MAT2x3,

	/*(2.1) Uniform of <mat2x4> type*/
	FloatMat2x4 = GL_FLOAT_MAT2x4,

	/*(2.1) Uniform of <mat3x2> type*/
	FloatMat3x2 = GL_FLOAT_MAT3x2,

	/*(2.1) Uniform of <mat3x4> type*/
	FloatMat3x4 = GL_FLOAT_MAT3x4,

	/*(2.1) Uniform of <mat4x2> type*/
	FloatMat4x2 = GL_FLOAT_MAT4x2,

	/*(2.1) Uniform of <mat4x3> type*/
	FloatMat4x3 = GL_FLOAT_MAT4x3,
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) Uniform of <uvec2> type*/
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,

	/*(3.0) Uniform of <uvec3> type*/
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,

	/*(3.0) Uniform of <uvec4> type*/
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,

	/*(3.0) Uniform of <sampler1DArray> type*/
	Sampler1DArray = GL_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of <sampler2DArray> type*/
	Sampler2DArray = GL_SAMPLER_2D_ARRAY,

	/*(3.0) Uniform of <sampler1DArrayShadow> type*/
	Sampler1DArrayShadow = GL_SAMPLER_1D_ARRAY_SHADOW,

	/*(3.0) Uniform of <sampler2DArrayShadow> type*/
	Sampler2DArrayShadow = GL_SAMPLER_2D_ARRAY_SHADOW,

	/*(3.0) Uniform of <samplerCubeShadow> type*/
	SamplerCubeShadow = GL_SAMPLER_CUBE_SHADOW,

	/*(3.0) Uniform of <isampler1D> type*/
	IntSampler1D = GL_INT_SAMPLER_1D,

	/*(3.0) Uniform of <isampler2D> type*/
	IntSampler2D = GL_INT_SAMPLER_2D,

	/*(3.0) Uniform of <isampler3D> type*/
	IntSampler3D = GL_INT_SAMPLER_3D,

	/*(3.0) Uniform of <isamplerCube> type*/
	IntSamplerCube = GL_INT_SAMPLER_CUBE,

	/*(3.0) Uniform of <isampler1DArray> type*/
	IntSampler1DArray = GL_INT_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of <isampler2DArray> type*/
	IntSampler2DArray = GL_INT_SAMPLER_2D_ARRAY,

	/*(3.0) Uniform of <usampler1D> type*/
	UnsignedIntSampler1D = GL_UNSIGNED_INT_SAMPLER_1D,

	/*(3.0) Uniform of <usampler2D> type*/
	UnsignedIntSampler2D = GL_UNSIGNED_INT_SAMPLER_2D,

	/*(3.0) Uniform of <usampler3D> type*/
	UnsignedIntSampler3D = GL_UNSIGNED_INT_SAMPLER_3D,

	/*(3.0) Uniform of <usamplerCube> type*/
	UnsignedIntSamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,

	/*(3.0) Uniform of <usampler1DArray> type*/
	UnsignedIntSampler1DArray = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,

	/*(3.0) Uniform of <usampler2DArray> type*/
	UnsignedIntSampler2DArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	/*(3.1) Uniform of <samplerBuffer> type*/
	SamplerBuffer = GL_SAMPLER_BUFFER,

	/*(3.1) Uniform of <sampler2DRect> type*/
	Sampler2DRect = GL_SAMPLER_2D_RECT,

	/*(3.1) Uniform of <sampler2DRectShadow> type*/
	Sampler2DRectShadow = GL_SAMPLER_2D_RECT_SHADOW,

	/*(3.1) Uniform of <isampler2DRect> type*/
	IntSampler2DRect = GL_INT_SAMPLER_2D_RECT,

	/*(3.1) Uniform of <isamplerBuffer> type*/
	IntSamplerBuffer = GL_INT_SAMPLER_BUFFER,

	/*(3.1) Uniform of <usampler2DRect> type*/
	UnsignedIntSampler2DRect = GL_UNSIGNED_INT_SAMPLER_2D_RECT,

	/*(3.1) Uniform of <usamplerBuffer> type*/
	UnsignedIntSamplerBuffer = GL_UNSIGNED_INT_SAMPLER_BUFFER,
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) Uniform of <sampler2DMS> type*/
	Sampler2DMultisample = GL_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of <sampler2DMSArray> type*/
	Sampler2DMultisampleArray = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,

	/*(3.2) Uniform of <isampler2DMS> type*/
	IntSampler2DMultisample = GL_INT_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of <isampler2DMSArray> type*/
	IntSampler2DMultisampleArray = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,

	/*(3.2) Uniform of <usampler2DMS> type*/
	UnsignedIntSampler2DMultisample = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,

	/*(3.2) Uniform of <usampler2DMSArray> type*/
	UnsignedIntSampler2DMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
#endif // #ifdef GL_VERSION_3_2
};

/*OpenGL uniform variable object root class*/
class Uniform
{
private:
	GLint _miLocation = -1; // Uniform index
	GLuint _location();

public:
	/*(1) Constructs unassigned uniform object*/
	Uniform() {}

	/*(2) Constructs uniform object with <setUniformLocation>*/
	Uniform(GLuint location)
	{
		setUniformLocation(location);
	}

	/*(3) Constructs uniform object with <getUniformLocation>*/
	Uniform(Program& program, _In_z_ const GLchar* name)
	{
		getUniformLocation(program, name);
	}

	/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a fragment shader
	@return The maximum fragment uniform components. The value must be at least 1024*/
	static GLuint getMaxFragmentUniformComponents()
	{
		return _getInteger(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
	}

	/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a vertex shader
	@return The maximum vertex uniform components. The value must be at least 1024*/
	static GLuint getMaxVertexUniformComponents()
	{
		return _getInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
	}

	/*(1) Returns the value(s) of float uniform variable
	@param The valid linked program object
	@param Pointer to store the float value(s) of the uniform variable*/
	void getUniform(Program& program, _Out_ GLfloat* params);

	/*(2) Returns the value(s) of integer uniform variable
	@param The valid linked program object
	@param Pointer to store the integer value(s) of the uniform variable*/
	void getUniform(Program& program, _Out_ GLint* params);

	/*Returns the location of a uniform variable. Assigns the new value to the uniform object
	@param The valid linked program object
	@param [in] Pointer to a nul-terminated string containing the name of the uniform variable
	@return True if uniform location found, false otherwise*/
	GLboolean getUniformLocation(Program& program, _In_z_ const GLchar* name);

	/*Checks if retrieved uniform is valid
	@param True if valid uniform, false otherwise*/
	GLboolean isUniform()
	{
		return _miLocation > -1;
	}

	/*Directly assigns the location of a uniform variable
	@param Location value of the uniform variable, must be less than the value returned by <getMaxVertexUniformComponents>*/
	void setUniformLocation(GLuint location);

	/*(1) Specifies the single float value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void uniform(GLfloat v0);

	/*(2) Specifies the two float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void uniform(GLfloat v0, GLfloat v1);

	/*(3) Specifies the three float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void uniform(GLfloat v0, GLfloat v1, GLfloat v2);
	
	/*(4) Specifies the four float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	/*(5) Specifies the single integer value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void uniform(GLint v0);

	/*(6) Specifies the two integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void uniform(GLint v0, GLint v1);

	/*(7) Specifies the three integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void uniform(GLint v0, GLint v1, GLint v2);

	/*(8) Specify the four integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void uniform(GLint v0, GLint v1, GLint v2, GLint v3);

	/*(9) Specifies the float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of float values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const GLfloat* value);

	/*(10) Specifies the two-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component float values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::vec2* value);

	/*(11) Specifies the three-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component float values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::vec3* value);

	/*(12) Specifies the four-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component float values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::vec4* value);

	/*(13) Specifies the integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const GLint* value);

	/*(14) Specifies the two-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::ivec2* value);

	/*(15) Specifies the three-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::ivec3* value);

	/*(16) Specifies the four-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::ivec4* value);

	/*(1) Specifies 2x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x2 matrix values that will be used to update the uniform*/
	void uniformMatrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value);

	/*(1) Specifies 3x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x3 matrix values that will be used to update the uniform*/
	void uniformMatrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value);

	/*(1) Specifies 4x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x4 matrix values that will be used to update the uniform*/
	void uniformMatrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value);

	/*Specifies the TextureUnit value of a sampler uniform variable for the current program object. This is an alias of <uniform(GLint)> function
	@param Specifies the new TextureUnit value to be used for the sampler uniform variable*/
	void uniformTextureUnit(TextureUnit unit)
	{
		uniform((GLint)unit);
	}

#ifdef GL_VERSION_2_1
	/*(2.1) (1) Specifies 2x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x3 matrix values that will be used to update the uniform*/
	void uniformMatrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value);

	/*(2.1) (1) Specifies 2x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x4 matrix values that will be used to update the uniform*/
	void uniformMatrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value);

	/*(2.1) (1) Specifies 3x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x2 matrix values that will be used to update the uniform*/
	void uniformMatrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value);

	/*(2.1) (1) Specifies 3x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x4 matrix values that will be used to update the uniform*/
	void uniformMatrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value);

	/*(2.1) (1) Specifies 4x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x2 matrix values that will be used to update the uniform*/
	void uniformMatrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value);

	/*(2.1) (1) Specifies 4x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x3 matrix values that will be used to update the uniform*/
	void uniformMatrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value);
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) (3) Returns the value(s) of unsigned integer uniform variable
	@param The valid program object
	@param [in] Pointer to store the unsigned integer value(s) of the uniform variable*/
	void getUniform(Program& program, _Out_ GLuint* params);

	/*(3.0) (17) Specifies the single unsigned integer value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void uniform(GLuint v0);

	/*(3.0) (18) Specifies the two unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void uniform(GLuint v0, GLuint v1);

	/*(3.0) (19) Specifies the unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void uniform(GLuint v0, GLuint v1, GLuint v2);

	/*(3.0) (20) Specifies the unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void uniform(GLuint v0, GLuint v1, GLuint v2, GLuint v3);

	/*(3.0) (21) Specifies the unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of unsigned integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const GLuint* value);

	/*(3.0) (22) Specifies the two-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component unsigned integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::uvec2* value);

	/*(3.0) (23) Specifies the three-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component unsigned integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::uvec3* value);

	/*(3.0) (24) Specifies the four-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component unsigned integer values that will be used to update the uniform*/
	void uniform(GLsizei count, _In_reads_(count) const glm::uvec4* value);
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	/*(3.1) Gets the number of words for fragment shader uniform variables in all uniform blocks (including default). The value must be at least 1
	@return The maximum combined fragment uniform components*/
	static GLuint getMaxCombinedFragmentUniformComponents()
	{
		return _getInteger(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
	}

	/*(3.1) Gets the number of words for geometry shader uniform variables in all uniform blocks (including default). The value must be at least 1
	@return The maximum combined geometry uniform components*/
	static GLuint getMaxCombinedGeometryUniformComponents()
	{
		return _getInteger(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS);
	}

	/*(3.1) Gets the number of words for vertex shader uniform variables in all uniform blocks (including default). The value must be at least 1
	@return The maximum combined vertex uniform components*/
	static GLuint getMaxCombinedVertexUniformComponents()
	{
		return _getInteger(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
	}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a geometry shader
	@return The maximum geometry uniform components. The value must be at least 1024*/
	static GLint getMaxGeometryUniformComponents()
	{
		return _getInteger(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS);
	}
#endif // #ifdef GL_VERSION_3_2
}; // class Uniform
} // namespace gl

#include "Program.h"
namespace gl {
#ifndef _DEBUG
inline GLuint Uniform::_location()
{
	return _miLocation;
}

inline void Uniform::getUniform(Program& program, _Out_ GLfloat* params)
{
	glGetUniformfv(program._program_id(), _location(), params);
}

inline void Uniform::getUniform(Program& program, _Out_ GLint* params)
{
	glGetUniformiv(program._program_id(), _location(), params);
}

inline GLboolean Uniform::getUniformLocation(Program& program, _In_z_ const GLchar* name)
{
	_miLocation = glGetUniformLocation(program._program_id(), name); return _miLocation > -1;
}

inline void Uniform::setUniformLocation(GLuint location)
{
	_miLocation = (GLint)location;
}

inline void Uniform::uniform(GLfloat v0)
{
	glUniform1f(_location(), v0);
}

inline void Uniform::uniform(GLfloat v0, GLfloat v1)
{
	glUniform2f(_location(), v0, v1);
}

inline void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(_location(), v0, v1, v2);
}

inline void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(_location(), v0, v1, v2, v3);
}

inline void Uniform::uniform(GLint v0)
{
	glUniform1i(_location(), v0);
}

inline void Uniform::uniform(GLint v0, GLint v1)
{
	glUniform2i(_location(), v0, v1);
}

inline void Uniform::uniform(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(_location(), v0, v1, v2);
}

inline void Uniform::uniform(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(_location(), v0, v1, v2, v3);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(_location(), count, value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(_location(), count, (GLfloat*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(_location(), count, (GLfloat*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(_location(), count, value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(_location(), count, (GLint*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(_location(), count, (GLint*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(_location(), count, (GLint*)value);
}

inline void Uniform::uniformMatrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(_location(), count, transpose, value);
}

#ifdef GL_VERSION_2_1
inline void Uniform::uniformMatrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(_location(), count, transpose, value);
}

inline void Uniform::uniformMatrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(_location(), count, transpose, value);
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
inline void Uniform::getUniform(Program& program, _Out_ GLuint* params)
{
	glGetUniformuiv(program._program_id(), _location(), params);
}

inline void Uniform::uniform(GLuint v0)
{
	glUniform1ui(_location(), v0);
}

inline void Uniform::uniform(GLuint v0, GLuint v1)
{
	glUniform2ui(_location(), v0, v1);
}

inline void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(_location(), v0, v1, v2);
}

inline void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(_location(), v0, v1, v2, v3);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(_location(), count, value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(_location(), count, (GLuint*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(_location(), count, (GLuint*)value);
}

inline void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(_location(), count, (GLuint*)value);
}
#endif // #ifdef GL_VERSION_3_0
#endif // #ifndef _DEBUG
} // namespace gl
