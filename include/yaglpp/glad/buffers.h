#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_BUFFERS_H
#define YAGLPP_BUFFERS_H

namespace gl {
/*OpenGL untyped buffer object class derived from <Objects>. Can be used as a temporary asset before its reference is casted to any valid buffer type*/
class Buffers : public Objects
{
public:
	using Objects::Objects;
	enum class Access : GLenum;
	enum class Usage : GLenum;
	/*Allocates an array of buffer objects of a given size, and generates their object names. Must be deallocated with <Buffers::Dealloc> after use
	@param The number of the array elements 
	@return The pointer to allocated array*/
	static Buffers* Alloc(GLsizei n)
	{
		return (Buffers*)object_alloc(glGenBuffers, n);
	}

	/*Deletes previously allocated array of buffer object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Buffers* buffers)
	{
		object_dealloc(glDeleteBuffers, (GLuint*)buffers);
	}

	/*Deletes valid OpenGL buffer object name and sets the buffer class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteBuffers);
	}

	/*Deletes previously generated OpenGL buffer object names in a static array or a user-defined structure of buffers, namely buffer map, and sets its class objects in empty state. Allows to unset multiple buffers of various types in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of buffer map returned by sizeof operator
	@param [in-out] Pointer to buffer map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* bufferMap)
	{
		object_delete_map(glDeleteBuffers, n, bufferMap);
	}

	/*Generates OpenGL buffer object name in an empty buffer class object*/
	void Gen()
	{
		object_gen(glGenBuffers);
	}

	/*Generates OpenGL buffer object names in a static array or a user-defined structure of buffers, namely buffer map. Allows to set multiple buffers of various types in one function call. All class objects are silently overwritten
	@param The size in bytes of buffer map returned by sizeof operator
	@param [out] Pointer to buffer map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* bufferMap)
	{
		object_gen_map(glGenBuffers, n, bufferMap);
	}

	/*Determines if a valid OpenGL buffer object name corresponds to a buffer object. MSVC getter for <buffer> property
	@return True if active buffer object, false otherwise*/
	GLboolean IsBuffer() const
	{
		return object_is(glIsBuffer);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if active buffer object*/
	__declspec(property(get = IsBuffer)) GLboolean buffer;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	enum class AccessFlags : GLbitfield;

	/*(3.0) Constant expression <AccessFlags> bitwise OR operator, combines multiple buffer access flags into bitfield mask
	@param Bitmask buffer access flags enumerator 1
	@param Bitmask buffer access flags enumerator 2
	@return Resulting bitmask buffer access flags enumerator*/
	friend constexpr AccessFlags operator | (AccessFlags flag1, AccessFlags flag2)
	{
		return (AccessFlags)((GLbitfield)flag1 | (GLbitfield)flag2);
	}

	/*(3.0) Constant expression <AccessFlags> bitwise AND operator, checks the bitmask against the flag
	@param Bitmask buffer access flags enumerator
	@param Query buffer access flags bitmask enumerator
	@return True if query flag exists in the bitmask enumerator, false otherwise*/
	friend constexpr GLboolean operator & (AccessFlags mask, AccessFlags flags)
	{
		return ((GLbitfield)mask & (GLbitfield)flags) > 0;
	}
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) Binds a buffer object to copy read buffer target*/
	void BindCopyRead()
	{
		object_bind(glBindBuffer, GL_COPY_READ_BUFFER);
	}

	/*(3.1) Binds a buffer object to copy write buffer target*/
	void BindCopyWrite()
	{
		object_bind(glBindBuffer, GL_COPY_WRITE_BUFFER);
	}

	/*(3.1) (1) Copies all or part of the data store of a buffer object bound to copy read buffer target into the data store of buffer object bound to copy write buffer target
	@param Specifies the offset, in basic machine units, within the copy read buffer, from which data will be read
	@param Specifies the offset, in basic machine units, within the copy write buffer, into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied*/
	static void CopySubData(GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);

	/*(3.1) (1) Creates and initializes buffer object's data store using copy write buffer target with the valid DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void CopyWriteData(DataStore& dataStore, Usage usage);

	/*(3.1) (2) Creates and initializes buffer object's data store using copy write buffer target
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void CopyWriteData(GLsizeiptr size, _Pre_maybenull_ const void* data, Usage usage);

	/*(3.1) Determines if the buffer object is currently bound to copy read buffer target. MSVC getter for <copyReadBinding> property
	@return True if buffer object currently bound to copy read buffer target, false otherwise*/
	GLboolean IsCopyReadBinding()
	{
		return object_binding(GL_COPY_READ_BUFFER_BINDING, Get());
	}

	/*(3.1) Determines if the buffer object is currently bound to copy write buffer target. MSVC: used as a setter of <copyWriteBinding> property
	@return True if buffer object currently bound to copy write buffer target, false otherwise*/
	GLboolean IsCopyWriteBinding()
	{
		return object_binding(GL_COPY_WRITE_BUFFER_BINDING, Get());
	}

	/*(3.1) Unbinds any buffer object bound to copy read buffer target*/
	static void UnbindCopyRead()
	{
		glBindBuffer(GL_COPY_READ_BUFFER, 0);
	}

	/*(3.1) Unbinds any buffer object bound to copy write buffer target*/
	static void UnbindCopyWrite()
	{
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	}
#endif // #ifdef YAGLPP_VERSION_3_1

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.1) Read-only property to check if buffer object is currently bound to copy read buffer target*/
	__declspec(property(get = IsCopyReadBinding)) GLboolean copyReadBinding;

	/*(3.1) Read-only property to check if buffer object is currently bound to copy write buffer target*/
	__declspec(property(get = IsCopyWriteBinding)) GLboolean copyWriteBinding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	void buffer_data(GLenum target, GLenum binding, GLenum usage, DataStore& dataStore);
	void buffer_data(GLenum target, GLenum binding, GLsizeiptr size, const void* data, GLenum usage);
	void buffer_sub_data(GLenum target, GLenum binding, DataStore& data);
	void buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, DataStore& data);
	void buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, const void* data);
	void buffer_create(GLenum target, GLenum usage, DataStore& dataStore);
	void buffer_create(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	GLint get_buffer_parameter(GLenum target, GLenum binding, GLenum pname);
	void* get_buffer_pointer(GLenum target, GLenum binding);
	void get_buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, DataStore& data);
	void get_buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, void* data);
	void* map_buffer(GLenum target, GLenum binding, GLenum access);
	GLboolean unmap_buffer(GLenum target, GLenum binding);

#ifdef YAGLPP_VERSION_3_0
	void bind_buffer_base(GLenum target, GLuint index);
	void bind_buffer_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size);
	void flush_mapped_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length);
	void* map_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length, GLbitfield access);
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	void copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLintptr roffset, GLintptr woffset, GLsizeiptr size);
	void copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLenum wtarget, GLenum wbinding, GLuint buffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size);
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	GLint64 get_buffer_parameter64(GLenum target, GLenum binding, GLenum pname);
#endif // #ifdef 
}; // class Buffers : public Objects

/*GLAD buffer access policy enumerator*/
enum class Buffers::Access : GLenum
{
	/*Indicates that the returned pointer may be used to read buffer object data*/
	ReadOnly = GL_READ_ONLY,

	/*Indicates that the returned pointer may be used to modify buffer object data*/
	WriteOnly = GL_WRITE_ONLY,

	/*Indicates that the returned pointer may be used to read and to modify buffer object data*/
	ReadWrite = GL_READ_WRITE,
};

/*GLAD buffer expected usage pattern enumerator*/
enum class Buffers::Usage : GLenum
{
	/*The data store contents will be modified once and used at most a few times. The data store contents are modified by the application, and used as the source for GL drawing and image specification commands*/
	StreamDraw = GL_STREAM_DRAW,

	/*The data store contents will be modified once and used at most a few times. The data store contents are modified by reading data from the GL, and used to return that data when queried by the application*/
	StreamRead = GL_STREAM_READ,

	/*The data store contents will be modified once and used at most a few times. The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands*/
	StreamCopy = GL_STREAM_COPY,

	/*The data store contents will be modified once and used many times. The data store contents are modified by the application, and used as the source for GL drawing and image specification commands*/
	StaticDraw = GL_STATIC_DRAW,

	/*The data store contents will be modified once and used many times. The data store contents are modified by reading data from the GL, and used to return that data when queried by the application*/
	StaticRead = GL_STATIC_READ,

	/*The data store contents will be modified once and used many times. The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands*/
	StaticCopy = GL_STATIC_COPY,

	/*The data store contents will be modified repeatedly and used many times. The data store contents are modified by the application, and used as the source for GL drawing and image specification commands*/
	DynamicDraw = GL_DYNAMIC_DRAW,

	/*The data store contents will be modified repeatedly and used many times. The data store contents are modified by reading data from the GL, and used to return that data when queried by the application*/
	DynamicRead = GL_DYNAMIC_READ,

	/*The data store contents will be modified repeatedly and used many times. The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands*/
	DynamicCopy = GL_DYNAMIC_COPY,
};

#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD buffer access flags bitmask enumerator*/
enum class Buffers::AccessFlags : GLbitfield
{
	/*(3.0) Indicates that the returned pointer may be used to read buffer object data. No GL error is generated if the pointer is used to query a mapping which excludes this flag, but the result is undefined and system errors (possibly including program termination) may occur*/
	ReadBit = GL_MAP_READ_BIT,

	/*(3.0) Indicates that the returned pointer may be used to modify buffer object data. No GL error is generated if the pointer is used to modify a mapping which excludes this flag, but the result is undefined and system errors (possibly including program termination) may occur*/
	WriteBit = GL_MAP_WRITE_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the previous contents of the specified range may be discarded. Data within this range are undefined with the exception of subsequently written data. No GL error is generated if subsequent GL operations access unwritten data, but the result is undefined and system errors (possibly including program termination) may occur. This flag may not be used in combination with <ReadBit>*/
	InvalidateRangeBit = GL_MAP_INVALIDATE_RANGE_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the previous contents of the entire buffer may be discarded. Data within the entire buffer are undefined with the exception of subsequently written data. No GL error is generated if subsequent GL operations access unwritten data, but the result is undefined and system errors (possibly including program termination) may occur. This flag may not be used in combination with <ReadBit>*/
	InvalidateBufferBit = GL_MAP_INVALIDATE_BUFFER_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that one or more discrete subranges of the mapping may be modified. When this flag is set, modifications to each subrange must be explicitly flushed by calling <FlushMappedRange>. No GL error is set if a subrange of the mapping is modified and not flushed, but data within the corresponding subrange of the buffer are undefined. This flag may only be used in conjunction with <WriteBit>. When this option is selected, flushing is strictly limited to regions that are explicitly indicated with calls to <FlushMappedRange> prior to unmap; if this option is not selected <Unmap> will automatically flush the entire mapped range when called*/
	FlushExplicitBit = GL_MAP_FLUSH_EXPLICIT_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the GL should not attempt to synchronize pending operations on the buffer prior to returning from <MapRange>. No GL error is generated if pending operations which source or modify the buffer overlap the mapped region, but the result of such previous and any subsequent operations is undefined*/
	UnsynchronizedBit = GL_MAP_UNSYNCHRONIZED_BIT,
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
inline void Buffers::CopyWriteData(DataStore& dataStore, Usage usage)
{
	buffer_data(GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER_BINDING, (GLsizeiptr)dataStore.GetSize(), dataStore.Get(), (GLenum)usage);
}

inline void Buffers::CopyWriteData(GLsizeiptr size, _Pre_maybenull_ const void* data, Usage usage)
{
	buffer_data(GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER_BINDING, size, data, (GLenum)usage);
}
#endif // #ifdef YAGLPP_VERSION_3_1

inline void Buffers::buffer_data(GLenum target, GLenum binding, GLenum usage, DataStore& dataStore)
{
	buffer_data(target, binding, (GLsizeiptr)dataStore.GetSize(), dataStore.Get(), usage);
}

inline void Buffers::buffer_sub_data(GLenum target, GLenum binding, DataStore& data)
{
	buffer_sub_data(target, binding, 0, data.GetSize(), data.Get());
}

inline void Buffers::buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, DataStore& data)
{
	buffer_sub_data(target, binding, offset, size, data.GetRegion((int)offset, (int)size));
}

inline void Buffers::buffer_create(GLenum target, GLenum usage, DataStore& dataStore)
{
	buffer_create(target, (GLsizeiptr)dataStore.GetSize(), dataStore.Get(), usage);
}

inline void Buffers::get_buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, DataStore& data)
{
	get_buffer_sub_data(target, binding, offset, size, data.GetRegion((int)offset, (int)size));
}

#ifdef YAGLPP_IMPLEMENTATION
void Buffers::buffer_create(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	object_gen(glGenBuffers);
	object_bind(glBindBuffer, target);
	glBufferData(target, size, data, usage);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Buffers::buffer_data(GLenum target, GLenum binding, GLsizeiptr size, const void* data, GLenum usage)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glBufferData(target, size, data, usage);
	YAGLPP_GLAD_ERROR;
}

void Buffers::buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, const void* data)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glBufferSubData(target, offset, size, data);
	YAGLPP_GLAD_ERROR;
}

GLint Buffers::get_buffer_parameter(GLenum target, GLenum binding, GLenum pname)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLint iResult;
	glGetBufferParameteriv(target, pname, &iResult);
	return iResult;
}

void* Buffers::get_buffer_pointer(GLenum target, GLenum binding)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	void* pResult;
	glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &pResult);
	return pResult;
}

void Buffers::get_buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, void* data)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGetBufferSubData(target, offset, size, data);
	YAGLPP_GLAD_ERROR;
}

void* Buffers::map_buffer(GLenum target, GLenum binding, GLenum access)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	void* pResult = glMapBuffer(target, access);
	YAGLPP_GLAD_ERROR;
	return pResult;
}

GLboolean Buffers::unmap_buffer(GLenum target, GLenum binding)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLboolean bResult = glUnmapBuffer(target);
	YAGLPP_GLAD_ERROR;
	return bResult;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Buffers::buffer_data(GLenum target, GLenum binding, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

inline void Buffers::buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, const void* data)
{
	glBufferSubData(target, offset, size, data);
}

inline GLint Buffers::get_buffer_parameter(GLenum target, GLenum binding, GLenum pname)
{
	GLint i; glGetBufferParameteriv(target, pname, &i); return i;
}

inline void* Buffers::get_buffer_pointer(GLenum target, GLenum binding)
{
	void* p; glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &p); return p;
}

inline void Buffers::get_buffer_sub_data(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, void* data)
{
	glGetBufferSubData(target, offset, size, data);
}

inline void* Buffers::map_buffer(GLenum target, GLenum binding, GLenum access)
{
	return glMapBuffer(target, access);
}

inline GLboolean Buffers::unmap_buffer(GLenum target, GLenum binding)
{
	return glUnmapBuffer(target);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Buffers::bind_buffer_base(GLenum target, GLuint index)
{
	glBindBufferBase(target, index, object_id());
	YAGLPP_GLAD_ERROR;
}

void Buffers::bind_buffer_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, object_id(), offset, size);
	YAGLPP_GLAD_ERROR;
}

void Buffers::flush_mapped_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glFlushMappedBufferRange(target, offset, length);
	YAGLPP_GLAD_ERROR;
}

void* Buffers::map_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	void* pResult = glMapBufferRange(target, offset, length, access);
	YAGLPP_GLAD_ERROR;
	return pResult;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Buffers::bind_buffer_base(GLenum target, GLuint index)
{
	glBindBufferBase(target, index, object_id());
}

inline void Buffers::bind_buffer_range(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, object_id(), offset, size);
}

inline void Buffers::flush_mapped_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length)
{
	glFlushMappedBufferRange(target, offset, length);
}

inline void* Buffers::map_buffer_range(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	return glMapBufferRange(target, offset, length, access);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Buffers::copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	// READ BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(rbinding, Get()));

	// WRITE BUFFER TARGET IS UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_COPY_WRITE_BUFFER_BINDING) != 0);

	glCopyBufferSubData(rtarget, GL_COPY_WRITE_BUFFER, roffset, woffset, size);
	YAGLPP_GLAD_ERROR;
}

void Buffers::copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLenum wtarget, GLenum wbinding, GLuint buffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	// READ BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(rbinding, Get()));

	// WRITE BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(wbinding, buffer));

	glCopyBufferSubData(rtarget, wtarget, roffset, woffset, size);
	YAGLPP_GLAD_ERROR;
}

void Buffers::CopySubData(GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	// READ BUFFER TARGET IS UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_COPY_READ_BUFFER_BINDING) != 0);

	// WRITE BUFFER TARGET IS UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_COPY_WRITE_BUFFER_BINDING) != 0);

	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, readOffset, writeOffset, size);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Buffers::copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	glCopyBufferSubData(rtarget, GL_COPY_WRITE_BUFFER, roffset, woffset, size);
}

inline void Buffers::copy_buffer_sub_data(GLenum rtarget, GLenum rbinding, GLenum wtarget, GLenum wbinding, GLuint buffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	glCopyBufferSubData(rtarget, wtarget, roffset, woffset, size);
}

inline void Buffers::CopySubData(GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, readOffset, writeOffset, size);
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
GLint64 Buffers::get_buffer_parameter64(GLenum target, GLenum binding, GLenum pname)
{
	// BUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLint64 iResult;
	glGetBufferParameteri64v(target, pname, &iResult);
	return iResult;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline GLint64 Buffers::get_buffer_parameter64(GLenum target, GLenum binding, GLenum pname)
{
	GLint64 i; glGetBufferParameteri64v(target, pname, &i); return i;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_BUFFERS_H
