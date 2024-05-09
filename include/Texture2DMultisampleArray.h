#pragma once
#include "gladpp.h"
#include "_Texture.h"
#ifdef GL_VERSION_3_2
namespace gl {
/*(3.2) OpenGL multiple two-dimensional multisample layered texture object class derived from <_Texture>*/
class Texture2DMultisampleArray : public _Texture
{
public:
	/*(3.2) (1) Constructs an empty texture object*/
	Texture2DMultisampleArray() : _Texture() {}

	/*(3.2) (2) Constucts a texture object with <shareTexture>*/
	Texture2DMultisampleArray(Texture2DMultisampleArray& texture)
	{
		shareTexture(texture);
	}

	/*(3.2) (3) Constucts a texture object with <assignTexture>*/
	Texture2DMultisampleArray(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*(3.2) Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, index);
	}

	/*(3.2) Set an empty texture object as a reference to an element of the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*(3.2) Explicitly binds texture object to its target*/
	void bindTexture()
	{
		_texture_rebind(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	}

	/*(3.2) Unbinds any previously bound texture object, and restores the default texture for its target. Does nothing if no such texture is bound*/
	static void defaultTexture()
	{
		_texture_unbind(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	}

	/*(3.2) Gets the value that indicates the maximum number of layers allowed in an array texture
	@return The maximum array texture layers. Must be at least 256*/
	static GLsizei getMaxArrayTextureLayers()
	{
		return _getInteger(GL_MAX_ARRAY_TEXTURE_LAYERS);
	}

	/*(3.2) Returns the maximum number of samples in a color multisample texture
	@return The maximum color texture samples*/
	static GLsizei getMaxColorTextureSamples()
	{
		return _getInteger(GL_MAX_COLOR_TEXTURE_SAMPLES);
	}

	/*(3.2) Returns the maximum number of samples in a multisample depth or depth-stencil texture
	@return The maximum depth texture samples*/
	static GLsizei getMaxDepthTextureSamples()
	{
		return _getInteger(GL_MAX_DEPTH_TEXTURE_SAMPLES);
	}

	/*(3.2) Returns the maximum number of samples in multisample texture
	@return The maximum samples*/
	static GLsizei getMaxSamples()
	{
		return _getInteger(GL_MAX_SAMPLES);
	}

	/*(3.2) Returns internal storage resolution of ALPHA component of the texture image
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLint getTextureAlphaSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns internal storage resolution of ALPHA component of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	static GLint getTextureAlphaSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns the type of ALPHA component of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static TextureComponentType getTextureAlphaTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the proxy texture
	@return The internal storage resolution of BLUE component*/
	static GLint getTextureBlueSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) Returns the type of BLUE component of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static TextureComponentType getTextureBlueTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color)
	{
		_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color)
	{
		_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Returns the current texture comparison function
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.2) Gets the texture comparison mode for currently bound depth textures
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLint getTextureDepthSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns the type of DEPTH component of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static TextureComponentType getTextureDepthTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLint getTextureGreenSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the type of GREEN component of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static TextureComponentType getTextureGreenTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the height of the texture image
	@return The height of the texture image. The initial value is 0*/
	GLsizei getTextureHeight()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the height of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei getTextureHeightProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	ColorDepthStencilFormat getTextureInternalFormat()
	{
		return (ColorDepthStencilFormat)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the internal format capacity of the proxy texture
	@return The internal format capacity of the texture*/
	static ColorDepthStencilFormat getTextureInternalFormatProxy()
	{
		return (ColorDepthStencilFormat)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the layers of the texture image
	@return The layers of the texture image. The initial value is 0*/
	GLsizei getTextureLayers()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Returns the layers of the proxy texture
	@return The layers of the texture image*/
	static GLsizei getTextureLayersProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Gets the current texture magnification function
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.2) Gets the current texture minifying function
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.2) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns internal storage resolution of RED component of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLint getTextureRedSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the type of RED component of the proxy texture
	@return The type of RED component of the proxy texture*/
	static TextureComponentType getTextureRedTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the width of the texture image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns the width of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei getTextureWidthProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns the wrapping function for texture coordinate r
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_R);
	}

	/*(3.2) Returns the wrapping function for texture coordinate s
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_S);
	}

	/*(3.2) Returns the wrapping function for texture coordinate t
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_T);
	}

	/*(3.2) Determines via API if the texture object is currently bound to its target
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBinding2DMultisampleArray()
	{
		return _object_id() == _getInteger(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY);
	}

	/*(3.2) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.2) Sets the texture comparison mode for currently bound depth textures
	@param Specifies the texture compare mode value*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.2) Sets the texture magnification function value
	@param Specifies the texture magnification function's value. The initial value is linear*/
	void setTextureMagFilter(TextureMagFilter func)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAG_FILTER, (GLint)func);
	}

	/*(3.2) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.2) Sets the wrapping function for texture coordinate r
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate s
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate t
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.2) Set an empty texture object as a reference to the texture object from another context
	@param The texture object to share, must not be empty*/
	void shareTexture(Texture2DMultisampleArray& texture)
	{
		_object_share((_Object&)texture);
	}

	/*(3.2) Establish the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <getMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param The number of layers of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	void texImage3DMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height, GLsizei layers, GLboolean fixedsamplelocations)
	{
		_texImage3DMultisample(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, (GLenum)internalformat, width, height, layers, fixedsamplelocations);
	}

	/*(3.2) Recalculate the capacity for the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <getMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param The number of layers of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	static void texImage3DMultisampleProxy(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height, GLsizei layers, GLboolean fixedsamplelocations)
	{
		_texImage3DMultisample(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, (GLenum)internalformat, width, height, layers, fixedsamplelocations);
	}

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value
	@return The alpha component swizzle value. The initial value is <Alpha>*/
	TextureSwizzleMask getTextureSwizzleA()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value
	@return The blue component swizzle value. The initial value is <Blue>*/
	TextureSwizzleMask getTextureSwizzleB()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value
	@return The green component swizzle value. The initial value is <Green>*/
	TextureSwizzleMask getTextureSwizzleG()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value
	@return The red component swizzle value. The initial value is <Red>*/
	TextureSwizzleMask getTextureSwizzleR()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query
	@param [out] Stores four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void getTextureSwizzleRGBA(_Out_writes_(4) TextureSwizzleMask* swizzle)
	{
		_getTexParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader
	@param The alpha component swizzle value. The initial value is <Alpha>*/
	void setTextureSwizzleA(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader
	@param The blue component swizzle value. The initial value is <Blue>*/
	void setTextureSwizzleB(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader
	@param The green component swizzle value. The initial value is <Green>*/
	void setTextureSwizzleG(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader
	@param The red component swizzle value. The initial value is <Red>*/
	void setTextureSwizzleR(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void setTextureSwizzleRGBA(_In_reads_(4) const TextureSwizzleMask* swizzle)
	{
		_texParameter(_tlsTexture2DMultisampleArray(), GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}
#endif // #ifdef GL_VERSION_3_3
}; // class Texture2DMultisampleArray : public _Texture
} // namespace gl {
#endif // #ifdef GL_VERSION_3_2
