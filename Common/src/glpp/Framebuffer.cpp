#define GLPP_BUILD_LIB
#include <glpp/_Framebuffer.h>
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
	GLPP_GLAD_ERROR;
	*tls = id;
}

#ifdef _DEBUG
void _Framebuffer::_blitFramebuffer(_Framebuffer& fbo, GLuint* tls, GLenum target, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
{
	fbo._framebuffer_bind(tls, target);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
	GLPP_GLAD_ERROR;
}

GLenum _Framebuffer::_checkFramebufferStatus(GLuint* tls, GLenum target)
{
	GLenum eResult = 0;
	_framebuffer_bind(tls, target);
	eResult = glCheckFramebufferStatus(target);
	GLPP_GLAD_ERROR;
	return eResult;
}

void _Framebuffer::_framebufferRenderbuffer(GLuint* tls, GLenum target, GLuint attachment, Renderbuffer& renderbuffer)
{
	_framebuffer_bind(tls, target);
	glFramebufferRenderbuffer(target, attachment + GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer._renderbuffer_id());
	GLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture1D(GLuint* tls, GLenum target, GLuint attachment, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture1D(target, attachment + GL_COLOR_ATTACHMENT0, textarget, texture._texture_id(), level);
	GLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture2D(GLuint* tls, GLenum target, GLuint attachment, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture2D(target, attachment + GL_COLOR_ATTACHMENT0, textarget, texture._texture_id(), level);
	GLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture3D(GLuint* tls, GLenum target, GLuint attachment, GLenum textarget, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture3D(target, attachment + GL_COLOR_ATTACHMENT0, textarget, texture._texture_id(), level, layer);
	GLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTextureLayer(GLuint* tls, GLenum target, GLuint attachment, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTextureLayer(target, attachment + GL_COLOR_ATTACHMENT0, texture._texture_id(), level, layer);
	GLPP_GLAD_ERROR;
}

GLint _Framebuffer::_getFramebufferAttachmentParameter(GLuint* tls, GLenum target, GLuint attachment, GLenum pname)
{
	GLint iResult = 0;
	_framebuffer_bind(tls, target);
	glGetFramebufferAttachmentParameteriv(target, attachment + GL_COLOR_ATTACHMENT0, pname, &iResult);
	GLPP_GLAD_ERROR;
	return iResult;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
