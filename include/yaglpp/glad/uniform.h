#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_UNIFORM_H
#define YAGLPP_UNIFORM_H

namespace gl {
/*OpenGL uniform variable object class derived from <Indices>*/
class Uniform : public Indices
{
public:
	using Indices::Indices;
	/*(1) Constructs unassigned uniform variable*/
	Uniform() : Indices() {}

	/*(2) Constructs uniform variable with <SetLocation>*/
	Uniform(GLuint location) : Indices()
	{
		SetLocation(location);
	}

	/*(3) Constructs uniform variable with <GetLocation>*/
	Uniform(Program& program, _In_z_ const GLchar* name) : Indices()
	{
		GetLocation(program, name);
	}

	/*Allocates an array of uniform variables of a given size, and initialize their location values. Must be deallocated with <Uniform::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Uniform* Alloc(GLsizei n)
	{
		return (Uniform*)indices_alloc(n);
	}

	/*Deletes previously allocated array of uniform variables, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Uniform* uniforms)
	{
		indices_dealloc((GLint*)uniforms);
	}

	/*(2) Returns the value(s) of float uniform variable
	@param The valid linked program object
	@param Pointer to store the float value(s) of the uniform variable*/
	void Get(Program& program, _Out_ GLfloat* params);

	/*(3) Returns the value(s) of integer uniform variable
	@param The valid linked program object
	@param Pointer to store the integer value(s) of the uniform variable*/
	void Get(Program& program, _Out_ GLint* params);

	/*Assigns the newly retrieved location value to the uniform object
	@param The valid linked program object
	@param [in] Pointer to a nul-terminated string containing the name of the uniform variable*/
	void GetLocation(Program& program, _In_z_ const GLchar* name);

	/*Specifies 2x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x2 matrix values that will be used to update the uniform*/
	void Matrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value);

	/*Specifies 3x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x3 matrix values that will be used to update the uniform*/
	void Matrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value);

	/*Specifies 4x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x4 matrix values that will be used to update the uniform*/
	void Matrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value);

	/*Specifies the TextureUnit value of a sampler uniform variable for the current program object. This is an alias of <Set(GLint)> function
	@param Specifies the new TextureUnit value to be used for the sampler uniform variable*/
	void Sampler(TextureUnit unit);

	/*(1) Specifies the single float value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void Set(GLfloat v0);

	/*(2) Specifies the two float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void Set(GLfloat v0, GLfloat v1);

	/*(3) Specifies the three float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void Set(GLfloat v0, GLfloat v1, GLfloat v2);
	
	/*(4) Specifies the four float values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void Set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	/*(5) Specifies the single integer value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void Set(GLint v0);

	/*(6) Specifies the two integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void Set(GLint v0, GLint v1);

	/*(7) Specifies the three integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void Set(GLint v0, GLint v1, GLint v2);

	/*(8) Specify the four integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void Set(GLint v0, GLint v1, GLint v2, GLint v3);

	/*(9) Specifies the float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of float values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const GLfloat* value);

	/*(10) Specifies the two-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component float values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::vec2* value);

	/*(11) Specifies the three-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component float values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::vec3* value);

	/*(12) Specifies the four-component float array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component float values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::vec4* value);

	/*(13) Specifies the integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const GLint* value);

	/*(14) Specifies the two-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::ivec2* value);

	/*(15) Specifies the three-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::ivec3* value);

	/*(16) Specifies the four-component integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::ivec4* value);

	/*Directly assigns the location of a uniform variable
	@param Location value of the uniform variable, must be less than the value returned by <GetMaxVertexUniformComponents>*/
	void SetLocation(GLuint location);

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) Specifies 2x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x3 matrix values that will be used to update the uniform*/
	void Matrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value);

	/*(2.1) Specifies 2x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 2x4 matrix values that will be used to update the uniform*/
	void Matrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value);

	/*(2.1) Specifies 3x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x2 matrix values that will be used to update the uniform*/
	void Matrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value);

	/*(2.1) Specifies 3x4 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 3x4 matrix values that will be used to update the uniform*/
	void Matrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value);

	/*(2.1) Specifies 4x2 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x2 matrix values that will be used to update the uniform*/
	void Matrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value);

	/*(2.1) Specifies 4x3 matrix or array of matrices of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param Specifies whether to transpose the matrix as the values are loaded into the uniform variable
	@param [in] Pointer to an array of specified number of 4x3 matrix values that will be used to update the uniform*/
	void Matrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value);
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) (3) Returns the value(s) of unsigned integer uniform variable
	@param The valid program object
	@param [in] Pointer to store the unsigned integer value(s) of the uniform variable*/
	void Get(Program& program, _Out_ GLuint* params);

	/*(3.0) (17) Specifies the single unsigned integer value of a uniform variable for the current program object
	@param Specifies the new value to be used for the uniform variable*/
	void Set(GLuint v0);

	/*(3.0) (18) Specifies the two unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable*/
	void Set(GLuint v0, GLuint v1);

	/*(3.0) (19) Specifies the unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable*/
	void Set(GLuint v0, GLuint v1, GLuint v2);

	/*(3.0) (20) Specifies the unsigned integer values of a uniform variable for the current program object
	@param Specifies the first new value to be used for the uniform variable
	@param Specifies the second new value to be used for the uniform variable
	@param Specifies the third new value to be used for the uniform variable
	@param Specifies the fourth new value to be used for the uniform variable*/
	void Set(GLuint v0, GLuint v1, GLuint v2, GLuint v3);

	/*(3.0) (21) Specifies the unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of unsigned integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const GLuint* value);

	/*(3.0) (22) Specifies the two-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of two-component unsigned integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::uvec2* value);

	/*(3.0) (23) Specifies the three-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of three-component unsigned integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::uvec3* value);

	/*(3.0) (24) Specifies the four-component unsigned integer array of a uniform variable for the current program object
	@param Specifies the number of elements that are to be modified
	@param [in] Pointer to an array of specified number of four-component unsigned integer values that will be used to update the uniform*/
	void Set(GLsizei count, _In_reads_(count) const glm::uvec4* value);
#endif // #ifdef YAGLPP_VERSION_3_0
}; // class Uniform

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Uniform::Get(Program& program, _Out_ GLfloat* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformfv(program.Get(), indices_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Get(Program& program, _Out_ GLint* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformiv(program.Get(), indices_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	indices_location(glGetUniformLocation(program.Get(), name));
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Sampler(TextureUnit unit)
{
	glUniform1i(indices_location(), (GLint)unit);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0)
{
	glUniform1f(indices_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1)
{
	glUniform2f(indices_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(indices_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(indices_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0)
{
	glUniform1i(indices_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1)
{
	glUniform2i(indices_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(indices_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(indices_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(indices_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(indices_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(indices_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(indices_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(indices_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(indices_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(indices_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(indices_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::SetLocation(GLuint location)
{
	// OPENGL UNIFORM LOCATION INDEX IS INVALID
	YAGLPP_ASSERT(location < GetMaxVertexUniformComponents());

	indices_location(location);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Uniform::Get(Program& program, _Out_ GLfloat* params)
{
	glGetUniformfv(program.Get(), indices_location(), params);
}

inline void Uniform::Get(Program& program, _Out_ GLint* params)
{
	glGetUniformiv(program.Get(), indices_location(), params);
}

inline void Uniform::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	indices_location(glGetUniformLocation(program.Get(), name));
}

inline void Uniform::Matrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(indices_location(), count, transpose, value);
}

inline void Uniform::Sampler(TextureUnit unit)
{
	glUniform1i(indices_location(), (GLint)unit);
}

inline void Uniform::Set(GLfloat v0)
{
	glUniform1f(indices_location(), v0);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1)
{
	glUniform2f(indices_location(), v0, v1);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(indices_location(), v0, v1, v2);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(indices_location(), v0, v1, v2, v3);
}

inline void Uniform::Set(GLint v0)
{
	glUniform1i(indices_location(), v0);
}

inline void Uniform::Set(GLint v0, GLint v1)
{
	glUniform2i(indices_location(), v0, v1);
}

inline void Uniform::Set(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(indices_location(), v0, v1, v2);
}

inline void Uniform::Set(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(indices_location(), v0, v1, v2, v3);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(indices_location(), count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(indices_location(), count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(indices_location(), count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(indices_location(), count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(indices_location(), count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(indices_location(), count, (GLint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(indices_location(), count, (GLint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(indices_location(), count, (GLint*)value);
}

inline void Uniform::SetLocation(GLuint location)
{
	indices_location(location);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Uniform::Matrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(indices_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Uniform::Matrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(indices_location(), count, transpose, value);
}

inline void Uniform::Matrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(indices_location(), count, transpose, value);
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Uniform::Get(Program& program, _Out_ GLuint* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformuiv(program.Get(), indices_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0)
{
	glUniform1ui(indices_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1)
{
	glUniform2ui(indices_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(indices_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(indices_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(indices_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(indices_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(indices_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(indices_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Uniform::Get(Program& program, _Out_ GLuint* params)
{
	glGetUniformuiv(program.Get(), indices_location(), params);
}

inline void Uniform::Set(GLuint v0)
{
	glUniform1ui(indices_location(), v0);
}

inline void Uniform::Set(GLuint v0, GLuint v1)
{
	glUniform2ui(indices_location(), v0, v1);
}

inline void Uniform::Set(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(indices_location(), v0, v1, v2);
}

inline void Uniform::Set(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(indices_location(), v0, v1, v2, v3);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(indices_location(), count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(indices_location(), count, (GLuint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(indices_location(), count, (GLuint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(indices_location(), count, (GLuint*)value);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_UNIFORM_H
