#define GLPP_BUILD_LIB
#include <glpp/Uniform.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
GLuint Uniform::_location()
{
	GLPP_ASSERT(m_iLocation > -1); // OPENGL UNIFORM LOCATION INDEX IS INVALID
	return m_iLocation;
}

void Uniform::getUniform(Program& program, _Out_ GLfloat* params)
{
	glGetUniformfv(program._program_id(), _location(), params);
	GLPP_GLAD_ERROR;
}

void Uniform::getUniform(Program& program, _Out_ GLint* params)
{
	glGetUniformiv(program._program_id(), _location(), params);
	GLPP_GLAD_ERROR;
}

GLboolean Uniform::getUniformLocation(Program& program, _In_z_ const GLchar* name)
{
	m_iLocation = glGetUniformLocation(program._program_id(), name);
	GLPP_GLAD_ERROR;
	return isUniform();
}

void Uniform::setUniformLocation(GLuint location)
{
	GLPP_ASSERT(location < (GLuint)_getInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS)); // OPENGL UNIFORM LOCATION INDEX IS INVALID
	m_iLocation = (GLint)location;
}

void Uniform::uniform(GLfloat v0)
{
	glUniform1f(_location(), v0);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLfloat v0, GLfloat v1)
{
	glUniform2f(_location(), v0, v1);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(_location(), v0, v1, v2);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(_location(), v0, v1, v2, v3);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLint v0)
{
	glUniform1i(_location(), v0);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLint v0, GLint v1)
{
	glUniform2i(_location(), v0, v1);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(_location(), v0, v1, v2);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(_location(), v0, v1, v2, v3);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(_location(), count, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(_location(), count, (GLfloat*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(_location(), count, (GLfloat*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(_location(), count, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(_location(), count, (GLint*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(_location(), count, (GLint*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(_location(), count, (GLint*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

#ifdef GL_VERSION_2_1
void Uniform::uniformMatrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniformMatrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(_location(), count, transpose, value);
	GLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
void Uniform::getUniform(Program& program, _Out_ GLuint* params)
{
	glGetUniformuiv(program._program_id(), _location(), params);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLuint v0)
{
	glUniform1ui(_location(), v0);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLuint v0, GLuint v1)
{
	glUniform2ui(_location(), v0, v1);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(_location(), v0, v1, v2);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(_location(), v0, v1, v2, v3);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(_location(), count, value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(_location(), count, (GLuint*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(_location(), count, (GLuint*)value);
	GLPP_GLAD_ERROR;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(_location(), count, (GLuint*)value);
	GLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_3_0
#endif // #ifdef _DEBUG
} // namespace gl
