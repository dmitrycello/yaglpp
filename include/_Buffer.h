#pragma once
#include "gladpp.h"
#include "_Object.h"
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
void readPixels(PixelPackBuffer& buffer, GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, GLintptr offset);
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
	GLuint _buffer_id()
	{
		return _object_id(glGenBuffers);
	}

	void _buffer_bind(GLuint* tls, GLenum target)
	{
		_bindBuffer(tls, target, _buffer_id());
	}

	void _buffer_rebind(GLuint* tls, GLenum target)
	{
		*tls = 0; _buffer_bind(tls, target);
	}

	static void _buffer_unbind(GLuint* tls, GLenum target)
	{
		_bindBuffer(tls, target, 0);
	}

	static GLuint* _tlsArrayBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsElementArrayBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static void _bindBuffer(GLuint* tls, GLenum target, GLuint buffer);
	void _bufferData(GLuint* tls, GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	void _bufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
	GLint _getBufferParameter(GLuint* tls, GLenum target, GLenum pname);
	void* _getBufferPointer(GLuint* tls, GLenum target);
	void _getBufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, void* data);
	void* _mapBuffer(GLuint* tls, GLenum target, GLenum access);
	GLboolean _unmapBuffer(GLuint* tls, GLenum target);

#ifdef GL_VERSION_2_1
	friend void readPixels(GLint, GLint, GLsizei, GLsizei, ReadPixelsFormat, ReadPixelsType, _Out_ void*);
	friend void readPixels(PixelPackBuffer&, GLint, GLint, GLsizei, GLsizei, ReadPixelsFormat, ReadPixelsType, GLintptr);
	static GLuint* _tlsPixelPackBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsPixelUnpackBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	GLuint _buffer_base(GLuint* tls, GLenum target)
	{
		GLuint u = _buffer_id(); *tls = u; return u;
	}

	static GLuint* _tlsTransformFeedbackBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	void _bindBufferBase(GLuint* tls, GLenum target, GLuint index);
	void _bindBufferRange(GLuint* tls, GLenum target, GLuint index, GLintptr offset, GLsizeiptr size);
	void _flushMappedBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length);
	void* _mapBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	static GLuint* _tlsCopyReadBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsCopyWriteBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsTextureBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsUniformBuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	void _buffer_copy(GLuint* tls, GLuint* ntls, GLenum ntarget)
	{
		GLuint u = _buffer_id(); if (*tls == u) *tls = 0;
		_bindBuffer(ntls, ntarget, u);
	}

	void _copyBufferSubData(GLuint* rtls, GLenum rtarget, GLuint* wtls, GLenum wtarget, _Buffer& wbuffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size);
	void _copyWriteBufferData(GLuint* tls, GLsizeiptr size, const void* data, GLenum usage);
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	GLint64 _getBufferParameter64(GLuint* tls, GLenum target, GLenum pname);
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

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to determine if a name corresponds to a buffer object*/
	__declspec(property(get = isBuffer)) GLboolean buffer;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_1
	/*(3.1) Determines via API if the buffer object is currently bound to copy read buffer target
	@return True if buffer object currently bound to copy read buffer target, or false otherwise*/
	GLboolean isCopyReadBufferBinding()
	{
		return _object_id() == _getInteger(GL_COPY_READ_BUFFER_BINDING);
	}

	/*(3.1) Determines via API if the buffer object is currently bound to copy write buffer target
	@return True if buffer object currently bound to copy write buffer target, or false otherwise*/
	GLboolean isCopyWriteBufferBinding()
	{
		return _object_id() == _getInteger(GL_COPY_WRITE_BUFFER_BINDING);
	}
#endif // #ifdef GL_VERSION_3_1
}; // class _Buffer : public _Object

#ifndef _DEBUG
inline void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, _Out_ void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, data);
}

inline void _Buffer::_bindBuffer(GLuint* tls, GLenum target, GLuint buffer)
{
	if (*tls == buffer) return;
	glBindBuffer(target, buffer); *tls = buffer;
}

inline void _Buffer::_bufferData(GLuint* tls, GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_buffer_bind(tls, target);
	glBufferData(target, size, data, usage);
}

inline void _Buffer::_bufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_buffer_bind(tls, target);
	glBufferSubData(target, offset, size, data);
}

inline GLint _Buffer::_getBufferParameter(GLuint* tls, GLenum target, GLenum pname)
{
	_buffer_bind(tls, target);
	GLint i; glGetBufferParameteriv(target, pname, &i); return i;
}

inline void* _Buffer::_getBufferPointer(GLuint* tls, GLenum target)
{
	_buffer_bind(tls, target);
	void* p; glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &p); return p;
}

inline void _Buffer::_getBufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, void* data)
{
	_buffer_bind(tls, target);
	glGetBufferSubData(target, offset, size, data);
}

inline void* _Buffer::_mapBuffer(GLuint* tls, GLenum target, GLenum access)
{
	_buffer_bind(tls, target);
	return glMapBuffer(target, access);
}

inline GLboolean _Buffer::_unmapBuffer(GLuint* tls, GLenum target)
{
	_buffer_bind(tls, target);
	return glUnmapBuffer(target);
}
#endif // #ifndef _DEBUG

#if !defined _DEBUG && defined GL_VERSION_2_1
inline void readPixels(PixelPackBuffer& buffer, GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, GLintptr offset)
{
	((_Buffer&)buffer)._buffer_bind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, (void*)offset);
}
#endif // #if !defined _DEBUG && defined GL_VERSION_2_1

#if !defined _DEBUG && defined GL_VERSION_3_0
inline void _Buffer::_bindBufferBase(GLuint* tls, GLenum target, GLuint index)
{
	glBindBufferBase(target, index, _buffer_base(tls, target));
}

inline void _Buffer::_bindBufferRange(GLuint* tls, GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, _buffer_base(tls, target), offset, size);
}

inline void _Buffer::_flushMappedBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length)
{
	_buffer_bind(tls, target);
	glFlushMappedBufferRange(target, offset, length);
}

inline void* _Buffer::_mapBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	_buffer_bind(tls, target);
	return glMapBufferRange(target, offset, length, access);
}
#endif // #if !defined _DEBUG && defined GL_VERSION_3_0

#if !defined _DEBUG && defined GL_VERSION_3_1
inline void _Buffer::_copyWriteBufferData(GLuint* tls, GLsizeiptr size, const void* data, GLenum usage)
{
	_buffer_copy(tls, _tlsCopyWriteBuffer(), GL_COPY_WRITE_BUFFER);
	glBufferData(GL_COPY_WRITE_BUFFER, size, data, usage);
}
#endif // #if !defined _DEBUG && defined GL_VERSION_3_1

#if !defined _DEBUG && defined GL_VERSION_3_2
inline GLint64 _Buffer::_getBufferParameter64(GLuint* tls, GLenum target, GLenum pname)
{
	_buffer_bind(tls, target);
	GLint64 i; glGetBufferParameteri64v(target, pname, &i); return i;
}
#endif // #if !defined _DEBUG && defined GL_VERSION_3_2
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
