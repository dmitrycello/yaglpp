#define YAGLPP_BUILD_LIB
#include <yaglpp/_Buffer.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, _Out_ void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, data);
	YAGLPP_GLAD_ERROR;
}

void _Buffer::_bindBuffer(GLuint* tls, GLenum target, GLuint buffer)
{
	if (*tls != buffer)
	{
		glBindBuffer(target, buffer);
		YAGLPP_GLAD_ERROR;
		*tls = buffer;
	}
}

void _Buffer::_bufferData(GLuint* tls, GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_buffer_bind(tls, target);
	glBufferData(target, size, data, usage);
	YAGLPP_GLAD_ERROR;
}

void _Buffer::_bufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_buffer_bind(tls, target);
	glBufferSubData(target, offset, size, data);
	YAGLPP_GLAD_ERROR;
}

GLint _Buffer::_getBufferParameter(GLuint* tls, GLenum target, GLenum pname)
{
	GLint iData = 0;
	_buffer_bind(tls, target);
	glGetBufferParameteriv(target, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

void* _Buffer::_getBufferPointer(GLuint* tls, GLenum target)
{
	void* pData = nullptr;
	_buffer_bind(tls, target);
	glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &pData);
	YAGLPP_GLAD_ERROR;
	return pData;
}

void _Buffer::_getBufferSubData(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr size, void* data)
{
	_buffer_bind(tls, target);
	glGetBufferSubData(target, offset, size, data);
	YAGLPP_GLAD_ERROR;
}

void* _Buffer::_mapBuffer(GLuint* tls, GLenum target, GLenum access)
{
	_buffer_bind(tls, target);
	void* pData = glMapBuffer(target, access);
	YAGLPP_GLAD_ERROR;
	return pData;
}

GLboolean _Buffer::_unmapBuffer(GLuint* tls, GLenum target)
{
	_buffer_bind(tls, target);
	GLboolean bResult = glUnmapBuffer(target);
	YAGLPP_GLAD_ERROR;
	return bResult;
}
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_2_1
void readPixels(PixelPackBuffer& buffer, GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, GLintptr offset)
{
	((_Buffer&)buffer)._buffer_bind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_2_1

#if defined _DEBUG && defined GL_VERSION_3_0
void _Buffer::_bindBufferBase(GLuint* tls, GLenum target, GLuint index)
{
	glBindBufferBase(target, index, _buffer_base(tls, target));
	YAGLPP_GLAD_ERROR;
}

void _Buffer::_bindBufferRange(GLuint* tls, GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, _buffer_base(tls, target), offset, size);
	YAGLPP_GLAD_ERROR;
}

void _Buffer::_flushMappedBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length)
{
	_buffer_bind(tls, target);
	glFlushMappedBufferRange(target, offset, length);
	YAGLPP_GLAD_ERROR;
}

void* _Buffer::_mapBufferRange(GLuint* tls, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	_buffer_bind(tls, target);
	void* pData = glMapBufferRange(target, offset, length, access);
	YAGLPP_GLAD_ERROR;
	return pData;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void _Buffer::_copyBufferSubData(GLuint* rtls, GLenum rtarget, GLuint* wtls, GLenum wtarget, _Buffer& wbuffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	if (*rtls != _buffer_id())
	{
		rtarget = GL_COPY_READ_BUFFER; // Use copy read target if unbound
		_buffer_bind(_tlsCopyReadBuffer(), GL_COPY_READ_BUFFER);
	}
	if (*wtls != wbuffer._buffer_id())
	{
		wtarget = GL_COPY_WRITE_BUFFER; // Use copy write target if unbound
		wbuffer._buffer_bind(_tlsCopyWriteBuffer(), GL_COPY_WRITE_BUFFER);
	}
	glCopyBufferSubData(rtarget, wtarget, roffset, woffset, size);
	YAGLPP_GLAD_ERROR;
}

#ifdef _DEBUG
void _Buffer::_copyWriteBufferData(GLuint* tls, GLsizeiptr size, const void* data, GLenum usage)
{
	_buffer_copy(tls, _tlsCopyWriteBuffer(), GL_COPY_WRITE_BUFFER);
	glBufferData(GL_COPY_WRITE_BUFFER, size, data, usage);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG
#endif // #ifdef GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_2
GLint64 _Buffer::_getBufferParameter64(GLuint* tls, GLenum target, GLenum pname)
{
	GLint64 iData = 0;
	_buffer_bind(tls, target);
	glGetBufferParameteri64v(target, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
} // namespace gl
