#define YAGLPP_BUILD_LIB
#include <yaglpp/gladpp.h>
#pragma comment(lib, "opengl32.lib")
#if (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR == 3)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.3 support...")
#elif (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR == 2)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.2 support...")
#elif (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR == 1)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.1 support...")
#elif (YAGLPP_CONTEXT_VERSION_MAJOR == 3) && (YAGLPP_CONTEXT_VERSION_MINOR == 0)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.0 support...")
#elif (YAGLPP_CONTEXT_VERSION_MAJOR == 2) && (YAGLPP_CONTEXT_VERSION_MINOR == 1)
#pragma message("gladpp.cpp: Compiling with GLAD version 2.1 support...")
#elif (YAGLPP_CONTEXT_VERSION_MAJOR == 2) && (YAGLPP_CONTEXT_VERSION_MINOR == 0)
#pragma message("gladpp.cpp: Compiling with GLAD version 2.0 support...")
#endif

int _loadGL(void* proc)
{
    return gladLoadGLLoader((GLADloadproc)proc);
}

namespace gl {
#ifdef _DEBUG
void _disable(GLenum cap)
{
    glDisable(cap);
    _YAGLPP_GLAD_ERROR_;
}

void _enable(GLenum cap)
{
    glEnable(cap);
    _YAGLPP_GLAD_ERROR_;
}

GLboolean _getBoolean(GLenum pname)
{
    GLboolean bData = GL_FALSE;
    glGetBooleanv(pname, &bData);
    _YAGLPP_GLAD_ERROR_;
    return bData;
}

void _getBoolean(GLenum pname, GLboolean* data)
{
    glGetBooleanv(pname, data);
    _YAGLPP_GLAD_ERROR_;
}

GLdouble _getDouble(GLenum pname)
{
    GLdouble dData = 0.0;
    glGetDoublev(pname, &dData);
    _YAGLPP_GLAD_ERROR_;
    return dData;
}

void _getDouble(GLenum pname, GLdouble* data)
{
    glGetDoublev(pname, data);
    _YAGLPP_GLAD_ERROR_;
}

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

#ifdef GL_VERSION_3_0
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            zDescription = "INVALID FRAMEBUFFER OPERATION";
#endif // #ifdef GL_VERSION_3_0
        }
        std::cout << "GLAD ERROR <" << eNumber << ">: " << zDescription << std::endl;
        eNumber = glGetError();
    } while (eNumber != GL_NO_ERROR);
    return GL_FALSE;
}

GLfloat _getFloat(GLenum pname)
{
    GLfloat fData = 0.0f;
    glGetFloatv(pname, &fData);
    _YAGLPP_GLAD_ERROR_;
    return fData;
}

void _getFloat(GLenum pname, GLfloat* data)
{
    glGetFloatv(pname, data);
    _YAGLPP_GLAD_ERROR_;
}

GLint _getInteger(GLenum pname)
{
    GLint iData = 0;
    glGetIntegerv(pname, &iData);
    _YAGLPP_GLAD_ERROR_;
    return iData;
}

void _getInteger(GLenum pname, GLint* data)
{
    glGetIntegerv(pname, data);
    _YAGLPP_GLAD_ERROR_;
}

void _hint(GLenum target, GLenum mode)
{
    glHint(target, mode);
    _YAGLPP_GLAD_ERROR_;
}

void _pixelStore(GLenum pname, GLfloat param)
{
    glPixelStoref(pname, param);
    _YAGLPP_GLAD_ERROR_;
}

void _pixelStore(GLenum pname, GLint param)
{
    glPixelStorei(pname, param);
    _YAGLPP_GLAD_ERROR_;
}

void activeTexture(TextureUnit index)
{
    glActiveTexture(GL_TEXTURE0 + (GLenum)index);
    _YAGLPP_GLAD_ERROR_;
}

void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glBlendColor(red, green, blue, alpha);
    _YAGLPP_GLAD_ERROR_;
}

void blendEquation(BlendEquationMode mode)
{
    glBlendEquation((GLenum)mode);
    _YAGLPP_GLAD_ERROR_;
}

void blendEquationSeparate(BlendEquationMode modeRGB, BlendEquationMode modeAlpha)
{
    glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
    _YAGLPP_GLAD_ERROR_;
}

void blendFunc(BlendFuncFactor sfactor, BlendFuncFactor dfactor)
{
    glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
    _YAGLPP_GLAD_ERROR_;
}

void blendFuncSeparate(BlendFuncFactor srcRGB, BlendFuncFactor dstRGB, BlendFuncFactor srcAlpha, BlendFuncFactor dstAlpha)
{
    glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
    _YAGLPP_GLAD_ERROR_;
}

void clear(BufferBitMask mask)
{
    glClear((GLbitfield)mask);
    _YAGLPP_GLAD_ERROR_;
}

void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    _YAGLPP_GLAD_ERROR_;
}

void clearDepth(GLdouble depth)
{
    glClearDepth(depth);
    _YAGLPP_GLAD_ERROR_;
}

void clearStencil(GLint stencil)
{
    glClearStencil(stencil);
    _YAGLPP_GLAD_ERROR_;
}

void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    glColorMask(red, green, blue, alpha);
    _YAGLPP_GLAD_ERROR_;
}

void cullFace(FaceMode mode)
{
    glCullFace((GLenum)mode);
    _YAGLPP_GLAD_ERROR_;
}

void depthFunc(CompareFunc func)
{
    glDepthFunc((GLenum)func);
    _YAGLPP_GLAD_ERROR_;
}

void depthMask(GLboolean flag)
{
    glDepthMask(flag);
    _YAGLPP_GLAD_ERROR_;
}

void depthRange(GLdouble nearVal, GLdouble farVal)
{
    glDepthRange(nearVal, farVal);
    _YAGLPP_GLAD_ERROR_;
}

void drawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
    glDrawArrays((GLenum)mode, first, count);
    _YAGLPP_GLAD_ERROR_;
}

void drawBuffer(DrawBufferUnit buf)
{
    glDrawBuffer((GLenum)buf);
    _YAGLPP_GLAD_ERROR_;
}

void drawBuffers(GLsizei n, _In_reads_(n) const DrawBuffersUnit* bufs)
{
    glDrawBuffers(n, (GLenum*)bufs);
    _YAGLPP_GLAD_ERROR_;
}

void drawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
    glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
    _YAGLPP_GLAD_ERROR_;
}

void drawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
    glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
    _YAGLPP_GLAD_ERROR_;
}

void finish()
{
    glFinish();
    _YAGLPP_GLAD_ERROR_;
}

void flush()
{
    glFlush();
    _YAGLPP_GLAD_ERROR_;
}

void frontFace(FrontFaceMode mode)
{
    glFrontFace((GLenum)mode);
    _YAGLPP_GLAD_ERROR_;
}

void lineWidth(GLfloat width)
{
    glLineWidth(width);
    _YAGLPP_GLAD_ERROR_;
}

void logicOp(LogicOpMode opcode)
{
    glLogicOp((GLenum)opcode);
    _YAGLPP_GLAD_ERROR_;
}

void multiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
    glMultiDrawArrays((GLenum)mode, first, count, drawcount);
    _YAGLPP_GLAD_ERROR_;
}

void multiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
    glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
    _YAGLPP_GLAD_ERROR_;
}

void pointSize(GLfloat size)
{
    glPointSize(size);
    _YAGLPP_GLAD_ERROR_;
}

void polygonMode(PolygonMode mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
    _YAGLPP_GLAD_ERROR_;
}

void polygonOffset(GLfloat factor, GLfloat units)
{
    glPolygonOffset(factor, units);
    _YAGLPP_GLAD_ERROR_;
}

void readBuffer(ReadBufferUnit mode)
{
    glReadBuffer((GLenum)mode);
    _YAGLPP_GLAD_ERROR_;
}

void sampleCoverage(GLfloat value, GLboolean invert)
{
    glSampleCoverage(value, invert);
    _YAGLPP_GLAD_ERROR_;
}

void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glScissor(x, y, width, height);
    _YAGLPP_GLAD_ERROR_;
}

void setPointFadeThresholdSize(GLfloat size)
{
    glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
    _YAGLPP_GLAD_ERROR_;
}

void setPointSpriteCoordOrigin(PointSpriteCoordOrigin origin)
{
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
    _YAGLPP_GLAD_ERROR_;
}

void stencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
    glStencilFunc((GLenum)func, ref, mask);
    _YAGLPP_GLAD_ERROR_;
}

void stencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
    glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
    _YAGLPP_GLAD_ERROR_;
}

void stencilMask(GLuint mask)
{
    glStencilMask(mask);
    _YAGLPP_GLAD_ERROR_;
}

void stencilMaskSeparate(FaceMode face, GLuint mask)
{
    glStencilMaskSeparate((GLenum)face, mask);
    _YAGLPP_GLAD_ERROR_;
}

void stencilOp(StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
    glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
    _YAGLPP_GLAD_ERROR_;
}

void stencilOpSeparate(FaceMode face, StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
    glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
    _YAGLPP_GLAD_ERROR_;
}

void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
    _YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_3_0
GLboolean _getBoolean(GLenum target, GLuint index)
{
    GLboolean bData = 0;
    glGetBooleani_v(target, index, &bData);
    _YAGLPP_GLAD_ERROR_;
    return bData;
}

GLint _getInteger(GLenum target, GLuint index)
{
    GLint iData = 0;
    glGetIntegeri_v(target, index, &iData);
    _YAGLPP_GLAD_ERROR_;
    return iData;
}

void beginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
    glBeginTransformFeedback((GLenum)primitiveMode);
    _YAGLPP_GLAD_ERROR_;
}

void clampColor(ClampColor clamp)
{
    glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
    _YAGLPP_GLAD_ERROR_;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLint* color)
{
    glClearBufferiv(GL_COLOR, (GLint)index, color);
    _YAGLPP_GLAD_ERROR_;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLuint* color)
{
    glClearBufferuiv(GL_COLOR, (GLint)index, color);
    _YAGLPP_GLAD_ERROR_;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLfloat* color)
{
    glClearBufferfv(GL_COLOR, (GLint)index, color);
    _YAGLPP_GLAD_ERROR_;
}

void clearDepthBuffer(GLfloat depth)
{
    glClearBufferfv(GL_DEPTH, 0, &depth);
    _YAGLPP_GLAD_ERROR_;
}

void clearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
    glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
    _YAGLPP_GLAD_ERROR_;
}

void clearStencilBuffer(GLint stencil)
{
    glClearBufferiv(GL_STENCIL, 0, &stencil);
    _YAGLPP_GLAD_ERROR_;
}

void colorMask(DrawBuffer index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    glColorMaski((GLint)index, red, green, blue, alpha);
    _YAGLPP_GLAD_ERROR_;
}

void endTransformFeedback()
{
    glEndTransformFeedback();
    _YAGLPP_GLAD_ERROR_;
}

const GLubyte* getExtensions(GLuint index)
{
    const GLubyte* pValue = glGetStringi(GL_EXTENSIONS, index);
    _YAGLPP_GLAD_ERROR_;
    return pValue;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#if defined _DEBUG && defined GL_VERSION_3_1
void drawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
    glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
    _YAGLPP_GLAD_ERROR_;
}

void drawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
    glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
    _YAGLPP_GLAD_ERROR_;
}

void primitiveRestartIndex(GLuint index)
{
    glPrimitiveRestartIndex(index);
    _YAGLPP_GLAD_ERROR_;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_2
GLint64 _getInteger64(GLenum pname)
{
    GLint64 iData64 = 0;
    glGetInteger64v(pname, &iData64);
    _YAGLPP_GLAD_ERROR_;
    return iData64;
}

GLint64 _getInteger64(GLenum target, GLuint index)
{
    GLint64 iData64 = 0;
    glGetInteger64i_v(target, index, &iData64);
    _YAGLPP_GLAD_ERROR_;
    return iData64;
}

void drawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
    glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
    _YAGLPP_GLAD_ERROR_;
}

void drawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
    glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
    _YAGLPP_GLAD_ERROR_;
}

void drawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
    glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
    _YAGLPP_GLAD_ERROR_;
}

void getMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
    glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
    _YAGLPP_GLAD_ERROR_;
}

void multiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
    glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
    _YAGLPP_GLAD_ERROR_;
}

void provokingVertex(ProvokeMode provokeMode)
{
    glProvokingVertex((GLenum)provokeMode);
    _YAGLPP_GLAD_ERROR_;
}

void sampleMask(GLuint maskNumber, GLbitfield mask)
{
    glSampleMaski(maskNumber, mask);
    _YAGLPP_GLAD_ERROR_;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
} // namespace gl
