#define YAGLPP_BUILD_LIB
#include <yaglpp/_Texture.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void _Texture::_activeTexture(GLenum target, GLenum binding, TextureUnit index)
{
	glActiveTexture(GL_TEXTURE0 + (GLenum)index);
	_YAGLPP_GLAD_ERROR_;
	_bindTexture(target, binding);
}

void _Texture::_bindTexture(GLenum target, GLenum binding)
{
	GLuint uBound, uId = _texture_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != uId)
	{
		glBindTexture(target, uId);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Texture::_compressedTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
}

void _Texture::_compressedTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexImage2D(plane, level, internalformat, width, height, 0, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexImage3D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexSubImage2D(plane, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_copyTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	_bindTexture(target, binding);
	glCopyTexImage1D(target, level, internalformat, x, y, width, 0);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_copyTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_bindTexture(target, binding);
	glCopyTexImage2D(plane, level, internalformat, x, y, width, height, 0);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_copyTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	_bindTexture(target, binding);
	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_copyTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_bindTexture(target, binding);
	glCopyTexSubImage2D(plane, level, xoffset, yoffset, x, y, width, height);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_copyTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_bindTexture(target, binding);
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getCompressedTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glGetCompressedTexImage(plane, level, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum format, GLenum type, void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glGetTexImage(plane, level, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Texture::_getTexLevelParameter(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum pname)
{
	GLint iData = 0;
	_bindTexture(target, binding);
	glGetTexLevelParameteriv(plane, level, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

GLint _Texture::_getTexParameter(GLenum target, GLenum binding, GLenum pname)
{
	GLint iData = 0;
	_bindTexture(target, binding);
	glGetTexParameteriv(target, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

GLfloat _Texture::_getTexParameterFloat(GLenum target, GLenum binding, GLenum pname)
{
	GLfloat fData = 0;
	_bindTexture(target, binding);
	glGetTexParameterfv(target, pname, &fData);
	_YAGLPP_GLAD_ERROR_;
	return fData;
}

void _Texture::_getTexParameter(GLenum target, GLenum binding, GLenum pname, GLint* param)
{
	_bindTexture(target, binding);
	glGetTexParameteriv(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getTexParameter(GLenum target, GLenum binding, GLenum pname, GLfloat* param)
{
	_bindTexture(target, binding);
	glGetTexParameterfv(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

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
	_YAGLPP_ASSERT_(false); // STB IMAGE FORMAT IS UNSUPPORTED
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
	_YAGLPP_ASSERT_(false); // STB IMAGE DEPTH IS UNSUPPORTED
	return 0;
}

void _Texture::_texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexImage2D(plane, level, internalformat, width, height, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texParameter(GLenum target, GLenum binding, GLenum pname, GLint param)
{
	_bindTexture(target, binding);
	glTexParameteri(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texParameter(GLenum target, GLenum binding, GLenum pname, GLfloat param)
{
	_bindTexture(target, binding);
	glTexParameterf(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texParameter(GLenum target, GLenum binding, GLenum pname, const GLint* param)
{
	_bindTexture(target, binding);
	glTexParameteriv(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texParameter(GLenum target, GLenum binding, GLenum pname, const GLfloat* param)
{
	_bindTexture(target, binding);
	glTexParameterfv(target, pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexSubImage2D(plane, level, xoffset, yoffset, width, height, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
#ifdef GL_VERSION_2_1
	_Buffer::_unbindTarget(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
#endif // #ifdef GL_VERSION_2_1

	_bindTexture(target, binding);
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_unbindTarget(GLenum target, GLenum binding)
{
	GLuint uBound;
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != 0)
	{
		glBindTexture(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Texture::_unbindTexture(GLenum target, GLenum binding)
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		glBindTexture(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Texture::setTexture(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteTexture();
		}
	}
	else if (gen == GL_TRUE)
	{
		genTexture();
	}
}

#ifdef _DEBUG
void _Texture::_compressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getCompressedTexImage(GLenum target, GLint level, void* pixels)
{
	glGetCompressedTexImage(target, level, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels)
{
	glGetTexImage(target, level, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Texture::_getTexLevelParameter(GLenum target, GLint level, GLenum pname)
{
	GLint iData = 0;
	glGetTexLevelParameteriv(target, level, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

void _Texture::_texImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG

#ifdef GL_VERSION_2_1
void _Texture::_compressedTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexImage2D(plane, level, internalformat, width, height, 0, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexImage3D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, internalformat, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexSubImage2D(plane, level, xoffset, yoffset, width, height, internalformat, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_compressedTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getCompressedTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glGetCompressedTexImage(plane, level, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_getTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glGetTexImage(plane, level, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexImage1D(target, level, internalformat, width, 0, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexImage2D(plane, level, internalformat, width, height, 0, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexSubImage2D(plane, level, xoffset, yoffset, width, height, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	buffer._bindBuffer(GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING);
	_bindTexture(target, binding);
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
void _Texture::_generateMipmap(GLenum target, GLenum binding)
{
	_bindTexture(target, binding);
	glGenerateMipmap(target);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
void _Texture::_texBuffer(GLenum internalformat, _Buffer* buffer)
{
	GLuint uId = (buffer != nullptr) ? buffer->_buffer_id() : 0;
	_bindTexture(GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_BINDING);
	glTexBuffer(GL_TEXTURE_BUFFER, internalformat, uId);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
void _Texture::_texImage2DMultisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	_bindTexture(target, binding);
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage3DMultisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	_bindTexture(target, binding);
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	_YAGLPP_GLAD_ERROR_;
}

#ifdef _DEBUG
void _Texture::_texImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	_YAGLPP_GLAD_ERROR_;
}

void _Texture::_texImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG
#endif // #ifdef GL_VERSION_3_2
} // namespace gl
