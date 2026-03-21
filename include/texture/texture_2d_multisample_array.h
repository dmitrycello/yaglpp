#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_TEXTURE_2D_MULTISAMPLE_ARRAY_H
#define YAGLPP_TEXTURE_2D_MULTISAMPLE_ARRAY_H

#ifdef YAGLPP_VERSION_3_2
namespace gl {
/*(3.2) OpenGL multi-layered two-dimensional multisample texture object class derived from <Textures>*/
class Texture2DMultisampleArray : public Textures
{
public:
	using Textures::Textures;
	/*(3.2) Binds texture object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(glBindTexture, GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	}

	/*(3.2) Generates OpenGL texture object name in an empty texture class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenTextures, glBindTexture, GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	}

	/*(3.2) Returns internal storage resolution of ALPHA component of the texture image. The initial value is 0
	@return The internal storage resolution of ALPHA component*/
	GLuint GetAlphaSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns the type of ALPHA component of the texture image
	@return The type of ALPHA component of the texture image*/
	ComponentType GetAlphaType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns the texture object currently bound to particular target
	@return The bound texture object, or empty object*/
	static Texture2DMultisampleArray GetBinding()
	{
		return Texture2DMultisampleArray(yaglpp_glad_integer(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY));
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the texture image. The initial value is 0
	@return The internal storage resolution of BLUE component*/
	GLuint GetBlueSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns the type of BLUE component of the texture image
	@return The type of BLUE component of the texture image*/
	ComponentType GetBlueType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) (1) Returns four integer values that comprise the current RGBA color of the texture border. The initial value is (0, 0, 0, 0)
	@param [out] Stores four integer texture color values*/
	void GetBorderColor(_Out_writes_(4) GLint* color)
	{
		get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Returns four float values that comprise the current RGBA color of the texture border. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [out] Stores four float texture color values*/
	void GetBorderColor(_Out_writes_(4) GLfloat* color)
	{
		get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Returns the current texture comparison function. The initial value is <Lequal>. MSVC getter for <compareFunc> property
	@return The texture comparison function value*/
	CompareFunc GetCompareFunc()
	{
		return (CompareFunc)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_FUNC);
	}

	/*(3.2) Gets the texture comparison mode for currently bound depth textures. MSVC getter for <compareMode> property
	@return Returns one of the selected texture compare mode values*/
	CompareMode GetCompareMode()
	{
		return (CompareMode)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_MODE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the texture image. The initial value is 0
	@return The internal storage resolution of DEPTH component*/
	GLuint GetDepthSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns the type of DEPTH component of the texture image
	@return The type of DEPTH component of the texture image*/
	ComponentType GetDepthType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the texture image. The initial value is 0
	@return The internal storage resolution of GREEN component*/
	GLuint GetGreenSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns the type of GREEN component of the texture image
	@return The type of GREEN component of the texture image*/
	ComponentType GetGreenType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the height of the texture image. The initial value is 0
	@return The height of the texture image*/
	GLsizei GetHeight()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the internal format of the texture image
	@return The internal format of the texture image*/
	ColorDepthStencil GetInternalFormat()
	{
		return (ColorDepthStencil)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the layers of the texture image. The initial value is 0
	@return The layers of the texture image*/
	GLsizei GetLayers()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Gets the current texture magnification function. The initial value is <Linear>. MSVC getter for <magFilter> property
	@return The texture magnification function value*/
	MagFilter GetMagFilter()
	{
		return (MagFilter)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAG_FILTER);
	}

	/*(3.1) Gets the current texture minifying function. The initial value is <NearestMipmapLinear>. MSVC getter for <minFilter> property
	@return The texture minifying function value*/
	MinFilter GetMinFilter()
	{
		return (MinFilter)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MIN_FILTER);
	}

	/*(3.2) Returns internal storage resolution of ALPHA component of the proxy texture
	@return The internal storage resolution of ALPHA component*/
	static GLuint GetProxyAlphaSize()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_SIZE);
	}

	/*(3.2) Returns the type of ALPHA component of the proxy texture
	@return The type of ALPHA component of the proxy texture*/
	static ComponentType GetProxyAlphaType()
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_ALPHA_TYPE);
	}

	/*(3.2) Returns internal storage resolution of BLUE component of the proxy texture
	@return The internal storage resolution of BLUE component*/
	static GLuint GetProxyBlueSize()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_SIZE);
	}

	/*(3.2) Returns the type of BLUE component of the proxy texture
	@return The type of BLUE component of the proxy texture*/
	static ComponentType GetProxyBlueType()
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_BLUE_TYPE);
	}

	/*(3.2) Returns internal storage resolution of DEPTH component of the proxy texture
	@return The internal storage resolution of DEPTH component*/
	static GLuint GetProxyDepthSize()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_SIZE);
	}

	/*(3.2) Returns the type of DEPTH component of the proxy texture
	@return The type of DEPTH component of the proxy texture*/
	static ComponentType GetProxyDepthType()
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH_TYPE);
	}

	/*(3.2) Returns internal storage resolution of GREEN component of the proxy texture
	@return The internal storage resolution of GREEN component*/
	static GLuint GetProxyGreenSize()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_SIZE);
	}

	/*(3.2) Returns the type of GREEN component of the proxy texture
	@return The type of GREEN component of the proxy texture*/
	static ComponentType GetProxyGreenType()
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_GREEN_TYPE);
	}

	/*(3.2) Returns the height of the proxy texture
	@return The height of the proxy texture*/
	static GLsizei GetProxyHeight()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_HEIGHT);
	}

	/*(3.2) Returns the internal format capacity of the proxy texture
	@return The internal format capacity of the texture*/
	static ColorDepthStencil GetProxyInternalFormat()
	{
		return (ColorDepthStencil)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT);
	}

	/*(3.2) Returns the layers of the proxy texture
	@return The layers of the texture image*/
	static GLsizei GetProxyLayers()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_DEPTH);
	}

	/*(3.2) Returns internal storage resolution of RED component of the proxy texture
	@return The internal storage resolution of RED component*/
	static GLuint GetProxyRedSize()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns the type of RED component of the proxy texture
	@return The type of RED component of the proxy texture*/
	static ComponentType GetProxyRedType()
	{
		return (ComponentType)get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the width of the proxy texture
	@return The width of the proxy texture*/
	static GLsizei GetProxyWidth()
	{
		return get_proxy_level_parameter(GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns internal storage resolution of RED component of the texture image. The initial value is 0
	@return The internal storage resolution of RED component*/
	GLuint GetRedSize()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_SIZE);
	}

	/*(3.2) Returns the type of RED component of the texture image
	@return The type of RED component of the texture image*/
	ComponentType GetRedType()
	{
		return (ComponentType)get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_RED_TYPE);
	}

	/*(3.2) Returns the width of the texture image. The initial value is 0
	@return The width of the texture image*/
	GLsizei GetWidth()
	{
		return get_tex_level_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_WIDTH);
	}

	/*(3.2) Returns the wrapping function for texture coordinate r. The initial value is <Repeat>. MSVC getter for <wrapR> property
	@return The current wrap mode for texture coordinate r*/
	WrapMode GetWrapR()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_R);
	}

	/*(3.2) Returns the wrapping function for texture coordinate s. The initial value is <Repeat>. MSVC getter for <wrapS> property
	@return The current wrap mode for texture coordinate s*/
	WrapMode GetWrapS()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_S);
	}

	/*(3.2) Returns the wrapping function for texture coordinate t. The initial value is <Repeat>. MSVC getter for <wrapT> property
	@return The current wrap mode for texture coordinate t*/
	WrapMode GetWrapT()
	{
		return (WrapMode)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_T);
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

	/*(3.2) Determines if the texture object is currently bound to its target. MSVC getter for <binding> property
	@return True if texture object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, Get());
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

	/*(3.2) (1) Specifies four integer values that should be used for border texels. The initial value is (0, 0, 0, 0)
	@param [in] Loads four integer texture color values*/
	void SetBorderColor(_In_reads_(4) const GLint* color)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) (2) Specifies four float values that should be used for border texels. The initial value is (0.0, 0.0, 0.0, 0.0)
	@param [in] Loads four float texture color values*/
	void SetBorderColor(_In_reads_(4) const GLfloat* color)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BORDER_COLOR, color);
	}

	/*(3.2) Specifies the comparison operator used when texture compare mode flag is set. The result is always assigned to the red channel. In the following equations the <r> is the current interpolated texture coordinate, and <Dt> is the depth texture value sampled from the currently bound depth texture. Equal: result = {1.0: r = Dt, 0.0: r != Dt}, Notequal: result = {1.0: r != Dt, 0.0: r = Dt}, Less: result = {1.0: r < Dt, 0.0: r >= Dt}, Greater: result = {1.0: r > Dt, 0.0: r <= Dt}, Lequal: result = {1.0: r <= Dt, 0.0: r > Dt}, Gequal: result = {1.0: r >= Dt, 0.0: r < Dt}, Always: result = {1.0}, Never: result = {0.0}. The initial value is <Lequal>. MSVC setter for <compareFunc> property
	@param The texture comparison function value*/
	void SetCompareFunc(CompareFunc func)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_FUNC, (GLint)func);
	}

	/*(3.2) Sets the texture comparison mode for currently bound depth textures. MSVC setter for <compareMode> property
	@param Specifies the texture compare mode value*/
	void SetCompareMode(CompareMode mode)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_COMPARE_MODE, (GLint)mode);
	}

	/*(3.2) Sets the texture magnification function value. The initial value is <Linear>. MSVC setter for <magFilter> property
	@param Specifies the texture magnification function's value*/
	void SetMagFilter(MagFilter filter)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	}

	/*(3.2) The texture minifying function is used whenever the level-of-detail function used when sampling from the texture determines that the texture should be minified. The initial value is <NearestMipmapLinear>. MSVC setter for <minFilter> property
	@param The texture minifying function value*/
	void SetMinFilter(MinFilter filter)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	}

	/*(3.2) Sets the wrapping function for texture coordinate r. MSVC setter for <wrapR> property
	@param The texture wrap mode for coordinate r*/
	void SetWrapR(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_R, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate s. MSVC setter for <wrapS> property
	@param The texture wrap mode for coordinate s*/
	void SetWrapS(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_S, (GLint)wrap);
	}

	/*(3.2) Sets the wrapping function for texture coordinate t. MSVC setter for <wrapT> property
	@param The texture wrap mode for coordinate t*/
	void SetWrapT(WrapMode wrap)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_T, (GLint)wrap);
	}

	/*(3.2) Unbinds any texture object bound to particular target, and restores its default texture. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property to determine if the texture object is currently bound to its target*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.2) Read-write property for current texture comparison function*/
	__declspec(property(get = GetCompareFunc, put = SetCompareFunc)) CompareFunc compareFunc;

	/*(3.2) Read-write property for texture comparison mode for currently bound depth textures*/
	__declspec(property(get = GetCompareMode, put = SetCompareMode)) CompareMode compareMode;

	/*(3.2) Read-write property for current texture magnification function*/
	__declspec(property(get = GetMagFilter, put = SetMagFilter)) MagFilter magFilter;

	/*(3.2) Read-write property for current texture minifying function*/
	__declspec(property(get = GetMinFilter, put = SetMinFilter)) MinFilter minFilter;

	/*(3.2) Read-write property for wrapping function of texture coordinate r*/
	__declspec(property(get = GetWrapR, put = SetWrapR)) WrapMode wrapR;

	/*(3.2) Read-write property for wrapping function of texture coordinate s*/
	__declspec(property(get = GetWrapS, put = SetWrapS)) WrapMode wrapS;

	/*(3.2) Read-write property for wrapping function of texture coordinate t*/
	__declspec(property(get = GetWrapT, put = SetWrapT)) WrapMode wrapT;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Returns the current alpha component swizzle value. The initial value is <Alpha>. MSVC getter for <swizzleA> property
	@return The alpha component swizzle value*/
	SwizzleMask GetSwizzleA()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_A);
	}

	/*(3.3) Returns the current blue component swizzle value. The initial value is <Blue>. MSVC getter for <swizzleB> property
	@return The blue component swizzle value*/
	SwizzleMask GetSwizzleB()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_B);
	}

	/*(3.3) Returns the current green component swizzle value. The initial value is <Green>. MSVC getter for <swizzleG> property
	@return The green component swizzle value*/
	SwizzleMask GetSwizzleG()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_G);
	}

	/*(3.3) Returns the current red component swizzle value. The initial value is <Red>. MSVC getter for <swizzleR> property
	@return The red component swizzle value*/
	SwizzleMask GetSwizzleR()
	{
		return (SwizzleMask)get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_R);
	}

	/*(3.3) Returns the component swizzle for red, green, blue, and alpha channels in a single query. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)
	@param [out] Stores four swizzle mask values*/
	void GetSwizzleRGBA(_Out_writes_(4) SwizzleMask* swizzle)
	{
		get_tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (GLint*)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the alpha component of a texel before it is returned to the shader. The initial value is <Alpha>. MSVC setter for <swizzleA> property
	@param The alpha component swizzle value*/
	void SetSwizzleA(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_A, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the blue component of a texel before it is returned to the shader. The initial value is <Blue>. MSVC setter for <swizzleB> property
	@param The blue component swizzle value*/
	void SetSwizzleB(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_B, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the green component of a texel before it is returned to the shader. The initial value is <Green>. MSVC setter for <swizzleG> property
	@param The green component swizzle value*/
	void SetSwizzleG(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_G, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzle that will be applied to the red component of a texel before it is returned to the shader. The initial value is <Red>. MSVC setter for <swizzleR> property
	@param The red component swizzle value*/
	void SetSwizzleR(SwizzleMask swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_R, (GLint)swizzle);
	}

	/*(3.3) Sets the swizzles that will be applied to the red, green, blue, and alpha components of a texel before they are returned to the shader. The initial value is (<Red>, <Green>, <Blue>, <Alpha>)
	@param [in] Loads four swizzle mask values*/
	void SetSwizzleRGBA(_In_reads_(4) const SwizzleMask* swizzle)
	{
		tex_parameter(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_RGBA, (const GLint*)swizzle);
	}
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.3) Read-write property for current alpha component swizzle value*/
	__declspec(property(get = GetSwizzleA, put = SetSwizzleA)) SwizzleMask swizzleA;

	/*(3.3) Read-write property for current blue component swizzle value*/
	__declspec(property(get = GetSwizzleB, put = SetSwizzleB)) SwizzleMask swizzleB;

	/*(3.3) Read-write property for current green component swizzle value*/
	__declspec(property(get = GetSwizzleG, put = SetSwizzleG)) SwizzleMask swizzleG;

	/*(3.3) Read-write property for current red component swizzle value*/
	__declspec(property(get = GetSwizzleR, put = SetSwizzleR)) SwizzleMask swizzleR;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
}; // class Texture2DMultisampleArray : public Textures
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_2
#endif // #ifndef YAGLPP_TEXTURE_2D_MULTISAMPLE_ARRAY_H
