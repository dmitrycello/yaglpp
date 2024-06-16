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
    GLdouble dData = 0.0;
    glGetDoublev(pname, &dData);
    YAGLPP_GLAD_ERROR;
    return dData;
}

void _getDouble(GLenum pname, GLdouble* data)
{
    glGetDoublev(pname, data);
    YAGLPP_GLAD_ERROR;
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
    GLint iData = 0;
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
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_3_0
GLboolean _getBoolean(GLenum target, GLuint index)
{
    GLboolean bData = 0;
    glGetBooleani_v(target, index, &bData);
    YAGLPP_GLAD_ERROR;
    return bData;
}

GLint _getInteger(GLenum target, GLuint index)
{
    GLint iData = 0;
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
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#if defined _DEBUG && defined GL_VERSION_3_1
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
#endif // #if defined _DEBUG && defined GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_2
GLint64 _getInteger64(GLenum pname)
{
    GLint64 iData64 = 0;
    glGetInteger64v(pname, &iData64);
    YAGLPP_GLAD_ERROR;
    return iData64;
}

GLint64 _getInteger64(GLenum target, GLuint index)
{
    GLint64 iData64 = 0;
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
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
} // namespace gl
