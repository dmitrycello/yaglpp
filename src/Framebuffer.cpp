#define YAGLPP_BUILD_LIB
#include <yaglpp/_Framebuffer.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_0
namespace gl {
void _Framebuffer::_bindFramebuffer(GLuint* tls, GLenum target, GLuint id)
{
	if (*tls == id)
	{
		return;
	}
	if (target == GL_FRAMEBUFFER)
	{
		*_tlsDrawFramebuffer() = 0;
		*_tlsReadFramebuffer() = 0;
	}
	else
	{
		*_tlsFramebuffer() = 0;
	}
	glBindFramebuffer(target, id);
	_YAGLPP_GLAD_ERROR_;
	*tls = id;
}

#ifdef _DEBUG
void _Framebuffer::_blitFramebuffer(_Framebuffer& fbo, GLuint* tls, GLenum target, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
{
	fbo._framebuffer_bind(tls, target);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
	_YAGLPP_GLAD_ERROR_;
}

GLenum _Framebuffer::_checkFramebufferStatus(GLuint* tls, GLenum target)
{
	GLenum eResult = 0;
	_framebuffer_bind(tls, target);
	eResult = glCheckFramebufferStatus(target);
	_YAGLPP_GLAD_ERROR_;
	return eResult;
}

void _Framebuffer::_framebufferRenderbuffer(GLuint* tls, GLenum target, ColorAttachment index, Renderbuffer& renderbuffer)
{
	_framebuffer_bind(tls, target);
	glFramebufferRenderbuffer(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, GL_RENDERBUFFER, renderbuffer._renderbuffer_id());
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture1D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture1D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture2D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTexture3D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture3D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level, layer);
	_YAGLPP_GLAD_ERROR_;
}

void _Framebuffer::_framebufferTextureLayer(GLuint* tls, GLenum target, ColorAttachment index, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTextureLayer(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, texture._texture_id(), level, layer);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Framebuffer::_getFramebufferAttachmentParameter(GLuint* tls, GLenum target, ColorAttachment index, GLenum pname)
{
	GLint iResult = 0;
	_framebuffer_bind(tls, target);
	glGetFramebufferAttachmentParameteriv(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, pname, &iResult);
	_YAGLPP_GLAD_ERROR_;
	return iResult;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
