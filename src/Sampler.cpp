#define YAGLPP_BUILD_LIB
#include <yaglpp/Sampler.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_3
namespace gl {
void Sampler::setSampler(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteSampler();
		}
	}
	else if (gen == GL_TRUE)
	{
		genSampler();
	}
}

#ifdef _DEBUG
GLint Sampler::_getSamplerParameter(GLenum pname)
{
	GLint iData = 0;
	glGetSamplerParameteriv(_sampler_id(), pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

GLfloat Sampler::_getSamplerParameterFloat(GLenum pname)
{
	GLfloat fData = 0.0f;
	glGetSamplerParameterfv(_sampler_id(), pname, &fData);
	_YAGLPP_GLAD_ERROR_;
	return fData;
}

void Sampler::_samplerParameter(GLenum pname, GLint param)
{
	glSamplerParameteri(_sampler_id(), pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::_samplerParameter(GLenum pname, GLfloat param)
{
	glSamplerParameterf(_sampler_id(), pname, param);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::bindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, _sampler_id());
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::getTextureBorderColor(_Out_writes_(4) GLint* color)
{
	glGetSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::getTextureBorderColor(_Out_writes_(4) GLfloat* color)
{
	glGetSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::setTextureBorderColor(_In_reads_(4) const GLint* color)
{
	glSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::setTextureBorderColor(_In_reads_(4) const GLfloat* color)
{
	glSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
	_YAGLPP_GLAD_ERROR_;
}

void Sampler::unbindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, 0);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_3
