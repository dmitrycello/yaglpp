#pragma once
#include "gladpp.h"
#include "_Texture.h"
#ifdef GL_VERSION_3_1
namespace gl {
/*(3.1) GLAD buffer texture internal format enumerator used in <texBuffer>*/
enum class TexBufferInternalformat : GLenum
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

/*(3.1) OpenGL one-dimensional buffer texture object class derived from <_Texture>*/
class BufferTexture : public _Texture
{
public:
	/*(3.1) (1) Constructs an empty texture object*/
	BufferTexture() {}

	/*(3.1) (2) Constucts a texture object with <shareTexture>*/
	BufferTexture(BufferTexture& texture)
	{
		shareTexture(texture);
	}

	/*(3.1) (3) Constucts a texture object with <assignTexture>*/
	BufferTexture(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*(3.1) Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, index);
	}

	/*(3.1) Set an empty texture object as a reference to an element of the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_BUFFER);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*(3.1) Explicitly binds texture object to its target. Does nothing if specified texture is bound*/
	void bindTexture()
	{
		_bindTexture(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER);
	}

	/*(3.1) Detatch a texture buffer (buffer) object's data store currently attached to buffer texture (texture) object*/
	void detachTexBuffer()
	{
		_texBuffer(0, nullptr);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the texture image
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLint getTextureAlphaSize()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	TexInternalformat getTextureInternalFormat()
	{
		return (TexInternalformat)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the texture image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth()
	{
		return _getTexLevelParameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.1) Determines if the texture object is currently bound to its target. Used as a getter of <textureBinding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBinding()
	{
		return _object_id() == (GLuint)_getInteger(GL_TEXTURE_BINDING_BUFFER);
	}

	/*(3.1) Sets the binding state of the texture object, only if current state is opposite. Used as a setter of <textureBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setTextureBinding(GLboolean bind)
	{
		_setTextureBinding(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, bind);
	}

	/*(3.1) Set an empty texture object as a reference to the texture object from another context
	@param The texture object to share, must not be empty*/
	void shareTexture(BufferTexture& texture)
	{
		_object_share((_Object&)texture);
	}

	/*(3.1) Attach a texture buffer (buffer) object's data store to an active buffer texture (texture) object
	@param Specifies texture buffer object whose storage to attach to the active buffer texture
	@param Specifies the internal format of the data in the store belonging to buffer*/
	void texBuffer(TextureBuffer& buffer, TexBufferInternalformat internalformat)
	{
		_texBuffer((GLenum)internalformat, &buffer);
	}

	/*(3.1) Explicitly unbinds any texture object of specified type bound to its target. Does nothing if no such texture is bound*/
	static void unbindTarget()
	{
		_unbindTarget(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER);
	}

	/*(3.1) Explicitly unbinds specified texture object from its target. Does nothing if specified texture is not bound*/
	void unbindTexture()
	{
		_unbindTexture(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-write property for state of the texture binding*/
	__declspec(property(get = isTextureBinding, put = setTextureBinding)) GLboolean textureBinding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class BufferTexture : public _Texture

/*(3.1) Explicitly unbinds any texture object of specified type bound to its target. Does nothing if no such texture is bound*/
inline void unbindBufferTexture()
{
	BufferTexture::unbindTarget();
}
} // namespace gl
#endif // #ifdef GL_VERSION_3_1
