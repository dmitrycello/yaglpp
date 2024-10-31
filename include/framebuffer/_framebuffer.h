#pragma once
#include <yaglpp/glad/_object.h>
#ifdef YAGLPP_VERSION_3_0
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

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target*/
	FramebufferIncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
#endif // #ifdef YAGLPP_VERSION_3_2
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
	void _framebuffer_delete() {
		_object_delete(glDeleteFramebuffers);
	}
	void _framebuffer_dup(_Object& source) {
		_object_dup(glDeleteFramebuffers, source);
	}
	void _framebuffer_gen() {
		_object_gen(glGenFramebuffers, glDeleteFramebuffers, 1);
	}
	GLuint _framebuffer_id() {
		return _object_id(glGenFramebuffers, 1);
	}
	void _framebuffer_ref(_Object& source) {
		_object_ref(glDeleteFramebuffers, source);
	}
	void _framebuffer_set(GLenum target, GLenum binding, GLboolean bind) {
		(bind) ? _bindFramebuffer(target, binding) : _unbindFramebuffer(target, binding);
	}
	void _bindFramebuffer(GLenum target, GLenum binding);
	static void _blitFramebuffer(_Framebuffer& fbo, GLenum target, GLenum binding, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter);
	GLenum _checkFramebufferStatus(GLenum target, GLenum binding);
	static GLuint _framebufferBinding(GLenum binding);
	void _framebufferRenderbuffer(GLenum target, GLenum binding, GLenum attachment, Renderbuffer* renderbuffer);
	void _framebufferTexture1D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level);
	void _framebufferTexture2D(GLenum target, GLenum binding, GLenum attachment, GLenum textarget, _Texture& texture, GLint level);
	void _framebufferTexture3D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer);
	void _framebufferTextureLayer(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer);
	GLint _getFramebufferAttachmentParameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname);
	GLboolean _isFramebufferBinding(GLenum binding) const;
	void _unbindFramebuffer(GLenum target, GLenum binding);
	static void _unbindTarget(GLenum target, GLenum binding);

public:
	/*(3.0) Cleans up the valid framebuffer object*/
	~_Framebuffer()
	{
		_framebuffer_delete();
	}

	/*(3.0) Explicitly deletes previously generated single framebuffer object*/
	void deleteFramebuffer()
	{
		_framebuffer_delete();
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
		_framebuffer_gen();
	}

	/*(3.0) Gets the maximum number of the color attachment units of the framebuffer. The value must be at least 8
	@return The maximum of the color attachments*/
	static GLuint getMaxColorAttachments()
	{
		return _getInteger(GL_MAX_COLOR_ATTACHMENTS);
	}

	/*(3.0) Determines if a name corresponds to a framebuffer object. Used as a getter of <framebuffer> property
	@return True if active framebuffer object, false otherwise*/
	GLboolean isFramebuffer() const
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

/*(3.0) OpenGL framebuffer multi-object class derived from <_Objects>*/
class Framebuffers : public _Objects
{
protected:
	void _framebuffers_delete() {
		_objects_delete(glDeleteFramebuffers);
	}
	void _framebuffers_dup(_Objects& source) {
		_objects_dup(glDeleteFramebuffers, source);
	}
	void _framebuffers_gen(GLsizei n) {
		_objects_gen(glGenFramebuffers, glDeleteFramebuffers, n);
	}

public:
	/*(3.0) (1) Constructs an empty framebuffer multi-object*/
	Framebuffers() {}

	/*(3.0) (2) Constructs a copy of framebuffer multi-object*/
	Framebuffers(const Framebuffers& framebuffers)
	{
		_framebuffers_dup((_Objects&)framebuffers);
	}

	/*(3.0) (3) Constucts an initialized framebuffer multi-object*/
	Framebuffers(GLsizei n)
	{
		_framebuffers_gen(n);
	}

	/*(3.0) Cleans up the valid framebuffer multi-object*/
	~Framebuffers()
	{
		_framebuffers_delete();
	}

	/*(3.0) Duplicates a framebuffer multi-object increasing its reference count
	@param Specifies the source framebuffer multi-object*/
	void duplicateFramebuffers(const Framebuffers& framebuffers)
	{
		_framebuffers_dup((_Objects&)framebuffers);
	}

	/*(3.0) Deletes valid framebuffer multi-object*/
	void deleteFramebuffers()
	{
		_framebuffers_delete();
	}

	/*(3.0) Generates one or more framebuffer object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genFramebuffers(GLsizei n)
	{
		_framebuffers_gen(n);
	}

	/*(3.0) Retrieves a reference to the Framebuffer object from a valid multi-object
	@param Specifies the object name index*/
	Framebuffer& getFramebuffer(GLuint index) const
	{
#ifdef _DEBUG
		return (Framebuffer&)_objects_get(index, GL_FRAMEBUFFER);
#else // #ifdef _DEBUG
		return (Framebuffer&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Retrieves a reference to the ReadFramebuffer object from a valid multi-object
	@param Specifies the object name index*/
	ReadFramebuffer& getReadFramebuffer(GLuint index) const
	{
#ifdef _DEBUG
		return (ReadFramebuffer&)_objects_get(index, GL_READ_FRAMEBUFFER);
#else // #ifdef _DEBUG
		return (ReadFramebuffer&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Retrieves a reference to the DrawFramebuffer object from a valid multi-object
	@param Specifies the object name index*/
	DrawFramebuffer& getDrawFramebuffer(GLuint index) const
	{
#ifdef _DEBUG
		return (DrawFramebuffer&)_objects_get(index, GL_DRAW_FRAMEBUFFER);
#else // #ifdef _DEBUG
		return (DrawFramebuffer&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Checks if the source Framebuffers object is referencing the same multi-object
	@param The source multi-object
	@return True if duplicate multi-object*/
	GLboolean isDuplicate(const Framebuffers& source) const
	{
		return _objects_is((Framebuffers&)source);
	}
}; // class Framebuffers : public _Objects
} // namespace gl

#include <yaglpp/texture/_texture.h>
#include <yaglpp/glad/renderbuffer.h>
namespace gl {
#ifdef YAGLPP_IMPLEMENTATION
void _Framebuffer::_bindFramebuffer(GLenum target, GLenum binding)
{
	if (!_isFramebufferBinding(binding))
	{
		glBindFramebuffer(target, _framebuffer_id());
		YAGLPP_GLAD_ERROR;
	}
}

void _Framebuffer::_blitFramebuffer(_Framebuffer& fbo, GLenum target, GLenum binding, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
{
	fbo._bindFramebuffer(target, binding);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, (GLbitfield)mask, (GLenum)filter);
	YAGLPP_GLAD_ERROR;
}

GLenum _Framebuffer::_checkFramebufferStatus(GLenum target, GLenum binding)
{
	_bindFramebuffer(target, binding);
	GLenum eResult = glCheckFramebufferStatus(target);
	YAGLPP_GLAD_ERROR;
	return eResult;
}

GLuint _Framebuffer::_framebufferBinding(GLenum binding)
{
	GLuint uDraw, uRead;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&uDraw);
	YAGLPP_GLAD_ERROR;
	glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&uRead);
	YAGLPP_GLAD_ERROR;
	if (binding == GL_FRAMEBUFFER_BINDING)
	{
		return (uRead == uDraw) ? uRead : 0;
	}
	else if (uRead != uDraw)
	{
		return (binding == GL_READ_FRAMEBUFFER_BINDING) ? uRead : uDraw;
	}
	return 0;
}

void _Framebuffer::_framebufferRenderbuffer(GLenum target, GLenum binding, GLenum attachment, Renderbuffer* renderbuffer)
{
	_bindFramebuffer(target, binding);
	GLuint uId = (renderbuffer != nullptr) ? renderbuffer->_renderbuffer_id() : 0;
	glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, uId);
	YAGLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture1D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture1D(target, attachment, GL_TEXTURE_1D, texture._texture_id(), level);
	YAGLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture2D(GLenum target, GLenum binding, GLenum attachment, GLenum textarget, _Texture& texture, GLint level)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture2D(target, attachment, textarget, texture._texture_id(), level);
	YAGLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTexture3D(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer)
{
	_bindFramebuffer(target, binding);
	glFramebufferTexture3D(target, attachment, GL_TEXTURE_3D, texture._texture_id(), level, layer);
	YAGLPP_GLAD_ERROR;
}

void _Framebuffer::_framebufferTextureLayer(GLenum target, GLenum binding, GLenum attachment, _Texture& texture, GLint level, GLint layer)
{
	_bindFramebuffer(target, binding);
	glFramebufferTextureLayer(target, attachment, texture._texture_id(), level, layer);
	YAGLPP_GLAD_ERROR;
}

GLint _Framebuffer::_getFramebufferAttachmentParameter(GLenum target, GLenum binding, GLenum attachment, GLenum pname)
{
	GLint iResult;
	_bindFramebuffer(target, binding);
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

GLboolean _Framebuffer::_isFramebufferBinding(GLenum binding) const
{
	GLuint uBound = _framebufferBinding(binding);
	return (uBound > 0) && (uBound == _object_id());
}

void _Framebuffer::_unbindFramebuffer(GLenum target, GLenum binding)
{
	if (_isFramebufferBinding(binding))
	{
		glBindFramebuffer(target, 0);
		YAGLPP_GLAD_ERROR;
	}
}

void _Framebuffer::_unbindTarget(GLenum target, GLenum binding)
{
	if (_framebufferBinding(binding) != 0)
	{
		glBindFramebuffer(target, 0);
		YAGLPP_GLAD_ERROR;
	}
}

void _Framebuffer::setFramebuffer(GLboolean gen)
{
	if (gen == GL_FALSE)
	{
		_framebuffer_delete();
	}
	else if (!isObject())
	{
		_framebuffer_gen();
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0

#include <yaglpp/framebuffer/draw_framebuffer.h>
#include <yaglpp/framebuffer/framebuffer.h>
#include <yaglpp/framebuffer/read_framebuffer.h>
