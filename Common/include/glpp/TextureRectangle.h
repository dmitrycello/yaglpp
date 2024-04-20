#pragma once
#include "gladpp.h"
#include "_Texture.h"
#ifdef GL_VERSION_3_1
namespace gl {
/*(3.1) OpenGL two-dimensional rectangle texture object class derived from <_Texture>*/
class TextureRectangle : public _Texture
{
public:
	/*(3.1) (1) Constructs an empty texture object*/
	TextureRectangle() : _Texture() {}

	/*(3.1) (2) Constucts a texture object with <assignTexture>*/
	TextureRectangle(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*(3.1) Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, index);
	}

	/*(3.1) Assigns an empty texture object with the object name from the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_RECTANGLE);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*(3.1) Explicitly binds texture object to its target*/
	void bindTexture()
	{
		_texture_rebind(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE);
	}

	/*(3.1) Replaces a rectangular portion of a rectangle texture image with pixels from the current read buffer
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void copyTexSubImage2D(GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		_copyTexSubImage2D(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, xoffset, yoffset, x, y, width, height);
	}

	/*(3.1) Unbinds any previously bound texture object, and restores the default texture for its target. Does nothing if no such texture is bound*/
	static void defaultTexture()
	{
		_texture_unbind(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE);
	}

	/*(3.1) Get a rough estimate of the largest rectangular texture that the GL can handle. The value must be at least 1024. Use <getTextureWidthProxy> or <getTextureHeightProxy> to determine if a texture is too large
	@return The maximum rectangle texture size*/
	static GLsizei getMaxRectangleTextureSize()
	{
		return _getInteger(GL_MAX_RECTANGLE_TEXTURE_SIZE);
	}

	/*(3.1) (1) Returns a two-dimensional rectangle texture image into client's memory. (2.1) Unbinds pixel pack buffer from its target
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void getTexImage(GetTexFormat format, GetTexType type, _Out_ void* pixels)
	{
		_getTexImage(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.1) (2) Returns a two-dimensional rectangle texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer used for storing the data
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void getTexImage(PixelPackBuffer& buffer, GetTexFormat format, GetTexType type, GLintptr offset)
	{
		_getTexImage(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the texture image
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLint getTextureAlphaSize()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	static GLint getTextureAlphaSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns the type of ALPHA component of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static TextureComponentType getTextureAlphaTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the proxy texture
	@return The internal storage resolution of BLUE component*/
	static GLint getTextureBlueSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns the type of BLUE component of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static TextureComponentType getTextureBlueTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color)
	{
		_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.1) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color)
	{
		_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.1) Returns the current texture comparison function
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.1) Gets the texture comparison mode for currently bound depth textures
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLint getTextureDepthSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns the type of DEPTH component of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static TextureComponentType getTextureDepthTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLint getTextureGreenSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the type of GREEN component of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static TextureComponentType getTextureGreenTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the height of the texture image
	@return The height of the texture image. The initial value is 0*/
	GLsizei getTextureHeight()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.1) Returns the height of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei getTextureHeightProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.1) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	TexInternalformat getTextureInternalFormat()
	{
		return (TexInternalformat)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns the internal format capacity of the proxy texture
	@return The internal format capacity of the texture*/
	static TexInternalformat getTextureInternalFormatProxy()
	{
		return (TexInternalformat)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Gets the current texture magnification function
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.1) Gets the current texture minifying function
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.1) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns internal storage resolution of RED component of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLint getTextureRedSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the type of RED component of the proxy texture
	@return The type of RED component of the proxy texture*/
	static TextureComponentType getTextureRedTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the texture image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth()
	{
		return _getTexLevelParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.1) Returns the width of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei getTextureWidthProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_RECTANGLE, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.1) Returns the wrapping function for texture coordinate r
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_R);
	}

	/*(3.1) Returns the wrapping function for texture coordinate s
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S);
	}

	/*(3.1) Returns the wrapping function for texture coordinate t
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T);
	}

	/*(3.1) Determines via API if the texture object is currently bound to its target
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBindingRectangle()
	{
		return _texture_id() == _getInteger(GL_TEXTURE_BINDING_RECTANGLE);
	}

	/*(3.1) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.1) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.1) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.1) Sets the texture comparison mode for currently bound depth textures
	@param Specifies the texture compare mode value*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.1) Sets the texture magnification function value
	@param Specifies the texture magnification function's value. The initial value is linear*/
	void setTextureMagFilter(TextureMagFilter func)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, (GLint)func);
	}

	/*(3.1) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.1) Sets the wrapping function for texture coordinate r
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.1) Sets the wrapping function for texture coordinate s
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.1) Sets the wrapping function for texture coordinate t
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.1) (1) Specifies a two-dimensional rectangle texture image initialized from the StbImage object. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the texture internal formats*/
	void texImage2D(StbImage& image, GLint level, TexInternalformat internalformat)
	{
		_texImage2D(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, (GLint)internalformat, image);
	}

	/*(3.1) (2) Specifies a two-dimensional rectangle texture image initialized from client's memory. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void texImage2D(GLint level, TexInternalformat internalformat, GLsizei width, GLsizei height, TexFormat format, TexType type, _In_ const void* data)
	{
		_texImage2D(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, data);
	}

	/*(3.1) (3) Specifies a one-dimensional rectangle texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void texImage2D(PixelUnpackBuffer& buffer, GLint level, TexInternalformat internalformat, GLsizei width, GLsizei height, TexFormat format, TexType type, GLintptr offset)
	{
		_texImage2D(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(3.1) Recalculates the capacity for a two-dimensional rectangle texture image using proxy target
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void texImage2DProxy(GLint level, TexInternalformat internalformat, GLsizei width, GLsizei height, TexFormat format, TexType type)
	{
		_texImage2D(GL_PROXY_TEXTURE_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, nullptr);
	}

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value
	@return The alpha component swizzle value. The initial value is <Alpha>*/
	TextureSwizzleMask getTextureSwizzleA()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value
	@return The blue component swizzle value. The initial value is <Blue>*/
	TextureSwizzleMask getTextureSwizzleB()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value
	@return The green component swizzle value. The initial value is <Green>*/
	TextureSwizzleMask getTextureSwizzleG()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value
	@return The red component swizzle value. The initial value is <Red>*/
	TextureSwizzleMask getTextureSwizzleR()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query
	@param [out] Stores four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void getTextureSwizzleRGBA(_Out_writes_(4) TextureSwizzleMask* swizzle)
	{
		_getTexParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader
	@param The alpha component swizzle value. The initial value is <Alpha>*/
	void setTextureSwizzleA(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader
	@param The blue component swizzle value. The initial value is <Blue>*/
	void setTextureSwizzleB(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader
	@param The green component swizzle value. The initial value is <Green>*/
	void setTextureSwizzleG(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader
	@param The red component swizzle value. The initial value is <Red>*/
	void setTextureSwizzleR(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void setTextureSwizzleRGBA(_In_reads_(4) const TextureSwizzleMask* swizzle)
	{
		_texParameter(_tlsTextureRectangle(), GL_TEXTURE_RECTANGLE, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}
#endif // #ifdef GL_VERSION_3_3
}; // class TextureRectangle : public _Texture
} // namespace gl {
#endif // #ifdef GL_VERSION_3_1
