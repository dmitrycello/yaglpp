#define YAGLPP_BUILD_LIB
#include <yaglpp/_Texture.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
GLenum _Texture::_siFormat(StbImage& image)
{
	switch (image.getChannels())
	{
	case StbFormat::RgbAlpha:
		return GL_RGBA;

	case StbFormat::Rgb:
		return GL_RGB;

	case StbFormat::Grey:
		return GL_RED;

#ifdef GL_VERSION_3_0
	case StbFormat::GreyAlpha:
		return GL_RG;
#endif // #ifdef GL_VERSION_3_0
	}
	YAGLPP_ASSERT(false); // STB IMAGE FORMAT IS UNSUPPORTED
	return 0;
}

GLenum _Texture::_siType(StbImage& image)
{
	switch (image.getDepth())
	{
	case StbFormat::Unsigned8:
		return GL_UNSIGNED_BYTE;

	case StbFormat::Unsigned16:
		return GL_UNSIGNED_SHORT;

	case StbFormat::Float32:
		return GL_FLOAT;
	}
	YAGLPP_ASSERT(false); // STB IMAGE DEPTH IS UNSUPPORTED
	return 0;
}

#ifdef _DEBUG
void _Texture::_activeTexture(GLuint* tls, GLenum target, TextureUnit index)
{
	glActiveTexture((GLenum)index + GL_TEXTURE0);
	YAGLPP_GLAD_ERROR;
	_texture_rebind(tls, target);
}

void _Texture::_bindTexture(GLuint* tls, GLenum target, GLuint texture)
{
	if (*tls == texture)
	{
		return;
	}
	glBindTexture(target, texture);
	YAGLPP_GLAD_ERROR;
	*tls = texture;
}

void _Texture::_compressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glCompressedTexImage2D(plane, level, internalformat, width, height, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage3D(GLuint* tls, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage1D(GLuint* tls, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, GL_TEXTURE_1D);
	glCompressedTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glCompressedTexSubImage2D(plane, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage3D(GLuint* tls, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_copyTexImage1D(GLuint* tls, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	_texture_bind(tls, GL_TEXTURE_1D);
	glCopyTexImage1D(GL_TEXTURE_1D, level, internalformat, x, y, width, 0);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_copyTexImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_texture_bind(tls, target);
	glCopyTexImage2D(plane, level, internalformat, x, y, width, height, 0);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_copyTexSubImage1D(GLuint* tls, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	_texture_bind(tls, GL_TEXTURE_1D);
	glCopyTexSubImage1D(GL_TEXTURE_1D, level, xoffset, x, y, width);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_copyTexSubImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_texture_bind(tls, target);
	glCopyTexSubImage2D(plane, level, xoffset, yoffset, x, y, width, height);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_copyTexSubImage3D(GLuint* tls, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_texture_bind(tls, target);
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getCompressedTexImage(GLenum target, GLint level, void* pixels)
{
	glGetCompressedTexImage(target, level, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getCompressedTexImage(GLuint* tls, GLenum target, GLenum plane, GLint level, void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glGetCompressedTexImage(plane, level, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels)
{
	glGetTexImage(target, level, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getTexImage(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum format, GLenum type, void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target); // +GL_PIXEL_PACK_BUFFER
	glGetTexImage(plane, level, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

GLint _Texture::_getTexLevelParameter(GLenum target, GLint level, GLenum pname)
{
	GLint iData = 0;
	glGetTexLevelParameteriv(target, level, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

GLint _Texture::_getTexLevelParameter(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum pname)
{
	GLint iData = 0;
	_texture_bind(tls, target);
	glGetTexLevelParameteriv(plane, level, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

GLint _Texture::_getTexParameter(GLuint* tls, GLenum target, GLenum pname)
{
	GLint iData = 0;
	_texture_bind(tls, target);
	glGetTexParameteriv(target, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

GLfloat _Texture::_getTexParameterFloat(GLuint* tls, GLenum target, GLenum pname)
{
	GLfloat fData = 0;
	_texture_bind(tls, target);
	glGetTexParameterfv(target, pname, &fData);
	YAGLPP_GLAD_ERROR;
	return fData;
}

void _Texture::_getTexParameter(GLuint* tls, GLenum target, GLenum pname, GLint* param)
{
	_texture_bind(tls, target);
	glGetTexParameteriv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getTexParameter(GLuint* tls, GLenum target, GLenum pname, GLfloat* param)
{
	_texture_bind(tls, target);
	glGetTexParameterfv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage1D(GLuint* tls, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, GL_TEXTURE_1D);
	glTexImage1D(GL_TEXTURE_1D, level, internalformat, width, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glTexImage2D(plane, level, internalformat, width, height, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage3D(GLuint* tls, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target);
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texParameter(GLuint* tls, GLenum target, GLenum pname, GLint param)
{
	_texture_bind(tls, target);
	glTexParameteri(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texParameter(GLuint* tls, GLenum target, GLenum pname, GLfloat param)
{
	_texture_bind(tls, target);
	glTexParameterf(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texParameter(GLuint* tls, GLenum target, GLenum pname, const GLint* param)
{
	_texture_bind(tls, target);
	glTexParameteriv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texParameter(GLuint* tls, GLenum target, GLenum pname, const GLfloat* param)
{
	_texture_bind(tls, target);
	glTexParameterfv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage1D(GLuint* tls, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, GL_TEXTURE_1D);
	glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target); // +GL_PIXEL_UNPACK_BUFFER 
	glTexSubImage2D(plane, level, xoffset, yoffset, width, height, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage3D(GLuint* tls, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_buffer_unbind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
#endif // #ifdef GL_VERSION_2_1

	_texture_bind(tls, target); // +GL_PIXEL_UNPACK_BUFFER 
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

#ifdef GL_VERSION_2_1
void _Texture::_compressedTexImage1D(GLuint* tls, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, GL_TEXTURE_1D);
	glCompressedTexImage1D(GL_TEXTURE_1D, level, internalformat, width, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glCompressedTexImage2D(plane, level, internalformat, width, height, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexImage3D(GLuint* tls, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage1D(GLuint* tls, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, GL_TEXTURE_1D);
	glCompressedTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glCompressedTexSubImage2D(plane, level, xoffset, yoffset, width, height, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_compressedTexSubImage3D(GLuint* tls, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getCompressedTexImage(GLuint* tls, GLenum target, GLenum plane, GLint level, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
	_texture_bind(tls, target);
	glGetCompressedTexImage(plane, level, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_getTexImage(GLuint* tls, GLenum target, GLenum plane, GLint level, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER);
	_texture_bind(tls, target);
	glGetTexImage(plane, level, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage1D(GLuint* tls, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, GL_TEXTURE_1D);
	glTexImage1D(GL_TEXTURE_1D, level, internalformat, width, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glTexImage2D(plane, level, internalformat, width, height, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage3D(GLuint* tls, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage1D(GLuint* tls, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, GL_TEXTURE_1D);
	glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage2D(GLuint* tls, GLenum target, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glTexSubImage2D(plane, level, xoffset, yoffset, width, height, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texSubImage3D(GLuint* tls, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._buffer_bind(_Buffer::_tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER);
	_texture_bind(tls, target);
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
void _Texture::_generateMipmap(GLuint* tls, GLenum target)
{
	_texture_bind(tls, target);
	glGenerateMipmap(target);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void _Texture::_texBuffer(GLenum internalformat, GLuint buffer)
{
	glTexBuffer(GL_TEXTURE_BUFFER, internalformat, buffer);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texBuffer(GLenum internalformat, _Buffer& buffer)
{
	buffer._buffer_bind(_Buffer::_tlsTextureBuffer(), GL_TEXTURE_BUFFER);
	_texture_bind(_tlsBufferTexture(), GL_TEXTURE_BUFFER);
	glTexBuffer(GL_TEXTURE_BUFFER, internalformat, buffer._buffer_id());
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
void _Texture::_texImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage2DMultisample(GLuint* tls, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	_texture_bind(tls, GL_TEXTURE_2D_MULTISAMPLE);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalformat, width, height, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void _Texture::_texImage3DMultisample(GLuint* tls, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	_texture_bind(tls, GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	glTexImage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, internalformat, width, height, depth, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_3_2
#endif // #ifdef _DEBUG
} // namespace gl
