#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_GLADPP_H
#define YAGLPP_GLADPP_H
#include <glad/glad.h>

#ifdef YAGLPP_IMPLEMENTATION
	#ifdef _DEBUG
		#define YAGLPP_GLAD_ERROR YAGLPP_ASSERT(yaglpp_glad_error())
	#else
		#define YAGLPP_GLAD_ERROR ((void)0)
	#endif
	#ifdef YAGLPP_MSVC
		#define YAGLPP__S(x) #x
		#define YAGLPP__X(x) YAGLPP__S(x)
		#pragma message ("YAGL++: Compiling with OpenGL " YAGLPP__X(YAGLPP_CONTEXT_VERSION_MAJOR) "." YAGLPP__X(YAGLPP_CONTEXT_VERSION_MINOR) " context version support...")
		#undef YAGLPP__S
		#undef YAGLPP__X
	#endif
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 20
	#define YAGLPP_VERSION_2_1
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 21
	#define YAGLPP_VERSION_3_0
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 30
	#define YAGLPP_VERSION_3_1
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 31
	#define YAGLPP_VERSION_3_2
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 32
	#define YAGLPP_VERSION_3_3
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 33
	#define YAGLPP_VERSION_4_0
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 40
	#define YAGLPP_VERSION_4_1
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 41
	#define YAGLPP_VERSION_4_2
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 42
	#define YAGLPP_VERSION_4_3
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 43
	#define YAGLPP_VERSION_4_4
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 44
	#define YAGLPP_VERSION_4_5
#endif

#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 45
	#define YAGLPP_VERSION_4_6
#endif

/*YAGL++ GLAD library namespace*/
namespace gl {
class ArrayBuffer;
class Buffers;
class ElementArrayBuffer;
class FragmentShader;
class Objects;
class Program;
class Queries;
class SamplesPassed;
class Shaders;
class Textures;
class Texture1D;
class Texture2D;
class Texture3D;
class TextureCubeMap;
class Uniform;
class VertexAttrib;
class VertexShader;
void yaglpp_glad_free();
void yaglpp_glad_load(void* proc);
void yaglpp_glad_pixel(GLenum pname, GLint param);
inline GLboolean yaglpp_glad_boolean(GLenum p)
{
	GLboolean b; glGetBooleanv(p, &b); return b;
}

inline GLdouble yaglpp_glad_double(GLenum p)
{
	GLdouble d; glGetDoublev(p, &d); return d;
}

inline GLfloat yaglpp_glad_float(GLenum p)
{
	GLfloat f; glGetFloatv(p, &f); return f;
}

inline GLint yaglpp_glad_integer(GLenum p)
{
	GLint i; glGetIntegerv(p, &i); return i;
}

/*GLAD draw buffer unit index ranging from 0 to the value returned by <GetMaxDrawBuffers> minus 1*/
typedef unsigned int BufferUnit;

/*GLAD active texture unit index ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1*/
typedef unsigned int TextureUnit;

/*GLAD GL behavior hint enumerator*/
enum class BehaviorHint : GLenum
{
	/*No preference*/
	DontCare = GL_DONT_CARE,

	/*The most efficient option should be chosen*/
	Fastest = GL_FASTEST,

	/*The most correct, or highest quality, option should be chosen*/
	Nicest = GL_NICEST,
};

/*GLAD blend function factor enumerator*/
enum class BlendFactor : GLenum
{
	/*Zero blend function factor calculated per-channel as 0*/
	Zero = GL_ZERO,

	/*One blend function factor calculated per-channel as 1*/
	One = GL_ONE,

	/*Source color blend function factor calculated per-channel as (Src0 / Max)*/
	SrcColor = GL_SRC_COLOR,

	/*One minus source color blend function factor calculated per-channel as 1 - (Src0 / Max)*/
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,

	/*Source alpha blend function factor calculated per-channel as (SrcAlpha0 / Max)*/
	SrcAlpha = GL_SRC_ALPHA,

	/*One minus source alpha blend function factor calculated per-channel as 1 - (SrcAlpha0 / Max)*/
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,

	/*Destination alpha blend function factor calculated per-channel as (DstAlpha0 / Max)*/
	DstAlpha = GL_DST_ALPHA,

	/*One minus destination alpha blend function factor calculated per-channel as 1 - (DstAlpha0 / Max)*/
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,

	/*Destination color blend function factor calculated per-channel as (Dst0 / Max)*/
	DstColor = GL_DST_COLOR,

	/*One minus destination color blend function factor calculated per-channel as 1 - (Dst0 / Max)*/
	OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,

	/*Constant color blend function factor calculated per-channel as BlendClr*/
	ConstantColor = GL_CONSTANT_COLOR,

	/*One minus constant color blend function factor calculated per-channel as 1 - BlendClr*/
	OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,

	/*Constant alpha blend function factor calculated per-channel as BlendClrAlpha*/
	ConstantAlpha = GL_CONSTANT_ALPHA,

	/*One minus constant alpha blend function factor calculated per-channel as 1 - BlendClrAlpha*/
	OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,

	/*Source alpha saturate blend function factor calculated for RGB channels as min(SrcAlpha, 1 - DstAlpha), and for alpha channel as 1*/
	SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,

	/*Source-one alpha blend function factor calculated per-channel as (Src1Alpha / MaxAlpha)*/
	Src1Alpha = GL_SRC1_ALPHA,

#ifdef YAGLPP_VERSION_3_3
	/*Source-one color blend function factor calculated per-channel as (Src1 / Max)*/
	Src1Color = GL_SRC1_COLOR,

	/*One minus source-one color blend function factor calculated per-channel as 1 - (Src1 / Max)*/
	OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,

	/*One minus source-one alpha blend function factor calculated per-channel as 1 - (Src1Alpha / MaxAlpha)*/
	OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
#endif // #ifdef YAGLPP_VERSION_3_3
};

/*GLAD blend equation mode enumerator*/
enum class BlendMode : GLenum
{
	/*Add blend equation mode calculated per-channel as (Src * SrcFact) + (Dst * DstFact) clamped to [0, 1]*/
	Add = GL_FUNC_ADD,

	/*Min blend equation mode calculated per-channel as min(Src, Dst) clamped to [0, 1]*/
	Min = GL_MIN,

	/*Max blend equation mode calculated per-channel as max(Src, Dst) clamped to [0, 1]*/
	Max = GL_MAX,

	/*Subtract blend equation mode calculated per-channel as (Src * SrcFact) - (Dst * DstFact) clamped to [0, 1]*/
	Subtract = GL_FUNC_SUBTRACT,

	/*Reversed subtract blend equation mode calculated per-channel as (Src * SrcFact) - (Dst * DstFact) clamped to [0, 1]*/
	ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
};

/*GLAD buffer bit mask enumerator*/
enum class BufferBit : GLbitfield
{
	/*Indicates the depth buffer*/
	Depth = GL_DEPTH_BUFFER_BIT,

	/*Indicates the stencil buffer*/
	Stencil = GL_STENCIL_BUFFER_BIT,

	/*Indicates the buffers currently enabled for color writing*/
	Color = GL_COLOR_BUFFER_BIT,
};

/*GLAD color-renderable, depth-renderable, or stencil-renderable format enumerator*/
enum class ColorDepthStencil : GLenum
{
	/*RGB color component format with (8:8:8)-bit resolution*/
	Rgb8 = GL_RGB8,

	/*RGBA color component format with (4:4:4:4)-bit resolution*/
	Rgba4 = GL_RGBA4,

	/*RGBA color component format with (5:5:5:1)-bit resolution*/
	Rgb5A1 = GL_RGB5_A1,

	/*RGBA color component format with (8:8:8:8)-bit resolution*/
	Rgba8 = GL_RGBA8,

	/*RGBA color component format with (10:10:10:2)-bit resolution*/
	Rgb10A2 = GL_RGB10_A2,

	/*Depth component format with 16-bit resolution*/
	DepthComponent16 = GL_DEPTH_COMPONENT16,

	/*Depth component format with 24-bit resolution*/
	DepthComponent24 = GL_DEPTH_COMPONENT24,

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) SRGB Alpha color component format with (8:8:8:8)-bit resolution*/
	Srgb8Alpha8 = GL_SRGB8_ALPHA8,
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Red color component format with 8-bit resolution*/
	R8 = GL_R8,

	/*(3.0) RG color component format with (8:8)-bit resolution*/
	Rg8 = GL_RG8,

	/*(3.0) Red signed integer color component format with 8-bit resolution*/
	R8i = GL_R8I,

	/*(3.0) Red unsigned integer color component format with 8-bit resolution*/
	R8ui = GL_R8UI,

	/*(3.0) Red signed integer color component format with 16-bit resolution*/
	R16i = GL_R16I,

	/*(3.0) Red unsigned integer color component format with 16-bit resolution*/
	R16ui = GL_R16UI,

	/*(3.0) Red signed integer color component format with 32-bit resolution*/
	R32i = GL_R32I,

	/*(3.0) Red unsigned integer color component format with 32-bit resolution*/
	R32ui = GL_R32UI,

	/*(3.0) RG signed integer color component format with (8:8)-bit resolution*/
	Rg8i = GL_RG8I,

	/*(3.0) RG unsigned integer color component format with (8:8)-bit resolution*/
	Rg8ui = GL_RG8UI,

	/*(3.0) RG signed integer color component format with (16:16)-bit resolution*/
	Rg16i = GL_RG16I,

	/*(3.0) RG unsigned integer color component format with (16:16)-bit resolution*/
	Rg16ui = GL_RG16UI,

	/*(3.0) RG signed integer color component format with (32:32)-bit resolution*/
	Rg32i = GL_RG32I,

	/*(3.0) RG unsigned integer color component format with (32:32)-bit resolution*/
	Rg32ui = GL_RG32UI,

	/*(3.0) Depth and stencil component format with (24:8)-bit resolution*/
	Depth24Stencil8 = GL_DEPTH24_STENCIL8,

	/*(3.0) Depth component format with 32f-bit resolution*/
	DepthComponent32f = GL_DEPTH_COMPONENT32F,

	/*(3.0) Depth and stencil component format with (32f:8)-bit resolution*/
	Depth32fStencil8 = GL_DEPTH32F_STENCIL8,

	/*(3.0) Stencil component format with 8-bit resolution*/
	StencilIndex8 = GL_STENCIL_INDEX8,

	/*(3.0) RGBA unsigned integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32ui = GL_RGBA32UI,

	/*(3.0) RGBA unsigned integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.0) RGBA unsigned integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.0) RGBA signed integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32i = GL_RGBA32I,

	/*(3.0) RGBA signed integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16i = GL_RGBA16I,

	/*(3.0) RGBA signed integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8i = GL_RGBA8I,
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) RGBA unsigned integer color component format with (10:10:10:2)-bit resolution*/
	Rgb10A2ui = GL_RGB10_A2UI,
#endif // #ifdef YAGLPP_VERSION_3_3
};

/*GLAD comparison function enumerator*/
enum class CompareFunc : GLenum
{
	/*Never passes, result defers on particular implementation*/
	Never = GL_NEVER,

	/*Passes if less, for details refer to particular function implementation*/
	Less = GL_LESS,

	/*Passes if equal, for details refer to particular function implementation*/
	Equal = GL_EQUAL,

	/*Passes if less or equal, for details refer to particular function implementation*/
	Lequal = GL_LEQUAL,

	/*Passes if greater, for details refer to particular function implementation*/
	Greater = GL_GREATER,

	/*Passes if not equal, for details refer to particular function implementation*/
	Notequal = GL_NOTEQUAL,

	/*Passes if greater or equal, for details refer to particular function implementation*/
	Gequal = GL_GEQUAL,

	/*Always passes, for details refer to particular function implementation*/
	Always = GL_ALWAYS,
};

/*GLAD polygon rasterization mode enumerator*/
enum class DrawMode : GLenum
{
	/*Polygon vertices that are marked as the start of a boundary edge are drawn as points*/
	Point = GL_POINT,

	/*Boundary edges of the polygon are drawn as line segments*/
	Line = GL_LINE,

	/*The interior of the polygon is filled*/
	Fill = GL_FILL,
};

/*GLAD draw buffer unit enumerator used by <DrawBuffer>*/
enum class DrawUnit : GLenum
{
	/*No color buffers are written*/
	None = GL_NONE,

	/*Only the front left color buffer is written*/
	FrontLeft = GL_FRONT_LEFT,

	/*Only the front right color buffer is written*/
	FrontRight = GL_FRONT_RIGHT,

	/*Only the back left color buffer is written*/
	BackLeft = GL_BACK_LEFT,

	/*Only the back right color buffer is written*/
	BackRight = GL_BACK_RIGHT,

	/*Only the front left and front right color buffers are written. If there is no front right color buffer, only the front left color buffer is written*/
	Front = GL_FRONT,

	/*Only the back left and back right color buffers are written. If there is no back right color buffer, only the back left color buffer is written*/
	Back = GL_BACK,

	/*Only the front left and back left color buffers are written. If there is no back left color buffer, only the front left color buffer is written*/
	Left = GL_LEFT,

	/*Only the front right and back right color buffers are written. If there is no back right color buffer, only the front right color buffer is written*/
	Right = GL_RIGHT,

	/*All the front and back color buffers (front left, front right, back left, back right) are written. If there are no back color buffers, only the front left and front right color buffers are written. If there are no right color buffers, only the front left and back left color buffers are written. If there are no right or back color buffers, only the front left color buffer is written*/
	FrontAndBack = GL_FRONT_AND_BACK,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Framebuffer color attachment unit 0*/
	Color0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	Color1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	Color2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	Color3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	Color4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	Color5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	Color6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	Color7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	Color8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	Color9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	Color10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	Color11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	Color12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	Color13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	Color14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	Color15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	Color16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	Color17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	Color18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	Color19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	Color20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	Color21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	Color22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	Color23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	Color24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	Color25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	Color26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	Color27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	Color28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	Color29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	Color30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	Color31 = GL_COLOR_ATTACHMENT31,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD draw buffer unit enumerator used by <DrawBuffers>*/
enum class DrawUnits : GLenum
{
	/*The fragment shader output value is not written into any color buffer*/
	None = GL_NONE,

	/*The fragment shader output value is written into the front left color buffer*/
	FrontLeft = GL_FRONT_LEFT,

	/*The fragment shader output value is written into the front right color buffer*/
	FrontRight = GL_FRONT_RIGHT,

	/*The fragment shader output value is written into the back left color buffer*/
	BackLeft = GL_BACK_LEFT,

	/*The fragment shader output value is written into the back right color buffer*/
	BackRight = GL_BACK_RIGHT,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Framebuffer color attachment unit 0*/
	Color0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	Color1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	Color2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	Color3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	Color4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	Color5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	Color6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	Color7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	Color8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	Color9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	Color10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	Color11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	Color12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	Color13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	Color14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	Color15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	Color16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	Color17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	Color18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	Color19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	Color20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	Color21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	Color22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	Color23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	Color24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	Color25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	Color26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	Color27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	Color28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	Color29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	Color30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	Color31 = GL_COLOR_ATTACHMENT31,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD face plane mode enumerator*/
enum class FaceMode : GLenum
{
	/*Front-facing facet candidate*/
	Front = GL_FRONT,

	/*Back-facing facet candidate*/
	Back = GL_BACK,

	/*No facets are drawn, but other primitives such as points and lines are drawn*/
	FrontAndBack = GL_FRONT_AND_BACK,
};

/*GLAD orientation of front-facing polygons enumerator used by <FrontFace>*/
enum class FrontMode : GLenum
{
	/*Selects clockwise polygons as front-facing*/
	Cw = GL_CW,

	/*Selects counterclockwise polygons as front-facing*/
	Ccw = GL_CCW,
};

/*GLAD logic operation mode enumerator*/
enum class LogicMode : GLenum
{
	/*Logic operation mode: dst = 0*/
	Clear = GL_CLEAR,

	/*Logic operation mode: dst = src & dst*/
	And = GL_AND,

	/*Logic operation mode: dst = src & ~dst*/
	AndReverse = GL_AND_REVERSE,

	/*Logic operation mode: dst = src*/
	Copy = GL_COPY,

	/*Logic operation mode: dst = ~src & dst*/
	AndInverted = GL_AND_INVERTED,

	/*Logic operation mode: dst = dst*/
	Noop = GL_NOOP,

	/*Logic operation mode: dst = src ^ dst*/
	Xor = GL_XOR,

	/*Logic operation mode: dst = src | dst*/
	Or = GL_OR,

	/*Logic operation mode: dst = ~(src | dst)*/
	Nor = GL_NOR,

	/*Logic operation mode: dst = ~(src ^ dst)*/
	Equiv = GL_EQUIV,

	/*Logic operation mode: dst = ~dst*/
	Invert = GL_INVERT,

	/*Logic operation mode: dst = src | ~dst*/
	OrReverse = GL_OR_REVERSE,

	/*Logic operation mode: dst = ~src*/
	CopyInverted = GL_COPY_INVERTED,

	/*Logic operation mode: dst = ~src | dst*/
	OrInverted = GL_OR_INVERTED,

	/*Logic operation mode: dst = ~(src & dst)*/
	Nand = GL_NAND,

	/*Logic operation mode: dst = 1*/
	Set = GL_SET,
};

/*GLAD pixel memory alignment enumerator*/
enum class PixelAlignment : GLenum
{
	/*One byte alignment*/
	One = 1,

	/*Two bytes alignment (rows aligned to even-numbered bytes)*/
	Two = 2,

	/*Four byte alignment (word-alignment)*/
	Four = 4,

	/*Eight byte alignment (rows start on double-word boundaries)*/
	Eight = 8,
};

/*GLAD pixel format enumerator*/
enum class PixelFormat : GLenum
{
	/*One-channel pixel format: grey*/
	Red = GL_RED,

	/*Three-channel pixel format: red, green, blue*/
	Rgb = GL_RGB,

	/*Four-channel pixel format: red, green, blue, alpha*/
	Rgba = GL_RGBA,

#ifdef YAGLPP_VERSION_3_0
	/*Two-channel pixel format: grey, alpha*/
	Rg = GL_RG,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD point sprite texture coordinate origin enumerator*/
enum class PointOrigin : GLenum
{
	/*Lower left origin*/
	LowerLeft = GL_LOWER_LEFT,

	/*Upper left origin*/
	UpperLeft = GL_UPPER_LEFT,
};

/*GLAD primitive mode enumerator*/
enum class PrimitiveMode : GLenum
{
	/*Causes OpenGL to interpret each individual vertex in the stream as a point. Points that have a texture mapped onto them are often called "point sprites"*/
	Points = GL_POINTS,

	/*Vertices 0 and 1 are considered a line. Vertices 2 and 3 are considered a line. And so on. If the user specifies a non-even number of vertices, then the extra vertex is ignored*/
	Lines = GL_LINES,

	/*As <LineStrip>, except that the first and last vertices are also used as a line. Thus, you get n lines for n input vertices. If the user only specifies 1 vertex, the drawing command is ignored. The line between the first and last vertices happens after all of the previous lines in the sequence*/
	LineLoop = GL_LINE_LOOP,

	/*The adjacent vertices are considered lines. Thus, if you pass n vertices, you will get n-1 lines. If the user only specifies 1 vertex, the drawing command is ignored*/
	LineStrip = GL_LINE_STRIP,

	/*Vertices 0, 1, and 2 form a triangle. Vertices 3, 4, and 5 form a triangle. And so on*/
	Triangles = GL_TRIANGLES,

	/*Every group of 3 adjacent vertices forms a triangle. The face direction of the strip is determined by the winding of the first triangle. Each successive triangle will have its effective face order reversed, so the system compensates for that by testing it in the opposite way. A vertex stream of n length will generate n-2 triangles*/
	TriangleStrip = GL_TRIANGLE_STRIP,

	/*The first vertex is always held fixed. From there on, every group of 2 adjacent vertices form a triangle with the first. So with a vertex stream, you get a list of triangles like so: (0, 1, 2) (0, 2, 3), (0, 3, 4), etc. A vertex stream of n length will generate n-2 triangles*/
	TriangleFan = GL_TRIANGLE_FAN,

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) If 4 vertices are given, a line segment is drawn between 1 and 2. Vertices 0 and 3 are there to provide adjacency information*/
	LinesAdjacency = GL_LINES_ADJACENCY,

	/*(3.2) If 6 vertices are given, a line segment is drawn between 1 and 2, 2 and 3, 3 and 4. Vertices 0 and 5 are there to provide adjacency information.*/
	LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,

	/*(3.2) If 6 vertices are given, points 0, 2, and 4 define the triangle. Points 1, 3, and 5 tell where adjacent triangles are*/
	TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,

	/*(3.2) If 8 vertices are given, points 0, 2, 4, 6 define the triangles. Points 1, 3, 5, 7 tell where adjacent triangles are*/
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
#endif // #ifdef YAGLPP_VERSION_3_2
};

/*GLAD primitive type enumerator*/
enum class PrimitiveType : GLenum
{
	/*The 1 byte indices*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*The 2 byte indices*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*The 4 byte indices*/
	UnsignedInt = GL_UNSIGNED_INT,
};

/*GLAD image pixel data format enumerator used by <ReadPixels>*/
enum class ReadFormat : GLenum
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
	/*(3.0) Each pixel is depth and stencil components*/
	DpthStencil = GL_DEPTH_STENCIL,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD image pixel data type enumerator used in <ReadPixels>*/
enum class ReadType : GLenum
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

/*GLAD read buffer unit enumerator used by <ReadBuffer>*/
enum class ReadUnit : GLenum
{
	/*Only the front left color buffer is written*/
	FrontLeft = GL_FRONT_LEFT,

	/*Only the front right color buffer is written*/
	FrontRight = GL_FRONT_RIGHT,

	/*Only the back left color buffer is written*/
	BackLeft = GL_BACK_LEFT,

	/*Only the back right color buffer is written*/
	BackRight = GL_BACK_RIGHT,

	/*Only the front left and front right color buffers are written. If there is no front right color buffer, only the front left color buffer is written*/
	Front = GL_FRONT,

	/*Only the back left and back right color buffers are written. If there is no back right color buffer, only the back left color buffer is written*/
	Back = GL_BACK,

	/*Only the front left and back left color buffers are written. If there is no back left color buffer, only the front left color buffer is written*/
	Left = GL_LEFT,

	/*Only the front right and back right color buffers are written. If there is no back right color buffer, only the front right color buffer is written*/
	Right = GL_RIGHT,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Framebuffer color attachment unit 0*/
	Color0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	Color1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	Color2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	Color3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	Color4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	Color5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	Color6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	Color7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	Color8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	Color9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	Color10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	Color11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	Color12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	Color13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	Color14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	Color15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	Color16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	Color17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	Color18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	Color19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	Color20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	Color21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	Color22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	Color23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	Color24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	Color25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	Color26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	Color27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	Color28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	Color29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	Color30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	Color31 = GL_COLOR_ATTACHMENT31,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD stencil operation mode enumerator*/
enum class StencilMode : GLenum
{
	/*Sets the stencil buffer value to 0*/
	Zero = GL_ZERO,

	/*Keeps the current value*/
	Keep = GL_KEEP,

	/*Sets the stencil buffer value to ref, as specified by <StencilFunc>*/
	Replace = GL_REPLACE,

	/*Increments the current stencil buffer value. Clamps to the maximum representable unsigned value*/
	Incr = GL_INCR,

	/*Decrements the current stencil buffer value. Clamps to 0*/
	Decr = GL_DECR,

	/*Bitwise inverts the current stencil buffer value*/
	Invert = GL_INVERT,

	/*Increments the current stencil buffer value. Wraps stencil buffer value to zero when incrementing the maximum representable unsigned value*/
	IncrWrap = GL_INCR_WRAP,

	/*Decrements the current stencil buffer value. Wraps stencil buffer value to the maximum representable unsigned value when decrementing a stencil buffer value of zero*/
	DecrWrap = GL_DECR_WRAP,
};

/*Constant expression <BufferBit> bitwise OR operator combining multiple flags into bitfield mask
@param BufferBit bitmask enumerator flag 1
@param BufferBit bitmask enumerator flag 2
@return Resulting bitmask BufferBit enumerator*/
constexpr BufferBit operator | (BufferBit flag1, BufferBit flag2)
{
	return (BufferBit)((GLbitfield)flag1 | (GLbitfield)flag2);
}

/*OpenGL auto-delete template unit compatible with all classes derived from <Objects>*/
template <typename T> class Auto : public T
{
public:
	using T::T;
	/*OpenGL auto-delete template unit implemented as class destructor*/
	~Auto()
	{
		T::auto_delete();
	}
};

/*Selects active texture unit by the index value ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1. All subsequetial calls to texture functions will be performad on that texture unit. Initial index is 0
@param Specifies the index of texture unit to make active*/
void ActiveTexture(TextureUnit index);

/*Sets the blend color
@param specify the red components of the blend color
@param specify the green components of the blend color
@param specify the blue components of the blend color
@param specify the alpha components of the blend color*/
inline void BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glBlendColor(red, green, blue, alpha);
}

/*Specifies the equation used for both the RGB blend equation and the Alpha blend equation
@param Specifies how source and destination colors are combined*/
void BlendEquation(BlendMode mode);

/*Set the RGB blend equation and the alpha blend equation separately
@param Specifies the RGB blend equation, how the red, green, and blue components of the source and destination colors are combined
@param Specifies the alpha blend equation, how the alpha component of the source and destination colors are combined*/
void BlendEquationSeparate(BlendMode modeRGB, BlendMode modeAlpha);

/*Defines the operation of blending for all draw buffers when it is enabled. The initial values are <One>, <Zero>
@param Specifies how the red, green, blue, and alpha source blending factors are computed
@param Specifies how the red, green, blue, and alpha destination blending factors are computed*/
void BlendFunc(BlendFactor sfactor, BlendFactor dfactor);

/*Defines the operation of blending for all draw buffers when it is enabled for RGB and alpha components separately. The initial values are <One>, <Zero>, <One>, <Zero>
@param Specifies how the red, green, and blue source blending factors are computed
@param Specifies how the red, green, and blue destination blending factors are computed
@param Specifies how the alpha source blending factors are computed
@param Specifies how the alpha destination blending factors are computed*/
void BlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);

/*Clear specified buffers to preset values. The bitmask flags can be combined with OR operator
@param The clear buffer mask enumerator*/
void Clear(BufferBit mask);

/*Specifies clear values for the color buffers. The initial values are 0.0, 0.0, 0.0, 0.0
@param Specifies the red value used when the color buffers are cleared
@param Specifies the green value used when the color buffers are cleared
@param Specifies the blue value used when the color buffers are cleared
@param Specifies the alpha value used when the color buffers are cleared*/
inline void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
}

/*Specifies the clear value for the depth buffer
@param Specifies the depth value used when the depth buffer is cleared*/
inline void ClearDepth(GLdouble depth)
{
	glClearDepth(depth);
}

/*Specifies the clear value for the stencil buffer. The initial value is 0
@param Specifies the index used when the stencil buffer is cleared*/
inline void ClearStencil(GLint stencil)
{
	glClearStencil(stencil);
}

/*(1) Enable and disable writing of color components to every draw buffers. The initial values are true, true, true, true
@param Specifies whether red component is to be written into the frame buffer
@param Specifies whether green component is be written into the frame buffer
@param Specifies whether blue component is to be written into the frame buffer
@param Specifies whether alpha  component is to be written into the frame buffer*/
inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
}

/*Specifies whether front- or back-facing facets can be culled. The initial value is <Back>
@param Specifies whether front- or back-facing facets are candidates for culling*/
void CullFace(FaceMode mode);

/*When depth testing enabled, compares each incoming pixel depth value with the depth value present in the depth buffer. In the following equations Di is the incoming depth value, and Ds is the stored depth value. Equal: passes if Di == Ds, Notequal: passes if Di != Ds, Less: passes if Di < Ds, Greater: passes if Di > Ds, Lequal: passes if Di <= Ds, Gequal: passes if Di >= Ds, Always: Always passes, Never: Never passes
@param Specifies the depth comparison function*/
void DepthFunc(CompareFunc func);

/*Enable or disable writing into the depth buffer. Initially, depth buffer writing is enabled
@param Specifies whether the depth buffer is enabled for writing*/
inline void DepthMask(GLboolean flag)
{
	glDepthMask(flag);
}

/*Specifies mapping of depth values from normalized device coordinates to window coordinates. The initial values are 0.0, 1.0
@param Specifies the mapping of the near clipping plane to window coordinates
@param Specifies the mapping of the far clipping plane to window coordinates*/
inline void DepthRange(GLdouble nearVal, GLdouble farVal)
{
	glDepthRange(nearVal, farVal);
}

/*Disable enabled blend server-side GL capability, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers*/
inline void DisableBlend()
{
	glDisable(GL_BLEND);
}

/*Disable enabled color logic operation server-side GL capability, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values*/
inline void DisableColorLogicOp()
{
	glDisable(GL_COLOR_LOGIC_OP);
}

/*Disable enabled cull face server-side GL capability, initially disabled. If enabled, cull polygons based on their winding in window coordinates*/
inline void DisableCullFace()
{
	glDisable(GL_CULL_FACE);
}

/*Disable enabled depth test server-side GL capability, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled*/
inline void DisableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

/*Disable enabled dither server-side GL capability, initially enabled. If enabled, dither color components or indices before they are written to the color buffer*/
inline void DisableDither()
{
	glDisable(GL_DITHER);
}

/*Disable enabled line smooth server-side GL capability, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines*/
inline void DisableLineSmooth()
{
	glDisable(GL_LINE_SMOOTH);
}

/*Disable enabled multisample server-side GL capability, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel*/
inline void DisableMultisample()
{
	glDisable(GL_MULTISAMPLE);
}

/*Disable enabled polygon offset fill server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void DisablePolygonOffsetFill()
{
	glDisable(GL_POLYGON_OFFSET_FILL);
}

/*Disable enabled polygon offset line server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void DisablePolygonOffsetLine()
{
	glDisable(GL_POLYGON_OFFSET_LINE);
}

/*Disable enabled polygon offset point server-side GL capability, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode*/
inline void DisablePolygonOffsetPoint()
{
	glDisable(GL_POLYGON_OFFSET_POINT);
}

/*Disable enabled polygon smooth server-side GL capability, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back*/
inline void DisablePolygonSmooth()
{
	glDisable(GL_POLYGON_SMOOTH);
}

/*Disable enabled sample alpha to coverage server-side GL capability, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value*/
inline void DisableSampleAlphaToCoverage()
{
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Disable enabled sample alpha to one server-side GL capability, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value*/
inline void DisableSampleAlphaToOne()
{
	glDisable(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Disable enabled sample coverage server-side GL capability, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value*/
inline void DisableSampleCoverage()
{
	glDisable(GL_SAMPLE_COVERAGE);
}

/*Disable enabled scissor test server-side GL capability, initially disabled. If enabled, discard fragments that are outside the scissor rectangle*/
inline void DisableScissorTest()
{
	glDisable(GL_SCISSOR_TEST);
}

/*Disable enabled stencil test server-side GL capability, initially disabled. If enabled, do stencil testing and update the stencil buffer*/
inline void DisableStencilTest()
{
	glDisable(GL_STENCIL_TEST);
}

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the starting index in the enabled arrays
@param Specifies the number of indices to be rendered*/
void DrawArrays(PrimitiveMode mode, GLint first, GLsizei count);

/*Specifies which color buffers of the default framebuffer are to be drawn into. The initial value is <Front> for single-buffered, and <Back> for double-buffered contexts
@param Specifies up to four color buffers to be drawn into*/
void DrawBuffer(DrawUnit buf);

/*Specifies a list of color buffers to be drawn into. The maximum number of draw buffers supported is <GetMaxDrawBuffers>
@param Specifies the number of draw buffers in the array
@param Pointer to an array of symbolic constants specifying the buffers into which fragment colors or data values will be written*/
void DrawBuffers(GLsizei n, _In_reads_(n) const DrawUnits* bufs);

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store*/
void DrawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices);

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the minimum array index contained in indices
@param Specifies the maximum array index contained in indices
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store*/
void DrawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices);

/*Enable blend server-side GL capability, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers*/
inline void EnableBlend()
{
	glEnable(GL_BLEND);
}

/*Enable color logic operation server-side GL capability, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values*/
inline void EnableColorLogicOp()
{
	glEnable(GL_COLOR_LOGIC_OP);
}

/*Enable cull face server-side GL capability, initially disabled. If enabled, cull polygons based on their winding in window coordinates*/
inline void EnableCullFace()
{
	glEnable(GL_CULL_FACE);
}

/*Enable depth test server-side GL capability, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled*/
inline void EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

/*Enable dither server-side GL capability, initially enabled. If enabled, dither color components or indices before they are written to the color buffer*/
inline void EnableDither()
{
	glEnable(GL_DITHER);
}

/*Enable line smooth server-side GL capability, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines*/
inline void EnableLineSmooth()
{
	glEnable(GL_LINE_SMOOTH);
}

/*Enable multisample server-side GL capability, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel*/
inline void EnableMultisample()
{
	glEnable(GL_MULTISAMPLE);
}

/*Enable polygon offset fill server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void EnablePolygonOffsetFill()
{
	glEnable(GL_POLYGON_OFFSET_FILL);
}

/*Enable polygon offset line server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void EnablePolygonOffsetLine()
{
	glEnable(GL_POLYGON_OFFSET_LINE);
}

/*Enable polygon offset point server-side GL capability, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode*/
inline void EnablePolygonOffsetPoint()
{
	glEnable(GL_POLYGON_OFFSET_POINT);
}

/*Enable polygon smooth server-side GL capability, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back*/
inline void EnablePolygonSmooth()
{
	glEnable(GL_POLYGON_SMOOTH);
}

/*Enable sample alpha to coverage server-side GL capability, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value*/
inline void EnableSampleAlphaToCoverage()
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Enable sample alpha to one server-side GL capability, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value*/
inline void EnableSampleAlphaToOne()
{
	glEnable(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Enable sample coverage server-side GL capability, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value*/
inline void EnableSampleCoverage()
{
	glEnable(GL_SAMPLE_COVERAGE);
}

/*Enable scissor test server-side GL capability, initially disabled. If enabled, discard fragments that are outside the scissor rectangle*/
inline void EnableScissorTest()
{
	glEnable(GL_SCISSOR_TEST);
}

/*Enable stencil test server-side GL capability, initially disabled. If enabled, do stencil testing and update the stencil buffer*/
inline void EnableStencilTest()
{
	glEnable(GL_STENCIL_TEST);
}

/*Block until all GL execution is complete*/
inline void Finish()
{
	glFinish();
}

/*Force execution of GL commands in finite time*/
inline void Flush()
{
	glFlush();
}

/*Define front- and back-facing polygons
@param Specifies the orientation of front-facing polygons. The initial value is <Ccw>*/
void FrontFace(FrontMode mode);

/*Returns the index value of an active multitexture unit ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1
@return The active multitexture unit index value*/
inline TextureUnit GetActiveTexture()
{
	return yaglpp_glad_integer(GL_ACTIVE_TEXTURE) - GL_TEXTURE0;
}

/*Gets a boolean value indicating whether blending is enabled. The initial value is false
@return True if blending is enabled, false otherwise*/
inline GLboolean GetBlend()
{
	return yaglpp_glad_boolean(GL_BLEND);
}

/*Gets four float values, the red, green, blue and alpha which are the components of the blend color. Initially the blend color is set to (0.0, 0.0, 0.0, 0.0)
@param [out] Pointer to store the four blend color values*/
inline void GetBlendColor(_Out_writes_(4) GLfloat* rgba)
{
	glGetFloatv(GL_BLEND_COLOR, rgba);
}

/*Gets previously set value indicating the alpha destination blend function scale factor. The initial value is <Zero>
@return The alpha destination blend function scale factor*/
inline BlendFactor GetBlendDstAlpha()
{
	return (BlendFactor)yaglpp_glad_integer(GL_BLEND_DST_ALPHA);
}

/*Gets previously set value indicating the RGB destination blend function scale factor. The initial value is <Zero>
@return The RGB destination blend function scale factor*/
inline BlendFactor GetBlendDstRGB()
{
	return (BlendFactor)yaglpp_glad_integer(GL_BLEND_DST_ALPHA);
}

/*Gets previously set value indicating the alpha blend equation mode
@return The alpha blend equation mode*/
inline BlendMode GetBlendEquationAlpha()
{
	return (BlendMode)yaglpp_glad_integer(GL_BLEND_EQUATION_ALPHA);
}

/*Gets previously set value indicating the RGB blend equation mode
@return The RGB blend equation mode*/
inline BlendMode GetBlendEquationRGB()
{
	return (BlendMode)yaglpp_glad_integer(GL_BLEND_EQUATION_RGB);
}

/*Gets previously set value indicating the alpha source blend function scale factor. The initial value is <One>
@return The alpha source blend function scale factor*/
inline BlendMode GetBlendSrcAlpha()
{
	return (BlendMode)yaglpp_glad_integer(GL_BLEND_SRC_ALPHA);
}

/*Gets previously set value indicating the RGB source blend function scale factor. The initial value is <One>
@return The RGB source blend function scale factor*/
inline BlendMode GetBlendSrcRGB()
{
	return (BlendMode)yaglpp_glad_integer(GL_BLEND_SRC_RGB);
}

/*(1) Gets four integer linearly mapped values used to clear the color buffers. The initial value is (0, 0, 0, 0)
@param [out] Pointer to store the four integer values: red, green, blue, and alpha*/
inline void GetColorClearValue(_Out_writes_(4) GLint* rgba)
{
	glGetIntegerv(GL_COLOR_CLEAR_VALUE, rgba);
}

/*(2) Gets four float values used to clear the color buffers. The initial value is (0.0, 0.0, 0.0, 0.0)
@param [out] Pointer to store the four float values: red, green, blue, and alpha*/
inline void GetColorClearValue(_Out_writes_(4) GLfloat* rgba)
{
	glGetFloatv(GL_COLOR_CLEAR_VALUE, rgba);
}

/*Gets a boolean value indicating whether a fragment's RGBA color values are merged into the framebuffer using a logical operation. The initial value is false
@return True if color logical operation is enabled, false otherwise*/
inline GLboolean GetColorLogicOp()
{
	return yaglpp_glad_boolean(GL_COLOR_LOGIC_OP);
}

/*Gets four boolean values: the red, green, blue, and alpha write enables for the color buffers. The initial value is (True, True, True, True)
@param [out] Pointer to store the four color writemask values*/
inline void GetColorWritemask(_Out_writes_(4) GLboolean* rgba)
{
	glGetBooleanv(GL_COMPRESSED_TEXTURE_FORMATS, rgba);
}

/*Returns a list of symbolic constants indicating which compressed texture format is available. It is being freed by the library at the de-initializtion and should not be discarded elsewhere. The list size is equal to the value returned by <GetNumCompressedTextureFormats>
@return The list of available compressed texture formats*/
_Ret_notnull_ GLenum* GetCompressedTextureFormats();

/*Gets a boolean value indicating whether polygon culling is enabled. The initial value is false
@return True if polygon culling is enabled, false otherwise*/
inline GLboolean GetCullFace()
{
	return yaglpp_glad_boolean(GL_CULL_FACE);
}

/*Gets previously set value indicating the mode of polygon culling. The initial value is <Back>
@return The mode of polygon culling value*/
inline FaceMode GetCullFaceMode()
{
	return (FaceMode)yaglpp_glad_integer(GL_CULL_FACE_MODE);
}

/*Gets the double value used to clear the depth buffer. The initial value is 1.0
@return The double depth clear value*/
inline GLdouble GetDepthClearValue()
{
	return yaglpp_glad_double(GL_DEPTH_CLEAR_VALUE);
}

/*Gets previously set value indicating the depth comparison function. The initial value is <Less>
@return The depth comparison function value*/
inline CompareFunc GetDepthFunc()
{
	return (CompareFunc)yaglpp_glad_integer(GL_DEPTH_FUNC);
}

/*Gets two float values: the near and far mapping limits for the depth buffer. The initial value is (0.0, 1.0)
@param [out] Pointer to store the two mapping limits*/
inline void GetDepthRange(_Out_writes_(2) GLdouble* mapping)
{
	glGetDoublev(GL_DEPTH_RANGE, mapping);
}

/*Gets the boolean value indicating whether depth testing of fragments is enabled. The initial value is false
@return True if depth testing is enabled, false otherwise*/
inline GLboolean GetDepthTest()
{
	return yaglpp_glad_boolean(GL_DEPTH_TEST);
}

/*Gets the boolean value indicating if the depth buffer is enabled for writing. The initial value is true
@return True if depth buffer is enabled for writing, false otherwise*/
inline GLboolean GetDepthWritemask()
{
	return yaglpp_glad_boolean(GL_DEPTH_WRITEMASK);
}

/*Gets a boolean value indicating whether dithering of fragment colors and indices is enabled. The initial value is false
@return The dither value*/
inline GLboolean GetDither()
{
	return yaglpp_glad_boolean(GL_DITHER);
}

/*Gets a boolean value indicating whether double buffering is supported
@return True if double buffering is supported, false otherwise*/
inline GLboolean GetDoublebuffer()
{
	return yaglpp_glad_boolean(GL_DOUBLEBUFFER);
}

/*Gets a <DrawUnit> enumerator, previously set by <DrawBuffer>, indicating which buffers are being drawn to. The initial value is <Back> if there are back buffers, otherwise it is <Front>
@return The draw buffer unit enumerator*/
inline DrawUnit GetDrawBuffer()
{
	return (DrawUnit)yaglpp_glad_integer(GL_DRAW_BUFFER);
}

/*Gets a <DrawUnits> enumerator, previously set by <DrawBuffers>, indicating which buffers are being drawn to by the corresponding output color. The initial value of buffer 0 is <Back> if there are back buffers, otherwise it is <Front>. The initial values of draw buffers for all other output colors is <None>. The draw buffer index must be between 0 and a value returned by <GetMaxDrawBuffers> minus 1
@param The draw buffer index
@return The draw buffer unit enumerator*/
DrawUnits GetDrawBuffers(BufferUnit index);


/*Gets the <FrontMode> enumerator, previously set by <FrontFace>, indicating the orientation of front-facing polygons. The initial value is <Ccw>
@return The orientation of front-facing polygons mode*/
inline FrontMode GetFrontFace()
{
	return (FrontMode)yaglpp_glad_integer(GL_FRONT_FACE);
}

/*Gets a symbolic constant indicating the mode of the derivative accuracy hint for fragment shaders. The initial value is <DontCare>
@return The derivative accuracy hint*/
inline BehaviorHint GetFragmentShaderDerivativeHint()
{
	return (BehaviorHint)yaglpp_glad_integer(GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
}

/*Gets a boolean value indicating whether antialiasing of lines is enabled. The initial value is false
@return True if line smoothing is enabled, false otherwise*/
inline GLboolean GetLineSmooth()
{
	return yaglpp_glad_boolean(GL_LINE_SMOOTH);
}

/*Gets a symbolic constant indicating the mode of the line antialiasing hint. The initial value is <DontCare>
@return The line smoothing hint value*/
inline BehaviorHint GetLineSmoothHint()
{
	return (BehaviorHint)yaglpp_glad_integer(GL_LINE_SMOOTH_HINT);
}

/*Gets the line width as specified with <LineWidth>. The initial value is 1.0
@return The line width value*/
inline GLfloat GetLineWidth()
{
	return yaglpp_glad_float(GL_LINE_WIDTH);
}

/*Gets a symbolic constant indicating the selected logic operation mode
@return The logic operation mode value*/
inline LogicMode GetLogicOpMode()
{
	return (LogicMode)yaglpp_glad_integer(GL_LOGIC_OP_MODE);
}

/*Gets a rough estimate of the largest 3D texture that the GL can handle. The value must be at least 64
@return The maximum 3D texture size*/
GLuint GetMax3DTextureSize();

/*Gets a maximum width value supported for aliased (non-smooth) line
@return The maximum aliased line width value*/
GLfloat GetMaxAliasedLineWidth();

/*Gets the maximum supported texture image units that can be used to access texture maps from the vertex shader and the fragment processor combined. The value must be at least 48
@return The maximum supported texture image units*/
GLuint GetMaxCombinedTextureImageUnits();

/*Gets a rough estimate of the largest cube-map texture that the GL can handle. The value must be at least 1024
@return The maximum cube map texture size*/
GLuint GetMaxCubeMapTextureSize();

/*Gets the maximum number of simultaneous outputs that may be written in a fragment shader. The value must be at least 8
@return The maximum number of draw buffers*/
GLuint GetMaxDrawBuffers();

/*Gets the recommended maximum number of vertex array indices for <DrawRangeElements>
@return The maximum elements indices value*/
GLuint GetMaxElementsIndices();

/*Gets the recommended maximum number of vertex array vertices for <DrawRangeElements>
@return The maximum elements vertices value*/
GLuint GetMaxElementsVertices();

/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a fragment shader. The value must be at least 1024
@return The maximum fragment uniform components*/
GLuint GetMaxFragmentUniformComponents();

/*Gets the largest supported size for antialiased points. The largest size must be at least 1.0
@return The largest supported point size value*/
GLfloat GetMaxPointSize();

/*Gets a maximum width value of supported smooth (antialiased) lines
@return The maximum smooth line width value*/
GLfloat GetMaxSmoothLineWidth();

/*Gets the maximum supported texture image units that can be used to access texture maps from the fragment shader. The value must be at least 16
@return The maximum supported texture image units*/
GLuint GetMaxTextureImageUnits();

/*Gets absolute value of the texture level-of-detail bias. The value must be at least 2.0
@return The maximum texture level-of-detail bias*/
GLfloat GetMaxTextureLodBias();

/*Gets the value that gives a rough estimate of the largest 1D texture that the GL can handle. The value must be at least 1024
@return The maximum texture size*/
GLuint GetMaxTextureSize();

/*Gets the maximum number of interpolators available for processing varying variables used by vertex and fragment shaders. This value represents the number of individual floating-point values that can be interpolated; varying variables declared as vectors, matrices, and arrays will all consume multiple interpolators. The value must be at least 32
@return The maximum number of varying interpolators*/
GLuint GetMaxVaryingFloats();

/*Returns the maximum number of 4-component generic vertex attributes accessible to a vertex shader. The value must be at least 16
@return The maximum vertex attributes*/
GLuint GetMaxVertexAttribs();

/*Returns the maximum supported texture image units that can be used to access texture maps from the vertex shader. The value must be at least 16
@return The maximum supported vertex texture image units*/
GLuint GetMaxVertexTextureImageUnits();

/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a vertex shader. The value must be at least 1024
@return The maximum vertex uniform components*/
GLuint GetMaxVertexUniformComponents();

/*Gets the two values, the maximum supported width and height of the viewport
@param [out] Pointer to store the two maximum viewport dimentions*/
inline void GetMaxViewportDims(_Out_writes_(2) GLsizei* dims)
{
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dims);
}

/*Gets the maximum supported height of the viewport
@return The maximum viewport height*/
GLuint GetMaxViewportHeight();

/*Gets the maximum supported width of the viewport
@return The maximum viewport width*/
GLuint GetMaxViewportWidth();

/*Gets a minimum width value supported for aliased (non-smooth) line
@return The minimum aliased line width value*/
GLfloat GetMinAliasedLineWidth();

/*Gets the smallest supported size for antialiased points. The smallest size must be at most 1.0
@return The smallest supported point size value*/
GLfloat GetMinPointSize();

/*Gets a minimum width value of supported smooth (antialiased) lines
@return The minimum smooth line width value*/
GLfloat GetMinSmoothLineWidth();

/*Gets an integer value indicating the number of available compressed texture formats. The minimum value is 4
@return The number of available compressed texture formats*/
GLuint GetNumCompressedTextureFormats();

/*Gets the byte alignment used for writing pixel data to memory. The initial value is <Four>
@return The pack alignment pixel storage mode*/
inline PixelAlignment GetPackAlignment()
{
	return (PixelAlignment)yaglpp_glad_integer(GL_PACK_ALIGNMENT);
}

/*Gets the image height used for writing pixel data to memory. The initial value is 0
@return The pack image height pixel storage mode*/
inline GLuint GetPackImageHeight()
{
	return yaglpp_glad_integer(GL_PACK_IMAGE_HEIGHT);
}

/*Gets a boolean value indicating whether single-bit pixels being written to memory are written first to the least significant bit of each unsigned byte. The initial value is false
@return The pack LSB first pixel storage mode flag*/
inline GLboolean GetPackLsbFirst()
{
	return yaglpp_glad_boolean(GL_PACK_LSB_FIRST);
}

/*Gets the row length used for writing pixel data to memory. The initial value is 0
@return The pack row length pixel storage mode*/
inline GLuint GetPackRowLength()
{
	return yaglpp_glad_integer(GL_PACK_ROW_LENGTH);
}

/*Gets the number of pixel images skipped before the first pixel is written into memory. The initial value is 0
@return The pack skip images pixel storage mode*/
inline GLuint GetPackSkipImages()
{
	return yaglpp_glad_integer(GL_PACK_SKIP_IMAGES);
}

/*Gets the number of pixel locations skipped before the first pixel is written into memory. The initial value is 0
@return The pack skip pixels pixel storage mode*/
inline GLuint GetPackSkipPixels()
{
	return yaglpp_glad_integer(GL_PACK_SKIP_PIXELS);
}

/*Gets the number of rows of pixel locations skipped before the first pixel is written into memory. The initial value is 0
@return The pack skip rows pixel storage mode*/
inline GLuint GetPackSkipRows()
{
	return yaglpp_glad_integer(GL_PACK_SKIP_ROWS);
}

/*Gets a boolean value indicating whether the bytes of two-byte and four-byte pixel indices and components are swapped before being written to memory. The initial value is false
@return The pack swap bytes pixel storage mode flag*/
inline GLboolean GetPackSwapBytes()
{
	return yaglpp_glad_boolean(GL_PACK_LSB_FIRST);
}

/*Gets a floating-point value that specifies the threshold value to which point sizes are clamped if they exceed the specified value. The default value is 1.0
@return The point size threshold*/
inline GLfloat GetPointFadeThresholdSize()
{
	return yaglpp_glad_float(GL_POINT_FADE_THRESHOLD_SIZE);
}

/*Gets the point size value as specified by <PointSize>. The initial value is 1.0
@return The point size value*/
inline GLfloat GetPointSize()
{
	return yaglpp_glad_float(GL_POINT_SIZE);
}

/*Gets the size difference between adjacent supported sizes for antialiased points
@return The point size granularity*/
inline GLfloat GetPointSizeGranularity()
{
	return yaglpp_glad_float(GL_POINT_SIZE_GRANULARITY);
}

/*Gets two values, the smallest and largest supported sizes for antialiased points. The smallest size must be at most 1.0, and the largest size must be at least 1.0
@param [out] Pointer to store the point size range values*/
inline void GetPointSizeRange(_Out_writes_(2) GLfloat* range)
{
	glGetFloatv(GL_POINT_SIZE_RANGE, range);
}

/*Gets the point sprite texture coordinate origin enumerator. The default value is <UpperLeft>
@return The point sprite texture coordinate origin*/
inline PointOrigin GetPointSpriteCoordOrigin()
{
	return (PointOrigin)yaglpp_glad_integer(GL_POINT_SPRITE_COORD_ORIGIN);
}

/*Gets the scaling factor used to determine the variable offset that is added to the depth value of each fragment generated when a polygon is rasterized. The initial value is 0.0
@return The polygon offset scaling factor*/
inline GLfloat GetPolygonOffsetFactor()
{
	return yaglpp_glad_float(GL_POLYGON_OFFSET_FACTOR);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in fill mode. The initial value is false
@return True if polygon fill offset is enabled*/
inline GLboolean GetPolygonOffsetFill()
{
	return  yaglpp_glad_boolean(GL_POLYGON_OFFSET_FILL);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in line mode. The initial value is false
@return True if polygon line offset is enabled*/
inline GLboolean GetPolygonOffsetLine()
{
	return yaglpp_glad_boolean(GL_POLYGON_OFFSET_LINE);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in point mode. The initial value is false
@return True if polygon point offset is enabled*/
inline GLboolean GetPolygonOffsetPoint()
{
	return yaglpp_glad_boolean(GL_POLYGON_OFFSET_POINT);
}

/*Gets the value, previously set by <PolygonOffset>, which is multiplied by an implementation-specific value and then added to the depth value of each fragment generated when a polygon is rasterized. The initial value is 0.0
@return The polygon offset units value*/
inline GLfloat GetPolygonOffsetUnits()
{
	return yaglpp_glad_float(GL_POLYGON_OFFSET_UNITS);
}

/*Gets a boolean value indicating whether antialiasing of polygons is enabled. The initial value is false
@return True if polygon point smoothing is enabled*/
inline GLboolean GetPolygonSmooth()
{
	return yaglpp_glad_boolean(GL_POLYGON_SMOOTH);
}

/*Gets a symbolic constant indicating the mode of the polygon antialiasing hint. The initial value is <DontCare>
@return The desired behavior hint*/
inline BehaviorHint GetPolygonSmoothHint()
{
	return (BehaviorHint)yaglpp_glad_integer(GL_POLYGON_SMOOTH_HINT);
}

/*Gets a symbolic constant set by <ReadBuffer> indicating which color buffer is selected for reading. The initial value is <Back> if there is a back buffer, <Front> otherwise
@return The selected color buffer mode*/
inline ReadUnit GetReadBuffer()
{
	return (ReadUnit)yaglpp_glad_integer(GL_READ_BUFFER);
}

/*Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release
@return The string value of the renderer*/
inline const GLubyte* GetRenderer()
{
	return glGetString(GL_RENDERER);
}

/*Gets an integer value indicating the number of sample buffers associated with the framebuffer
@return The number of sample buffers*/
inline GLuint GetSampleBuffers()
{
	return yaglpp_glad_integer(GL_SAMPLE_BUFFERS);
}

/*Gets a boolean value indicating the temporary coverage value invertion flag set by <SampleCoverage>
@return True if the temporary coverage value should be inverted, false otherwise*/
inline GLboolean GetSampleCoverageInvert()
{
	return yaglpp_glad_boolean(GL_SAMPLE_COVERAGE_INVERT);
}

/*Gets a positive floating-point value indicating the current sample coverage value set by <SampleCoverage>. The initial value is 1.0
@return The sample coverage value*/
inline GLfloat GetSampleCoverageValue()
{
	return yaglpp_glad_float(GL_SAMPLE_COVERAGE_VALUE);
}

/*Gets an integer value indicating the coverage mask size used by <SampleCoverage>
@return The coverage mask size*/
inline GLuint GetSamples()
{
	return yaglpp_glad_integer(GL_SAMPLES);
}

/*Gets four values: the x and y window coordinates of the scissor box, followed by its width and height. Initially the x and y window coordinates are both 0 and the width and height are set to the size of the window
@param [out] The scissor box position and size*/
inline void GetScissorBox(_Out_writes_(4) GLint* box)
{
	glGetIntegerv(GL_SCISSOR_BOX, box);
}

/*Gets a boolean value indicating whether scissoring is enabled. The initial value is false
@return True if the scissoring is enabled, false otherwise*/
inline GLboolean GetScissorTest()
{
	return yaglpp_glad_boolean(GL_SCISSOR_TEST);
}

/*Returns a version or release number for the shading language
@return The string value of the shading language version*/
inline const GLubyte* GetShadingLanguageVersion()
{
	return glGetString(GL_SHADING_LANGUAGE_VERSION);
}

/*Gets the level of quantization applied to smooth line width parameters
@return The level of quantization for line width parameters*/
inline GLfloat GetSmoothLineWidthGranularity()
{
	return yaglpp_glad_float(GL_SMOOTH_LINE_WIDTH_GRANULARITY);
}

/*Gets a pair of values indicating the range of widths supported for smooth (antialiased) lines
@param [out] Two values indicating the range of widths*/
inline void GetSmoothLineWidthRange(_Out_writes_(2) GLfloat* range)
{
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test fails. The initial value is <Keep>
@return The stencil back fail operation mode*/
inline StencilMode GetStencilBackFail()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_BACK_FAIL);
}

/*Gets symbolic constant indicating what function is used for back-facing polygons to compare the stencil reference value with the stencil buffer value. The initial value is <Always>
@return The stencil back function set by <StencilFunc>*/
inline CompareFunc GetStencilBackFunc()
{
	return (CompareFunc)yaglpp_glad_integer(GL_STENCIL_BACK_FUNC);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test passes, but the depth test fails. The initial value is <Keep>
@return The stencil back pass depth fail operation mode*/
inline StencilMode GetStencilBackPassDepthFail()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test passes and the depth test passes. The initial value is <Keep>
@return The stencil back pass depth pass operation mode*/
inline StencilMode GetStencilBackPassDepthPass()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_BACK_PASS_DEPTH_PASS);
}

/*Gets the reference value that is compared with the contents of the stencil buffer for back-facing polygons. The initial value is 0
@return The stencil back reference value set by <StencilFunc>*/
inline GLint GetStencilBackRef()
{
	return yaglpp_glad_integer(GL_STENCIL_BACK_REF);
}

/*Gets the mask that is used for back-facing polygons to mask both the stencil reference value and the stencil buffer value before they are compared. The initial value is all 1's
@return The stencil back mask value set by <StencilFunc>*/
inline GLbitfield GetStencilBackValueMask()
{
	return yaglpp_glad_integer(GL_STENCIL_BACK_VALUE_MASK);
}

/*Gets the mask that controls writing of the stencil bitplanes for back-facing polygons. The initial value is all 1's
@return The stencil back writing mask value set by <StencilMask>*/
inline GLbitfield GetStencilBackWritemask()
{
	return yaglpp_glad_integer(GL_STENCIL_BACK_WRITEMASK);
}

/*Gets the index to which the stencil bitplanes are cleared. The initial value is 0
@return The default stencil clear value*/
inline GLint GetStencilClearValue()
{
	return yaglpp_glad_integer(GL_STENCIL_CLEAR_VALUE);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test fails. The initial value is <Keep>
@return The stencil fail operation mode*/
inline StencilMode GetStencilFail()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_FAIL);
}

/*Gets a symbolic constant indicating what function is used to compare the stencil reference value with the stencil buffer value. The initial value is <Always>
@return The stencil function set by <StencilFunc>*/
inline CompareFunc GetStencilFunc()
{
	return (CompareFunc)yaglpp_glad_integer(GL_STENCIL_FUNC);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test passes and the depth test passes. The initial value is <Keep>
@return The stencil pass depth pass operation mode*/
inline StencilMode GetStencilPassDepthPass()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_PASS_DEPTH_PASS);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test passes, but the depth test fails. The initial value is <Keep>
@return The stencil pass depth fail operation mode*/
inline StencilMode GetStencilPassDepthFail()
{
	return (StencilMode)yaglpp_glad_integer(GL_STENCIL_PASS_DEPTH_FAIL);
}

/*Gets the reference value that is compared with the contents of the stencil buffer. The initial value is 0
@return The stencil reference value set by <StencilFunc>*/
inline GLint GetStencilRef()
{
	return yaglpp_glad_integer(GL_STENCIL_REF);
}

/*Gets a boolean value indicating whether stencil testing of fragments is enabled. The initial value is false
@return True if the stencil testing is enabled, false otherwise*/
inline GLboolean GetStencilTest()
{
	return yaglpp_glad_boolean(GL_STENCIL_TEST);
}

/*Gets the mask that is used to mask both the stencil reference value and the stencil buffer value before they are compared. The initial value is all 1's
@return The stencil back mask value set by <StencilFunc>*/
inline GLbitfield GetStencilValueMask()
{
	return yaglpp_glad_integer(GL_STENCIL_VALUE_MASK);
}

/*Gets the mask that controls writing of the stencil bitplanes. The initial value is all 1's
@return The stencil writing mask value set by <StencilMask>*/
inline GLbitfield GetStencilWritemask()
{
	return yaglpp_glad_integer(GL_STENCIL_WRITEMASK);
}

/*Gets a boolean value indicating whether stereo buffers (left and right) are supported
@return True if stereo buffers are supported, false otherwise*/
GLboolean GetStereo();

/*Gets an estimate of the number of bits of subpixel resolution that are used to position rasterized geometry in window coordinates. The value must be at least 4
@return The subpixel bits value*/
GLuint GetSubpixelBits();

/*Gets a value indicating the mode of the texture compression hint. The initial value is <DontCare>
@return The desired behavior hint*/
inline BehaviorHint GetTextureCompressionHint()
{
	return (BehaviorHint)yaglpp_glad_integer(GL_TEXTURE_COMPRESSION_HINT);
}

/*Gets the byte alignment used for reading pixel data from memory. The initial value is <Four>
@return The unpack alignment pixel storage mode*/
inline PixelAlignment GetUnpackAlignment()
{
	return (PixelAlignment)yaglpp_glad_integer(GL_UNPACK_ALIGNMENT);
}

/*Gets the image height used for reading pixel data from memory. The initial value is 0
@return The unpack image height pixel storage mode*/
inline GLuint GetUnpackImageHeight()
{
	return yaglpp_glad_integer(GL_UNPACK_IMAGE_HEIGHT);
}

/*Gets a boolean value indicating whether single-bit pixels being read from memory are read first from the least significant bit of each unsigned byte. The initial value is false
@return The unpack LSB first pixel storage mode flag*/
inline GLboolean GetUnpackLsbFirst()
{
	return yaglpp_glad_boolean(GL_UNPACK_LSB_FIRST);
}

/*Gets the row length used for reading pixel data from memory. The initial value is 0
@return The unpack row length pixel storage mode*/
inline GLuint GetUnpackRowLength()
{
	return yaglpp_glad_integer(GL_UNPACK_ROW_LENGTH);
}

/*Gets the number of pixel images skipped before the first pixel is read from memory. The initial value is 0
@return The unpack skip images pixel storage mode*/
inline GLuint GetUnpackSkipImages()
{
	return yaglpp_glad_integer(GL_UNPACK_SKIP_IMAGES);
}

/*Gets the number of pixel locations skipped before the first pixel is read from memory. The initial value is 0
@return The unpack skip pixels pixel storage mode*/
inline GLuint GetUnpackSkipPixels()
{
	return yaglpp_glad_integer(GL_UNPACK_SKIP_PIXELS);
}

/*Gets the number of rows of pixel locations skipped before the first pixel is read from memory. The initial value is 0
@return The unpack skip rows pixel storage mode*/
inline GLuint GetUnpackSkipRows()
{
	return yaglpp_glad_integer(GL_UNPACK_SKIP_ROWS);
}

/*Gets a boolean value indicating whether the bytes of two-byte and four-byte pixel indices and components are swapped after being read from memory. The initial value is false
@return The unpack swap bytes pixel storage mode flag*/
inline GLboolean GetUnpackSwapBytes()
{
	return yaglpp_glad_boolean(GL_UNPACK_SWAP_BYTES);
}

/*Returns the company responsible for this GL implementation. This name does not change from release to release
@return The string value of the vendor*/
inline const GLubyte* GetVendor()
{
	return glGetString(GL_VENDOR);
}

/*Returns a version or release number
@return The string value of the version*/
inline const GLubyte* GetVersion()
{
	return glGetString(GL_VERSION);
}

/*Gets the four viewport values: the x and y window coordinates of the viewport, followed by its width and height. Initial values are: 0, 0, width and height of the window rendered by GL
@param [out] Pointer to store the four viewport values*/
inline void GetViewport(_Out_writes_(4) GLint* viewport)
{
	glGetIntegerv(GL_VIEWPORT, viewport);
}

/*Checks if blend server-side GL capability is enabled, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers
@return True if blend GL capability is enabled, false otherwise*/
inline GLboolean IsBlend()
{
	return glIsEnabled(GL_BLEND);
}

/*Checks if color logic operation server-side GL capability is enabled, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values
@return True if color logic operation GL capability is enabled, false otherwise*/
inline GLboolean IsColorLogicOp()
{
	return glIsEnabled(GL_COLOR_LOGIC_OP);
}

/*Checks if cull face server-side GL capability is enabled, initially disabled. If enabled, cull polygons based on their winding in window coordinates
@return True if cull face GL capability is enabled, false otherwise*/
inline GLboolean IsCullFace()
{
	return glIsEnabled(GL_CULL_FACE);
}

/*Checks if depth test server-side GL capability is enabled, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled
@return True if depth test GL capability is enabled, false otherwise*/
inline GLboolean IsDepthTest()
{
	return glIsEnabled(GL_DEPTH_TEST);
}

/*Checks if dither server-side GL capability is enabled, initially enabled. If enabled, dither color components or indices before they are written to the color buffer
@return True if dither GL capability is enabled, false otherwise*/
inline GLboolean IsDither()
{
	return glIsEnabled(GL_DITHER);
}

/*Checks if line smooth server-side GL capability is enabled, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines
@return True if line smooth GL capability is enabled, false otherwise*/
inline GLboolean IsLineSmooth()
{
	return glIsEnabled(GL_LINE_SMOOTH);
}

/*Checks if multisample server-side GL capability is enabled, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel
@return True if multisample GL capability is enabled, false otherwise*/
inline GLboolean IsMultisample()
{
	return glIsEnabled(GL_MULTISAMPLE);
}

/*Checks if polygon offset fill server-side GL capability is enabled, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed
@return True if polygon offset fill GL capability is enabled, false otherwise*/
inline GLboolean IsPolygonOffsetFill()
{
	return glIsEnabled(GL_POLYGON_OFFSET_FILL);
}

/*Checks if polygon offset line server-side GL capability is enabled, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed
@return True if polygon offset line GL capability is enabled, false otherwise*/
inline GLboolean IsPolygonOffsetLine()
{
	return glIsEnabled(GL_POLYGON_OFFSET_LINE);
}

/*Checks if polygon offset point server-side GL capability is enabled, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode
@return True if polygon offset point GL capability is enabled, false otherwise*/
inline GLboolean IsPolygonOffsetPoint()
{
	return glIsEnabled(GL_POLYGON_OFFSET_POINT);
}

/*Checks if polygon smooth server-side GL capability is enabled, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back
@return True if polygon smooth GL capability is enabled, false otherwise*/
inline GLboolean IsPolygonSmooth()
{
	return glIsEnabled(GL_POLYGON_SMOOTH);
}

/*Checks if sample alpha to coverage server-side GL capability is enabled, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value
@return True if sample alpha to coverage GL capability is enabled, false otherwise*/
inline GLboolean IsSampleAlphaToCoverage()
{
	return glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Checks if sample alpha to one server-side GL capability is enabled, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value
@return True if sample alpha to one GL capability is enabled, false otherwise*/
inline GLboolean IsSampleAlphaToOne()
{
	return glIsEnabled(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Checks if sample coverage server-side GL capability is enabled, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value
@return True if sample coverage GL capability is enabled, false otherwise*/
inline GLboolean IsSampleCoverage()
{
	return glIsEnabled(GL_SAMPLE_COVERAGE);
}

/*Checks if scissor test server-side GL capability is enabled, initially disabled. If enabled, discard fragments that are outside the scissor rectangle
@return True if scissor test GL capability is enabled, false otherwise*/
inline GLboolean IsScissorTest()
{
	return glIsEnabled(GL_SCISSOR_TEST);
}

/*Checks if stencil test server-side GL capability is enabled, initially disabled. If enabled, do stencil testing and update the stencil buffer
@return True if stencil test GL capability is enabled, false otherwise*/
inline GLboolean IsStencilTest()
{
	return glIsEnabled(GL_STENCIL_TEST);
}

/*Specifies the width of rasterized lines. The initial value is 1.0
@param Specifies the width of rasterized lines*/
void LineWidth(GLfloat width);

/*Specifies a logical pixel operation for rendering. The initial value is <Copy>
@param Specifies a symbolic constant that selects a logical operation>*/
void LogicOp(LogicMode opcode);

/*Render multiple sets of primitives from array data
@param Specifies what kind of primitives to render
@param [in] Pointer to an array of starting indices in the enabled arrays
@param [in] Pointer to an array of the number of indices to be rendered
@param Specifies the size of the first and count arrays*/
void MultiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount);

/*Render multiple sets of primitives by specifying indices of array data elements
@param Specifies what kind of primitives to render
@param [in] Pointer to an array of the elements counts
@param Specifies the type of the values in indices
@param [in] Pointer to an array of the byte offsets into the element array index buffer object's data store
@param Specifies the size of the count and indices arrays*/
void MultiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount);

/*Specifies the diameter of rasterized points. The initial value is 1.0
@param Specifies the diameter of rasterized points*/
void PointSize(GLfloat size);

/*Select a polygon rasterization mode. The initial value is <Fill>
@param Specifies how polygons will be rasterized*/
void PolygonMode(DrawMode mode);

/*Set the scale and units used to calculate depth values. The initial values are 0.0, 0.0
@param Specifies a scale factor that is used to create a variable depth offset for each polygon
@param Is multiplied by an implementation-specific value to create a constant depth offset*/
inline void PolygonOffset(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
}

/*Select a color buffer source for pixels
@param Specifies a color buffer*/
void ReadBuffer(ReadUnit mode);

/*(1) Reads a block of pixels from the frame buffer into client memory data store. Unbinds pixel back buffer if bound
@param Specifies the window x coordinate of the first pixel that is read from the frame buffer
@param Specifies the window y coordinate of the first pixel that is read from the frame buffer
@param Specifies the width of the pixel rectangle
@param Specifies the height of the pixel rectangle
@param Specifies the format of the pixel data
@param Specifies the data type of the pixel data
@param [out] Specifies the pointer to the pixel data
@param Specifies the number of commponents in returning pixel array, default RGBA*/
void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, _Out_ void* data);

/*Specifies multisample coverage parameters. The initial values are 1.0, false
@param Specifies a single floating-point sample coverage value
@param True if the coverage masks should be inverted*/
inline void SampleCoverage(GLfloat value, GLboolean invert)
{
	glSampleCoverage(value, invert);
}

/*Define the scissor box. When a GL context is first attached to a window, width and height are set to the dimensions of that window. Initial x, y coordinates values are 0, 0
@param Specifies the lower left corner x coordinate of the scissor box
@param Specifies the lower left corner y coordinate of the scissor box
@param Specifies the width of the scissor box
@param Specifies the height of the scissor box*/
void Scissor(GLint x, GLint y, GLsizei width, GLsizei height);

/*Set the accuracy of the derivative calculation for the GL shading language fragment processing built-in functions: dFdx, dFdy, and fwidth
@param Specifies a symbolic constant indicating the desired behavior*/
inline void SetFragmentShaderDerivativeHint(BehaviorHint hint)
{
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, (GLenum)hint);
}

/*Indicates the sampling quality of antialiased lines. If a larger filter function is applied, hinting <Nicest> can result in more pixel fragments being generated during rasterization
@param Specifies a symbolic constant indicating the desired behavior*/
inline void SetLineSmoothHint(BehaviorHint hint)
{
	glHint(GL_LINE_SMOOTH_HINT, (GLenum)hint);
}

/*Set pack alignment pixel storage mode
@param Specifies the alignment requirements for the start of each pixel row in memory*/
inline void SetPackAlignment(PixelAlignment swap)
{
	yaglpp_glad_pixel(GL_PACK_ALIGNMENT, (GLint)swap);
}

/*Set pack image height pixel storage mode
@param If greater than 0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void SetPackImageHeight(GLint height)
{
	yaglpp_glad_pixel(GL_PACK_IMAGE_HEIGHT, height);
}

/*Set pack LSB first pixel storage mode
@param If true, bits are ordered within a byte from least significant to most significant. Otherwise, the first bit in each byte is the most significant one*/
inline void SetPackLsbFirst(GLboolean swap)
{
	yaglpp_glad_pixel(GL_PACK_LSB_FIRST, swap);
}

/*Set pack row length pixel storage mode
@param If greater than 0, defines the number of pixels in a row*/
inline void SetPackRowLength(GLint length)
{
	yaglpp_glad_pixel(GL_PACK_ROW_LENGTH, length);
}

/*Set pack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void SetPackSkipImages(GLint skip)
{
	yaglpp_glad_pixel(GL_PACK_SKIP_IMAGES, skip);
}

/*Set pack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void SetPackSkipPixels(GLint skip)
{
	yaglpp_glad_pixel(GL_PACK_SKIP_PIXELS, skip);
}

/*Set pack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void SetPackSkipRows(GLint skip)
{
	yaglpp_glad_pixel(GL_PACK_SKIP_ROWS, skip);
}

/*Set pack swap bytes pixel storage mode
@param If true, byte ordering for multibyte color components, depth components, or stencil indices is reversed*/
inline void SetPackSwapBytes(GLboolean swap)
{
	yaglpp_glad_pixel(GL_PACK_SWAP_BYTES, swap);
}

/*Set the threshold value to which point sizes are clamped if they exceed the specified value. The default value is 1.0
@param The point threshold size*/
void SetPointFadeThresholdSize(GLfloat size);

/*Set the point sprite texture coordinate origin. The default value is <UpperLeft>
@param The point sprite texture coordinate origin*/
void SetPointSpriteCoordOrigin(PointOrigin origin);

/*Indicates the sampling quality of antialiased polygons. Hinting <Nicest> can result in more pixel fragments being generated during rasterization, if a larger filter function is applied
@param Specifies a symbolic constant indicating the desired behavior*/
inline void SetPolygonSmoothHint(BehaviorHint hint)
{
	glHint(GL_POLYGON_SMOOTH_HINT, (GLenum)hint);
}

/*Indicates the quality and performance of the compressing texture images. Hinting <Fastest> indicates that texture images should be compressed as quickly as possible, while <Nicest> indicates that texture images should be compressed with as little image quality loss as possible
@param Specifies a symbolic constant indicating the desired behavior*/
inline void SetTextureCompressionHint(BehaviorHint hint)
{
	glHint(GL_TEXTURE_COMPRESSION_HINT, (GLenum)hint);
}

/*Set unpack alignment pixel storage mode
@param Specifies the alignment requirements for the start of each pixel row in memory*/
inline void SetUnpackAlignment(PixelAlignment swap)
{
	yaglpp_glad_pixel(GL_UNPACK_ALIGNMENT, (GLint)swap);
}

/*Set unpack image height pixel storage mode
@param If greater than 0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void SetUnpackImageHeight(GLint height)
{
	yaglpp_glad_pixel(GL_UNPACK_IMAGE_HEIGHT, height);
}

/*Set unpack LSB first pixel storage mode
@param If true, bits are ordered within a byte from least significant to most significant. Otherwise, the first bit in each byte is the most significant one*/
inline void SetUnpackLsbFirst(GLboolean swap)
{
	yaglpp_glad_pixel(GL_UNPACK_LSB_FIRST, swap);
}

/*Set unpack row length pixel storage mode
@param If greater than 0, defines the number of pixels in a row*/
inline void SetUnpackRowLength(GLint length)
{
	yaglpp_glad_pixel(GL_UNPACK_ROW_LENGTH, length);
}

/*Set unpack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void SetUnpackSkipImages(GLint skip)
{
	yaglpp_glad_pixel(GL_UNPACK_SKIP_IMAGES, skip);
}

/*Set unpack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void SetUnpackSkipPixels(GLint skip)
{
	yaglpp_glad_pixel(GL_UNPACK_SKIP_PIXELS, skip);
}

/*Set unpack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void SetUnpackSkipRows(GLint skip)
{
	yaglpp_glad_pixel(GL_UNPACK_SKIP_ROWS, skip);
}

/*Set unpack swap bytes pixel storage mode
@param If true, byte ordering for multibyte color components, depth components, or stencil indices is reversed*/
inline void SetUnpackSwapBytes(GLboolean swap)
{
	yaglpp_glad_pixel(GL_UNPACK_SWAP_BYTES, swap);
}

/*Set front and back function and reference value for stencil testing. The initial values are <Always>, 0, all 1's
@param Specifies the test function
@param Specifies the reference value for the stencil test
@param Specifies a mask that is AND'ed with both values when the test is done*/
void StencilFunc(CompareFunc func, GLint ref, GLuint mask);

/*Set front and/or back function and reference value for stencil testing. The initial values after face parameter are <Always>, 0, all 1's
@param Specifies whether front and/or back stencil state is updated
@param Specifies the test function
@param Specifies the reference value for the stencil test
@param Specifies a mask that is AND'ed with both values when the test is done*/
void StencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask);

/*Control the front and back writing of individual bits in the stencil planes. Initially, the mask is all 1's
@param Specifies a bit mask to enable and disable writing of individual bits in the stencil planes*/
inline void StencilMask(GLuint mask)
{
	glStencilMask(mask);
}

/*Control the front and/or back writing of individual bits in the stencil planes. Initially, the mask is all 1's
@param Specifies whether the front and/or back stencil writemask is updated
@param Specifies a bit mask to enable and disable writing of individual bits in the stencil planes*/
void StencilMaskSeparate(FaceMode face, GLuint mask);

/*Set front and back stencil test actions. The initial values are <Keep>, <Keep>, <Keep>
@param Specifies the action to take when the stencil test fails
@param Specifies the action when the stencil test passes, but the depth test fails
@param Specifies the action when both tests pass, or when the stencil test passes and either depth buffer is missing or disabled*/
void StencilOp(StencilMode sfail, StencilMode dpfail, StencilMode dppass);

/*Set front and/or back stencil test actions. The initial values after face parameter are <Keep>, <Keep>, <Keep>
@param Specifies whether front and/or back stencil state is updated
@param Specifies the action to take when the stencil test fails
@param Specifies the action when the stencil test passes, but the depth test fails
@param Specifies the action when both tests pass, or when the stencil test passes and either depth buffer is missing or disabled*/
void StencilOpSeparate(FaceMode face, StencilMode sfail, StencilMode dpfail, StencilMode dppass);

/*Set the viewport
@param Specifies the the x coordinate of a lower left corner of the viewport rectangle, in pixels
@param Specifies the the y coordinate of a lower left corner of the viewport rectangle, in pixels
@param Specifies the width of the viewport
@param Specifies the height of the viewport*/
void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);

#ifdef YAGLPP_IMPLEMENTATION
static GLint yaglpp_max_viewport_dims[2];
static GLfloat yaglpp_point_size_range[2];
static GLfloat yaglpp_smooth_line_width_range[2];
static GLfloat yaglpp_aliased_line_width_range[2];
static GLenum* yaglpp_compressed_texture_formats;
void yaglpp_glad_free()
{
	YAGLPP_FREE(yaglpp_compressed_texture_formats);
}

void yaglpp_glad_load(void* proc)
{
	int r = (proc) ? gladLoadGLLoader((GLADloadproc)proc) : gladLoadGL();

	// FAILED TO LOAD GLAD
	YAGLPP_RUNTIME(!r, "YAGL++: failed to load GLAD");

	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, yaglpp_max_viewport_dims);
	glGetFloatv(GL_POINT_SIZE_RANGE, yaglpp_point_size_range);
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, yaglpp_smooth_line_width_range);
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, yaglpp_aliased_line_width_range);
	yaglpp_compressed_texture_formats = YAGLPP_MALLOC(GLenum, GetNumCompressedTextureFormats());
	glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, (GLint*)yaglpp_compressed_texture_formats);
}

_Ret_notnull_ GLenum* GetCompressedTextureFormats()
{
	return yaglpp_compressed_texture_formats;
}

GLuint GetMax3DTextureSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_3D_TEXTURE_SIZE);
	return n;
}

GLfloat GetMaxAliasedLineWidth()
{
	return yaglpp_aliased_line_width_range[1];
}

GLuint GetMaxCombinedTextureImageUnits()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	return n;
}

GLuint GetMaxCubeMapTextureSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
	return n;
}

GLuint GetMaxDrawBuffers()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_DRAW_BUFFERS);
	return n;
}

GLuint GetMaxElementsIndices()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_ELEMENTS_INDICES);
	return n;
}

GLuint GetMaxElementsVertices()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_ELEMENTS_VERTICES);
	return n;
}

GLuint GetMaxFragmentUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
	return n;
}

GLfloat GetMaxPointSize()
{
	return yaglpp_point_size_range[1];
}

GLfloat GetMaxSmoothLineWidth()
{
	return yaglpp_smooth_line_width_range[1];
}

GLuint GetMaxTextureImageUnits()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_TEXTURE_IMAGE_UNITS);
	return n;
}

GLuint GetMaxViewportHeight()
{
	return yaglpp_max_viewport_dims[1];
}

GLuint GetMaxViewportWidth()
{
	return yaglpp_max_viewport_dims[0];
}

GLfloat GetMinAliasedLineWidth()
{
	return yaglpp_aliased_line_width_range[0];
}

GLfloat GetMinPointSize()
{
	return yaglpp_point_size_range[0];
}

GLfloat GetMinSmoothLineWidth()
{
	return yaglpp_smooth_line_width_range[0];
}

GLfloat GetMaxTextureLodBias()
{
	static GLfloat f = yaglpp_glad_float(GL_MAX_TEXTURE_LOD_BIAS);
	return f;
}

GLuint GetMaxTextureSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_TEXTURE_SIZE);
	return n;
}

GLuint GetMaxVaryingFloats()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VARYING_FLOATS);
	return n;
}

GLuint GetMaxVertexAttribs()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VERTEX_ATTRIBS);
	return n;
}

GLuint GetMaxVertexTextureImageUnits()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	return n;
}

GLuint GetMaxVertexUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
	return n;
}

GLuint GetNumCompressedTextureFormats()
{
	static GLuint n = yaglpp_glad_integer(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
	return n;
}

GLboolean GetStereo()
{
	static GLboolean b = yaglpp_glad_boolean(GL_MAX_3D_TEXTURE_SIZE);
	return b;
}

GLuint GetSubpixelBits()
{
	static GLuint n = yaglpp_glad_integer(GL_SUBPIXEL_BITS);
	return n;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLboolean yaglpp_glad_error()
{
	GLenum eNumber;
	GLboolean bAssert = GL_TRUE;
	while ((eNumber = glGetError()) != GL_NO_ERROR)
	{
		const char* pString;
		switch (eNumber)
		{
		case GL_INVALID_ENUM:
			pString = "invalid enum";
			break;

		case GL_INVALID_VALUE:
			pString = "invalid value";
			break;

		case GL_INVALID_OPERATION:
			pString = "invalid operation";
			break;

		case GL_OUT_OF_MEMORY:
			pString = "out of memory";
			break;

#ifdef YAGLPP_VERSION_3_0
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			pString = "invalid framebuffer operation";
			break;
#endif // #ifdef YAGLPP_VERSION_3_0

		default:
			pString = "undefined error code";
			break;
		}

		bAssert = GL_FALSE;
		std::cout << "YAGL++ GLAD error " << eNumber << ": " << pString << std::endl;
	}
	return bAssert;
}

void yaglpp_glad_pixel(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
	YAGLPP_GLAD_ERROR;
}

void ActiveTexture(TextureUnit index)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetMaxCombinedTextureImageUnits());

	glActiveTexture(GL_TEXTURE0 + (GLenum)index);
}

void BlendEquation(BlendMode mode)
{
	glBlendEquation((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void BlendEquationSeparate(BlendMode modeRGB, BlendMode modeAlpha)
{
	glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
	YAGLPP_GLAD_ERROR;
}

void BlendFunc(BlendFactor sfactor, BlendFactor dfactor)
{
	glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
	YAGLPP_GLAD_ERROR;
}

void BlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
{
	glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
	YAGLPP_GLAD_ERROR;
}

void Clear(BufferBit mask)
{
	glClear((GLbitfield)mask);
	YAGLPP_GLAD_ERROR;
}

void CullFace(FaceMode mode)
{
	glCullFace((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void DepthFunc(CompareFunc func)
{
	glDepthFunc((GLenum)func);
	YAGLPP_GLAD_ERROR;
}

void DrawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
	glDrawArrays((GLenum)mode, first, count);
	YAGLPP_GLAD_ERROR;
}

void DrawBuffer(DrawUnit buf)
{
	glDrawBuffer((GLenum)buf);
	YAGLPP_GLAD_ERROR;
}

void DrawBuffers(GLsizei n, _In_reads_(n) const DrawUnits* bufs)
{
	glDrawBuffers(n, (GLenum*)bufs);
	YAGLPP_GLAD_ERROR;
}

void DrawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
	YAGLPP_GLAD_ERROR;
}

void DrawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
	YAGLPP_GLAD_ERROR;
}

void FrontFace(FrontMode mode)
{
	glFrontFace((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

DrawUnits GetDrawBuffers(BufferUnit index)
{
	static GLuint num = GetMaxDrawBuffers();

	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < num);

	return (DrawUnits)yaglpp_glad_integer(GL_DRAW_BUFFER0 + (GLenum)index);
}

void LineWidth(GLfloat width)
{
	// INVALID WIDTH VALUE
	YAGLPP_ASSERT(width > 0.0);

	glLineWidth(width);
}

void LogicOp(LogicMode opcode)
{
	glLogicOp((GLenum)opcode);
	YAGLPP_GLAD_ERROR;
}

void MultiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
	glMultiDrawArrays((GLenum)mode, first, count, drawcount);
	YAGLPP_GLAD_ERROR;
}

void MultiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
	glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
	YAGLPP_GLAD_ERROR;
}

void PointSize(GLfloat size)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(size > 0.0);

	glPointSize(size);
}

void PolygonMode(DrawMode mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void ReadBuffer(ReadUnit mode)
{
	glReadBuffer((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, _Out_ void* data)
{
#ifdef YAGLPP_VERSION_2_1
	// PIXEL PACK BUFFER TARGET MUST BE UNBOUND
	YAGLPP_ASSERT(yaglpp_glad_integer(GL_PIXEL_PACK_BUFFER) == 0);
#endif // #ifdef YAGLPP_VERSION_2_1

	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, data);
	YAGLPP_GLAD_ERROR;
}

void Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	// INVALID WIDTH / HEIGHT VALUE
	YAGLPP_ASSERT((width >= 0) && (height >= 0));

	glScissor(x, y, width, height);
}

void SetPointFadeThresholdSize(GLfloat size)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(size >= 0.0);

	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
}

void SetPointSpriteCoordOrigin(PointOrigin origin)
{
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
	YAGLPP_GLAD_ERROR;
}

void StencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFunc((GLenum)func, ref, mask);
	YAGLPP_GLAD_ERROR;
}

void StencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
	YAGLPP_GLAD_ERROR;
}

void StencilMaskSeparate(FaceMode face, GLuint mask)
{
	glStencilMaskSeparate((GLenum)face, mask);
	YAGLPP_GLAD_ERROR;
}

void StencilOp(StencilMode sfail, StencilMode dpfail, StencilMode dppass)
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
	YAGLPP_GLAD_ERROR;
}

void StencilOpSeparate(FaceMode face, StencilMode sfail, StencilMode dpfail, StencilMode dppass)
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
	YAGLPP_GLAD_ERROR;
}

void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	// INVALID WIDTH / HEIGHT VALUE
	YAGLPP_ASSERT((width >= 0) && (height >= 0));

	glViewport(x, y, width, height);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void yaglpp_glad_pixel(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
}

inline void ActiveTexture(TextureUnit index)
{
	glActiveTexture(GL_TEXTURE0 + (GLenum)index);
}

inline void BlendEquation(BlendMode mode)
{
	glBlendEquation((GLenum)mode);
}

inline void BlendEquationSeparate(BlendMode modeRGB, BlendMode modeAlpha)
{
	glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
}

inline void BlendFunc(BlendFactor sfactor, BlendFactor dfactor)
{
	glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
}

inline void BlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
{
	glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
}

inline void Clear(BufferBit mask)
{
	glClear((GLbitfield)mask);
}

inline void CullFace(FaceMode mode)
{
	glCullFace((GLenum)mode);
}

inline void DepthFunc(CompareFunc func)
{
	glDepthFunc((GLenum)func);
}

inline void DrawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
	glDrawArrays((GLenum)mode, first, count);
}

inline void DrawBuffer(DrawUnit buf)
{
	glDrawBuffer((GLenum)buf);
}

inline void DrawBuffers(GLsizei n, _In_reads_(n) const DrawUnits* bufs)
{
	glDrawBuffers(n, (GLenum*)bufs);
}

inline void DrawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
}

inline void DrawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
}

inline void FrontFace(FrontMode mode)
{
	glFrontFace((GLenum)mode);
}

inline DrawUnits GetDrawBuffers(BufferUnit index)
{
	(DrawUnits)yaglpp_glad_integer(GL_DRAW_BUFFER0 + (GLenum)index);
}

inline void LineWidth(GLfloat width)
{
	glLineWidth(width);
}

inline void LogicOp(LogicMode opcode)
{
	glLogicOp((GLenum)opcode);
}

inline void MultiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
	glMultiDrawArrays((GLenum)mode, first, count, drawcount);
}

inline void MultiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
	glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
}

inline void PointSize(GLfloat size)
{
	glPointSize(size);
}

inline void PolygonMode(DrawMode mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
}

inline void ReadBuffer(ReadUnit mode)
{
	glReadBuffer((GLenum)mode);
}

inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, _Out_ void* data)
{
	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, data);
}

inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
}

inline void SetPointFadeThresholdSize(GLfloat size)
{
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
}

inline void SetPointSpriteCoordOrigin(PointOrigin origin)
{
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
}

inline void StencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFunc((GLenum)func, ref, mask);
}

inline void StencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
}

inline void StencilMaskSeparate(FaceMode face, GLuint mask)
{
	glStencilMaskSeparate((GLenum)face, mask);
}

inline void StencilOp(StencilMode sfail, StencilMode dpfail, StencilMode dppass)
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

inline void StencilOpSeparate(FaceMode face, StencilMode sfail, StencilMode dpfail, StencilMode dppass)
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#ifdef YAGLPP_VERSION_2_1
class PixelPackBuffer;
class PixelUnpackBuffer;

/*(2) (2.1) Read a block of pixels from the frame buffer into pixel pack buffer object's data store
@param Specifies the window x coordinate of the first pixel that is read from the frame buffer
@param Specifies the window y coordinate of the first pixel that is read from the frame buffer
@param Specifies the width of the pixel rectangle
@param Specifies the height of the pixel rectangle
@param Specifies the format of the pixel data
@param Specifies the data type of the pixel data
@param Specifies the byte offset into the PBO object's data store*/
void ReadPixels(PixelPackBuffer& ppb, GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, GLintptr offset);
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
class DrawFramebuffer;
class Framebuffer;
class Framebuffers;
class PrimitivesGenerated;
class ReadFramebuffer;
class Renderbuffer;
class Texture1DArray;
class Texture2DArray;
class TransformFeedbackBuffer;
class TransformFeedbackPrimitivesWritten;
class VertexArray;

/*(3.0) GLAD clip geometry unit index ranging from 0 to the value returned by <GetMaxClipDistances> minus 1*/
typedef unsigned int ClipDistance;

/*(3.0) GLAD color attachment unit index ranging from 0 to the value returned by <GetMaxColorAttachments> minus 1*/
typedef unsigned int ColorAttachment;

/*(3.0) GLAD color number index ranging from 0 to the value returned by <GetMaxDrawBuffers> minus 1*/
typedef unsigned int ColorNumber;

/*(3.0) GLAD read clamp color value enumerator used in <ClampColor>*/
enum class ClampRead : GLenum
{
	/*(3.0) Read color clamping is enabled*/
	True = GL_TRUE,

	/*(3.0) Read color clamping is disabled*/
	False = GL_FALSE,

	/*(3.0) Read color clamping is enabled only if the selected read buffer has fixed point components and disabled otherwise*/
	FixedOnly = GL_FIXED_ONLY,
};

/*(3.0) GLAD compare mode enumerator*/
enum class CompareMode : GLenum
{
	/*(3.0) Specifies that the red channel should be assigned the appropriate value from the currently bound depth texture*/
	None = GL_NONE,

	/*(3.0) Specifies that the interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture*/
	CompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE,
};

/*(3.0) GLAD transform feedback buffer mode enumerator*/
enum class TransformFeedbackBufferMode : GLenum
{
	/*(3.0) Interleaved attributes value. Writes all attributes to a single buffer object*/
	Interleaved = GL_INTERLEAVED_ATTRIBS,

	/*(3.0) Separate attributes value. Writes attributes to multiple buffer objects or at different offsets into a single buffer*/
	Separate = GL_SEPARATE_ATTRIBS,
};

/*(3.0) GLAD transform feedback primitive mode enumerator*/
enum class TransformFeedbackPrimitiveMode : GLenum
{
	/*(3.0) Transform feedback operation with allowed primitives of type <Points>*/
	Points = GL_POINTS,

	/*(3.0) Transform feedback operation with allowed primitives of type <Lines>, <LineLoop>, <LineStrip>, <LinesAdjacency>, <LineStripAdjacency>*/
	Lines = GL_LINES,

	/*(3.0) Transform feedback operation with allowed primitives of type <Triangles>, <TriangleStrip>, <TriangleFan>, <TrianglesAdjacency>, <TriangleStripAdjacency>*/
	Triangles = GL_TRIANGLES,
};

/*(3.0) Constant expression converting color attachment index value into <DrawUnit> enumerator
@param The index of color attachment unit between 0 and value returned by <GetMaxColorAttachments> minus 1
@return Color attachment unit value within <DrawUnit> enumerator*/
constexpr DrawUnit IndexToDrawUnit(ColorAttachment index)
{
	return (DrawUnit)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Constant expression converting color attachment unit index value into <DrawUnits> enumerator
@param The index of color attachment unit between 0 and value returned by <GetMaxColorAttachments> minus 1
@return Color attachment unit value within <DrawUnits> enumerator*/
constexpr DrawUnits IndexToDrawUnits(ColorAttachment index)
{
	return (DrawUnits)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Constant expression converting color attachment unit index value into <ReadUnit> enumerator
@param The index of color attachment unit between 0 and value returned by <GetMaxColorAttachments> minus 1
@return Color attachment unit value within <ReadUnit> enumerator*/
constexpr ReadUnit IndexToReadUnit(ColorAttachment index)
{
	return (ReadUnit)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Constant expression checking if the returned color number index is valid
@param The index of color number ranging from 0 to the value returned by <GetMaxDrawBuffers> minus 1
@return True if the color number index is valid*/
constexpr GLboolean IsColorNumber(ColorNumber index)
{
	return index != 0xFFFFFFFF;
}

/*(3.0) Start transform feedback operation, must be paired with called before <EndTransformFeedback>
@param Specifies the output type of the primitives that will be recorded into the buffer objects*/
void BeginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode);

/*(3.0) Specifies whether data read via <ReadPixels> should be clamped
@param Specifies whether to apply color clamping*/
void ClampColor(ClampRead clamp);

/*(3.0) (1) Clear the color of individual buffer of a framebuffer to four-element vector specifying the R, G, B and A color to clear that draw buffer to. The buffer unit index value must be 0 to the value returned by <GetMaxDrawBuffers> minus 1
@param The draw buffer unit index
@param Pointer to a four-element RGBA integer values*/
void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLint* color);

/*(3.0) (2) Clear the color of individual buffer of a framebuffer to four-element vector specifying the R, G, B and A color to clear that draw buffer to. The buffer unit index value must be 0 to the value returned by <GetMaxDrawBuffers> minus 1
@param The draw buffer unit index
@param Pointer to a four-element RGBA unsigned integer values*/
void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLuint* color);

/*(3.0) (3) Clear the color of individual buffer of a framebuffer to four-element vector specifying the R, G, B and A color to clear that draw buffer to. The buffer unit index value must be 0 to the value returned by <GetMaxDrawBuffers> minus 1
@param The draw buffer unit index
@param Pointer to a four-element RGBA float values*/
void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLfloat* color);

/*(3.0) Clear the depth buffer to a float value
@param The value to clear the depth buffer to*/
void ClearDepthBuffer(GLfloat depth);

/*(3.0) Clear the depth and stencil buffers simultaneously to a float and integer values
@param The value to clear the depth buffer to
@param The value to clear the stencil buffer to*/
void ClearDepthStencilBuffer(GLfloat depth, GLint stencil);

/*(3.0) Clear the stencil buffer to an integer value
@param The value to clear the stencil buffer to*/
void ClearStencilBuffer(GLint stencil);

/*(3.0) (2) Enable and disable writing of color components to specified draw buffer. The buffer unit index value must be 0 to the value returned by <GetMaxDrawBuffers> minus 1. The initial values after index parameter are true, true, true, true
@param The draw buffer unit index
@param Specifies whether red component is to be written into the frame buffer
@param Specifies whether green component is be written into the frame buffer
@param Specifies whether blue component is to be written into the frame buffer
@param Specifies whether alpha  component is to be written into the frame buffer*/
void ColorMask(BufferUnit index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

/*(3.0) Disable enabled clip geometry against user-defined half space server-side GL capability, initially disabled. The clip geometry unit index is between 0 and the value returned by <GetMaxClipDistances> minus 1
@param The index of clip geometry unit*/
void DisableClipDistance(ClipDistance index);

/*(3.0) Disable enabled framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
inline void DisableFramebufferSrgb()
{
	glDisable(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Disable enabled rasterizer discard server-side GL capability, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization*/
inline void DisableRasterizerDiscard()
{
	glDisable(GL_RASTERIZER_DISCARD);
}

/*(3.0) Enable clip geometry against user-defined half space server-side GL capability, initially disabled. The clip geometry unit index is between 0 and the value returned by <GetMaxClipDistances> minus 1
@param The index of clip geometry unit*/
void EnableClipDistance(ClipDistance index);

/*(3.0) Enable framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
inline void EnableFramebufferSrgb()
{
	glEnable(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Enable rasterizer discard server-side GL capability, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization*/
inline void EnableRasterizerDiscard()
{
	glEnable(GL_RASTERIZER_DISCARD);
}

/*(3.0) End conditional rendering started using occlusion query object*/
void EndConditionalRender();

/*(3.0) End transform feedback operation, must be paired with called after <BeginTransformFeedback>*/
void EndTransformFeedback();

/*(3.0) Gets previously set color clamping value, whether data read via <ReadPixels> should be clamped
@return Whether to apply color clamping*/
inline ClampRead GetClampReadColor()
{
	return (ClampRead)yaglpp_glad_integer(GL_CLAMP_READ_COLOR);
}

/*(3.0) Returns the flags with which the context was created
@param The context flags*/
inline GLbitfield GetContextFlags()
{
	return yaglpp_glad_integer(GL_CONTEXT_FLAGS);
}

/*(3.0) Returns the extension string supported by the implementation at index
@param The index of the supported extension
@return The extension string*/
const GLubyte* GetExtensions(GLuint index);

/*(3.0) Gets the major version number of the OpenGL API supported by the current context
@return The OpenGL major version number*/
GLuint GetMajorVersion();

/*(3.0) Gets the maximum number of layers allowed in an array texture, and must be at least 256
@return The maximum number of layers in the array texture*/
GLuint GetMaxArrayTextureLayers();

/*(3.0) Gets the maximum number of application-defined clipping distances. The value must be at least 8
@return The maximum clip distances number*/
GLuint GetMaxClipDistances();

/*(3.0) Gets the maximum number of the color attachment units of the framebuffer. The value must be at least 8
@return The maximum of the color attachments*/
GLuint GetMaxColorAttachments();

/*(3.0) Gets the maximum texel offset allowed in a texture lookup, which must be at least 7
@return The maximum texel offset*/
GLuint GetMaxProgramTexelOffset();

/*(3.0) Gets the maximum supported size for render-buffers
@return The maximum renderbuffer size*/
GLuint GetMaxRenderbufferSize();

/*(3.0) Retrieves the maximum number of samples supported by the current OpenGL context for multisampling
#return The maximum of supported samples*/
GLuint GetMaxSamples();

/*(3.0) Gets the number components for varying variables, which must be at least 60
@param The maximum components for varying variables*/
GLuint GetMaxVaryingComponents();

/*(3.0) Gets the minor version number of the OpenGL API supported by the current context
@return The minor version number*/
GLuint GetMinorVersion();

/*(3.0) Get the minimum texel offset allowed in a texture lookup, which must be at most -8
@return The minimum program texel offset*/
GLuint GetMinProgramTexelOffset();

/*(3.0) Gets the number of extensions supported by the GL implementation for the current context
@return The number of extensions*/
GLuint GetNumExtensions();

/*(3.0) Gets the size of the binding range for each transform feedback attribute stream
@return The size of the binding range*/
inline GLint GetTransformFeedbackBufferSize()
{
	return yaglpp_glad_integer(GL_TRANSFORM_FEEDBACK_BUFFER_SIZE);
}

/*(3.0) Gets the start offset of the binding range for each transform feedback attribute stream
@return The start offset of the binding range*/
inline GLint GetTransformFeedbackBufferStart()
{
	return yaglpp_glad_integer(GL_TRANSFORM_FEEDBACK_BUFFER_START);
}

/*(3.0) Checks if clip geometry against user-defined half space server-side GL capability is enabled, initially disabled. The clip geometry unit index is between 0 and the value returned by <GetMaxClipDistances> minus 1
@param The index of clip geometry unit
@return True if the clip geometry unit is enabled*/
GLboolean IsClipDistance(ClipDistance index);

/*(3.0) Performs a binary scan of present extensions against the search string
@param The extension search string
@return The index of the supported extension if present, -1 otherwise*/
GLint IsExtension(_In_z_ const char* search);

/*(3.0) Check if framebuffer SRGB server-side GL capability is enabled, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending
@return True if framebuffer SRGB GL capability is enabled, false otherwise*/
inline GLboolean IsFramebufferSrgb()
{
	return glIsEnabled(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Checks if rasterizer discard server-side GL capability is enabled, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization
@return True if rasterizer discard GL capability is enabled, false otherwise*/
inline GLboolean IsRasterizerDiscard()
{
	return glIsEnabled(GL_RASTERIZER_DISCARD);
}
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_IMPLEMENTATION)
GLuint GetMajorVersion()
{
	static GLuint n = yaglpp_glad_integer(GL_MAJOR_VERSION);
	return n;
}

GLuint GetMaxArrayTextureLayers()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_ARRAY_TEXTURE_LAYERS);
	return n;
}

GLuint GetMaxClipDistances()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_CLIP_DISTANCES);
	return n;
}

GLuint GetMaxColorAttachments()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COLOR_ATTACHMENTS);
	return n;
}

GLuint GetMaxProgramTexelOffset()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_PROGRAM_TEXEL_OFFSET);
	return n;
}

GLuint GetMaxRenderbufferSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_RENDERBUFFER_SIZE);
	return n;
}

GLuint GetMaxSamples()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_SAMPLES);
	return n;
}

GLuint GetMaxVaryingComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VARYING_COMPONENTS);
	return n;
}

GLuint GetMinorVersion()
{
	static GLuint n = yaglpp_glad_integer(GL_MINOR_VERSION);
	return n;
}

GLuint GetMinProgramTexelOffset()
{
	static GLuint n = yaglpp_glad_integer(GL_MIN_PROGRAM_TEXEL_OFFSET);
	return n;
}

GLuint GetNumExtensions()
{
	static GLuint n = yaglpp_glad_integer(GL_NUM_EXTENSIONS);
	return n;
}

GLint IsExtension(_In_z_ const char* search)
{
	// INVALID STRING VALUE
	YAGLPP_ASSERT(search != nullptr);

	GLint low = 0, high = GetNumExtensions() - 1, mid, cmp;
	while (low <= high)
	{
		mid = (low + high) / 2;
		cmp = std::strncmp((const char*)glGetStringi(GL_EXTENSIONS, mid), search, FILENAME_MAX);
		if (cmp < 0)
		{
			low = mid + 1;
		}
		else if (cmp > 0)
		{
			high = mid - 1;
		}
		else return mid;
	}
	return -1;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void BeginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
	glBeginTransformFeedback((GLenum)primitiveMode);
	YAGLPP_GLAD_ERROR;
}

void ClampColor(ClampRead clamp)
{
	glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
	YAGLPP_GLAD_ERROR;
}

void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLint* color)
{
	glClearBufferiv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLuint* color)
{
	glClearBufferuiv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLfloat* color)
{
	glClearBufferfv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void ClearDepthBuffer(GLfloat depth)
{
	glClearBufferfv(GL_DEPTH, 0, &depth);
	YAGLPP_GLAD_ERROR;
}

void ClearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
	glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
	YAGLPP_GLAD_ERROR;
}

void ClearStencilBuffer(GLint stencil)
{
	glClearBufferiv(GL_STENCIL, 0, &stencil);
	YAGLPP_GLAD_ERROR;
}

void ColorMask(BufferUnit index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetMaxDrawBuffers());

	glColorMaski((GLint)index, red, green, blue, alpha);
}

void DisableClipDistance(ClipDistance index)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetMaxClipDistances());

	glDisable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

void EnableClipDistance(ClipDistance index)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetMaxClipDistances());

	glEnable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

void EndConditionalRender()
{
	glEndConditionalRender();
	YAGLPP_GLAD_ERROR;
}

void EndTransformFeedback()
{
	glEndTransformFeedback();
	YAGLPP_GLAD_ERROR;
}

const GLubyte* GetExtensions(GLuint index)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetNumExtensions());

	return glGetStringi(GL_EXTENSIONS, index);
}

GLboolean IsClipDistance(ClipDistance index)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetMaxClipDistances());

	return glIsEnabled(GL_CLIP_DISTANCE0 + (GLenum)index);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void BeginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
	glBeginTransformFeedback((GLenum)primitiveMode);
}

inline void ClampColor(ClampRead clamp)
{
	glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
}

inline void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLint* color)
{
	glClearBufferiv(GL_COLOR, (GLint)index, color);
}

inline void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLuint* color)
{
	glClearBufferuiv(GL_COLOR, (GLint)index, color);
}

inline void ClearColorBuffer(BufferUnit index, _In_reads_(4) const GLfloat* color)
{
	glClearBufferfv(GL_COLOR, (GLint)index, color);
}

inline void ClearDepthBuffer(GLfloat depth)
{
	glClearBufferfv(GL_DEPTH, 0, &depth);
}

inline void ClearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
	glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
}

inline void ClearStencilBuffer(GLint stencil)
{
	glClearBufferiv(GL_STENCIL, 0, &stencil);
}

inline void ColorMask(BufferUnit index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMaski((GLint)index, red, green, blue, alpha);
}

inline void DisableClipDistance(ClipDistance index)
{
	glDisable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

inline void EnableClipDistance(ClipDistance index)
{
	glEnable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

inline void EndConditionalRender()
{
	glEndConditionalRender();
}

inline void EndTransformFeedback()
{
	glEndTransformFeedback();
}

inline const GLubyte* GetExtensions(GLuint index)
{
	return glGetStringi(GL_EXTENSIONS, index);
}

inline GLboolean IsClipDistance(ClipDistance index)
{
	return glIsEnabled(GL_CLIP_DISTANCE0 + (GLenum)index);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_1
class BufferTexture;
class TextureBuffer;
class TextureRectangle;
class UniformBlock;
class UniformBuffer;

/*(3.1) Disable enabled primitive restart server-side GL capability, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index*/
inline void DisablePrimitiveRestart()
{
	glDisable(GL_PRIMITIVE_RESTART);
}

/*(3.1) Draw multiple instances of a range of elements
@param Specifies what kind of primitives to render
@param Specifies the starting index in the enabled arrays
@param Specifies the number of indices to be rendered
@param Specifies the number of instances of the specified range of indices to be rendered*/
void DrawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount);

/*(3.1) Draw multiple instances of a set of elements
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies the number of instances of the specified range of indices to be rendered*/
void DrawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount);

/*(3.1) Enable primitive restart server-side GL capability, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index*/
inline void EnablePrimitiveRestart()
{
	glEnable(GL_PRIMITIVE_RESTART);
}

/*(3.1) Gets the number of words for fragment shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined fragment uniform components*/
GLuint GetMaxCombinedFragmentUniformComponents();

/*(3.1) Gets the maximum number of uniform blocks per program. The value must be at least 70
@return The maximum combined uniform blocks*/
GLuint GetMaxCombinedUniformBlocks();

/*(3.1) Gets the number of words for vertex shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined vertex uniform components*/
GLuint GetMaxCombinedVertexUniformComponents();

/*(3.1) Gets the maximum number of uniform blocks per fragment shader. The value must be at least 12
@return The maximum fragment uniform components*/
GLuint GetMaxFragmentUniformBlocks();

/*(3.1) Get a rough estimate of the largest rectangular texture that the GL can handle. The value must be at least 1024. Use <GetProxyWidth> or <GetProxyHeight> to determine if a texture is too large
@return The maximum rectangle texture size*/
GLuint GetMaxRectangleTextureSize();

/*(3.1) The maximum number of texels allowed in the texel array of a texture buffer object. Value must be at least 65536
@param The maximum allowed number of texels*/
GLuint GetMaxTextureBufferSize();

/*(3.1) Gets the maximum size in basic machine units of a uniform block. The value must be at least 16384
@return The maximum uniform block size*/
GLuint GetMaxUniformBlockSize();

/*(3.1) Gets the maximum number of uniform buffer binding points on the context, must be at least 36
@return The maximum uniform buffer bindings*/
GLuint GetMaxUniformBufferBindings();

/*(3.1) Gets the maximum number of uniform blocks per vertex shader. The value must be at least 12
@return The maximum vertex uniform components*/
GLuint GetMaxVertexUniformBlocks();

/*(3.1) Gets the current primitive restart index. The initial value is 0
@return The primitive restart index*/
inline GLuint GetPrimitiveRestartIndex()
{
	return yaglpp_glad_integer(GL_PRIMITIVE_RESTART_INDEX);
}

/*(3.1) Gets the alignment for uniform buffer sizes and offset
@return The minimum required alignment for uniform buffer sizes and offset*/
inline GLuint GetUniformBufferOffsetAlignment()
{
	return yaglpp_glad_integer(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT);
}

/*(3.1) Gets the size of the binding range
@return The size of the binding range for each indexed uniform buffer binding*/
inline GLint GetUniformBufferSize()
{
	return yaglpp_glad_integer(GL_UNIFORM_BUFFER_SIZE);
}

/*(3.1) Gets the start offset of the binding range
@return The start offset of the binding range for each indexed uniform buffer binding*/
inline GLint GetUniformBufferStart()
{
	return (GLintptr)yaglpp_glad_integer(GL_UNIFORM_BUFFER_START);
}

/*(3.1) Checks if primitive restart server-side GL capability is enabled, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index
@return True if primitive restart GL capability is enabled, false otherwise*/
inline GLboolean IsPrimitiveRestart()
{
	return glIsEnabled(GL_PRIMITIVE_RESTART);
}

/*(3.1) Specifies the primitive restart index. Using this GL feature requires enabling <PrimitiveRestart> capability to activate it
@param Specifies the value to be interpreted as the primitive restart index*/
inline void PrimitiveRestartIndex(GLuint index)
{
	glPrimitiveRestartIndex(index);
}
#endif // #ifdef YAGLPP_VERSION_3_1

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)
GLuint GetMaxCombinedFragmentUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
	return n;
}

GLuint GetMaxCombinedUniformBlocks()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COMBINED_UNIFORM_BLOCKS);
	return n;
}

GLuint GetMaxCombinedVertexUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
	return n;
}

GLuint GetMaxFragmentUniformBlocks()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
	return n;
}

GLuint GetMaxRectangleTextureSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_RECTANGLE_TEXTURE_SIZE);
	return n;
}

GLuint GetMaxTextureBufferSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_TEXTURE_BUFFER_SIZE);
	return n;
}

GLuint GetMaxUniformBlockSize()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_UNIFORM_BLOCK_SIZE);
	return n;
}

GLuint GetMaxUniformBufferBindings()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_UNIFORM_BUFFER_BINDINGS);
	return n;
}

GLuint GetMaxVertexUniformBlocks()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VERTEX_UNIFORM_BLOCKS);
	return n;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void DrawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
	glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
	YAGLPP_GLAD_ERROR;
}

void DrawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
	glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void DrawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
	glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
}

inline void DrawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
	glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_2
class GeometryShader;
class Sync;
class Texture2DMultisample;
class Texture2DMultisampleArray;
inline GLint64 yaglpp_glad_integer64(GLenum pname) { GLint64 i; glGetInteger64v(pname, &i); return i; }

/*(3.2) Provoking vertex mode enumerator used in <ProvokingVertex>*/
enum class ProvokeMode : GLenum
{
	/*(3.2) First vertex convention mode*/
	FirstVertexConvention = GL_FIRST_VERTEX_CONVENTION,

	/*(3.2) Last vertex convention mode*/
	LastVertexConvention = GL_LAST_VERTEX_CONVENTION,
};

/*(3.2) Disable enabled depth clamp server-side GL capability, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)*/
inline void DisableDepthClamp()
{
	glDisable(GL_DEPTH_CLAMP);
}

/*(3.2) Disable enabled sample mask server-side GL capability, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs*/
inline void DisableSampleMask()
{
	glDisable(GL_SAMPLE_MASK);
}

/*(3.2) Disable enabled program point size server-side GL capability, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range*/
inline void DisableProgramPointSize()
{
	glDisable(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Disables enabled texture cube map seamless server-side GL capability, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value*/
inline void DisableTextureCubeMapSeamless()
{
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Render primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void DrawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex);

/*(3.2) Render multiple instances of a set of primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies the number of instances of the indexed geometry that should be drawn
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void DrawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex);

/*(3.2) Render primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the minimum array index contained in indices
@param Specifies the maximum array index contained in indices
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void DrawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex);

/*(3.2) Enable depth clamp server-side GL capability, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)*/
inline void EnableDepthClamp()
{
	glEnable(GL_DEPTH_CLAMP);
}

/*(3.2) Enable sample mask server-side GL capability, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs*/
inline void EnableSampleMask()
{
	glEnable(GL_SAMPLE_MASK);
}

/*(3.2) Enable program point size server-side GL capability, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range*/
inline void EnableProgramPointSize()
{
	glEnable(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Enables texture cube map seamless server-side GL capability, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value*/
inline void EnableTextureCubeMapSeamless()
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Gets the maximum number of samples in a color multisample texture
@return The maximum texture samples value*/
GLuint GetMaxColorTextureSamples();

/*(3.2) Gets the number of words for geometry shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined geometry uniform components*/
GLuint GetMaxCombinedGeometryUniformComponents();

/*(3.2) Returns the maximum number of samples in a multisample depth or depth-stencil texture
@return The maximum depth texture samples*/
GLuint GetMaxDepthTextureSamples();

/*(3.2) Returns the maximum number of components of the inputs read by the fragment shader. The value must be at least 128
@return The maximum fragment input components*/
GLuint GetMaxFragmentInputComponents();

/*(3.2) Returns the maximum number of components of inputs read by a geometry shader. The value must be at least 64
@return The maximum geometry input components*/
GLuint GetMaxGeometryInputComponents();

/*(3.2) Returns the maximum number of components of outputs written by a geometry shader. The value must be at least 128
@return The maximum geometry output components*/
GLuint GetMaxGeometryOutputComponents();

/*(3.2) Returns the maximum supported texture image units that can be used to access texture maps from the geometry shader. The value must be at least 16
@return The maximum number of supported texture image units*/
GLuint GetMaxGeometryTextureImageUnits();

/*(3.2) Returns the maximum number of uniform blocks per geometry shader. The value must be at least 12
@return The maximum geometry uniform blocks*/
GLuint GetMaxGeometryUniformBlocks();

/*(3.2) Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a geometry shader. The value must be at least 1024
@return The maximum geometry uniform components*/
GLuint GetMaxGeometryUniformComponents();

/*(3.2) The maximum number of individual 4-vectors of floating-point, integer, or boolean values that can be held in uniform variable storage for a fragment shader.
The value is equal to the value returned by <GetMaxFragmentUniformComponents> divided by 4 and must be at least 256
@return The maximum number of fragment uniform vectors*/
GLuint GetMaxFragmentUniformVectors();

/*(3.2) Returns the maximum number of samples supported in integer format multisample buffers
@return The maximum number of integer samples*/
GLuint GetMaxIntegerSamples();

/*(3.2) Returns the maximum number of sample mask words
@return The maximum number of sample mask words*/
GLuint GetMaxSampleMaskWords();

/*(3.2) Returns the maximum timeout interval used by sync object
@return The maximum sync timeout interval*/
GLuint GetMaxServerWaitTimeout();

/*(3.2) Returns the maximum number of components of output written by a vertex shader. The value must be at least 64
@return The maximum vertex output components*/
GLuint GetMaxVertexOutputComponents();

/*(3.2) Retrieves the location of a sample
@param Specifies the index of the sample whose position to query, must be less than the value returned by <GetSamples>
@param [out] Pointer to a two-element float value receiving the position of the sample*/
void GetMultisample(GLuint index, _Out_writes_(2) GLfloat* val);

/*(3.2) Checks whether vertex program point size mode is enabled
@return True if vertex program point size mode is enabled, false otherwise*/
inline GLboolean GetProgramPointSize()
{
	return yaglpp_glad_boolean(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Returns the currently selected provoking vertex convention used by <ProvokingVertex>. The initial value is <LastVertexConvention>
@return True if vertex program point size mode is enabled, false otherwise*/
inline ProvokeMode GetProvokingVertex()
{
	return (ProvokeMode)yaglpp_glad_integer(GL_PROVOKING_VERTEX);
}

/*(3.2) Returns the current sample mask value set by <SampleMaski>
@return The current sample mask value*/
inline GLbitfield GetSampleMaskValue()
{
	return yaglpp_glad_integer(GL_SAMPLE_MASK_VALUE);
}

/*(3.2) Gets the 64-bit size of the binding range for each transform feedback attribute stream
@return The 64-bit size of the binding range*/
inline GLint64 GetTransformFeedbackBufferSize64()
{
	return yaglpp_glad_integer64(GL_TRANSFORM_FEEDBACK_BUFFER_SIZE);
}

/*(3.2) Gets the 64-bit start offset of the binding range for each transform feedback attribute stream
@return The 64-bit start offset of the binding range*/
inline GLint64 GetTransformFeedbackBufferStart64()
{
	return yaglpp_glad_integer64(GL_TRANSFORM_FEEDBACK_BUFFER_START);
}

/*(3.2) Gets the 64-bit size of the binding range
@return The 64-bit size of the binding range for each indexed uniform buffer binding*/
inline GLint64 GetUniformBufferSize64()
{
	return yaglpp_glad_integer64(GL_UNIFORM_BUFFER_SIZE);
}

/*(3.2) Gets the 64-bit start offset of the binding range
@return The 64-bit start offset of the binding range for each indexed uniform buffer binding*/
inline GLint64 GetUniformBufferStart64()
{
	return yaglpp_glad_integer64(GL_UNIFORM_BUFFER_START);
}

/*(3.2) Checks if depth clamp server-side GL capability is enabled, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)
@return True if depth clamp GL capability is enabled, false otherwise*/
inline GLboolean IsDepthClamp()
{
	return glIsEnabled(GL_DEPTH_CLAMP);
}

/*(3.2) Checks if sample mask server-side GL capability is enabled, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs
@return True if sample mask GL capability is enabled, false otherwise*/
inline GLboolean IsSampleMask()
{
	return glIsEnabled(GL_SAMPLE_MASK);
}

/*(3.2) Checks if program point size server-side GL capability is enabled, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range
@return True if program point size GL capability is enabled, false otherwise*/
inline GLboolean IsProgramPointSize()
{
	return glIsEnabled(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Checks if texture cube map seamless server-side GL capability is enabled, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value
@return True if texture cube map seamless GL capability is enabled, false otherwise*/
inline GLboolean IsTextureCubeMapSeamless()
{
	return glIsEnabled(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Render multiple sets of primitives by specifying indices of array data elements and an index to apply to each index
@param Specifies what kind of primitives to render
@param [in] Specifies a pointer to an array of the elements counts
@param Specifies the type of the values in indices
@param [in] Pointer to an array of the byte offsets into the element array index buffer object's data store
@param Specifies the size of the count, indices and basevertex arrays
@param [in] Specifies a pointer to an array of the base vertices*/
void MultiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex);

/*(3.2) Specifies the vertex to be used as the source of data for flat shaded varyings
@param Controls the selection of the vertex whose values are assigned to flatshaded varying outputs*/
void ProvokingVertex(ProvokeMode provokeMode);

/*(3.2) Sets the value of a sub-word of the sample mask, which must be less than the value returned by <GetMaxSampleMaskWords>
@param Specifies which 32-bit sub-word of the sample mask to update
@param Specifies the new value of the mask sub-word*/
void SampleMask(GLuint maskNumber, GLbitfield mask);
#endif // #ifdef YAGLPP_VERSION_3_2

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
GLuint GetMaxColorTextureSamples()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COLOR_TEXTURE_SAMPLES);
	return n;
}

GLuint GetMaxCombinedGeometryUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS);
	return n;
}

GLuint GetMaxDepthTextureSamples()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_DEPTH_TEXTURE_SAMPLES);
	return n;
}

GLuint GetMaxFragmentInputComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_FRAGMENT_INPUT_COMPONENTS);
	return n;
}

GLuint GetMaxFragmentUniformVectors()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_FRAGMENT_UNIFORM_VECTORS);
	return n;
}

GLuint GetMaxGeometryInputComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_GEOMETRY_INPUT_COMPONENTS);
	return n;
}

GLuint GetMaxGeometryOutputComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS);
	return n;
}

GLuint GetMaxGeometryTextureImageUnits()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS);
	return n;
}

GLuint GetMaxGeometryUniformBlocks()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_GEOMETRY_UNIFORM_BLOCKS);
	return n;
}

GLuint GetMaxGeometryUniformComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS);
	return n;
}

GLuint GetMaxIntegerSamples()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_INTEGER_SAMPLES);
	return n;
}

GLuint GetMaxSampleMaskWords()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_SAMPLE_MASK_WORDS);
	return n;
}

GLuint GetMaxServerWaitTimeout()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_SERVER_WAIT_TIMEOUT);
	return n;
}

GLuint GetMaxVertexOutputComponents()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_VERTEX_OUTPUT_COMPONENTS);
	return n;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void DrawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
	YAGLPP_GLAD_ERROR;
}

void DrawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
	glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
	YAGLPP_GLAD_ERROR;
}

void DrawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
	YAGLPP_GLAD_ERROR;
}

void GetMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(index < GetSamples());

	glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
}

void MultiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
	glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
	YAGLPP_GLAD_ERROR;
}

void ProvokingVertex(ProvokeMode provokeMode)
{
	glProvokingVertex((GLenum)provokeMode);
	YAGLPP_GLAD_ERROR;
}

void SampleMask(GLuint maskNumber, GLbitfield mask)
{
	// INDEX EXCEEDS MAXIMUM VALUE
	YAGLPP_ASSERT(maskNumber < GetMaxSampleMaskWords());

	glSampleMaski(maskNumber, mask);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void DrawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
}

inline void DrawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
	glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
}

inline void DrawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
}

inline void GetMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
	glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
}

inline void MultiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
	glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
}

inline void ProvokingVertex(ProvokeMode provokeMode)
{
	glProvokingVertex((GLenum)provokeMode);
}

inline void SampleMask(GLuint maskNumber, GLbitfield mask)
{
	glSampleMaski(maskNumber, mask);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_3
class AnySamplesPassed;
class Sampler;
class TimeElapsed;

/*(3.3) Gets the maximum number of active draw buffers when using dual-source blending. The value must be at least 1
@return The maximum number of dual source draw buffers*/
GLuint GetMaxDualSourceDrawBuffers();
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined(YAGLPP_VERSION_3_3) && defined(YAGLPP_IMPLEMENTATION)
GLuint GetMaxDualSourceDrawBuffers()
{
	static GLuint n = yaglpp_glad_integer(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS);
	return n;
}
#endif // if defined(YAGLPP_VERSION_3_3) && defined(YAGLPP_IMPLEMENTATION)
} // namespace gl

#include <yaglpp/glad/sync.h>
#include <yaglpp/glad/objects.h>
#include <yaglpp/glad/indices.h>
#include <yaglpp/glad/uniform_block.h>

namespace gl {
inline VertexAttrib Program::GetVertexAttrib(_In_z_ const GLchar* name)
{
	return VertexAttrib(*this, name);
}

inline Uniform Program::GetUniform(_In_z_ const GLchar* name)
{
	return Uniform(*this, name);
}

#ifdef YAGLPP_VERSION_3_1
inline void Program::GetUniformBlock(UniformBlock& uniformBlock, _In_z_ const GLchar* name)
{
	uniformBlock.GetIndex(*this, name);
}
#endif // #ifdef YAGLPP_VERSION_3_1
} // namespace gl
#endif // #ifndef YAGLPP_GLADPP_H
