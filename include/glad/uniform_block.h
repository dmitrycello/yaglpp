#pragma once
#include <yaglpp/gladpp.h>
#ifdef YAGLPP_VERSION_3_1
namespace gl {
/*(3.1) OpenGL uniform block object root class*/
class UniformBlock
{
private:
	typedef struct
	{
		GLuint index;	// Uniform block index
		GLuint program;	// Program id
		GLint count;	// Number of uniforms
		GLsizei size;	// Data block size
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint data[0];	// Zero data array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA _mpData;	// Class data
	_LPDATA _data();
	GLint _getActiveUniformBlock(GLenum pname);
	void _getActiveUniforms(GLenum pname, GLint* params);

public:
	/*(3.1) (1) Constructs an empty uniform block object*/
	UniformBlock()
	{
		_mpData = nullptr;
	}

	/*(3.1) (2) Constructs uniform block object with <setUniformBlockIndex>*/
	UniformBlock(Program& program, GLuint index) : UniformBlock()
	{
		setUniformBlockIndex(program, index);
	}

	/*(3.1) (3) Constructs uniform block object with <getUniformBlockIndex>*/
	UniformBlock(Program& program, _In_z_ const GLchar* name) : UniformBlock()
	{
		getUniformBlockIndex(program, name);
	}

	/*(3.1) Cleans up the valid uniform block object*/
	~UniformBlock()
	{
		if (isUniformBlock())
		{
			deleteUniformBlock();
		}
	}

	/*(3.1) Deletes non-empty uniform block object*/
	void deleteUniformBlock();

	/*(3.1) Gets the maximum number of uniform blocks per program. The value must be at least 70
	@return The maximum combined uniform blocks*/
	static GLuint getMaxCombinedUniformBlocks()
	{
		return _getInteger(GL_MAX_COMBINED_UNIFORM_BLOCKS);
	}

	/*(3.1) Gets the maximum number of uniform blocks per fragment shader
	@return The maximum fragment uniform components. The value must be at least 12*/
	static GLuint getMaxFragmentUniformBlocks()
	{
		return _getInteger(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
	}

	/*(3.1) Gets the maximum number of uniform blocks per vertex shader
	@return The maximum vertex uniform components. The value must be at least 12*/
	static GLuint getMaxVertexUniformBlocks()
	{
		return _getInteger(GL_MAX_VERTEX_UNIFORM_BLOCKS);
	}
	
	/*(3.1) Gets the maximum size in basic machine units of a uniform block
	@return The maximum uniform block size. The value must be at least 16384*/
	static GLsizei getMaxUniformBlockSize()
	{
		return _getInteger(GL_MAX_UNIFORM_BLOCK_SIZE);
	}

	/*(3.1) Returns an array identifying the stride between elements of each of the active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the strides between elements*/
	void getUniformArrayStride(_Out_ GLsizei* uniformStrides)
	{
		_getActiveUniforms(GL_UNIFORM_ARRAY_STRIDE, uniformStrides);
	}

	/*(3.1) Returns the list of the active uniform indices for the uniform block
	@return The list of the active uniform indices*/
	_Ret_notnull_ GLuint* getUniformBlockActiveUniformIndices()
	{
		return _data()->data; // Already retrieved
	}

	/*(3.1) Returns the number of active uniforms within the uniform block. Used as a getter of <uniformBlockActiveUniforms> property
	@return The number active uniforms within the uniform block*/
	GLint getUniformBlockActiveUniforms()
	{
		return _data()->count; // Already retrieved
	}

	/*(3.1) Returns the index of the uniform buffer binding point last selected by the uniform block object. Used as a getter of <uniformBlockBinding> property
	@return Last selected uniform buffer binding point, or zero if no uniform block has been previously selected*/
	GLuint getUniformBlockBinding()
	{
		return _getActiveUniformBlock(GL_UNIFORM_BLOCK_BINDING);
	}

	/*(3.1) Returns the implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block. Used as a getter of <uniformBlockDataSize> property
	@return The uniform block buffer object data size*/
	GLsizei getUniformBlockDataSize()
	{
		return _data()->size; // Already retrieved
	}

	/*(3.1) Retrieves the index of a named uniform block of a specified linked program object, and sets up the uniform block object. Must be called before using any other class methods, the object nust be empty prior to the call. If successfull, retreives as well the number and indices of all active uniforms within the block
	@param The valid linked program object
	@param [in] Pointer to a nul-terminated string containing the name of the uniform block
	@return True if uniform block index found, false otherwise*/
	GLboolean getUniformBlockIndex(Program& program, _In_z_ const GLchar* name);

	/*(3.1) Returns the total length (including the nul terminator) of the name of the uniform block. Used as a getter of <uniformBlockNameLength> property
	@return The uniform block name length*/
	GLsizei getUniformBlockNameLength()
	{
		return _getActiveUniformBlock(GL_UNIFORM_BLOCK_NAME_LENGTH);
	}

	/*(3.1) Returns a boolean flag indicating whether the uniform block is referenced by the fragment shader
	@return True if uniform block is referenced by the fragment shader*/
	GLboolean getUniformBlockReferencedByFragmentShader()
	{
		return _getActiveUniformBlock(GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER);
	}

	/*(3.1) Returns a boolean flag indicating whether the uniform block is referenced by the vertex shader
	@return True if uniform block is referenced by the vertex shader*/
	GLboolean getUniformBlockReferencedByVertexShader()
	{
		return _getActiveUniformBlock(GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER);
	}

	/*(3.1) Returns an array identifying whether each of the uniforms specified by the corresponding array of indices is a row-major or a column-major matrix
	@param [out] Pointer to an array of integers receiving the matrix row-major (1) or column-major (0)*/
	void getUniformIsRowMajor(_Out_ GLint* uniformIsRowMajor)
	{
		_getActiveUniforms(GL_UNIFORM_IS_ROW_MAJOR, uniformIsRowMajor);
	}

	/*(3.1) Returns an array identifying the stride between columns of a column-major matrix or rows of a row-major matrix, in basic machine units, of each of the active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the matrix strides between columns or rows*/
	void getUniformMatrixStride(_Out_ GLsizei* uniformMatrixStrides)
	{
		_getActiveUniforms(GL_UNIFORM_MATRIX_STRIDE, uniformMatrixStrides);
	}

	/*(3.1) Returns an array identifying the length, including the terminating null character of the active uniform names specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the uniform lengths of names*/
	void getUniformNameLength(_Out_ GLsizei* uniformNameLengths)
	{
		_getActiveUniforms(GL_UNIFORM_NAME_LENGTH, uniformNameLengths);
	}

	/*(3.1) Returns an array identifying the uniform buffer offsets of active uniforms within the uniform blocks specified by the corresponding array of indices. The uniforms from the default scope will receive invalid index value (-1)
	@param [out] Pointer to an array of integers receiving the uniform buffer offsets*/
	void getUniformOffset(_Out_ GLint* uniformOffsets)
	{
		_getActiveUniforms(GL_UNIFORM_OFFSET, uniformOffsets);
	}

	/*(3.1) Returns an array identifying the number of components of active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the uniform number of components values*/
	void getUniformSize(_Out_ GLsizei* uniformSizes)
	{
		_getActiveUniforms(GL_UNIFORM_SIZE, uniformSizes);
	}

	/*(3.1) Returns an array identifying the types of active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the uniform type values*/
	void getUniformType(_Out_ ActiveUniformType* uniformTypes)
	{
		_getActiveUniforms(GL_UNIFORM_TYPE, (GLint*)uniformTypes);
	}

	/*(3.1) Checks if retrieved uniform block is valid. Used as a getter of <uniformBlock> property
	@param True if valid uniform block, false otherwise*/
	GLboolean isUniformBlock()
	{
		return _mpData != nullptr;
	}

	/*(3.1) Assigns an index of a binding point to the active uniform block. Used as a setter of <uniformBlockBinding> property
	@param Specifies the binding point to which to bind the uniform block*/
	void setUniformBlockBinding(GLuint uniformBlockBinding);

	/*(3.1) Directly assigns the index of a uniform block of a valid linked program object
	@param The valid linked program object
	@param Index value of the uniform block, must be less than the value returned by <getActiveUniformBlocks>*/
	void setUniformBlockIndex(Program& program, GLuint index);

	/*(3.1) (1) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to the beginning of uniform block buffer's data store*/
	void uniformBlockOffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data);

	/*(3.1) (2) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param Specifies the DataStore object carriyng uniform block buffer's data store
	@param Specifies the starting offset in bytes within the DataStore memory block, default 0*/
	void uniformBlockOffsetMap(_Out_ void* offsetMap, DataStore& dataStore, int dataOffset = 0);

	/*(3.1) (3) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to an array of integers identifying the uniform buffer offsets
	@param [in] Specifies a pointer to the beginning of uniform block buffer data store*/
	void uniformBlockOffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, _Pre_notnull_ const void* data);

	/*(3.1) (4) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to an array of integers identifying the uniform buffer offsets
	@param Specifies the DataStore object carriyng uniform block buffer's data store
	@param Specifies the starting offset in bytes within the DataStore memory block, default 0*/
	void uniformBlockOffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, DataStore& dataStore, int dataOffset = 0);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-only property to check if retrieved uniform block is valid*/
	__declspec(property(get = isUniformBlock)) GLboolean uniformBlock;

	/*(3.1) Read-only property for number of active uniforms within the uniform block*/
	__declspec(property(get = getUniformBlockActiveUniforms)) GLint uniformBlockActiveUniforms;

	/*(3.1) Read-write property for index of the uniform buffer binding point selected by the uniform block object*/
	__declspec(property(get = getUniformBlockBinding, put = setUniformBlockBinding)) GLuint uniformBlockBinding;

	/*(3.1) Read-only property for implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block*/
	__declspec(property(get = getUniformBlockDataSize)) GLsizei uniformBlockDataSize;

	/*(3.1) Read-only property for total length (including the nul terminator) of the name of the uniform block*/
	__declspec(property(get = getUniformBlockNameLength)) GLsizei uniformBlockNameLength;

	/*(3.1) Read-only property for boolean flag indicating whether the uniform block is referenced by the fragment shader*/
	__declspec(property(get = getUniformBlockReferencedByFragmentShader)) GLboolean uniformBlockReferencedByFragmentShader;

	/*(3.1) Read-only property for boolean flag indicating whether the uniform block is referenced by the vertex shader*/
	__declspec(property(get = getUniformBlockReferencedByVertexShader)) GLboolean uniformBlockReferencedByVertexShader;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Returns the maximum number of uniform blocks per geometry shader
	@return The maximum geometry uniform blocks. The value must be at least 12*/
	static GLuint getMaxGeometryUniformBlocks()
	{
		return _getInteger(GL_MAX_GEOMETRY_UNIFORM_BLOCKS);
	}

	/*(3.2) Returns a boolean flag indicating whether the uniform block is referenced by the geometry shader. Used as a getter of <uniformBlockReferencedByGeometryShader> property
	@return True if uniform block is referenced by the geometry shader*/
	GLboolean getUniformBlockReferencedByGeometryShader()
	{
		return _getActiveUniformBlock(GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property for boolean flag indicating whether the uniform block is referenced by the geometry shader*/
	__declspec(property(get = getUniformBlockReferencedByGeometryShader)) GLboolean uniformBlockReferencedByGeometryShader;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class UniformBlock
} // namespace gl

#include <yaglpp/data_store.h>
#include <yaglpp/glad/program.h>
namespace gl {
inline void UniformBlock::uniformBlockOffsetMap(_Out_ void* offsetMap, DataStore& dataStore, int dataOffset)
{
	uniformBlockOffsetMap(offsetMap, dataStore.getSubData(dataOffset, _data()->size));
}

inline void UniformBlock::uniformBlockOffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, DataStore& dataStore, int dataOffset)
{
	uniformBlockOffsetMap(offsetMap, uniformOffsets, dataStore.getSubData(dataOffset, _data()->size));
}

#ifdef YAGLPP_IMPLEMENTATION
void UniformBlock::deleteUniformBlock()
{
	_deallocate(_data(), nullptr);
	_mpData = nullptr;
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

void UniformBlock::setUniformBlockIndex(Program& program, GLuint index)
{
	YAGLPP_ASSERT(_mpData == nullptr); // OPENGL UNIFORM BLOCK MUST BE EMPTY
	YAGLPP_ASSERT(index < program.getActiveUniformBlocks()); // OPENGL UNIFORM BLOCK INDEX IS INVALID
	GLint iCount, uProgram = program._program_id();
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &iCount);
	_mpData = (_LPDATA)_allocate(sizeof(_DATA) + sizeof(GLuint) * iCount, nullptr);
	_mpData->index = index;
	_mpData->program = uProgram;
	_mpData->count = iCount;
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_DATA_SIZE, &_mpData->size);
	glGetActiveUniformBlockiv(uProgram, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)_mpData->data);
	YAGLPP_GLAD_ERROR;
}

void UniformBlock::uniformBlockOffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data)
{
	GLint* pOffsets = (GLint*)_allocate(_data()->count * sizeof(GLint), nullptr);
	_getActiveUniforms(GL_UNIFORM_OFFSET, pOffsets);
	uniformBlockOffsetMap(offsetMap, pOffsets, data);
	_deallocate(pOffsets, nullptr);
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
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
UniformBlock::_LPDATA UniformBlock::_data()
{
	YAGLPP_ASSERT(_mpData != nullptr); // OPENGL UNIFORM BLOCK OBJECT IS EMPTY
	return _mpData;
}

GLint UniformBlock::_getActiveUniformBlock(GLenum pname)
{
	GLint iData;
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

void UniformBlock::setUniformBlockBinding(GLuint uniformBlockBinding)
{
	_LPDATA lpData = _data();
	glUniformBlockBinding(lpData->program, lpData->index, uniformBlockBinding);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline UniformBlock::_LPDATA UniformBlock::_data()
{
	return _mpData;
}

inline GLint UniformBlock::_getActiveUniformBlock(GLenum pname)
{
	GLint i; glGetActiveUniformBlockiv(_mpData->program, _mpData->index, pname, &i); return i;
}

inline void UniformBlock::_getActiveUniforms(GLenum pname, GLint* params)
{
	glGetActiveUniformsiv(_mpData->program, _mpData->count, _mpData->data, pname, params);
}

inline void UniformBlock::setUniformBlockBinding(GLuint uniformBlockBinding)
{
	glUniformBlockBinding(_mpData->program, _mpData->index, uniformBlockBinding);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_1
