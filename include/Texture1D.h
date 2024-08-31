#pragma once
#include "_Texture.h"
namespace gl {
/*OpenGL one-dimensional texture object class derived from <_Texture>*/
class Texture1D : public _Texture
{
public:
	/*(1) Constructs an empty texture object*/
	Texture1D() {}

	/*(2) Constucts a texture object with <shareTexture>*/
	Texture1D(Texture1D& texture)
	{
		shareTexture(texture);
	}

	/*(3) Constucts a texture object with <assignTexture>*/
	Texture1D(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, index);
	}

	/*Set an empty texture object as a reference to an element of the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_1D);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*Explicitly binds texture object to its target. Does nothing if specified texture is bound*/
	void bindTexture()
	{
		_bindTexture(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D);
	}

	/*(1) Specifies a one-dimensional texture image in a compressed format. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide, and 1 texel high
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void compressedTexImage(GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei imageSize, _In_ const void* data)
	{
		_compressedTexImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)internalformat, width, imageSize, data);
	}

	/*Recalculates the capacity of one-dimensional texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void compressedTexImageProxy(GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei imageSize)
	{
		_compressedTexImage1D(GL_PROXY_TEXTURE_1D, level, (GLenum)internalformat, width, imageSize, nullptr);
	}

	/*(1) Replaces a contiguous subregion of an existing one-dimensional texture image in a compressed format. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void compressedTexSubImage(GLint level, GLint xoffset, GLsizei width, CompressedTexInternalformat internalformat, GLsizei imageSize, _In_ const void* data)
	{
		_compressedTexSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)internalformat, imageSize, data);
	}

	/*Copies pixels into a one-dimensional texture image from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies the internal format of the texture
	@param Specifies the window x coordinate of the left corner of the row of pixels to be copied
	@param Specifies the window y coordinate of the left corner of the row of pixels to be copied
	@param Specifies the width of the texture image, the height of the image is 1*/
	void copyTexImage(GLint level, CopyTexInternalformat internalformat, GLint x, GLint y, GLsizei width)
	{
		_copyTexImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)internalformat, x, y, width);
	}

	/*Replaces a portion of a one-dimensional texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies the texel offset within the texture array
	@param Specifies the window x coordinate of the left corner of the row of pixels to be copied
	@param Specifies the window y coordinate of the left corner of the row of pixels to be copied
	@paran Specifies the width of the texture subimage*/
	void copyTexSubImage(GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		_copyTexSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, x, y, width);
	}

	/*Disable enabled one-dimensional texturing server-side GL capability, initially enabled*/
	static void disableTexture1D()
	{
		_disable(GL_TEXTURE_1D);
	}

	/*Enable one-dimensional texturing server-side GL capability, initially enabled*/
	static void enableTexture1D()
	{
		_enable(GL_TEXTURE_1D);
	}

	/*(1) Return a compressed one-dimensional texture image into client's memory of the size returned by <getTextureCompressedImageSize>. (2.1) Unbinds pixel pack buffer from its target
	@param Specifies the level-of-detail number of the desired image
	@param [out] Specifies a pointer to store the compressed texture image*/
	void getCompressedTexImage(GLint level, _Out_ void* pixels)
	{
		_getCompressedTexImage(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, pixels);
	}

	/*Returns a list of symbolic constants of length returned by <getNumCompressedTextureFormats> indicating which compressed texture formats are available
	@param [out] Pointer to an array of available compressed texture formats*/
	static void getCompressedTextureFormats(_Out_ CompressedTexInternalformat* internalformats)
	{
		_getInteger(GL_COMPRESSED_TEXTURE_FORMATS, (GLint*)internalformats);
	}

	/*Gets maximum absolute value of the texture level-of-detail bias
	@return The maximum texture level-of-detail bias. The value must be at least 2.0*/
	static GLfloat getMaxTextureLodBias()
	{
		return _getFloat(GL_MAX_TEXTURE_LOD_BIAS);
	}

	/*Returns the maximum supported texture image units that can be used to access texture maps from the vertex shader
	@return The maximum vertex texture image units. The value may be at least 16*/
	static GLint getMaxVertexTextureImageUnits()
	{
		return _getInteger(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	}

	/*Gets the number of available compressed texture formats
	@return number of available compressed texture formats. The minimum value is 4*/
	static GLuint getNumCompressedTextureFormats()
	{
		return _getInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
	}

	/*(1) Returns a one-dimensional texture image into client's memory. (2.1) Unbinds pixel pack buffer from its target
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void getTexImage(GLint level, GetTexFormat format, GetTexType type, _Out_ void* pixels)
	{
		_getTexImage(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)format, (GLenum)type, pixels);
	}

	/*Returns internal storage resolution of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLint getTextureAlphaSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*Returns internal storage resolution of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of ALPHA component*/
	static GLint getTextureAlphaSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*Returns the current base texture mipmap level. Used as a getter of <textureBaseLevel> property
	@return The lowest defined mipmap level. The initial value is 0*/
	GLint getTextureBaseLevel()
	{
		return _getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BASE_LEVEL);
	}

	/*Returns internal storage resolution of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*Returns internal storage resolution of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	static GLint getTextureBlueSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color)
	{
		_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color)
	{
		_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*Returns the current texture comparison function. Used as a getter of <textureCompareFunc> property
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_COMPARE_FUNC);
	}

	/*Returns boolean value indicating if the texture image is stored in a compressed internal format
	@param Specifies the level-of-detail number of the desired image
	@return True if the texture image is stored in a compressed internal format, false otherwise*/
	GLboolean getTextureCompressed(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_COMPRESSED);
	}

	/*Returns boolean value indicating if the proxy texture was queried in a compressed internal format
	@param Specifies the level-of-detail number of the proxy texture
	@return True if the proxy texture was queried as compressed, false otherwise*/
	static GLboolean getTextureCompressedProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_COMPRESSED);
	}

	/*Returns the number of unsigned bytes of the compressed texture image that would be returned from <getCompressedTexImage>
	@param Specifies the level-of-detail number of the desired image
	@return The number of unsigned bytes of the compressed texture image*/
	GLsizei getTextureCompressedImageSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*Returns the number of unsigned bytes of the compressed proxy texture that would be returned from <getCompressedTexImage>
	@param Specifies the level-of-detail number of the proxy texture
	@return The number of unsigned bytes of the compressed proxy texture*/
	static GLsizei getTextureCompressedImageSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*Gets a value indicating the mode of the texture compression hint
	@return The desired behavior hint. The initial value is <DontCare>*/
	static BehaviorHint getTextureCompressionHint()
	{
		return (BehaviorHint)_getInteger(GL_TEXTURE_COMPRESSION_HINT);
	}

	/*Returns internal storage resolution of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*Returns internal storage resolution of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLint getTextureDepthSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*Returns internal storage resolution of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*Returns internal storage resolution of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLint getTextureGreenSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*Returns the internal format of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal format of the texture image*/
	TexInternalformat getTextureInternalFormat(GLint level)
	{
		return (TexInternalformat)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*Returns the internal format capacity of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal format capacity of the texture*/
	static TexInternalformat getTextureInternalFormatProxy(GLint level)
	{
		return (TexInternalformat)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*Returns the current fixed level-of-detail bias value. Used as a getter of <textureLodBias> property
	@return The texture level-of-detail bias value*/
	GLfloat getTextureLodBias()
	{
		return _getTexParameterFloat(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_LOD_BIAS);
	}

	/*Gets the current texture magnification function. Used as a getter of <textureMagFilter> property
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAG_FILTER);
	}

	/*Returns the current maximum texture mipmap array level. Used as a getter of <textureMaxLevel> property
	@return The texture maximum mipmap level. The initial value is 1000*/
	GLint getTextureMaxLevel()
	{
		return _getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAX_LEVEL);
	}

	/*Returns the current texture maximum level-of-detail value. Used as a getter of <textureMaxLod> property
	@return The maximum level-of-detail value. The initial value is 1000*/
	GLfloat getTextureMaxLod()
	{
		return _getTexParameterFloat(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAX_LOD);
	}

	/*Gets the current texture minifying function. Used as a getter of <textureMinFilter> property
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MIN_FILTER);
	}

	/*Returns the current texture minimum level-of-detail value. Used as a getter of <textureMinLod> property
	@return The minimum level-of-detail value. The initial value is -1000*/
	GLfloat getTextureMinLod()
	{
		return _getTexParameterFloat(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MIN_LOD);
	}

	/*Returns internal storage resolution of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_RED_SIZE);
	}

	/*Returns internal storage resolution of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLint getTextureRedSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_RED_SIZE);
	}

	/*Returns the width of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth(GLint level)
	{
		return _getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_WIDTH);
	}

	/*Returns the width of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei getTextureWidthProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_WIDTH);
	}

	/*Returns the wrapping function for texture coordinate r. Used as a getter of <textureWrapR> property
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_R);
	}

	/*Returns the wrapping function for texture coordinate s. Used as a getter of <textureWrapS> property
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_S);
	}

	/*Returns the wrapping function for texture coordinate t. Used as a getter of <textureWrapT> property
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_T);
	}

	/*Checks if one-dimensional texturing server-side GL capability is enabled, initially disabled
	@return True if one-dimensional texturing GL capability is enabled, false otherwise*/
	static GLboolean isTexture1D()
	{
		return _isEnabled(GL_TEXTURE_1D);
	}

	/*Determines if the texture object is currently bound to its target. Used as a getter of <textureBinding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBinding()
	{
		return _object_id() == (GLuint)_getInteger(GL_TEXTURE_BINDING_1D);
	}

	/*Specifies the index of the lowest defined mipmap level. Used as a setter of <textureBaseLevel> property
	@param The lowest defined mipmap level. The initial value is 0*/
	void setTextureBaseLevel(GLint level)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BASE_LEVEL, level);
	}

	/*Sets the binding state of the texture object, only if current state is opposite. Used as a setter of <textureBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setTextureBinding(GLboolean bind)
	{
		_setTextureBinding(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, bind);
	}

	/*(1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}. Used as a setter of <textureCompareFunc> property
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*Indicates the quality and performance of the compressing texture images. Hinting <Fastest> indicates that texture images should be compressed as quickly as possible, while <Nicest> indicates that texture images should be compressed with as little image quality loss as possible
	@param Specifies a symbolic constant indicating the desired behavior*/
	static void setTextureCompressionHint(BehaviorHint hint)
	{
		_hint(GL_TEXTURE_COMPRESSION_HINT, (GLenum)hint);
	}

	/*Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling. Used as a setter of <textureLodBias> property
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void setTextureLodBias(GLfloat bias)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_LOD_BIAS, bias);
	}

	/*Sets the texture magnification function value. Used as a setter of <textureMagFilter> property
	@param Specifies the texture magnification function's value. The initial value is linear*/
	void setTextureMagFilter(TextureMagFilter filter)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*Sets the index of the highest defined mipmap level. Used as a setter of <textureMaxLevel> property
	@param The texture maximum mipmap level. The initial value is 1000*/
	void setTextureMaxLevel(GLint maxlevel)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAX_LEVEL, maxlevel);
	}

	/*Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap. Used as a setter of <textureMaxLod> property
	@param The maximum level-of-detail value. The initial value is 1000*/
	void setTextureMaxLod(GLfloat maxlod)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. Used as a setter of <textureMinFilter> property
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap. Used as a setter of <textureMinLod> property
	@param The minimum level-of-detail value. The initial value is -1000*/
	void setTextureMinLod(GLfloat minlod)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_MIN_LOD, minlod);
	}

	/*Sets the wrapping function for texture coordinate r. Used as a setter of <textureWrapR> property
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*Sets the wrapping function for texture coordinate s. Used as a setter of <textureWrapS> property
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*Sets the wrapping function for texture coordinate t. Used as a setter of <textureWrapT> property
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*Set an empty texture object as a reference to the texture object from another context
	@param The texture object to share, must not be empty*/
	void shareTexture(Texture1D& texture)
	{
		_object_share((_Object&)texture);
	}

	/*(1) Specifies a one-dimensional texture image initialized from the StbImage object. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void texImage(StbImage& image, GLint level, TexInternalformat internalformat)
	{
		_texImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, image);
	}

	/*(2) Specifies a one-dimensional texture image initialized from client's memory. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide, and 1 texel high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void texImage(GLint level, TexInternalformat internalformat, GLsizei width, TexFormat format, TexType type, _In_ const void* data)
	{
		_texImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type, data);
	}

	/*Recalculates the capacity for the one-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void texImageProxy(GLint level, TexInternalformat internalformat, GLsizei width, TexFormat format, TexType type)
	{
		_texImage1D(GL_PROXY_TEXTURE_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type, nullptr);
	}

	/*(1) Replaces a contiguous subregion of an existing one-dimensional texture image copied from the StbImage object. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the StbImage object with loaded image*/
	void texSubImage(StbImage& image, GLint level, GLint xoffset)
	{
		_texSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, image);
	}

	/*(2) Replaces a contiguous subregion of an existing one-dimensional texture image copied from client's memory data store. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void texSubImage(GLint level, GLint xoffset, GLsizei width, TexFormat format, TexType type, _In_ const void* pixels)
	{
		_texSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)format, (GLenum)type, pixels);
	}

	/*Explicitly unbinds any texture object of specified type bound to its target. Does nothing if no such texture is bound*/
	static void unbindTarget()
	{
		_unbindTarget(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D);
	}

	/*Explicitly unbinds specified texture object from its target. Does nothing if specified texture is not bound*/
	void unbindTexture()
	{
		_unbindTexture(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for index of the lowest defined mipmap level*/
	__declspec(property(get = getTextureBaseLevel, put = setTextureBaseLevel)) GLint textureBaseLevel;

	/*Read-write property for state of the texture binding*/
	__declspec(property(get = isTextureBinding, put = setTextureBinding)) GLboolean textureBinding;

	/*Read-write property for current texture comparison function*/
	__declspec(property(get = getTextureCompareFunc, put = setTextureCompareFunc)) CompareFunc textureCompareFunc;

	/*Read-write property for current fixed level-of-detail bias value*/
	__declspec(property(get = getTextureLodBias, put = setTextureLodBias)) GLfloat textureLodBias;

	/*Read-write property for current texture magnification function*/
	__declspec(property(get = getTextureMagFilter, put = setTextureMagFilter)) TextureMagFilter textureMagFilter;

	/*Read-write property for current maximum texture mipmap array level*/
	__declspec(property(get = getTextureMaxLevel, put = setTextureMaxLevel)) GLint textureMaxLevel;

	/*Read-write property for current texture maximum level-of-detail value*/
	__declspec(property(get = getTextureMaxLod, put = setTextureMaxLod)) GLfloat textureMaxLod;

	/*Read-write property for current texture minifying function*/
	__declspec(property(get = getTextureMinFilter, put = setTextureMinFilter)) TextureMinFilter textureMinFilter;

	/*Read-write property for current texture minimum level-of-detail value*/
	__declspec(property(get = getTextureMinLod, put = setTextureMinLod)) GLfloat textureMinLod;

	/*Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = getTextureWrapR, put = setTextureWrapR)) TextureWrapMode textureWrapR;

	/*Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = getTextureWrapS, put = setTextureWrapS)) TextureWrapMode textureWrapS;

	/*Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = getTextureWrapT, put = setTextureWrapT)) TextureWrapMode textureWrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_2_1
	/*(2.1) (2) Specifies a one-dimensional texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide, and 1 texel high
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void compressedTexImage(PixelUnpackBuffer& buffer, GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei imageSize, GLintptr offset)
	{
		_compressedTexImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)internalformat, width, imageSize, (_Buffer&)buffer, offset);
	}

	/*(2.1) (2) Replaces a contiguous subregion of an existing one-dimensional texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store*/
	void compressedTexSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLsizei width, CompressedTexInternalformat internalformat, GLsizei imageSize, GLintptr offset)
	{
		_compressedTexSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)internalformat, imageSize, (_Buffer&)buffer, offset);
	}

	/*(2.1) (2) Return a compressed one-dimensional texture image into pixel pack buffer data store of the size returned by <getTextureCompressedImageSize>
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies the byte offset into PBO data store*/
	void getCompressedTexImage(PixelPackBuffer& buffer, GLint level, GLintptr offset)
	{
		_getCompressedTexImage(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (_Buffer&)buffer, offset);
	}

	/*(2.1) (2) Returns a one-dimensional texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void getTexImage(PixelPackBuffer& buffer, GLint level, GetTexFormat format, GetTexType type, GLintptr offset)
	{
		_getTexImage(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(2.1) (3) Specifies a one-dimensional texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide, and 1 texel high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void texImage(PixelUnpackBuffer& buffer, GLint level, TexInternalformat internalformat, GLsizei width, TexFormat format, TexType type, GLintptr offset)
	{
		_texImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(2.1) (3) Specifies a one-dimensional texture subimage copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void texSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLsizei width, TexFormat format, TexType type, GLintptr offset)
	{
		_texSubImage1D(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) Generates mipmaps for specified texture target*/
	void generateMipmap()
	{
		_generateMipmap(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D);
	}
 
	/*(3.0) Returns the type of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static TextureComponentType getTextureAlphaTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static TextureComponentType getTextureBlueTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Gets the texture comparison mode for currently bound depth textures. Used as a getter of <textureCompareMode> property
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.0) Returns the type of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static TextureComponentType getTextureDepthTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static TextureComponentType getTextureGreenTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Returns the type of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of RED component of the proxy texture*/
	static TextureComponentType getTextureRedTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Sets the texture comparison mode for currently bound depth textures. Used as a setter of <textureCompareMode> property
	@param Specifies the texture compare mode value*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = getTextureCompareMode, put = setTextureCompareMode)) TextureCompareMode textureCompareMode;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value. Used as a getter of <textureSwizzleA> property
	@return The alpha component swizzle value. The initial value is <Alpha>*/
	TextureSwizzleMask getTextureSwizzleA()
	{
		return (TextureSwizzleMask)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value. Used as a getter of <textureSwizzleB> property
	@return The blue component swizzle value. The initial value is <Blue>*/
	TextureSwizzleMask getTextureSwizzleB()
	{
		return (TextureSwizzleMask)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value. Used as a getter of <textureSwizzleG> property
	@return The green component swizzle value. The initial value is <Green>*/
	TextureSwizzleMask getTextureSwizzleG()
	{
		return (TextureSwizzleMask)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value. Used as a getter of <textureSwizzleR> property
	@return The red component swizzle value. The initial value is <Red>*/
	TextureSwizzleMask getTextureSwizzleR()
	{
		return (TextureSwizzleMask)_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query
	@param [out] Stores four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void getTextureSwizzleRGBA(_Out_writes_(4) TextureSwizzleMask* swizzle)
	{
		_getTexParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader. Used as a setter of <textureSwizzleA> property
	@param The alpha component swizzle value. The initial value is <Alpha>*/
	void setTextureSwizzleA(TextureSwizzleMask swizzle)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader. Used as a setter of <textureSwizzleB> property
	@param The blue component swizzle value. The initial value is <Blue>*/
	void setTextureSwizzleB(TextureSwizzleMask swizzle)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader. Used as a setter of <textureSwizzleG> property
	@param The green component swizzle value. The initial value is <Green>*/
	void setTextureSwizzleG(TextureSwizzleMask swizzle)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader. Used as a setter of <textureSwizzleR> property
	@param The red component swizzle value. The initial value is <Red>*/
	void setTextureSwizzleR(TextureSwizzleMask swizzle)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void setTextureSwizzleRGBA(_In_reads_(4) const TextureSwizzleMask* swizzle)
	{
		_texParameter(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
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
}; // class Texture1D : public _Texture

/*Explicitly unbinds any texture object of specified type bound to its target. Does nothing if no such texture is bound*/
inline void unbindTexture1D()
{
	Texture1D::unbindTarget();
}
} // namespace gl
