#pragma once
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

/*(3.0) GLAD type and color framebuffer attachment point enumerator*/
enum class FramebufferAttachment : GLenum
{
	/*(3.0) Framebuffer depth attachment type*/
	DepthAttachment = GL_DEPTH_ATTACHMENT,

	/*(3.0) Framebuffer stencil attachment type*/
	StencilAttachment = GL_STENCIL_ATTACHMENT,

	/*(3.0) Framebuffer depth and stencil attachment type*/
	DepthStencilAttachment = GL_DEPTH_STENCIL_ATTACHMENT,

	/*(3.0) Framebuffer color attachment unit 0*/
	ColorAttachment0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	ColorAttachment1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	ColorAttachment2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	ColorAttachment3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	ColorAttachment4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	ColorAttachment5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	ColorAttachment6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	ColorAttachment7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	ColorAttachment8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	ColorAttachment9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	ColorAttachment10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	ColorAttachment11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	ColorAttachment12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	ColorAttachment13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	ColorAttachment14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	ColorAttachment15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	ColorAttachment16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	ColorAttachment17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	ColorAttachment18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	ColorAttachment19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	ColorAttachment20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	ColorAttachment21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	ColorAttachment22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	ColorAttachment23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	ColorAttachment24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	ColorAttachment25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	ColorAttachment26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	ColorAttachment27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	ColorAttachment28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	ColorAttachment29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	ColorAttachment30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	ColorAttachment31 = GL_COLOR_ATTACHMENT31,
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

/*(3.0) Constant expression converting index value to color attachment unit within <FramebufferAttachment> enumerator
@param The index of color attachment unit, must be between 0 and value returned by <getMaxColorAttachments> minus 1
@return Color attachment unit value within <FramebufferAttachment> enumerator*/
constexpr FramebufferAttachment framebufferAttachment(ColorAttachment index)
{
	return (FramebufferAttachment)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) OpenGL framebuffer object abstract class derived from <_Object>*/
class _Framebuffer : public _Object
{
protected:
	void _bindFramebuffer(GLenum target, GLenum binding);
	static void _blitFramebuffer(_Framebuffer& fbo, GLenum target, GLenum binding, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter);
	GLenum _checkFramebufferStatus(GLenum target, GLenum binding);
	void _framebufferRenderbuffer(GLenum target, GLenum binding, GLenum attachment, Renderbuffer* renderbuffer);
	void _framebufferTexture1D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level);
	void _framebufferTexture2D(GLenum target, GLenum binding, GLenum attachment, GLenum textarget, _Texture& texture, GLint level);
	void _framebufferTexture3D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer);
	void _framebufferTextureLayer(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer);
	GLint _getFramebufferAttachmentParameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname);
	GLboolean _isFramebufferBinding(GLenum binding);
	void _unbindFramebuffer(GLenum target, GLenum binding);
	static void _unbindTarget(GLenum target, GLenum binding);
	GLuint _framebuffer_id()
	{
		return _object_id(glGenFramebuffers);
	}

	void _setFramebufferBinding(GLenum target, GLenum binding, GLboolean bind)
	{
		(bind) ? _bindFramebuffer(target, binding) : _unbindFramebuffer(target, binding);
	}

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

	/*(3.0) Determines if a name corresponds to a framebuffer object. Used as a getter of <framebuffer> property
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

	/*Sets the creation state of the framebuffer object, only if current state is opposite. Depending of the flag value, calls <genFramebuffer> or <deleteFramebuffer> functions. Used as a setter of <framebuffer> property
	@param True to generate framebuffer object name, false to delete framebuffer object*/
	void setFramebuffer(GLboolean gen);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for creation state of the framebuffer object*/
	__declspec(property(get = isFramebuffer, put = setFramebuffer)) GLboolean framebuffer;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Framebuffer : public _Object
} // namespace gl
#endif // #ifdef GL_VERSION_3_0

#ifndef YAGLPP_BUILD_LIB
#include "Framebuffer.h"
#include "DrawFramebuffer.h"
#include "ReadFramebuffer.h"
#endif // #ifdef YAGLPP_BUILD
