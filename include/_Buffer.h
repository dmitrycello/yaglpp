#pragma once
#include "_Object.h"
#include "DataStore.h"
#ifndef GL_COPY_READ_BUFFER_BINDING
#define GL_COPY_READ_BUFFER_BINDING 0x8F36
#endif // #ifndef GL_COPY_READ_BUFFER_BINDING
#ifndef GL_COPY_WRITE_BUFFER_BINDING
#define GL_COPY_WRITE_BUFFER_BINDING 0x8F37
#endif // #ifndef GL_COPY_WRITE_BUFFER_BINDING
#ifndef GL_TEXTURE_BUFFER_BINDING
#define GL_TEXTURE_BUFFER_BINDING 0x8C2A
#endif // #ifndef GL_TEXTURE_BUFFER_BINDING
namespace gl {
/*GLAD buffer access policy enumerator*/
enum class BufferAccess : GLenum
{
	/*Indicates that the returned pointer may be used to read buffer object data*/
	ReadOnly = GL_READ_ONLY,

	/*Indicates that the returned pointer may be used to read and to modify buffer object data*/
	ReadWrite = GL_READ_WRITE,

	/*Indicates that the returned pointer may be used to modify buffer object data*/
	WriteOnly = GL_WRITE_ONLY,
};

/*GLAD buffer expected usage pattern enumerator*/
enum class BufferUsage : GLenum
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

/*(1) Reads a block of pixels from the frame buffer into client memory data store. Unbinds pixel back buffer if bound
@param Specifies the window x coordinate of the first pixel that is read from the frame buffer
@param Specifies the window y coordinate of the first pixel that is read from the frame buffer
@param Specifies the width of the pixel rectangle
@param Specifies the height of the pixel rectangle
@param Specifies the format of the pixel data
@param Specifies the data type of the pixel data
@param [out] Specifies the pointer to the pixel data
@param Specifies the number of commponents in returning pixel array, default RGBA*/
void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, _Out_ void* data);

#ifdef GL_VERSION_2_1
/*(2) (2.1) Read a block of pixels from the frame buffer into pixel pack buffer object's data store
@param Specifies the pixel pack buffer to write into
@param Specifies the window x coordinate of the first pixel that is read from the frame buffer
@param Specifies the window y coordinate of the first pixel that is read from the frame buffer
@param Specifies the width of the pixel rectangle
@param Specifies the height of the pixel rectangle
@param Specifies the format of the pixel data
@param Specifies the data type of the pixel data
@param Specifies the byte offset into the PBO object's data store*/
void readPixels(PixelPackBuffer& ppb, GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, GLintptr offset);
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
/*(3.0) GLAD access buffer flag bitmask enumerator*/
enum class BufferFlags : GLbitfield
{
	/*(3.0) Indicates that the returned pointer may be used to read buffer object data. No GL error is generated if the pointer is used to query a mapping which excludes this flag, but the result is undefined and system errors (possibly including program termination) may occur*/
	MapReadBit = GL_MAP_READ_BIT,

	/*(3.0) Indicates that the returned pointer may be used to modify buffer object data. No GL error is generated if the pointer is used to modify a mapping which excludes this flag, but the result is undefined and system errors (possibly including program termination) may occur*/
	MapWriteBit = GL_MAP_WRITE_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the previous contents of the specified range may be discarded. Data within this range are undefined with the exception of subsequently written data. No GL error is generated if subsequent GL operations access unwritten data, but the result is undefined and system errors (possibly including program termination) may occur. This flag may not be used in combination with <MapReadBit>*/
	MapInvalidateRangeBit = GL_MAP_INVALIDATE_RANGE_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the previous contents of the entire buffer may be discarded. Data within the entire buffer are undefined with the exception of subsequently written data. No GL error is generated if subsequent GL operations access unwritten data, but the result is undefined and system errors (possibly including program termination) may occur. This flag may not be used in combination with <MapReadBit>*/
	MapInvalidateBufferBit = GL_MAP_INVALIDATE_BUFFER_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that one or more discrete subranges of the mapping may be modified. When this flag is set, modifications to each subrange must be explicitly flushed by calling <flushMappedBufferRange>. No GL error is set if a subrange of the mapping is modified and not flushed, but data within the corresponding subrange of the buffer are undefined. This flag may only be used in conjunction with <MapWriteBit>. When this option is selected, flushing is strictly limited to regions that are explicitly indicated with calls to <flushMappedBufferRange> prior to unmap; if this option is not selected <unmapBuffer> will automatically flush the entire mapped range when called*/
	MapFlushExplicitBit = GL_MAP_FLUSH_EXPLICIT_BIT,

	/*(3.0) The optional bit flag used to modify the mapping. Indicates that the GL should not attempt to synchronize pending operations on the buffer prior to returning from <mapBufferRange>. No GL error is generated if pending operations which source or modify the buffer overlap the mapped region, but the result of such previous and any subsequent operations is undefined*/
	MapUnsynchronizedBit = GL_MAP_UNSYNCHRONIZED_BIT,
};

/*(3.0) Constant expression BufferFlags bitwise OR operator, combines multiple BufferFlags flags into bitfield mask
@param BufferFlags bitmask enumerator 1
@param BufferFlags bitmask enumerator 2
@return Resulting bitmask BufferFlags enumerator*/
constexpr BufferFlags operator | (BufferFlags flag1, BufferFlags flag2)
{
	return (BufferFlags)((GLbitfield)flag1 | (GLbitfield)flag2);
}

/*(3.0) Constant expression BufferFlags bitwise AND operator, checks the bitmask against the flag
@param Bitmask BufferFlags bitmask enumerator
@param Query BufferFlags bitmask enumerator
@return True if query flag exists in the bitmask enumerator, false otherwise*/
constexpr GLboolean operator & (BufferFlags mask, BufferFlags flags)
{
	return ((GLbitfield)mask & (GLbitfield)flags) > 0;
}
#endif // #ifdef GL_VERSION_3_0

/*OpenGL buffer object abstract class derived from <_Object>*/
class _Buffer : public _Object
{
protected:
	friend class _Texture;
	friend class VertexAttrib;
	void _bindBuffer(GLenum target, GLenum binding);
	void _bufferData(GLenum target, GLenum binding, GLsizeiptr size, const void* data, GLenum usage);
	void _bufferSubData(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, const void* data);
	GLint _getBufferParameter(GLenum target, GLenum binding, GLenum pname);
	void* _getBufferPointer(GLenum target, GLenum binding);
	void _getBufferSubData(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, void* data);
	void* _mapBuffer(GLenum target, GLenum binding, GLenum access);
	void _unbindBuffer(GLenum target, GLenum binding);
	static void _unbindTarget(GLenum target, GLenum binding);
	GLboolean _unmapBuffer(GLenum target, GLenum binding);
	GLuint _buffer_id()
	{
		return _object_id(glGenBuffers);
	}

	void _setBufferBinding(GLenum target, GLenum binding, GLboolean bind)
	{
		(bind) ? _bindBuffer(target, binding) : _unbindBuffer(target, binding);
	}

#ifdef GL_VERSION_2_1
	friend void readPixels(GLint, GLint, GLsizei, GLsizei, ReadPixelsFormat, ReadPixelsType, _Out_ void*);
	friend void readPixels(PixelPackBuffer&, GLint, GLint, GLsizei, GLsizei, ReadPixelsFormat, ReadPixelsType, GLintptr);
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	void _bindBufferBase(GLenum target, GLuint index);
	void _bindBufferRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size);
	void _flushMappedBufferRange(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length);
	void* _mapBufferRange(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length, GLbitfield access);
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	void _copyBufferSubData(GLenum rtarget, GLenum rbinding, GLenum wtarget, GLenum wbinding, _Buffer& wbuffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size);
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	GLint64 _getBufferParameter64(GLenum target, GLenum binding, GLenum pname);
#endif // #ifdef 

public:
	/*Cleans up the valid buffer object*/
	~_Buffer()
	{
		if (isObject())
		{
			deleteBuffer();
		}
	}

	/*Explicitly deletes previously generated single buffer object*/
	void deleteBuffer()
	{
		_object_delete(glDeleteBuffers);
	}

	/*Explicitly generates single buffer object*/
	void genBuffer()
	{
		_object_gen(glGenBuffers);
	}

	/*Determines if a name corresponds to a buffer object. Used as a getter of <buffer> property
	@return True if active buffer object, false otherwise*/
	GLboolean isBuffer()
	{
		return glIsBuffer(_object_id());
	}

	/*Sets the creation state of the buffer object, only if current state is opposite. Depending of the flag value, calls <genBuffer> or <deleteBuffer> functions. Used as a setter of <buffer> property
	@param True to generate buffer object name, false to delete buffer object*/
	void setBuffer(GLboolean gen);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for creation state of the buffer object*/
	__declspec(property(get = isBuffer, put = setBuffer)) GLboolean buffer;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_1
	/*(3.1) (1) Directly binds and initializes buffer object using copy-write target with the valid DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void copyWriteBufferData(DataStore& dataStore, BufferUsage usage)
	{
		copyWriteBufferData((GLsizeiptr)dataStore.getSize(), dataStore.getData(0), usage);
	}

	/*(3.1) (2) Directly initializes buffer object using copy-write target
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void copyWriteBufferData(GLsizeiptr size, _Pre_maybenull_ const void* data, BufferUsage usage);

	/*(3.1) Determines if the buffer object is currently bound to copy read buffer target. Used as a getter of <copyReadBufferBinding> property
	@return True if buffer object currently bound to copy read buffer target, false otherwise*/
	GLboolean isCopyReadBufferBinding()
	{
		return _object_id() == _getInteger(GL_COPY_READ_BUFFER_BINDING);
	}

	/*(3.1) Determines if the buffer object is currently bound to copy write buffer target. Used as a setter of <copyWriteBufferBinding> property
	@return True if buffer object currently bound to copy write buffer target, false otherwise*/
	GLboolean isCopyWriteBufferBinding()
	{
		return _object_id() == _getInteger(GL_COPY_WRITE_BUFFER_BINDING);
	}

	/*(3.1) Sets the copy read binding state of the buffer object, only if current state is opposite. Used as a setter of <copyReadBufferBinding> property
	@param True to bind the object to copy read target, false to unbind*/
	void setCopyReadBufferBinding(GLboolean bind)
	{
		_setBufferBinding(GL_COPY_READ_BUFFER, GL_COPY_READ_BUFFER_BINDING, bind);
	}

	/*(3.1) Sets the copy write binding state of the buffer object, only if current state is opposite. Used as a setter of <copyWriteBufferBinding> property
	@param True to bind the object to copy write target, false to unbind*/
	void setCopyWriteBufferBinding(GLboolean bind)
	{
		_setBufferBinding(GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER_BINDING, bind);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-write property for copy read binding state of the buffer object*/
	__declspec(property(get = isCopyReadBufferBinding, put = setCopyReadBufferBinding)) GLboolean copyReadBufferBinding;

	/*(3.1) Read-write property for copy write binding state of the buffer object*/
	__declspec(property(get = isCopyWriteBufferBinding, put = setCopyWriteBufferBinding)) GLboolean copyWriteBufferBinding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_1
}; // class _Buffer : public _Object

#if !defined(_DEBUG) && defined(GL_VERSION_3_0)
inline void _Buffer::_bindBufferBase(GLenum target, GLuint index)
{
	glBindBufferBase(target, index, _buffer_id());
}

inline void _Buffer::_bindBufferRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, _buffer_id(), offset, size);
}
#endif // #if defined(_DEBUG) && defined(GL_VERSION_3_0)
} // namespace gl

#ifndef YAGLPP_BUILD_LIB
#include "ArrayBuffer.h"
#include "ElementArrayBuffer.h"
#include "PixelPackBuffer.h"
#include "PixelUnpackBuffer.h"
#include "TransformFeedbackBuffer.h"
#include "TextureBuffer.h"
#include "UniformBuffer.h"
#endif // #ifdef YAGLPP_BUILD
