#define GLPP_BUILD_LIB
#include <glpp/Sampler.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_3
namespace gl {
GLint Sampler::_getSamplerParameter(GLenum pname)
{
	GLint iData = 0;
	glGetSamplerParameteriv(_sampler_id(), pname, &iData);
	GLPP_GLAD_ERROR;
	return iData;
}

GLfloat Sampler::_getSamplerParameterFloat(GLenum pname)
{
	GLfloat fData = 0;
	glGetSamplerParameterfv(_sampler_id(), pname, &fData);
	GLPP_GLAD_ERROR;
	return fData;
}

void Sampler::_samplerParameter(GLenum pname, GLint param)
{
	glSamplerParameteri(_sampler_id(), pname, param);
	GLPP_GLAD_ERROR;
}

void Sampler::_samplerParameter(GLenum pname, GLfloat param)
{
	glSamplerParameterf(_sampler_id(), pname, param);
	GLPP_GLAD_ERROR;
}

void Sampler::bindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, _sampler_id());
	GLPP_GLAD_ERROR;
}

void Sampler::getTextureBorderColor(_Out_writes_(4) GLint* color)
{
	glGetSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	GLPP_GLAD_ERROR;
}

void Sampler::getTextureBorderColor(_Out_writes_(4) GLfloat* color)
{
	glGetSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	GLPP_GLAD_ERROR;
}

void Sampler::setTextureBorderColor(_In_reads_(4) const GLint* color)
{
	glSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	GLPP_GLAD_ERROR;
}

void Sampler::setTextureBorderColor(_In_reads_(4) const GLfloat* color)
{
	glSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	GLPP_GLAD_ERROR;
}

void Sampler::unbindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, 0);
	GLPP_GLAD_ERROR;
}
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_3
