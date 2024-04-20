#define GLPP_BUILD_LIB
#include <glpp/Renderbuffer.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_0
namespace gl {
void Renderbuffer::_bindRenderbuffer(GLuint* tls, GLuint renderbuffer)
{
	if (*tls == renderbuffer)
	{
		return;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	GLPP_GLAD_ERROR;
	*tls = renderbuffer;
}

GLint Renderbuffer::_getRenderbufferParameter(GLenum pname)
{
	GLint iResult = 0;
	_renderbuffer_bind(_tlsRenderbuffer());
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &iResult);
	GLPP_GLAD_ERROR;
	return iResult;
}

void Renderbuffer::renderbufferStorage(ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	_renderbuffer_bind(_tlsRenderbuffer());
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
	GLPP_GLAD_ERROR;
}

void Renderbuffer::renderbufferStorageMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	_renderbuffer_bind(_tlsRenderbuffer());
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
	GLPP_GLAD_ERROR;
}
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_0
