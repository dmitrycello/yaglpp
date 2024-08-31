#define YAGLPP_BUILD_LIB
#include <yaglpp/_Buffer.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, _Out_ void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Buffer::_bindBuffer(GLenum target, GLenum binding)
{
	GLuint uBound, uId = _buffer_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != uId)
	{
		glBindBuffer(target, uId);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Buffer::_bufferData(GLenum target, GLenum binding, GLsizeiptr size, const void* data, GLenum usage)
{
	_bindBuffer(target, binding);
	glBufferData(target, size, data, usage);
	_YAGLPP_GLAD_ERROR_;
}

void _Buffer::_bufferSubData(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, const void* data)
{
	_bindBuffer(target, binding);
	glBufferSubData(target, offset, size, data);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Buffer::_getBufferParameter(GLenum target, GLenum binding, GLenum pname)
{
	GLint iData = 0;
	_bindBuffer(target, binding);
	glGetBufferParameteriv(target, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

void* _Buffer::_getBufferPointer(GLenum target, GLenum binding)
{
	void* pData = nullptr;
	_bindBuffer(target, binding);
	glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &pData);
	_YAGLPP_GLAD_ERROR_;
	return pData;
}

void _Buffer::_getBufferSubData(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr size, void* data)
{
	_bindBuffer(target, binding);
	glGetBufferSubData(target, offset, size, data);
	_YAGLPP_GLAD_ERROR_;
}

void* _Buffer::_mapBuffer(GLenum target, GLenum binding, GLenum access)
{
	_bindBuffer(target, binding);
	void* pData = glMapBuffer(target, access);
	_YAGLPP_GLAD_ERROR_;
	return pData;
}

void _Buffer::_unbindBuffer(GLenum target, GLenum binding)
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		glBindBuffer(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Buffer::_unbindTarget(GLenum target, GLenum binding)
{
	GLuint uBound;
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != 0)
	{
		glBindBuffer(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

GLboolean _Buffer::_unmapBuffer(GLenum target, GLenum binding)
{
	_bindBuffer(target, binding);
	GLboolean bResult = glUnmapBuffer(target);
	_YAGLPP_GLAD_ERROR_;
	return bResult;
}

void _Buffer::setBuffer(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteBuffer();
		}
	}
	else if (gen == GL_TRUE)
	{
		genBuffer();
	}
}

#ifdef GL_VERSION_2_1
void readPixels(PixelPackBuffer& buffer, GLint x, GLint y, GLsizei width, GLsizei height, ReadPixelsFormat format, ReadPixelsType type, GLintptr offset)
{
	((_Buffer&)buffer)._bindBuffer(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
void _Buffer::_flushMappedBufferRange(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length)
{
	_bindBuffer(target, binding);
	glFlushMappedBufferRange(target, offset, length);
	_YAGLPP_GLAD_ERROR_;
}

void* _Buffer::_mapBufferRange(GLenum target, GLenum binding, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	_bindBuffer(target, binding);
	void* pData = glMapBufferRange(target, offset, length, access);
	_YAGLPP_GLAD_ERROR_;
	return pData;
}

#ifdef _DEBUG
void _Buffer::_bindBufferBase(GLenum target, GLuint index)
{
	glBindBufferBase(target, index, _buffer_id());
	_YAGLPP_GLAD_ERROR_;
}

void _Buffer::_bindBufferRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size)
{
	glBindBufferRange(target, index, _buffer_id(), offset, size);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void _Buffer::_copyBufferSubData(GLenum rtarget, GLenum rbinding, GLenum wtarget, GLenum wbinding, _Buffer& wbuffer, GLintptr roffset, GLintptr woffset, GLsizeiptr size)
{
	GLuint uBound, uId = _buffer_id();
	glGetIntegerv(rbinding, (GLint*)&uBound);
	if (uBound != uId)
	{
		rtarget = GL_COPY_READ_BUFFER; // Use copy read target if unbound
		glBindBuffer(GL_COPY_READ_BUFFER, uId);
		_YAGLPP_GLAD_ERROR_;
	}
	uId = wbuffer._buffer_id();
	glGetIntegerv(wbinding, (GLint*)&uBound);
	if (uBound != uId)
	{
		wtarget = GL_COPY_WRITE_BUFFER; // Use copy write target if unbound
		glBindBuffer(GL_COPY_WRITE_BUFFER, uId);
		_YAGLPP_GLAD_ERROR_;
	}
	glCopyBufferSubData(rtarget, wtarget, roffset, woffset, size);
	_YAGLPP_GLAD_ERROR_;
}

void _Buffer::copyWriteBufferData(GLsizeiptr size, _Pre_maybenull_ const void* data, BufferUsage usage)
{
	_bindBuffer(GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER_BINDING);
	glBufferData(GL_COPY_WRITE_BUFFER, size, data, (GLenum)usage);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
GLint64 _Buffer::_getBufferParameter64(GLenum target, GLenum binding, GLenum pname)
{
	GLint64 iData = 0;
	_bindBuffer(target, binding);
	glGetBufferParameteri64v(target, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}
#endif // #ifdef GL_VERSION_3_2
} // namespace gl
