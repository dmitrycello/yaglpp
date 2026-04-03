#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_UNIFORM_BLOCK_H
#define YAGLPP_UNIFORM_BLOCK_H

#ifdef YAGLPP_VERSION_3_1
namespace gl {
/*(3.1) OpenGL uniform block object root class*/
class UniformBlock
{
public:
	/*(3.1) (1) Constructs an empty uniform block object*/
	UniformBlock()
	{
		std::memset(this, 0, sizeof(UniformBlock));
	}

	/*(3.1) (2) Constructs a copy of uniform block object*/
	UniformBlock(const UniformBlock& source) : UniformBlock()
	{
		Copy(source);
	}

	/*(3.1) (3) Constructs uniform block object with <SetIndex>*/
	UniformBlock(Program& program, GLuint index) : UniformBlock()
	{
		SetIndex(program, index);
	}

	/*(3.1) (4) Constructs uniform block object with <GetIndex>*/
	UniformBlock(Program& program, _In_z_ const GLchar* name) : UniformBlock()
	{
		GetIndex(program, name);
	}

	/*(3.1) Cleans up the uniform block object*/
	~UniformBlock()
	{
		if (IsUniformBlock()) Delete();
	}

	/*(3.1) Copies the valid uniform block object
	@param The source uniform block object*/
	void Copy(const UniformBlock& source);

	/*(3.1) Frees and re-initialize the uniform block object*/
	void Delete();

	/*(3.1) Returns the list of the active uniform indices for the uniform block
	@return The list of the active uniform indices*/
	_Ret_notnull_ GLint* GetActiveUniformIndices() const;

	/*(3.1) Returns the number of active uniforms within the uniform block. MSVC getter for <activeUniforms> property
	@return The number active uniforms within the uniform block*/
	GLint GetActiveUniforms() const;

	/*(3.1) Returns the index of the uniform buffer binding point last selected by the uniform block object. MSVC getter for <binding> property
	@return Last selected uniform buffer binding point, or zero if no uniform block has been previously selected*/
	GLuint GetBinding() const
	{
		return get_active_uniform_block(GL_UNIFORM_BLOCK_BINDING);
	}

	/*(3.1) Retrieves the index of a named uniform block of a specified linked program object, and sets up the uniform block object. Must be called before using any other class methods, the object nust be empty prior to the call. If successfull, retreives as well the number and indices of all active uniforms within the block
	@param The valid linked program object
	@param [in] Pointer to a nul-terminated string containing the name of the uniform block*/
	void GetIndex(Program& program, _In_z_ const GLchar* name);

	/*(3.1) Returns the total length (including the nul terminator) of the name of the uniform block. MSVC getter for <nameLength> property
	@return The uniform block name length*/
	GLsizei GetNameLength() const
	{
		return get_active_uniform_block(GL_UNIFORM_BLOCK_NAME_LENGTH);
	}

	/*(3.1) Returns a boolean flag indicating whether the uniform block is referenced by the fragment shader. MSVC getter for <referencedByFragmentShader> property
	@return True if uniform block is referenced by the fragment shader*/
	GLboolean GetReferencedByFragmentShader() const
	{
		return get_active_uniform_block(GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER);
	}

	/*(3.1) Returns a boolean flag indicating whether the uniform block is referenced by the vertex shader. MSVC getter for <referencedByVertexShader> property
	@return True if uniform block is referenced by the vertex shader*/
	GLboolean GetReferencedByVertexShader() const
	{
		return get_active_uniform_block(GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER);
	}

	/*(3.1) Returns the implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block. MSVC getter for <size> property
	@return The uniform block buffer object data size*/
	GLsizei GetSize() const;

	/*(3.1) Returns an array identifying the stride between elements of each of the active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the strides between elements*/
	void GetUniformArrayStride(_Out_ GLint* uniformStrides) const
	{
		get_active_uniforms(GL_UNIFORM_ARRAY_STRIDE, uniformStrides);
	}

	/*(3.1) Returns an array identifying whether each of the uniforms specified by the corresponding array of indices is a row-major or a column-major matrix
	@param [out] Pointer to an array of integers receiving the matrix row-major (1) or column-major (0)*/
	void GetUniformIsRowMajor(_Out_ GLint* uniformIsRowMajor) const
	{
		get_active_uniforms(GL_UNIFORM_IS_ROW_MAJOR, uniformIsRowMajor);
	}

	/*(3.1) Returns an array identifying the stride between columns of a column-major matrix or rows of a row-major matrix, in basic machine units, of each of the active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the matrix strides between columns or rows*/
	void GetUniformMatrixStride(_Out_ GLint* uniformMatrixStrides) const
	{
		get_active_uniforms(GL_UNIFORM_MATRIX_STRIDE, uniformMatrixStrides);
	}

	/*(3.1) Returns an array identifying the length, including the terminating null character of the active uniform names specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the uniform lengths of names*/
	void GetUniformNameLength(_Out_ GLsizei* uniformNameLengths) const
	{
		get_active_uniforms(GL_UNIFORM_NAME_LENGTH, uniformNameLengths);
	}

	/*(3.1) Returns an array identifying the uniform buffer offsets of active uniforms within the uniform blocks specified by the corresponding array of indices. The uniforms from the default scope will receive invalid index value (-1)
	@param [out] Pointer to an array of integers receiving the uniform buffer offsets*/
	void GetUniformOffset(_Out_ GLint* uniformOffsets) const
	{
		get_active_uniforms(GL_UNIFORM_OFFSET, uniformOffsets);
	}

	/*(3.1) Returns an array identifying the number of components of active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of integers receiving the uniform number of components values*/
	void GetUniformSize(_Out_ GLint* uniformSizes) const
	{
		get_active_uniforms(GL_UNIFORM_SIZE, uniformSizes);
	}

	/*(3.1) Returns an array identifying the types of active uniforms specified by the corresponding array of indices
	@param [out] Pointer to an array of enumerators receiving the uniform type values*/
	void GetUniformType(_Out_ Program::UniformType* uniformTypes) const
	{
		get_active_uniforms(GL_UNIFORM_TYPE, (GLint*)uniformTypes);
	}

	/*(3.1) Checks if retrieved uniform block is valid. MSVC getter for <uniformBlock> property
	@param True if valid uniform block, false otherwise*/
	GLboolean IsUniformBlock() const
	{
		return m_Indices != nullptr;
	}

	/*(3.1) (1) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to the beginning of uniform block buffer's data store*/
	void OffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data) const;

	/*(3.1) (2) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param Specifies the DataStore object carriyng uniform block buffer's data store
	@param Specifies the starting offset in bytes within the DataStore memory block, default 0*/
	void OffsetMap(_Out_ void* offsetMap, DataStore& dataStore, int dataOffset = 0) const;

	/*(3.1) (3) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to an array of integers identifying the uniform buffer offsets
	@param [in] Specifies a pointer to the beginning of uniform block buffer data store*/
	void OffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, _Pre_notnull_ const void* data) const;

	/*(3.1) (4) Fills up a user-defined stucture of pointers, namely offset map, receiving the calculated offsets of each uniform block variable within the buffer data store
	@param [out] Specifies a pointer to the offset map stucture receiving the uniform offsets
	@param [in] Specifies a pointer to an array of integers identifying the uniform buffer offsets
	@param Specifies the DataStore object carriyng uniform block buffer's data store
	@param Specifies the starting offset in bytes within the DataStore memory block, default 0*/
	void OffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, DataStore& dataStore, int dataOffset = 0) const;

	/*(3.1) Assigns an index of a binding point to the active uniform block. MSVC setter for <binding> property
	@param Specifies the binding point to which to bind the uniform block*/
	void SetBinding(GLuint binding);

	/*(3.1) Directly assigns the index of a uniform block of a valid linked program object, and sets up the uniform block object. Must be called before using any other class methods, the object nust be empty prior to the call. If successfull, retreives as well the number and indices of all active uniforms within the block
	@param The valid linked program object
	@param Index value of the uniform block, must be less than the value returned by <GetActiveUniformBlocks>*/
	void SetIndex(Program& program, GLuint index);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-only property for number of active uniforms within the uniform block*/
	__declspec(property(get = GetActiveUniforms)) GLint activeUniforms;

	/*(3.1) Read-write property for index of the uniform buffer binding point selected by the uniform block object*/
	__declspec(property(get = GetBinding, put = SetBinding)) GLuint binding;

	/*(3.1) Read-only property for total length (including the nul terminator) of the name of the uniform block*/
	__declspec(property(get = GetNameLength)) GLsizei nameLength;

	/*(3.1) Read-only property for boolean flag indicating whether the uniform block is referenced by the fragment shader*/
	__declspec(property(get = GetReferencedByFragmentShader)) GLboolean referencedByFragmentShader;

	/*(3.1) Read-only property for boolean flag indicating whether the uniform block is referenced by the vertex shader*/
	__declspec(property(get = GetReferencedByVertexShader)) GLboolean referencedByVertexShader;

	/*(3.1) Read-only property for implementation-dependent minimum total buffer object size, in basic machine units, required to hold all active uniforms in the uniform block*/
	__declspec(property(get = GetSize)) GLsizei size;

	/*(3.1) Read-only property to check if retrieved uniform block is valid*/
	__declspec(property(get = IsUniformBlock)) GLboolean uniformBlock;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Returns a boolean flag indicating whether the uniform block is referenced by the geometry shader. MSVC getter for <referencedByGeometryShader> property
	@return True if uniform block is referenced by the geometry shader*/
	GLboolean GetReferencedByGeometryShader() const
	{
		return get_active_uniform_block(GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property for boolean flag indicating whether the uniform block is referenced by the geometry shader*/
	__declspec(property(get = GetReferencedByGeometryShader)) GLboolean referencedByGeometryShader;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef YAGLPP_VERSION_3_2

private:
	GLint m_Count; // Number of uniforms
	GLuint m_Index; // Uniform block index
	GLuint m_Program; // Program id
	GLsizei m_Size; // Data block size
	GLint* m_Indices; // Active uniform indices
	GLint get_active_uniform_block(GLenum pname) const;
	void get_active_uniforms(GLenum pname, GLint* params) const;
}; // class UniformBlock

inline void UniformBlock::OffsetMap(_Out_ void* offsetMap, DataStore& dataStore, int dataOffset) const
{
	OffsetMap(offsetMap, dataStore.GetRegion(dataOffset, m_Size));
}

inline void UniformBlock::OffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, DataStore& dataStore, int dataOffset) const
{
	OffsetMap(offsetMap, uniformOffsets, dataStore.GetRegion(dataOffset, m_Size));
}

#ifdef YAGLPP_IMPLEMENTATION
void UniformBlock::Copy(const UniformBlock& source)
{
	if (&source != this)
	{
		Delete();
		if (source.IsUniformBlock())
		{
			std::memcpy(this, &source, sizeof(UniformBlock));
			m_Indices = YAGLPP_MALLOC(GLint, m_Count);
			std::memcpy(m_Indices, source.m_Indices, m_Count * sizeof(GLint));
		}
	}
}

void UniformBlock::Delete()
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	YAGLPP_FREE(m_Indices);
	std::memset(this, 0, sizeof(UniformBlock));
}

void UniformBlock::GetIndex(Program& program, _In_z_ const GLchar* name)
{
	// UNIFORM BLOCK OBJECT MUST BE EMPTY
	YAGLPP_ASSERT(!IsUniformBlock());

	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	GLuint uIndex = glGetUniformBlockIndex(program.Get(), name);
	YAGLPP_GLAD_ERROR;

	// UNIDENTIFIED ACTIVE UNIFORM BLOCK
	YAGLPP_ASSERT(uIndex != GL_INVALID_INDEX);

	SetIndex(program, uIndex);
}

void UniformBlock::OffsetMap(_Out_ void* offsetMap, _Pre_notnull_ const void* data) const
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	GLint* pUniformOffsets = YAGLPP_MALLOC(GLint, m_Count);
	get_active_uniforms(GL_UNIFORM_OFFSET, pUniformOffsets);
	OffsetMap(offsetMap, pUniformOffsets, data);
	YAGLPP_FREE(pUniformOffsets);
}

void UniformBlock::OffsetMap(_Out_ void* offsetMap, _In_ const GLint* uniformOffsets, _Pre_notnull_ const void* data) const
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	for (int i = 1; i < m_Count; i++)
	{
		((GLintptr*)offsetMap)[i] = (GLintptr)data + (GLintptr)uniformOffsets[i];
	}
	((GLintptr*)offsetMap)[0] = (GLintptr)data + (GLintptr)uniformOffsets[0]; // SAL requirement
}

void UniformBlock::SetIndex(Program& program, GLuint index)
{
	// UNIFORM BLOCK OBJECT MUST BE EMPTY
	YAGLPP_ASSERT(!IsUniformBlock());

	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	// UNIFORM BLOCK INDEX IS INVALID
	YAGLPP_ASSERT(index < program.GetActiveUniformBlocks());

	GLuint uId = program.Get();
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &m_Count);
	m_Index = index;
	m_Program = uId;
	m_Indices = YAGLPP_MALLOC(GLint, m_Count);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_DATA_SIZE, &m_Size);
	glGetActiveUniformBlockiv(uId, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, m_Indices);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint UniformBlock::get_active_uniform_block(GLenum pname) const
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	GLint iResult;
	glGetActiveUniformBlockiv(m_Program, m_Index, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void UniformBlock::get_active_uniforms(GLenum pname, GLint* params) const
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	glGetActiveUniformsiv(m_Program, m_Count, (GLuint*)m_Indices, pname, params);
	YAGLPP_GLAD_ERROR;
}

_Ret_notnull_ GLint* UniformBlock::GetActiveUniformIndices() const
{
	// INVALID UNIFORM BLOCK OBJECT
	YAGLPP_ASSERT(IsUniformBlock());

	return m_Indices; // Already retrieved
}

GLint UniformBlock::GetActiveUniforms() const
{
	// INVALID UNIFORM BLOCK OBJECT
	YAGLPP_ASSERT(IsUniformBlock());

	return m_Count; // Already retrieved
}

GLsizei UniformBlock::GetSize() const
{
	// INVALID UNIFORM BLOCK OBJECT
	YAGLPP_ASSERT(IsUniformBlock());

	return m_Size; // Already retrieved
}

void UniformBlock::SetBinding(GLuint binding)
{
	// UNIFORM BLOCK OBJECT IS EMPTY
	YAGLPP_ASSERT(IsUniformBlock());

	glUniformBlockBinding(m_Program, m_Index, binding);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint UniformBlock::get_active_uniform_block(GLenum pname) const
{
	GLint i; glGetActiveUniformBlockiv(m_Program, m_Index, pname, &i); return i;
}

inline void UniformBlock::get_active_uniforms(GLenum pname, GLint* params) const
{
	glGetActiveUniformsiv(m_Program, m_Count, (GLuint*)m_Indices, pname, params);
}

inline _Ret_notnull_ GLint* UniformBlock::GetActiveUniformIndices() const
{
	return m_Indices;
}

inline GLint UniformBlock::GetActiveUniforms() const
{
	return m_Count;
}

inline GLsizei UniformBlock::GetSize() const
{
	return m_Size;
}

inline void UniformBlock::SetBinding(GLuint binding)
{
	glUniformBlockBinding(m_Program, m_Index, binding);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_1
#endif // #ifndef YAGLPP_UNIFORM_BLOCK_H
