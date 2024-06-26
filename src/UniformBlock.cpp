#define YAGLPP_BUILD_LIB
#include <yaglpp/UniformBlock.h>
#include <yaglpp/Program.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_1
namespace gl {
void UniformBlock::deleteUniformBlock()
{
	YAGLPP_FREE(_data());
	m_lpData = nullptr;
}

void UniformBlock::setUniformBlockIndex(Program& program, GLuint index)
{
	YAGLPP_ASSERT(m_lpData == nullptr); // OPENGL UNIFORM BLOCK MUST BE EMPTY
	YAGLPP_ASSERT(index < program.getActiveUniformBlocks()); // OPENGL UNIFORM BLOCK INDEX IS INVALID
	GLint iCount, uProgram = program._program_id();
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &iCount);
	m_lpData = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + sizeof(GLuint) * iCount);
	m_lpData->index = index;
	m_lpData->program = uProgram;
	m_lpData->count = iCount;
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_DATA_SIZE, &m_lpData->size);
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)m_lpData->data);
	YAGLPP_GLAD_ERROR;
}

void UniformBlock::setUniformOffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data)
{
	GLint* pOffsets = (GLint*)YAGLPP_MALLOC(_data()->count * sizeof(GLint));
	_getActiveUniforms(GL_UNIFORM_OFFSET, pOffsets);
	setUniformOffsetMap(offsetMap, pOffsets, data);
	YAGLPP_FREE(pOffsets);
}

void UniformBlock::setUniformOffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, _Pre_notnull_ const void* data)
{
	GLsizei iCount = _data()->count;
	for (int i = 1; i < iCount; i++)
	{
		((GLintptr*)offsetMap)[i] = (GLintptr)data + (GLintptr)uniformOffsets[i];
	}
	((GLintptr*)offsetMap)[0] = (GLintptr)data + (GLintptr)uniformOffsets[0]; // SAL requirment
}

#ifdef _DEBUG
UniformBlock::_LPDATA UniformBlock::_data()
{
	YAGLPP_ASSERT(m_lpData != nullptr); // OPENGL UNIFORM BLOCK OBJECT IS EMPTY
	return m_lpData;
}

GLint UniformBlock::_getActiveUniformBlock(GLenum pname)
{
	GLint iData = 0;
	_LPDATA lpData = _data();
	glGetActiveUniformBlockiv(lpData->program, lpData->index, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

void UniformBlock::_getActiveUniforms(GLenum pname, GLint* params)
{
	_LPDATA lpData = _data();
	glGetActiveUniformsiv(lpData->program, lpData->count, lpData->data, pname, params);
	YAGLPP_GLAD_ERROR;
}

GLboolean UniformBlock::getUniformBlockIndex(Program& program, _In_z_ const GLchar* name)
{
	GLuint uIndex = glGetUniformBlockIndex(program._program_id(), name);
	YAGLPP_GLAD_ERROR;
	if (uIndex != GL_INVALID_INDEX)
	{
		setUniformBlockIndex(program, uIndex);
		return GL_TRUE;
	}
	return GL_FALSE;
}

void UniformBlock::uniformBlockBinding(GLuint uniformBlockBinding)
{
	_LPDATA lpData = _data();
	glUniformBlockBinding(lpData->program, lpData->index, uniformBlockBinding);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_1
