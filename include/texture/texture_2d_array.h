#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_TEXTURE_2D_ARRAY_H
#define YAGLPP_TEXTURE_2D_ARRAY_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL multiple two-dimensional multi-layered texture object class derived from <Textures>*/
class Texture2DArray : public Textures
{
public:
	using Textures::Textures;
	/*(3.0) Binds texture object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(glBindTexture, GL_TEXTURE_2D_ARRAY);
	}

	/*(3.0) (1) Specifies a two-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the layers of the texture image. Supports images with at least 16 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, internalformat, width, height, layers, imageSize, data);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the layers of the texture image. Supports images with at least 16 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, internalformat, width, height, layers, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Recalculates the capacity of two-dimensional multi-layered texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the layers of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize)
	{
		compressed_proxy_image_3d(GL_PROXY_TEXTURE_2D_ARRAY, level, internalformat, width, height, layers, imageSize);
	}

	/*(3.0) (1) Replaces a contiguous subregion of an existing two-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, internalformat, imageSize, data);
	}

	/*(3.0) (2) Replaces a contiguous subregion of an existing two-dimensional multi-layered texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used as a source of subimage
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the depth of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Replaces a rectangular portion of a two-dimensional multi-layered texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	/*(3.0) Generates OpenGL texture object name in an empty texture class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenTextures, glBindTexture, GL_TEXTURE_2D_ARRAY);
	}

	/*(3.0) Generates mipmaps for specified texture target*/
	void GenerateMipmap()
	{
		generate_mipmap(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY);
	}

	/*(3.0) Returns internal storage resolution of ALPHA component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	GLuint GetAlphaSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.0) Returns the type of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of ALPHA component of the texture image*/
	ComponentType GetAlphaType(GLint level)
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the current base texture mipmap level. The initial value is 0. MSVC getter for <baseLevel> property
	@return The lowest defined mipmap level*/
	GLint GetBaseLevel()
	{
		return get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BASE_LEVEL);
	}

	/*(3.0) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2DArray GetBinding()
	{
		return Texture2DArray(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D_ARRAY));
	}

	/*(3.0) Returns internal storage resolution of BLUE component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	GLuint GetBlueSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.0) Returns the type of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of BLUE component of the texture image*/
	ComponentType GetBlueType(GLint level)
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) (1) Returns four integer values that comprise the current RGBA color of the texture border. The initial value is (0, 0, 0, 0)
	@param [out] Stores four integer texture color values*/
	void GetBorderColor(_Out_writes_(4) GLint* color)
	{
		get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) (2) Returns four float values that comprise the current RGBA color of the texture border. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [out] Stores four float texture color values*/
	void GetBorderColor(_Out_writes_(4) GLfloat* color)
	{
		get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) Returns the current texture comparison function. The initial value is <Lequal>. MSVC getter for <compareFunc> property
	@return The texture comparison function value*/
	CompareFunc GetCompareFunc()
	{
		return (CompareFunc)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.0) Gets the texture comparison mode for currently bound depth textures. MSVC getter for <compareMode> property
	@return Returns one of the selected texture compare mode values*/
	CompareMode GetCompareMode()
	{
		return (CompareMode)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.0) (1) Return a compressed two-dimensional multi-layered texture image into client's memory of the size returned by <GetCompressedImageSize>. Pixel pack buffer must be unbound from its target
	@param Specifies the level-of-detail number of the desired image
	@param [out] Specifies a pointer to store the compressed texture image*/
	void GetCompressedImage(GLint level, _Out_ void* pixels)
	{
		get_compressed_tex_image(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, pixels);
	}

	/*(3.0) (2) Return a compressed two-dimensional multi-layered texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies the byte offset into PBO data store*/
	void GetCompressedImage(PixelPackBuffer& buffer, GLint level, GLintptr offset)
	{
		get_compressed_tex_image(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, buffer.Get(), offset);
	}

	/*(3.0) Returns the number of unsigned bytes of the compressed texture image that would be returned from <GetCompressedImage>
	@param Specifies the level-of-detail number of the desired image
	@return The number of unsigned bytes of the compressed texture image*/
	GLsizei GetCompressedImageSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*(3.0) Returns internal storage resolution of DEPTH component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of DEPTH component*/
	GLuint GetDepthSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.0) Returns the type of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of DEPTH component of the texture image*/
	ComponentType GetDepthType(GLint level)
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns internal storage resolution of GREEN component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of GREEN component*/
	GLuint GetGreenSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.0) Returns the type of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of GREEN component of the texture image*/
	ComponentType GetGreenType(GLint level)
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the height of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The height of the texture image*/
	GLsizei GetHeight(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) (1) Returns a two-dimensional multi-layered texture image into client's memory. Pixel pack buffer must be unbound from its target
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void GetImage(GLint level, GetFormat format, GetType type, _Out_ void* pixels)
	{
		get_tex_image(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (2) Returns a two-dimensional multi-layered texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer used for storing the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void GetImage(PixelPackBuffer& buffer, GLint level, GetFormat format, GetType type, GLintptr offset)
	{
		get_tex_image(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.0) Returns the internal format of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal format of the texture image*/
	Internalformat GetInternalFormat(GLint level)
	{
		return (Internalformat)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.0) Returns the number of layers in the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The layers of the texture image*/
	GLsizei GetLayers(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns the current fixed level-of-detail bias value. MSVC getter for <lodBias> property
	@return The texture level-of-detail bias value*/
	GLfloat GetLodBias()
	{
		return get_tex_parameter_float(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_LOD_BIAS);
	}

	/*(3.0) Gets the current texture magnification function. The initial value is <Linear>. MSVC getter for <magFilter> property
	@return The texture magnification function value*/
	MagFilter GetMagFilter()
	{
		return (MagFilter)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.0) Returns the current maximum texture mipmap array level. The initial value is 1000. MSVC getter for <maxLevel> property
	@return The texture maximum mipmap level*/
	GLint GetMaxLevel()
	{
		return get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAX_LEVEL);
	}

	/*(3.0) Returns the current texture maximum level-of-detail value. The initial value is 1000. MSVC getter for <maxLod> property
	@return The maximum level-of-detail value*/
	GLfloat GetMaxLod()
	{
		return get_tex_parameter_float(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAX_LOD);
	}

	/*(3.0) Gets the current texture minifying function. The initial value is <NearestMipmapLinear>. MSVC getter for <minFilter> property
	@return The texture minifying function value*/
	MinFilter GetMinFilter()
	{
		return (MinFilter)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.0) Returns the current texture minimum level-of-detail value. The initial value is -1000. MSVC getter for <minLod> property
	@return The minimum level-of-detail value*/
	GLfloat GetMinLod()
	{
		return get_tex_parameter_float(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MIN_LOD);
	}

	/*(3.0) Returns internal storage resolution of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of ALPHA component*/
	static GLuint GetProxyAlphaSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.0) Returns the type of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static ComponentType GetProxyAlphaType(GLint level)
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns internal storage resolution of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	static GLuint getProxyTextureBlueSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.0) Returns the type of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static ComponentType GetProxyBlueType(GLint level)
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the number of unsigned bytes of the compressed proxy texture that would be returned from <GetCompressedImage>
	@param Specifies the level-of-detail number of the proxy texture
	@return The number of unsigned bytes of the compressed proxy texture*/
	static GLsizei GetProxyCompressedImageSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*(3.0) Returns internal storage resolution of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLuint GetProxyDepthSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.0) Returns the type of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static ComponentType GetProxyDepthType(GLint level)
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns internal storage resolution of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLuint GetProxyGreenSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.0) Returns the type of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static ComponentType GetProxyGreenType(GLint level)
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) Returns the internal format capacity of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal format capacity of the texture*/
	static Internalformat GetProxyInternalFormat(GLint level)
	{
		return (Internalformat)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.0) Returns the number of layers in the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The layers in the texture image*/
	static GLsizei GetProxyLayers(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns internal storage resolution of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLuint GetProxyRedSize(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_RED_SIZE);
	}

	/*(3.0) Returns the type of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of RED component of the proxy texture*/
	static ComponentType GetProxyRedType(GLint level)
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Returns the width of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei GetProxyWidth(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_WIDTH);
	}

	/*(3.0) Returns internal storage resolution of RED component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of RED component*/
	GLuint GetRedSize(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_RED_SIZE);
	}

	/*(3.0) Returns the type of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of RED component of the texture image*/
	ComponentType GetRedType(GLint level)
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_RED_TYPE);
	}

	/*(3.0) Returns the width of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The width of the texture image*/
	GLsizei GetWidth(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_WIDTH);
	}

	/*(3.0) Returns the wrapping function for texture coordinate r. The initial value is <Repeat>. MSVC getter for <wrapR> property
	@return The current wrap mode for texture coordinate r*/
	WrapMode GetWrapR()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_R);
	}

	/*(3.0) Returns the wrapping function for texture coordinate s. The initial value is <Repeat>. MSVC getter for <wrapS> property
	@return The current wrap mode for texture coordinate s*/
	WrapMode GetWrapS()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_S);
	}

	/*(3.0) Returns the wrapping function for texture coordinate t. The initial value is <Repeat>. MSVC getter for <wrapT> property
	@return The current wrap mode for texture coordinate t*/
	WrapMode GetWrapT()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_T);
	}

	/*(3.0) (1) Specifies a two-dimensional multi-layered texture image initialized from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded 2D image
	@param Specifies the number of interleaved layers in loaded 2D image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLsizei layers, GLint level)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, stb_get_format(image), layers, image);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture image initialized from the StbImage object with specified texture internal format. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded 2D image
	@param Specifies the number of interleaved layers in loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLsizei layers, GLint level, Internalformat internalformat)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, layers, image);
	}

	/*(3.0) (3) Specifies a two-dimensional multi-layered texture image initialized from client's memory. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type, _In_ const void* data)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type, data);
	}

	/*(3.0) (4) Specifies a two-dimensional multi-layered texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type, GLintptr offset)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.0) Determines if the texture object is currently bound to its target. MSVC getter for <binding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_TEXTURE_BINDING_2D_ARRAY, Get());
	}

	/*(3.0) Returns boolean value indicating if the texture image is stored in a compressed internal format
	@param Specifies the level-of-detail number of the desired image
	@return True if the texture image is stored in a compressed internal format, false otherwise*/
	GLboolean IsCompressed(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_COMPRESSED);
	}

	/*(3.0) Returns boolean value indicating if the proxy texture was queried in a compressed internal format
	@param Specifies the level-of-detail number of the proxy texture
	@return True if the proxy texture was queried as compressed, false otherwise*/
	static GLboolean IsProxyCompressed(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_COMPRESSED);
	}

	/*(3.0) Recalculates the capacity for a two-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type)
	{
		proxy_image_3d(GL_PROXY_TEXTURE_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type);
	}

	/*(3.0) Specifies the index of the lowest defined mipmap level. The initial value is 0. MSVC setter for <baseLevel> property
	@param The lowest defined mipmap level*/
	void SetBaseLevel(GLint level)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, level);
	}

	/*(3.0) (1) Specifies four integer values that should be used for border texels. The initial value is (0, 0, 0, 0)
	@param [in] Loads four integer texture color values*/
	void SetBorderColor(_In_reads_(4) const GLint* color)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) (2) Specifies four float values that should be used for border texels. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [in] Loads four float texture color values*/
	void SetBorderColor(_In_reads_(4) const GLfloat* color)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.0) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}. The initial value is <Lequal>. MSVC setter for <compareFunc> property
	@param The texture comparison function value*/
	void SetCompareFunc(CompareFunc func)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.0) Sets the texture comparison mode for currently bound depth textures. MSVC setter for <compareMode> property
	@param Specifies the texture compare mode value*/
	void SetCompareMode(CompareMode mode)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.0) Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling. MSVC setter for <lodBias> property
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void SetLodBias(GLfloat bias)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_LOD_BIAS, bias);
	}

	/*(3.0) Sets the texture magnification function value. The initial value is <Linear>. MSVC setter for <magFilter> property
	@param Specifies the texture magnification function's value*/
	void SetMagFilter(MagFilter filter)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*(3.0) Sets the index of the highest defined mipmap level. The initial value is 1000. MSVC setter for <maxLevel> property
	@param The texture maximum mipmap level*/
	void SetMaxLevel(GLint maxlevel)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, maxlevel);
	}

	/*(3.0) Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap. The initial value is 1000. MSVC setter for <maxLod> property
	@param The maximum level-of-detail value*/
	void SetMaxLod(GLfloat maxlod)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*(3.0) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. The initial value is <NearestMipmapLinear>. MSVC setter for <minFilter> property
	@param The texture minifying function value*/
	void SetMinFilter(MinFilter filter)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.0) Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap. The initial value is -1000. MSVC setter for <minLod> property
	@param The minimum level-of-detail value*/
	void SetMinLod(GLfloat minlod)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_MIN_LOD, minlod);
	}

	/*(3.0) Sets the wrapping function for texture coordinate r. MSVC setter for <wrapR> property
	@param The texture wrap mode for coordinate r*/
	void SetWrapR(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.0) Sets the wrapping function for texture coordinate s. MSVC setter for <wrapS> property
	@param The texture wrap mode for coordinate s*/
	void SetWrapS(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.0) Sets the wrapping function for texture coordinate t. MSVC setter for <wrapT> property
	@param The texture wrap mode for coordinate t*/
	void SetWrapT(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.0) (1) Specifies a two-dimensional multi-layered texture subimage copied from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the number of interleaved layers within loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array*/
	void SubImage(StbImage& image, GLsizei layers, GLint level, GLint xoffset, GLint yoffset, GLint zoffset)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, layers, image);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture subimage copied from client's memory data store. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (3) Specifies a two-dimensional multi-layered texture subimage copied from from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.0) Unbinds any texture object bound to particular target, and restores its default texture. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for index of the lowest defined mipmap level*/
	__declspec(property(get = GetBaseLevel, put = SetBaseLevel)) GLint baseLevel;

	/*(3.0) Read-only property for state of the texture binding*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.0) Read-write property for current texture comparison function*/
	__declspec(property(get = GetCompareFunc, put = SetCompareFunc)) CompareFunc compareFunc;

	/*(3.0) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = GetCompareMode, put = SetCompareMode)) CompareMode compareMode;

	/*(3.0) Read-write property for current fixed level-of-detail bias value*/
	__declspec(property(get = GetLodBias, put = SetLodBias)) GLfloat lodBias;

	/*(3.0) Read-write property for current texture magnification function*/
	__declspec(property(get = GetMagFilter, put = SetMagFilter)) MagFilter magFilter;

	/*(3.0) Read-write property for current maximum texture mipmap array level*/
	__declspec(property(get = GetMaxLevel, put = SetMaxLevel)) GLint maxLevel;

	/*(3.0) Read-write property for current texture maximum level-of-detail value*/
	__declspec(property(get = GetMaxLod, put = SetMaxLod)) GLfloat maxLod;

	/*(3.0) Read-write property for current texture minifying function*/
	__declspec(property(get = GetMinFilter, put = SetMinFilter)) MinFilter minFilter;

	/*(3.0) Read-write property for current texture minimum level-of-detail value*/
	__declspec(property(get = GetMinLod, put = SetMinLod)) GLfloat minLod;

	/*(3.0) Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = GetWrapR, put = SetWrapR)) WrapMode wrapR;

	/*(3.0) Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = GetWrapS, put = SetWrapS)) WrapMode wrapS;

	/*(3.0) Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = GetWrapT, put = SetWrapT)) WrapMode wrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value. The initial value is <Alpha>. MSVC getter for <swizzleA> property
	@return The alpha component swizzle value*/
	SwizzleMask GetSwizzleA()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value. The initial value is <Blue>. MSVC getter for <swizzleB> property
	@return The blue component swizzle value*/
	SwizzleMask GetSwizzleB()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value. The initial value is <Green>. MSVC getter for <swizzleG> property
	@return The green component swizzle value*/
	SwizzleMask GetSwizzleG()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value. The initial value is <Red>. MSVC getter for <swizzleR> property
	@return The red component swizzle value*/
	SwizzleMask GetSwizzleR()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)
	@param [out] Stores four swizzle mask values*/
	void GetSwizzleRGBA(_Out_writes_(4) SwizzleMask* swizzle)
	{
		get_tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader. The initial value is <Alpha>. MSVC setter for <swizzleA> property
	@param The alpha component swizzle value*/
	void SetSwizzleA(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader. The initial value is <Blue>. MSVC setter for <swizzleB> property
	@param The blue component swizzle value*/
	void SetSwizzleB(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader. The initial value is <Green>. MSVC setter for <swizzleG> property
	@param The green component swizzle value*/
	void SetSwizzleG(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader. The initial value is <Red>. MSVC setter for <swizzleR> property
	@param The red component swizzle value*/
	void SetSwizzleR(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)
	@param [in] Loads four swizzle mask values*/
	void SetSwizzleRGBA(_In_reads_(4) const SwizzleMask* swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.3) Read-write property for current alpha component swizzle value*/
	__declspec(property(get = GetSwizzleA, put = SetSwizzleA)) SwizzleMask swizzleA;

	/*(3.3) Read-write property for current blue component swizzle value*/
	__declspec(property(get = GetSwizzleB, put = SetSwizzleB)) SwizzleMask swizzleB;

	/*(3.3) Read-write property for current green component swizzle value*/
	__declspec(property(get = GetSwizzleG, put = SetSwizzleG)) SwizzleMask swizzleG;

	/*(3.3) Read-write property for current red component swizzle value*/
	__declspec(property(get = GetSwizzleR, put = SetSwizzleR)) SwizzleMask swizzleR;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
}; // class Texture2DArray : public Textures
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_TEXTURE_2D_ARRAY_H
