#pragma once
#include <yaglpp/framebuffer/_framebuffer.h>
#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL read framebuffer object class derived from <_Framebuffer>*/
class ReadFramebuffer : public _Framebuffer
{
private:
	friend class Framebuffers;
	ReadFramebuffer(GLint name) { _object_set(name); }

public:
	/*(3.0) (1) Constructs an empty framebuffer object*/
	ReadFramebuffer() {}

	/*(3.0) (2) Constructs a copy of framebuffer object*/
	ReadFramebuffer(const ReadFramebuffer& source)
	{
		_framebuffer_dup((_Object&)source);
	}

	/*(3.0) Explicitly binds framebuffer object to its target, this also unbinds framebuffer binding. Does nothing if specified buffer is bound*/
	void bindFramebuffer()
	{
		_bindFramebuffer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING);
	}

	/*(3.0) Transfer a rectangle of pixel values from one region of a read framebuffer to another region of a draw framebuffer
	@param Specifies the destination draw framebuffer object
	@param Four parameters (x0, y0, x1, y1) of source rectangle of a read framebuffer
	@param Four parameters (x0, y0, x1, y1) of destination rectangle of a draw framebuffer
	@param The bitwise OR of the mask flags indicating which buffers are to be copied
	@param Specifies the interpolation to be applied if the image is stretched*/
	void blitFramebuffer(DrawFramebuffer& destination, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
	{
		bindFramebuffer();
		_blitFramebuffer((_Framebuffer&)destination, GL_DRAW_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER_BINDING, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	/*(3.0) Checks the completeness status of a framebuffer. Used as a getter of <checkFramebufferStatus> property
	@return The framebuffer completeness status value*/
	FramebufferCompletenessStatus checkFramebufferStatus()
	{
		return (FramebufferCompletenessStatus)_checkFramebufferStatus(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING);
	}

	/*(3.0) Detaches the image, if any, identified by the specified attachment point of the framebuffer object
	@param Specifies the attachment point of the framebuffer*/
	void detachFramebufferAttachment(FramebufferAttachment attachment)
	{
		_framebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, nullptr);
	}

	/*(3.0) Duplicates a framebuffer object, increasing its reference count. The reference source object is being copied
	@param Specifies the source framebuffer object*/
	void duplicateFramebuffer(const ReadFramebuffer& source)
	{
		_framebuffer_dup((_Object&)source);
	}

	/*(3.0) Attaches a renderbuffer as a logical buffer of a framebuffer object
	@param Specifies the attachment point of the framebuffer
	@param Specifies a valid renderbuffer object to attach*/
	void framebufferRenderbuffer(Renderbuffer& renderbuffer, FramebufferAttachment attachment)
	{
		_framebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, &renderbuffer);
	}

	/*(3.0) (1) Attaches a level of a one-dimensional texture object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture(Texture1D& texture, FramebufferAttachment attachment, GLint level)
	{
		_framebufferTexture1D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (_Texture&)texture, level);
	}

	/*(3.0) (2) Attaches a level of a two-dimensional texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture(Texture2D& texture, FramebufferAttachment attachment, GLint level)
	{
		_framebufferTexture2D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_TEXTURE_2D, (_Texture&)texture, level);
	}

	/*(3.0) (3) Attaches a level of a layer of three-dimensional texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTexture(Texture3D& texture, FramebufferAttachment attachment, GLint level, GLint layer)
	{
		_framebufferTexture3D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (_Texture&)texture, level, layer);
	}

	/*(3.0) (4) Attaches a level of a plane of a cube map texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies a selected plane of a cube map texture object
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture(TextureCubeMap& texture, TextureCubeMapPlane plane, FramebufferAttachment attachment, GLint level)
	{
		_framebufferTexture2D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (GLenum)plane, (_Texture&)texture, level);
	}

	/*(3.0) (5) Attaches a level of a one-dimensional multi-layered texture object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 1-dimensional image within a 2-dimensional texture*/
	void framebufferTexture(Texture1DArray& texture, FramebufferAttachment attachment, GLint level, GLint layer)
	{
		_framebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (_Texture&)texture, level, layer);
	}

	/*(3.0) (6) Attaches a level of a two-dimensional multi-layered texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTexture(Texture2DArray& texture, FramebufferAttachment attachment, GLint level, GLint layer)
	{
		_framebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (_Texture&)texture, level, layer);
	}

	/*(3.0) Identifies the type of object which contains the attached image
	@param Specifies the attachment point of the framebuffer
	@return The attached image object type value*/
	FramebufferAttachmentType getFramebufferAttachmentObjectType(FramebufferAttachment attachment)
	{
		return (FramebufferAttachmentType)_getFramebufferAttachmentParameter(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
	}

	/*(3.0) Returns the mipmap level of the texture object which contains the attached image
	@param Specifies the attachment point of the framebuffer
	@return The mipmap level of the texture object*/
	GLint getFramebufferAttachmentTextureLevel(FramebufferAttachment attachment)
	{
		return _getFramebufferAttachmentParameter(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
	}

	/*(3.0) Returns the texture layer which contains the attached image, the layered flag must be false
	@param Specifies the attachment point of the framebuffer
	@return The texture layer of the texture object containing the attached image, or 0 if none*/
	GLint getFramebufferAttachmentTextureLayer(FramebufferAttachment attachment)
	{
		return _getFramebufferAttachmentParameter(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
	}

	/*(3.0) Returns a reference framebuffer object currently bound to its target
	@return The reference framebuffer object, or empty object*/
	static ReadFramebuffer getFramebufferBinding()
	{
		return ReadFramebuffer(_framebufferBinding(GL_READ_FRAMEBUFFER_BINDING));
	}

	/*(3.0) Determines if the framebuffer object is currently bound to its target. Used as a getter of <framebufferBinding> property
	@return True if framebuffer object currently bound to its target, or false otherwise*/
	GLboolean isFramebufferBinding() const
	{
		return _isFramebufferBinding(GL_READ_FRAMEBUFFER_BINDING);
	}

	/*(3.0) Checks if the source framebuffer object is referencing the same OpenGL object
	@param Specifies the source framebuffer object
	@return True if duplicate object*/
	GLboolean isDuplicate(const ReadFramebuffer& source) const
	{
		return _object_is((_Object&)source);
	}

	/*(3.0) Creates a thread-safe reference object from the source framebuffer object
	@param Specifies the source framebuffer object*/
	void referFramebuffer(const ReadFramebuffer& source)
	{
		_framebuffer_refer((_Object&)source);
	}

	/*(3.0) Sets the binding state of the framebuffer object, only if current state is opposite. Used as a setter of <framebufferBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setFramebufferBinding(GLboolean bind)
	{
		_framebuffer_set(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, bind);
	}

	/*(3.0) Explicitly unbinds specified framebuffer object from its target. Does nothing if specified framebuffer is not bound*/
	void unbindBuffer()
	{
		_unbindFramebuffer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING);
	}

	/*(3.0) Explicitly unbinds any framebuffer object of specified type bound to its target. Does nothing if no such framebuffer is bound*/
	static void unbindTarget()
	{
		_unbindTarget(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for state of the framebuffer binding*/
	__declspec(property(get = isFramebufferBinding, put = setFramebufferBinding)) GLboolean framebufferBinding;

	/*(3.0) Read-only property for framebuffer completeness status value*/
	__declspec(property(get = checkFramebufferStatus)) FramebufferCompletenessStatus framebufferStatus;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) (7) Attaches a two-dimensional rectangle texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer*/
	void framebufferTexture(TextureRectangle& texture, FramebufferAttachment attachment)
	{
		_framebufferTexture2D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_TEXTURE_RECTANGLE, (_Texture&)texture, 0);
	}
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) (8) Attaches a level of a two-dimensional multisample texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer*/
	void framebufferTexture(Texture2DMultisample& texture, FramebufferAttachment attachment)
	{
		_framebufferTexture2D(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_TEXTURE_2D_MULTISAMPLE, (_Texture&)texture, 0);
	}

	/*(3.2) (9) Attaches a level of a multi-layered two-dimensional multisample texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTexture(Texture2DMultisampleArray& texture, FramebufferAttachment attachment, GLint layer)
	{
		_framebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, (_Texture&)texture, 0, layer);
	}

	/*(3.2) Returns whether an entire level of a three-dimensional texture, cube map texture, or one-or two-dimensional array texture is attached
	@param Specifies the index of attachment point of the framebuffer
	@return Thue if an entire level of the texture object is attached, false otherwise*/
	GLboolean getFramebufferAttachmentLayered(FramebufferAttachment attachment)
	{
		return _getFramebufferAttachmentParameter(GL_READ_FRAMEBUFFER, GL_READ_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
	}
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class ReadFramebuffer : public _Framebuffer

/*(3.0) Returns a reference ReadFramebuffer object currently bound to its target
@return The reference ReadFramebuffer object, or empty object*/
inline ReadFramebuffer getReadFramebufferBinding()
{
	return ReadFramebuffer::getFramebufferBinding();
}

/*(3.0) Explicitly unbinds any framebuffer object of specified type bound to its target. Does nothing if no such framebuffer is bound*/
inline void unbindReadFramebuffer()
{
	ReadFramebuffer::unbindTarget();
}
} // namespace gl {
#endif // #ifdef YAGLPP_VERSION_3_0
