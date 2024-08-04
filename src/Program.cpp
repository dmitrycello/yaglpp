#define YAGLPP_BUILD_LIB
#include <yaglpp/Program.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void WINAPI Program::_glCreateProgram(GLsizei unused, GLuint* id)
{
	*id = glCreateProgram();
}

void WINAPI Program::_glDeleteProgram(GLsizei unused, const GLuint* id)
{
	glDeleteProgram(*id);
}

void Program::detachShaders()
{
	GLint iCount; GLuint uId = _program_id();
	glGetProgramiv(uId, GL_ATTACHED_SHADERS, &iCount);
	if (iCount)
	{
		GLuint* pShaders = (GLuint*)_YAGLPP_MALLOC_(iCount * sizeof(GLuint));
		glGetAttachedShaders(uId, iCount, &iCount, pShaders);
		for (GLint i = 0; i < iCount; i++)
		{
			glDetachShader(uId, pShaders[i]);
		}
		_YAGLPP_FREE_(pShaders);
	}
	_YAGLPP_GLAD_ERROR_;
}

#ifdef _DEBUG
GLint Program::_getProgram(GLenum pname)
{
	GLint iResult;
	glGetProgramiv(_program_id(), pname, &iResult);
	_YAGLPP_GLAD_ERROR_;
	return iResult;
}

void Program::getActiveAttrib(GLuint index, _Out_ ActiveAttribInfo* info)
{
	_YAGLPP_ASSERT_(index < getActiveAttributes()); // THE OPENGL ACTIVE ATTRIBUTE INDEX IS INVALID
	glGetActiveAttrib(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	_YAGLPP_GLAD_ERROR_;
}

void Program::getActiveUniform(GLuint index, _Out_ ActiveUniformInfo* info)
{
	_YAGLPP_ASSERT_(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniform(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	_YAGLPP_GLAD_ERROR_;
}

void Program::linkProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glLinkProgram(uId);
	glGetProgramiv(uId, GL_LINK_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)_YAGLPP_MALLOC_(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> LINK ERROR:" << std::endl << pBuffer << std::endl;
		_YAGLPP_FREE_(pBuffer);
		_YAGLPP_ASSERT_(false); // PROGRAM LINKING FAILED
	}
	_YAGLPP_GLAD_ERROR_;
}

void Program::useProgram()
{
	glUseProgram(_program_id());
	_YAGLPP_GLAD_ERROR_;
}

void Program::validateProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glValidateProgram(uId);
	glGetProgramiv(uId, GL_VALIDATE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)_YAGLPP_MALLOC_(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> VALIDATION ERROR:" << std::endl << pBuffer << std::endl;
		_YAGLPP_FREE_(pBuffer);
		_YAGLPP_ASSERT_(false); // PROGRAM VALIDATION FAILED
	}
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_3_0
void Program::bindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(_program_id(), (GLuint)colorNumber, name);
	_YAGLPP_GLAD_ERROR_;
}

ColorNumber Program::getFragDataLocation(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataLocation(_program_id(), name);
	_YAGLPP_GLAD_ERROR_;
	return (ColorNumber)iData;
}

void Program::getTransformFeedbackVarying(GLuint index, _Out_ ActiveAttribInfo* info)
{
	_YAGLPP_ASSERT_(index < getTransformFeedbackVaryings()); // THE OPENGL VARYING VARIABLE INDEX IS INVALID
	glGetTransformFeedbackVarying(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	_YAGLPP_GLAD_ERROR_;
}

void Program::transformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(_program_id(), count, varyings, (GLenum)bufferMode);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void Program::getActiveUniformBlock(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	GLuint uId = _program_id();
	_YAGLPP_ASSERT_(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
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

#ifdef _DEBUG
void Program::getActiveUniformBlockName(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	_YAGLPP_ASSERT_(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	glGetActiveUniformBlockName(_program_id(), index, MAX_PATH, &info->length, info->name);
	_YAGLPP_GLAD_ERROR_;
}

void Program::getActiveUniformName(GLuint index, _Out_ ActiveUniformInfo* info)
{
	_YAGLPP_ASSERT_(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniformName(_program_id(), index, MAX_PATH, &info->length, info->name);
	_YAGLPP_GLAD_ERROR_;
}

void Program::getUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(_program_id(), uniformCount, uniformNames, uniformIndices);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG
#endif // #ifdef GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_3
void Program::bindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(_program_id(), colorNumber, index, name);
	_YAGLPP_GLAD_ERROR_;
}

GLint Program::getFragDataIndex(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataIndex(_program_id(), name);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_3
} // namespace gl
