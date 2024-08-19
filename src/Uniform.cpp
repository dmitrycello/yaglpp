#define YAGLPP_BUILD_LIB
#include <yaglpp/Uniform.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
GLuint Uniform::_location()
{
	_YAGLPP_ASSERT_(_miLocation > -1); // OPENGL UNIFORM LOCATION INDEX IS INVALID
	return _miLocation;
}

void Uniform::getUniform(Program& program, _Out_ GLfloat* params)
{
	glGetUniformfv(program._program_id(), _location(), params);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::getUniform(Program& program, _Out_ GLint* params)
{
	glGetUniformiv(program._program_id(), _location(), params);
	_YAGLPP_GLAD_ERROR_;
}

GLboolean Uniform::getUniformLocation(Program& program, _In_z_ const GLchar* name)
{
	_miLocation = glGetUniformLocation(program._program_id(), name);
	_YAGLPP_GLAD_ERROR_;
	return isUniform();
}

void Uniform::setUniformLocation(GLuint location)
{
	_YAGLPP_ASSERT_(location < (GLuint)_getInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS)); // OPENGL UNIFORM LOCATION INDEX IS INVALID
	_miLocation = (GLint)location;
}

void Uniform::uniform(GLfloat v0)
{
	glUniform1f(_location(), v0);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLfloat v0, GLfloat v1)
{
	glUniform2f(_location(), v0, v1);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(_location(), v0, v1, v2);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(_location(), v0, v1, v2, v3);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLint v0)
{
	glUniform1i(_location(), v0);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLint v0, GLint v1)
{
	glUniform2i(_location(), v0, v1);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLint v0, GLint v1, GLint v2)
{
	glUniform3i(_location(), v0, v1, v2);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(_location(), v0, v1, v2, v3);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLfloat* value)
{
	glUniform1fv(_location(), count, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec2* value)
{
	glUniform2fv(_location(), count, (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec4* value)
{
	glUniform4fv(_location(), count, (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLint* value)
{
	glUniform1iv(_location(), count, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec2* value)
{
	glUniform2iv(_location(), count, (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec3* value)
{
	glUniform3iv(_location(), count, (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::ivec4* value)
{
	glUniform4iv(_location(), count, (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix2(GLsizei count, GLboolean transpose, _In_reads_(count * 4) const GLfloat* value)
{
	glUniformMatrix2fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix3(GLsizei count, GLboolean transpose, _In_reads_(count * 9) const GLfloat* value)
{
	glUniformMatrix3fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix4(GLsizei count, GLboolean transpose, _In_reads_(count * 16) const GLfloat* value)
{
	glUniformMatrix4fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

#ifdef GL_VERSION_2_1
void Uniform::uniformMatrix2x3(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix2x3fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix2x4(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix2x4fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix3x2(GLsizei count, GLboolean transpose, _In_reads_(count * 6) const GLfloat* value)
{
	glUniformMatrix3x2fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix3x4(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix3x4fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix4x2(GLsizei count, GLboolean transpose, _In_reads_(count * 8) const GLfloat* value)
{
	glUniformMatrix4x2fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniformMatrix4x3(GLsizei count, GLboolean transpose, _In_reads_(count * 12) const GLfloat* value)
{
	glUniformMatrix4x3fv(_location(), count, transpose, value);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
void Uniform::getUniform(Program& program, _Out_ GLuint* params)
{
	glGetUniformuiv(program._program_id(), _location(), params);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLuint v0)
{
	glUniform1ui(_location(), v0);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLuint v0, GLuint v1)
{
	glUniform2ui(_location(), v0, v1);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(_location(), v0, v1, v2);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(_location(), v0, v1, v2, v3);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const GLuint* value)
{
	glUniform1uiv(_location(), count, value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec2* value)
{
	glUniform2uiv(_location(), count, (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec3* value)
{
	glUniform3uiv(_location(), count, (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::uvec4* value)
{
	glUniform4uiv(_location(), count, (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_0
#endif // #ifdef _DEBUG
} // namespace gl
