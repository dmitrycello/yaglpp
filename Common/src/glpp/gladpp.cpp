#define GLPP_BUILD_LIB
#include <glpp/gladpp.h>
#pragma comment(lib, "opengl32.lib")
#if (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR == 3)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.3 support...")
#elif (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR == 2)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.2 support...")
#elif (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR == 1)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.1 support...")
#elif (GLPP_CONTEXT_VERSION_MAJOR == 3) && (GLPP_CONTEXT_VERSION_MINOR == 0)
#pragma message("gladpp.cpp: Compiling with GLAD version 3.0 support...")
#elif (GLPP_CONTEXT_VERSION_MAJOR == 2) && (GLPP_CONTEXT_VERSION_MINOR == 1)
#pragma message("gladpp.cpp: Compiling with GLAD version 2.1 support...")
#elif (GLPP_CONTEXT_VERSION_MAJOR == 2) && (GLPP_CONTEXT_VERSION_MINOR == 0)
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
    GLPP_GLAD_ERROR;
}

void _enable(GLenum cap)
{
    glEnable(cap);
    GLPP_GLAD_ERROR;
}

GLboolean _getBoolean(GLenum pname)
{
    GLboolean bData = GL_FALSE;
    glGetBooleanv(pname, &bData);
    GLPP_GLAD_ERROR;
    return bData;
}

void _getBoolean(GLenum pname, GLboolean* data)
{
    glGetBooleanv(pname, data);
    GLPP_GLAD_ERROR;
}

GLdouble _getDouble(GLenum pname)
{
    GLdouble dData = 0.0;
    glGetDoublev(pname, &dData);
    GLPP_GLAD_ERROR;
    return dData;
}

void _getDouble(GLenum pname, GLdouble* data)
{
    glGetDoublev(pname, data);
    GLPP_GLAD_ERROR;
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
    GLPP_GLAD_ERROR;
    return fData;
}

void _getFloat(GLenum pname, GLfloat* data)
{
    glGetFloatv(pname, data);
    GLPP_GLAD_ERROR;
}

GLint _getInteger(GLenum pname)
{
    GLint iData = 0;
    glGetIntegerv(pname, &iData);
    GLPP_GLAD_ERROR;
    return iData;
}

void _getInteger(GLenum pname, GLint* data)
{
    glGetIntegerv(pname, data);
    GLPP_GLAD_ERROR;
}

void _hint(GLenum target, GLenum mode)
{
    glHint(target, mode);
    GLPP_GLAD_ERROR;
}

void _pixelStore(GLenum pname, GLfloat param)
{
    glPixelStoref(pname, param);
    GLPP_GLAD_ERROR;
}

void _pixelStore(GLenum pname, GLint param)
{
    glPixelStorei(pname, param);
    GLPP_GLAD_ERROR;
}

void activeTexture(TextureUnit index)
{
    glActiveTexture((GLenum)index + GL_TEXTURE0);
    GLPP_GLAD_ERROR;
}

void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glBlendColor(red, green, blue, alpha);
    GLPP_GLAD_ERROR;
}

void blendEquation(BlendEquationMode mode)
{
    glBlendEquation((GLenum)mode);
    GLPP_GLAD_ERROR;
}

void blendEquationSeparate(BlendEquationMode modeRGB, BlendEquationMode modeAlpha)
{
    glBlendEquationSeparate((GLenum)modeRGB, (GLenum)modeAlpha);
    GLPP_GLAD_ERROR;
}

void blendFunc(BlendFuncFactor sfactor, BlendFuncFactor dfactor)
{
    glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
    GLPP_GLAD_ERROR;
}

void blendFuncSeparate(BlendFuncFactor srcRGB, BlendFuncFactor dstRGB, BlendFuncFactor srcAlpha, BlendFuncFactor dstAlpha)
{
    glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
    GLPP_GLAD_ERROR;
}

void clear(BufferBitMask mask)
{
    glClear((GLbitfield)mask);
    GLPP_GLAD_ERROR;
}

void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    GLPP_GLAD_ERROR;
}

void clearDepth(GLdouble depth)
{
    glClearDepth(depth);
    GLPP_GLAD_ERROR;
}

void clearStencil(GLint stencil)
{
    glClearStencil(stencil);
    GLPP_GLAD_ERROR;
}

void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    glColorMask(red, green, blue, alpha);
    GLPP_GLAD_ERROR;
}

void cullFace(FaceMode mode)
{
    glCullFace((GLenum)mode);
    GLPP_GLAD_ERROR;
}

void depthFunc(CompareFunc func)
{
    glDepthFunc((GLenum)func);
    GLPP_GLAD_ERROR;
}

void depthMask(GLboolean flag)
{
    glDepthMask(flag);
    GLPP_GLAD_ERROR;
}

void depthRange(GLdouble nearVal, GLdouble farVal)
{
    glDepthRange(nearVal, farVal);
    GLPP_GLAD_ERROR;
}

void drawArrays(PrimitiveMode mode, GLint first, GLsizei count)
{
    glDrawArrays((GLenum)mode, first, count);
    GLPP_GLAD_ERROR;
}

void drawBuffer(DrawBufferUnit buf)
{
    glDrawBuffer((GLenum)buf);
    GLPP_GLAD_ERROR;
}

void drawBuffers(GLsizei n, _In_reads_(n) const DrawBuffersUnit* bufs)
{
    glDrawBuffers(n, (GLenum*)bufs);
    GLPP_GLAD_ERROR;
}

void drawElements(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices)
{
    glDrawElements((GLenum)mode, count, (GLenum)type, (void*)indices);
    GLPP_GLAD_ERROR;
}

void drawRangeElements(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices)
{
    glDrawRangeElements((GLenum)mode, start, end, count, (GLenum)type, (void*)indices);
    GLPP_GLAD_ERROR;
}

void finish()
{
    glFinish();
    GLPP_GLAD_ERROR;
}

void flush()
{
    glFlush();
    GLPP_GLAD_ERROR;
}

void frontFace(FrontFaceMode mode)
{
    glFrontFace((GLenum)mode);
    GLPP_GLAD_ERROR;
}

void lineWidth(GLfloat width)
{
    glLineWidth(width);
    GLPP_GLAD_ERROR;
}

void logicOp(LogicOpMode opcode)
{
    glLogicOp((GLenum)opcode);
    GLPP_GLAD_ERROR;
}

void multiDrawArrays(PrimitiveMode mode, _In_ const GLint* first, _In_ const GLsizei* count, GLsizei drawcount)
{
    glMultiDrawArrays((GLenum)mode, first, count, drawcount);
    GLPP_GLAD_ERROR;
}

void multiDrawElements(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount)
{
    glMultiDrawElements((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount);
    GLPP_GLAD_ERROR;
}

void pointSize(GLfloat size)
{
    glPointSize(size);
    GLPP_GLAD_ERROR;
}

void polygonMode(PolygonMode mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
    GLPP_GLAD_ERROR;
}

void polygonOffset(GLfloat factor, GLfloat units)
{
    glPolygonOffset(factor, units);
    GLPP_GLAD_ERROR;
}

void readBuffer(ReadBufferUnit mode)
{
    glReadBuffer((GLenum)mode);
    GLPP_GLAD_ERROR;
}

void sampleCoverage(GLfloat value, GLboolean invert)
{
    glSampleCoverage(value, invert);
    GLPP_GLAD_ERROR;
}

void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glScissor(x, y, width, height);
    GLPP_GLAD_ERROR;
}

void setPointFadeThresholdSize(GLfloat size)
{
    glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);
    GLPP_GLAD_ERROR;
}

void setPointSpriteCoordOrigin(PointSpriteCoordOrigin origin)
{
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLenum)origin);
    GLPP_GLAD_ERROR;
}

void stencilFunc(CompareFunc func, GLint ref, GLuint mask)
{
    glStencilFunc((GLenum)func, ref, mask);
    GLPP_GLAD_ERROR;
}

void stencilFuncSeparate(FaceMode face, CompareFunc func, GLint ref, GLuint mask)
{
    glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
    GLPP_GLAD_ERROR;
}

void stencilMask(GLuint mask)
{
    glStencilMask(mask);
    GLPP_GLAD_ERROR;
}

void stencilMaskSeparate(FaceMode face, GLuint mask)
{
    glStencilMaskSeparate((GLenum)face, mask);
    GLPP_GLAD_ERROR;
}

void stencilOp(StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
    glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
    GLPP_GLAD_ERROR;
}

void stencilOpSeparate(FaceMode face, StencilOpMode sfail, StencilOpMode dpfail, StencilOpMode dppass)
{
    glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
    GLPP_GLAD_ERROR;
}

void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
    GLPP_GLAD_ERROR;
}
#endif // #ifdef _DEBUG

#if defined _DEBUG && defined GL_VERSION_3_0
GLboolean _getBoolean(GLenum target, GLuint index)
{
    GLboolean bData = 0;
    glGetBooleani_v(target, index, &bData);
    GLPP_GLAD_ERROR;
    return bData;
}

GLint _getInteger(GLenum target, GLuint index)
{
    GLint iData = 0;
    glGetIntegeri_v(target, index, &iData);
    GLPP_GLAD_ERROR;
    return iData;
}

void beginTransformFeedback(TransformFeedbackPrimitiveMode primitiveMode)
{
    glBeginTransformFeedback((GLenum)primitiveMode);
    GLPP_GLAD_ERROR;
}

void clampColor(ClampColor clamp)
{
    glClampColor(GL_CLAMP_READ_COLOR, (GLenum)clamp);
    GLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLint* color)
{
    glClearBufferiv(GL_COLOR, (GLint)index, color);
    GLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLuint* color)
{
    glClearBufferuiv(GL_COLOR, (GLint)index, color);
    GLPP_GLAD_ERROR;
}

void clearColorBuffer(DrawBuffer index, _In_reads_(4) const GLfloat* color)
{
    glClearBufferfv(GL_COLOR, (GLint)index, color);
    GLPP_GLAD_ERROR;
}

void clearDepthBuffer(GLfloat depth)
{
    glClearBufferfv(GL_DEPTH, 0, &depth);
    GLPP_GLAD_ERROR;
}

void clearDepthStencilBuffer(GLfloat depth, GLint stencil)
{
    glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
    GLPP_GLAD_ERROR;
}

void clearStencilBuffer(GLint stencil)
{
    glClearBufferiv(GL_STENCIL, 0, &stencil);
    GLPP_GLAD_ERROR;
}

void colorMask(DrawBuffer index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    glColorMaski((GLint)index, red, green, blue, alpha);
    GLPP_GLAD_ERROR;
}

void endTransformFeedback()
{
    glEndTransformFeedback();
    GLPP_GLAD_ERROR;
}

const GLubyte* getExtensions(GLuint index)
{
    const GLubyte* pValue = glGetStringi(GL_EXTENSIONS, index);
    GLPP_GLAD_ERROR;
    return pValue;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_0

#if defined _DEBUG && defined GL_VERSION_3_1
void drawArraysInstanced(PrimitiveMode mode, GLint first, GLsizei count, GLsizei instancecount)
{
    glDrawArraysInstanced((GLenum)mode, first, count, instancecount);
    GLPP_GLAD_ERROR;
}

void drawElementsInstanced(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount)
{
    glDrawElementsInstanced((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount);
    GLPP_GLAD_ERROR;
}

void primitiveRestartIndex(GLuint index)
{
    glPrimitiveRestartIndex(index);
    GLPP_GLAD_ERROR;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_1

#if defined _DEBUG && defined GL_VERSION_3_2
GLint64 _getInteger64(GLenum pname)
{
    GLint64 iData64 = 0;
    glGetInteger64v(pname, &iData64);
    GLPP_GLAD_ERROR;
    return iData64;
}

GLint64 _getInteger64(GLenum target, GLuint index)
{
    GLint64 iData64 = 0;
    glGetInteger64i_v(target, index, &iData64);
    GLPP_GLAD_ERROR;
    return iData64;
}

void drawElementsBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
    glDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, basevertex);
    GLPP_GLAD_ERROR;
}

void drawElementsInstancedBaseVertex(PrimitiveMode mode, GLsizei count, PrimitiveType type, GLintptr indices, GLsizei instancecount, GLint basevertex)
{
    glDrawElementsInstancedBaseVertex((GLenum)mode, count, (GLenum)type, (void*)indices, instancecount, basevertex);
    GLPP_GLAD_ERROR;
}

void drawRangeElementsBaseVertex(PrimitiveMode mode, GLuint start, GLuint end, GLsizei count, PrimitiveType type, GLintptr indices, GLint basevertex)
{
    glDrawRangeElementsBaseVertex((GLenum)mode, start, end, count, (GLenum)type, (void*)indices, basevertex);
    GLPP_GLAD_ERROR;
}

void getMultisample(GLuint index, _Out_writes_(2) GLfloat* val)
{
    glGetMultisamplefv(GL_SAMPLE_POSITION, index, val);
    GLPP_GLAD_ERROR;
}

void multiDrawElementsBaseVertex(PrimitiveMode mode, _In_ const GLsizei* count, PrimitiveType type, _In_ const GLintptr* indices, GLsizei drawcount, _In_ const GLint* basevertex)
{
    glMultiDrawElementsBaseVertex((GLenum)mode, count, (GLenum)type, (void* const*)indices, drawcount, basevertex);
    GLPP_GLAD_ERROR;
}

void provokingVertex(ProvokeMode provokeMode)
{
    glProvokingVertex((GLenum)provokeMode);
    GLPP_GLAD_ERROR;
}

void sampleMask(GLuint maskNumber, GLbitfield mask)
{
    glSampleMaski(maskNumber, mask);
    GLPP_GLAD_ERROR;
}
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
} // namespace gl
