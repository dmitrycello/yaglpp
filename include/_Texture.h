#pragma once
#include "_Object.h"
namespace gl {
/*GLAD texture output pixel type enumerator used in <gexTexImage>*/
typedef ReadPixelsType GetTexType;

/*GLAD compressed texture internal pixel format enumerator used in <compressedTexImage> and <compressedTexSubImage>*/
enum class CompressedTexInternalformat : GLenum
{
	/*Generic compressed three-component format*/
	CompressedRgb = GL_COMPRESSED_RGB,

	/*Generic compressed four-component format*/
	CompressedRgba = GL_COMPRESSED_RGBA,

#ifdef GL_VERSION_2_1
	/*(2.1) Generic compressed three-component color space format*/
	CompressedSrgb = GL_COMPRESSED_SRGB,

	/*(2.1) Generic compressed four-component color space format*/
	CompressedSrgbAlpha = GL_COMPRESSED_SRGB_ALPHA,
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) Generic compressed one-component format*/
	CompressedRed = GL_COMPRESSED_RED,

	/*(3.0) Generic compressed two-component format*/
	CompressedRg = GL_COMPRESSED_RG,

	/*(3.0) Specific compressed unsigned normalized one-component format*/
	CompressedRedRgtc1 = GL_COMPRESSED_RED_RGTC1,
	
	/*(3.0) Specific compressed signed normalized one-component format*/
	CompressedSignedRedRgtc1 = GL_COMPRESSED_SIGNED_RED_RGTC1,

	/*(3.0) Specific compressed unsigned normalized two-component format*/
	CompressedRgRgtc2 = GL_COMPRESSED_RG_RGTC2,

	/*(3.0) Specific compressed signed normalized two-component format*/
	CompressedSignedRgRgtc2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD texture internal pixel format enumerator used in <CopyTexImage>*/
enum class CopyTexInternalformat : GLenum
{
	/*Each pixel is a single red component*/
	Red = GL_RED,

	/*Each pixel is a three-component group*/
	Rgb = GL_RGB,

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

	/*Each pixel is a four-component group*/
	Rgba = GL_RGBA,

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

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

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

#ifdef GL_VERSION_2_1
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
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is a single 8-bit stencil index value*/
	StencilIndex8 = GL_STENCIL_INDEX8,

	/*(3.0) Generic compressed one-component format*/
	CompressedRed = GL_COMPRESSED_RED,

	/*(3.0) Generic compressed two-component format*/
	CompressedRg = GL_COMPRESSED_RG,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD texture output pixel format enumerator used in <getTexImage>*/
enum class GetTexFormat : GLenum
{
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

	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

#ifdef GL_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is a single integer red component*/
	RedInteger = GL_RED_INTEGER,

	/*(3.0) Each pixel is a single integer green component*/
	GreenInteger = GL_GREEN_INTEGER,

	/*(3.0) Each pixel is a single integer blue component*/
	BlueInteger = GL_BLUE_INTEGER,

	/*(3.0) Each pixel is an integer two-component group*/
	RgInteger = GL_RG_INTEGER,

	/*(3.0) Each pixel is an integer three-component group*/
	RgbInteger = GL_RGB_INTEGER,

	/*(3.0) Each pixel is an integer four-component group*/
	RgbaInteger = GL_RGBA_INTEGER,

	/*(3.0) Each pixel is an integer reversed three-component group*/
	BgrInteger = GL_BGR_INTEGER,

	/*(3.0) Each pixel is an integer reversed four-component group*/
	BgraInteger = GL_BGRA_INTEGER,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD texture input pixel format enumerator used in <texImage>*/
enum class TexFormat : GLenum
{
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

	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

#ifdef GL_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,

	/*(3.0) Each pixel is a single integer red component*/
	RedInteger = GL_RED_INTEGER,

	/*(3.0) Each pixel is an integer two-component group*/
	RgInteger = GL_RG_INTEGER,

	/*(3.0) Each pixel is an integer three-component group*/
	RgbInteger = GL_RGB_INTEGER,

	/*(3.0) Each pixel is an integer four-component group*/
	RgbaInteger = GL_RGBA_INTEGER,

	/*(3.0) Each pixel is an integer reversed three-component group*/
	BgrInteger = GL_BGR_INTEGER,

	/*(3.0) Each pixel is an integer reversed four-component group*/
	BgraInteger = GL_BGRA_INTEGER,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD texture internal pixel format enumerator used in <texImage>*/
enum class TexInternalformat : GLenum
{
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

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

#ifdef GL_VERSION_2_1
	/*(2.1) Single 24-bit value used for three (8:8:8)-bit color space components*/
	Srgb8 = GL_SRGB8,

	/*(2.1) Each pixel is a four-component color space group*/
	SrgbAlpha = GL_SRGB_ALPHA,

	/*(2.1) Generic compressed three-component color space format*/
	CompressedSrgb = GL_COMPRESSED_SRGB,

	/*(2.1) Generic compressed four-component color space format*/
	CompressedSrgbAlpha = GL_COMPRESSED_SRGB_ALPHA,
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
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

	/*(3.0) Single 32-bit value used for two float (16f:16f)-bit color components*/
	Rg16f = GL_RG16F,

	/*(3.0) Single 48-bit value used for three float (16f:16f:16f)-bit color components*/
	Rgb16f = GL_RGB16F,

	/*(3.0) Single 64-bit value used for four float (16f:16f:16f:16f)-bit color components*/
	Rgba16f = GL_RGBA16F,

	/*(3.0) Single 32-bit float red component*/
	R32f = GL_R32F,

	/*(3.0) Single 64-bit value used for two float (32f:32f)-bit color components*/
	Rg32f = GL_RG32F,

	/*(3.0) Single 96-bit value used for three float (32f:32f:32f)-bit color components*/
	Rgb32f = GL_RGB32F,

	/*(3.0) Single 128-bit value used for four float (32f:32f:32f:32f)-bit color components*/
	Rgba32f = GL_RGBA32F,

	/*(3.0) Special 32-bit value used for three no-sign float (11f:11f:10f)-bit color components*/
	R11fG11fB10f = GL_R11F_G11F_B10F,

	/*(3.0) Special 32-bit value used for three float (9f:9f:9f:5e)-bit color components with shared 5-bit exponent*/
	Rgb9E5 = GL_RGB9_E5,

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

	/*(3.0) Single 24-bit value used for three signed integer (8:8:8)-bit color components*/
	Rgb8i = GL_RGB8I,

	/*(3.0) Single 24-bit value used for three unsigned integer (8:8:8)-bit color components*/
	Rgb8ui = GL_RGB8UI,

	/*(3.0) Single 48-bit value used for three signed integer (16:16:16)-bit color components*/
	Rgb16i = GL_RGB16I,

	/*(3.0) Single 48-bit value used for three unsigned integer (16:16:16)-bit color components*/
	Rgb16ui = GL_RGB16UI,

	/*(3.0) Single 96-bit value used for three signed integer (32:32:32)-bit color components*/
	Rgb32i = GL_RGB32I,

	/*(3.0) Single 96-bit value used for three unsigned integer (32:32:32)-bit color components*/
	Rgb32ui = GL_RGB32UI,

	/*(3.0) Single 32-bit value used for four signed integer (8:8:8:8)-bit color components*/
	Rgba8i = GL_RGBA8I,

	/*(3.0) Single 32-bit value used for four unsigned integer (8:8:8:8)-bit color components*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.0) Single 64-bit value used for four signed integer (16:16:16:16)-bit color components*/
	Rgba16i = GL_RGBA16I,

	/*(3.0) Single 64-bit value used for four unsigned integer (16:16:16:16)-bit color components*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.0) Single 128-bit value used for four signed integer (32:32:32:32)-bit color components*/
	Rgba32i = GL_RGBA32I,

	/*(3.0) Single 128-bit value used for four unsigned integer (32:32:32:32)-bit color components*/
	Rgba32ui = GL_RGBA32UI,

	/*(3.0) Generic compressed one-component format*/
	CompressedRed = GL_COMPRESSED_RED,

	/*(3.0) Generic compressed two-component format*/
	CompressedRg = GL_COMPRESSED_RG,

	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	/*(3.1) Normalized 8-bit signed integer used for single color components*/
	R8Snorm = GL_R8_SNORM,

	/*(3.1) Normalized 16-bit signed integer used for single color components*/
	R16Snorm = GL_R16_SNORM,

	/*(3.1) Single 16-bit value used for two normalized signed integer (8:8)-bit color components*/
	Rg8Snorm = GL_RG8_SNORM,

	/*(3.1) Single 32-bit value used for two normalized signed integer (16:16)-bit color components*/
	Rg16Snorm = GL_RG16_SNORM,

	/*(3.1) Single 24-bit value used for three normalized signed integer (8:8:8)-bit color components*/
	Rgb8Snorm = GL_RGB8_SNORM,

	/*(3.1) Single 48-bit value used for three normalized signed integer (16:16:16)-bit color components*/
	Rgb16Snorm = GL_RGB16_SNORM,

	/*(3.1) Single 64-bit value used for four normalized signed integer (8:8:8:8)-bit color components*/
	Rgba8Snorm = GL_RGBA8_SNORM,
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_3
	/*(3.3) Unsigned 32-bit integer used for four (8:8:8:2)-bit color components*/
	Rgb10A2ui = GL_RGB10_A2UI,
#endif // #ifdef GL_VERSION_3_3
};

/*GLAD texture input pixel format enumerator used in <texSubImage>*/
enum class TexSubFormat : GLenum
{
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

	/*Each pixel is a single stencil index value. It is converted to fixed-point format, with an unspecified number of bits to the right of the binary point, regardless of the memory data type*/
	StencilIndex = GL_STENCIL_INDEX,

	/*Each pixel is a single-depth component. Floating-point data is converted directly to an internal floating-point format with unspecified precision*/
	DepthComponent = GL_DEPTH_COMPONENT,

#ifdef GL_VERSION_3_0
	/*(3.0) Each pixel is a two-component group*/
	Rg = GL_RG,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD texture input pixel type enumerator used in <texSubImage>*/
enum class TexSubType : GLenum
{
	/*Unsigned 8-bit value used for each color component*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*Signed 8-bit used for each color component*/
	Byte = GL_BYTE,

	/*Unsigned 16-bit value used for each color component*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*Signed 16-bit value used for each color component*/
	Short = GL_SHORT,

	/*Unsigned 32-bit value used for each color component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Signed 32-bit value used for each color component*/
	Int = GL_INT,

	/*Float 32-bit value used for each color component*/
	Float = GL_FLOAT,

	/*Single 8-bit value used for three unsigned integer (3:3:2)-bit color components, format must be <Rgb>*/
	UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,

	/*Single 8-bit value used for three unsigned integer (2:3:3)-bit reversed color components, format must be <Bgr>*/
	UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit color components, format must be <Rgb>*/
	UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,

	/*Single 16-bit value used for three unsigned integer (5:6:5)-bit reversed color components, format must be <Bgr>*/
	UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit color components, format must be <Rgba>*/
	UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,

	/*Single 16-bit value used for four unsigned integer (4:4:4:4)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,

	/*Single 16-bit value used for four unsigned integer (5:5:5:1)-bit color components, format must be <Rgba>*/
	UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,

	/*Single 16-bit value used for four unsigned integer (1:5:5:5)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit color components, format must be <Rgba>*/
	UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,

	/*Single 32-bit value used for four unsigned integer (8:8:8:8)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,

	/*Single 32-bit value used for four unsigned integer (10:10:10:2)-bit color components, format must be <Rgba>*/
	UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,

	/*Single 32-bit value used for four unsigned integer (2:10:10:10)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
};

/*GLAD texture magnifying function enumerator*/
enum class TextureMagFilter : GLenum
{
	/*Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates*/
	Nearest = GL_NEAREST,

	/*Returns the weighted average of the four texture elements that are closest to the specified texture coordinates*/
	Linear = GL_LINEAR,
};

/*GLAD texture minifying function enumerator*/
enum class TextureMinFilter : GLenum
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

/*GLAD texture wrap mode enumerator*/
enum class TextureWrapMode : GLenum
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

/*GLAD texture input pixel type enumerator used by <texImage>*/
enum class TexType : GLenum
{
	/*Unsigned 8-bit value used for each color component*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*Signed 8-bit used for each color component*/
	Byte = GL_BYTE,

	/*Unsigned 16-bit value used for each color component*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*Signed 16-bit value used for each color component*/
	Short = GL_SHORT,

	/*Unsigned 32-bit value used for each color component*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*Signed 32-bit value used for each color component*/
	Int = GL_INT,

	/*Float 32-bit value used for each color component*/
	Float = GL_FLOAT,

	/*Unsigned 8-bit value used for three (3:3:2)-bit color components, format must be <Rgb>*/
	UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,

	/*Unsigned 8-bit value used for three (2:3:3)-bit reversed color components, format must be <Bgr>*/
	UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,

	/*Unsigned 16-bit value used for three (5:6:5)-bit color components, format must be <Rgb>*/
	UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,

	/*Unsigned 16-bit value used for three (5:6:5)-bit reversed color components, format must be <Bgr>*/
	UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,

	/*Unsigned 16-bit value used for four (4:4:4:4)-bit color components, format must be <Rgba>*/
	UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,

	/*Unsigned 16-bit value used for four (4:4:4:4)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,

	/*Unsigned 16-bit value used for four (5:5:5:1)-bit color components, format must be <Rgba>*/
	UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,

	/*Unsigned 16-bit value used for four (1:5:5:5)-bit reversed color components, format must be <Bgra>*/
	UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,

	/*Unsigned 32-bit value used for four (8:8:8:8)-bit color components, format must be <Rgba>*/
	UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,

	/*Unsigned 32-bit value used for four (8:8:8:8)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,

	/*Unsigned 32-bit value used for four (10:10:10:2)-bit color components, format must be <Rgba>*/
	UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,

	/*Unsigned 32-bit value used for four (2:10:10:10)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

#ifdef GL_VERSION_3_0
	HalfFloat = GL_HALF_FLOAT,
#endif // #ifdef GL_VERSION_3_0
};

#ifdef GL_VERSION_3_0
/*(3.0) GLAD texture compare mode enumerator*/
enum class TextureCompareMode : GLenum
{
	/*(3.0) Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture*/
	CompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE,

	/*(3.0) Specifies that the red channel should be assigned the appropriate value from the currently bound depth texture*/
	None = GL_NONE,
};

/*(3.0) GLAD texture component type enumerator*/
enum class TextureComponentType : GLenum
{
	/*(3.0) The component type is unset*/
	None = GL_NONE,

	/*(3.0) Unsigned normalized fixed-point component*/
	UnsignedNormalized = GL_UNSIGNED_NORMALIZED,

	/*(3.0) Floating-point component*/
	Float = GL_FLOAT,

	/*(3.0) Integer unnormalized component*/
	Int = GL_INT,

	/*(3.0) Unsigned integer unnormalized component*/
	UnsignedInt = GL_UNSIGNED_INT,

#ifdef GL_VERSION_3_1
	/*(3.1) Signed normalized fixed-point component*/
	SignedNormalized = GL_SIGNED_NORMALIZED,
#endif // #ifdef GL_VERSION_3_1
};
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
/*(3.3) GLAD texture swizzle mask enumerator*/
enum class TextureSwizzleMask : GLenum
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
#endif // #ifdef GL_VERSION_3_3

/*OpenGL texture object abstract class derived from <_Object>*/
class _Texture : public _Object
{
#ifdef GL_VERSION_3_0
	friend _Framebuffer;
#endif // #ifdef GL_VERSION_3_0
protected:
	void _activeTexture(GLenum target, GLenum binding, TextureUnit index);
	void _bindTexture(GLenum target, GLenum binding);
	static void _compressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data);
	void _compressedTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data);
	static void _compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data);
	void _compressedTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data);
	void _compressedTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data);
	static void _compressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data);
	void _compressedTexImage3D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data);
	static void _compressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data);
	void _compressedTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data);
	static void _compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data);
	void _compressedTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data);
	void _compressedTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data);
	static void _compressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data);
	void _compressedTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data);
	void _copyTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width);
	void _copyTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
	void _copyTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
	void _copyTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	void _copyTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void _copyTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void _copyTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	static void _getCompressedTexImage(GLenum target, GLint level, void* pixels);
	void _getCompressedTexImage(GLenum target, GLenum binding, GLint level, void* pixels);
	void _getCompressedTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, void* pixels);
	static void _getTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
	void _getTexImage(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, void* pixels);
	void _getTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum format, GLenum type, void* pixels);
	static GLint _getTexLevelParameter(GLenum target, GLint level, GLenum pname);
	GLint _getTexLevelParameter(GLenum target, GLenum binding, GLint level, GLenum pname);
	GLint _getTexLevelParameter(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum pname);
	GLint _getTexParameter(GLenum target, GLenum binding, GLenum pname);
	GLfloat _getTexParameterFloat(GLenum target, GLenum binding, GLenum pname);
	void _getTexParameter(GLenum target, GLenum binding, GLenum pname, GLint* param);
	void _getTexParameter(GLenum target, GLenum binding, GLenum pname, GLfloat* param);
	static GLenum _siFormat(StbImage& image);
	static GLenum _siType(StbImage& image);
	static void _texImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data);
	void _texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image);
	void _texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data);
	static void _texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);
	void _texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image);
	void _texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, StbImage& image);
	void _texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);
	void _texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data);
	static void _texImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data);
	void _texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei layers, StbImage& image);
	void _texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data);
	void _texParameter(GLenum target, GLenum binding, GLenum pname, GLint param);
	void _texParameter(GLenum target, GLenum binding, GLenum pname, GLfloat param);
	void _texParameter(GLenum target, GLenum binding, GLenum pname, const GLint* param);
	void _texParameter(GLenum target, GLenum binding, GLenum pname, const GLfloat* param);
	static void _texSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
	void _texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, StbImage& image);
	void _texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
	static void _texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void _texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, StbImage& image);
	void _texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, StbImage& image);
	void _texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	void _texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	static void _texSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
	void _texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei layers, StbImage& image);
	void _texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
	static void _unbindTarget(GLenum target, GLenum binding);
	void _unbindTexture(GLenum target, GLenum binding);
	GLuint _texture_id()
	{
		return _object_id(glGenTextures);
	}

	void _setTextureBinding(GLenum target, GLenum binding, GLboolean bind)
	{
		(bind) ? _bindTexture(target, binding) : _unbindTexture(target, binding);
	}

#ifdef GL_VERSION_2_1
	void _compressedTexImage1D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexImage3D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _compressedTexSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset);
	void _getCompressedTexImage(GLenum target, GLenum binding, GLint level, _Buffer& buffer, GLintptr offset);
	void _getCompressedTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, _Buffer& buffer, GLintptr offset);
	void _getTexImage(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _getTexImage(GLenum target, GLenum binding, GLenum plane, GLint level, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
	void _texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset);
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	void _generateMipmap(GLenum target, GLenum binding);
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_1
	void _texBuffer(GLenum internalformat, _Buffer* buffer);
#endif // #ifdef GL_VERSION_3_1

#ifdef GL_VERSION_3_2
	static void _texImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	void _texImage2DMultisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	static void _texImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
	void _texImage3DMultisample(GLenum target, GLenum binding, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#endif // #ifdef GL_VERSION_3_2

public:
	/*Cleans up the valid texture object*/
	~_Texture()
	{
		if (isObject())
		{
			deleteTexture();
		}
	}

	/*Explicitly deletes previously generated single texture object name*/
	void deleteTexture()
	{
		_object_delete(glDeleteTextures);
	}

	/*Explicitly generates single texture object name in the empty texture object*/
	void genTexture()
	{
		_object_gen(glGenTextures);
	}

	/*Returns the index value of an active multitexture unit ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1
	@return The active multitexture unit index value*/
	static TextureUnit getActiveTexture()
	{
		return _getInteger(GL_ACTIVE_TEXTURE) - GL_TEXTURE0;
	}

	/*Gets the maximum supported texture image units that can be used to access texture maps from the vertex shader and the fragment processor combined
	@return The maximum supported texture image units. The value must be at least 48*/
	static GLuint getMaxCombinedTextureImageUnits()
	{
		return _getInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	}

	/*Gets the maximum supported texture image units that can be used to access texture maps from the fragment shader
	@return The maximum supported texture image units. The value must be at least 16*/
	static GLuint getMaxTextureImageUnits()
	{
		return _getInteger(GL_MAX_TEXTURE_IMAGE_UNITS);
	}

	/*Gets the value that gives a rough estimate of the largest 1D texture that the GL can handle
	@return The maximum texture size. The value must be at least 1024*/
	static GLsizei getMaxTextureSize()
	{
		return _getInteger(GL_MAX_TEXTURE_SIZE);
	}

	/*Determines if a name corresponds to a texture object. Used as a getter of <texture> property
	@return True if active texture object, false otherwise*/
	GLboolean isTexture()
	{
		return glIsTexture(_object_id());
	}

	/*Sets the creation state of the texture object, only if current state is opposite. Depending of the flag value, calls <genTexture> or <deleteTexture> functions. Used as a setter of <texture> property
	@param True to generate texture object name, false to delete texture object*/
	void setTexture(GLboolean gen);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for creation state of the texture object*/
	__declspec(property(get = isTexture, put = setTexture)) GLboolean texture;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_0
	/*(3.0) Get the maximum texel offset allowed in a texture lookup, which must be at least 7
	@return The maximum program texel offset*/
	static GLuint getMaxProgramTexelOffset()
	{
		return _getInteger(GL_MAX_PROGRAM_TEXEL_OFFSET);
	}

	/*(3.0) Get the minimum texel offset allowed in a texture lookup, which must be at most -8
	@return The minimum program texel offset*/
	static GLuint getMinProgramTexelOffset()
	{
		return _getInteger(GL_MIN_PROGRAM_TEXEL_OFFSET);
	}
#endif // #ifdef GL_VERSION_3_0
}; // class _Texture : public _Object
} // namespace gl

#include "_Buffer.h"
#include "StbImage.h"
namespace gl {
inline void _Texture::_compressedTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
	_compressedTexImage2D(target, binding, target, level, internalformat, width, height, imageSize, data);
}

inline void _Texture::_compressedTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
	_compressedTexSubImage2D(target, binding, target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
}

inline void _Texture::_copyTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_copyTexImage2D(target, binding, target, level, internalformat, x, y, width, height);
}

inline void _Texture::_copyTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_copyTexSubImage2D(target, binding, target, level, xoffset, yoffset, x, y, width, height);
}

inline void _Texture::_getCompressedTexImage(GLenum target, GLenum binding, GLint level, void* pixels)
{
	_getCompressedTexImage(target, binding, target, level, pixels);
}

inline void _Texture::_getTexImage(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, void* pixels)
{
	_getTexImage(target, binding, target, level, format, type, pixels);
}

inline GLint _Texture::_getTexLevelParameter(GLenum target, GLenum binding, GLint level, GLenum pname)
{
	return _getTexLevelParameter(target, binding, target, level, pname);
}

inline void _Texture::_texImage1D(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image)
{
	_texImage1D(target, binding, level, internalformat, image.getWidth(), _siFormat(image), _siType(image), image.getPixels());
}

inline void _Texture::_texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, StbImage& image)
{
	_texImage2D(target, binding, target, level, internalformat, image);
}

inline void _Texture::_texImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint internalformat, StbImage& image)
{
	_texImage2D(target, binding, plane, level, internalformat, image.getWidth(), image.getHeight(), _siFormat(image), _siType(image), image.getPixels());
}

inline void _Texture::_texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	_texImage2D(target, binding, target, level, internalformat, width, height, format, type, data);
}

inline void _Texture::_texImage3D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei layers, StbImage& image)
{
	_texImage3D(target, binding, level, internalformat, image.getWidth(), image.getHeight() / layers, layers, _siFormat(image), _siType(image), image.getPixels());
}

inline void _Texture::_texSubImage1D(GLenum target, GLenum binding, GLint level, GLint xoffset, StbImage& image)
{
	_texSubImage1D(target, binding, level, xoffset, image.getWidth(), _siFormat(image), _siType(image), image.getPixels());
}

inline void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, StbImage& image)
{
	_texSubImage2D(target, binding, target, level, xoffset, yoffset, image);
}

inline void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLenum plane, GLint level, GLint xoffset, GLint yoffset, StbImage& image)
{
	_texSubImage2D(target, binding, plane, level, xoffset, yoffset, image.getWidth(), image.getHeight(), _siFormat(image), _siType(image), image.getPixels());
}

inline void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	_texSubImage2D(target, binding, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void _Texture::_texSubImage3D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei layers, StbImage& image)
{
	_texSubImage3D(target, binding, level, xoffset, yoffset, zoffset, image.getWidth(), image.getHeight() / layers, layers, _siFormat(image), _siType(image), image.getPixels());
}

#ifndef _DEBUG
inline void _Texture::_compressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, const void* data)
{
	glCompressedTexImage1D(target, level, internalformat, width, 0, imageSize, data);
}

inline void _Texture::_compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, const void* data)
{
	glCompressedTexImage2D(target, level, internalformat, width, height, 0, imageSize, data);
}

inline void _Texture::_compressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, const void* data)
{
	glCompressedTexImage3D(target, level, internalformat, width, height, depth, 0, imageSize, data);
}

inline void _Texture::_compressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage1D(target, level, xoffset, width, internalformat, imageSize, data);
}

inline void _Texture::_compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
}

inline void _Texture::_compressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, const void* data)
{
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
}

inline void _Texture::_getCompressedTexImage(GLenum target, GLint level, void* pixels)
{
	glGetCompressedTexImage(target, level, pixels);
}

inline void _Texture::_getTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels)
{
	glGetTexImage(target, level, format, type, pixels);
}

inline GLint _Texture::_getTexLevelParameter(GLenum target, GLint level, GLenum pname)
{
	GLint iData = 0; glGetTexLevelParameteriv(target, level, pname, &iData); return iData;
}

inline void _Texture::_texImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const void* data)
{
	glTexImage1D(target, level, internalformat, width, 0, format, type, data);
}

inline void _Texture::_texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
}

inline void _Texture::_texImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
	glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
}

inline void _Texture::_texSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

inline void _Texture::_texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void _Texture::_texSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
#endif // #ifndef _DEBUG

#ifdef GL_VERSION_2_1
inline void _Texture::_compressedTexImage2D(GLenum target, GLenum binding, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	_compressedTexImage2D(target, binding, target, level, internalformat, width, height, imageSize, buffer, offset);
}

inline void _Texture::_compressedTexSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _Buffer& buffer, GLintptr offset)
{
	_compressedTexSubImage2D(target, binding, target, level, xoffset, yoffset, width, height, internalformat, imageSize, buffer, offset);
}

inline void _Texture::_getCompressedTexImage(GLenum target, GLenum binding, GLint level, _Buffer& buffer, GLintptr offset)
{
	_getCompressedTexImage(target, binding, target, level, buffer, offset);
}

inline void _Texture::_getTexImage(GLenum target, GLenum binding, GLint level, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	_getTexImage(target, binding, target, level, format, type, buffer, offset);
}

inline void _Texture::_texImage2D(GLenum target, GLenum binding, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	_texImage2D(target, binding, target, level, internalformat, width, height, format, type, buffer, offset);
}

inline void _Texture::_texSubImage2D(GLenum target, GLenum binding, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, _Buffer& buffer, GLintptr offset)
{
	_texSubImage2D(target, binding, target, level, xoffset, yoffset, width, height, format, type, buffer, offset);
}
#endif // #ifdef GL_VERSION_2_1

#if !defined(_DEBUG) && defined(GL_VERSION_3_2)
inline void _Texture::_texImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

inline void _Texture::_texImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
#endif // #if !defined(_DEBUG) && defined(GL_VERSION_3_2)
} // namespace gl

#ifndef YAGLPP_BUILD_LIB
#include "Texture1D.h"
#include "Texture2D.h"
#include "Texture3D.h"
#include "TextureCubeMap.h"
#include "Texture1DArray.h"
#include "Texture2DArray.h"
#include "BufferTexture.h"
#include "TextureRectangle.h"
#include "Texture2DMultisample.h"
#include "Texture2DMultisampleArray.h"
#endif // #ifdef YAGLPP_BUILD
