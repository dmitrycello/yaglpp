#define GLPP_BUILD_LIB
#include <glpp/Program.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void Program::detachShaders()
{
	GLint iCount; GLuint uId = _program_id();
	glGetProgramiv(uId, GL_ATTACHED_SHADERS, &iCount);
	if (iCount)
	{
		GLuint* pShaders = (GLuint*)GLPP_MALLOC(iCount * sizeof(GLuint));
		glGetAttachedShaders(uId, iCount, &iCount, pShaders);
		for (GLint i = 0; i < iCount; i++)
		{
			glDetachShader(uId, pShaders[i]);
		}
		GLPP_FREE(pShaders);
	}
	GLPP_GLAD_ERROR;
}

#ifdef _DEBUG
GLint Program::_getProgram(GLenum pname)
{
	GLint iResult;
	glGetProgramiv(_program_id(), pname, &iResult);
	GLPP_GLAD_ERROR;
	return iResult;
}

void Program::createProgram()
{
	GLPP_ASSERT(m_uProgram == 0); // OPENGL PROGRAM OBJECT MUST BE EMPTY
	m_uProgram = glCreateProgram();
	GLPP_GLAD_ERROR;
}

void Program::deleteProgram()
{
	GLPP_ASSERT(m_uProgram != 0); // OPENGL PROGRAM OBJECT IS EMPTY
	glDeleteProgram(m_uProgram);
	m_uProgram = 0;
	GLPP_GLAD_ERROR;
}

void Program::getActiveAttrib(GLuint index, _Out_ ActiveAttribInfo* info)
{
	GLPP_ASSERT(index < getActiveAttributes()); // THE OPENGL ACTIVE ATTRIBUTE INDEX IS INVALID
	glGetActiveAttrib(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	GLPP_GLAD_ERROR;
}

void Program::getActiveUniform(GLuint index, _Out_ ActiveUniformInfo* info)
{
	GLPP_ASSERT(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniform(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	GLPP_GLAD_ERROR;
}

void Program::linkProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glLinkProgram(uId);
	glGetProgramiv(uId, GL_LINK_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)GLPP_MALLOC(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> LINK ERROR:" << std::endl << pBuffer << std::endl;
		GLPP_FREE(pBuffer);
		GLPP_ASSERT(false); // PROGRAM LINKING FAILED
	}
	GLPP_GLAD_ERROR;
}

void Program::useProgram()
{
	glUseProgram(_program_id());
	GLPP_GLAD_ERROR;
}

void Program::validateProgram()
{
	GLint iValue; GLuint uId = _program_id();
	glValidateProgram(uId);
	glGetProgramiv(uId, GL_VALIDATE_STATUS, &iValue);
	if (iValue == GL_FALSE)
	{
		glGetProgramiv(uId, GL_INFO_LOG_LENGTH, &iValue);
		GLchar* pBuffer = (GLchar*)GLPP_MALLOC(iValue);
		glGetProgramInfoLog(uId, iValue, NULL, pBuffer);
		std::cout << "GLAD PROGRAM ID <" << uId << "> VALIDATION ERROR:" << std::endl << pBuffer << std::endl;
		GLPP_FREE(pBuffer);
		GLPP_ASSERT(false); // PROGRAM VALIDATION FAILED
	}
	GLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_3_0
void Program::bindFragDataLocation(ColorNumber colorNumber, _In_z_ const GLchar* name)
{
	glBindFragDataLocation(_program_id(), colorNumber, name);
	GLPP_GLAD_ERROR;
}

ColorNumber Program::getFragDataLocation(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataLocation(_program_id(), name);
	GLPP_GLAD_ERROR;
	return (ColorNumber)iData;
}

void Program::getTransformFeedbackVarying(GLuint index, _Out_ ActiveAttribInfo* info)
{
	GLPP_ASSERT(index < getTransformFeedbackVaryings()); // THE OPENGL VARYING VARIABLE INDEX IS INVALID
	glGetTransformFeedbackVarying(_program_id(), index, MAX_PATH, &info->length, &info->size, (GLenum*)&info->type, info->name);
	GLPP_GLAD_ERROR;
}

void Program::transformFeedbackVaryings(GLsizei count, _In_reads_(count) const GLchar** varyings, TransformFeedbackBufferMode bufferMode)
{
	glTransformFeedbackVaryings(_program_id(), count, varyings, (GLenum)bufferMode);
	GLPP_GLAD_ERROR;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void Program::getActiveUniformBlock(GLuint index, _Out_ ActiveUniformBlockInfo* info)
{
	GLuint uId = _program_id();
	GLPP_ASSERT(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
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
	GLPP_ASSERT(index < getActiveUniformBlocks()); // THE OPENGL ACTIVE UNIFORM BLOCK INDEX IS INVALID
	glGetActiveUniformBlockName(_program_id(), index, MAX_PATH, &info->length, info->name);
	GLPP_GLAD_ERROR;
}

void Program::getActiveUniformName(GLuint index, _Out_ ActiveUniformInfo* info)
{
	GLPP_ASSERT(index < getActiveUniforms()); // THE OPENGL ACTIVE UNIFORM INDEX IS INVALID
	glGetActiveUniformName(_program_id(), index, MAX_PATH, &info->length, info->name);
	GLPP_GLAD_ERROR;
}

void Program::getUniformIndices(GLsizei uniformCount, _In_reads_z_(uniformCount) const GLchar** uniformNames, _Out_writes_(uniformCount) GLuint* uniformIndices)
{
	glGetUniformIndices(_program_id(), uniformCount, uniformNames, uniformIndices);
	GLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG
#endif // #ifdef GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_3
void Program::bindFragDataLocationIndexed(GLuint colorNumber, GLuint index, _In_z_ const GLchar* name)
{
	glBindFragDataLocationIndexed(_program_id(), colorNumber, index, name);
	GLPP_GLAD_ERROR;
}

GLint Program::getFragDataIndex(_In_z_ const GLchar* name)
{
	GLint iData = glGetFragDataIndex(_program_id(), name);
	GLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_3
} // namespace gl
