#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_TEXTURES_H
#define YAGLPP_TEXTURES_H

namespace gl {
/*OpenGL untyped texture object class derived from <Objects>. Can be used as a temporary asset before its reference is casted to any valid texture type*/
class Textures : public Objects
{
public:
	using Objects::Objects;
	enum class CopyFormat : GLenum;
	enum class GetFormat : GLenum;
	enum class GetType : GLenum;
	enum class Format : GLenum;
	enum class Internalformat : GLenum;
	enum class MagFilter : GLenum;
	enum class MinFilter : GLenum;
	enum class SubFormat : GLenum;
	enum class SubType : GLenum;
	enum class Type : GLenum;
	enum class WrapMode : GLenum;
	/*Allocates an array of texture objects of a given size, and generates their object names. Must be deallocated with <Textures::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Textures* Alloc(GLsizei n)
	{
		return (Textures*)object_alloc(glGenTextures, n);
	}

	/*Deletes previously allocated array of texture object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Textures* textures)
	{
		object_dealloc(glDeleteTextures, (GLuint*)textures);
	}

	/*Deletes valid OpenGL texture object name and sets the texture class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteTextures);
	}

	/*Deletes previously generated OpenGL texture object names in a static array or a user-defined structure of textures, namely texture map, and sets its class objects in empty state. Allows to unset multiple textures of various types in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of texture map returned by sizeof operator
	@param [in-out] Pointer to texture map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* textureMap)
	{
		object_delete_map(glDeleteTextures, n, textureMap);
	}

	/*Generates OpenGL texture object name in an empty texture class object*/
	void Gen()
	{
		object_gen(glGenTextures);
	}

	/*Generates OpenGL texture object names in a static array or a user-defined structure of textures, namely texture map. Allows to set multiple textures of various types in one function call. All class objects are silently overwritten
	@param The size in bytes of texture map returned by sizeof operator
	@param [out] Pointer to texture map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* textureMap)
	{
		object_gen_map(glGenTextures, n, textureMap);
	}

	/*Determines if a valid OpenGL texture object name corresponds to a texture object. MSVC getter for <texture> property
	@return True if active texture object, false otherwise*/
	GLboolean IsTexture() const
	{
		return object_is(glIsTexture);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if active texture object*/
	__declspec(property(get = IsTexture)) GLboolean texture;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	enum class ComponentType : GLenum;
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
	enum class SwizzleMask : GLenum;
#endif // #ifdef YAGLPP_VERSION_3_3

protected:
	static void compressed_proxy_image_1d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize);
	static void compressed_proxy_image_2d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize);
	static void compressed_proxy_image_3d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize);
	void compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data);
	void compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data);
	void compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data);
	void compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data);
	void compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data);
	void compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data);
	void copy_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width);
	void copy_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
	void copy_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	void copy_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void copy_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void get_compressed_tex_image(GLenum target, GLenum binding, GLint level, void* pixels);
	static GLint get_proxy_level_parameter(GLenum target, GLint level, GLenum pname);
	GLint get_tex_level_parameter(GLenum target, GLenum binding, GLint level, GLenum pname);
	void get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, void* pixels);
	GLint get_tex_parameter(GLenum target, GLenum binding, GLenum pname);
	GLfloat get_tex_parameter_float(GLenum target, GLenum binding, GLenum pname);
	void get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint* param);
	void get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat* param);
	static void proxy_image_1d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type);
	static void proxy_image_2d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type);
	static void proxy_image_3d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type);
	static GLenum stb_get_channels(StbImage& image);
	static GLenum stb_get_depth(StbImage& image);
	static GLint stb_get_format(StbImage& image);
	void tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image);
	void tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data);
	void tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image);
	void tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);
	void tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei layers, StbImage& image);
	void tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data);
	void tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint param);
	void tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat param);
	void tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLint* param);
	void tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLfloat* param);
	void tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, StbImage& image);
	void tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
	void tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, StbImage& image);
	void tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei layers, StbImage& image);
	void tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);

#ifdef YAGLPP_VERSION_2_1
	void compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset);
	void get_compressed_tex_image(GLenum target, GLenum binding, GLint level, GLuint buffer, GLintptr offset);
	void get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
	void tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset);
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	void generate_mipmap(GLenum target, GLenum binding);
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	void tex_buffer(GLenum internalformat, GLuint buffer);
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	static void proxy_image_2d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	static void proxy_image_3d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
	void tex_image_2d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	void tex_image_3d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class Textures : public Object

/*GLAD texture internal pixel format enumerator used in <CopyImage>*/
enum class Textures::CopyFormat : GLenum
{
	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

	/*Normalized 8-bit integer used for three (3:3:2)-bit color components*/
	R3G3B2 = GL_R3_G3_B2,

	/*Single 12-bit value used for three (4:4:4)-bit color components*/
	Rgb4 = GL_RGB4,

	/*Single 15-bit value used for three (5:5:5)-bit color components*/
	Rgb5 = GL_RGB5,

	/*Single 24-bit value used for three (8:8:8)-bit color components*/
	Rgb8 = GL_RGB8,

	/*Single 30-bit value used for three (10:10:10)-bit color components*/
	Rgb10 = GL_RGB10,

	/*Single 36-bit value used for three (12:12:12)-bit color components*/
	Rgb12 = GL_RGB12,

	/*Single 48-bit value used for three (16:16:16)-bit color components*/
	Rgb16 = GL_RGB16,

	/*Single 8-bit value used for four (2:2:2:2)-bit color components*/
	Rgba2 = GL_RGBA2,

	/*Single 16-bit value used for four (4:4:4:4)-bit color components*/
	Rgba4 = GL_RGBA4,

	/*Single 16-bit value used for four (5:5:5:1)-bit color components*/
	Rgb5A1 = GL_RGB5_A1,

	/*Single 32-bit value used for four (8:8:8:8)-bit color components*/
	Rgba8 = GL_RGBA8,

	/*Single 32-bit value used for four (10:10:10:2)-bit color components*/
	Rgb10A2 = GL_RGB10_A2,

	/*Single 48-bit value used for four (12:12:12:12)-bit color components*/
	Rgba12 = GL_RGBA12,

	/*Single 64-bit value used for four (16:16:16:16)-bit color components*/
	Rgba16 = GL_RGBA16,

	/*Each pixel is a 16-bit single-depth component*/
	DepthComponent16 = GL_DEPTH_COMPONENT16,

	/*Each pixel is a 24-bit single-depth component*/
	DepthComponent24 = GL_DEPTH_COMPONENT24,

	/*Each pixel is a 32-bit single-depth component*/
	DepthComponent32 = GL_DEPTH_COMPONENT32,

	/*Generic compressed three-component format*/
	CompressedRgb = GL_COMPRESSED_RGB,

	/*Generic compressed four-component format*/
	CompressedRgba = GL_COMPRESSED_RGBA,

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) Each pixel is a three-component color space group*/
	Srgb = GL_SRGB,

	/*(2.1) Single 24-bit value used for three (8:8:8)-bit color space components*/
	Srgb8 = GL_SRGB8,

	/*(2.1) Each pixel is a four-component color space group*/
	SrgbAlpha = GL_SRGB_ALPHA,

	/*(2.1) Single 32-bit value used for four (8:8:8:8)-bit color space components*/
	Srgb8Alpha8 = GL_SRGB8_ALPHA8,

	/*(2.1) Generic compressed three-component color space format*/
	CompressedSrgb = GL_COMPRESSED_SRGB,

	/*(2.1) Generic compressed four-component color space format*/
	CompressedSrgbAlpha = GL_COMPRESSED_SRGB_ALPHA,
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Generic compressed one-component format*/
	CompressedRed = GL_COMPRESSED_RED,

	/*(3.0) Generic compressed two-component format*/
	CompressedRg = GL_COMPRESSED_RG,

	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is a single 8-bit stencil index value*/
	StencilIndex8 = GL_STENCIL_INDEX8,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture output pixel format enumerator used in <GetImage>*/
enum class Textures::GetFormat : GLenum
{
	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a single green component*/
	Green = GL_GREEN,

	/*Each pixel is a single blue component*/
	Blue = GL_BLUE,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

	/*Each pixel is a reversed three-component group*/
	Bgr = GL_BGR,

	/*Each pixel is a reversed four-component group*/
	Bgra = GL_BGRA,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is an integer two-component group*/
	RgInteger = GL_RG_INTEGER,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,

	/*(3.0) Each pixel is a single integer red component*/
	RedInteger = GL_RED_INTEGER,

	/*(3.0) Each pixel is a single integer green component*/
	GreenInteger = GL_GREEN_INTEGER,

	/*(3.0) Each pixel is a single integer blue component*/
	BlueInteger = GL_BLUE_INTEGER,

	/*(3.0) Each pixel is an integer three-component group*/
	RgbInteger = GL_RGB_INTEGER,

	/*(3.0) Each pixel is an integer four-component group*/
	RgbaInteger = GL_RGBA_INTEGER,

	/*(3.0) Each pixel is an integer reversed three-component group*/
	BgrInteger = GL_BGR_INTEGER,

	/*(3.0) Each pixel is an integer reversed four-component group*/
	BgraInteger = GL_BGRA_INTEGER,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture output pixel type enumerator used in <GetImage>*/
enum class Textures::GetType : GLenum
{
	/*Signed 8-bit used for each color component*/
	Byte = GL_BYTE,

	/*Unsigned 8-bit value used for each color component*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*Signed 16-bit value used for each color component*/
	Short = GL_SHORT,

	/*Unsigned 16-bit value used for each color component*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*Signed 32-bit value used for each color component*/
	Int = GL_INT,

	/*Unsigned 32-bit value used for each color component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Float 32-bit value used for each color component*/
	Float = GL_FLOAT,

	/*Single 8-bit value used for three unsigned integer (3:3:2)-bit color components, format must be <Rgb>*/
	UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit color components, format must be <Rgba>*/
	UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,

	/*Single 16-bit value used for four unsigned integer (5:5:5:1)-bit color components, format must be <Rgba>*/
	UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit color components, format must be <Rgba>*/
	UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,

	/*Single 32-bit value used for four unsigned integer (10:10:10:2)-bit color components, format must be <Rgba>*/
	UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,

	/*Single 8-bit value used for three unsigned integer (2:3:3)-bit reversed color components, format must be <Bgr>*/
	UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit color components, format must be <Rgb>*/
	UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit reversed color components, format must be <Bgr>*/
	UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,

	/*Single 16-bit value used for four unsigned integer (1:5:5:5)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,

	/*Single 32-bit value used for four unsigned integer (2:10:10:10)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Float 16-bit value used for each color component*/
	HalfFloat = GL_HALF_FLOAT,

	/*(3.0) Single 32-bit value used for depth and stencil unsigned integer (24:8)-bit components, format must be <DepthStencil>*/
	UnsignedInt248 = GL_UNSIGNED_INT_24_8,

	/*(3.0) Single 32-bit value used for three float (10f:11f:11f)-bit reversed color components, format must be <Bgr>*/
	UnsignedInt10f11f11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,

	/*(3.0) Single 32-bit value used for four unsigned integer (5:9:9:9)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt5999Rev = GL_UNSIGNED_INT_5_9_9_9_REV,

	/*(3.0) Single 40-bit value used for depth and stencil (32f:8)-bit reversed components, format must be <DepthStencil>*/
	Float32UnsignedInt248Rev = GL_FLOAT_32_UNSIGNED_INT_24_8_REV,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture input pixel format enumerator used in <Image>*/
enum class Textures::Format : GLenum
{
	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

	/*Each pixel is a reversed three-component group*/
	Bgr = GL_BGR,

	/*Each pixel is a reversed four-component group*/
	Bgra = GL_BGRA,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is an integer two-component group*/
	RgInteger = GL_RG_INTEGER,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,

	/*(3.0) Each pixel is a single integer red component*/
	RedInteger = GL_RED_INTEGER,

	/*(3.0) Each pixel is an integer three-component group*/
	RgbInteger = GL_RGB_INTEGER,

	/*(3.0) Each pixel is an integer four-component group*/
	RgbaInteger = GL_RGBA_INTEGER,

	/*(3.0) Each pixel is an integer reversed three-component group*/
	BgrInteger = GL_BGR_INTEGER,

	/*(3.0) Each pixel is an integer reversed four-component group*/
	BgraInteger = GL_BGRA_INTEGER,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture internal pixel format enumerator used in <Image>*/
enum class Textures::Internalformat : GLenum
{
	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

	/*Single 8-bit value used for three normalized integer (3:3:2)-bit color components*/
	R3G3B2 = GL_R3_G3_B2,

	/*Single 12-bit value used for three (4:4:4)-bit color components*/
	Rgb4 = GL_RGB4,

	/*Single 15-bit value used for three (5:5:5)-bit color components*/
	Rgb5 = GL_RGB5,

	/*Single 24-bit value used for three (8:8:8)-bit color components*/
	Rgb8 = GL_RGB8,

	/*Single 30-bit value used for three (10:10:10)-bit color components*/
	Rgb10 = GL_RGB10,

	/*Single 36-bit value used for three (12:12:12)-bit color components*/
	Rgb12 = GL_RGB12,

	/*Single 48-bit value used for three (16:16:16)-bit color components*/
	Rgb16 = GL_RGB16,

	/*Single 8-bit value used for four (2:2:2:2)-bit color components*/
	Rgba2 = GL_RGBA2,

	/*Single 16-bit value used for four (4:4:4:4)-bit color components*/
	Rgba4 = GL_RGBA4,

	/*Single 16-bit value used for four (5:5:5:1)-bit color components*/
	Rgb5A1 = GL_RGB5_A1,

	/*Single 32-bit value used for four (8:8:8:8)-bit color components*/
	Rgba8 = GL_RGBA8,

	/*Single 32-bit value used for four (10:10:10:2)-bit color components*/
	Rgb10A2 = GL_RGB10_A2,

	/*Single 48-bit value used for four (12:12:12:12)-bit color components*/
	Rgba12 = GL_RGBA12,

	/*Single 64-bit value used for four (16:16:16:16)-bit color components*/
	Rgba16 = GL_RGBA16,

	/*Generic compressed three-component format*/
	CompressedRgb = GL_COMPRESSED_RGB,

	/*Generic compressed four-component format*/
	CompressedRgba = GL_COMPRESSED_RGBA,

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) Single 24-bit value used for three (8:8:8)-bit color space components*/
	Srgb8 = GL_SRGB8,

	/*(2.1) Each pixel is a four-component color space group*/
	SrgbAlpha = GL_SRGB_ALPHA,

	/*(2.1) Generic compressed three-component color space format*/
	CompressedSrgb = GL_COMPRESSED_SRGB,

	/*(2.1) Generic compressed four-component color space format*/
	CompressedSrgbAlpha = GL_COMPRESSED_SRGB_ALPHA,
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Generic compressed one-component format*/
	CompressedRed = GL_COMPRESSED_RED,

	/*(3.0) Generic compressed two-component format*/
	CompressedRg = GL_COMPRESSED_RG,

	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is a single 8-bit red component*/
	R8 = GL_R8,

	/*(3.0) Each pixel is a single 16-bit red component*/
	R16 = GL_R16,

	/*(3.0) Single 16-bit value used for two (8:8)-bit color components*/
	Rg8 = GL_RG8,

	/*(3.0) Single 32-bit value used for two (16:16)-bit color components*/
	Rg16 = GL_RG16,

	/*(3.0) Each pixel is a single 16-bit float red component*/
	R16f = GL_R16F,

	/*(3.0) Single 32-bit float red component*/
	R32f = GL_R32F,

	/*(3.0) Single 32-bit value used for two float (16f:16f)-bit color components*/
	RG16f = GL_RG16F,

	/*(3.0) Single 64-bit value used for two float (32f:32f)-bit color components*/
	Rg32f = GL_RG32F,

	/*(3.0) Signed 8-bit integer value used for single red color component*/
	R8i = GL_R8I,

	/*(3.0) Unsigned 8-bit integer value used for single red color component*/
	R8ui = GL_R8UI,

	/*(3.0) Signed 16-bit integer value used for single red color component*/
	R16i = GL_R16I,

	/*(3.0) Unsigned 16-bit integer value used for single red color component*/
	R16ui = GL_R16UI,

	/*(3.0) Signed 32-bit integer value used for single red color component*/
	R32i = GL_R32I,

	/*(3.0) Unsigned 32-bit integer value used for single red color component*/
	R32ui = GL_R32UI,

	/*(3.0) Single 16-bit value used for two signed integer (8:8)-bit color components*/
	Rg8i = GL_RG8I,

	/*(3.0) Single 16-bit value used for two unsigned integer (8:8)-bit color components*/
	Rg8ui = GL_RG8UI,

	/*(3.0) Single 32-bit value used for two signed integer (16:16)-bit color components*/
	Rg16i = GL_RG16I,

	/*(3.0) Single 32-bit value used for two unsigned integer (16:16)-bit color components*/
	Rg16ui = GL_RG16UI,

	/*(3.0) Single 64-bit value used for two signed integer (32:32)-bit color components*/
	Rg32i = GL_RG32I,

	/*(3.0) Single 64-bit value used for two unsigned integer (32:32)-bit color components*/
	Rg32ui = GL_RG32UI,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,

	/*(3.0) Single 128-bit value used for four float (32f:32f:32f:32f)-bit color components*/
	Rgba32f = GL_RGBA32F,

	/*(3.0) Single 96-bit value used for three float (32f:32f:32f)-bit color components*/
	Rgb32f = GL_RGB32F,

	/*(3.0) Single 64-bit value used for four float (16f:16f:16f:16f)-bit color components*/
	Rgba16f = GL_RGBA16F,

	/*(3.0) Single 48-bit value used for three float (16f:16f:16f)-bit color components*/
	Rgb16f = GL_RGB16F,

	/*(3.0) Special 32-bit value used for three no-sign float (11f:11f:10f)-bit color components*/
	R11fG11fB10f = GL_R11F_G11F_B10F,

	/*(3.0) Special 32-bit value used for three float (9f:9f:9f:5e)-bit color components with shared 5-bit exponent*/
	Rgb9E5 = GL_RGB9_E5,

	/*(3.0) Single 128-bit value used for four unsigned integer (32:32:32:32)-bit color components*/
	Rgba32ui = GL_RGBA32UI,

	/*(3.0) Single 96-bit value used for three unsigned integer (32:32:32)-bit color components*/
	Rgb32ui = GL_RGB32UI,

	/*(3.0) Single 64-bit value used for four unsigned integer (16:16:16:16)-bit color components*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.0) Single 48-bit value used for three unsigned integer (16:16:16)-bit color components*/
	Rgb16ui = GL_RGB16UI,

	/*(3.0) Single 32-bit value used for four unsigned integer (8:8:8:8)-bit color components*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.0) Single 24-bit value used for three unsigned integer (8:8:8)-bit color components*/
	Rgb8ui = GL_RGB8UI,

	/*(3.0) Single 128-bit value used for four signed integer (32:32:32:32)-bit color components*/
	Rgba32i = GL_RGBA32I,

	/*(3.0) Single 96-bit value used for three signed integer (32:32:32)-bit color components*/
	Rgb32i = GL_RGB32I,

	/*(3.0) Single 64-bit value used for four signed integer (16:16:16:16)-bit color components*/
	Rgba16i = GL_RGBA16I,

	/*(3.0) Single 48-bit value used for three signed integer (16:16:16)-bit color components*/
	Rgb16i = GL_RGB16I,

	/*(3.0) Single 32-bit value used for four signed integer (8:8:8:8)-bit color components*/
	Rgba8i = GL_RGBA8I,

	/*(3.0) Single 24-bit value used for three signed integer (8:8:8)-bit color components*/
	Rgb8i = GL_RGB8I,
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) Normalized 8-bit signed integer used for single color components*/
	R8Snorm = GL_R8_SNORM,

	/*(3.1) Single 16-bit value used for two normalized signed integer (8:8)-bit color components*/
	Rg8Snorm = GL_RG8_SNORM,

	/*(3.1) Single 24-bit value used for three normalized signed integer (8:8:8)-bit color components*/
	Rgb8Snorm = GL_RGB8_SNORM,

	/*(3.1) Single 64-bit value used for four normalized signed integer (8:8:8:8)-bit color components*/
	Rgba8Snorm = GL_RGBA8_SNORM,

	/*(3.1) Normalized 16-bit signed integer used for single color components*/
	R16Snorm = GL_R16_SNORM,

	/*(3.1) Single 32-bit value used for two normalized signed integer (16:16)-bit color components*/
	Rg16Snorm = GL_RG16_SNORM,

	/*(3.1) Single 48-bit value used for three normalized signed integer (16:16:16)-bit color components*/
	Rgb16Snorm = GL_RGB16_SNORM,
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Unsigned 32-bit integer used for four (8:8:8:2)-bit color components*/
	Rgb10A2ui = GL_RGB10_A2UI,
#endif // #ifdef YAGLPP_VERSION_3_3
};

/*GLAD texture input pixel format enumerator used in <SubImage>*/
enum class Textures::SubFormat : GLenum
{
	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

	/*Each pixel is a reversed three-component group*/
	Bgr = GL_BGR,

	/*Each pixel is a reversed four-component group*/
	Bgra = GL_BGRA,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture magnifying function enumerator*/
enum class Textures::MagFilter : GLenum
{
	/*Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates*/
	Nearest = GL_NEAREST,

	/*Returns the weighted average of the four texture elements that are closest to the specified texture coordinates*/
	Linear = GL_LINEAR,
};

/*GLAD texture minifying function enumerator*/
enum class Textures::MinFilter : GLenum
{
	/*Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates*/
	Nearest = GL_NEAREST,

	/*Returns the weighted average of the four texture elements that are closest to the specified texture coordinates*/
	Linear = GL_LINEAR,

	/*Chooses the mipmap that most closely matches the size of the pixel being textured and uses the nearest criterion*/
	NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,

	/*Chooses the mipmap that most closely matches the size of the pixel being textured and uses the linear criterion*/
	LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,

	/*Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the nearest criterion*/
	NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,

	/*Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the linear criterion*/
	LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
};

/*GLAD texture input pixel type enumerator used in <SubImage>*/
enum class Textures::SubType : GLenum
{
	/*Signed 8-bit used for each color component*/
	Byte = GL_BYTE,

	/*Unsigned 8-bit value used for each color component*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*Signed 16-bit value used for each color component*/
	Short = GL_SHORT,

	/*Unsigned 16-bit value used for each color component*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*Signed 32-bit value used for each color component*/
	Int = GL_INT,

	/*Unsigned 32-bit value used for each color component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Float 32-bit value used for each color component*/
	Float = GL_FLOAT,

	/*Single 8-bit value used for three unsigned integer (3:3:2)-bit color components, format must be <Rgb>*/
	UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit color components, format must be <Rgba>*/
	UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,

	/*Single 16-bit value used for four unsigned integer (5:5:5:1)-bit color components, format must be <Rgba>*/
	UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit color components, format must be <Rgba>*/
	UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,

	/*Single 32-bit value used for four unsigned integer (10:10:10:2)-bit color components, format must be <Rgba>*/
	UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,

	/*Single 8-bit value used for three unsigned integer (2:3:3)-bit reversed color components, format must be <Bgr>*/
	UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit color components, format must be <Rgb>*/
	UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit reversed color components, format must be <Bgr>*/
	UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,

	/*Single 16-bit value used for four unsigned integer (1:5:5:5)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,

	/*Single 32-bit value used for four unsigned integer (2:10:10:10)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
};

/*GLAD texture input pixel type enumerator used by <Image>*/
enum class Textures::Type : GLenum
{
	/*Signed 8-bit used for each color component*/
	Byte = GL_BYTE,

	/*Unsigned 8-bit value used for each color component*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*Signed 16-bit value used for each color component*/
	Short = GL_SHORT,

	/*Unsigned 16-bit value used for each color component*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*Signed 32-bit value used for each color component*/
	Int = GL_INT,

	/*Unsigned 32-bit value used for each color component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Float 32-bit value used for each color component*/
	Float = GL_FLOAT,

	/*Unsigned 8-bit value used for three (3:3:2)-bit color components, format must be <Rgb>*/
	UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,

	/*Unsigned 16-bit value used for four (4:4:4:4)-bit color components, format must be <Rgba>*/
	UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,

	/*Unsigned 16-bit value used for four (5:5:5:1)-bit color components, format must be <Rgba>*/
	UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,

	/*Unsigned 32-bit value used for four (8:8:8:8)-bit color components, format must be <Rgba>*/
	UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,

	/*Unsigned 32-bit value used for four (10:10:10:2)-bit color components, format must be <Rgba>*/
	UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,

	/*Unsigned 8-bit value used for three (2:3:3)-bit reversed color components, format must be <Bgr>*/
	UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,

	/*Unsigned 16-bit value used for three (5:6:5)-bit color components, format must be <Rgb>*/
	UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,

	/*Unsigned 16-bit value used for three (5:6:5)-bit reversed color components, format must be <Bgr>*/
	UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,

	/*Unsigned 16-bit value used for four (4:4:4:4)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,

	/*Unsigned 16-bit value used for four (1:5:5:5)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	/*Unsigned 32-bit value used for four (8:8:8:8)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,

	/*Unsigned 32-bit value used for four (2:10:10:10)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

#ifdef YAGLPP_VERSION_3_0
	HalfFloat = GL_HALF_FLOAT,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD texture wrap mode enumerator*/
enum class Textures::WrapMode : GLenum
{
	/*Default value. Causes the integer part of the s coordinate to be ignored, the GL uses only the fractional part, thereby creating a repeating pattern*/
	Repeat = GL_REPEAT,

	/*Evaluates s coordinates in a similar manner to <ClampToEdge>. However, in cases where clamping would have occurred in <ClampToEdge> mode, the fetched texel data is substituted with the values specified by texture border color*/
	ClampToBorder = GL_CLAMP_TO_BORDER,

	/*Causes s coordinates to be clamped to the range [1/2N, 1 - 1/2N], where N is the size of the texture in the direction of clamping*/
	ClampToEdge = GL_CLAMP_TO_EDGE,

	/*Causes the s coordinate to be set to the fractional part of the texture coordinate if the integer part of s is even; if the integer part of s is odd, then the s texture coordinate is set to [1 - frac(s)], where frac(s) represents the fractional part of s*/
	MirroredRepeat = GL_MIRRORED_REPEAT,
};

#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD texture component type enumerator*/
enum class Textures::ComponentType : GLenum
{
	/*(3.0) The component type is unset*/
	None = GL_NONE,

	/*(3.0) Integer unnormalized component*/
	Int = GL_INT,

	/*(3.0) Unsigned integer unnormalized component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*(3.0) Unsigned normalized fixed-point component*/
	UnsignedNormalized = GL_UNSIGNED_NORMALIZED,

	/*(3.0) Floating-point component*/
	Float = GL_FLOAT,

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) Signed normalized fixed-point component*/
	SignedNormalized = GL_SIGNED_NORMALIZED,
#endif // #ifdef YAGLPP_VERSION_3_1
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
/*(3.3) GLAD texture swizzle mask enumerator*/
enum class Textures::SwizzleMask : GLenum
{
	/*(3.3) The value for this component is always 0*/
	Zero = GL_ZERO,

	/*(3.3) The value for this component is always 1*/
	One = GL_ONE,

	/*(3.3) The value for this component always comes from the red channel of the image*/
	Red = GL_RED,

	/*(3.3) The value for this component comes from the green channel of the image, or 0 if no green channel*/
	Green = GL_GREEN,

	/*(3.3) The value for this component comes from the blue channel of the image, or 0 if no blue channel*/
	Blue = GL_BLUE,

	/*(3.3) The value for this component comes from the alpha channel of the image, or 1 if no alpha channel*/
	Alpha = GL_ALPHA,
};
#endif // #ifdef YAGLPP_VERSION_3_3

inline void Textures::tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image)
{
	tex_image_1d(target, binding, level, internalformat, image.GetWidth(), stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

inline void Textures::tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image)
{
	tex_image_2d(target, binding, level, internalformat, image.GetWidth(), image.GetHeight(), stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

inline void Textures::tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei layers, StbImage& image)
{
	tex_image_3d(target, binding, level, internalformat, image.GetWidth(), image.GetHeight() / layers, layers, stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

inline void Textures::tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, StbImage& image)
{
	tex_sub_image_1d(target, binding, level, xoffset, image.GetWidth(), stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

inline void Textures::tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, StbImage& image)
{
	tex_sub_image_2d(target, binding, level, xoffset, yoffset, image.GetWidth(), image.GetHeight(), stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

inline void Textures::tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei layers, StbImage& image)
{
	tex_sub_image_3d(target, binding, level, xoffset, yoffset, zoffset, image.GetWidth(), image.GetHeight() / layers, layers, stb_get_channels(image), stb_get_depth(image), image.GetPixels());
}

#ifdef YAGLPP_IMPLEMENTATION
GLenum Textures::stb_get_channels(StbImage& image)
{
	switch (image.GetChannels())
	{
	case StbImage::Format::RgbAlpha:
		return GL_RGBA;

	case StbImage::Format::Rgb:
		return GL_RGB;

	case StbImage::Format::Grey:
		return GL_RED;

#ifdef YAGLPP_VERSION_3_0
	case StbImage::Format::GreyAlpha:
		return GL_RG;
#endif // #ifdef YAGLPP_VERSION_3_0
	}

	// STB IMAGE NUMBER OF COMPONENTS IS UNSUPPORTED
	YAGLPP_ASSERT(0);

	return 0;
}

GLenum Textures::stb_get_depth(StbImage& image)
{
	switch (image.GetDepth())
	{
	case StbImage::Format::Unsigned8:
		return GL_UNSIGNED_BYTE;

	case StbImage::Format::Unsigned16:
		return GL_UNSIGNED_SHORT;

	case StbImage::Format::Float32:
		return GL_FLOAT;
	}

	// STB IMAGE COMPONENT DEPTH IS UNSUPPORTED
	YAGLPP_ASSERT(0);

	return 0;
}

GLint Textures::stb_get_format(StbImage& image)
{
#ifdef YAGLPP_VERSION_3_0
	switch (image.GetFormat())
	{
	case StbImage::Format::Grey8:
		return GL_R8;

	case StbImage::Format::Grey16:
		return GL_R16;

	case StbImage::Format::GreyF:
		return GL_R32F;

	case StbImage::Format::GreyAlpha8:
		return GL_RG8;

	case StbImage::Format::GreyAlpha16:
		return GL_RG16;

	case StbImage::Format::GreyAlphaF:
		return GL_RG32F;

	case StbImage::Format::Rgb8:
		return GL_RGB8;

	case StbImage::Format::Rgb16:
		return GL_RGB16;

	case StbImage::Format::RgbF:
		return GL_RGB32F;

	case StbImage::Format::RgbAlpha8:
		return GL_RGBA8;

	case StbImage::Format::RgbAlpha16:
		return GL_RGBA16;

	case StbImage::Format::RgbAlphaF:
		return GL_RGBA32F;
	}

	// STB IMAGE FORMAT IS INVALID
	YAGLPP_ASSERT(0);

	return 0;
#else
	return stb_get_channels(image);
#endif
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Textures::compressed_proxy_image_1d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_proxy_image_2d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_proxy_image_3d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::copy_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCopyTexImage1D(target, level, internalformat, x, y, width, 0);
	YAGLPP_GLAD_ERROR;
}

void Textures::copy_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCopyTexImage2D(target, level, internalformat, x, y, width, height, 0);
	YAGLPP_GLAD_ERROR;
}

void Textures::copy_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
	YAGLPP_GLAD_ERROR;
}

void Textures::copy_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	YAGLPP_GLAD_ERROR;
}

void Textures::copy_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	YAGLPP_GLAD_ERROR;
}

void Textures::get_compressed_tex_image(GLenum target, GLenum binding, GLint level, void* pixels)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL PACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_PACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGetCompressedTexImage(target, level, pixels);
	YAGLPP_GLAD_ERROR;
}

GLint Textures::get_proxy_level_parameter(GLenum target, GLint level, GLenum pname)
{
	GLint iResult;
	glGetTexLevelParameteriv(target, level, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void Textures::get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, void* pixels)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL PACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_PACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGetTexImage(target, level, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

GLint Textures::get_tex_level_parameter(GLenum target, GLenum binding, GLint level, GLenum pname)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLint iResult;
	glGetTexLevelParameteriv(target, level, pname, &iResult);
	return iResult;
}

GLint Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLint iResult;
	glGetTexParameteriv(target, pname, &iResult);
	return iResult;
}

GLfloat Textures::get_tex_parameter_float(GLenum target, GLenum binding, GLenum pname)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	GLfloat fResult;
	glGetTexParameterfv(target, pname, &fResult);
	return fResult;
}

void Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint* param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGetTexParameteriv(target, pname, param);
}

void Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat* param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGetTexParameterfv(target, pname, param);
}

void Textures::proxy_image_1d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::proxy_image_2d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::proxy_image_3d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, nullptr);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexParameteri(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexParameterf(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLint* param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));
	
	glTexParameteriv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLfloat* param)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexParameterfv(target, pname, param);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL UNPACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Textures::compressed_proxy_image_1d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, nullptr);
}

inline void Textures::compressed_proxy_image_2d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, nullptr);
}

inline void Textures::compressed_proxy_image_3d(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, nullptr);
}

inline void Textures::compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
}

inline void Textures::compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, data);
}

inline void Textures::compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
}

inline void Textures::compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, data);
}

inline void Textures::compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
}

inline void Textures::compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
}

inline void Textures::copy_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	glCopyTexImage1D(target, level, internalformat, x, y, width, 0);
}

inline void Textures::copy_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	glCopyTexImage2D(target, level, internalformat, x, y, width, height, 0);
}

inline void Textures::copy_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

inline void Textures::copy_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

inline void Textures::copy_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

inline void Textures::get_compressed_tex_image(GLenum target, GLenum binding, GLint level, void* pixels)
{
	glGetCompressedTexImage(target, level, pixels);
}

inline GLint Textures::get_proxy_level_parameter(GLenum target, GLint level, GLenum pname)
{
	GLint i; glGetTexLevelParameteriv(target, level, pname, &i); return i;
}

inline void Textures::get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, void* pixels)
{
	glGetTexImage(target, level, format, type, pixels);
}

inline GLint Textures::get_tex_level_parameter(GLenum target, GLenum binding, GLint level, GLenum pname)
{
	GLint i; glGetTexLevelParameteriv(target, level, pname, &i); return i;
}

inline GLint Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname)
{
	GLint i; glGetTexParameteriv(target, pname, &i); return i;
}

inline GLfloat Textures::get_tex_parameter_float(GLenum target, GLenum binding, GLenum pname)
{
	GLfloat f; glGetTexParameterfv(target, pname, &f); return f;
}

inline void Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint* param)
{
	glGetTexParameteriv(target, pname, param);
}

inline void Textures::get_tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat* param)
{
	glGetTexParameterfv(target, pname, param);
}

inline void Textures::proxy_image_1d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, nullptr);
}

inline void Textures::proxy_image_2d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, nullptr);
}

inline void Textures::proxy_image_3d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, nullptr);
}

inline void Textures::tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
}

inline void Textures::tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
}

inline void Textures::tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
}

inline void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

inline void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, GLfloat param)
{
	glTexParameterf(target, pname, param);
}

inline void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLint* param)
{
	glTexParameteriv(target, pname, param);
}

inline void Textures::tex_parameter(GLenum target, GLenum binding, GLenum pname, const GLfloat* param)
{
	glTexParameterfv(target, pname, param);
}

inline void Textures::tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

inline void Textures::tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void Textures::tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Textures::compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::get_compressed_tex_image(GLenum target, GLenum binding, GLint level, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL PACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_PACK_BUFFER_BINDING, buffer));

	glGetCompressedTexImage(target, level, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL PACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_PACK_BUFFER_BINDING, buffer));

	glGetTexImage(target, level, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexImage1D(target, level, internalformat, width, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexImage2D(target, level, internalformat, width, height, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));
	
	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexSubImage1D(target, level, xoffset, width, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	// PIXEL UNPACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_PIXEL_UNPACK_BUFFER_BINDING, buffer));

	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Textures::compressed_tex_image_1d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, (void*)offset);
}

inline void Textures::compressed_tex_image_2d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, (void*)offset);
}

inline void Textures::compressed_tex_image_3d(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, (void*)offset);
}

inline void Textures::compressed_tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, (void*)offset);
}

inline void Textures::compressed_tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, (void*)offset);
}

inline void Textures::compressed_tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLuint buffer, GLintptr offset)
{
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, (void*)offset);
}

inline void Textures::get_compressed_tex_image(GLenum target, GLenum binding, GLint level, GLuint buffer, GLintptr offset)
{
	glGetCompressedTexImage(target, level, (void*)offset);
}

inline void Textures::get_tex_image(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glGetTexImage(target, level, format, type, (void*)offset);
}

inline void Textures::tex_image_1d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, (void*)offset);
}

inline void Textures::tex_image_2d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, (void*)offset);
}

inline void Textures::tex_image_3d(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, (void*)offset);
}

inline void Textures::tex_sub_image_1d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexSubImage1D(target, level, xoffset, width, format, type, (void*)offset);
}

inline void Textures::tex_sub_image_2d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, (void*)offset);
}

inline void Textures::tex_sub_image_3d(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLuint buffer, GLintptr offset)
{
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, (void*)offset);
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Textures::generate_mipmap(GLenum target, GLenum binding)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glGenerateMipmap(target);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Textures::generate_mipmap(GLenum target, GLenum binding)
{
	glGenerateMipmap(target);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Textures::tex_buffer(GLenum internalformat, GLuint buffer)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(GL_TEXTURE_BINDING_BUFFER, Get()));

	// TEXTURE BUFFER IS UNBOUND
	YAGLPP_ASSERT(object_binding(GL_TEXTURE_BUFFER_BINDING, buffer));

	glTexBuffer(GL_TEXTURE_BUFFER, internalformat, buffer);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Textures::tex_buffer(GLenum internalformat, GLuint buffer)
{
	glTexBuffer(GL_TEXTURE_BUFFER, internalformat, buffer);
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Textures::proxy_image_2d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void Textures::proxy_image_3d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_2d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}

void Textures::tex_image_3d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	// TEXTURE OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(binding, Get()));

	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Textures::proxy_image_2d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

inline void Textures::proxy_image_3d_multisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

inline void Textures::tex_image_2d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

inline void Textures::tex_image_3d_multisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_TEXTURES_H
