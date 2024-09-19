#pragma once
#include <yaglpp/glpp.h>
#include <glad/glad.h>
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 20
#define YAGLPP_VERSION_2_1
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 20
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 21
#define YAGLPP_VERSION_3_0
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 21
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 30
#define YAGLPP_VERSION_3_1
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 30
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 31
#define YAGLPP_VERSION_3_2
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 31
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 32
#define YAGLPP_VERSION_3_3
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 32
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 33
#define YAGLPP_VERSION_4_0
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 33
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 40
#define YAGLPP_VERSION_4_1
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 40
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 41
#define YAGLPP_VERSION_4_2
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 41
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 42
#define YAGLPP_VERSION_4_3
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 42
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 43
#define YAGLPP_VERSION_4_4
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 43
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 44
#define YAGLPP_VERSION_4_5
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 44
#if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 45
#define YAGLPP_VERSION_4_6
#endif // #if (YAGLPP_CONTEXT_VERSION_MAJOR * 10 + YAGLPP_CONTEXT_VERSION_MINOR) > 45
#define YAGLPP_STR(x) #x
#define YAGLPP_XSTR(x) YAGLPP_STR(x)
#pragma message ("YAGL++: Compiling with OpenGL " YAGLPP_XSTR(YAGLPP_CONTEXT_VERSION_MAJOR) "." YAGLPP_XSTR(YAGLPP_CONTEXT_VERSION_MINOR) " context version support...")
/*(1) The GLAD loader to be ported into another library with an extern declaration. Prefered version for SFML and GLEW
@return True if GLAD sucessfully loaded, false otherwise*/
bool loadGL();

/*(2) The GLAD loader to be ported into another library with an extern declaration. Prefered version for GLFW
@param GLAD proc address returned by <glfwGetProcAddress> function
@return True if GLAD sucessfully loaded, false otherwise*/
bool loadGL(void* proc);

#ifdef YAGLPP_IMPLEMENTATION
bool loadGL()
{
	return gladLoadGL() != 0;
}

bool loadGL(void* proc)
{
	return gladLoadGLLoader((GLADloadproc)proc) != 0;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

/*YAGL++ GLAD library namespace*/
namespace gl {
void _disable(GLenum cap);
void _enable(GLenum cap);
GLboolean _getBoolean(GLenum pname);
void _getBoolean(GLenum pname, GLboolean* data);
GLdouble _getDouble(GLenum pname);
void _getDouble(GLenum pname, GLdouble* data);
GLfloat _getFloat(GLenum pname);
void _getFloat(GLenum pname, GLfloat* data);
GLint _getInteger(GLenum pname);
void _getInteger(GLenum pname, GLint* data);
const GLubyte* _getString(GLenum name);
void _hint(GLenum target, GLenum mode);
GLboolean _isEnabled(GLenum cap);
void _pixelStore(GLenum pname, GLfloat param);
void _pixelStore(GLenum pname, GLint param);

#ifdef YAGLPP_VERSION_3_0
GLboolean _getBoolean(GLenum target, GLuint index);
GLint _getInteger(GLenum target, GLuint index);
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_2
GLint64 _getInteger64(GLenum pname);
GLint64 _getInteger64(GLenum target, GLuint index);
#endif // #ifdef YAGLPP_VERSION_3_2

/*GLAD draw buffer unit index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1*/
typedef unsigned short DrawBuffer;

/*GLAD active texture unit index ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1*/
typedef unsigned short TextureUnit;

class _Buffer;
class _Object;
class _Objects;
class _Query;
class _Shader;
class _Texture;
class ArrayBuffer;
class Buffers;
class ElementArrayBuffer;
class FragmentShader;
class Program;
class SamplesPassed;
class Texture1D;
class Texture2D;
class Texture3D;
class TextureCubeMap;
class Textures;
class Uniform;
class VertexAttrib;
class VertexShader;
enum class ActiveAttribType : GLenum;
enum class ActiveUniformType : GLenum;
enum class BufferAccess : GLenum;
enum class BufferUsage : GLenum;
enum class CompressedTexInternalformat : GLenum;
enum class CopyTexInternalformat : GLenum;
enum class GetTexFormat : GLenum;
enum class ShaderType : GLenum;
enum class TexFormat : GLenum;
enum class TexInternalformat : GLenum;
enum class TexSubFormat : GLenum;
enum class TexSubType : GLenum;
enum class TextureCubeMapPlane : GLenum;
enum class TextureMagFilter : GLenum;
enum class TextureMinFilter : GLenum;
enum class TexType : GLenum;
enum class TextureWrapMode : GLenum;
enum class VertexAttribSize : GLsizei;
enum class VertexAttribType : GLenum;
enum class VertexAttribPType : GLenum;

/*GLAD GL behavior hint enumerator*/
enum class BehaviorHint : GLenum
{
	/*The most efficient option should be chosen*/
	Fastest = GL_FASTEST,

	/*The most correct, or highest quality, option should be chosen*/
	Nicest = GL_NICEST,

	/*No preference*/
	DontCare = GL_DONT_CARE,
};

/*GLAD blend equation mode enumerator*/
enum class BlendEquationMode : GLenum
{
	/*Add blend equation mode calculated per-channel as (Src * SrcFact) + (Dst * DstFact) clamped to [0, 1]*/
	FuncAdd = GL_FUNC_ADD,

	/*Subtract blend equation mode calculated per-channel as (Src * SrcFact) - (Dst * DstFact) clamped to [0, 1]*/
	FuncSubtract = GL_FUNC_SUBTRACT,

	/*Reversed subtract blend equation mode calculated per-channel as (Src * SrcFact) - (Dst * DstFact) clamped to [0, 1]*/
	FuncReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,

	/*Min blend equation mode calculated per-channel as min(Src, Dst) clamped to [0, 1]*/
	Min = GL_MIN,

	/*Max blend equation mode calculated per-channel as max(Src, Dst) clamped to [0, 1]*/
	Max = GL_MAX,
};

/*GLAD blend function factor enumerator*/
enum class BlendFuncFactor : GLenum
{
	/*Zero blend function factor calculated per-channel as 0*/
	Zero = GL_ZERO,

	/*One blend function factor calculated per-channel as 1*/
	One = GL_ONE,

	/*Source color blend function factor calculated per-channel as (Src0 / Max)*/
	SrcColor = GL_SRC_COLOR,

	/*One minus source color blend function factor calculated per-channel as 1 - (Src0 / Max)*/
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,

	/*Destination color blend function factor calculated per-channel as (Dst0 / Max)*/
	DstColor = GL_DST_COLOR,

	/*One minus destination color blend function factor calculated per-channel as 1 - (Dst0 / Max)*/
	OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,

	/*Source alpha blend function factor calculated per-channel as (SrcAlpha0 / Max)*/
	SrcAlpha = GL_SRC_ALPHA,

	/*One minus source alpha blend function factor calculated per-channel as 1 - (SrcAlpha0 / Max)*/
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,

	/*Destination alpha blend function factor calculated per-channel as (DstAlpha0 / Max)*/
	DstAlpha = GL_DST_ALPHA,

	/*One minus destination alpha blend function factor calculated per-channel as 1 - (DstAlpha0 / Max)*/
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,

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

/*GLAD buffer bit mask enumerator*/
enum class BufferBitMask : GLbitfield
{
	/*Indicates the buffers currently enabled for color writing*/
	ColorBufferBit = GL_COLOR_BUFFER_BIT,

	/*Indicates the depth buffer*/
	DepthBufferBit = GL_DEPTH_BUFFER_BIT,

	/*Indicates the stencil buffer*/
	StencilBufferBit = GL_STENCIL_BUFFER_BIT,
};

/*GLAD color-renderable, depth-renderable, or stencil-renderable format enumerator*/
enum class ColorDepthStencilFormat : GLenum
{
	/*RGB color component format with (8:8:8)-bit resolution*/
	Rgb8 = GL_RGB8,

	/*RGBA color component format with (8:8:8:8)-bit resolution*/
	Rgba8 = GL_RGBA8,

	/*RGBA color component format with (5:5:5:1)-bit resolution*/
	Rgb5A1 = GL_RGB5_A1,

	/*RGBA color component format with (4:4:4:4)-bit resolution*/
	Rgba4 = GL_RGBA4,

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

	/*(3.0) Red unsigned integer color component format with 8-bit resolution*/
	R8ui = GL_R8UI,

	/*(3.0) Red signed integer color component format with 8-bit resolution*/
	R8i = GL_R8I,

	/*(3.0) Red unsigned integer color component format with 16-bit resolution*/
	R16ui = GL_R16UI,

	/*(3.0) Red signed integer color component format with 16-bit resolution*/
	R16i = GL_R16I,

	/*(3.0) Red unsigned integer color component format with 32-bit resolution*/
	R32ui = GL_R32UI,

	/*(3.0) Red signed integer color component format with 32-bit resolution*/
	R32i = GL_R32I,

	/*(3.0) RG color component format with (8:8)-bit resolution*/
	Rg8 = GL_RG8,

	/*(3.0) RG unsigned integer color component format with (8:8)-bit resolution*/
	Rg8ui = GL_RG8UI,

	/*(3.0) RG signed integer color component format with (8:8)-bit resolution*/
	Rg8i = GL_RG8I,

	/*(3.0) RG unsigned integer color component format with (16:16)-bit resolution*/
	Rg16ui = GL_RG16UI,

	/*(3.0) RG signed integer color component format with (16:16)-bit resolution*/
	Rg16i = GL_RG16I,

	/*(3.0) RG unsigned integer color component format with (32:32)-bit resolution*/
	Rg32ui = GL_RG32UI,

	/*(3.0) RG signed integer color component format with (32:32)-bit resolution*/
	Rg32i = GL_RG32I,

	/*(3.0) RGBA unsigned integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.0) RGBA signed integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8i = GL_RGBA8I,

	/*(3.0) RGBA unsigned integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.0) RGBA signed integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16i = GL_RGBA16I,

	/*(3.0) RGBA signed integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32i = GL_RGBA32I,

	/*(3.0) RGBA unsigned integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32ui = GL_RGBA32UI,

	/*(3.0) Depth component format with 32f-bit resolution*/
	DepthComponent32f = GL_DEPTH_COMPONENT32F,

	/*(3.0) Depth and stencil component format with (24:8)-bit resolution*/
	Depth24Stencil8 = GL_DEPTH24_STENCIL8,

	/*(3.0) Depth and stencil component format with (32f:8)-bit resolution*/
	Depth32fStencil8 = GL_DEPTH32F_STENCIL8,

	/*(3.0) Stencil component format with 8-bit resolution*/
	StencilIndex8 = GL_STENCIL_INDEX8,
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

/*GLAD draw buffer unit enumerator used by <drawBuffer>*/
enum class DrawBufferUnit : GLenum
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
	ColorAttachment0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	ColorAttachment1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	ColorAttachment2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	ColorAttachment3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	ColorAttachment4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	ColorAttachment5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	ColorAttachment6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	ColorAttachment7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	ColorAttachment8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	ColorAttachment9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	ColorAttachment10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	ColorAttachment11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	ColorAttachment12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	ColorAttachment13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	ColorAttachment14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	ColorAttachment15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	ColorAttachment16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	ColorAttachment17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	ColorAttachment18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	ColorAttachment19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	ColorAttachment20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	ColorAttachment21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	ColorAttachment22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	ColorAttachment23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	ColorAttachment24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	ColorAttachment25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	ColorAttachment26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	ColorAttachment27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	ColorAttachment28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	ColorAttachment29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	ColorAttachment30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	ColorAttachment31 = GL_COLOR_ATTACHMENT31,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD draw buffer unit enumerator used by <drawBuffers>*/
enum class DrawBuffersUnit : GLenum
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
	ColorAttachment0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	ColorAttachment1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	ColorAttachment2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	ColorAttachment3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	ColorAttachment4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	ColorAttachment5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	ColorAttachment6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	ColorAttachment7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	ColorAttachment8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	ColorAttachment9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	ColorAttachment10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	ColorAttachment11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	ColorAttachment12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	ColorAttachment13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	ColorAttachment14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	ColorAttachment15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	ColorAttachment16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	ColorAttachment17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	ColorAttachment18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	ColorAttachment19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	ColorAttachment20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	ColorAttachment21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	ColorAttachment22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	ColorAttachment23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	ColorAttachment24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	ColorAttachment25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	ColorAttachment26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	ColorAttachment27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	ColorAttachment28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	ColorAttachment29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	ColorAttachment30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	ColorAttachment31 = GL_COLOR_ATTACHMENT31,
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

/*GLAD orientation of front-facing polygons enumerator*/
enum class FrontFaceMode : GLenum
{
	/*Selects clockwise polygons as front-facing*/
	Clockwise = GL_CW,

	/*Selects counterclockwise polygons as front-facing*/
	CounterClockwise = GL_CCW,
};

/*GLAD logic operation mode enumerator*/
enum class LogicOpMode : GLenum
{
	/*Logic operation mode: dst = 0*/
	Clear = GL_CLEAR,

	/*Logic operation mode: dst = 1*/
	Set = GL_SET,

	/*Logic operation mode: dst = src*/
	Copy = GL_COPY,

	/*Logic operation mode: dst = ~src*/
	CopyInverted = GL_COPY_INVERTED,

	/*Logic operation mode: dst = dst*/
	Noop = GL_NOOP,

	/*Logic operation mode: dst = ~dst*/
	Invert = GL_INVERT,

	/*Logic operation mode: dst = src & dst*/
	And = GL_AND,

	/*Logic operation mode: dst = ~(src & dst)*/
	Nand = GL_NAND,

	/*Logic operation mode: dst = src | dst*/
	Or = GL_OR,

	/*Logic operation mode: dst = ~(src | dst)*/
	Nor = GL_NOR,

	/*Logic operation mode: dst = src ^ dst*/
	Xor = GL_XOR,

	/*Logic operation mode: dst = ~(src ^ dst)*/
	Equiv = GL_EQUIV,

	/*Logic operation mode: dst = src & ~dst*/
	AndReverse = GL_AND_REVERSE,

	/*Logic operation mode: dst = ~src & dst*/
	AndInverted = GL_AND_INVERTED,

	/*Logic operation mode: dst = src | ~dst*/
	OrReverse = GL_OR_REVERSE,

	/*Logic operation mode: dst = ~src | dst*/
	OrInverted = GL_OR_INVERTED,
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
enum class PointSpriteCoordOrigin : GLenum
{
	/*Lower left origin*/
	LowerLeft = GL_LOWER_LEFT,

	/*Upper left origin*/
	UpperLeft = GL_UPPER_LEFT,
};

/*GLAD polygon rasterization mode enumerator*/
enum class PolygonMode : GLenum
{
	/*Polygon vertices that are marked as the start of a boundary edge are drawn as points*/
	Point = GL_POINT,

	/*Boundary edges of the polygon are drawn as line segments*/
	Line = GL_LINE,

	/*The interior of the polygon is filled*/
	Fill = GL_FILL,
};

/*GLAD primitive mode enumerator*/
enum class PrimitiveMode : GLenum
{
	/*Causes OpenGL to interpret each individual vertex in the stream as a point. Points that have a Texture mapped onto them are often called "point sprites"*/
	Points = GL_POINTS,

	/*Vertices 0 and 1 are considered a line. Vertices 2 and 3 are considered a line. And so on. If the user specifies a non-even number of vertices, then the extra vertex is ignored*/
	Lines = GL_LINES,

	/*As <lineStrip>, except that the first and last vertices are also used as a line. Thus, you get n lines for n input vertices. If the user only specifies 1 vertex, the drawing command is ignored. The line between the first and last vertices happens after all of the previous lines in the sequence*/
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

/*GLAD stencil operation mode enumerator*/
enum class StencilOpMode : GLenum
{
	/*Keeps the current value*/
	Keep = GL_KEEP,

	/*Sets the stencil buffer value to 0*/
	Zero = GL_ZERO,

	/*Sets the stencil buffer value to ref, as specified by <stencilFunc>*/
	Replace = GL_REPLACE,

	/*Increments the current stencil buffer value. Clamps to the maximum representable unsigned value*/
	Incr = GL_INCR,

	/*Increments the current stencil buffer value. Wraps stencil buffer value to zero when incrementing the maximum representable unsigned value*/
	IncrWrap = GL_INCR_WRAP,

	/*Decrements the current stencil buffer value. Clamps to 0*/
	Decr = GL_DECR,

	/*Decrements the current stencil buffer value. Wraps stencil buffer value to the maximum representable unsigned value when decrementing a stencil buffer value of zero*/
	DecrWrap = GL_DECR_WRAP,

	/*Bitwise inverts the current stencil buffer value*/
	Invert = GL_INVERT,
};

/*GLAD read buffer unit enumerator used by <readBuffer>*/
enum class ReadBufferUnit : GLenum
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
	ColorAttachment0 = GL_COLOR_ATTACHMENT0,

	/*(3.0) Framebuffer color attachment unit 1*/
	ColorAttachment1 = GL_COLOR_ATTACHMENT1,

	/*(3.0) Framebuffer color attachment unit 2*/
	ColorAttachment2 = GL_COLOR_ATTACHMENT2,

	/*(3.0) Framebuffer color attachment unit 3*/
	ColorAttachment3 = GL_COLOR_ATTACHMENT3,

	/*(3.0) Framebuffer color attachment unit 4*/
	ColorAttachment4 = GL_COLOR_ATTACHMENT4,

	/*(3.0) Framebuffer color attachment unit 5*/
	ColorAttachment5 = GL_COLOR_ATTACHMENT5,

	/*(3.0) Framebuffer color attachment unit 6*/
	ColorAttachment6 = GL_COLOR_ATTACHMENT6,

	/*(3.0) Framebuffer color attachment unit 7*/
	ColorAttachment7 = GL_COLOR_ATTACHMENT7,

	/*(3.0) Framebuffer color attachment unit 8*/
	ColorAttachment8 = GL_COLOR_ATTACHMENT8,

	/*(3.0) Framebuffer color attachment unit 9*/
	ColorAttachment9 = GL_COLOR_ATTACHMENT9,

	/*(3.0) Framebuffer color attachment unit 10*/
	ColorAttachment10 = GL_COLOR_ATTACHMENT10,

	/*(3.0) Framebuffer color attachment unit 11*/
	ColorAttachment11 = GL_COLOR_ATTACHMENT11,

	/*(3.0) Framebuffer color attachment unit 12*/
	ColorAttachment12 = GL_COLOR_ATTACHMENT12,

	/*(3.0) Framebuffer color attachment unit 13*/
	ColorAttachment13 = GL_COLOR_ATTACHMENT13,

	/*(3.0) Framebuffer color attachment unit 14*/
	ColorAttachment14 = GL_COLOR_ATTACHMENT14,

	/*(3.0) Framebuffer color attachment unit 15*/
	ColorAttachment15 = GL_COLOR_ATTACHMENT15,

	/*(3.0) Framebuffer color attachment unit 16*/
	ColorAttachment16 = GL_COLOR_ATTACHMENT16,

	/*(3.0) Framebuffer color attachment unit 17*/
	ColorAttachment17 = GL_COLOR_ATTACHMENT17,

	/*(3.0) Framebuffer color attachment unit 18*/
	ColorAttachment18 = GL_COLOR_ATTACHMENT18,

	/*(3.0) Framebuffer color attachment unit 19*/
	ColorAttachment19 = GL_COLOR_ATTACHMENT19,

	/*(3.0) Framebuffer color attachment unit 20*/
	ColorAttachment20 = GL_COLOR_ATTACHMENT20,

	/*(3.0) Framebuffer color attachment unit 21*/
	ColorAttachment21 = GL_COLOR_ATTACHMENT21,

	/*(3.0) Framebuffer color attachment unit 22*/
	ColorAttachment22 = GL_COLOR_ATTACHMENT22,

	/*(3.0) Framebuffer color attachment unit 23*/
	ColorAttachment23 = GL_COLOR_ATTACHMENT23,

	/*(3.0) Framebuffer color attachment unit 24*/
	ColorAttachment24 = GL_COLOR_ATTACHMENT24,

	/*(3.0) Framebuffer color attachment unit 25*/
	ColorAttachment25 = GL_COLOR_ATTACHMENT25,

	/*(3.0) Framebuffer color attachment unit 26*/
	ColorAttachment26 = GL_COLOR_ATTACHMENT26,

	/*(3.0) Framebuffer color attachment unit 27*/
	ColorAttachment27 = GL_COLOR_ATTACHMENT27,

	/*(3.0) Framebuffer color attachment unit 28*/
	ColorAttachment28 = GL_COLOR_ATTACHMENT28,

	/*(3.0) Framebuffer color attachment unit 29*/
	ColorAttachment29 = GL_COLOR_ATTACHMENT29,

	/*(3.0) Framebuffer color attachment unit 30*/
	ColorAttachment30 = GL_COLOR_ATTACHMENT30,

	/*(3.0) Framebuffer color attachment unit 31*/
	ColorAttachment31 = GL_COLOR_ATTACHMENT31,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD image pixel data format enumerator used by <readPixels>*/
enum class ReadPixelsFormat : GLenum
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

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Each pixel is depth and stencil components*/
	DepthStencil = GL_DEPTH_STENCIL,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*GLAD image pixel data type enumerator used in <readPixels>*/
enum class ReadPixelsType : GLenum
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

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Float 16-bit value used for each color component*/
	HalfFloat = GL_HALF_FLOAT,

	/*(3.0) Single 32-bit value used for depth and stencil unsigned integer (24:8)-bit components, format must be <DepthStencil>*/
	UnsignedInt248 = GL_UNSIGNED_INT_24_8,

	/*(3.0) Single 32-bit value used for three float (10f:11f:11f)-bit reversed color components, format must be <Bgr>*/
	UnsignedInt10F11F11FRev = GL_UNSIGNED_INT_10F_11F_11F_REV,

	/*(3.0) Single 32-bit value used for four unsigned integer (5:9:9:9)-bit reversed color components, format must be <Bgra>*/
	UnsignedInt5999Rev = GL_UNSIGNED_INT_5_9_9_9_REV,

	/*(3.0) Single 40-bit value used for depth and stencil (32f:8)-bit reversed components, format must be <DepthStencil>*/
	Float32UnsignedInt248Rev = GL_FLOAT_32_UNSIGNED_INT_24_8_REV,
#endif // #ifdef YAGLPP_VERSION_3_0
};

/*Constant expression BufferBitMask bitwise OR operator combining multiple BufferBitMask flags into bitfield mask
@param BufferBitMask bitmask enumerator flag 1
@param BufferBitMask bitmask enumerator flag 2
@return Resulting bitmask BufferBitMask enumerator*/
constexpr BufferBitMask operator | (BufferBitMask flag1, BufferBitMask flag2)
{
	return (BufferBitMask)((GLbitfield)flag1 | (GLbitfield)flag2);
}

/*Selects active texture unit by the index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1. All subsequetial calls to texture functions will be performad on that texture unit.
@param Specifies the index of texture unit to make active, initial is 0*/
void activeTexture(TextureUnit index);

/*Sets the blend color
@param specify the red components of the blend color
@param specify the green components of the blend color
@param specify the blue components of the blend color
@param specify the alpha components of the blend color*/
void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

/*Specifies the equation used for both the RGB blend equation and the Alpha blend equation
@param Specifies how source and destination colors are combined*/
void blendEquation(BlendEquationMode mode);

/*Set the RGB blend equation and the alpha blend equation separately
@param Specifies the RGB blend equation, how the red, green, and blue components of the source and destination colors are combined
@param Specifies the alpha blend equation, how the alpha component of the source and destination colors are combined*/
void blendEquationSeparate(BlendEquationMode modeRGB, BlendEquationMode modeAlpha);

/*Defines the operation of blending for all draw buffers when it is enabled
@param Specifies how the red, green, blue, and alpha source blending factors are computed. The initial value is <One>
@param Specifies how the red, green, blue, and alpha destination blending factors are computed. The initial value is <Zero>*/
void blendFunc(BlendFuncFactor sfactor, BlendFuncFactor dfactor);

/*Defines the operation of blending for all draw buffers when it is enabled for RGB and alpha components separately
@param Specifies how the red, green, and blue source blending factors are computed. The initial value is <One>
@param Specifies how the red, green, and blue destination blending factors are computed. The initial value is <Zero>
@param Specifies how the alpha source blending factors are computed. The initial value is <One>
@param Specifies how the alpha destination blending factors are computed. The initial value is <Zero>*/
void blendFuncSeparate(BlendFuncFactor srcRGB, BlendFuncFactor dstRGB, BlendFuncFactor srcAlpha, BlendFuncFactor dstAlpha);

/*Clear specified buffers to preset values. The bitmask flags can be combined with OR operator
@param The clear buffer mask enumerator*/
void clear(BufferBitMask mask);

/*Specifies clear values for the color buffers
@param Specifies the red value used when the color buffers are cleared. The initial values is 0.0f
@param Specifies the green value used when the color buffers are cleared. The initial values is 0.0f
@param Specifies the blue value used when the color buffers are cleared. The initial values is 0.0f
@param Specifies the alpha value used when the color buffers are cleared. The initial values is 0.0f*/
void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

/*Specifies the clear value for the depth buffer
@param Specifies the depth value used when the depth buffer is cleared*/
void clearDepth(GLdouble depth);

/*Specifies the clear value for the stencil buffer
@param Specifies the index used when the stencil buffer is cleared. The initial value is 0*/
void clearStencil(GLint stencil);

/*(1) Enable and disable writing of color components to every draw buffers
@param Specifies whether red component is to be written into the frame buffer. The initial value is true
@param Specifies whether green component is be written into the frame buffer. The initial value is true
@param Specifies whether blue component is to be written into the frame buffer. The initial value is true
@param Specifies whether alpha  component is to be written into the frame buffer. The initial value is true*/
void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

/*Specifies whether front- or back-facing facets can be culled
@param Specifies whether front- or back-facing facets are candidates for culling. The initial value is <Back>*/
void cullFace(FaceMode mode);

/*When depth testing enabled, compares each incoming pixel depth value with the depth value present in the depth buffer. In the following equations <Di> is the incoming depth value, and <Ds> is the stored depth value. Equal: passes if Di == Ds, Notequal: passes if Di != Ds, Less: passes if Di < Ds, Greater: passes if Di > Ds, Lequal: passes if Di <= Ds, Gequal: passes if Di >= Ds, Always: Always passes, Never: Never passes
@param Specifies the depth comparison function*/
void depthFunc(CompareFunc func);

/*Enable or disable writing into the depth buffer. Initially, depth buffer writing is enabled
@param Specifies whether the depth buffer is enabled for writing*/
void depthMask(GLboolean flag);

/*Specifies mapping of depth values from normalized device coordinates to window coordinates
@param Specifies the mapping of the near clipping plane to window coordinates. The initial value is 0.0
@param Specifies the mapping of the far clipping plane to window coordinates. The initial value is 1.0*/
void depthRange(GLdouble nearVal, GLdouble farVal);

/*Disable enabled blend server-side GL capability, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers*/
inline void disableBlend()
{
	_disable(GL_BLEND);
}

/*Disable enabled color logic operation server-side GL capability, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values*/
inline void disableColorLogicOp()
{
	_disable(GL_COLOR_LOGIC_OP);
}

/*Disable enabled cull face server-side GL capability, initially disabled. If enabled, cull polygons based on their winding in window coordinates*/
inline void disableCullFace()
{
	_disable(GL_CULL_FACE);
}

/*Disable enabled depth test server-side GL capability, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled*/
inline void disableDepthTest()
{
	_disable(GL_DEPTH_TEST);
}

/*Disable enabled dither server-side GL capability, initially enabled. If enabled, dither color components or indices before they are written to the color buffer*/
inline void disableDither()
{
	_disable(GL_DITHER);
}

/*Disable enabled line smooth server-side GL capability, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines*/
inline void disableLineSmooth()
{
	_disable(GL_LINE_SMOOTH);
}

/*Disable enabled multisample server-side GL capability, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel*/
inline void disableMultisample()
{
	_disable(GL_MULTISAMPLE);
}

/*Disable enabled polygon offset fill server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void disablePolygonOffsetFill()
{
	_disable(GL_POLYGON_OFFSET_FILL);
}

/*Disable enabled polygon offset line server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void disablePolygonOffsetLine()
{
	_disable(GL_POLYGON_OFFSET_LINE);
}

/*Disable enabled polygon offset point server-side GL capability, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode*/
inline void disablePolygonOffsetPoint()
{
	_disable(GL_POLYGON_OFFSET_POINT);
}

/*Disable enabled polygon smooth server-side GL capability, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back*/
inline void disablePolygonSmooth()
{
	_disable(GL_POLYGON_SMOOTH);
}

/*Disable enabled sample alpha to coverage server-side GL capability, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value*/
inline void disableSampleAlphaToCoverage()
{
	_disable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Disable enabled sample alpha to one server-side GL capability, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value*/
inline void disableSampleAlphaToOne()
{
	_disable(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Disable enabled sample coverage server-side GL capability, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value*/
inline void disableSampleCoverage()
{
	_disable(GL_SAMPLE_COVERAGE);
}

/*Disable enabled scissor test server-side GL capability, initially disabled. If enabled, discard fragments that are outside the scissor rectangle*/
inline void disableScissorTest()
{
	_disable(GL_SCISSOR_TEST);
}

/*Disable enabled stencil test server-side GL capability, initially disabled. If enabled, do stencil testing and update the stencil buffer*/
inline void disableStencilTest()
{
	_disable(GL_STENCIL_TEST);
}

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the starting index in the enabled arrays
@param Specifies the number of indices to be rendered*/
void drawArrays(PrimitiveMode mode, GLint first, GLsizei count);

/*Specifies which color buffers of the default framebuffer are to be drawn into
@param Specifies up to four color buffers to be drawn into. The initial value is <Front> for single-buffered, and <Back> for double-buffered contexts*/
void drawBuffer(DrawBufferUnit buf);

/*Specifies a list of color buffers to be drawn into
@param Specifies the number of buffers in the array. The maximum number of draw buffers supported is <getMaxDrawBuffers>
@param Pointer to an array of symbolic constants specifying the buffers into which fragment colors or data values will be written*/
void drawBuffers(GLsizei n, _In_reads_(n) const DrawBuffersUnit* bufs);

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store*/
void drawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices);

/*Render primitives from array data
@param Specifies what kind of primitives to render
@param Specifies the minimum array index contained in indices
@param Specifies the maximum array index contained in indices
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store*/
void drawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices);

/*Enable blend server-side GL capability, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers*/
inline void enableBlend()
{
	_enable(GL_BLEND);
}

/*Enable color logic operation server-side GL capability, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values*/
inline void enableColorLogicOp()
{
	_enable(GL_COLOR_LOGIC_OP);
}

/*Enable cull face server-side GL capability, initially disabled. If enabled, cull polygons based on their winding in window coordinates*/
inline void enableCullFace()
{
	_enable(GL_CULL_FACE);
}

/*Enable depth test server-side GL capability, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled*/
inline void enableDepthTest()
{
	_enable(GL_DEPTH_TEST);
}

/*Enable dither server-side GL capability, initially enabled. If enabled, dither color components or indices before they are written to the color buffer*/
inline void enableDither()
{
	_enable(GL_DITHER);
}

/*Enable line smooth server-side GL capability, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines*/
inline void enableLineSmooth()
{
	_enable(GL_LINE_SMOOTH);
}

/*Enable multisample server-side GL capability, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel*/
inline void enableMultisample()
{
	_enable(GL_MULTISAMPLE);
}

/*Enable polygon offset fill server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void enablePolygonOffsetFill()
{
	_enable(GL_POLYGON_OFFSET_FILL);
}

/*Enable polygon offset line server-side GL capability, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed*/
inline void enablePolygonOffsetLine()
{
	_enable(GL_POLYGON_OFFSET_LINE);
}

/*Enable polygon offset point server-side GL capability, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode*/
inline void enablePolygonOffsetPoint()
{
	_enable(GL_POLYGON_OFFSET_POINT);
}

/*Enable polygon smooth server-side GL capability, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back*/
inline void enablePolygonSmooth()
{
	_enable(GL_POLYGON_SMOOTH);
}

/*Enable sample alpha to coverage server-side GL capability, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value*/
inline void enableSampleAlphaToCoverage()
{
	_enable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Enable sample alpha to one server-side GL capability, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value*/
inline void enableSampleAlphaToOne()
{
	_enable(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Enable sample coverage server-side GL capability, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value*/
inline void enableSampleCoverage()
{
	_enable(GL_SAMPLE_COVERAGE);
}

/*Enable scissor test server-side GL capability, initially disabled. If enabled, discard fragments that are outside the scissor rectangle*/
inline void enableScissorTest()
{
	_enable(GL_SCISSOR_TEST);
}

/*Enable stencil test server-side GL capability, initially disabled. If enabled, do stencil testing and update the stencil buffer*/
inline void enableStencilTest()
{
	_enable(GL_STENCIL_TEST);
}

/*Block until all GL execution is complete*/
void finish();

/*Force execution of GL commands in finite time*/
void flush();

/*Define front- and back-facing polygons
@param Specifies the orientation of front-facing polygons. The initial value is <CCW>*/
void frontFace(FrontFaceMode mode);

/*Returns the index value of an active multitexture unit ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1
@return The active multitexture unit index value*/
inline TextureUnit getActiveTexture()
{
	return _getInteger(GL_ACTIVE_TEXTURE) - GL_TEXTURE0;
}

/*Gets two values indicating the range of widths supported for aliased lines
@param Two values indicating the range of widths*/
inline void getAliasedLineWidthRange(_Out_writes_(2) GLfloat* widths)
{
	_getFloat(GL_ALIASED_LINE_WIDTH_RANGE, widths);
}

/*Gets a boolean value indicating whether blending is enabled. The initial value is false
@return True if blending is enabled, false otherwise*/
inline GLboolean getBlend()
{
	return _getBoolean(GL_BLEND);
}

/*Gets four float values, the red, green, blue and alpha which are the components of the blend color
@param [out] Pointer to store the four blend color values. Initially the blend color is set to (0.0, 0.0, 0.0, 0.0)*/
inline void getBlendColor(_Out_writes_(4) GLfloat* color)
{
	_getFloat(GL_BLEND_COLOR, color);
}

/*Gets previously set value indicating the alpha destination blend function scale factor. The initial value is <Zero>
@return The alpha destination blend function scale factor*/
inline BlendFuncFactor getBlendDstAlpha()
{
	return (BlendFuncFactor)_getInteger(GL_BLEND_DST_ALPHA);
}

/*Gets previously set value indicating the RGB destination blend function scale factor. The initial value is <Zero>
@return The RGB destination blend function scale factor*/
inline BlendFuncFactor getBlendDstRGB()
{
	return (BlendFuncFactor)_getInteger(GL_BLEND_DST_RGB);
}

/*Gets previously set value indicating the alpha blend equation mode
@return The alpha blend equation mode*/
inline BlendEquationMode getBlendEquationAlpha()
{
	return (BlendEquationMode)_getInteger(GL_BLEND_EQUATION_ALPHA);
}

/*Gets previously set value indicating the RGB blend equation mode
@return The RGB blend equation mode*/
inline BlendEquationMode getBlendEquationRGB()
{
	return (BlendEquationMode)_getInteger(GL_BLEND_EQUATION_RGB);
}

/*Gets previously set value indicating the alpha source blend function scale factor. The initial value is <One>
@return The alpha source blend function scale factor*/
inline BlendFuncFactor getBlendSrcAlpha()
{
	return (BlendFuncFactor)_getInteger(GL_BLEND_SRC_ALPHA);
}

/*Gets previously set value indicating the RGB source blend function scale factor. The initial value is <One>
@return The RGB source blend function scale factor*/
inline BlendFuncFactor getBlendSrcRGB()
{
	return (BlendFuncFactor)_getInteger(GL_BLEND_SRC_RGB);
}

/*(1) Gets four integer linearly mapped values used to clear the color buffers
@param [out] Pointer to store the four integer values: red, green, blue, and alpha. The initial value is (0, 0, 0, 0)*/
inline void getColorClearValue(_Out_writes_(4) GLint* color)
{
	_getInteger(GL_COLOR_CLEAR_VALUE, color);
}

/*(2) Gets four float values used to clear the color buffers
@param [out] Pointer to store the four float values: red, green, blue, and alpha. The initial value is (0.0, 0.0, 0.0, 0.0)*/
inline void getColorClearValue(_Out_writes_(4) GLfloat* color)
{
	_getFloat(GL_COLOR_CLEAR_VALUE, color);
}

/*Gets a boolean value indicating whether a fragment's RGBA color values are merged into the framebuffer using a logical operation. The initial value is false
@return True if color logic operation is enabled, false otherwise*/
inline GLboolean getColorLogicOp()
{
	return _getBoolean(GL_COLOR_LOGIC_OP);
}

/*Gets four boolean values: the red, green, blue, and alpha write enables for the color buffers
@param [out] Pointer to store the four boolean values: the red, green, blue, and alpha. The initial value is (True, True, True, True)*/
inline void getColorWritemask(_Out_writes_(4) GLboolean* masks)
{
	_getBoolean(GL_COLOR_WRITEMASK, masks);
}

/*Returns a list of symbolic constants of length returned by <getNumCompressedTextureFormats> indicating which compressed texture formats are available
@param [out] Pointer to an array of available compressed texture formats*/
inline void getCompressedTextureFormats(_Out_ CompressedTexInternalformat* internalformats)
{
	_getInteger(GL_COMPRESSED_TEXTURE_FORMATS, (GLint*)internalformats);
}

/*Gets a boolean value indicating whether polygon culling is enabled. The initial value is false
@return True if polygon culling is enabled, false otherwise*/
inline GLboolean getCullFace()
{
	_getBoolean(GL_CULL_FACE);
}

/*Gets previously set value indicating the mode of polygon culling. The initial value is <Back>
@return The mode of polygon culling value*/
inline FaceMode getCullFaceMode()
{
	return (FaceMode)_getInteger(GL_CULL_FACE_MODE);
}

/*Gets the float value used to clear the depth buffer
@return The default float depth clear value. The initial value is 1.0*/
inline GLdouble getDepthClearValue()
{
	return _getDouble(GL_DEPTH_CLEAR_VALUE);
}

/*Gets previously set value indicating the depth comparison function. The initial value is <Less>
@return The depth comparison function value*/
inline CompareFunc getDepthFunc()
{
	return (CompareFunc)_getInteger(GL_DEPTH_FUNC);
}

/*Gets two float values: the near and far mapping limits for the depth buffer
@param [out] Pointer to store the two mapping limits. The initial value is (0.0, 1.0)*/
inline void getDepthRange(_Out_writes_(2) GLdouble* mapping)
{
	_getDouble(GL_DEPTH_RANGE, mapping);
}

/*Gets the boolean value indicating whether depth testing of fragments is enabled
@return True if depth testing of fragments is enabled, false otherwise*/
inline GLboolean getDepthTest()
{
	return _getBoolean(GL_DEPTH_TEST);
}

/*Gets the boolean value indicating if the depth buffer is enabled for writing. The initial value is true
@return True if depth buffer is enabled for writing, false otherwise*/
inline GLboolean getDepthWritemask()
{
	return _getBoolean(GL_DEPTH_WRITEMASK);
}

/*Gets a boolean value indicating whether dithering of fragment colors and indices is enabled. The initial value is false
@return True if dithering is enabled, false otherwise*/
inline GLboolean getDither()
{
	return _getBoolean(GL_DITHER);
}

/*Returns a single boolean value indicating whether double buffering is supported
@return True if double buffering is supported, false otherwise*/
inline GLboolean getDoublebuffer()
{
	return _getBoolean(GL_DOUBLEBUFFER);
}

/*(1) Gets a boolean value indicating whether double buffering is supported
@return True if double buffering is supported, false otherwise*/
inline DrawBufferUnit getDrawBuffer()
{
	return (DrawBufferUnit)_getInteger(GL_DRAW_BUFFER);
}

/*Gets previously set value indicating the orientation of front-facing polygons. The initial value is <CCW>
@return The orientation of front-facing polygons mode value*/
inline FrontFaceMode getFrontFace()
{
	return (FrontFaceMode)_getInteger(GL_FRONT_FACE);
}

/*Gets a symbolic constant indicating the mode of the derivative accuracy hint for fragment shaders
@return The desired behavior hint. The initial value is <DontCare>*/
inline BehaviorHint getFragmentShaderDerivativeHint()
{
	return (BehaviorHint)_getInteger(GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
}

/*Gets a boolean value indicating whether antialiasing of lines is enabled. The initial value is false
@return True if line smoothing is enabled, false otherwise*/
inline GLboolean getLineSmooth()
{
	return _getBoolean(GL_LINE_SMOOTH);
}

/*Gets a symbolic constant indicating the mode of the line antialiasing hint
@return The desired behavior hint. The initial value is <DontCare>*/
inline BehaviorHint getLineSmoothHint()
{
	return (BehaviorHint)_getInteger(GL_LINE_SMOOTH_HINT);
}

/*Gets the line width as specified with <lineWidth>. The initial value is 1
@return The line width in pixels*/
inline GLfloat getLineWidth()
{
	return _getFloat(GL_LINE_WIDTH);
}

/*Gets a symbolic constant indicating the selected logic operation mode
@return Logic operation mode. The initial value is <Copy>*/
inline LogicOpMode getLogicOpMode()
{
	return (LogicOpMode)_getInteger(GL_LOGIC_OP_MODE);
}

/*Gets a rough estimate of the largest 3D texture that the GL can handle
@return The maximum 3D texture size. The value must be at least 64*/
inline GLsizei getMax3DTextureSize()
{
	return _getInteger(GL_MAX_3D_TEXTURE_SIZE);
}

/*Gets the maximum supported texture image units that can be used to access texture maps from the vertex shader and the fragment processor combined
@return The maximum supported texture image units. The value must be at least 48*/
inline GLuint getMaxCombinedTextureImageUnits()
{
	return _getInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

/*Returns a rough estimate of the largest cube-map texture that the GL can handle
@paran The maximum cube-map texture size. The value must be at least 1024*/
inline GLsizei getMaxCubeMapTextureSize()
{
	return _getInteger(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
}

/*Gets the maximum number of simultaneous outputs that may be written in a fragment shader. The value must be at least 8
@return The maximum number of draw buffers*/
inline GLuint getMaxDrawBuffers()
{
	return _getInteger(GL_MAX_DRAW_BUFFERS);
}

/*Gets the recommended maximum number of vertex array indices for <drawRangeElements>
@return The maximum elements indices value*/
inline GLuint getMaxElementsIndices()
{
	return _getInteger(GL_MAX_ELEMENTS_INDICES);
}

/*Gets the recommended maximum number of vertex array vertices for <drawRangeElements>
@return The maximum elements vertices value*/
inline GLuint getMaxElementsVertices()
{
	return _getInteger(GL_MAX_ELEMENTS_VERTICES);
}

/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a fragment shader
@return The maximum fragment uniform components. The value must be at least 1024*/
inline GLuint getMaxFragmentUniformComponents()
{
	return _getInteger(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
}

/*Gets the maximum supported texture image units that can be used to access texture maps from the fragment shader
@return The maximum supported texture image units. The value must be at least 16*/
inline GLuint getMaxTextureImageUnits()
{
	return _getInteger(GL_MAX_TEXTURE_IMAGE_UNITS);
}

/*Gets absolute value of the texture level-of-detail bias
@return The maximum texture level-of-detail bias. The value must be at least 2.0*/
inline GLfloat getMaxTextureLodBias()
{
	return _getFloat(GL_MAX_TEXTURE_LOD_BIAS);
}

/*Gets the value that gives a rough estimate of the largest 1D texture that the GL can handle
@return The maximum texture size. The value must be at least 1024*/
inline GLsizei getMaxTextureSize()
{
	return _getInteger(GL_MAX_TEXTURE_SIZE);
}

/*Gets the maximum number of interpolators available for processing varying variables used by vertex and fragment shaders. This value represents the number of individual floating-point values that can be interpolated; varying variables declared as vectors, matrices, and arrays will all consume multiple interpolators
@return The maximum number of varying interpolators. The value must be at least 32*/
inline GLuint getMaxVaryingFloats()
{
	return _getInteger(GL_MAX_VARYING_FLOATS);
}

/*Returns the maximum number of 4-component generic vertex attributes accessible to a vertex shader
@return The maximum vertex attributes. The value must be at least 16*/
inline GLuint getMaxVertexAttribs()
{
	return _getInteger(GL_MAX_VERTEX_ATTRIBS);
}

/*Returns the maximum supported texture image units that can be used to access texture maps from the vertex shader
@return The maximum supported vertex texture image units. The value must be at least 16*/
inline GLuint getMaxVertexTextureImageUnits()
{
	return _getInteger(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
}

/*Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a vertex shader
@return The maximum vertex uniform components. The value must be at least 1024*/
inline GLuint getMaxVertexUniformComponents()
{
	return _getInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
}

/*Gets the two values, the maximum supported width and height of the viewport
@param [out] Pointer to store the two maximum viewport dimentions*/
inline void getMaxViewportDims(_Out_writes_(2) GLint* dims)
{
	_getInteger(GL_MAX_VIEWPORT_DIMS, dims);
}

/*Gets the number of available compressed texture formats
@return number of available compressed texture formats. The minimum value is 4*/
inline GLuint getNumCompressedTextureFormats()
{
	return _getInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
}

/*Gets the byte alignment used for writing pixel data to memory
@return The pack alignment pixel storage mode. The initial value is <Four>*/
inline PixelAlignment getPackAlignment()
{
	return (PixelAlignment)_getInteger(GL_PACK_ALIGNMENT);
}

/*Gets the image height used for writing pixel data to memory
@return The pack image height pixel storage mode. The initial value is 0*/
inline GLint getPackImageHeight()
{
	return _getInteger(GL_PACK_IMAGE_HEIGHT);
}

/*Gets a boolean value indicating whether single-bit pixels being written to memory are written first to the least significant bit of each unsigned byte
@return The pack LSB first pixel storage mode. The initial value is false*/
inline GLboolean getPackLsbFirst()
{
	return _getBoolean(GL_PACK_LSB_FIRST);
}

/*Gets the row length used for writing pixel data to memory
@return The pack row length pixel storage mode. The initial value is 0*/
inline GLint getPackRowLength()
{
	return _getInteger(GL_PACK_ROW_LENGTH);
}

/*Gets the number of pixel images skipped before the first pixel is written into memory
@return The pack skip images pixel storage mode. The initial value is 0*/
inline GLint getPackSkipImages()
{
	return _getInteger(GL_PACK_SKIP_IMAGES);
}

/*Gets the number of pixel locations skipped before the first pixel is written into memory
@return The pack skip pixels pixel storage mode. The initial value is 0*/
inline GLint getPackSkipPixels()
{
	return _getInteger(GL_PACK_SKIP_PIXELS);
}

/*Gets the number of rows of pixel locations skipped before the first pixel is written into memory
@return The pack skip rows pixel storage mode. The initial value is 0*/
inline GLint getPackSkipRows()
{
	return _getInteger(GL_PACK_SKIP_ROWS);
}

/*Gets a boolean value indicating whether the bytes of two-byte and four-byte pixel indices and components are swapped before being written to memory
@return The pack swap bytes pixel storage mode. The initial value is false*/
inline GLboolean getPackSwapBytes()
{
	return _getBoolean(GL_PACK_SWAP_BYTES);
}

/*Gets the point size threshold for determining the point size
@return The point size threshold. The default value is 1.0*/
inline GLfloat getPointFadeThresholdSize()
{
	return _getFloat(GL_POINT_FADE_THRESHOLD_SIZE);
}

/*Gets the point size as specified by <pointSize>
@return The point size. The initial value is 1*/
inline GLfloat getPointSize()
{
	return _getFloat(GL_POINT_SIZE);
}

/*Gets the size difference between adjacent supported sizes for antialiased points
@return The point size granularity*/
inline GLfloat getPointSizeGranularity()
{
	return _getFloat(GL_POINT_SIZE_GRANULARITY);
}

/*Gets two values, the smallest and largest supported sizes for antialiased points. The smallest size must be at most 1.0, and the largest size must be at least 1.0
@param The point size range*/
inline void getPointSizeRange(_Out_writes_(2) GLfloat* range)
{
	_getFloat(GL_POINT_SIZE_RANGE, range);
}

/*Gets the point sprite texture coordinate origin
@param The point sprite texture coordinate origin. The default value is <UpperLeft>*/
inline PointSpriteCoordOrigin getPointSpriteCoordOrigin()
{
	return (PointSpriteCoordOrigin)_getInteger(GL_POINT_SPRITE_COORD_ORIGIN);
}

/*Gets the scaling factor used to determine the variable offset that is added to the depth value of each fragment generated when a polygon is rasterized. The value is set by <polygonOffset>
@return The polygon offset scaling factor. The initial value is 0.0*/
inline GLfloat getPolygonOffsetFactor()
{
	return _getFloat(GL_POLYGON_OFFSET_FACTOR);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in fill mode
@return True if polygon fill offset is enabled. The initial value is false*/
inline GLboolean getPolygonOffsetFill()
{
	return  _getBoolean(GL_POLYGON_OFFSET_FILL);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in line mode
@return True if polygon line offset is enabled. The initial value is false*/
inline GLboolean getPolygonOffsetLine()
{
	return _getBoolean(GL_POLYGON_OFFSET_LINE);
}

/*Gets a boolean value indicating whether polygon offset is enabled for polygons in point mode
@return True if polygon point offset is enabled. The initial value is false*/
inline GLboolean getPolygonOffsetPoint()
{
	return _getBoolean(GL_POLYGON_OFFSET_POINT);
}

/*Gets the value which is multiplied by an implementation-specific value and then added to the depth value of each fragment generated when a polygon is rasterized. The value is set by <polygonOffset>
@return The polygon offset units value. The initial value is 0.0*/
inline GLfloat getPolygonOffsetUnits()
{
	return _getFloat(GL_POLYGON_OFFSET_UNITS);
}

/*Gets a boolean value indicating whether antialiasing of polygons is enabled
@return True if polygon point smoothing is enabled. The initial value is false*/
inline GLboolean getPolygonSmooth()
{
	return _getBoolean(GL_POLYGON_SMOOTH);
}

/*Gets a symbolic constant indicating the mode of the polygon antialiasing hint
@return The desired behavior hint. The initial value is <DontCare>*/
inline BehaviorHint getPolygonSmoothHint()
{
	return (BehaviorHint)_getInteger(GL_POLYGON_SMOOTH_HINT);
}

/*Gets a symbolic constant set by <readBuffer> indicating which color buffer is selected for reading. The initial value is <Back> if there is a back buffer, <Front> otherwise
@return The selected color buffer mode*/
inline ReadBufferUnit getReadBuffer()
{
	return (ReadBufferUnit)_getInteger(GL_READ_BUFFER);
}

/*Returns the name of the renderer. This name is typically specific to a particular configuration of a hardware platform. It does not change from release to release
@return The string value of the renderer*/
inline const GLubyte* getRenderer()
{
	return _getString(GL_RENDERER);
}

/*Gets an integer value indicating the number of sample buffers associated with the framebuffer
@return The number of sample buffers*/
inline GLint getSampleBuffers()
{
	return _getInteger(GL_SAMPLE_BUFFERS);
}

/*Gets a boolean value indicating the temporary coverage value invertion flag set by <sampleCoverage>
@return True if the temporary coverage value should be inverted, false otherwise*/
inline GLboolean getSampleCoverageInvert()
{
	return _getBoolean(GL_SAMPLE_COVERAGE_INVERT);
}

/*Gets a positive floating-point value indicating the current sample coverage value set by <sampleCoverage>
@return The sample coverage value. The initial value is 1.0*/
inline GLfloat getSampleCoverageValue()
{
	return _getFloat(GL_SAMPLE_COVERAGE_VALUE);
}

/*Gets an integer value indicating the coverage mask size used by <sampleCoverage>
@return The coverage mask size*/
inline GLuint getSamples()
{
	return _getInteger(GL_SAMPLES);
}

/*Gets four values: the x and y window coordinates of the scissor box, followed by its width and height. Initially the x and y window coordinates are both 0 and the width and height are set to the size of the window
@param [out] The scissor box position and size*/
inline void getScissorBox(_Out_writes_(4) GLint* box)
{
	_getInteger(GL_SCISSOR_BOX, box);
}

/*Gets a boolean value indicating whether scissoring is enabled
@return True if the scissoring is enabled. The initial value is false*/
inline GLboolean getScissorTest()
{
	return _getBoolean(GL_SCISSOR_TEST);
}

/*Returns a version or release number for the shading language
@return The string value of the shading language version*/
inline const GLubyte* getShadingLanguageVersion()
{
	return _getString(GL_SHADING_LANGUAGE_VERSION);
}

/*Gets the level of quantization applied to smooth line width parameters
@return The level of quantization for line width parameters*/
inline GLfloat getSmoothLineWidthGranularity()
{
	return _getFloat(GL_SMOOTH_LINE_WIDTH_GRANULARITY);
}

/*Gets a pair of values indicating the range of widths supported for smooth (antialiased) lines
@param [out] Two values indicating the range of widths*/
inline void getSmoothLineWidthRange(_Out_writes_(2) GLfloat* widths)
{
	_getFloat(GL_SMOOTH_LINE_WIDTH_RANGE, widths);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test fails
@return The stencil back fail operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilBackFail()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_BACK_FAIL);
}

/*Gets symbolic constant indicating what function is used for back-facing polygons to compare the stencil reference value with the stencil buffer value
@return The stencil back function set by <stencilFunc>. The initial value is <Always>*/
inline CompareFunc getStencilBackFunc()
{
	return (CompareFunc)_getInteger(GL_STENCIL_BACK_FUNC);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test passes, but the depth test fails
@return The stencil back pass depth fail operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilBackPassDepthFail()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
}

/*Gets a symbolic constant indicating what action is taken for back-facing polygons when the stencil test passes and the depth test passes
@return The stencil back pass depth pass operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilBackPassDepthPass()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_BACK_PASS_DEPTH_PASS);
}

/*Gets the reference value that is compared with the contents of the stencil buffer for back-facing polygons
@return The stencil back reference value set by <stencilFunc>. The initial value is 0*/
inline GLint getStencilBackRef()
{
	return _getInteger(GL_STENCIL_BACK_REF);
}

/*Gets the mask that is used for back-facing polygons to mask both the stencil reference value and the stencil buffer value before they are compared
@return The stencil back mask value set by <stencilFunc>. The initial value is all 1's*/
inline GLbitfield getStencilBackValueMask()
{
	return _getInteger(GL_STENCIL_BACK_VALUE_MASK);
}

/*Gets the mask that controls writing of the stencil bitplanes for back-facing polygons
@return The stencil back writing mask value set by <stencilMask>. The initial value is all 1's*/
inline GLbitfield getStencilBackWritemask()
{
	return _getInteger(GL_STENCIL_BACK_WRITEMASK);
}

/*Gets the index to which the stencil bitplanes are cleared
@return The default stencil clear value. The initial value is 0*/
inline GLuint getStencilClearValue()
{
	return _getInteger(GL_STENCIL_CLEAR_VALUE);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test fails
@return The stencil fail operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilFail()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_FAIL);
}

/*Gets a symbolic constant indicating what function is used to compare the stencil reference value with the stencil buffer value
@return The stencil function set by <stencilFunc>. The initial value is <Always>*/
inline CompareFunc getStencilFunc()
{
	return (CompareFunc)_getInteger(GL_STENCIL_FUNC);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test passes and the depth test passes
@return The stencil pass depth pass operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilPassDepthPass()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_PASS_DEPTH_PASS);
}

/*Gets a symbolic constant indicating what action is taken when the stencil test passes, but the depth test fails
@return The stencil pass depth fail operation mode. The initial value is <Keep>*/
inline StencilOpMode getStencilPassDepthFail()
{
	return (StencilOpMode)_getInteger(GL_STENCIL_PASS_DEPTH_FAIL);
}

/*Gets the reference value that is compared with the contents of the stencil buffer
@return The stencil reference value set by <stencilFunc>. The initial value is 0*/
inline GLint getStencilRef()
{
	return _getInteger(GL_STENCIL_REF);
}

/*Gets a boolean value indicating whether stencil testing of fragments is enabled
@return True if the stencil testing is enabled. The initial value is false*/
inline GLboolean getStencilTest()
{
	return _getBoolean(GL_STENCIL_TEST);
}

/*Gets the mask that is used to mask both the stencil reference value and the stencil buffer value before they are compared
@return The stencil back mask value set by <stencilFunc>. The initial value is all 1's*/
inline GLbitfield getStencilValueMask()
{
	return _getInteger(GL_STENCIL_VALUE_MASK);
}

/*Gets the mask that controls writing of the stencil bitplanes
@return The stencil writing mask value set by <stencilMask>. The initial value is all 1's*/
inline GLbitfield getStencilWritemask()
{
	return _getInteger(GL_STENCIL_WRITEMASK);
}

/*Gets a boolean value indicating whether stereo buffers (left and right) are supported
@return True if stereo buffers are supported, false otherwise*/
inline GLboolean getStereo()
{
	return _getBoolean(GL_STEREO);
}

/*Gets an estimate of the number of bits of subpixel resolution that are used to position rasterized geometry in window coordinates
@return The subpixel bits. The value must be at least 4*/
inline GLint getSubpixelBits()
{
	return _getInteger(GL_SUBPIXEL_BITS);
}

/*Gets a value indicating the mode of the texture compression hint
@return The desired behavior hint. The initial value is <DontCare>*/
inline BehaviorHint getTextureCompressionHint()
{
	return (BehaviorHint)_getInteger(GL_TEXTURE_COMPRESSION_HINT);
}

/*Gets the byte alignment used for reading pixel data from memory
@return The unpack alignment pixel storage mode. The initial value is <Four>*/
inline PixelAlignment getUnpackAlignment()
{
	return (PixelAlignment)_getInteger(GL_UNPACK_ALIGNMENT);
}

/*Gets the image height used for reading pixel data from memory
@return The unpack image height pixel storage mode. The initial value is 0*/
inline GLint getUnpackImageHeight()
{
	return _getInteger(GL_UNPACK_IMAGE_HEIGHT);
}

/*Gets a boolean value indicating whether single-bit pixels being read from memory are read first from the least significant bit of each unsigned byte
@return The unpack LSB first pixel storage mode. The initial value is false*/
inline GLboolean getUnpackLsbFirst()
{
	return _getBoolean(GL_UNPACK_LSB_FIRST);
}

/*Gets the row length used for reading pixel data from memory.
@return The unpack row length pixel storage mode. The initial value is 0*/
inline GLint getUnpackRowLength()
{
	return _getInteger(GL_UNPACK_ROW_LENGTH);
}

/*Gets the number of pixel images skipped before the first pixel is read from memory
@return The unpack skip images pixel storage mode. The initial value is 0*/
inline GLint getUnpackSkipImages()
{
	return _getInteger(GL_UNPACK_SKIP_IMAGES);
}

/*Gets the number of pixel locations skipped before the first pixel is read from memory
@return The unpack skip pixels pixel storage mode. The initial value is 0*/
inline GLint getUnpackSkipPixels()
{
	return _getInteger(GL_UNPACK_SKIP_PIXELS);
}

/*Gets the number of rows of pixel locations skipped before the first pixel is read from memory
@return The unpack skip rows pixel storage mode. The initial value is 0*/
inline GLint getUnpackSkipRows()
{
	return _getInteger(GL_UNPACK_SKIP_ROWS);
}

/*Gets a boolean value indicating whether the bytes of two-byte and four-byte pixel indices and components are swapped after being read from memory
@return The unpack swap bytes pixel storage mode. The initial value is false*/
inline GLboolean getUnpackSwapBytes()
{
	return _getBoolean(GL_UNPACK_SWAP_BYTES);
}

/*Returns the company responsible for this GL implementation. This name does not change from release to release
@return The string value of the vendor*/
inline const GLubyte* getVendor()
{
	return _getString(GL_VENDOR);
}

/*Returns a version or release number
@return The string value of the version*/
inline const GLubyte* getVersion()
{
	return _getString(GL_VERSION);
}

/*Gets the four viewport values: the x and y window coordinates of the viewport, followed by its width and height
@param [out] Pointer to store the four viewport values. Initiall values are: 0, 0, width and height of the window rendered by GL*/
inline void getViewport(_Out_writes_(4) GLint* viewport)
{
	_getInteger(GL_VIEWPORT, viewport);
}

/*Checks if blend server-side GL capability is enabled, initially disabled. If enabled, blend the computed fragment color values with the values in the color buffers
@return True if blend GL capability is enabled, false otherwise*/
inline GLboolean isBlend()
{
	return _isEnabled(GL_BLEND);
}

/*Checks if color logic operation server-side GL capability is enabled, initially disabled. If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values
@return True if color logic operation GL capability is enabled, false otherwise*/
inline GLboolean isColorLogicOp()
{
	return _isEnabled(GL_COLOR_LOGIC_OP);
}

/*Checks if cull face server-side GL capability is enabled, initially disabled. If enabled, cull polygons based on their winding in window coordinates
@return True if cull face GL capability is enabled, false otherwise*/
inline GLboolean isCullFace()
{
	return _isEnabled(GL_CULL_FACE);
}

/*Checks if depth test server-side GL capability is enabled, initially disabled. If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled
@return True if depth test GL capability is enabled, false otherwise*/
inline GLboolean isDepthTest()
{
	return _isEnabled(GL_DEPTH_TEST);
}

/*Checks if dither server-side GL capability is enabled, initially enabled. If enabled, dither color components or indices before they are written to the color buffer
@return True if dither GL capability is enabled, false otherwise*/
inline GLboolean isDither()
{
	return _isEnabled(GL_DITHER);
}

/*Checks if line smooth server-side GL capability is enabled, initially disabled. If enabled, draw lines with correct filtering. Otherwise, draw aliased lines
@return True if line smooth GL capability is enabled, false otherwise*/
inline GLboolean isLineSmooth()
{
	return _isEnabled(GL_LINE_SMOOTH);
}

/*Checks if multisample server-side GL capability is enabled, initially disabled. If enabled, use multiple fragment samples in computing the final color of a pixel
@return True if multisample GL capability is enabled, false otherwise*/
inline GLboolean isMultisample()
{
	return _isEnabled(GL_MULTISAMPLE);
}

/*Checks if polygon offset fill server-side GL capability is enabled, initially disabled. If enabled, and if the polygon is rendered in <Fill> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed
@return True if polygon offset fill GL capability is enabled, false otherwise*/
inline GLboolean isPolygonOffsetFill()
{
	return _isEnabled(GL_POLYGON_OFFSET_FILL);
}

/*Checks if polygon offset line server-side GL capability is enabled, initially disabled. If enabled, and if the polygon is rendered in <Line> mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed
@return True if polygon offset line GL capability is enabled, false otherwise*/
inline GLboolean isPolygonOffsetLine()
{
	return _isEnabled(GL_POLYGON_OFFSET_LINE);
}

/*Checks if polygon offset point server-side GL capability is enabled, initially disabled. If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in <Point> mode
@return True if polygon offset point GL capability is enabled, false otherwise*/
inline GLboolean isPolygonOffsetPoint()
{
	return _isEnabled(GL_POLYGON_OFFSET_POINT);
}

/*Checks if polygon smooth server-side GL capability is enabled, initially disabled. If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back
@return True if polygon smooth GL capability is enabled, false otherwise*/
inline GLboolean isPolygonSmooth()
{
	return _isEnabled(GL_POLYGON_SMOOTH);
}

/*Checks if sample alpha to coverage server-side GL capability is enabled, initially disabled. If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then AND'ed with the fragment coverage value
@return True if sample alpha to coverage GL capability is enabled, false otherwise*/
inline GLboolean isSampleAlphaToCoverage()
{
	return _isEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/*Checks if sample alpha to one server-side GL capability is enabled, initially disabled. If enabled, each sample alpha value is replaced by the maximum representable alpha value
@return True if sample alpha to one GL capability is enabled, false otherwise*/
inline GLboolean isSampleAlphaToOne()
{
	return _isEnabled(GL_SAMPLE_ALPHA_TO_ONE);
}

/*Checks if sample coverage server-side GL capability is enabled, initially disabled. If enabled, the fragment's coverage is AND'ed with the temporary coverage value. If <SampleCoverage>'s invert patameter is set to true, invert the coverage value
@return True if sample coverage GL capability is enabled, false otherwise*/
inline GLboolean isSampleCoverage()
{
	return _isEnabled(GL_SAMPLE_COVERAGE);
}

/*Checks if scissor test server-side GL capability is enabled, initially disabled. If enabled, discard fragments that are outside the scissor rectangle
@return True if scissor test GL capability is enabled, false otherwise*/
inline GLboolean isScissorTest()
{
	return _isEnabled(GL_SCISSOR_TEST);
}

/*Checks if stencil test server-side GL capability is enabled, initially disabled. If enabled, do stencil testing and update the stencil buffer
@return True if stencil test GL capability is enabled, false otherwise*/
inline GLboolean isStencilTest()
{
	return _isEnabled(GL_STENCIL_TEST);
}

/*Specifies the width of rasterized lines
@param Specifies the width of rasterized lines. The initial value is 1*/
void lineWidth(GLfloat width);

/*Specifies a logical pixel operation for rendering
@param Specifies a symbolic constant that selects a logical operation. The initial value is <Copy>*/
void logicOp(LogicOpMode opcode);

/*Render multiple sets of primitives from array data
@param Specifies what kind of primitives to render
@param [in] Pointer to an array of starting indices in the enabled arrays
@param [in] Pointer to an array of the number of indices to be rendered
@param Specifies the size of the first and count arrays*/
void multiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount);

/*Render multiple sets of primitives by specifying indices of array data elements
@param Specifies what kind of primitives to render
@param [in] Pointer to an array of the elements counts
@param Specifies the type of the values in indices
@param [in] Pointer to an array of the byte offsets into the element array index buffer object's data store
@param Specifies the size of the count and indices arrays*/
void multiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount);

/*Specifies the diameter of rasterized points
@param Specifies the diameter of rasterized points. The initial value is 1.0*/
void pointSize(GLfloat size);

/*Select a polygon rasterization mode
@param Specifies how polygons will be rasterized. The initial value is <Fill>*/
void polygonMode(PolygonMode mode);

/*Set the scale and units used to calculate depth values
@param Specifies a scale factor that is used to create a variable depth offset for each polygon. The initial value is 0
@param Is multiplied by an implementation-specific value to create a constant depth offset. The initial value is 0*/
void polygonOffset(GLfloat factor, GLfloat units);

/*Select a color buffer source for pixels
@param Specifies a color buffer*/
void readBuffer(ReadBufferUnit mode);

/*Specifies multisample coverage parameters
@param Specifies a single floating-point sample coverage value. The initial value is 1.0
@param True if the coverage masks should be inverted, initial value is false*/
void sampleCoverage(GLfloat value, GLboolean invert);

/*Define the scissor box. When a GL context is first attached to a window, width and height are set to the dimensions of that window
@param Specifies the lower left corner x coordinate of the scissor box. Initially 0
@param Specifies the lower left corner y coordinate of the scissor box. Initially 0
@param Specifies the width of the scissor box
@param Specifies the height of the scissor box*/
void scissor(GLint x, GLint y, GLsizei width, GLsizei height);

/*Set the accuracy of the derivative calculation for the GL shading language fragment processing built-in functions: dFdx, dFdy, and fwidth
@param Specifies a symbolic constant indicating the desired behavior*/
inline void setFragmentShaderDerivativeHint(BehaviorHint hint)
{
	_hint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, (GLenum)hint);
}

/*Indicates the sampling quality of antialiased lines. If a larger filter function is applied, hinting <Nicest> can result in more pixel fragments being generated during rasterization
@param Specifies a symbolic constant indicating the desired behavior*/
inline void setLineSmoothHint(BehaviorHint hint)
{
	_hint(GL_LINE_SMOOTH_HINT, (GLenum)hint);
}

/*Set pack alignment pixel storage mode
@param Specifies the alignment requirements for the start of each pixel row in memory*/
inline void setPackAlignment(PixelAlignment swap)
{
	_pixelStore(GL_PACK_ALIGNMENT, (GLint)swap);
}

/*(1) Set pack image height pixel storage mode
@param If greater than 0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void setPackImageHeight(GLint height)
{
	_pixelStore(GL_PACK_IMAGE_HEIGHT, height);
}

/*(2) Set pack image height pixel storage mode
@param If greater than 0.0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void setPackImageHeight(GLfloat height)
{
	_pixelStore(GL_PACK_IMAGE_HEIGHT, height);
}

/*Set pack LSB first pixel storage mode
@param If true, bits are ordered within a byte from least significant to most significant. Otherwise, the first bit in each byte is the most significant one*/
inline void setPackLsbFirst(GLboolean swap)
{
	_pixelStore(GL_PACK_LSB_FIRST, swap);
}

/*(1) Set pack row length pixel storage mode
@param If greater than 0, defines the number of pixels in a row*/
inline void setPackRowLength(GLint length)
{
	_pixelStore(GL_PACK_ROW_LENGTH, length);
}

/*(2) Set pack row length pixel storage mode
@param If greater than 0.0, defines the number of pixels in a row*/
inline void setPackRowLength(GLfloat length)
{
	_pixelStore(GL_PACK_ROW_LENGTH, length);
}

/*(1) Set pack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void setPackSkipImages(GLint skip)
{
	_pixelStore(GL_PACK_SKIP_IMAGES, skip);
}

/*(2) Set pack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void setPackSkipImages(GLfloat skip)
{
	_pixelStore(GL_PACK_SKIP_IMAGES, skip);
}

/*(1) Set pack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void setPackSkipPixels(GLint skip)
{
	_pixelStore(GL_PACK_SKIP_PIXELS, skip);
}

/*(2) Set pack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void setPackSkipPixels(GLfloat skip)
{
	_pixelStore(GL_PACK_SKIP_PIXELS, skip);
}

/*(1) Set pack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void setPackSkipRows(GLint skip)
{
	_pixelStore(GL_PACK_SKIP_ROWS, skip);
}

/*(2) Set pack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void setPackSkipRows(GLfloat skip)
{
	_pixelStore(GL_PACK_SKIP_ROWS, skip);
}

/*Set pack swap bytes pixel storage mode
@param If true, byte ordering for multibyte color components, depth components, or stencil indices is reversed*/
inline void setPackSwapBytes(GLboolean swap)
{
	_pixelStore(GL_PACK_SWAP_BYTES, swap);
}

/*Set the threshold value to which point sizes are clamped if they exceed the specified value
@param The point threshold size. The default value is 1.0*/
void setPointFadeThresholdSize(GLfloat size);

/*Set the point sprite texture coordinate origin
@param The point sprite texture coordinate origin. The default value is <UpperLeft>*/
void setPointSpriteCoordOrigin(PointSpriteCoordOrigin origin);

/*Indicates the sampling quality of antialiased polygons. Hinting <Nicest> can result in more pixel fragments being generated during rasterization, if a larger filter function is applied
@param Specifies a symbolic constant indicating the desired behavior*/
inline void setPolygonSmoothHint(BehaviorHint hint)
{
	_hint(GL_POLYGON_SMOOTH_HINT, (GLenum)hint);
}

/*Indicates the quality and performance of the compressing texture images. Hinting <Fastest> indicates that texture images should be compressed as quickly as possible, while <Nicest> indicates that texture images should be compressed with as little image quality loss as possible
@param Specifies a symbolic constant indicating the desired behavior*/
inline void setTextureCompressionHint(BehaviorHint hint)
{
	_hint(GL_TEXTURE_COMPRESSION_HINT, (GLenum)hint);
}

/*Set unpack alignment pixel storage mode
@param Specifies the alignment requirements for the start of each pixel row in memory*/
inline void setUnpackAlignment(PixelAlignment swap)
{
	_pixelStore(GL_UNPACK_ALIGNMENT, (GLint)swap);
}

/*(1) Set unpack image height pixel storage mode
@param If greater than 0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void setUnpackImageHeight(GLint height)
{
	_pixelStore(GL_UNPACK_IMAGE_HEIGHT, height);
}

/*(2) Set unpack image height pixel storage mode
@param If greater than 0.0, defines the number of pixels in an image three-dimensional texture volume, where image is defined by all pixels sharing the same third dimension index*/
inline void setUnpackImageHeight(GLfloat height)
{
	_pixelStore(GL_UNPACK_IMAGE_HEIGHT, height);
}

/*Set unpack LSB first pixel storage mode
@param If true, bits are ordered within a byte from least significant to most significant. Otherwise, the first bit in each byte is the most significant one*/
inline void setUnpackLsbFirst(GLboolean swap)
{
	_pixelStore(GL_UNPACK_LSB_FIRST, swap);
}

/*(1) Set unpack row length pixel storage mode
@param If greater than 0, defines the number of pixels in a row*/
inline void setUnpackRowLength(GLint length)
{
	_pixelStore(GL_UNPACK_ROW_LENGTH, length);
}

/*(2) Set unpack row length pixel storage mode
@param If greater than 0.0, defines the number of pixels in a row*/
inline void setUnpackRowLength(GLfloat length)
{
	_pixelStore(GL_UNPACK_ROW_LENGTH, length);
}

/*(1) Set unpack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void setUnpackSkipImages(GLint skip)
{
	_pixelStore(GL_UNPACK_SKIP_IMAGES, skip);
}

/*(2) Set unpack skip images pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per image*/
inline void setUnpackSkipImages(GLfloat skip)
{
	_pixelStore(GL_UNPACK_SKIP_IMAGES, skip);
}

/*(1) Set unpack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void setUnpackSkipPixels(GLint skip)
{
	_pixelStore(GL_UNPACK_SKIP_PIXELS, skip);
}

/*(2) Set unpack skip pixels pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices in each pixel*/
inline void setUnpackSkipPixels(GLfloat skip)
{
	_pixelStore(GL_UNPACK_SKIP_PIXELS, skip);
}

/*(1) Set unpack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void setUnpackSkipRows(GLint skip)
{
	_pixelStore(GL_UNPACK_SKIP_ROWS, skip);
}

/*(2) Set unpack skip rows pixel storage mode
@param Adds an offset to data pointer, nultiplied by number of components or indices per row*/
inline void setUnpackSkipRows(GLfloat skip)
{
	_pixelStore(GL_UNPACK_SKIP_ROWS, skip);
}

/*Set unpack swap bytes pixel storage mode
@param If true, byte ordering for multibyte color components, depth components, or stencil indices is reversed*/
inline void setUnpackSwapBytes(GLboolean swap)
{
	_pixelStore(GL_UNPACK_SWAP_BYTES, swap);
}

/*Set front and back function and reference value for stencil testing
@param Specifies the test function. The initial value is <Always>
@param Specifies the reference value for the stencil test. The initial value is 0
@param Specifies a mask that is AND'ed with both values when the test is done. The initial value is all 1's*/
void stencilFunc(CompareFunc func, GLint ref, GLuint mask);

/*Set front and/or back function and reference value for stencil testing
@param Specifies whether front and/or back stencil state is updated
@param Specifies the test function. The initial value is <Always>
@param Specifies the reference value for the stencil test. The initial value is 0
@param Specifies a mask that is AND'ed with both values when the test is done. The initial value is all 1's*/
void stencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask);

/*Control the front and back writing of individual bits in the stencil planes
@param Specifies a bit mask to enable and disable writing of individual bits in the stencil planes. Initially, the mask is all 1's*/
void stencilMask(GLuint mask);

/*Control the front and/or back writing of individual bits in the stencil planes
@param Specifies whether the front and/or back stencil writemask is updated
@param Specifies a bit mask to enable and disable writing of individual bits in the stencil planes. Initially, the mask is all 1's*/
void stencilMaskSeparate(FaceMode face, GLuint mask);

/*Set front and back stencil test actions
@param Specifies the action to take when the stencil test fails. The initial value is <Keep>
@param Specifies the action when the stencil test passes, but the depth test fails. The initial value is <Keep>
@param Specifies the action when both tests pass, or when the stencil test passes and either depth buffer is missing or disabled. The initial value is <Keep>*/
void stencilOp(StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass);

/*Set front and/or back stencil test actions
@param Specifies whether front and/or back stencil state is updated
@param Specifies the action to take when the stencil test fails. The initial value is <Keep>
@param Specifies the action when the stencil test passes, but the depth test fails. The initial value is <Keep>
@param Specifies the action when both tests pass, or when the stencil test passes and either depth buffer is missing or disabled. The initial value is <Keep>*/
void stencilOpSeparate(FaceMode face, StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass);

/*Set the viewport
@param Specifies the the x coordinate of a lower left corner of the viewport rectangle, in pixels
@param Specifies the the y coordinate of a lower left corner of the viewport rectangle, in pixels
@param Specifies the width of the viewport
@param Specifies the height of the viewport*/
void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
/*YAGL++ GLAD error checking macro, does nothing in Release mode*/
#define YAGLPP_GLAD_ERROR YAGLPP_ASSERT(_getError())
GLboolean _getError()
{
	GLenum eNumber = glGetError();
	if (eNumber == GL_NO_ERROR) return GL_TRUE;
	do
	{
		const char* zDescription = "UNDEFINED ERROR";
		switch (eNumber)
		{
		case GL_INVALID_ENUM:
			zDescription = "INVALID ENUM";
			break;
		case GL_INVALID_VALUE:
			zDescription = "INVALID VALUE";
			break;
		case GL_INVALID_OPERATION:
			zDescription = "INVALID OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			zDescription = "OUT OF MEMORY";

#ifdef YAGLPP_VERSION_3_0
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			zDescription = "INVALID FRAMEBUFFER OPERATION";
#endif // #ifdef YAGLPP_VERSION_3_0
		}
		std::cout << "GLAD ERROR <" << eNumber << ">: " << zDescription << std::endl;
		eNumber = glGetError();
	} while (eNumber != GL_NO_ERROR);
	return GL_FALSE;
}

void _disable(GLenum cap)
{
	glDisable(cap);
	YAGLPP_GLAD_ERROR;
}

void _enable(GLenum cap)
{
	glEnable(cap);
	YAGLPP_GLAD_ERROR;
}

GLboolean _getBoolean(GLenum pname)
{
	GLboolean bData = GL_FALSE;
	glGetBooleanv(pname, &bData);
	YAGLPP_GLAD_ERROR;
	return bData;
}

void _getBoolean(GLenum pname, GLboolean* data)
{
	glGetBooleanv(pname, data);
	YAGLPP_GLAD_ERROR;
}

GLdouble _getDouble(GLenum pname)
{
	GLdouble dData;
	glGetDoublev(pname, &dData);
	YAGLPP_GLAD_ERROR;
	return dData;
}

void _getDouble(GLenum pname, GLdouble* data)
{
	glGetDoublev(pname, data);
	YAGLPP_GLAD_ERROR;
}

GLfloat _getFloat(GLenum pname)
{
	GLfloat fData;
	glGetFloatv(pname, &fData);
	YAGLPP_GLAD_ERROR;
	return fData;
}

void _getFloat(GLenum pname, GLfloat* data)
{
	glGetFloatv(pname, data);
	YAGLPP_GLAD_ERROR;
}

GLint _getInteger(GLenum pname)
{
	GLint iData;
	glGetIntegerv(pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

void _getInteger(GLenum pname, GLint* data)
{
	glGetIntegerv(pname, data);
	YAGLPP_GLAD_ERROR;
}

void _hint(GLenum target, GLenum mode)
{
	glHint(target, mode);
	YAGLPP_GLAD_ERROR;
}

void _pixelStore(GLenum pname, GLfloat param)
{
	glPixelStoref(pname, param);
	YAGLPP_GLAD_ERROR;
}

void _pixelStore(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
	YAGLPP_GLAD_ERROR;
}

void activeTexture(TextureUnit index)
{
	glActiveTexture(GL_TEXTURE0 + (GLenum)index);
	YAGLPP_GLAD_ERROR;
}

void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glBlendColor(red, green, blue, alpha);
	YAGLPP_GLAD_ERROR;
}

void blendEquation(BlendEquationMode mode)
{
	glBlendEquation((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void blendEquationSeparate(BlendEquationMode modeRGB, BlendEquationMode modeAlpha)
{
	glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
	YAGLPP_GLAD_ERROR;
}

void blendFunc(BlendFuncFactor sfactor, BlendFuncFactor dfactor)
{
	glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
	YAGLPP_GLAD_ERROR;
}

void blendFuncSeparate(BlendFuncFactor srcRGB, BlendFuncFactor dstRGB, BlendFuncFactor srcAlpha, BlendFuncFactor dstAlpha)
{
	glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
	YAGLPP_GLAD_ERROR;
}

void clear(BufferBitMask mask)
{
	glClear((GLbitfield)mask);
	YAGLPP_GLAD_ERROR;
}

void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
	YAGLPP_GLAD_ERROR;
}

void clearDepth(GLdouble depth)
{
	glClearDepth(depth);
	YAGLPP_GLAD_ERROR;
}

void clearStencil(GLint stencil)
{
	glClearStencil(stencil);
	YAGLPP_GLAD_ERROR;
}

void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
	YAGLPP_GLAD_ERROR;
}

void cullFace(FaceMode mode)
{
	glCullFace((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void depthFunc(CompareFunc func)
{
	glDepthFunc((GLenum)func);
	YAGLPP_GLAD_ERROR;
}

void depthMask(GLboolean flag)
{
	glDepthMask(flag);
	YAGLPP_GLAD_ERROR;
}

void depthRange(GLdouble nearVal, GLdouble farVal)
{
	glDepthRange(nearVal, farVal);
	YAGLPP_GLAD_ERROR;
}

void drawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
	glDrawArrays((GLenum)mode, first, count);
	YAGLPP_GLAD_ERROR;
}

void drawBuffer(DrawBufferUnit buf)
{
	glDrawBuffer((GLenum)buf);
	YAGLPP_GLAD_ERROR;
}

void drawBuffers(GLsizei n, _In_reads_(n) const DrawBuffersUnit* bufs)
{
	glDrawBuffers(n, (GLenum*)bufs);
	YAGLPP_GLAD_ERROR;
}

void drawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
	YAGLPP_GLAD_ERROR;
}

void drawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
	YAGLPP_GLAD_ERROR;
}

void finish()
{
	glFinish();
	YAGLPP_GLAD_ERROR;
}

void flush()
{
	glFlush();
	YAGLPP_GLAD_ERROR;
}

void frontFace(FrontFaceMode mode)
{
	glFrontFace((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void lineWidth(GLfloat width)
{
	glLineWidth(width);
	YAGLPP_GLAD_ERROR;
}

void logicOp(LogicOpMode opcode)
{
	glLogicOp((GLenum)opcode);
	YAGLPP_GLAD_ERROR;
}

void multiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
	glMultiDrawArrays((GLenum)mode, first, count, drawcount);
	YAGLPP_GLAD_ERROR;
}

void multiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
	glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
	YAGLPP_GLAD_ERROR;
}

void pointSize(GLfloat size)
{
	glPointSize(size);
	YAGLPP_GLAD_ERROR;
}

void polygonMode(PolygonMode mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void polygonOffset(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
	YAGLPP_GLAD_ERROR;
}

void readBuffer(ReadBufferUnit mode)
{
	glReadBuffer((GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void sampleCoverage(GLfloat value, GLboolean invert)
{
	glSampleCoverage(value, invert);
	YAGLPP_GLAD_ERROR;
}

void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
	YAGLPP_GLAD_ERROR;
}

void setPointFadeThresholdSize(GLfloat size)
{
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
	YAGLPP_GLAD_ERROR;
}

void setPointSpriteCoordOrigin(PointSpriteCoordOrigin origin)
{
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
	YAGLPP_GLAD_ERROR;
}

void stencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFunc((GLenum)func, ref, mask);
	YAGLPP_GLAD_ERROR;
}

void stencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
	YAGLPP_GLAD_ERROR;
}

void stencilMask(GLuint mask)
{
	glStencilMask(mask);
	YAGLPP_GLAD_ERROR;
}

void stencilMaskSeparate(FaceMode face, GLuint mask)
{
	glStencilMaskSeparate((GLenum)face, mask);
	YAGLPP_GLAD_ERROR;
}

void stencilOp(StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
	YAGLPP_GLAD_ERROR;
}

void stencilOpSeparate(FaceMode face, StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
	YAGLPP_GLAD_ERROR;
}

void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
	YAGLPP_GLAD_ERROR;
}
#else // #ifdef YAGLPP_DEBUG_IMPLEMENTATION
#define YAGLPP_GLAD_ERROR
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void _disable(GLenum cap)
{
	glDisable(cap);
}

inline void _enable(GLenum cap)
{
	glEnable(cap);
}

inline GLboolean _getBoolean(GLenum pname)
{
	GLboolean b; glGetBooleanv(pname, &b); return b;
}

inline void _getBoolean(GLenum pname, GLboolean* data)
{
	glGetBooleanv(pname, data);
}

inline GLdouble _getDouble(GLenum pname)
{
	GLdouble d; glGetDoublev(pname, &d); return d;
}

inline void _getDouble(GLenum pname, GLdouble* data)
{
	glGetDoublev(pname, data);
}

inline GLfloat _getFloat(GLenum pname)
{
	GLfloat f; glGetFloatv(pname, &f); return f;
}

inline void _getFloat(GLenum pname, GLfloat* data)
{
	glGetFloatv(pname, data);
}

inline GLint _getInteger(GLenum pname)
{
	GLint i; glGetIntegerv(pname, &i); return i;
}

inline void _getInteger(GLenum pname, GLint* data)
{
	glGetIntegerv(pname, data);
}

inline const GLubyte* _getString(GLenum name)
{
	return glGetString(name);
}

inline void _hint(GLenum target, GLenum mode)
{
	glHint(target, mode);
}

inline GLboolean _isEnabled(GLenum cap)
{
	return glIsEnabled(cap);
}

inline void _pixelStore(GLenum pname, GLfloat param)
{
	glPixelStoref(pname, param);
}

inline void _pixelStore(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
}

inline void activeTexture(TextureUnit index)
{
	glActiveTexture(GL_TEXTURE0 + (GLenum)index);
}

inline void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glBlendColor(red, green, blue, alpha);
}

inline void blendEquation(BlendEquationMode mode)
{
	glBlendEquation((GLenum)mode);
}

inline void blendEquationSeparate(BlendEquationMode modeRGB, BlendEquationMode modeAlpha)
{
	glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
}

inline void blendFunc(BlendFuncFactor sfactor, BlendFuncFactor dfactor)
{
	glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
}

inline void blendFuncSeparate(BlendFuncFactor srcRGB, BlendFuncFactor dstRGB, BlendFuncFactor srcAlpha, BlendFuncFactor dstAlpha)
{
	glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
}

inline void clear(BufferBitMask mask)
{
	glClear((GLbitfield)mask);
}

inline void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
}

inline void clearDepth(GLdouble depth)
{
	glClearDepth(depth);
}

inline void clearStencil(GLint stencil)
{
	glClearStencil(stencil);
}

inline void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
}

inline void cullFace(FaceMode mode)
{
	glCullFace((GLenum)mode);
}

inline void depthFunc(CompareFunc func)
{
	glDepthFunc((GLenum)func);
}

inline void depthMask(GLboolean flag)
{
	glDepthMask(flag);
}

inline void depthRange(GLdouble nearVal, GLdouble farVal)
{
	glDepthRange(nearVal, farVal);
}

inline void drawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
	glDrawArrays((GLenum)mode, first, count);
}

inline void drawBuffer(DrawBufferUnit buf)
{
	glDrawBuffer((GLenum)buf);
}

inline void drawBuffers(GLsizei n, _In_reads_(n) const DrawBuffersUnit* bufs)
{
	glDrawBuffers(n, (GLenum*)bufs);
}

inline void drawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
}

inline void drawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
	glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
}

inline void finish()
{
	glFinish();
}

inline void flush()
{
	glFlush();
}

inline void frontFace(FrontFaceMode mode)
{
	glFrontFace((GLenum)mode);
}

inline void lineWidth(GLfloat width)
{
	glLineWidth(width);
}

inline void logicOp(LogicOpMode opcode)
{
	glLogicOp((GLenum)opcode);
}

inline void multiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
	glMultiDrawArrays((GLenum)mode, first, count, drawcount);
}

inline void multiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
	glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
}

inline void pointSize(GLfloat size)
{
	glPointSize(size);
}

inline void polygonMode(PolygonMode mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
}

inline void polygonOffset(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
}

inline void readBuffer(ReadBufferUnit mode)
{
	glReadBuffer((GLenum)mode);
}

inline void sampleCoverage(GLfloat value, GLboolean invert)
{
	glSampleCoverage(value, invert);
}

inline void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
}

inline void setPointFadeThresholdSize(GLfloat size)
{
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
}

inline void setPointSpriteCoordOrigin(PointSpriteCoordOrigin origin)
{
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
}

inline void stencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFunc((GLenum)func, ref, mask);
}

inline void stencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
}

inline void stencilMask(GLuint mask)
{
	glStencilMask(mask);
}

inline void stencilMaskSeparate(FaceMode face, GLuint mask)
{
	glStencilMaskSeparate((GLenum)face, mask);
}

inline void stencilOp(StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

inline void stencilOpSeparate(FaceMode face, StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

inline void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#ifdef YAGLPP_VERSION_2_1
class PixelPackBuffer;
class PixelUnpackBuffer;
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD clip geometry unit index ranging from 0 to the value returned by <getMaxClipDistances> minus 1*/
typedef unsigned short ClipDistance;

/*(3.0) GLAD color attachment unit index ranging from 0 to the value returned by <getMaxColorAttachments> minus 1*/
typedef unsigned short ColorAttachment;

/*(3.0) GLAD color number index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1*/
typedef unsigned short ColorNumber;

class _Framebuffer;
class DrawFramebuffer;
class Framebuffer;
class Framebuffers;
class PrimitivesGenerated;
class ReadFramebuffer;
class Renderbuffer;
class Renderbuffers;
class Texture1DArray;
class Texture2DArray;
class TransformFeedbackBuffer;
class TransformFeedbackPrimitivesWritten;
class VertexArray;
class VertexArrays;
enum class BufferFlags : GLbitfield;
enum class FramebufferAttachmentType : GLenum;
enum class FramebufferCompletenessStatus : GLenum;
enum class QueryConditionalRenderMode : GLenum;
enum class TextureCompareMode : GLenum;
enum class TextureComponentType : GLenum;
enum class TransformFeedbackBufferMode : GLenum;
enum class VertexAttribISize : GLsizei;
enum class VertexAttribIType : GLenum;

/*(3.0) GLAD clamp color value enumerator*/
enum class ClampColor : GLenum
{
	/*(3.0) Read color clamping is enabled*/
	True = GL_TRUE,

	/*(3.0) Read color clamping is disabled*/
	False = GL_FALSE,

	/*(3.0) Read color clamping is enabled only if the selected read buffer has fixed point components and disabled otherwise*/
	FixedOnly = GL_FIXED_ONLY,
};

/*(3.0) GLAD transform feedback buffer mode enumerator*/
enum class TransformFeedbackBufferMode : GLenum
{
	/*(3.0) Interleaved attributes value. Writes all attributes to a single buffer object*/
	InterleavedAttribs = GL_INTERLEAVED_ATTRIBS,

	/*(3.0) Separate attributes value. Writes attributes to multiple buffer objects or at different offsets into a single buffer*/
	SeparateAttribs = GL_SEPARATE_ATTRIBS,
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

/*(3.0) Constant expression converting index value to color attachment unit within <DrawBufferUnit> enumerator
@param The index of color attachment unit between 0 and value returned by <getMaxColorAttachments> minus 1
@return Color attachment unit value within <DrawBuffer> enumerator*/
constexpr DrawBufferUnit drawBufferAttachment(ColorAttachment index)
{
	return (DrawBufferUnit)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Constant expression converting index value to color attachment unit within <DrawBuffersUnit> enumerator
@param The index of color attachment unit between 0 and value returned by <getMaxColorAttachments> minus 1
@return Color attachment unit value within <DrawBuffers> enumerator*/
constexpr DrawBuffersUnit drawBuffersAttachment(ColorAttachment index)
{
	return (DrawBuffersUnit)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Constant expression checking if the returned color number index is valid
@param The index of color number ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1
@return True if the color number index is valid*/
constexpr GLboolean isColorNumber(ColorNumber index)
{
	return index != 0xFFFFFFFF;
}

/*(3.0) Constant expression converting index value to color attachment unit within <ReadBuffer> enumerator
@param The index of color attachment unit between 0 and value returned by <getMaxColorAttachments> minus 1
@return Color attachment unit value within <ReadBuffer> enumerator*/
constexpr ReadBufferUnit readBufferAttachment(ColorAttachment index)
{
	return (ReadBufferUnit)(GL_COLOR_ATTACHMENT0 + (GLenum)index);
}

/*(3.0) Start transform feedback operation, must be paired with called before <endTransformFeedback>
@param Specifies the output type of the primitives that will be recorded into the buffer objects*/
void beginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode);

/*(3.0) Specifies whether data read via <readPixels> should be clamped
@param Specifies whether to apply color clamping*/
void clampColor(ClampColor clamp);

/*(3.0) (1) Clear the color of individual buffer of a framebuffer to four-element RGBA integer values
@param The draw buffer unit index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1
@param Pointer to a four-element vector specifying the R, G, B and A color to clear that draw buffer to*/
void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLint* color);

/*(3.0) (2) Clear the color of individual buffer of a framebuffer to four-element RGBA unsigned integer values
@param The draw buffer unit index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1
@param Pointer to a four-element vector specifying the R, G, B and A color to clear that draw buffer to*/
void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLuint* color);

/*(3.0) (3) Clear the color of individual buffer of a framebuffer to four-element RGBA float values
@param The draw buffer unit index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1
@param Pointer to a four-element vector specifying the R, G, B and A color to clear that draw buffer to*/
void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLfloat* color);

/*(3.0) Clear the depth buffer to a float value
@param The value to clear the depth buffer to*/
void clearDepthBuffer(GLfloat depth);

/*(3.0) Clear the depth and stencil buffers simultaneously to a float and integer values
@param The value to clear the depth buffer to
@param The value to clear the stencil buffer to*/
void clearDepthStencilBuffer(GLfloat depth, GLint stencil);

/*(3.0) Clear the stencil buffer to an integer value
@param The value to clear the stencil buffer to*/
void clearStencilBuffer(GLint stencil);

/*(3.0) (2) Enable and disable writing of color components to specified draw buffer
@param The draw buffer unit index ranging from 0 to the value returned by <getMaxDrawBuffers> minus 1
@param Specifies whether red component is to be written into the frame buffer. The initial value is true
@param Specifies whether green component is be written into the frame buffer. The initial value is true
@param Specifies whether blue component is to be written into the frame buffer. The initial value is true
@param Specifies whether alpha  component is to be written into the frame buffer. The initial value is true*/
void colorMask(DrawBuffer index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

/*(3.0) Disable enabled clip geometry against user-defined half space server-side GL capability, initially disabled. The clip geometry unit index is between 0 and the value returned by <getMaxClipDistances> minus 1
@param The index of clip geometry unit*/
inline void disableClipDistance(ClipDistance index)
{
	_disable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

/*(3.0) Disable enabled framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
inline void disableFramebufferSrgb()
{
	_disable(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Disable enabled rasterizer discard server-side GL capability, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization*/
inline void disableRasterizerDiscard()
{
	_disable(GL_RASTERIZER_DISCARD);
}

/*(3.0) Enable clip geometry against user-defined half space server-side GL capability, initially disabled. The clip geometry unit index is between 0 and the value returned by <getMaxClipDistances> minus 1
@param The index of clip geometry unit*/
inline void enableClipDistance(ClipDistance index)
{
	_enable(GL_CLIP_DISTANCE0 + (GLenum)index);
}

/*(3.0) Enable framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending*/
inline void enableFramebufferSrgb()
{
	_enable(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Enable rasterizer discard server-side GL capability, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization*/
inline void enableRasterizerDiscard()
{
	_enable(GL_RASTERIZER_DISCARD);
}

/*(3.0) End transform feedback operation, must be paired with called after <beginTransformFeedback>*/
void endTransformFeedback();

/*(3.0) Gets previously set color clamping value, whether data read via <readPixels> should be clamped
@return Whether to apply color clamping*/
inline ClampColor getClampReadColor()
{
	return (ClampColor)_getInteger(GL_CLAMP_READ_COLOR);
}

/*(3.0) (2) Gets symbolic constant set by <drawBuffers> indicating which buffers are being drawn to by the corresponding output color. The initial value of draw buffer with index 0 is <Back> if there are back buffers, otherwise it is <Front>. The initial values of draw buffers for all other output colors is <None>
@param The index of querying draw buffer. The maximum value is <getMaxDrawBuffers> minus 1
@return The color buffer unit which is being drawn to*/
inline DrawBuffersUnit getDrawBuffer(DrawBuffer index)
{
	return (DrawBuffersUnit)_getInteger(GL_DRAW_BUFFER, index);
}

/*(3.0) Returns the extension string supported by the implementation at index
@param The index of the supported extension
@return The extension string*/
const GLubyte* getExtensions(GLuint index);

/*(3.0) Gets the major version number of the OpenGL API supported by the current context
@return The major version number*/
inline GLint getMajorVersion()
{
	return _getInteger(GL_MAJOR_VERSION);
}

/*(3.0) Gets the maximum number of layers allowed in an array texture, and must be at least 256
@return The maximum number of array texture layers*/
inline GLuint getMaxArrayTextureLayers()
{
	return _getInteger(GL_MAX_ARRAY_TEXTURE_LAYERS);
}

/*(3.0) Gets the maximum number of application-defined clipping distances. The value must be at least 8
@return The maximum clip distances number*/
inline GLuint getMaxClipDistances()
{
	return _getInteger(GL_MAX_CLIP_DISTANCES);
}

/*(3.0) Gets the maximum number of the color attachment units of the framebuffer. The value must be at least 8
@return The maximum of the color attachments*/
inline GLuint getMaxColorAttachments()
{
	return _getInteger(GL_MAX_COLOR_ATTACHMENTS);
}

/*(3.0) Gets the maximum texel offset allowed in a texture lookup, which must be at least 7
@return The maximum program texel offset*/
inline GLuint getMaxProgramTexelOffset()
{
	return _getInteger(GL_MAX_PROGRAM_TEXEL_OFFSET);
}

/*(3.0) Gets the maximum supported size for render-buffers
@return The maximum renderbuffer size*/
inline GLsizei getMaxRenderbufferSize()
{
	return _getInteger(GL_MAX_RENDERBUFFER_SIZE);
}

/*(3.0) Gets the number components for varying variables, which must be at least 60
@param The maximum components for varying variables*/
inline GLuint getMaxVaryingComponents()
{
	return _getInteger(GL_MAX_VARYING_COMPONENTS);
}

/*(3.0) Get the minimum texel offset allowed in a texture lookup, which must be at most -8
@return The minimum program texel offset*/
inline GLuint getMinProgramTexelOffset()
{
	return _getInteger(GL_MIN_PROGRAM_TEXEL_OFFSET);
}

/*(3.0) Gets the minor version number of the OpenGL API supported by the current context
@return The minor version number*/
inline GLint getMinorVersion()
{
	return _getInteger(GL_MINOR_VERSION);
}

/*(3.0) Gets the number of extensions supported by the GL implementation for the current context
@return The number of extensions*/
inline GLuint getNumExtensions()
{
	return _getInteger(GL_NUM_EXTENSIONS);
}

/*(3.0) Gets the size of the binding range
@return The size of the binding range for each transform feedback attribute stream*/
inline GLsizeiptr getTransformFeedbackBufferSize()
{
#ifdef YAGLPP_VERSION_3_2
	return (GLsizeiptr)_getInteger64(GL_TRANSFORM_FEEDBACK_BUFFER_SIZE);
#else // #ifdef YAGLPP_VERSION_3_2
	return (GLsizeiptr)_getInteger(GL_TRANSFORM_FEEDBACK_BUFFER_SIZE);
#endif // #ifdef YAGLPP_VERSION_3_2
}

/*(3.0) Gets the start offset of the binding range
@return The start offset of the binding range for each transform feedback attribute stream*/
inline GLintptr getTransformFeedbackBufferStart()
{
#ifdef YAGLPP_VERSION_3_2
	return (GLintptr)_getInteger64(GL_TRANSFORM_FEEDBACK_BUFFER_START);
#else // #ifdef YAGLPP_VERSION_3_2
	return (GLintptr)_getInteger(GL_TRANSFORM_FEEDBACK_BUFFER_START);
#endif // #ifdef YAGLPP_VERSION_3_2
}

/*(3.0) Checks if clip geometry against user-defined half space server-side GL capability is enabled, initially disabled. The clip geometry unit index is between 0 and the value returned by <getMaxClipDistances> minus 1
@param The index of clip geometry unit
@return True if the clip geometry unit is enabled*/
inline GLboolean isClipDistance(ClipDistance index)
{
	return _isEnabled(GL_CLIP_DISTANCE0 + (GLenum)index);
}

/*(3.0) Checks if context flag forward compatible bit was set at the context creation
@return True if the context is a forward compatible context, false otherwise*/
inline GLboolean isContextFlagForwardCompatibleBit()
{
	return _getInteger(GL_CONTEXT_FLAGS) == GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT;
}

/*(3.0) Checks if framebuffer SRGB server-side GL capability, initially disabled. If enabled and the value of <FramebufferAttachmentColorEncoding> for the framebuffer attachment corresponding to the destination buffer is <Srgb>, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending
@return True if framebuffer SRGB GL capability is enabled, false otherwise*/
inline GLboolean isFramebufferSrgb()
{
	return _isEnabled(GL_FRAMEBUFFER_SRGB);
}

/*(3.0) Checks if rasterizer discard server-side GL capability is enabled, initially disabled. If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization
@return True if rasterizer discard GL capability is enabled, false otherwise*/
inline GLboolean isRasterizerDiscard()
{
	return _isEnabled(GL_RASTERIZER_DISCARD);
}
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
GLboolean _getBoolean(GLenum target, GLuint index)
{
	GLboolean bData;
	glGetBooleani_v(target, index, &bData);
	YAGLPP_GLAD_ERROR;
	return bData;
}

GLint _getInteger(GLenum target, GLuint index)
{
	GLint iData;
	glGetIntegeri_v(target, index, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

void beginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
	glBeginTransformFeedback((GLenum)primitiveMode);
	YAGLPP_GLAD_ERROR;
}

void clampColor(ClampColor clamp)
{
	glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
	YAGLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLint* color)
{
	glClearBufferiv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLuint* color)
{
	glClearBufferuiv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLfloat* color)
{
	glClearBufferfv(GL_COLOR, (GLint)index, color);
	YAGLPP_GLAD_ERROR;
}

void clearDepthBuffer(GLfloat depth)
{
	glClearBufferfv(GL_DEPTH, 0, &depth);
	YAGLPP_GLAD_ERROR;
}

void clearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
	glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
	YAGLPP_GLAD_ERROR;
}

void clearStencilBuffer(GLint stencil)
{
	glClearBufferiv(GL_STENCIL, 0, &stencil);
	YAGLPP_GLAD_ERROR;
}

void colorMask(DrawBuffer index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMaski((GLint)index, red, green, blue, alpha);
	YAGLPP_GLAD_ERROR;
}

void endTransformFeedback()
{
	glEndTransformFeedback();
	YAGLPP_GLAD_ERROR;
}

const GLubyte* getExtensions(GLuint index)
{
	const GLubyte* pValue = glGetStringi(GL_EXTENSIONS, index);
	YAGLPP_GLAD_ERROR;
	return pValue;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline GLboolean _getBoolean(GLenum target, GLuint index)
{
	GLboolean b; glGetBooleani_v(target, index, &b); return b;
}

inline GLint _getInteger(GLenum target, GLuint index)
{
	GLint i; glGetIntegeri_v(target, index, &i); return i;
}

inline void beginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
	glBeginTransformFeedback((GLenum)primitiveMode);
}

inline void clampColor(ClampColor clamp)
{
	glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
}

inline void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLint* color)
{
	glClearBufferiv(GL_COLOR, (GLint)index, color);
}

inline void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLuint* color)
{
	glClearBufferuiv(GL_COLOR, (GLint)index, color);
}

inline void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLfloat* color)
{
	glClearBufferfv(GL_COLOR, (GLint)index, color);
}

inline void clearDepthBuffer(GLfloat depth)
{
	glClearBufferfv(GL_DEPTH, 0, &depth);
}

inline void clearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
	glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
}

inline void clearStencilBuffer(GLint stencil)
{
	glClearBufferiv(GL_STENCIL, 0, &stencil);
}

inline void colorMask(DrawBuffer index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMaski((GLint)index, red, green, blue, alpha);
}

inline void endTransformFeedback()
{
	glEndTransformFeedback();
}

inline const GLubyte* getExtensions(GLuint index)
{
	return glGetStringi(GL_EXTENSIONS, index);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_1
class BufferTexture;
class TextureBuffer;
class TextureRectangle;
class UniformBlock;
class UniformBuffer;

/*(3.1) Disable enabled primitive restart server-side GL capability, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index*/
inline void disablePrimitiveRestart()
{
	_disable(GL_PRIMITIVE_RESTART);
}

/*(3.1) Draw multiple instances of a range of elements
@param Specifies what kind of primitives to render
@param Specifies the starting index in the enabled arrays
@param Specifies the number of indices to be rendered
@param Specifies the number of instances of the specified range of indices to be rendered*/
void drawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount);

/*(3.1) Draw multiple instances of a set of elements
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies the number of instances of the specified range of indices to be rendered*/
void drawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount);

/*(3.1) Enable primitive restart server-side GL capability, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index*/
inline void enablePrimitiveRestart()
{
	_enable(GL_PRIMITIVE_RESTART);
}

/*(3.1) Gets the number of words for fragment shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined fragment uniform components*/
inline GLuint getMaxCombinedFragmentUniformComponents()
{
	return _getInteger(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
}

/*(3.1) Gets the number of words for geometry shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined geometry uniform components*/
inline GLuint getMaxCombinedGeometryUniformComponents()
{
	return _getInteger(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS);
}

/*(3.1) Gets the maximum number of uniform blocks per program. The value must be at least 70
@return The maximum combined uniform blocks*/
inline GLuint getMaxCombinedUniformBlocks()
{
	return _getInteger(GL_MAX_COMBINED_UNIFORM_BLOCKS);
}

/*(3.1) Gets the number of words for vertex shader uniform variables in all uniform blocks (including default). The value must be at least 1
@return The maximum combined vertex uniform components*/
inline GLuint getMaxCombinedVertexUniformComponents()
{
	return _getInteger(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
}

/*(3.1) Gets the maximum number of uniform blocks per fragment shader
@return The maximum fragment uniform components. The value must be at least 12*/
inline GLuint getMaxFragmentUniformBlocks()
{
	return _getInteger(GL_MAX_FRAGMENT_UNIFORM_BLOCKS);
}

/*(3.1) Get a rough estimate of the largest rectangular texture that the GL can handle. The value must be at least 1024. Use <getTextureWidthProxy> or <getTextureHeightProxy> to determine if a texture is too large
@return The maximum rectangle texture size*/
inline GLsizei getMaxRectangleTextureSize()
{
	return _getInteger(GL_MAX_RECTANGLE_TEXTURE_SIZE);
}

/*(3.1) The maximum number of texels allowed in the texel array of a texture buffer object
@param The maximum allowed number of texels. Value must be at least 65536*/
inline GLsizei getMaxTextureBufferSize()
{
	return _getInteger(GL_MAX_TEXTURE_BUFFER_SIZE);
}

/*(3.1) Gets the maximum size in basic machine units of a uniform block
@return The maximum uniform block size. The value must be at least 16384*/
inline GLsizei getMaxUniformBlockSize()
{
	return _getInteger(GL_MAX_UNIFORM_BLOCK_SIZE);
}

/*(3.1) Gets the maximum number of uniform buffer binding points on the context
@return The maximum uniform buffer bindings, must be at least 36*/
inline GLuint getMaxUniformBufferBindings()
{
	return _getInteger(GL_MAX_UNIFORM_BUFFER_BINDINGS);
}

/*(3.1) Gets the maximum number of uniform blocks per vertex shader
@return The maximum vertex uniform components. The value must be at least 12*/
inline GLuint getMaxVertexUniformBlocks()
{
	return _getInteger(GL_MAX_VERTEX_UNIFORM_BLOCKS);
}

/*(3.1) Gets the current primitive restart index. The initial value is 0
@return The primitive restart index*/
inline GLuint getPrimitiveRestartIndex()
{
	return _getInteger(GL_PRIMITIVE_RESTART_INDEX);
}

/*(3.1) Gets the alignment for uniform buffer sizes and offset
@return The minimum required alignment for uniform buffer sizes and offset*/
inline GLint getUniformBufferOffsetAlignment()
{
	return _getInteger(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT);
}

/*(3.1) Gets the size of the binding range
@return The size of the binding range for each indexed uniform buffer binding*/
inline GLsizeiptr getUniformBufferSize()
{
#ifdef YAGLPP_VERSION_3_2
	return (GLsizeiptr)_getInteger64(GL_UNIFORM_BUFFER_SIZE);
#else // #ifdef YAGLPP_VERSION_3_2
	return (GLsizeiptr)_getInteger(GL_UNIFORM_BUFFER_SIZE);
#endif //#ifdef YAGLPP_VERSION_3_2
}

/*(3.1) Gets the start offset of the binding range
@return The start offset of the binding range for each indexed uniform buffer binding*/
inline GLintptr getUniformBufferStart()
{
#ifdef YAGLPP_VERSION_3_2
	return (GLintptr)_getInteger64(GL_UNIFORM_BUFFER_START);
#else // #ifdef YAGLPP_VERSION_3_2
	return (GLintptr)_getInteger(GL_UNIFORM_BUFFER_START);
#endif //#ifdef YAGLPP_VERSION_3_2
}

/*(3.1) Checks if primitive restart server-side GL capability is enabled, initially disabled. Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index
@return True if primitive restart GL capability is enabled, false otherwise*/
inline GLboolean isPrimitiveRestart()
{
	return _isEnabled(GL_PRIMITIVE_RESTART);
}

/*(3.1) Specifies the primitive restart index. Using this GL feature requires enabling <PrimitiveRestart> capability to activate it
@param Specifies the value to be interpreted as the primitive restart index*/
void primitiveRestartIndex(GLuint index);
#endif // #ifdef YAGLPP_VERSION_3_1

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void drawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
	glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
	YAGLPP_GLAD_ERROR;
}

void drawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
	glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
	YAGLPP_GLAD_ERROR;
}

void primitiveRestartIndex(GLuint index)
{
	glPrimitiveRestartIndex(index);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

inline void drawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
	glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
}

inline void drawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
	glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
}

inline void primitiveRestartIndex(GLuint index)
{
	glPrimitiveRestartIndex(index);
}
#endif // #if defined (YAGLPP_VERSION_3_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_2
class GeometryShader;
class Sync;
class Texture2DMultisample;
class Texture2DMultisampleArray;
enum class SyncStatus : GLenum;

/*(3.2) Provoking vertex mode enumerator used in <provokingVertex>*/
enum class ProvokeMode : GLenum
{
	/*(3.2) First vertex convention mode*/
	FirstVertexConvention = GL_FIRST_VERTEX_CONVENTION,

	/*(3.2) Last vertex convention mode*/
	LastVertexConvention = GL_LAST_VERTEX_CONVENTION,
};

/*(3.2) Disable enabled depth clamp server-side GL capability, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)*/
inline void disableDepthClamp()
{
	_disable(GL_DEPTH_CLAMP);
}

/*(3.2) Disable enabled sample mask server-side GL capability, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs*/
inline void disableSampleMask()
{
	_disable(GL_SAMPLE_MASK);
}

/*(3.2) Disable enabled program point size server-side GL capability, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range*/
inline void disableProgramPointSize()
{
	_disable(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Disables enabled texture cube map seamless server-side GL capability, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value*/
inline void disableTextureCubeMapSeamless()
{
	_disable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Render primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void drawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex);

/*(3.2) Render multiple instances of a set of primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies the number of instances of the indexed geometry that should be drawn
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void drawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex);

/*(3.2) Render primitives from array data with a per-element offset
@param Specifies what kind of primitives to render
@param Specifies the minimum array index contained in indices
@param Specifies the maximum array index contained in indices
@param Specifies the number of elements to be rendered
@param Specifies the type of the values in indices
@param Specifies the byte offset into the element array index buffer object's data store
@param Specifies a constant that should be added to each element of indices when chosing elements from the enabled vertex arrays*/
void drawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex);

/*(3.2) Enable depth clamp server-side GL capability, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)*/
inline void enableDepthClamp()
{
	_enable(GL_DEPTH_CLAMP);
}

/*(3.2) Enable sample mask server-side GL capability, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs*/
inline void enableSampleMask()
{
	_enable(GL_SAMPLE_MASK);
}

/*(3.2) Enable program point size server-side GL capability, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range*/
inline void enableProgramPointSize()
{
	_enable(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Enables texture cube map seamless server-side GL capability, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value*/
inline void enableTextureCubeMapSeamless()
{
	_enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Returns the maximum number of uniform blocks per geometry shader
@return The maximum geometry uniform blocks. The value must be at least 12*/
inline GLuint getMaxGeometryUniformBlocks()
{
	return _getInteger(GL_MAX_GEOMETRY_UNIFORM_BLOCKS);
}

/*(3.2) Returns the maximum number of samples in a color multisample texture
@return The maximum color texture samples*/
inline GLsizei getMaxColorTextureSamples()
{
	return _getInteger(GL_MAX_COLOR_TEXTURE_SAMPLES);
}

/*(3.2) Returns the maximum number of samples in a multisample depth or depth-stencil texture
@return The maximum depth texture samples*/
inline GLsizei getMaxDepthTextureSamples()
{
	return _getInteger(GL_MAX_DEPTH_TEXTURE_SAMPLES);
}

/*(3.2) Returns the maximum number of components of the inputs read by the fragment shader
@return The maximum fragment input components. The value must be at least 128*/
inline GLuint getMaxFragmentInputComponents()
{
	return _getInteger(GL_MAX_FRAGMENT_INPUT_COMPONENTS);
}

/*(3.2) Returns the maximum number of components of inputs read by a geometry shader
@return The maximum geometry input components. The value must be at least 64*/
inline GLuint getMaxGeometryInputComponents()
{
	return _getInteger(GL_MAX_GEOMETRY_INPUT_COMPONENTS);
}

/*(3.2) Returns the maximum number of components of outputs written by a geometry shader
@return The maximum geometry output components. The value must be at least 128*/
inline GLuint getMaxGeometryOutputComponents()
{
	return _getInteger(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS);
}

/*(3.2) Returns the maximum supported texture image units that can be used to access texture maps from the geometry shader
@return The maximum geometry texture image units. The value must be at least 16*/
inline GLuint getMaxGeometryTextureImageUnits()
{
	return _getInteger(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS);
}

/*(3.2) Returns the maximum number of individual floating-point, integer, or boolean values that can be held in uniform variable storage for a geometry shader
@return The maximum geometry uniform components. The value must be at least 1024*/
inline GLuint getMaxGeometryUniformComponents()
{
	return _getInteger(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS);
}

/*(3.2) Returns the maximum number of samples supported in integer format multisample buffers
@return The maximum number of integer samples*/
inline GLuint getMaxIntegerSamples()
{
	return _getInteger(GL_MAX_INTEGER_SAMPLES);
}

/*(3.2) Returns the maximum number of sample mask words
@return The maximum number of sample mask words*/
inline GLuint getMaxSampleMaskWords()
{
	return _getInteger(GL_MAX_SAMPLE_MASK_WORDS);
}

/*(3.2) Returns the maximum timeout interval used by sync object
@return The maximum sync timeout interval*/
inline GLuint getMaxServerWaitTimeout()
{
	return _getInteger(GL_MAX_SERVER_WAIT_TIMEOUT);
}

/*(3.2) Returns the maximum number of components of output written by a vertex shader
@return The maximum vertex output components. The value must be at least 64*/
inline GLuint getMaxVertexOutputComponents()
{
	return _getInteger(GL_MAX_VERTEX_OUTPUT_COMPONENTS);
}

/*(3.2) Retrieves the location of a sample
@param Specifies the index of the sample whose position to query, must be less than the value returned by <getSamples>
@param [out] Pointer to a two-element float value receiving the position of the sample*/
void getMultisample(GLuint index, _Out_writes_(2) GLfloat* val);

/*(3.2) Checks whether vertex program point size mode is enabled
@return True if vertex program point size mode is enabled, false otherwise*/
inline GLboolean getProgramPointSize()
{
	return _getInteger(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Returns the currently selected provoking vertex convention used by <provokingVertex>. The initial value is <LastVertexConvention>
@return True if vertex program point size mode is enabled, false otherwise*/
inline ProvokeMode getProvokingVertex()
{
	return (ProvokeMode)_getInteger(GL_PROVOKING_VERTEX);
}

/*(3.2) Returns the current sample mask value set by <sampleMaski>
@return The current sample mask value*/
inline GLbitfield getSampleMaskValue()
{
	return _getInteger(GL_SAMPLE_MASK_VALUE);
}

/*(3.2) Checks if depth clamp server-side GL capability is enabled, initially disabled. If enabled, the -Wc <= Zc <= Wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping)
@return True if depth clamp GL capability is enabled, false otherwise*/
inline GLboolean isDepthClamp()
{
	return _isEnabled(GL_DEPTH_CLAMP);
}

/*(3.2) Checks if sample mask server-side GL capability is enabled, initially disabled. If enabled, the sample coverage mask generated for a fragment during rasterization will be AND'ed with the value of <SampleMaskValue> before shading occurs
@return True if sample mask GL capability is enabled, false otherwise*/
inline GLboolean isSampleMask()
{
	return _isEnabled(GL_SAMPLE_MASK);
}

/*(3.2) Checks if program point size server-side GL capability is enabled, initially disabled. If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin <gl_PointSize> and clamped to the implementation-dependent point size range
@return True if program point size GL capability is enabled, false otherwise*/
inline GLboolean isProgramPointSize()
{
	return _isEnabled(GL_PROGRAM_POINT_SIZE);
}

/*(3.2) Checks if texture cube map seamless server-side GL capability is enabled, initially disabled. If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value
@return True if texture cube map seamless GL capability is enabled, false otherwise*/
inline GLboolean isTextureCubeMapSeamless()
{
	return _isEnabled(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/*(3.2) Render multiple sets of primitives by specifying indices of array data elements and an index to apply to each index
@param Specifies what kind of primitives to render
@param [in] Specifies a pointer to an array of the elements counts
@param Specifies the type of the values in indices
@param [in] Pointer to an array of the byte offsets into the element array index buffer object's data store
@param Specifies the size of the count, indices and basevertex arrays
@param [in] Specifies a pointer to an array of the base vertices*/
void multiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex);

/*(3.2) Specifies the vertex to be used as the source of data for flat shaded varyings
@param Controls the selection of the vertex whose values are assigned to flatshaded varying outputs*/
void provokingVertex(ProvokeMode provokeMode);

/*(3.2) Sets the value of a sub-word of the sample mask, which must be less than the value returned by <getMaxSampleMaskWords>
@param Specifies which 32-bit sub-word of the sample mask to update
@param Specifies the new value of the mask sub-word*/
void sampleMask(GLuint maskNumber, GLbitfield mask);
#endif // #ifdef YAGLPP_VERSION_3_2

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
GLint64 _getInteger64(GLenum pname)
{
	GLint64 iData64;
	glGetInteger64v(pname, &iData64);
	YAGLPP_GLAD_ERROR;
	return iData64;
}

GLint64 _getInteger64(GLenum target, GLuint index)
{
	GLint64 iData64;
	glGetInteger64i_v(target, index, &iData64);
	YAGLPP_GLAD_ERROR;
	return iData64;
}

void drawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
	YAGLPP_GLAD_ERROR;
}

void drawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
	glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
	YAGLPP_GLAD_ERROR;
}

void drawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
	YAGLPP_GLAD_ERROR;
}

void getMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
	glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
	YAGLPP_GLAD_ERROR;
}

void multiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
	glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
	YAGLPP_GLAD_ERROR;
}

void provokingVertex(ProvokeMode provokeMode)
{
	glProvokingVertex((GLenum)provokeMode);
	YAGLPP_GLAD_ERROR;
}

void sampleMask(GLuint maskNumber, GLbitfield mask)
{
	glSampleMaski(maskNumber, mask);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline GLint64 _getInteger64(GLenum pname)
{
	GLint64 i; glGetInteger64v(pname, &i); return i;
}

inline GLint64 _getInteger64(GLenum target, GLuint index)
{
	GLint64 i; glGetInteger64i_v(target, index, &i); return i;
}

inline void drawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
}

inline void drawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
	glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
}

inline void drawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
	glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
}

inline void getMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
	glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
}

inline void multiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
	glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
}

inline void provokingVertex(ProvokeMode provokeMode)
{
	glProvokingVertex((GLenum)provokeMode);
}

inline void sampleMask(GLuint maskNumber, GLbitfield mask)
{
	glSampleMaski(maskNumber, mask);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#ifdef YAGLPP_VERSION_3_3
class Sampler;
class Samplers;
class AnySamplesPassed;
class TimeElapsed;
enum class TextureSwizzleMask : GLenum;

/*(3.3) Gets the maximum number of active draw buffers when using dual-source blending. The value must be at least 1
@return The maximum number of dual source draw buffers*/
inline GLuint getMaxDualSourceDrawBuffers()
{
	return _getInteger(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS);
}
#endif // #ifdef YAGLPP_VERSION_3_3
} // namespace gl

#include <yaglpp/glad/_object.h>
#include <yaglpp/glad/sync.h>
#include <yaglpp/glad/uniform.h>
#include <yaglpp/glad/uniform_block.h>
#include <yaglpp/glad/vertex_attrib.h>
