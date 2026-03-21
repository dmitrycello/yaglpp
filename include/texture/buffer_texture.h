#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_BUFFER_TEXTURE_H
#define YAGLPP_BUFFER_TEXTURE_H

#ifdef YAGLPP_VERSION_3_1
namespace gl {
/*(3.1) OpenGL one-dimensional buffer texture object class derived from <Textures>*/
class BufferTexture : public Textures
{
public:
	using Textures::Textures;
	enum class BufferFormat : GLenum;
	/*(3.1) Attach a texture buffer (buffer) object's data store to an active buffer texture (texture) object
	@param Specifies texture buffer object whose storage to attach to the active buffer texture
	@param Specifies the internal format of the data in the store belonging to buffer*/
	void AttachBuffer(TextureBuffer& buffer, BufferFormat internalformat)
	{
		tex_buffer((GLenum)internalformat, buffer.Get());
	}

	/*(3.1) Binds texture object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(glBindTexture, GL_TEXTURE_BUFFER);
	}

	/*(3.1) Detatch a texture buffer (buffer) object's data store currently attached to buffer texture (texture) object*/
	void DetachBuffer()
	{
		tex_buffer(0, 0);
	}

	/*(3.1) Generates OpenGL texture object name in an empty texture class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenTextures, glBindTexture, GL_TEXTURE_BUFFER);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the texture image
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLuint GetAlphaSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	ComponentType GetAlphaType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static BufferTexture GetBinding()
	{
		return BufferTexture(yaglpp_glad_integer(GL_TEXTURE_BINDING_BUFFER));
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLuint GetBlueSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	ComponentType GetBlueType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLuint GetDepthSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	ComponentType GetDepthType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLuint GetGreenSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	ComponentType GetGreenType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	Internalformat GetInternalFormat()
	{
		return (Internalformat)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLuint GetRedSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	ComponentType GetRedType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the texture image. The initial value is 0
	@return The width of the texture image*/
	GLsizei GetWidth()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.1) Determines if the texture object is currently bound to its target. MSVC getter for <binding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_TEXTURE_BINDING_BUFFER, Get());
	}

	/*(3.1) Unbinds any texture object bound to particular target, and restores its default texture. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-only property for state of the texture binding*/
	__declspec(property(get = IsBinding)) GLboolean binding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class BufferTexture : public _Texture

/*(3.1) GLAD buffer texture internal format enumerator used in <AttachBuffer>*/
enum class BufferTexture::BufferFormat : GLenum
{
	/*(3.1) Red color component format with 8-bit resolution*/
	R8 = GL_R8,

	/*(3.1) Red color component format with 16-bit resolution*/
	R16 = GL_R16,

	/*(3.1) Red float color component format with 16-bit resolution*/
	R16f = GL_R16F,

	/*(3.1) Red float color component format with 32-bit resolution*/
	R32f = GL_R32F,

	/*(3.1) Red signed integer color component format with 8-bit resolution*/
	R8i = GL_R8I,

	/*(3.1) Red signed integer color component format with 16-bit resolution*/
	R16i = GL_R16I,

	/*(3.1) Red signed integer color component format with 32-bit resolution*/
	R32i = GL_R32I,

	/*(3.1) Red unsigned integer color component format with 8-bit resolution*/
	R8ui = GL_R8UI,

	/*(3.1) Red unsigned integer color component format with 16-bit resolution*/
	R16ui = GL_R16UI,

	/*(3.1) Red unsigned integer color component format with 32-bit resolution*/
	R32ui = GL_R32UI,

	/*(3.1) RG color component format with (8:8)-bit resolution*/
	Rg8 = GL_RG8,

	/*(3.1) RG color component format with (16:16)-bit resolution*/
	Rg16 = GL_RG16,

	/*(3.1) RG float color component format with (16:16)-bit resolution*/
	Rg16f = GL_RG16F,

	/*(3.1) RG float color component format with (32:32)-bit resolution*/
	Rg32f = GL_RG32F,

	/*(3.1) RG signed integer color component format with (8:8)-bit resolution*/
	Rg8i = GL_RG8I,

	/*(3.1) RG signed integer color component format with (16:16)-bit resolution*/
	Rg16i = GL_RG16I,

	/*(3.1) RG signed integer color component format with (32:32)-bit resolution*/
	Rg32i = GL_RG32I,

	/*(3.1) RG unsigned integer color component format with (8:8)-bit resolution*/
	Rg8ui = GL_RG8UI,

	/*(3.1) RG unsigned integer color component format with (16:16)-bit resolution*/
	Rg16ui = GL_RG16UI,

	/*(3.1) RG unsigned integer color component format with (32:32)-bit resolution*/
	Rg32ui = GL_RG32UI,

	/*(3.1) RGB float color component format with (32:32:32)-bit resolution*/
	Rgb32f = GL_RGB32F,

	/*(3.1) RGB signed integer color component format with (32:32:32)-bit resolution*/
	Rgb32i = GL_RGB32I,

	/*(3.1) RGB unsigned integer color component format with (32:32:32)-bit resolution*/
	Rgb32ui = GL_RGB32UI,

	/*(3.1) RGBA color component format with (8:8:8:8)-bit resolution*/
	Rgba8 = GL_RGBA8,

	/*(3.1) RGBA color component format with (16:16:16:16)-bit resolution*/
	Rgba16 = GL_RGBA16,

	/*(3.1) RGBA float color component format with (16:16:16:16)-bit resolution*/
	Rgba16f = GL_RGBA16F,

	/*(3.1) RGBA float color component format with (32:32:32:32)-bit resolution*/
	Rgba32f = GL_RGBA32F,

	/*(3.1) RGBA signed integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8i = GL_RGBA8I,

	/*(3.1) RGBA signed integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16i = GL_RGBA16I,

	/*(3.1) RGBA signed integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32i = GL_RGBA32I,

	/*(3.1) RGBA unsigned integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.1) RGBA unsigned integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.1) RGBA unsigned integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32ui = GL_RGBA32UI,
};
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_1
#endif // #ifndef YAGLPP_BUFFER_TEXTURE_H
