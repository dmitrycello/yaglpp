#define YAGLPP_BUILD_LIB
#include <yaglpp/Renderbuffer.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_0
namespace gl {
GLint Renderbuffer::_getRenderbufferParameter(GLenum pname)
{
	GLint iResult = 0;
	bindRenderbuffer();
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &iResult);
	_YAGLPP_GLAD_ERROR_;
	return iResult;
}

void Renderbuffer::bindRenderbuffer()
{
	GLuint uBound, uId = _renderbuffer_id();
	glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != uId)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, uId);
		_YAGLPP_GLAD_ERROR_;
	}
}

void Renderbuffer::renderbufferStorage(ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	bindRenderbuffer();
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
	_YAGLPP_GLAD_ERROR_;
}

void Renderbuffer::renderbufferStorageMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	bindRenderbuffer();
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
	_YAGLPP_GLAD_ERROR_;
}

void Renderbuffer::setRenderbuffer(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteRenderbuffer();
		}
	}
	else if (gen == GL_TRUE)
	{
		genRenderbuffer();
	}
}

void Renderbuffer::unbindRenderbuffer()
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void Renderbuffer::unbindTarget()
{
	GLuint uBound;
	glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != 0)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		_YAGLPP_GLAD_ERROR_;
	}
}
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
