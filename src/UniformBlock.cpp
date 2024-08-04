#define YAGLPP_BUILD_LIB
#include <yaglpp/UniformBlock.h>
#include <yaglpp/Program.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_1
namespace gl {
void UniformBlock::deleteUniformBlock()
{
	_YAGLPP_FREE_(_data());
	m_lpData = nullptr;
}

GLboolean UniformBlock::getUniformBlockIndex(Program& program, _In_z_ const GLchar* name)
{
	GLuint uIndex = glGetUniformBlockIndex(program._program_id(), name);
	_YAGLPP_GLAD_ERROR_;
	if (uIndex != GL_INVALID_INDEX)
	{
		setUniformBlockIndex(program, uIndex);
		return GL_TRUE;
	}
	return GL_FALSE;
}

void UniformBlock::setUniformBlockIndex(Program& program, GLuint index)
{
	_YAGLPP_ASSERT_(m_lpData == nullptr); // OPENGL UNIFORM BLOCK MUST BE EMPTY
	_YAGLPP_ASSERT_(index < program.getActiveUniformBlocks()); // OPENGL UNIFORM BLOCK INDEX IS INVALID
	GLint iCount, uProgram = program._program_id();
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &iCount);
	m_lpData = (_LPDATA)_YAGLPP_MALLOC_(sizeof(_DATA) + sizeof(GLuint) * iCount);
	m_lpData->index = index;
	m_lpData->program = uProgram;
	m_lpData->count = iCount;
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_DATA_SIZE, &m_lpData->size);
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)m_lpData->data);
	_YAGLPP_GLAD_ERROR_;
}

void UniformBlock::uniformBlockOffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data)
{
	GLint* pOffsets = (GLint*)_YAGLPP_MALLOC_(_data()->count * sizeof(GLint));
	_getActiveUniforms(GL_UNIFORM_OFFSET, pOffsets);
	uniformBlockOffsetMap(offsetMap, pOffsets, data);
	_YAGLPP_FREE_(pOffsets);
}

void UniformBlock::uniformBlockOffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, _Pre_notnull_ const void* data)
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
	_YAGLPP_ASSERT_(m_lpData != nullptr); // OPENGL UNIFORM BLOCK OBJECT IS EMPTY
	return m_lpData;
}

GLint UniformBlock::_getActiveUniformBlock(GLenum pname)
{
	GLint iData = 0;
	_LPDATA lpData = _data();
	glGetActiveUniformBlockiv(lpData->program, lpData->index, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

void UniformBlock::_getActiveUniforms(GLenum pname, GLint* params)
{
	_LPDATA lpData = _data();
	glGetActiveUniformsiv(lpData->program, lpData->count, lpData->data, pname, params);
	_YAGLPP_GLAD_ERROR_;
}

void UniformBlock::uniformBlockBinding(GLuint uniformBlockBinding)
{
	_LPDATA lpData = _data();
	glUniformBlockBinding(lpData->program, lpData->index, uniformBlockBinding);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_1
