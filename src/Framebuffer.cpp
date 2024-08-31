#define YAGLPP_BUILD_LIB
#include <yaglpp/_Framebuffer.h>
#include <yaglpp/_Texture.h>
#include <yaglpp/Renderbuffer.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_0
namespace gl {
void _Framebuffer::_bindFramebuffer(GLenum target, GLenum binding)
{
	if (!_isFramebufferBinding(binding))
	{
		glBindFramebuffer(target, _framebuffer_id());
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Framebuffer::_blitFramebuffer(_Framebuffer& fbo, GLenum target, GLenum binding, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
{
	fbo._bindFramebuffer(target, binding);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
	_YAGLPP_GLAD_ERROR_;
}

GLenum _Framebuffer::_checkFramebufferStatus(GLenum target, GLenum binding)
{
	GLenum eResult = 0;
	_bindFramebuffer(target, binding);
	eResult = glCheckFramebufferStatus(target);
	_YAGLPP_GLAD_ERROR_;
	return eResult;
}

void _Framebuffer::_framebufferRenderbuffer(GLenum target, GLenum binding, GLenum attachment, Renderbuffer* renderbuffer)
{
	_bindFramebuffer(target, binding);
	GLuint uId = (renderbuffer != nullptr) ? renderbuffer->_renderbuffer_id() : 0;
	glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, uId);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture1D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture1D(target, attachment, GL_TEXTURE_1D, texture._texture_id(), level);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture2D(GLenum target, GLenum binding, GLenum attachment, GLenum textarget, _Texture& texture, GLint level)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture2D(target, attachment, textarget, texture._texture_id(), level);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture3D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture3D(target, attachment, GL_TEXTURE_3D, texture._texture_id(), level, layer);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTextureLayer(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer)
{
	_bindFramebuffer(target, binding);
	glFramebufferTextureLayer(target, attachment, texture._texture_id(), level, layer);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Framebuffer::_getFramebufferAttachmentParameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname)
{
	GLint iResult = 0;
	_bindFramebuffer(target, binding);
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, &iResult);
	_YAGLPP_GLAD_ERROR_;
	return iResult;
}

GLboolean _Framebuffer::_isFramebufferBinding(GLenum binding)
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		if (binding == GL_FRAMEBUFFER_BINDING)
		{
			glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&uBound);
			_YAGLPP_GLAD_ERROR_;
			return uBound == uId;
		}
		return GL_TRUE;
	}
	return GL_FALSE;
}

void _Framebuffer::_unbindFramebuffer(GLenum target, GLenum binding)
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		glBindFramebuffer(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Framebuffer::_unbindTarget(GLenum target, GLenum binding)
{
	GLuint uBound;
	glGetIntegerv(binding, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != 0)
	{
		glBindFramebuffer(target, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void _Framebuffer::setFramebuffer(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteFramebuffer();
		}
	}
	else if (gen == GL_TRUE)
	{
		genFramebuffer();
	}
}
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
