#pragma once
#include "gladpp.h"
#include "_Object.h"
#ifdef GL_VERSION_3_3
namespace gl {
/*(3.3) OpenGL sampler object class derived from <_Object>*/
class Sampler : public _Object
{
protected:
	GLuint _sampler_id()
	{
		return _object_id(glGenSamplers);
	}

	GLint _getSamplerParameter(GLenum pname);
	GLfloat _getSamplerParameterFloat(GLenum pname);
	void _samplerParameter(GLenum pname, GLint param);
	void _samplerParameter(GLenum pname, GLfloat param);

public:
	/*(3.3) (1) Constructs an empty sampler object*/
	Sampler() : _Object() {}

	/*(3.3) (2) Constucts a buffer object with <assignBuffer>*/
	Sampler(Samplers& buffers, GLuint index)
	{
		assignSampler(buffers, index);
	}

	/*(3.3) Cleans up the valid sampler object*/
	~Sampler()
	{
		if (isObject())
		{
			deleteSampler();
		}
	}

	/*Assigns an empty sampler object with the object name from the sampler multi-object
	@param The sampler multi-object
	@param The index of the object name*/
	void assignSampler(Samplers& samplers, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)samplers, index, GL_TRUE); // Single target
#else // #ifdef _DEBUG
		_object_assign((_Objects&)samplers, index);
#endif // #ifdef _DEBUG
	}

	/*(3.3) Binds a sampler to a texture unit by an index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1
	@param Specifies the index of the texture unit to which the sampler is bound*/
	void bindSampler(TextureUnit index);

	/*(3.3) Explicitly deletes previously generated single sampler object*/
	void deleteSampler()
	{
		_object_delete(glDeleteSamplers);
	}

	/*(3.3) Explicitly generates single sampler object*/
	void genSampler()
	{
		_object_gen(glGenSamplers);
	}

	/*(3.3) Gets the maximum supported texture image units that can be used to access texture maps from the vertex shader and the fragment processor combined
	@return The maximum supported texture image units. The value must be at least 48*/
	static GLuint getMaxCombinedTextureImageUnits()
	{
		return _getInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	}

	/*(3.3) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void getTextureBorderColor(_Out_writes_(4) GLint* color);

	/*(3.3) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param The index of the object name, default 0*/
	void getTextureBorderColor(_Out_writes_(4) GLfloat* color);

	/*(3.3) Returns the current texture comparison function
	@param The index of the object name, default 0
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc getTextureCompareFunc()
	{
		return (CompareFunc)_getSamplerParameter(GL_TEXTURE_COMPARE_FUNC);
	}
	/*(3.3) Gets the texture comparison mode for currently bound depth textures
	@return Returns one of the selected texture compare mode values*/
	TextureCompareMode getTextureCompareMode()
	{
		return (TextureCompareMode)_getSamplerParameter(GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.3) Returns the current fixed level-of-detail bias value
	@return The texture level-of-detail bias value*/
	GLfloat getTextureLodBias()
	{
		return _getSamplerParameterFloat(GL_TEXTURE_LOD_BIAS);
	}

	/*(3.3) Gets the current texture magnification function
	@return The texture magnification function value. The initial value is <Linear>*/
	TextureMagFilter getTextureMagFilter()
	{
		return (TextureMagFilter)_getSamplerParameter(GL_TEXTURE_MAG_FILTER);
	}

	/*(3.3) Returns the current texture maximum level-of-detail value
	@return The maximum level-of-detail value. The initial value is 1000*/
	GLfloat getTextureMaxLod()
	{
		return _getSamplerParameterFloat(GL_TEXTURE_MAX_LOD);
	}

	/*(3.3) Gets the current texture minifying function
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	TextureMinFilter getTextureMinFilter()
	{
		return (TextureMinFilter)_getSamplerParameter(GL_TEXTURE_MIN_FILTER);
	}

	/*(3.3) Returns the current texture minimum level-of-detail value
	@return The minimum level-of-detail value. The initial value is -1000*/
	GLfloat getTextureMinLod()
	{
		return _getSamplerParameterFloat(GL_TEXTURE_MIN_LOD);
	}

	/*(3.3) Returns the wrapping function for texture coordinate r
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapR()
	{
		return (TextureWrapMode)_getSamplerParameter(GL_TEXTURE_WRAP_R);
	}

	/*(3.3) Returns the wrapping function for texture coordinate s
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapS()
	{
		return (TextureWrapMode)_getSamplerParameter(GL_TEXTURE_WRAP_S);
	}

	/*(3.3) Returns the wrapping function for texture coordinate t
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	TextureWrapMode getTextureWrapT()
	{
		return (TextureWrapMode)_getSamplerParameter(GL_TEXTURE_WRAP_T);
	}

	/*(3.3) Determines via API if valid sampler object
	@return True if valid sampler object, false otherwise*/
	GLboolean isSampler()
	{
		return glIsSampler(_sampler_id());
	}

	/*(3.3) Determines via API if the sampler object is currently bound to the active texture unit
	@return True if the sampler object is bound, false otherwise*/
	GLboolean isSamplerBinding()
	{
		return _sampler_id() == _getInteger(GL_SAMPLER_BINDING);
	}

	/*(3.3) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void setTextureBorderColor(_In_reads_(4) const GLint* color);

	/*(3.3) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void setTextureBorderColor(_In_reads_(4) const GLfloat* color);

	/*(3.3) Specifies the comparison operator used when texture compare mode flag is set
	@param The texture comparison function value. The initial value is <Lequal>*/
	void setTextureCompareFunc(CompareFunc func)
	{
		_samplerParameter(GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.3) Specifies the texture comparison mode flag for currently bound depth textures
	@param True if interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture*/
	void setTextureCompareMode(TextureCompareMode mode)
	{
		_samplerParameter(GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.3) Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void setTextureLodBias(GLfloat bias)
	{
		_samplerParameter(GL_TEXTURE_LOD_BIAS, bias);
	}

	/*(3.3) The texture magnification function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be magified
	@param The magnification function value. The initial value is <Linear>*/
	void setTextureMagFilter(TextureMagFilter func)
	{
		_samplerParameter(GL_TEXTURE_MAG_FILTER, (GLint)func);
	}

	/*(3.3) Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap
	@param The maximum level-of-detail value. The initial value is 1000*/
	void setTextureMaxLod(GLfloat maxlod)
	{
		_samplerParameter(GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*(3.3) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void setTextureMinFilter(TextureMinFilter filter)
	{
		_samplerParameter(GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.3) Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap
	@param The minimum level-of-detail value. The initial value is -1000*/
	void setTextureMinLod(GLfloat maxlod)
	{
		_samplerParameter(GL_TEXTURE_MIN_LOD, maxlod);
	}

	/*(3.3) Sets the wrapping function for texture coordinate r
	@param The texture wrap mode for coordinate r*/
	void setTextureWrapR(TextureWrapMode wrap)
	{
		_samplerParameter(GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.3) Sets the wrapping function for texture coordinate s
	@param The texture wrap mode for coordinate s*/
	void setTextureWrapS(TextureWrapMode wrap)
	{
		_samplerParameter(GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.3) Sets the wrapping function for texture coordinate t
	@param The texture wrap mode for coordinate t*/
	void setTextureWrapT(TextureWrapMode wrap)
	{
		_samplerParameter(GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.3) Restores the internal state of a texture unit specified by an index value ranging from 0 to the value returned by <getMaxCombinedTextureImageUnits> minus 1
	@param Specifies the index of the texture unit to restore*/
	static void unbindSampler(TextureUnit index);
}; // class Sampler : public _Object

#ifndef _DEBUG
inline GLint Sampler::_getSamplerParameter(GLenum pname)
{
	GLint i = 0; glGetSamplerParameteriv(_sampler_id(), pname, &i); return i;
}

inline GLfloat Sampler::_getSamplerParameterFloat(GLenum pname)
{
	GLfloat f; glGetSamplerParameterfv(_sampler_id(), pname, &f); return f;
}

inline void Sampler::_samplerParameter(GLenum pname, GLint param)
{
	glSamplerParameteri(_sampler_id(), pname, param);
}

inline void Sampler::_samplerParameter(GLenum pname, GLfloat param)
{
	glSamplerParameterf(_sampler_id(), pname, param);
}

inline void Sampler::bindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, _sampler_id());
}

inline void Sampler::getTextureBorderColor(_Out_writes_(4) GLint* color)
{
	glGetSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::getTextureBorderColor(_Out_writes_(4) GLfloat* color)
{
	glGetSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::setTextureBorderColor(_In_reads_(4) const GLint* color)
{
	glSamplerParameteriv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::setTextureBorderColor(_In_reads_(4) const GLfloat* color)
{
	glSamplerParameterfv(_sampler_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::unbindSampler(TextureUnit index)
{
	glBindSampler((GLuint)index, 0);
}
#endif // #ifndef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_3
