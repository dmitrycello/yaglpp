#pragma once
#include "gladpp.h"
#include "_Framebuffer.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL read framebuffer object class derived from <_Framebuffer>*/
class ReadFramebuffer : public _Framebuffer
{
public:
	/*(3.0) (1) Constructs an empty framebuffer object*/
	ReadFramebuffer() : _Framebuffer() {}

	/*(3.0) (2) Constucts a framebuffer object with <assignFramebuffer>*/
	ReadFramebuffer(Framebuffers& framebuffers, GLuint index)
	{
		assignFramebuffer(framebuffers, index);
	}

	/*(3.0) Assigns an empty framebuffer object with the object name from the framebuffer multi-object
	@param The framebuffer multi-object
	@param The index of the object name*/
	void assignFramebuffer(Framebuffers& framebuffers, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)framebuffers, index, GL_READ_FRAMEBUFFER);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)framebuffers, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Explicitly binds framebuffer object to its target*/
	void bindFramebuffer()
	{
		_framebuffer_rebind(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER);
	}

	/*(3.0) Transfer a rectangle of pixel values from one region of a read framebuffer to another region of a draw framebuffer
	@param Specifies the destination draw framebuffer object
	@param Four parameters (x0, y0, x1, y1) of source rectangle of a read framebuffer
	@param Four parameters (x0, y0, x1, y1) of destination rectangle of a draw framebuffer
	@param The bitwise OR of the mask flags indicating which buffers are to be copied
	@param Specifies the interpolation to be applied if the image is stretched*/
	void blitFramebuffer(DrawFramebuffer& dst, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBitMask mask, TextureMagFilter filter)
	{
		_framebuffer_bind(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER);
		_blitFramebuffer(dst, _tlsDrawFramebuffer(), GL_DRAW_FRAMEBUFFER, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	/*(3.0) Checks the completeness status of a framebuffer
	@return The framebuffer completeness status value*/
	FramebufferCompletenessStatus checkFramebufferStatus()
	{
		return (FramebufferCompletenessStatus)_checkFramebufferStatus(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER);
	}

	/*(3.0) Attaches a renderbuffer as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Renderbuffer object to attach*/
	void framebufferRenderbuffer(ColorAttachment index, Renderbuffer& renderbuffer)
	{
		_framebufferRenderbuffer(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, renderbuffer);
	}

	/*(3.0) Attaches a level of a Texture1D object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture1D object to attach
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture1D(ColorAttachment index, Texture1D& texture, GLint level)
	{
		_framebufferTexture1D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_TEXTURE_1D, texture, level);
	}

	/*(3.0) (1) Attaches a level of a Texture2D object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture2D object to attach
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture2D(ColorAttachment index, Texture2D& texture, GLint level)
	{
		_framebufferTexture2D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_TEXTURE_2D, texture, level);
	}

	/*(3.0) (2) Attaches a level of a TextureCubeMap object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid TextureCubeMap object to attach
	@param Specifies a selected plane of a TextureCubeMap object
	@param Specifies the mipmap level of the texture object to attach*/
	void framebufferTexture2D(ColorAttachment index, TextureCubeMap& texture, TextureCubeMapPlane plane, GLint level)
	{
		_framebufferTexture2D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, (GLenum)plane, texture, level);
	}

	/*(3.0) Attaches a level of a Texture3D object as a logical buffer of a framebuffer object. This is legacy function
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture3D object to attach
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTexture3D(ColorAttachment index, Texture3D& texture, GLint level, GLint layer)
	{
		_framebufferTexture3D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_TEXTURE_3D, texture, level, layer);
	}

	/*(3.0) (1) Attaches a level of a Texture3D object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture3D object to attach
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTextureLayer(ColorAttachment index, Texture3D& texture, GLint level, GLint layer)
	{
		_framebufferTextureLayer(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, texture, level, layer);
	}

	/*(3.0) (2) Attaches a level of a Texture1DArray object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture1DArray object to attach
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTextureLayer(ColorAttachment index, Texture1DArray& texture, GLint level, GLint layer)
	{
		_framebufferTextureLayer(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, texture, level, layer);
	}

	/*(3.0) (3) Attaches a level of a Texture2DArray object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture2DArray object to attach
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTextureLayer(ColorAttachment index, Texture2DArray& texture, GLint level, GLint layer)
	{
		_framebufferTextureLayer(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, texture, level, layer);
	}

	/*(3.0) Identifies the type of object which contains the attached image
	@param Specifies the index of attachment point of the framebuffer
	@return The attached image object type value*/
	FramebufferAttachmentType getFramebufferAttachmentObjectType(ColorAttachment index)
	{
		return (FramebufferAttachmentType)_getFramebufferAttachmentParameter(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
	}

	/*(3.0) Returns the mipmap level of the texture object which contains the attached image
	@param Specifies the index of attachment point of the framebuffer
	@return The mipmap level of the texture object*/
	GLint getFramebufferAttachmentTextureLevel(ColorAttachment index)
	{
		return _getFramebufferAttachmentParameter(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
	}

	/*(3.0) Returns the texture layer which contains the attached image, the layered flag must be false
	@param Specifies the index of attachment point of the framebuffer
	@return The texture layer of the texture object containing the attached image, or 0 if none*/
	GLint getFramebufferAttachmentTextureLayer(ColorAttachment index)
	{
		return _getFramebufferAttachmentParameter(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
	}

	/*(3.0) Determines via API if the framebuffer object is currently bound to its target
	@return True if framebuffer object currently bound to its target, or false otherwise*/
	GLboolean isReadFramebufferBinding()
	{
		GLuint uId = _framebuffer_id();
		return (uId == _getInteger(GL_READ_FRAMEBUFFER_BINDING)) && (uId != _getInteger(GL_DRAW_FRAMEBUFFER_BINDING));
	}

	/*(3.0) Unbinds any previously bound framebuffer object from its target. Does nothing if no such framebuffer is bound*/
	static void unbindFramebuffer()
	{
		_framebuffer_unbind(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER);
	}

#ifdef GL_VERSION_3_1
	/*(3.1) (3) Attaches a level of a TextureRectangle object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid TextureRectangle object to attach*/
	void framebufferTexture2D(ColorAttachment index, TextureRectangle& texture)
	{
		_framebufferTexture2D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_TEXTURE_RECTANGLE, texture, 0);
	}
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	/*(3.2) (4) Attaches a level of a Texture2DMultisample object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture2DMultisample object to attach*/
	void framebufferTexture2D(ColorAttachment index, Texture2DMultisample& texture)
	{
		_framebufferTexture2D(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);
	}

	/*(3.2) (4) Attaches a level of a Texture2DMultisampleArray object as a logical buffer of a framebuffer object
	@param Specifies the index of attachment point of the framebuffer
	@param Specifies a valid Texture2DMultisampleArray object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void framebufferTextureLayer(ColorAttachment index, Texture2DMultisampleArray& texture, GLint layer)
	{
		_framebufferTextureLayer(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, texture, 0, layer);
	}

	/*(3.2) Returns whether an entire level of a three-dimensional texture, cube map texture, or one-or two-dimensional array texture is attached
	@param Specifies the index of attachment point of the framebuffer
	@return Thue if an entire level of the texture object is attached, false otherwise*/
	GLboolean getFramebufferAttachmentLayered(ColorAttachment index)
	{
		return _getFramebufferAttachmentParameter(_tlsReadFramebuffer(), GL_READ_FRAMEBUFFER, index, GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
	}
#endif // #ifdef GL_VERSION_3_2
}; // class ReadFramebuffer : public _Framebuffer
} // namespace gl {
#endif // #ifdef GL_VERSION_3_0
