#pragma once
#include "gladpp.h"
#include "_Texture.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL one-dimensional multi-layered texture object class derived from <_Texture>*/
class Texture1DArray : public _Texture
{
public:
	/*(3.0) (1) Constructs an empty texture object*/
	Texture1DArray() {}

	/*(3.0) (2) Constucts a texture object with <shareTexture>*/
	Texture1DArray(Texture1DArray& texture)
	{
		shareTexture(texture);
	}

	/*(3.0) (3) Constucts a texture object with <assignTexture>*/
	Texture1DArray(Textures& textures, GLuint index)
	{
		assignTexture(textures, index);
	}

	/*(3.0) Select active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. Similar to global <activeTexture>, but also unconditionally binds the texture to its target after selection
	@param Specifies the index of texture unit to make active, initial is 0*/
	void activeTexture(TextureUnit index)
	{
		_activeTexture(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, index);
	}

	/*(3.0) Set an empty texture object as a reference to an element of the texture multi-object
	@param The texture multi-object
	@param The index of the object name*/
	void assignTexture(Textures& textures, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)textures, index, GL_TEXTURE_1D_ARRAY);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)textures, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Explicitly binds texture object to its target*/
	void bindTexture()
	{
		_texture_rebind(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY);
	}

	/*(3.0) (1) Specifies a one-dimensional multi-layered texture image in a compressed format. Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void compressedTexImage2D(GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei layers, GLsizei imageSize, _In_ const void* data)
	{
		_compressedTexImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLenum)internalformat, width, layers, imageSize, data);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void compressedTexImage2D(PixelUnpackBuffer& buffer, GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei layers, GLsizei imageSize, GLintptr offset)
	{
		_compressedTexImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLenum)internalformat, width, layers, imageSize, (_Buffer&)buffer, offset);
	}

	/*(3.0) Recalculates the capacity of one-dimensional multi-layered texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void compressedTexImage2DProxy(GLint level, CompressedTexInternalformat internalformat, GLsizei width, GLsizei layers, GLsizei imageSize)
	{
		_compressedTexImage2D(GL_PROXY_TEXTURE_1D_ARRAY, level, (GLenum)internalformat, width, layers, imageSize, nullptr);
	}

	/*(3.0) (1) Replaces a contiguous subregion of an existing one-dimensional multi-layered texture image in a compressed format. Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void compressedTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, CompressedTexInternalformat internalformat, GLsizei imageSize, _In_ const void* data)
	{
		_compressedTexSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)internalformat, imageSize, data);
	}

	/*(3.0) (2) Replaces a contiguous subregion of an existing one-dimensional multi-layered texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used as a source of subimage
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void compressedTexSubImage2D(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, CompressedTexInternalformat internalformat, GLsizei imageSize, GLintptr offset)
	{
		_compressedTexSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)internalformat, imageSize, (_Buffer&)buffer, offset);
	}

	/*(3.0) Replaces a linear portion of a number of slices of a one-dimensional multi-layered texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void copyTexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		_copyTexSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, x, y, width, height);
	}

	/*(3.0) Unbinds any previously bound texture object, and restores the default texture for its target. Does nothing if no such texture is bound*/
	static void defaultTexture()
	{
		_texture_unbind(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY);
	}

	/*(3.0) Generates mipmaps for specified texture target*/
	void generateMipmap()
	{
		_generateMipmap(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY);
	}

	/*(3.0) (1) Return a compressed one-dimensional multi-layered texture image into client's memory of the size returned by <getTextureCompressedImageSize>. (2.1) Unbinds pixel pack buffer from its target
	@param Specifies the level-of-detail number of the desired image
	@param [out] Specifies a pointer to store the compressed texture image*/
	void getCompressedTexImage(GLint level, _Out_ void* pixels)
	{
		_getCompressedTexImage(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, pixels);
	}

	/*(3.0) (2) Return a compressed one-dimensional multi-layered texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies the byte offset into PBO data store*/
	void getCompressedTexImage(PixelPackBuffer& buffer, GLint level, GLintptr offset)
	{
		_getCompressedTexImage(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (_Buffer&)buffer, offset);
	}

	/*(3.0) Returns a list of symbolic constants of length returned by <getNumCompressedTextureFormats> indicating which compressed texture formats are available
	@param [out] Pointer to an array of available compressed texture formats*/
	static void getCompressedTextureFormats(_Out_ CompressedTexInternalformat* internalformats)
	{
		_getInteger(GL_COMPRESSED_TEXTURE_FORMATS, (GLint*)internalformats);
	}

	/*(3.0) Gets the value that indicates the maximum number of layers allowed in an array texture
	@return The maximum array texture layers. Must be at least 256*/
	static GLsizei getMaxArrayTextureLayers()
	{
		return _getInteger(GL_MAX_ARRAY_TEXTURE_LAYERS);
	}

	/*(3.0) Gets maximum absolute value of the texture level-of-detail bias
	@return The maximum texture level-of-detail bias. The value must be at least 2.0*/
	static GLfloat getMaxTextureLodBias()
	{
		return _getFloat(GL_MAX_TEXTURE_LOD_BIAS);
	}

	/*(3.0) Returns the maximum supported texture image units that can be used to access texture maps from the vertex shader
	@return The maximum vertex texture image units. The value may be at least 16*/
	static GLint getMaxVertexTextureImageUnits()
	{
		return _getInteger(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	}

	/*(3.0) Gets the number of available compressed texture formats
	@return number of available compressed texture formats. The minimum value is 4*/
	static GLuint getNumCompressedTextureFormats()
	{
		return _getInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
	}

	/*(3.0) (1) Returns a one-dimensional multi-layered texture image into client's memory. Unbinds pixel pack buffer from its target
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void getTexImage(GLint level, GetTexFormat format, GetTexType type, _Out_ void* pixels)
	{
		_getTexImage(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (2) Returns a one-dimensional multi-layered texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer used for storing the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void getTexImage(PixelPackBuffer& buffer, GLint level, GetTexFormat format, GetTexType type, GLintptr offset)
	{
		_getTexImage(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(3.0) Returns internal storage resolution of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLint getTextureAlphaSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.0) Returns internal storage resolution of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of ALPHA component*/
	static GLint getTextureAlphaSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.0) Returns the type of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of ALPHA component of the texture image*/
	TextureComponentType getTextureAlphaType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static TextureComponentType getTextureAlphaTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the current base texture mipmap level
	@return The lowest defined mipmap level. The initial value is 0*/
	GLint getTextureBaseLevel()
	{
		return _getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BASE_LEVEL);
	}

	/*(3.0) Returns internal storage resolution of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLint getTextureBlueSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.0) Returns internal storage resolution of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	static GLint getTextureBlueSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.0) Returns the type of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of BLUE component of the texture image*/
	TextureComponentType getTextureBlueType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static TextureComponentType getTextureBlueTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color)
	{
		_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color)
	{
		_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) Returns the current texture comparison function
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.0) Gets the texture comparison mode for currently bound depth textures
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.0) Returns boolean value indicating if the texture image is stored in a compressed internal format
	@param Specifies the level-of-detail number of the desired image
	@return True if the texture image is stored in a compressed internal format, false otherwise*/
	GLboolean getTextureCompressed(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_COMPRESSED);
	}

	/*(3.0) Returns boolean value indicating if the proxy texture was queried in a compressed internal format
	@param Specifies the level-of-detail number of the proxy texture
	@return True if the proxy texture was queried as compressed, false otherwise*/
	static GLboolean getTextureCompressedProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_COMPRESSED);
	}

	/*(3.0) Returns the number of unsigned bytes of the compressed texture image that would be returned from <getCompressedTexImage>
	@param Specifies the level-of-detail number of the desired image
	@return The number of unsigned bytes of the compressed texture image*/
	GLsizei getTextureCompressedImageSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*(3.0) Returns the number of unsigned bytes of the compressed proxy texture that would be returned from <getCompressedTexImage>
	@param Specifies the level-of-detail number of the proxy texture
	@return The number of unsigned bytes of the compressed proxy texture*/
	static GLsizei getTextureCompressedImageSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*(3.0) Gets a value indicating the mode of the texture compression hint
	@return The desired behavior hint. The initial value is <DontCare>*/
	static BehaviorHint getTextureCompressionHint()
	{
		return (BehaviorHint)_getInteger(GL_TEXTURE_COMPRESSION_HINT);
	}

	/*(3.0) Returns internal storage resolution of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLint getTextureDepthSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.0) Returns internal storage resolution of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLint getTextureDepthSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.0) Returns the type of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of DEPTH component of the texture image*/
	TextureComponentType getTextureDepthType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static TextureComponentType getTextureDepthTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns internal storage resolution of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLint getTextureGreenSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.0) Returns internal storage resolution of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLint getTextureGreenSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.0) Returns the type of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of GREEN component of the texture image*/
	TextureComponentType getTextureGreenType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static TextureComponentType getTextureGreenTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the height of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The height of the texture image. The initial value is 0*/
	GLsizei getTextureHeight(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei getTextureHeightProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) Returns the internal format of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal format of the texture image*/
	TexInternalformat getTextureInternalFormat(GLint level)
	{
		return (TexInternalformat)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.0) Returns the internal format capacity of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal format capacity of the texture*/
	static TexInternalformat getTextureInternalFormatProxy(GLint level)
	{
		return (TexInternalformat)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.0) Returns the number of layers of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The number of layers of the texture image. The initial value is 0*/
	GLsizei getTextureLayers(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns the number of layers of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The number of layers of the texture image*/
	static GLsizei getTextureLayersProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns the current fixed level-of-detail bias value
	@return The texture level-of-detail bias value*/
	GLfloat getTextureLodBias()
	{
		return _getTexParameterFloat(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_LOD_BIAS);
	}

	/*(3.0) Gets the current texture magnification function
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.0) Returns the current maximum texture mipmap array level
	@return The texture maximum mipmap level. The initial value is 1000*/
	GLint getTextureMaxLevel()
	{
		return _getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAX_LEVEL);
	}

	/*(3.0) Returns the current texture maximum level-of-detail value
	@return The maximum level-of-detail value. The initial value is 1000*/
	GLfloat getTextureMaxLod()
	{
		return _getTexParameterFloat(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAX_LOD);
	}

	/*(3.0) Gets the current texture minifying function
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.0) Returns the current texture minimum level-of-detail value
	@return The minimum level-of-detail value. The initial value is -1000*/
	GLfloat getTextureMinLod()
	{
		return _getTexParameterFloat(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_LOD);
	}

	/*(3.0) Returns internal storage resolution of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLint getTextureRedSize(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_RED_SIZE);
	}

	/*(3.0) Returns internal storage resolution of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLint getTextureRedSizeProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_RED_SIZE);
	}

	/*(3.0) Returns the type of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of RED component of the texture image*/
	TextureComponentType getTextureRedType(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Returns the type of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of RED component of the proxy texture*/
	static TextureComponentType getTextureRedTypeProxy(GLint level)
	{
		return (TextureComponentType)_getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Returns the width of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The width of the texture image. The initial value is 0*/
	GLsizei getTextureWidth(GLint level)
	{
		return _getTexLevelParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, GL_TEXTURE_WIDTH);
	}

	/*(3.0) Returns the width of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei getTextureWidthProxy(GLint level)
	{
		return _getTexLevelParameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_WIDTH);
	}

	/*(3.0) Returns the wrapping function for texture coordinate r
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_R);
	}

	/*(3.0) Returns the wrapping function for texture coordinate s
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S);
	}

	/*(3.0) Returns the wrapping function for texture coordinate t
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_T);
	}

	/*(3.0) Determines via API if the texture object is currently bound to its target
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean isTextureBinding1DArray()
	{
		return _object_id() == _getInteger(GL_TEXTURE_BINDING_1D_ARRAY);
	}

	/*(3.0) Specifies the index of the lowest defined mipmap level
	@param The lowest defined mipmap level. The initial value is 0*/
	void setTextureBaseLevel(GLint level)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BASE_LEVEL, level);
	}

	/*(3.0) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.0) Sets the texture comparison mode for currently bound depth textures
	@param Specifies the texture compare mode value*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.0) Indicates the quality and performance of the compressing texture images. Hinting <Fastest> indicates that texture images should be compressed as quickly as possible, while <Nicest> indicates that texture images should be compressed with as little image quality loss as possible
	@param Specifies a symbolic constant indicating the desired behavior*/
	static void setTextureCompressionHint(BehaviorHint hint)
	{
		_hint(GL_TEXTURE_COMPRESSION_HINT, (GLenum)hint);
	}

	/*(3.0) Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void setTextureLodBias(GLfloat bias)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_LOD_BIAS, bias);
	}

	/*(3.0) Sets the texture magnification function value
	@param Specifies the texture magnification function's value. The initial value is linear*/
	void setTextureMagFilter(TextureMagFilter filter)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*(3.0) Sets the index of the highest defined mipmap level
	@param The texture maximum mipmap level. The initial value is 1000*/
	void setTextureMaxLevel(GLint maxlevel)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAX_LEVEL, maxlevel);
	}

	/*(3.0) Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap
	@param The maximum level-of-detail value. The initial value is 1000*/
	void setTextureMaxLod(GLfloat maxlod)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*(3.0) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.0) Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap
	@param The minimum level-of-detail value. The initial value is -1000*/
	void setTextureMinLod(GLfloat minlod)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_LOD, minlod);
	}

	/*(3.0) Sets the wrapping function for texture coordinate r
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.0) Sets the wrapping function for texture coordinate s
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.0) Sets the wrapping function for texture coordinate t
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.0) Set an empty texture object as a reference to the texture object from another context
	@param The texture object to share, must not be empty*/
	void shareTexture(Texture1DArray& texture)
	{
		_object_share((_Object&)texture);
	}

	/*(3.0) (1) Specifies a one-dimensional multi-layered texture image initialized from the StbImage object. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void texImage2D(StbImage& image, GLint level, TexInternalformat internalformat)
	{
		_texImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLint)internalformat, image);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture image initialized from client's memory. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void texImage2D(GLint level, TexInternalformat internalformat, GLsizei width, GLsizei layers, TexFormat format, TexType type, _In_ const void* data)
	{
		_texImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type, data);
	}

	/*(3.0) (3) Specifies a one-dimensional multi-layered texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void texImage2D(PixelUnpackBuffer& buffer, GLint level, TexInternalformat internalformat, GLsizei width, GLsizei layers, TexFormat format, TexType type, GLintptr offset)
	{
		_texImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

	/*(3.0) Recalculates the capacity for a one-dimensional multi-layered texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void texImage2DProxy(GLint level, TexInternalformat internalformat, GLsizei width, GLsizei layers, TexFormat format, TexType type)
	{
		_texImage2D(GL_PROXY_TEXTURE_2D, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type, nullptr);
	}

	/*(3.0) (1) Specifies a one-dimensional multi-layered texture subimage copied from the StbImage object. Unbinds pixel unpack buffer from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array*/
	void texSubImage2D(StbImage& image, GLint level, GLint xoffset, GLint yoffset)
	{
		_texSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, image);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture subimage copied from client's memory data store. Unbinds pixel unpack buffer from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void texSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, TexSubFormat format, TexSubType type, _In_ const void* pixels)
	{
		_texSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (3) Specifies a two-dimensional texture subimage copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void texSubImage2D(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, TexSubFormat format, TexSubType type, GLintptr offset)
	{
		_texSubImage2D(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)format, (GLenum)type, (_Buffer&)buffer, offset);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for index of the lowest defined mipmap level*/
	__declspec(property(get = getTextureBaseLevel, put = setTextureBaseLevel)) GLint textureBaseLevel;

	/*(3.0) Read-write property for current texture comparison function*/
	__declspec(property(get = getTextureCompareFunc, put = setTextureCompareFunc)) CompareFunc textureCompareFunc;

	/*(3.0) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = getTextureCompareMode, put = setTextureCompareMode)) TextureCompareMode textureCompareMode;

	/*(3.0) Read-write property for mode of the texture compression hint*/
	__declspec(property(get = getTextureCompressionHint, put = setTextureCompressionHint)) BehaviorHint textureCompressionHint;

	/*(3.0) Read-write property for current fixed level-of-detail bias value*/
	__declspec(property(get = getTextureLodBias, put = setTextureLodBias)) GLfloat textureLodBias;

	/*(3.0) Read-write property for current texture magnification function*/
	__declspec(property(get = getTextureMagFilter, put = setTextureMagFilter)) TextureMagFilter textureMagFilter;

	/*(3.0) Read-write property for current maximum texture mipmap array level*/
	__declspec(property(get = getTextureMaxLevel, put = setTextureMaxLevel)) GLint textureMaxLevel;

	/*(3.0) Read-write property for current texture maximum level-of-detail value*/
	__declspec(property(get = getTextureMaxLod, put = setTextureMaxLod)) GLfloat textureMaxLod;

	/*(3.0) Read-write property for current texture minifying function*/
	__declspec(property(get = getTextureMinFilter, put = setTextureMinFilter)) TextureMinFilter textureMinFilter;

	/*(3.0) Read-write property for current texture minimum level-of-detail value*/
	__declspec(property(get = getTextureMinLod, put = setTextureMinLod)) GLfloat textureMinLod;

	/*(3.0) Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = getTextureWrapR, put = setTextureWrapR)) TextureWrapMode textureWrapR;

	/*(3.0) Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = getTextureWrapS, put = setTextureWrapS)) TextureWrapMode textureWrapS;

	/*(3.0) Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = getTextureWrapT, put = setTextureWrapT)) TextureWrapMode textureWrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value
	@return The alpha component swizzle value. The initial value is <Alpha>*/
	TextureSwizzleMask getTextureSwizzleA()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value
	@return The blue component swizzle value. The initial value is <Blue>*/
	TextureSwizzleMask getTextureSwizzleB()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value
	@return The green component swizzle value. The initial value is <Green>*/
	TextureSwizzleMask getTextureSwizzleG()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value
	@return The red component swizzle value. The initial value is <Red>*/
	TextureSwizzleMask getTextureSwizzleR()
	{
		return (TextureSwizzleMask)_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query
	@param [out] Stores four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void getTextureSwizzleRGBA(_Out_writes_(4) TextureSwizzleMask* swizzle)
	{
		_getTexParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader
	@param The alpha component swizzle value. The initial value is <Alpha>*/
	void setTextureSwizzleA(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader
	@param The blue component swizzle value. The initial value is <Blue>*/
	void setTextureSwizzleB(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader
	@param The green component swizzle value. The initial value is <Green>*/
	void setTextureSwizzleG(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader
	@param The red component swizzle value. The initial value is <Red>*/
	void setTextureSwizzleR(TextureSwizzleMask swizzle)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four TextureSwizzleMask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void setTextureSwizzleRGBA(_In_reads_(4) const TextureSwizzleMask* swizzle)
	{
		_texParameter(_tlsTexture1DArray(), GL_TEXTURE_1D_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
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
}; // class Texture1DArray : public _Texture
} // namespace gl {
#endif // #ifdef GL_VERSION_3_0
