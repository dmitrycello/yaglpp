#pragma once
#include "gladpp.h"
#include "_Texture.h"
#ifdef GL_VERSION_3_2
namespace gl {
/*(3.2) OpenGL two-dimensional multisample texture object class derived from <_Texture>*/
class Texture2DMultisample : public _Texture
{
public:
	/*(3.2) (1) Constructs an empty texture object*/
	Texture2DMultisample() {}

	/*(3.2) (2) Constucts a texture object with <shareTexture>*/
	Texture2DMultisample(Texture2DMultisample& texture)
	{
		shareTexture(texture);
	}

	/*(3.2) (3) Constucts a texture object with <assignTexture>*/
	Texture2DMultisample(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*(3.2) Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, index);
	}

	/*(3.2) Set an empty texture object as a reference to an element of the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_2D_MULTISAMPLE);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*(3.2) Explicitly binds texture object to its target*/
	void bindTexture()
	{
		_texture_rebind(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE);
	}

	/*(3.2) Unbinds any previously bound texture object, and restores the default texture for its target. Does nothing if no such texture is bound*/
	static void defaultTexture()
	{
		_texture_unbind(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE);
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
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns internal storage resolution of ALPHA component of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	static GLint getTextureAlphaSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns the type of ALPHA component of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static TextureComponentType getTextureAlphaTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the proxy texture
	@return The internal storage resolution of BLUE component*/
	static GLint getTextureBlueSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) Returns the type of BLUE component of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static TextureComponentType getTextureBlueTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color)
	{
		_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color)
	{
		_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Returns the current texture comparison function. Used as the getter of <textureCompareFunc> property
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.2) Gets the texture comparison mode for currently bound depth textures. Used as the getter of <textureCompareMode> property
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLint getTextureDepthSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns the type of DEPTH component of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static TextureComponentType getTextureDepthTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLint getTextureGreenSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the type of GREEN component of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static TextureComponentType getTextureGreenTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the height of the texture image
	@return The height of the texture image. The initial value is 0*/
	GLsizei getTextureHeight()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the height of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei getTextureHeightProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	ColorDepthStencilFormat getTextureInternalFormat()
	{
		return (ColorDepthStencilFormat)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the internal format capacity of the proxy texture
	@return The internal format capacity of the texture*/
	static ColorDepthStencilFormat getTextureInternalFormatProxy()
	{
		return (ColorDepthStencilFormat)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the layers of the texture image
	@return The layers of the texture image. The initial value is 0*/
	GLsizei getTextureLayers()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Returns the layers of the proxy texture
	@return The layers of the texture image*/
	static GLsizei getTextureLayersProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Gets the current texture magnification function. Used as the getter of <textureMagFilter> property
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.1) Gets the current texture minifying function. Used as the getter of <textureMinFilter> property
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.2) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns internal storage resolution of RED component of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLint getTextureRedSizeProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType()
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the type of RED component of the proxy texture
	@return The type of RED component of the proxy texture*/
	static TextureComponentType getTextureRedTypeProxy()
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the width of the texture image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth()
	{
		return _getTexLevelParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns the width of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei getTextureWidthProxy()
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns the wrapping function for texture coordinate r. Used as the getter of <textureWrapR> property
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_R);
	}

	/*(3.2) Returns the wrapping function for texture coordinate s. Used as the getter of <textureWrapS> property
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S);
	}

	/*(3.2) Returns the wrapping function for texture coordinate t. Used as the getter of <textureWrapT> property
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T);
	}

	/*(3.2) Determines if the texture object is currently bound to its target. Used as a getter of <textureBinding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBinding()
	{
		return _object_id() == _getInteger(GL_TEXTURE_BINDING_2D_MULTISAMPLE);
	}

	/*(3.2) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}. Used as the setter of <textureCompareFunc> property
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.2) Sets the texture comparison mode for currently bound depth textures. Used as the setter of <textureCompareMode> property
	@param Specifies the texture compare mode value*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.2) Sets the texture magnification function value. Used as the setter of <textureMagFilter> property
	@param Specifies the texture magnification function's value. The initial value is linear*/
	void setTextureMagFilter(TextureMagFilter filter)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*(3.2) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. Used as the setter of <textureMinFilter> property
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.2) Sets the wrapping function for texture coordinate r. Used as the setter of <textureWrapR> property
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate s. Used as the setter of <textureWrapS> property
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate t. Used as the setter of <textureWrapT> property
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.2) Set an empty texture object as a reference to the texture object from another context
	@param The texture object to share, must not be empty*/
	void shareTexture(Texture2DMultisample& texture)
	{
		_object_share((_Object&)texture);
	}

	/*(3.2) Establish the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <getMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	void texImage2DMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		_texImage2DMultisample(_tlsTexture2DMultisample(), samples, (GLenum)internalformat, width, height, fixedsamplelocations);
	}

	/*(3.2) Recalculate the capacity for the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <getMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	static void texImage2DMultisampleProxy(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		_texImage2DMultisample(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, (GLenum)internalformat, width, height, fixedsamplelocations);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property to determine if the texture object is currently bound to its target*/
	__declspec(property(get = isTextureBinding)) GLboolean textureBinding;

	/*(3.2) Read-write property for current texture comparison function*/
	__declspec(property(get = getTextureCompareFunc, put = setTextureCompareFunc)) CompareFunc textureCompareFunc;

	/*(3.2) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = getTextureCompareMode, put = setTextureCompareMode)) TextureCompareMode textureCompareMode;

	/*(3.2) Read-write property for current texture magnification function*/
	__declspec(property(get = getTextureMagFilter, put = setTextureMagFilter)) TextureMagFilter textureMagFilter;

	/*(3.2) Read-write property for current texture minifying function*/
	__declspec(property(get = getTextureMinFilter, put = setTextureMinFilter)) TextureMinFilter textureMinFilter;

	/*(3.2) Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = getTextureWrapR, put = setTextureWrapR)) TextureWrapMode textureWrapR;

	/*(3.2) Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = getTextureWrapS, put = setTextureWrapS)) TextureWrapMode textureWrapS;

	/*(3.2) Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = getTextureWrapT, put = setTextureWrapT)) TextureWrapMode textureWrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value. Used as the getter of <textureSwizzleA> property
	@return The alpha component swizzle value. The initial value is <Alpha>*/
	TextureSwizzleMask getTextureSwizzleA()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value. Used as the getter of <textureSwizzleB> property
	@return The blue component swizzle value. The initial value is <Blue>*/
	TextureSwizzleMask getTextureSwizzleB()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value. Used as the getter of <textureSwizzleG> property
	@return The green component swizzle value. The initial value is <Green>*/
	TextureSwizzleMask getTextureSwizzleG()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value. Used as the getter of <textureSwizzleR> property
	@return The red component swizzle value. The initial value is <Red>*/
	TextureSwizzleMask getTextureSwizzleR()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query
	@param [out] Stores four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void getTextureSwizzleRGBA(_Out_writes_(4) TextureSwizzleMask* swizzle)
	{
		_getTexParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader. Used as the setter of <textureSwizzleA> property
	@param The alpha component swizzle value. The initial value is <Alpha>*/
	void setTextureSwizzleA(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader. Used as the setter of <textureSwizzleB> property
	@param The blue component swizzle value. The initial value is <Blue>*/
	void setTextureSwizzleB(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader. Used as the setter of <textureSwizzleG> property
	@param The green component swizzle value. The initial value is <Green>*/
	void setTextureSwizzleG(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader. Used as the setter of <textureSwizzleR> property
	@param The red component swizzle value. The initial value is <Red>*/
	void setTextureSwizzleR(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void setTextureSwizzleRGBA(_In_reads_(4) const TextureSwizzleMask* swizzle)
	{
		_texParameter(_tlsTexture2DMultisample(), GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-write property for current alpha component swizzle value*/
	__declspec(property(get = getTextureSwizzleA, put = setTextureSwizzleA)) TextureSwizzleMask textureSwizzleA;

	/*(3.3) Read-write property for current blue component swizzle value*/
	__declspec(property(get = getTextureSwizzleB, put = setTextureSwizzleB)) TextureSwizzleMask textureSwizzleB;

	/*(3.3) Read-write property for current green component swizzle value*/
	__declspec(property(get = getTextureSwizzleG, put = setTextureSwizzleG)) TextureSwizzleMask textureSwizzleG;

	/*(3.3) Read-write property for current red component swizzle value*/
	__declspec(property(get = getTextureSwizzleR, put = setTextureSwizzleR)) TextureSwizzleMask textureSwizzleR;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_3
}; // class Texture2DMultisample : public _Texture
} // namespace gl {
#endif // #ifdef GL_VERSION_3_2
