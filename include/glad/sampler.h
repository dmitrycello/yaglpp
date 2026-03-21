#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_SAMPLER_H
#define YAGLPP_SAMPLER_H

#ifdef YAGLPP_VERSION_3_3
namespace gl {
/*(3.3) OpenGL sampler object class derived from <Objects>*/
class Sampler : public Objects
{
public:
	using Objects::Objects;
	/*(3.3) Allocates an array of sampler objects of a given size, and generates their object names. Must be deallocated with <Sampler::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Sampler* Alloc(GLsizei n)
	{
		return (Sampler*)object_alloc(glGenSamplers, n);
	}

	/*(3.3) Binds a sampler to a texture unit by an index value ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1
	@param Specifies the index of the texture unit to which the sampler is bound*/
	void Bind(TextureUnit index)
	{
		object_bind(glBindSampler, index);
	}

	/*(3.3) Deletes previously allocated array of sampler object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Sampler* samplers)
	{
		object_dealloc(glDeleteSamplers, (GLuint*)samplers);
	}

	/*(3.3) Deletes valid OpenGL sampler object name and sets the sampler class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteSamplers);
	}

	/*(3.3) Deletes previously generated OpenGL sampler object names in a static array or a user-defined structure of samplers, namely sampler map, and sets its class objects in empty state. Allows to unset multiple samplers in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of sampler map returned by sizeof operator
	@param [in-out] Pointer to sampler map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* samplerMap)
	{
		object_delete_map(glDeleteSamplers, n, samplerMap);
	}

	/*(3.3) Generates OpenGL sampler object name in an empty sampler class object*/
	void Gen()
	{
		object_gen(glGenSamplers);
	}

	/*(3.3) Generates OpenGL sampler object name in an empty sampler class object, and binds a sampler to a texture unit by an index value ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1
	@param Specifies the index of the texture unit to which the sampler is bound*/
	void GenBind(TextureUnit index)
	{
		object_gen_bind(glGenSamplers, glBindSampler, index);
	}

	/*(3.3) Generates OpenGL sampler object names in a static array or a user-defined structure of samplers, namely sampler map. Allows to set multiple samplers in one function call. All class objects are silently overwritten
	@param The size in bytes of sampler map returned by sizeof operator
	@param [out] Pointer to sampler map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* samplerMap)
	{
		object_gen_map(glGenSamplers, n, samplerMap);
	}

	/*(3.3) Returns Sampler object currently bound to its target
	@return The Sampler object bound to its target, or empty object*/
	static Sampler GetBinding()
	{
		return Sampler(yaglpp_glad_integer(GL_SAMPLER_BINDING));
	}

	/*(3.3) (1) Returns four integer values that comprise the current RGBA color of the texture border
	@param [out] Stores four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void GetBorderColor(_Out_writes_(4) GLint* color);

	/*(3.3) (2) Returns four float values that comprise the current RGBA color of the texture border
	@param [out] Stores four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param The index of the object name, default 0*/
	void GetBorderColor(_Out_writes_(4) GLfloat* color);

	/*(3.3) Returns the current texture comparison function. MSVC getter for <compareFunc> property
	@param The index of the object name, default 0
	@return The texture comparison function value. The initial value is <Lequal>*/
	CompareFunc GetCompareFunc()
	{
		return (CompareFunc)get_sampler_parameter(GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.3) Gets the texture comparison mode for currently bound depth textures. MSVC getter for <compareMode> property
	@return Returns one of the selected texture compare mode values*/
	CompareMode GetCompareMode()
	{
		return (CompareMode)get_sampler_parameter(GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.3) Returns the current fixed level-of-detail bias value. MSVC getter for <lodBias> property
	@return The texture level-of-detail bias value*/
	GLfloat GetLodBias()
	{
		return get_sampler_parameter_float(GL_TEXTURE_LOD_BIAS);
	}

	/*(3.3) Gets the current texture magnification function. MSVC getter for <magFilter> property
	@return The texture magnification function value. The initial value is <Linear>*/
	Textures::MagFilter GetMagFilter()
	{
		return (Textures::MagFilter)get_sampler_parameter(GL_TEXTURE_MAG_FILTER);
	}

	/*(3.3) Returns the current texture maximum level-of-detail value. MSVC getter for <maxLod> property
	@return The maximum level-of-detail value. The initial value is 1000*/
	GLfloat GetMaxLod()
	{
		return get_sampler_parameter_float(GL_TEXTURE_MAX_LOD);
	}

	/*(3.3) Gets the current texture minifying function. MSVC getter for <minFilter> property
	@return The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	Textures::MinFilter GetMinFilter()
	{
		return (Textures::MinFilter)get_sampler_parameter(GL_TEXTURE_MIN_FILTER);
	}

	/*(3.3) Returns the current texture minimum level-of-detail value. MSVC getter for <minLod> property
	@return The minimum level-of-detail value. The initial value is -1000*/
	GLfloat GetMinLod()
	{
		return get_sampler_parameter_float(GL_TEXTURE_MIN_LOD);
	}

	/*(3.3) Returns the wrapping function for texture coordinate r. MSVC getter for <wrapR> property
	@return The current wrap mode for texture coordinate r. The initial value is <Repeat>*/
	Textures::WrapMode GetWrapR()
	{
		return (Textures::WrapMode)get_sampler_parameter(GL_TEXTURE_WRAP_R);
	}

	/*(3.3) Returns the wrapping function for texture coordinate s. MSVC getter for <wrapS> property
	@return The current wrap mode for texture coordinate s. The initial value is <Repeat>*/
	Textures::WrapMode GetWrapS()
	{
		return (Textures::WrapMode)get_sampler_parameter(GL_TEXTURE_WRAP_S);
	}

	/*(3.3) Returns the wrapping function for texture coordinate t. MSVC getter for <wrapT> property
	@return The current wrap mode for texture coordinate t. The initial value is <Repeat>*/
	Textures::WrapMode GetWrapT()
	{
		return (Textures::WrapMode)get_sampler_parameter(GL_TEXTURE_WRAP_T);
	}

	/*(3.3) Determines if a name corresponds to a sampler object. MSVC getter for <sampler> property
	@return True if active sampler object, false otherwise*/
	GLboolean IsSampler() const
	{
		return object_is(glIsSampler);
	}

	/*(3.3) Determines if the sampler object is currently bound to the active texture unit. MSVC getter for <binding> property
	@return True if sampler object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_SAMPLER_BINDING, Get());
	}

	/*(3.3) (1) Specifies four integer values that should be used for border texels
	@param [in] Loads four integer texture color values. The initial value is (0, 0, 0, 0)*/
	void SetBorderColor(_In_reads_(4) const GLint* color);

	/*(3.3) (2) Specifies four float values that should be used for border texels
	@param [in] Loads four float texture color values. The initial value is (0.0, 0.0, 0.0, 0.0)*/
	void SetBorderColor(_In_reads_(4) const GLfloat* color);

	/*(3.3) Specifies the comparison operator used when texture compare mode flag is set. MSVC setter for <compareFunc> property
	@param The texture comparison function value. The initial value is <Lequal>*/
	void SetCompareFunc(CompareFunc func)
	{
		sampler_parameter(GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.3) Specifies the texture comparison mode flag for currently bound depth textures. MSVC setter for <compareMode> property
	@param True if interpolated and clamped r texture coordinate should be compared to the value in the currently bound depth texture*/
	void SetCompareMode(CompareMode mode)
	{
		sampler_parameter(GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.3) Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling. MSVC setter for <lodBias> property
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void SetLodBias(GLfloat bias)
	{
		sampler_parameter(GL_TEXTURE_LOD_BIAS, bias);
	}

	/*(3.3) The texture magnification function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be magified. MSVC setter for <magFilter> property
	@param The magnification function value. The initial value is <Linear>*/
	void SetMagFilter(Textures::MagFilter func)
	{
		sampler_parameter(GL_TEXTURE_MAG_FILTER, (GLint)func);
	}

	/*(3.3) Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap. MSVC setter for <maxLod> property
	@param The maximum level-of-detail value. The initial value is 1000*/
	void SetMaxLod(GLfloat maxlod)
	{
		sampler_parameter(GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*(3.3) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. MSVC setter for <minFilter> property
	@param The texture minifying function value. The initial value is <NearestMipmapLinear>*/
	void SetMinFilter(Textures::MinFilter filter)
	{
		sampler_parameter(GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.3) Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap. MSVC setter for <minLod> property
	@param The minimum level-of-detail value. The initial value is -1000*/
	void SetMinLod(GLfloat maxlod)
	{
		sampler_parameter(GL_TEXTURE_MIN_LOD, maxlod);
	}

	/*(3.3) Sets the wrapping function for texture coordinate r. MSVC setter for <wrapR> property
	@param The texture wrap mode for coordinate r*/
	void SetWrapR(Textures::WrapMode wrap)
	{
		sampler_parameter(GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.3) Sets the wrapping function for texture coordinate s. MSVC setter for <wrapS> property
	@param The texture wrap mode for coordinate s*/
	void SetWrapS(Textures::WrapMode wrap)
	{
		sampler_parameter(GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.3) Sets the wrapping function for texture coordinate t. MSVC setter for <wrapT> property
	@param The texture wrap mode for coordinate t*/
	void SetWrapT(Textures::WrapMode wrap)
	{
		sampler_parameter(GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.3) Restores the internal state of a texture unit specified by an index value ranging from 0 to the value returned by <GetMaxCombinedTextureImageUnits> minus 1
	@param Specifies the index of the texture unit to restore*/
	static void Unbind(TextureUnit index)
	{
		glBindSampler((GLuint)index, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to check if active sampler object*/
	__declspec(property(get = IsSampler)) GLboolean sampler;

	/*(3.3) Read-only property to determine if the sampler object is currently bound to the active texture unit*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.3) Read-write property for current texture comparison function*/
	__declspec(property(get = GetCompareFunc, put = SetCompareFunc)) CompareFunc compareFunc;

	/*(3.3) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = GetCompareMode, put = SetCompareMode)) CompareMode compareMode;

	/*(3.3) Read-write property for current fixed level-of-detail bias value*/
	__declspec(property(get = GetLodBias, put = SetLodBias)) GLfloat lodBias;

	/*(3.3) Read-write property for current texture magnification function*/
	__declspec(property(get = GetMagFilter, put = SetMagFilter)) Textures::MagFilter magFilter;

	/*(3.3) Read-write property for current texture maximum level-of-detail value*/
	__declspec(property(get = GetMaxLod, put = SetMaxLod)) GLfloat maxLod;

	/*(3.3) Read-write property for current texture minifying function*/
	__declspec(property(get = GetMinFilter, put = SetMinFilter)) Textures::MinFilter minFilter;

	/*(3.3) Read-write property for current texture minimum level-of-detail value*/
	__declspec(property(get = GetMinLod, put = SetMinLod)) GLfloat minLod;

	/*(3.3) Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = GetWrapR, put = SetWrapR)) Textures::WrapMode wrapR;

	/*(3.3) Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = GetWrapS, put = SetWrapS)) Textures::WrapMode wrapS;

	/*(3.3) Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = GetWrapT, put = SetWrapT)) Textures::WrapMode wrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	GLint get_sampler_parameter(GLenum pname);
	GLfloat get_sampler_parameter_float(GLenum pname);
	void sampler_parameter(GLenum pname, GLint param);
	void sampler_parameter(GLenum pname, GLfloat param);
}; // class Sampler : public Object

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint Sampler::get_sampler_parameter(GLenum pname)
{
	GLint iResult;
	glGetSamplerParameteriv(object_id(), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

GLfloat Sampler::get_sampler_parameter_float(GLenum pname)
{
	GLfloat fResult;
	glGetSamplerParameterfv(object_id(), pname, &fResult);
	YAGLPP_GLAD_ERROR;
	return fResult;
}

void Sampler::sampler_parameter(GLenum pname, GLint param)
{
	glSamplerParameteri(object_id(), pname, param);
	YAGLPP_GLAD_ERROR;
}

void Sampler::sampler_parameter(GLenum pname, GLfloat param)
{
	glSamplerParameterf(object_id(), pname, param);
	YAGLPP_GLAD_ERROR;
}

void Sampler::GetBorderColor(_Out_writes_(4) GLint* color)
{
	glGetSamplerParameteriv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
	YAGLPP_GLAD_ERROR;
}

void Sampler::GetBorderColor(_Out_writes_(4) GLfloat* color)
{
	glGetSamplerParameterfv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
	YAGLPP_GLAD_ERROR;
}

void Sampler::SetBorderColor(_In_reads_(4) const GLint* color)
{
	glSamplerParameteriv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
	YAGLPP_GLAD_ERROR;
}

void Sampler::SetBorderColor(_In_reads_(4) const GLfloat* color)
{
	glSamplerParameterfv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint Sampler::get_sampler_parameter(GLenum pname)
{
	GLint i; glGetSamplerParameteriv(object_id(), pname, &i); return i;
}

inline GLfloat Sampler::get_sampler_parameter_float(GLenum pname)
{
	GLfloat f; glGetSamplerParameterfv(object_id(), pname, &f); return f;
}

inline void Sampler::sampler_parameter(GLenum pname, GLint param)
{
	glSamplerParameteri(object_id(), pname, param);
}

inline void Sampler::sampler_parameter(GLenum pname, GLfloat param)
{
	glSamplerParameterf(object_id(), pname, param);
}

inline void Sampler::GetBorderColor(_Out_writes_(4) GLint* color)
{
	glGetSamplerParameteriv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::GetBorderColor(_Out_writes_(4) GLfloat* color)
{
	glGetSamplerParameterfv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::SetBorderColor(_In_reads_(4) const GLint* color)
{
	glSamplerParameteriv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
}

inline void Sampler::SetBorderColor(_In_reads_(4) const GLfloat* color)
{
	glSamplerParameterfv(object_id(), GL_TEXTURE_BORDER_COLOR, color);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_3
#endif // #ifndef YAGLPP_SAMPLER_H
