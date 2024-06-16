#pragma once
#include "gladpp.h"
#include "_Object.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) GLAD framebuffer attached image object type enumerator*/
enum class FramebufferAttachmentType : GLenum
{
	/*(3.0) No attached unit*/
	None = GL_NONE,

	/*(3.0) Attached unit is texture object*/
	Texture = GL_TEXTURE,

	/*(3.0) Attached unit is renderbuffer object*/
	Renderbuffer = GL_RENDERBUFFER,

	/*(3.0) The default framebuffer is used for drawing*/
	FramebufferDefault = GL_FRAMEBUFFER_DEFAULT,
};

/*(3.0) GLAD framebuffer completeness status enumerator*/
enum class FramebufferCompletenessStatus : GLenum
{
	/*(3.0) Returned if the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist*/
	FramebufferUndefined = GL_FRAMEBUFFER_UNDEFINED,

	/*(3.0) Returned if the specified framebuffer is complete*/
	FramebufferComplete = GL_FRAMEBUFFER_COMPLETE,
	
	/*(3.0) Returned if any of the framebuffer attachment points are framebuffer incomplete*/
	FramebufferIncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,

	/*(3.0) Returned if the framebuffer does not have at least one image attached to it*/
	FramebufferIncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,

	/*(3.0) Returned if the value of attachment object type is <None> for any color attachment point(s) named by draw buffer*/
	FramebufferIncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,

	/*(3.0) Returned read buffer is not <None>, and if the value of attachment object type is <None> for the color attachment point named by read buffer*/
	FramebufferIncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,

	/*(3.0) Returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions*/
	FramebufferUnsupported = GL_FRAMEBUFFER_UNSUPPORTED,

	/*(3.0) Returned if the number of samples is not the same for all attached renderbuffers*/
	FramebufferIncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,

#ifdef GL_VERSION_3_2
	/*(3.2) Returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target*/
	FramebufferIncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
#endif // #ifdef GL_VERSION_3_2
};

/*(3.0) OpenGL framebuffer object abstract class derived from <_Object>*/
class _Framebuffer : public _Object
{
protected:
	GLuint _framebuffer_id()
	{
		return _object_id(glGenFramebuffers);
	}

	void _framebuffer_bind(GLuint* tls, GLenum target)
	{
		_bindFramebuffer(tls, target, _framebuffer_id());
	}

	void _framebuffer_rebind(GLuint* tls, GLenum target)
	{
		*tls = 0; _framebuffer_bind(tls, target);
	}

	static void _framebuffer_unbind(GLuint* tls, GLenum target)
	{
		_bindFramebuffer(tls, target, 0);
	}

	static GLuint* _tlsDrawFramebuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsFramebuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static GLuint* _tlsReadFramebuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static void _bindFramebuffer(GLuint* tls, GLenum target, GLuint id);
	static void _blitFramebuffer(_Framebuffer& fbo, GLuint* tls, GLenum target, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter);
	GLenum _checkFramebufferStatus(GLuint* tls, GLenum target);
	void _framebufferRenderbuffer(GLuint* tls, GLenum target, ColorAttachment index, Renderbuffer& renderbuffer);
	void _framebufferTexture1D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level);
	void _framebufferTexture2D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level);
	void _framebufferTexture3D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level, GLint layer);
	void _framebufferTextureLayer(GLuint* tls, GLenum target, ColorAttachment index, _Texture& texture, GLint level, GLint layer);
	GLint _getFramebufferAttachmentParameter(GLuint* tls, GLenum target, ColorAttachment index, GLenum pname);

public:
	/*(3.0) Cleans up the valid framebuffer object*/
	~_Framebuffer()
	{
		if (isObject())
		{
			deleteFramebuffer();
		}
	}

	/*(3.0) Explicitly deletes previously generated single framebuffer object*/
	void deleteFramebuffer()
	{
		_object_delete(glDeleteFramebuffers);
	}

	/*(3.0) Disable enabled framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
	static void disableFramebufferSrgb()
	{
		_disable(GL_FRAMEBUFFER_SRGB);
	}

	/*(3.0) Enable framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
	static void enableFramebufferSrgb()
	{
		_enable(GL_FRAMEBUFFER_SRGB);
	}

	/*(3.0) Explicitly generates single framebuffer object*/
	void genFramebuffer()
	{
		_object_gen(glGenFramebuffers);
	}

	/*(3.0) Gets the maximum number of the color attachment units of the framebuffer. The value must be at least 8
	@return The maximum of the color attachments*/
	static GLuint getMaxColorAttachments()
	{
		return _getInteger(GL_MAX_COLOR_ATTACHMENTS);
	}

	/*(3.0) Determines via API if framebuffer object is currently active
	@return True if active framebuffer object, false otherwise*/
	GLboolean isFramebuffer()
	{
		return glIsFramebuffer(_object_id());
	}

	/*(3.0) Check if framebuffer SRGB server-side GL capability is enabled, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending
	@return True if framebuffer SRGB GL capability is enabled, false otherwise*/
	static GLboolean isFramebufferSrgb()
	{
		return _isEnabled(GL_FRAMEBUFFER_SRGB);
	}
}; // class _Framebuffer : public _Object
} // namespace gl

#include "_Texture.h"
#include "Renderbuffer.h"
namespace gl {
#ifndef _DEBUG
inline void _Framebuffer::_blitFramebuffer(_Framebuffer& fbo, GLuint* tls, GLenum target, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
{
	fbo._framebuffer_bind(tls, target);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
}

inline GLenum _Framebuffer::_checkFramebufferStatus(GLuint* tls, GLenum target)
{
	_framebuffer_bind(tls, target);
	return glCheckFramebufferStatus(target);
}

inline void _Framebuffer::_framebufferRenderbuffer(GLuint* tls, GLenum target, ColorAttachment index, Renderbuffer& renderbuffer)
{
	_framebuffer_bind(tls, target);
	glFramebufferRenderbuffer(target, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER + (GLenum)index, renderbuffer._renderbuffer_id());
}

inline void _Framebuffer::_framebufferTexture1D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture1D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level);
}

inline void _Framebuffer::_framebufferTexture2D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level);
}

inline void _Framebuffer::_framebufferTexture3D(GLuint* tls, GLenum target, ColorAttachment index, GLenum textarget, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTexture3D(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, textarget, texture._texture_id(), level, layer);
}

inline void _Framebuffer::_framebufferTextureLayer(GLuint* tls, GLenum target, ColorAttachment index, _Texture& texture, GLint level, GLint layer)
{
	_framebuffer_bind(tls, target);
	glFramebufferTextureLayer(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, texture._texture_id(), level, layer);
}

inline GLint _Framebuffer::_getFramebufferAttachmentParameter(GLuint* tls, GLenum target, ColorAttachment index, GLenum pname)
{
	_framebuffer_bind(tls, target);
	GLint i; glGetFramebufferAttachmentParameteriv(target, GL_COLOR_ATTACHMENT0 + (GLenum)index, pname, &i); return i;
}
#endif // #ifndef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_0

#ifndef YAGLPP_BUILD_LIB
#include "DrawFramebuffer.h"
#include "Framebuffer.h"
#include "ReadFramebuffer.h"
#endif // #ifdef YAGLPP_BUILD
