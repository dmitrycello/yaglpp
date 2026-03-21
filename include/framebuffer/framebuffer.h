#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_FRAMEBUFFER_H
#define YAGLPP_FRAMEBUFFER_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL dual framebuffer object class derived from <Framebuffers>*/
class Framebuffer : public Framebuffers
{
public:
	using Framebuffers::Framebuffers;
	/*(3.0) (1) Attaches a renderbuffer as a logical buffer of a framebuffer object
	@param Specifies a valid renderbuffer object to attach
	@param Specifies the attachment point of the framebuffer*/
	void Attach(Renderbuffer& renderbuffer, Attachment attachment)
	{
		framebuffer_renderbuffer(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, renderbuffer.Get());
	}

	/*(3.0) (2) Attaches a level of a one-dimensional texture object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void Attach(Texture1D& texture, Attachment attachment, GLint level)
	{
		framebuffer_texture_1d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), level);
	}

	/*(3.0) (3) Attaches a level of a two-dimensional texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void Attach(Texture2D& texture, Attachment attachment, GLint level)
	{
		framebuffer_texture_2d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level);
	}

	/*(3.0) (4) Attaches a level of a layer of three-dimensional texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void Attach(Texture3D& texture, Attachment attachment, GLint level, GLint layer)
	{
		framebuffer_texture_3d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), level, layer);
	}

	/*(3.0) (5) Attaches a level of a plane of a cube map texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies a selected plane of a cube map texture object
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach*/
	void Attach(TextureCubeMap& texture, TextureCubeMap::Plane plane, Attachment attachment, GLint level)
	{
		framebuffer_texture_2d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), (GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level);
	}

	/*(3.0) (6) Attaches a level of a one-dimensional multi-layered texture object as a logical buffer of a framebuffer object. The image height is equal to 1
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 1-dimensional image within a 2-dimensional texture*/
	void Attach(Texture1DArray& texture, Attachment attachment, GLint level, GLint layer)
	{
		framebuffer_texture_layer(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_BINDING_1D_ARRAY, level, layer);
	}

	/*(3.0) (7) Attaches a level of a two-dimensional multi-layered texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the mipmap level of the texture object to attach
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void Attach(Texture2DArray& texture, Attachment attachment, GLint level, GLint layer)
	{
		framebuffer_texture_layer(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_BINDING_2D_ARRAY, level, layer);
	}

	/*(3.0) Binds framebuffer object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(glBindFramebuffer, GL_FRAMEBUFFER);
	}

	/*(3.0) Transfer a rectangle of pixel values from one region to another within the same dual framebuffer
	@param Four parameters (x0, y0, x1, y1) of source rectangle of a read framebuffer
	@param Four parameters (x0, y0, x1, y1) of destination rectangle of a draw framebuffer
	@param The bitwise OR of the mask flags indicating which buffers are to be copied
	@param Specifies the interpolation to be applied if the image is stretched*/
	void Blit(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, BufferBit mask, Textures::MagFilter filter)
	{
		blit_framebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, Get(), Get(), (GLenum)mask, (GLenum)filter);
	}

	/*(3.0) Checks the completeness status of a framebuffer. MSVC getter for <status> property
	@return The framebuffer completeness status value*/
	CompletenessStatus CheckStatus()
	{
		return (CompletenessStatus)check_framebuffer_status(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING);
	}

	/*(3.0) Detaches the image, if any, identified by the specified attachment point of the framebuffer object
	@param Specifies the attachment point of the framebuffer*/
	void Detach(Attachment attachment)
	{
		framebuffer_renderbuffer(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, 0);
	}

	/*(3.0) Generates OpenGL framebuffer object name in an empty framebuffer class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenFramebuffers, glBindFramebuffer, GL_FRAMEBUFFER);
	}

	/*(3.0) Identifies the type of object which contains the attached image
	@param Specifies the attachment point of the framebuffer
	@return The attached image object type value*/
	AttachmentType GetAttachmentObjectType(Attachment attachment)
	{
		return (AttachmentType)get_framebuffer_attachment_parameter(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
	}

	/*(3.0) Returns the mipmap level of the texture object which contains the attached image
	@param Specifies the attachment point of the framebuffer
	@return The mipmap level of the texture object*/
	GLint GetAttachmentTextureLevel(Attachment attachment)
	{
		return get_framebuffer_attachment_parameter(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
	}

	/*(3.0) Returns the framebuffer object currently bound to particular target
	@return The bound framebuffer object, or empty object*/
	static Framebuffer GetBinding()
	{
		return Framebuffer(yaglpp_glad_integer(GL_FRAMEBUFFER_BINDING));
	}

	/*(3.0) Determines if the framebuffer object is currently bound to its target. MSVC getter for <binding> property
	@return True if framebuffer object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_FRAMEBUFFER_BINDING, Get());
	}

	/*(3.0) Unbinds any framebuffer object bound to particular target. Affects the bound status of all framebuffer targets*/
	static void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property for state of the framebuffer binding*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.0) Read-only property for framebuffer completeness status value*/
	__declspec(property(get = CheckStatus)) CompletenessStatus status;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) (8) Attaches a two-dimensional rectangle texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer*/
	void Attach(TextureRectangle& texture, Attachment attachment)
	{
		framebuffer_texture_2d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0);
	}
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) (9) Attaches a level of a two-dimensional multisample texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer*/
	void Attach(Texture2DMultisample& texture, Attachment attachment)
	{
		framebuffer_texture_2d(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BINDING_2D_MULTISAMPLE, 0);
	}

	/*(3.2) (10) Attaches a level of a multi-layered two-dimensional multisample texture object as a logical buffer of a framebuffer object
	@param Specifies a valid texture object to attach
	@param Specifies the attachment point of the framebuffer
	@param Specifies the layer of a 2-dimensional image within a 3-dimensional texture*/
	void Attach(Texture2DMultisampleArray& texture, Attachment attachment, GLint layer)
	{
		framebuffer_texture_layer(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, texture.Get(), GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, layer);
	}

	/*(3.2) Returns whether an entire level of a three-dimensional texture, cube map texture, or one-or two-dimensional array texture is attached
	@param Specifies the index of attachment point of the framebuffer
	@return Thue if an entire level of the texture object is attached, false otherwise*/
	GLboolean IsAttachmentLayered(Attachment attachment)
	{
		return get_framebuffer_attachment_parameter(GL_FRAMEBUFFER, GL_FRAMEBUFFER_BINDING, (GLenum)attachment, GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
	}
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class Framebuffer : public Framebuffers
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_FRAMEBUFFER_H
