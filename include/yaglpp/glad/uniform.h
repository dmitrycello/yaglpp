#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_UNIFORM_H
#define YAGLPP_UNIFORM_H

namespace gl {
/*OpenGL uniform variable object root class*/
class Uniform
{
public:
	/*(1) Constructs unassigned uniform object*/
	Uniform()
	{
		m_Location = -1;
	}

	/*(2) Constructs a copy of uniform object*/
	Uniform(const Uniform& source)
	{
		m_Location = source.m_Location;
	}

	/*(3) Constructs uniform object with <SetLocation>*/
	Uniform(GLuint location)
	{
		SetLocation(location);
	}

	/*(4) Constructs uniform object with <GetLocation>*/
	Uniform(Program& program, _In_z_ const GLchar* name)
	{
		GetLocation(program, name);
	}

	/*(1) Gets current OpenGL uniform's location*/
	GLint Get() const
	{
		return m_Location;
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

	/*Checks if retrieved uniform location is valid. MSVC getter for <uniform> property
	@param True if valid uniform, false otherwise*/
	GLboolean IsUniform()
	{
		return m_Location > -1;
	}

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

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if retrieved uniform location is valid*/
	__declspec(property(get = IsUniform)) GLboolean uniform;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

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

private:
	GLint m_Location; // Uniform index
	GLuint get_location();
}; // class Uniform

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLuint Uniform::get_location()
{
	// OPENGL UNIFORM LOCATION INDEX IS INVALID
	YAGLPP_ASSERT(m_Location > -1);

	return m_Location;
}

void Uniform::Get(Program& program, _Out_ GLfloat* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformfv(program.Get(), get_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Get(Program& program, _Out_ GLint* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformiv(program.Get(), get_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	m_Location = glGetUniformLocation(program.Get(), name);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Sampler(TextureUnit unit)
{
	glUniform1i(get_location(), (GLint)unit);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0)
{
	glUniform1f(get_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1)
{
	glUniform2f(get_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(get_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(get_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0)
{
	glUniform1i(get_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1)
{
	glUniform2i(get_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(get_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(get_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(get_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(get_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(get_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(get_location(), count, (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(get_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(get_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(get_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(get_location(), count, (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::SetLocation(GLuint location)
{
	// OPENGL UNIFORM LOCATION INDEX IS INVALID
	YAGLPP_ASSERT(location < GetMaxVertexUniformComponents());

	m_Location = (GLint)location;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLuint Uniform::get_location()
{
	return m_Location;
}

inline void Uniform::Get(Program& program, _Out_ GLfloat* params)
{
	glGetUniformfv(program.Get(), m_Location, params);
}

inline void Uniform::Get(Program& program, _Out_ GLint* params)
{
	glGetUniformiv(program.Get(), m_Location, params);
}

inline void Uniform::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	m_Location = glGetUniformLocation(program.Get(), name);
}

inline void Uniform::Matrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(m_Location, count, transpose, value);
}

inline void Uniform::Sampler(TextureUnit unit)
{
	glUniform1i(m_Location, (GLint)unit);
}

inline void Uniform::Set(GLfloat v0)
{
	glUniform1f(m_Location, v0);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1)
{
	glUniform2f(m_Location, v0, v1);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(m_Location, v0, v1, v2);
}

inline void Uniform::Set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(m_Location, v0, v1, v2, v3);
}

inline void Uniform::Set(GLint v0)
{
	glUniform1i(m_Location, v0);
}

inline void Uniform::Set(GLint v0, GLint v1)
{
	glUniform2i(m_Location, v0, v1);
}

inline void Uniform::Set(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(m_Location, v0, v1, v2);
}

inline void Uniform::Set(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(m_Location, v0, v1, v2, v3);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(m_Location, count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(m_Location, count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(m_Location, count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(m_Location, count, (GLfloat*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(m_Location, count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(m_Location, count, (GLint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(m_Location, count, (GLint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(m_Location, count, (GLint*)value);
}

inline void Uniform::SetLocation(GLuint location)
{
	m_Location = (GLint)location;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Uniform::Matrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Matrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(get_location(), count, transpose, value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Uniform::Matrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(m_Location, count, transpose, value);
}

inline void Uniform::Matrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(m_Location, count, transpose, value);
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Uniform::Get(Program& program, _Out_ GLuint* params)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	glGetUniformuiv(program.Get(), get_location(), params);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0)
{
	glUniform1ui(get_location(), v0);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1)
{
	glUniform2ui(get_location(), v0, v1);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(get_location(), v0, v1, v2);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(get_location(), v0, v1, v2, v3);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(get_location(), count, value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(get_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(get_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(get_location(), count, (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Uniform::Get(Program& program, _Out_ GLuint* params)
{
	glGetUniformuiv(program.Get(), m_Location, params);
}

inline void Uniform::Set(GLuint v0)
{
	glUniform1ui(m_Location, v0);
}

inline void Uniform::Set(GLuint v0, GLuint v1)
{
	glUniform2ui(m_Location, v0, v1);
}

inline void Uniform::Set(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(m_Location, v0, v1, v2);
}

inline void Uniform::Set(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(m_Location, v0, v1, v2, v3);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(m_Location, count, value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(m_Location, count, (GLuint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(m_Location, count, (GLuint*)value);
}

inline void Uniform::Set(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(m_Location, count, (GLuint*)value);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_UNIFORM_H
