#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_TEXTURES_T_H
#define YAGLPP_TEXTURES_T_H

namespace gl {
template <GLenum T, GLenum B> class Textures_1 : public Textures
{
public:
	using Textures::Textures;
	/*Binds texture object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		Objects::object_bind(glBindTexture, T);
	}

	/*Generates OpenGL texture object name in an empty texture class object, and bind it to its target in one function call*/
	void GenBind()
	{
		Objects::object_gen_bind(glGenTextures, glBindTexture, T);
	}

	/*Determines if the texture object is currently bound to its target. MSVC getter for <binding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return Objects::object_binding(B, Get());
	}

	/*Unbinds any texture object bound to particular target, and restores its default texture. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindTexture(T, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for state of the texture binding*/
	__declspec(property(get = IsBinding)) GLboolean binding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // template <GLenum T, GLenum B, GLenum P> class Textures_1 : public Textures

template <GLenum T, GLenum B> class Textures_2 : public Textures_1<T, B>
{
public:
	using Textures_1<T, B>::Textures_1;
	/*(1) Returns four integer values that comprise the current RGBA color of the texture border. The initial value is (0, 0, 0, 0)
	@param [out] Stores four integer texture color values*/
	void GetBorderColor(_Out_writes_(4) GLint* color)
	{
		Textures::get_tex_parameter(T, B, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(2) Returns four float values that comprise the current RGBA color of the texture border. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [out] Stores four float texture color values*/
	void GetBorderColor(_Out_writes_(4) GLfloat* color)
	{
		Textures::get_tex_parameter(T, B, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*Returns the current texture comparison function. The initial value is <Lequal>. MSVC getter for <compareFunc> property
	@return The texture comparison function value*/
	CompareFunc GetCompareFunc()
	{
		return (CompareFunc)Textures::get_tex_parameter(T, B, GL_TEXTURE_COMPARE_FUNC);
	}

	/*Gets the current texture magnification function. MSVC getter for <magFilter> property. The initial value is <Linear>
	@return The texture magnification function value*/
	Textures::MagFilter GetMagFilter()
	{
		return (Textures::MagFilter)Textures::get_tex_parameter(T, B, GL_TEXTURE_MAG_FILTER);
	}

	/*Gets the current texture minifying function. The initial value is <NearestMipmapLinear>. MSVC getter for <minFilter> property
	@return The texture minifying function value*/
	Textures::MinFilter GetMinFilter()
	{
		return (Textures::MinFilter)Textures::get_tex_parameter(T, B, GL_TEXTURE_MIN_FILTER);
	}

	/*Returns the wrapping function for texture coordinate r. The initial value is <Repeat>. MSVC getter for <wrapR> property
	@return The current wrap mode for texture coordinate r*/
	Textures::WrapMode GetWrapR()
	{
		return (Textures::WrapMode)Textures::get_tex_parameter(T, B, GL_TEXTURE_WRAP_R);
	}

	/*Returns the wrapping function for texture coordinate s. The initial value is <Repeat>. MSVC getter for <wrapS> property
	@return The current wrap mode for texture coordinate s*/
	Textures::WrapMode GetWrapS()
	{
		return (Textures::WrapMode)Textures::get_tex_parameter(T, B, GL_TEXTURE_WRAP_S);
	}

	/*Returns the wrapping function for texture coordinate t. The initial value is <Repeat>. MSVC getter for <wrapT> property
	@return The current wrap mode for texture coordinate t*/
	Textures::WrapMode GetWrapT()
	{
		return (Textures::WrapMode)Textures::get_tex_parameter(T, B, GL_TEXTURE_WRAP_T);
	}

	/*(1) Specifies four integer values that should be used for border texels. The initial value is (0, 0, 0, 0)
	@param [in] Loads four integer texture color values*/
	void SetBorderColor(_In_reads_(4) const GLint* color)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(2) Specifies four float values that should be used for border texels. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [in] Loads four float texture color values*/
	void SetBorderColor(_In_reads_(4) const GLfloat* color)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}. The initial value is <Lequal>. Used as a setter of <compareFunc> property
	@param The texture comparison function value*/
	void SetCompareFunc(CompareFunc func)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*Sets the texture magnification function value. The initial value is <Linear>. Used as a setter of <magFilter> property
	@param Specifies the texture magnification function's value*/
	void SetMagFilter(Textures::MagFilter filter)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. The initial value is <NearestMipmapLinear>. Used as a setter of <minFilter> property
	@param The texture minifying function value*/
	void SetMinFilter(Textures::MinFilter filter)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*Sets the wrapping function for texture coordinate r. The initial value is <Repeat>. Used as a setter of <wrapR> property
	@param The texture wrap mode for coordinate r*/
	void SetWrapR(Textures::WrapMode wrap)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*Sets the wrapping function for texture coordinate s. The initial value is <Repeat>. Used as a setter of <wrapS> property
	@param The texture wrap mode for coordinate s*/
	void SetWrapS(Textures::WrapMode wrap)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*Sets the wrapping function for texture coordinate t. The initial value is <Repeat>. Used as a setter of <wrapT> property
	@param The texture wrap mode for coordinate t*/
	void SetWrapT(Textures::WrapMode wrap)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for current texture comparison function*/
	__declspec(property(get = GetCompareFunc, put = SetCompareFunc)) CompareFunc compareFunc;

	/*Read-write property for current texture magnification function*/
	__declspec(property(get = GetMagFilter, put = SetMagFilter)) Textures::MagFilter magFilter;

	/*Read-write property for current texture minifying function*/
	__declspec(property(get = GetMinFilter, put = SetMinFilter)) Textures::MinFilter minFilter;

	/*Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = GetWrapR, put = SetWrapR)) Textures::WrapMode wrapR;

	/*Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = GetWrapS, put = SetWrapS)) Textures::WrapMode wrapS;

	/*Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = GetWrapT, put = SetWrapT)) Textures::WrapMode wrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Gets the texture comparison mode for currently bound depth textures. MSVC getter for <compareMode> property
	@return Returns one of the selected texture compare mode values*/
	CompareMode GetCompareMode()
	{
		return (CompareMode)Textures::get_tex_parameter(T, B, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.0) Sets the texture comparison mode for currently bound depth textures. Used as a setter of <compareMode> property
	@param Specifies the texture compare mode value*/
	void SetCompareMode(CompareMode mode)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.0) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = GetCompareMode, put = SetCompareMode)) CompareMode compareMode;
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value. The initial value is <Alpha>. MSVC getter for <swizzleA> property
	@return The alpha component swizzle value*/
	Textures::SwizzleMask GetSwizzleA()
	{
		return (Textures::SwizzleMask)Textures::get_tex_parameter(T, B, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value. The initial value is <Blue>. MSVC getter for <swizzleB> property
	@return The blue component swizzle value*/
	Textures::SwizzleMask GetSwizzleB()
	{
		return (Textures::SwizzleMask)Textures::get_tex_parameter(T, B, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value. The initial value is <Green>. MSVC getter for <swizzleG> property
	@return The green component swizzle value*/
	Textures::SwizzleMask GetSwizzleG()
	{
		return (Textures::SwizzleMask)Textures::get_tex_parameter(T, B, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value. The initial value is <Red>. MSVC getter for <swizzleR> property
	@return The red component swizzle value*/
	Textures::SwizzleMask GetSwizzleR()
	{
		return (Textures::SwizzleMask)Textures::get_tex_parameter(T, B, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)
	@param [out] Stores four swizzle mask values*/
	void GetSwizzleRGBA(_Out_writes_(4) Textures::SwizzleMask* swizzle)
	{
		Textures::get_tex_parameter(T, B, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader. The initial value is <Alpha>. Used as a setter of <swizzleA> property
	@param The alpha component swizzle value*/
	void SetSwizzleA(Textures::SwizzleMask swizzle)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader. The initial value is <Blue>. Used as a setter of <swizzleB> property
	@param The blue component swizzle value*/
	void SetSwizzleB(Textures::SwizzleMask swizzle)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader. The initial value is <Green>. Used as a setter of <swizzleG> property
	@param The green component swizzle value*/
	void SetSwizzleG(Textures::SwizzleMask swizzle)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader. The initial value is <Red>. Used as a setter of <swizzleR> property
	@param The red component swizzle value*/
	void SetSwizzleR(Textures::SwizzleMask swizzle)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader
	@param [in] Loads four swizzle mask values. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)*/
	void SetSwizzleRGBA(_In_reads_(4) const Textures::SwizzleMask* swizzle)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.3) Read-write property for current alpha component swizzle value*/
	__declspec(property(get = GetSwizzleA, put = SetSwizzleA)) Textures::SwizzleMask swizzleA;

	/*(3.3) Read-write property for current blue component swizzle value*/
	__declspec(property(get = GetSwizzleB, put = SetSwizzleB)) Textures::SwizzleMask swizzleB;

	/*(3.3) Read-write property for current green component swizzle value*/
	__declspec(property(get = GetSwizzleG, put = SetSwizzleG)) Textures::SwizzleMask swizzleG;

	/*(3.3) Read-write property for current red component swizzle value*/
	__declspec(property(get = GetSwizzleR, put = SetSwizzleR)) Textures::SwizzleMask swizzleR;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
}; // template <GLenum T, GLenum B, GLenum P> class Textures_2 : public Textures_1<T, B, P>

template <GLenum T, GLenum B, GLenum P> class Textures_3 : public Textures_2<T, B>
{
public:
	using Textures_2<T, B>::Textures_2;
	/*Returns the current base texture mipmap level. MSVC getter for <baseLevel> property. The initial value is 0
	@return The lowest defined mipmap level*/
	GLint GetBaseLevel()
	{
		return Textures::get_tex_parameter(T, B, GL_TEXTURE_BASE_LEVEL);
	}

	/*Returns the current fixed level-of-detail bias value. MSVC getter for <lodBias> property
	@return The texture level-of-detail bias value*/
	GLfloat GetLodBias()
	{
		return Textures::get_tex_parameter_float(T, B, GL_TEXTURE_LOD_BIAS);
	}

	/*Returns the current maximum texture mipmap array level. The initial value is 1000. MSVC getter for <maxLevel> property
	@return The texture maximum mipmap level*/
	GLint GetMaxLevel()
	{
		return Textures::get_tex_parameter(T, B, GL_TEXTURE_MAX_LEVEL);
	}

	/*Returns the current texture maximum level-of-detail value. The initial value is 1000. MSVC getter for <maxLod> property
	@return The maximum level-of-detail value*/
	GLfloat GetMaxLod()
	{
		return Textures::get_tex_parameter_float(T, B, GL_TEXTURE_MAX_LOD);
	}

	/*Returns the current texture minimum level-of-detail value. The initial value is -1000. MSVC getter for <minLod> property
	@return The minimum level-of-detail value*/
	GLfloat GetMinLod()
	{
		return Textures::get_tex_parameter_float(T, B, GL_TEXTURE_MIN_LOD);
	}

	/*Recalculates the capacity of internal storage resolution of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of ALPHA component*/
	static GLuint GetProxyAlphaSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*Returns internal storage resolution of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	static GLuint GetProxyBlueSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*Returns the number of unsigned bytes of the compressed proxy texture that would be returned from <GetCompressedImage>
	@param Specifies the level-of-detail number of the proxy texture
	@return The number of unsigned bytes of the compressed proxy texture*/
	static GLsizei GetProxyCompressedImageSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*Returns internal storage resolution of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLuint GetProxyDepthSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*Returns internal storage resolution of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLuint GetProxyGreenSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*Returns the internal format capacity of the proxy texture
	@param Specifies the level-of-detail number of the desired image
	@return The internal format capacity of the texture*/
	static Textures::Internalformat GetProxyInternalFormat(GLint level)
	{
		return (Textures::Internalformat)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*Returns internal storage resolution of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLuint GetProxyRedSize(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_RED_SIZE);
	}

	/*Returns the width of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei GetProxyWidth(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_WIDTH);
	}

	/*Returns boolean value indicating if the proxy texture was queried in a compressed internal format
	@param Specifies the level-of-detail number of the proxy texture
	@return True if the proxy texture was queried as compressed, false otherwise*/
	static GLboolean IsProxyCompressed(GLint level)
	{
		return Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_COMPRESSED);
	}

	/*Specifies the index of the lowest defined mipmap level. The initial value is 0. Used as a setter of <baseLevel> property
	@param The lowest defined mipmap level*/
	void SetBaseLevel(GLint level)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_BASE_LEVEL, level);
	}

	/*Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling. The initial value is 0.0. Used as a setter of <lodBias> property
	@param The texture level-of-detail bias value which implementation-defined range is limited by maximum texture lod bias*/
	void SetLodBias(GLfloat bias)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_LOD_BIAS, bias);
	}

	/*Sets the index of the highest defined mipmap level. The initial value is 1000. Used as a setter of <maxLevel> property
	@param The texture maximum mipmap level*/
	void SetMaxLevel(GLint maxlevel)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_MAX_LEVEL, maxlevel);
	}

	/*Sets the maximum level-of-detail value that limits the selection of the lowest resolution mipmap. The initial value is 1000. Used as a setter of <maxLod> property
	@param The maximum level-of-detail value*/
	void SetMaxLod(GLfloat maxlod)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_MAX_LOD, maxlod);
	}

	/*Sets the minimum level-of-detail value that limits the selection of the highest resolution mipmap. The initial value is -1000. Used as a setter of <minLod> property
	@param The minimum level-of-detail value*/
	void SetMinLod(GLfloat minlod)
	{
		Textures::tex_parameter(T, B, GL_TEXTURE_MIN_LOD, minlod);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for index of the lowest defined mipmap level*/
	__declspec(property(get = GetBaseLevel, put = SetBaseLevel)) GLint baseLevel;

	/*Read-write property for current fixed level-of-detail bias value*/
	__declspec(property(get = GetLodBias, put = SetLodBias)) GLfloat lodBias;

	/*Read-write property for current maximum texture mipmap array level*/
	__declspec(property(get = GetMaxLevel, put = SetMaxLevel)) GLint maxLevel;

	/*Read-write property for current texture maximum level-of-detail value*/
	__declspec(property(get = GetMaxLod, put = SetMaxLod)) GLfloat maxLod;

	/*Read-write property for current texture minimum level-of-detail value*/
	__declspec(property(get = GetMinLod, put = SetMinLod)) GLfloat minLod;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Generates mipmaps for specified texture target*/
	void GenerateMipmap()
	{
		Textures::generate_mipmap(T, B);
	}

	/*(3.0) Returns the type of ALPHA component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static Textures::ComponentType GetProxyAlphaType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static Textures::ComponentType GetProxyBlueType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the type of DEPTH component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static Textures::ComponentType GetProxyDepthType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static Textures::ComponentType GetProxyGreenType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of RED component of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The type of RED component of the proxy texture*/
	static Textures::ComponentType GetProxyRedType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, level, GL_TEXTURE_RED_TYPE);
	}
#endif // #ifdef YAGLPP_VERSION_3_0
}; // template <GLenum T, GLenum B, GLenum P> class Textures_3 : public Textures_2<T, B, P>

template <GLenum T, GLenum B, GLenum P> class Textures_4 : public Textures_3<T, B, P>
{
public:
	using Textures_3<T, B, P>::Textures_3;
	/*Returns internal storage resolution of ALPHA component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	GLuint GetAlphaSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*Returns internal storage resolution of BLUE component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	GLuint GetBlueSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(1) Return a compressed one-dimensional texture image into client's memory of the size returned by <GetCompressedImageSize>. (2.1) Pixel pack buffer must be unbound from its target
	@param Specifies the level-of-detail number of the desired image
	@param [out] Specifies a pointer to store the compressed texture image*/
	void GetCompressedImage(GLint level, _Out_ void* pixels)
	{
		Textures::get_compressed_tex_image(T, B, level, pixels);
	}

	/*Returns the number of unsigned bytes of the compressed texture image that would be returned from <GetCompressedImage>
	@param Specifies the level-of-detail number of the desired image
	@return The number of unsigned bytes of the compressed texture image*/
	GLsizei GetCompressedImageSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*Returns internal storage resolution of DEPTH component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of DEPTH component*/
	GLuint GetDepthSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*Returns internal storage resolution of GREEN component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of GREEN component*/
	GLuint GetGreenSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*(1) Returns a one-dimensional texture image into client's memory. (2.1) Pixel pack buffer must be unbound from its target
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void GetImage(GLint level, Textures::GetFormat format, Textures::GetType type, _Out_ void* pixels)
	{
		Textures::get_tex_image(T, B, level, (GLenum)format, (GLenum)type, pixels);
	}

	/*Returns the internal format of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The internal format of the texture image*/
	Textures::Internalformat GetInternalFormat(GLint level)
	{
		return (Textures::Internalformat)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*Returns internal storage resolution of RED component of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of RED component*/
	GLuint GetRedSize(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_RED_SIZE);
	}

	/*Returns the width of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The width of the texture image*/
	GLsizei GetWidth(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_WIDTH);
	}

	/*Returns boolean value indicating if the texture image is stored in a compressed internal format
	@param Specifies the level-of-detail number of the desired image
	@return True if the texture image is stored in a compressed internal format, false otherwise*/
	GLboolean IsCompressed(GLint level)
	{
		return Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_COMPRESSED);
	}

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) (2) Return a compressed one-dimensional texture image into pixel pack buffer data store of the size returned by <GetCompressedImageSize>
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies the byte offset into PBO data store*/
	void GetCompressedImage(PixelPackBuffer& buffer, GLint level, GLintptr offset)
	{
		Textures::get_compressed_tex_image(T, B, level, buffer.Get(), offset);
	}

	/*(2.1) (2) Returns a one-dimensional texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void GetImage(PixelPackBuffer& buffer, GLint level, Textures::GetFormat format, Textures::GetType type, GLintptr offset)
	{
		Textures::get_tex_image(T, B, level, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Returns the type of ALPHA component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of ALPHA component of the texture image*/
	Textures::ComponentType GetAlphaType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of BLUE component of the texture image*/
	Textures::ComponentType GetBlueType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the type of DEPTH component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of DEPTH component of the texture image*/
	Textures::ComponentType GetDepthType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of GREEN component of the texture image*/
	Textures::ComponentType GetGreenType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of RED component of the texture image
	@param Specifies the level-of-detail number of the desired image
	@return The type of RED component of the texture image*/
	Textures::ComponentType GetRedType(GLint level)
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, level, GL_TEXTURE_RED_TYPE);
	}
#endif // #ifdef YAGLPP_VERSION_3_0
};

typedef Textures_1<GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D> Texture1D_1;
typedef Textures_2<GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D> Texture1D_2;
typedef Textures_3<GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_PROXY_TEXTURE_1D> Texture1D_3;
typedef Textures_4<GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, GL_PROXY_TEXTURE_1D> Texture1D_4;
/*OpenGL one-dimensional texture object class derived from <Textures>*/
class Texture1D : public Texture1D_4
{
public:
	using Texture1D_4::Texture1D_4;
	/*(1) Specifies a one-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide, and 1 texel high
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, internalformat, width, imageSize, data);
	}

	/*Recalculates the capacity of one-dimensional texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize)
	{
		compressed_proxy_image_1d(GL_PROXY_TEXTURE_1D, level, internalformat, width, imageSize);
	}

	/*(1) Replaces a contiguous subregion of an existing one-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, internalformat, imageSize, data);
	}

	/*Copies pixels into a one-dimensional texture image from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies the internal format of the texture
	@param Specifies the window x coordinate of the left corner of the row of pixels to be copied
	@param Specifies the window y coordinate of the left corner of the row of pixels to be copied
	@param Specifies the width of the texture image, the height of the image is 1*/
	void CopyImage(GLint level, CopyFormat internalformat, GLint x, GLint y, GLsizei width)
	{
		copy_tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLenum)internalformat, x, y, width);
	}

	/*Replaces a portion of a one-dimensional texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies the texel offset within the texture array
	@param Specifies the window x coordinate of the left corner of the row of pixels to be copied
	@param Specifies the window y coordinate of the left corner of the row of pixels to be copied
	@paran Specifies the width of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		copy_tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, x, y, width);
	}

	/*Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture1D GetBinding()
	{
		return Texture1D(yaglpp_glad_integer(GL_TEXTURE_BINDING_1D));
	}

	/*(1) Specifies a one-dimensional texture image initialized from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLint level)
	{
		tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, stb_get_format(image), image);
	}

	/*(2) Specifies a one-dimensional texture image initialized from the StbImage object with specified texture internal format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLint level, Internalformat internalformat)
	{
		tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, image);
	}

	/*(3) Specifies a one-dimensional texture image initialized from client's memory. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide, and 1 texel high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, Format format, Type type, _In_ const void* data)
	{
		tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type, data);
	}

	/*Recalculates the capacity for the one-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, Format format, Type type)
	{
		proxy_image_1d(GL_PROXY_TEXTURE_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type);
	}

	/*(1) Replaces a contiguous subregion of an existing one-dimensional texture image copied from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the StbImage object with loaded image*/
	void SubImage(StbImage& image, GLint level, GLint xoffset)
	{
		tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, image);
	}

	/*(2) Replaces a contiguous subregion of an existing one-dimensional texture image copied from client's memory data store. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLsizei width, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)format, (GLenum)type, pixels);
	}

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) (2) Specifies a one-dimensional texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide, and 1 texel high
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, internalformat, width, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (2) Replaces a contiguous subregion of an existing one-dimensional texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLsizei width, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (4) Specifies a one-dimensional texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide, and 1 texel high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, Format format, Type type, GLintptr offset)
	{
		tex_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, (GLint)internalformat, width, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(2.1) (3) Specifies a one-dimensional texture subimage copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLsizei width, Format format, Type type, GLintptr offset)
	{
		tex_sub_image_1d(GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, level, xoffset, width, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
#endif // #ifdef YAGLPP_VERSION_2_1
}; // class Texture1D : public Texture1D_4

typedef Textures_1<GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D> Texture2D_1;
typedef Textures_2<GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D> Texture2D_2;
typedef Textures_3<GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, GL_PROXY_TEXTURE_2D> Texture2D_3;
typedef Textures_4<GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, GL_PROXY_TEXTURE_2D> Texture2D_4;
/*OpenGL two-dimensional texture object class derived from <Textures>*/
class Texture2D : public Texture2D_4
{
public:
	using Texture2D_4::Texture2D_4;
	/*(1) Specifies a two-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 16384 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16384 texels high
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, (GLenum)internalformat, width, height, imageSize, data);
	}

	/*Recalculates the capacity of two-dimensional texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize)
	{
		compressed_proxy_image_2d(GL_PROXY_TEXTURE_2D, level, internalformat, width, height, imageSize);
	}

	/*(1) Replaces a contiguous subregion of an existing two-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	}

	/*Copies pixels into a two-dimensional texture image from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies the internal format of the texture
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image*/
	void CopyImage(GLint level, CopyFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, (GLenum)internalformat, x, y, width, height);
	}

	/*Replaces a rectangular portion of a two-dimensional texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, x, y, width, height);
	}

	/*Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2D GetBinding()
	{
		return Texture2D(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D));
	}

	/*Returns the height of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The height of the texture image*/
	GLsizei GetHeight(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, GL_TEXTURE_HEIGHT);
	}

	/*Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D, level, GL_TEXTURE_HEIGHT);
	}

	/*(1) Specifies a two-dimensional texture image initialized from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLint level)
	{
		tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, stb_get_format(image), image);
	}

	/*(2) Specifies a two-dimensional texture image initialized from the StbImage object with specified texture internal format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLint level, Internalformat internalformat)
	{
		tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, (GLint)internalformat, image);
	}

	/*(3) Specifies a two-dimensional texture image initialized from client's memory. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, _In_ const void* data)
	{
		tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, data);
	}

	/*Recalculates the capacity for a two-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type)
	{
		proxy_image_2d(GL_PROXY_TEXTURE_2D, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type);
	}

	/*(1) Specifies a two-dimensional texture subimage copied from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array*/
	void SubImage(StbImage& image, GLint level, GLint xoffset, GLint yoffset)
	{
		tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, image);
	}

	/*(2) Specifies a two-dimensional texture subimage copied from client's memory data store. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, width, height, (GLenum)format, (GLenum)type, pixels);
	}

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) (2) Specifies a two-dimensional texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 16384 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16384 texels high
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, internalformat, width, height, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (2) Replaces a contiguous subregion of an existing two-dimensional texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, width, height, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (4) Specifies a one-dimensional texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, GLintptr offset)
	{
		tex_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(2.1) (3) Specifies a two-dimensional texture image copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_2d(GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, level, xoffset, yoffset, width, height, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
#endif // #ifdef YAGLPP_VERSION_2_1
}; // class Texture2D : public Texture2D_4

typedef Textures_1<GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D> Texture3D_1;
typedef Textures_2<GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D> Texture3D_2;
typedef Textures_3<GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, GL_PROXY_TEXTURE_3D> Texture3D_3;
typedef Textures_4<GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, GL_PROXY_TEXTURE_3D> Texture3D_4;
/*OpenGL three-dimensional texture object class derived from <Textures>*/
class Texture3D : public Texture3D_4
{
public:
	using Texture3D_4::Texture3D_4;
	/*(1) Specifies a three-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the depth of the texture image. Supports images that are at least 16 texels deep
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, internalformat, width, height, depth, imageSize, data);
	}

	/*Recalculates the capacity of three-dimensional texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the depth of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize)
	{
		compressed_proxy_image_3d(GL_PROXY_TEXTURE_3D, level, internalformat, width, height, depth, imageSize);
	}

	/*(1) Replaces a contiguous subregion of an existing three-dimensional texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the depth of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, data);
	}

	/*Replaces a rectangular portion of a three-dimensional texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	/*Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture3D GetBinding()
	{
		return Texture3D(yaglpp_glad_integer(GL_TEXTURE_BINDING_3D));
	}

	/*Returns the number of layers in the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The depth of the texture image*/
	GLsizei GetDepth(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, GL_TEXTURE_DEPTH);
	}

	/*Returns the height of the texture image
	@param Specifies the level-of-detail number of the desired image. The initial value is 0
	@return The height of the texture image*/
	GLsizei GetHeight(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, GL_TEXTURE_HEIGHT);
	}

	/*Returns the number of layers in the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The depth of the proxy texture image*/
	static GLsizei GetProxyDepth(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_3D, level, GL_TEXTURE_DEPTH);
	}

	/*Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_3D, level, GL_TEXTURE_HEIGHT);
	}

	/*(1) Specifies a three-dimensional texture image initialized from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the number of interleaved layers within loaded 2D image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLsizei layers, GLint level)
	{
		tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, stb_get_format(image), layers, image);
	}

	/*(2) Specifies a three-dimensional texture image initialized from the StbImage object with specified texture internal format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the number of interleaved layers within loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLsizei layers, GLint level, Internalformat internalformat)
	{
		tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, (GLint)internalformat, layers, image);
	}

	/*(3) Specifies a three-dimensional texture image initialized from client's memory. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the depth of the texture image. Supports images that are at least 256 texels deep
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei depth, Format format, Type type, _In_ const void* data)
	{
		tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, (GLint)internalformat, width, height, depth, (GLenum)format, (GLenum)type, data);
	}

	/*Recalculates the capacity for a three-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the depth of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei depth, Format format, Type type)
	{
		proxy_image_3d(GL_PROXY_TEXTURE_3D, level, (GLint)internalformat, width, height, depth, (GLenum)format, (GLenum)type);
	}

	/*(1) Specifies a three-dimensional texture subimage copied from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the number of interleaved layers within loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array*/
	void SubImage(StbImage& image, GLsizei layers, GLint level, GLint xoffset, GLint yoffset, GLint zoffset)
	{
		tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, layers, image);
	}

	/*(2) Specifies a three-dimensional texture subimage copied from client's memory data store. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the depth of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, width, height, depth, (GLenum)format, (GLenum)type, pixels);
	}

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) (2) Specifies a three-dimensional texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the depth of the texture image. Supports images that are at least 16 texels deep
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, internalformat, width, height, depth, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (2) Replaces a contiguous subregion of an existing three-dimensional texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the depth of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (4) Specifies a three-dimensional texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the depth of the texture image. Supports images that are at least 256 texels deep
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei depth, Format format, Type type, GLintptr offset)
	{
		tex_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, (GLint)internalformat, width, height, depth, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(2.1) (3) Specifies a three-dimensional texture image copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the depth of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_3d(GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, level, xoffset, yoffset, zoffset, width, height, depth, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
#endif // #ifdef YAGLPP_VERSION_2_1
}; // class Texture3D : public Texture3D_4

typedef Textures_1<GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP> TextureCubeMap_1;
typedef Textures_2<GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP> TextureCubeMap_2;
typedef Textures_3<GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP, GL_PROXY_TEXTURE_CUBE_MAP> TextureCubeMap_3;
/*OpenGL two-dimensional six-face cube map texture object class derived from <Textures>*/
class TextureCubeMap : public TextureCubeMap_3
{
public:
	using TextureCubeMap_3::TextureCubeMap_3;
	enum class Plane : GLenum;
	/*(1) Specifies a two-dimensional cube map plane's texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 16384 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16384 texels high
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(Plane plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, internalformat, width, height, imageSize, data);
	}

	/*Recalculates the capacity of a cube map texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize)
	{
		compressed_proxy_image_2d(GL_PROXY_TEXTURE_CUBE_MAP, level, internalformat, width, height, imageSize);
	}

	/*(1) Replaces a contiguous subregion of an existing two-dimensional cube map plane's texture image in a compressed format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(Plane plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, width, height, internalformat, imageSize, data);
	}

	/*Copies pixels into a two-dimensional cube map plane's texture image from the current read buffer
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the internal format of the texture
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image*/
	void CopyImage(Plane plane, GLint level, CopyFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLenum)internalformat, x, y, width, height);
	}

	/*Replaces a rectangular portion of a two-dimensional cube map plane's texture image with pixels from the current read buffer
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(Plane plane, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, x, y, width, height);
	}

	/*Returns internal storage resolution of ALPHA component of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	GLuint GetAlphaSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_ALPHA_SIZE);
	}

	/*Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static TextureCubeMap GetBinding()
	{
		return TextureCubeMap(yaglpp_glad_integer(GL_TEXTURE_BINDING_CUBE_MAP));
	}

	/*Returns internal storage resolution of BLUE component of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of BLUE component*/
	GLuint GetBlueSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_BLUE_SIZE);
	}

	/*(1) Return a compressed two-dimensional cube map plane's texture image into client's memory of the size returned by <GetCompressedImageSize>. (2.1) Pixel pack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@param [out] Specifies a pointer to store the compressed texture image*/
	void GetCompressedImage(Plane plane, GLint level, _Out_ void* pixels)
	{
		get_compressed_tex_image((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, pixels);
	}

	/*Returns the number of unsigned bytes of the compressed texture image that would be returned from <GetCompressedImage>
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The number of unsigned bytes of the compressed texture image*/
	GLsizei GetCompressedImageSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
	}

	/*Returns internal storage resolution of DEPTH component of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of DEPTH component*/
	GLuint GetDepthSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_DEPTH_SIZE);
	}

	/*Returns internal storage resolution of GREEN component of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of GREEN component*/
	GLuint GetGreenSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_GREEN_SIZE);
	}

	/*Returns the height of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The height of the texture image*/
	GLsizei GetHeight(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_HEIGHT);
	}

	/*(1) Returns a two-dimensional cube map plane's texture image into client's memory. (2.1) Pixel pack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void GetImage(Plane plane, GLint level, GetFormat format, GetType type, _Out_ void* pixels)
	{
		get_tex_image((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLenum)format, (GLenum)type, pixels);
	}

	/*Returns the internal format of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The internal format of the texture image*/
	Internalformat GetInternalFormat(Plane plane, GLint level)
	{
		return (Internalformat)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_CUBE_MAP, level, GL_TEXTURE_HEIGHT);
	}

	/*Returns internal storage resolution of RED component of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The internal storage resolution of RED component*/
	GLuint GetRedSize(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_RED_SIZE);
	}

	/*Returns the width of the texture image. The initial value is 0
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The width of the texture image*/
	GLsizei GetWidth(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_WIDTH);
	}

	/*(1) Specifies a two-dimensional cube map plane's texture image initialized from the StbImage object. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, Plane plane, GLint level)
	{
		tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, stb_get_format(image), image);
	}

	/*(2) Specifies a two-dimensional cube map plane's texture image initialized from the StbImage object with specified texture internal format. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, Plane plane, GLint level, Internalformat internalformat)
	{
		tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLint)internalformat, image);
	}

	/*(3) Specifies a two-dimensional cube map plane's texture image initialized from client's memory. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(Plane plane, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, _In_ const void* data)
	{
		tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, data);
	}

	/*Returns boolean value indicating if the texture image is stored in a compressed internal format
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return True if the texture image is stored in a compressed internal format, false otherwise*/
	GLboolean IsCompressed(Plane plane, GLint level)
	{
		return get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_COMPRESSED);
	}

	/*Recalculates the capacity for a two-dimensional cube map texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type)
	{
		proxy_image_2d(GL_PROXY_TEXTURE_CUBE_MAP, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type);
	}

	/*(1) Specifies a two-dimensional cube map plane's texture subimage copied from the StbImage object. (2.1) Unbinds pixel unpack buffer from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array*/
	void SubImage(StbImage& image, Plane plane, GLint level, GLint xoffset, GLint yoffset)
	{
		tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, image);
	}

	/*(2) Specifies a two-dimensional cube map plane's texture subimage copied from client's memory data store. (2.1) Pixel unpack buffer must be unbound from its target
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(Plane plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, width, height, (GLenum)format, (GLenum)type, pixels);
	}

#ifdef YAGLPP_VERSION_2_1
	/*(2.1) (2) Specifies a two-dimensional cube map plane's texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 16384 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16384 texels high
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, Plane plane, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, internalformat, width, height, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (2) Replaces a contiguous subregion of an existing two-dimensional cube map plane's texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, Plane plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, width, height, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(2.1) (2) Return a compressed two-dimensional cube map plane's texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@param Specifies the byte offset into PBO data store*/
	void GetCompressedImage(PixelPackBuffer& buffer, Plane plane, GLint level, GLintptr offset)
	{
		get_compressed_tex_image((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, buffer.Get(), offset);
	}

	/*(2.1) (2) Returns a two-dimensional cube map plane's texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer to store the data
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void GetImage(PixelPackBuffer& buffer, Plane plane, GLint level, GetFormat format, GetType type, GLintptr offset)
	{
		get_tex_image((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(2.1) (4) Specifies a two-dimensional cube map plane's texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, Plane plane, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, GLintptr offset)
	{
		tex_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(2.1) (3) Specifies a two-dimensional texture subimage copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load the data from
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, Plane plane, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_2d((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, xoffset, yoffset, width, height, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Returns the type of ALPHA component of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The type of ALPHA component of the texture image*/
	ComponentType GetAlphaType(Plane plane, GLint level)
	{
		return (ComponentType)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.0) Returns the type of BLUE component of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The type of BLUE component of the texture image*/
	ComponentType GetBlueType(Plane plane, GLint level)
	{
		return (ComponentType)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.0) Returns the type of DEPTH component of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The type of DEPTH component of the texture image*/
	ComponentType GetDepthType(Plane plane, GLint level)
	{
		return (ComponentType)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.0) Returns the type of GREEN component of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The type of GREEN component of the texture image*/
	ComponentType GetGreenType(Plane plane, GLint level)
	{
		return (ComponentType)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.0) Returns the type of RED component of the texture image
	@param Specifies the cube map plane to process
	@param Specifies the level-of-detail number of the desired image
	@return The type of RED component of the texture image*/
	ComponentType GetRedType(Plane plane, GLint level)
	{
		return (ComponentType)get_tex_level_parameter((GLenum)plane, GL_TEXTURE_BINDING_CUBE_MAP, level, GL_TEXTURE_RED_TYPE);
	}

#endif // #ifdef YAGLPP_VERSION_3_0
}; // class TextureCubeMap : public TextureCubeMap_3

/*GLAD cube map texture plane enumerator*/
enum class TextureCubeMap::Plane : GLenum
{
	/*Positive-X face image appearing at the right side of a cube map*/
	PositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,

	/*Negative-X face image appearing at the left side of a cube map*/
	NegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,

	/*Positive-Y face image appearing at the top side of a cube map*/
	PositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,

	/*Negative-Y face image appearing at the bottom side of a cube map*/
	NegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,

	/*Positive-Z face image appearing at the front side of a cube map*/
	PositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,

	/*Negative-Z face image appearing at the back side of a cube map*/
	NegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

#ifdef YAGLPP_VERSION_3_0
typedef Textures_1<GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY> Texture1DArray_1;
typedef Textures_2<GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY> Texture1DArray_2;
typedef Textures_3<GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY> Texture1DArray_3;
typedef Textures_4<GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY> Texture1DArray_4;
/*(3.0) OpenGL one-dimensional multi-layered texture object class derived from <Textures>*/
class Texture1DArray : public Texture1DArray_4
{
public:
	using Texture1DArray_4::Texture1DArray_4;
	/*(3.0) (1) Specifies a one-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei layers, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, internalformat, width, layers, imageSize, data);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 64 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei layers, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, internalformat, width, layers, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Recalculates the capacity of one-dimensional multi-layered texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei layers, GLsizei imageSize)
	{
		compressed_proxy_image_2d(GL_PROXY_TEXTURE_1D_ARRAY, level, internalformat, width, layers, imageSize);
	}

	/*(3.0) (1) Replaces a contiguous subregion of an existing one-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, width, layers, internalformat, imageSize, data);
	}

	/*(3.0) (2) Replaces a contiguous subregion of an existing one-dimensional multi-layered texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used as a source of subimage
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, width, layers, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Replaces a linear portion of a number of slices of a one-dimensional multi-layered texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, x, y, width, height);
	}

	/*(3.0) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture1DArray GetBinding()
	{
		return Texture1DArray(yaglpp_glad_integer(GL_TEXTURE_BINDING_1D_ARRAY));
	}

	/*(3.0) Returns the number of layers in the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The depth of the texture image*/
	GLsizei GetDepth(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns the number of layers of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The depth of the proxy texture image*/
	static GLsizei GetProxyDepth(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_1D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) (1) Specifies a one-dimensional multi-layered texture image initialized from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLint level)
	{
		tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, stb_get_format(image), image);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture image initialized from the StbImage object with specified texture internal format. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLint level, Internalformat internalformat)
	{
		tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, (GLint)internalformat, image);
	}

	/*(3.0) (3) Specifies a one-dimensional multi-layered texture image initialized from client's memory. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, GLsizei layers, Format format, Type type, _In_ const void* data)
	{
		tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type, data);
	}

	/*(3.0) (4) Specifies a one-dimensional multi-layered texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the number of layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, GLsizei layers, Format format, Type type, GLintptr offset)
	{
		tex_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.0) Recalculates the capacity for a one-dimensional multi-layered texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei layers, Format format, Type type)
	{
		proxy_image_2d(GL_PROXY_TEXTURE_1D_ARRAY, level, (GLint)internalformat, width, layers, (GLenum)format, (GLenum)type);
	}

	/*(3.0) (1) Specifies a one-dimensional multi-layered texture subimage copied from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array*/
	void SubImage(StbImage& image, GLint level, GLint xoffset, GLint yoffset)
	{
		tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, image);
	}

	/*(3.0) (2) Specifies a one-dimensional multi-layered texture subimage copied from client's memory data store. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (3) Specifies a two-dimensional texture subimage copied from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei layers, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_2d(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY, level, xoffset, yoffset, width, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
}; // class Texture1DArray : public Texture1DArray_4

typedef Textures_1<GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY> Texture2DArray_1;
typedef Textures_2<GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY> Texture2DArray_2;
typedef Textures_3<GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_PROXY_TEXTURE_2D_ARRAY> Texture2DArray_3;
typedef Textures_4<GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, GL_PROXY_TEXTURE_2D_ARRAY> Texture2DArray_4;
/*(3.0) OpenGL multiple two-dimensional multi-layered texture object class derived from <Textures>*/
class Texture2DArray : public Texture2DArray_4
{
public:
	using Texture2DArray_4::Texture2DArray_4;
	/*(3.0) (1) Specifies a two-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at specified data address
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the layers of the texture image. Supports images with at least 16 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, internalformat, width, height, layers, imageSize, data);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture image in a compressed format initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data stored at the specified data offset into PBO data store
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 16 texels high
	@param Specifies the layers of the texture image. Supports images with at least 16 layers
	@param Specifies the number of unsigned bytes of image data starting at the specified data offset into PBO data store
	@param Specifies the byte offset into PBO data store*/
	void CompressedImage(PixelUnpackBuffer& buffer, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, internalformat, width, height, layers, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Recalculates the capacity of two-dimensional multi-layered texture image in a compressed format via proxy target
	@param Specifies the level-of-detail number
	@param Specifies the format of the compressed image data
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the layers of the texture image
	@param Specifies the number of unsigned bytes of image data*/
	static void CompressedProxyImage(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei layers, GLsizei imageSize)
	{
		compressed_proxy_image_3d(GL_PROXY_TEXTURE_2D_ARRAY, level, internalformat, width, height, layers, imageSize);
	}

	/*(3.0) (1) Replaces a contiguous subregion of an existing two-dimensional multi-layered texture image in a compressed format. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the layers of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, GLenum internalformat, GLsizei imageSize, _In_ const void* data)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, internalformat, imageSize, data);
	}

	/*(3.0) (2) Replaces a contiguous subregion of an existing two-dimensional multi-layered texture image in a compressed format from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used as a source of subimage
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the depth of the texture subimage
	@param Specifies the format of the compressed image data stored at the specified data address
	@param Specifies the number of unsigned bytes of image data starting at the specified data address
	@param [in] Specifies a pointer to the compressed image data in memory*/
	void CompressedSubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum internalformat, GLsizei imageSize, GLintptr offset)
	{
		compressed_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, depth, internalformat, imageSize, buffer.Get(), offset);
	}

	/*(3.0) Replaces a rectangular portion of a two-dimensional multi-layered texture image with pixels from the current read buffer
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	/*(3.0) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2DArray GetBinding()
	{
		return Texture2DArray(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D_ARRAY));
	}

	/*(3.0) Returns the height of the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The height of the texture image*/
	GLsizei GetHeight(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) Returns the number of layers in the texture image. The initial value is 0
	@param Specifies the level-of-detail number of the desired image
	@return The depth of the texture image*/
	GLsizei GetDepth(GLint level)
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) Returns the height of the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_HEIGHT);
	}

	/*(3.0) Returns the number of layers in the proxy texture
	@param Specifies the level-of-detail number of the proxy texture
	@return The depth of the proxy texture image*/
	static GLsizei GetProxyDepth(GLint level)
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_ARRAY, level, GL_TEXTURE_DEPTH);
	}

	/*(3.0) (1) Specifies a two-dimensional multi-layered texture image initialized from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded 2D image
	@param Specifies the number of interleaved layers in loaded 2D image
	@param Specifies the level-of-detail number*/
	void Image(StbImage& image, GLsizei layers, GLint level)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, stb_get_format(image), layers, image);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture image initialized from the StbImage object with specified texture internal format. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded 2D image
	@param Specifies the number of interleaved layers in loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, GLsizei layers, GLint level, Internalformat internalformat)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, layers, image);
	}

	/*(3.0) (3) Specifies a two-dimensional multi-layered texture image initialized from client's memory. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type, _In_ const void* data)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type, data);
	}

	/*(3.0) (4) Specifies a two-dimensional multi-layered texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 16 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 256 texels high
	@param Specifies the layers of the texture image. Supports images with at least 256 layers
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type, GLintptr offset)
	{
		tex_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.0) Recalculates the capacity for a two-dimensional texture image using proxy target
	@param Specifies the level-of-detail number
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(GLint level, Internalformat internalformat, GLsizei width, GLsizei height, GLsizei layers, Format format, Type type)
	{
		proxy_image_3d(GL_PROXY_TEXTURE_2D_ARRAY, level, (GLint)internalformat, width, height, layers, (GLenum)format, (GLenum)type);
	}

	/*(3.0) (1) Specifies a two-dimensional multi-layered texture subimage copied from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the number of interleaved layers within loaded 2D image
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array*/
	void SubImage(StbImage& image, GLsizei layers, GLint level, GLint xoffset, GLint yoffset, GLint zoffset)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, layers, image);
	}

	/*(3.0) (2) Specifies a two-dimensional multi-layered texture subimage copied from client's memory data store. Pixel unpack buffer must be unbound from its target
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage
	@param Specifies the number of layers of the texture subimage
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void SubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, SubFormat format, SubType type, _In_ const void* pixels)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.0) (3) Specifies a two-dimensional multi-layered texture subimage copied from from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer to load data from
	@param Specifies the level-of-detail number
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies a texel offset in the z direction within the texture array
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the number of layers of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void SubImage(PixelUnpackBuffer& buffer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei layers, SubFormat format, SubType type, GLintptr offset)
	{
		tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY, level, xoffset, yoffset, zoffset, width, height, layers, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
}; // class Texture2DArray : public Texture2DArray_4
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
template <GLenum T, GLenum B, GLenum P> class Textures_5 : public Textures_2<T, B>
{
public:
	using Textures_2<T, B>::Textures_2;

	/*(3.1) Returns internal storage resolution of ALPHA component of the texture image. The initial value is 0
	@return The internal storage resolution of ALPHA component*/
	GLuint GetAlphaSize()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	Textures::ComponentType GetAlphaType()
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the texture image. The initial value is 0
	@return The internal storage resolution of BLUE component*/
	GLuint GetBlueSize()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	Textures::ComponentType GetBlueType()
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the texture image. The initial value is 0
	@return The internal storage resolution of DEPTH component*/
	GLuint GetDepthSize()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	Textures::ComponentType GetDepthType()
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the texture image. The initial value is 0
	@return The internal storage resolution of GREEN component*/
	GLuint GetGreenSize()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	Textures::ComponentType GetGreenType()
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the height of the texture image. The initial value is 0
	@return The height of the texture image*/
	GLsizei GetHeight()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.1) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	Textures::Internalformat GetInternalFormat()
	{
		return (Textures::Internalformat)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	static GLuint GetProxyAlphaSize()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static Textures::ComponentType GetProxyAlphaType()
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the proxy texture
	@return The internal storage resolution of BLUE component*/
	static GLuint GetProxyBlueSize()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static Textures::ComponentType GetProxyBlueType()
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLuint GetProxyDepthSize()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static Textures::ComponentType GetProxyDepthType()
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLuint GetProxyGreenSize()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static Textures::ComponentType GetProxyGreenType()
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the height of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.1) Returns the internal format capacity of the proxy texture
	@return The internal format capacity of the texture*/
	static Textures::Internalformat GetProxyInternalFormat()
	{
		return (Textures::Internalformat)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns internal storage resolution of RED component of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLuint GetProxyRedSize()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the proxy texture
	@return The type of RED component of the proxy texture*/
	static Textures::ComponentType GetProxyRedType()
	{
		return (Textures::ComponentType)Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei GetProxyWidth()
	{
		return Textures::get_proxy_level_parameter(P, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.1) Returns internal storage resolution of RED component of the texture image. The initial value is 0
	@return The internal storage resolution of RED component*/
	GLuint GetRedSize()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	Textures::ComponentType GetRedType()
	{
		return (Textures::ComponentType)Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the texture image. The initial value is 0
	@return The width of the texture image*/
	GLsizei GetWidth()
	{
		return Textures::get_tex_level_parameter(T, B, 0, GL_TEXTURE_WIDTH);
	}
}; // template <GLenum T, GLenum B> class Textures_5 : public Textures_1<T, B>

typedef Textures_1<GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER> BufferTexture_1;
/*(3.1) OpenGL one-dimensional buffer texture object class derived from <Textures>*/
class BufferTexture : public BufferTexture_1
{
public:
	using BufferTexture_1::BufferTexture_1;
	enum class BufferFormat : GLenum;
	/*(3.1) Attach a texture buffer (buffer) object's data store to an active buffer texture (texture) object
	@param Specifies texture buffer object whose storage to attach to the active buffer texture
	@param Specifies the internal format of the data in the store belonging to buffer*/
	void AttachBuffer(TextureBuffer& buffer, BufferFormat internalformat)
	{
		tex_buffer((GLenum)internalformat, buffer.Get());
	}

	/*(3.1) Detatch a texture buffer (buffer) object's data store currently attached to buffer texture (texture) object*/
	void DetachBuffer()
	{
		tex_buffer(0, 0);
	}

	/*(3.1) Returns internal storage resolution of ALPHA component of the texture image
	@return The internal storage resolution of ALPHA component. The initial value is 0*/
	GLuint GetAlphaSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.1) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	ComponentType GetAlphaType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.1) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static BufferTexture GetBinding()
	{
		return BufferTexture(yaglpp_glad_integer(GL_TEXTURE_BINDING_BUFFER));
	}

	/*(3.1) Returns internal storage resolution of BLUE component of the texture image
	@return The internal storage resolution of BLUE component. The initial value is 0*/
	GLuint GetBlueSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.1) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	ComponentType GetBlueType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.1) Returns internal storage resolution of DEPTH component of the texture image
	@return The internal storage resolution of DEPTH component. The initial value is 0*/
	GLuint GetDepthSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.1) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	ComponentType GetDepthType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.1) Returns internal storage resolution of GREEN component of the texture image
	@return The internal storage resolution of GREEN component. The initial value is 0*/
	GLuint GetGreenSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.1) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	ComponentType GetGreenType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.1) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	Internalformat GetInternalFormat()
	{
		return (Internalformat)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.1) Returns internal storage resolution of RED component of the texture image
	@return The internal storage resolution of RED component. The initial value is 0*/
	GLuint GetRedSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.1) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	ComponentType GetRedType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.1) Returns the width of the texture image. The initial value is 0
	@return The width of the texture image*/
	GLsizei GetWidth()
	{
		return get_tex_level_parameter(GL_TEXTURE_BUFFER, GL_TEXTURE_BINDING_BUFFER, 0, GL_TEXTURE_WIDTH);
	}
}; // class BufferTexture : public BufferTexture_2

/*(3.1) GLAD buffer texture internal format enumerator used in <AttachBuffer>*/
enum class BufferTexture::BufferFormat : GLenum
{
	/*(3.1) Red color component format with 8-bit resolution*/
	R8 = GL_R8,

	/*(3.1) Red color component format with 16-bit resolution*/
	R16 = GL_R16,

	/*(3.1) Red float color component format with 16-bit resolution*/
	R16f = GL_R16F,

	/*(3.1) Red float color component format with 32-bit resolution*/
	R32f = GL_R32F,

	/*(3.1) Red signed integer color component format with 8-bit resolution*/
	R8i = GL_R8I,

	/*(3.1) Red signed integer color component format with 16-bit resolution*/
	R16i = GL_R16I,

	/*(3.1) Red signed integer color component format with 32-bit resolution*/
	R32i = GL_R32I,

	/*(3.1) Red unsigned integer color component format with 8-bit resolution*/
	R8ui = GL_R8UI,

	/*(3.1) Red unsigned integer color component format with 16-bit resolution*/
	R16ui = GL_R16UI,

	/*(3.1) Red unsigned integer color component format with 32-bit resolution*/
	R32ui = GL_R32UI,

	/*(3.1) RG color component format with (8:8)-bit resolution*/
	Rg8 = GL_RG8,

	/*(3.1) RG color component format with (16:16)-bit resolution*/
	Rg16 = GL_RG16,

	/*(3.1) RG float color component format with (16:16)-bit resolution*/
	Rg16f = GL_RG16F,

	/*(3.1) RG float color component format with (32:32)-bit resolution*/
	Rg32f = GL_RG32F,

	/*(3.1) RG signed integer color component format with (8:8)-bit resolution*/
	Rg8i = GL_RG8I,

	/*(3.1) RG signed integer color component format with (16:16)-bit resolution*/
	Rg16i = GL_RG16I,

	/*(3.1) RG signed integer color component format with (32:32)-bit resolution*/
	Rg32i = GL_RG32I,

	/*(3.1) RG unsigned integer color component format with (8:8)-bit resolution*/
	Rg8ui = GL_RG8UI,

	/*(3.1) RG unsigned integer color component format with (16:16)-bit resolution*/
	Rg16ui = GL_RG16UI,

	/*(3.1) RG unsigned integer color component format with (32:32)-bit resolution*/
	Rg32ui = GL_RG32UI,

	/*(3.1) RGB float color component format with (32:32:32)-bit resolution*/
	Rgb32f = GL_RGB32F,

	/*(3.1) RGB signed integer color component format with (32:32:32)-bit resolution*/
	Rgb32i = GL_RGB32I,

	/*(3.1) RGB unsigned integer color component format with (32:32:32)-bit resolution*/
	Rgb32ui = GL_RGB32UI,

	/*(3.1) RGBA color component format with (8:8:8:8)-bit resolution*/
	Rgba8 = GL_RGBA8,

	/*(3.1) RGBA color component format with (16:16:16:16)-bit resolution*/
	Rgba16 = GL_RGBA16,

	/*(3.1) RGBA float color component format with (16:16:16:16)-bit resolution*/
	Rgba16f = GL_RGBA16F,

	/*(3.1) RGBA float color component format with (32:32:32:32)-bit resolution*/
	Rgba32f = GL_RGBA32F,

	/*(3.1) RGBA signed integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8i = GL_RGBA8I,

	/*(3.1) RGBA signed integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16i = GL_RGBA16I,

	/*(3.1) RGBA signed integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32i = GL_RGBA32I,

	/*(3.1) RGBA unsigned integer color component format with (8:8:8:8)-bit resolution*/
	Rgba8ui = GL_RGBA8UI,

	/*(3.1) RGBA unsigned integer color component format with (16:16:16:16)-bit resolution*/
	Rgba16ui = GL_RGBA16UI,

	/*(3.1) RGBA unsigned integer color component format with (32:32:32:32)-bit resolution*/
	Rgba32ui = GL_RGBA32UI,
};

typedef Textures_1<GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE> TextureRectangle_1;
typedef Textures_5<GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE> TextureRectangle_2;
/*(3.1) OpenGL two-dimensional rectangle texture object class derived from <Textures>*/
class TextureRectangle : public TextureRectangle_2
{
public:
	using TextureRectangle_2::TextureRectangle_2;
	/*(3.1) Replaces a rectangular portion of a rectangle texture image with pixels from the current read buffer
	@param Specifies a texel offset in the x direction within the texture array
	@param Specifies a texel offset in the y direction within the texture array
	@param Specifies the window x coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the window y coordinate of the lower left corner of the rectangular region of pixels to be copied
	@param Specifies the width of the texture subimage
	@param Specifies the height of the texture subimage*/
	void CopySubImage(GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		copy_tex_sub_image_2d(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, xoffset, yoffset, x, y, width, height);
	}

	/*(3.1) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static TextureRectangle GetBinding()
	{
		return TextureRectangle(yaglpp_glad_integer(GL_TEXTURE_BINDING_RECTANGLE));
	}

	/*(3.1) (1) Returns a two-dimensional rectangle texture image into client's memory. Pixel pack buffer must be unbound from its target
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param [out] Specifies a pointer to store the texture image*/
	void GetImage(GetFormat format, GetType type, _Out_ void* pixels)
	{
		get_tex_image(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, (GLenum)format, (GLenum)type, pixels);
	}

	/*(3.1) (2) Returns a two-dimensional rectangle texture image into pixel pack buffer data store
	@param Specifies the pixel pack buffer used for storing the data
	@param Specifies a pixel format for the returned data
	@param Specifies a pixel type for the returned data
	@param Specifies the byte offset into PBO data store*/
	void GetImage(PixelPackBuffer& buffer, GetFormat format, GetType type, GLintptr offset)
	{
		get_tex_image(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}

	/*(3.1) Recalculates the capacity for a two-dimensional rectangle texture image using proxy target
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image
	@param Specifies the height of the texture image
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data*/
	static void ProxyImage(Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type)
	{
		proxy_image_2d(GL_PROXY_TEXTURE_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type);
	}

	/*(3.1) (1) Specifies a two-dimensional rectangle texture image initialized from the StbImage object. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image*/
	void Image(StbImage& image)
	{
		tex_image_2d(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, stb_get_format(image), image);
	}

	/*(3.1) (2) Specifies a two-dimensional rectangle texture image initialized from the StbImage object with specified texture internal format. Pixel unpack buffer must be unbound from its target
	@param Specifies the StbImage object with loaded image
	@param Specifies the texture internal formats*/
	void Image(StbImage& image, Internalformat internalformat)
	{
		tex_image_2d(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, (GLint)internalformat, image);
	}

	/*(3.1) (3) Specifies a two-dimensional rectangle texture image initialized from client's memory. Pixel unpack buffer must be unbound from its target
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param [in] Specifies a pointer to the image data in memory*/
	void Image(Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, _In_ const void* data)
	{
		tex_image_2d(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, data);
	}

	/*(3.1) (4) Specifies a one-dimensional rectangle texture image initialized from pixel unpack buffer data store
	@param Specifies the pixel unpack buffer used for initialization
	@param Specifies the texture internal formats
	@param Specifies the width of the texture image. Supports images that are at least 1024 texels wide
	@param Specifies the height of the texture image. Supports images that are at least 1024 texels high
	@param Specifies the format of the pixel data
	@param Specifies the data type of the pixel data
	@param Specifies the byte offset into PBO data store*/
	void Image(PixelUnpackBuffer& buffer, Internalformat internalformat, GLsizei width, GLsizei height, Format format, Type type, GLintptr offset)
	{
		tex_image_2d(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE, 0, (GLint)internalformat, width, height, (GLenum)format, (GLenum)type, buffer.Get(), offset);
	}
};
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
typedef Textures_1<GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BINDING_2D_MULTISAMPLE> Texture2DMultisample_1;
typedef Textures_5<GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BINDING_2D_MULTISAMPLE, GL_PROXY_TEXTURE_2D_MULTISAMPLE> Texture2DMultisample_2;
/*(3.2) OpenGL two-dimensional multisample texture object class derived from <Textures>*/
class Texture2DMultisample : public Texture2DMultisample_2
{
public:
	using Texture2DMultisample_2::Texture2DMultisample_2;
	/*(3.2) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2DMultisample GetBinding()
	{
		return Texture2DMultisample(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D_MULTISAMPLE));
	}

	/*(3.2) Establish the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <GetMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	void Image(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		tex_image_2d_multisample(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BINDING_2D_MULTISAMPLE, samples, (GLenum)internalformat, width, height, fixedsamplelocations);
	}

	/*(3.2) Recalculate the capacity for the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <GetMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	static void ProxyImage(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		proxy_image_2d_multisample(GL_PROXY_TEXTURE_2D_MULTISAMPLE, samples, (GLenum)internalformat, width, height, fixedsamplelocations);
	}
};

typedef Textures_1<GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY> Texture2DMultisampleArray_1;
typedef Textures_5<GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY> Texture2DMultisampleArray_2;
/*(3.2) OpenGL multi-layered two-dimensional multisample texture object class derived from <Textures>*/
class Texture2DMultisampleArray : public Texture2DMultisampleArray_2
{
public:
	using Texture2DMultisampleArray_2::Texture2DMultisampleArray_2;
	/*(3.2) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2DMultisampleArray GetBinding()
	{
		return Texture2DMultisampleArray(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY));
	}

	/*(3.2) Returns the layers of the texture image. The initial value is 0
	@return The depth of the texture image*/
	GLsizei GetDepth()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Returns the layers of the proxy texture
	@return The depth of the proxy texture image*/
	static GLsizei GetProxyDepth()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Establish the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <GetMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param The number of layers of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	void Image(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height, GLsizei layers, GLboolean fixedsamplelocations)
	{
		tex_image_3d_multisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, samples, (GLenum)internalformat, width, height, layers, fixedsamplelocations);
	}

	/*(3.2) Recalculate the capacity for the data storage, format, dimensions, and number of samples of a multisample texture's image
	@param The number of samples in the multisample texture's image, must be less than <GetMaxSamples>
	@param Specifies the texture color-renderable, depth-renderable, or stencil-renderable internal format
	@param The width of the multisample texture's image, in texels
	@param The height of the multisample texture's image, in texels
	@param The number of layers of the multisample texture's image, in texels
	@param True if the image will use identical sample locations and the same number of samples for all texels in the image*/
	static void ProxyImage(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height, GLsizei layers, GLboolean fixedsamplelocations)
	{
		proxy_image_3d_multisample(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, (GLenum)internalformat, width, height, layers, fixedsamplelocations);
	}
};
#endif // #ifdef YAGLPP_VERSION_3_2
} // namespace gl
#endif // #ifndef YAGLPP_TEXTURES_T_H
