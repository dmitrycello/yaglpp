#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_RENDERBUFFER_H
#define YAGLPP_RENDERBUFFER_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer object class derived from <Objects>*/
class Renderbuffer : public Objects
{
public:
	using Objects::Objects;
	/*(3.0) (1) Constructs default renderbuffer object*/
	Renderbuffer() : Objects() {}

	/*(3.0) (2) Constructs and establishes data storage of renderbuffer object with <Storage>*/
	Renderbuffer(ColorDepthStencil internalformat, GLsizei width, GLsizei height) : Objects()
	{
		create_renderbuffer(0, (GLenum)internalformat, width, height);
	}

	/*(3.0) (3) Constructs and establishes data storage of multisample renderbuffer object with <StorageMultisample>*/
	Renderbuffer(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height) : Objects()
	{
		create_renderbuffer(samples, (GLenum)internalformat, width, height);
	}

	/*(3.0) Allocates an array of renderbuffer objects of a given size, and generates their object names. Must be deallocated with <Renderbuffer::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Renderbuffer* Alloc(GLsizei n)
	{
		return (Renderbuffer*)object_alloc(glGenRenderbuffers, n);
	}

	/*(3.0) Binds renderbuffer object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(glBindRenderbuffer, GL_RENDERBUFFER);
	}

	/*(3.0) Deletes previously allocated array of renderbuffer object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Renderbuffer* renderbuffers)
	{
		object_dealloc(glDeleteRenderbuffers, (GLuint*)renderbuffers);
	}

	/*(3.0) Deletes valid OpenGL renderbuffer object name and sets the renderbuffer class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteRenderbuffers);
	}

	/*(3.0) Deletes previously generated OpenGL renderbuffer object names in a static array or a user-defined structure of renderbuffers, namely renderbuffer map, and sets its class objects in empty state. Allows to unset multiple renderbuffers in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of renderbuffer map returned by sizeof operator
	@param [in-out] Pointer to renderbuffer map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* renderbufferMap)
	{
		object_delete_map(glDeleteRenderbuffers, n, renderbufferMap);
	}

	/*(3.0) (1) Generates OpenGL renderbuffer object name in an empty renderbuffer class object*/
	void Gen()
	{
		object_gen(glGenRenderbuffers);
	}

	/*(3.0) Generates OpenGL renderbuffer object name in an empty renderbuffer class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenRenderbuffers, glBindRenderbuffer, GL_RENDERBUFFER);
	}

	/*(3.0) Generates OpenGL renderbuffer object names in a static array or a user-defined structure of renderbuffers, namely renderbuffer map. Allows to set multiple renderbuffers in one function call. All class objects are silently overwritten
	@param The size in bytes of renderbuffer map returned by sizeof operator
	@param [out] Pointer to renderbuffer map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* renderbufferMap)
	{
		object_gen_map(glGenRenderbuffers, n, renderbufferMap);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the ALPHA component of the image of the renderbuffer currently bound to target. MSVC getter for <alphaSize> property
	@return The renderbuffer actual resolution for the ALPHA component*/
	GLsizei GetAlphaSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_ALPHA_SIZE);
	}

	/*(3.0) Returns Renderbuffer object currently bound to its target
	@return The Renderbuffer object bound to its target, or empty object*/
	static Renderbuffer GetBinding()
	{
		return Renderbuffer(yaglpp_glad_integer(GL_RENDERBUFFER_BINDING));
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the BLUE component of the image of the renderbuffer currently bound to target. MSVC getter for <blueSize> property
	@return The renderbuffer actual resolution for the BLUE component*/
	GLsizei GetBlueSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_BLUE_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the DEPTH component of the image of the renderbuffer currently bound to target. MSVC getter for <depthSize> property
	@return The renderbuffer actual resolution for the DEPTH component*/
	GLsizei GetDepthSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_DEPTH_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the GREEN component of the image of the renderbuffer currently bound to target. MSVC getter for <greenSize> property
	@return The renderbuffer actual resolution for the GREEN component*/
	GLsizei GetGreenSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_GREEN_SIZE);
	}

	/*(3.0) Query the height in pixels of a renderbuffer object. MSVC getter for <height> property
	@return The height in pixels of a renderbuffer object*/
	GLsizei GetHeight()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_HEIGHT);
	}

	/*(3.0) Query the internal format of a renderbuffer object. MSVC getter for <internalFormat> property
	@return The internal format of a renderbuffer object*/
	ColorDepthStencil GetInternalFormat()
	{
		return (ColorDepthStencil)get_renderbuffer_parameter(GL_RENDERBUFFER_INTERNAL_FORMAT);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the RED component of the image of the renderbuffer currently bound to target. MSVC getter for <redSize> property
	@return The renderbuffer actual resolution for the RED component*/
	GLsizei GetRedSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_RED_SIZE);
	}

	/*(3.0) Query the number of samples of a renderbuffer object. MSVC getter for <samples> property
	@return The number of samples of a renderbuffer object*/
	GLint GetSamples()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_SAMPLES);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the STENCIL component of the image of the renderbuffer currently bound to target. MSVC getter for <stencilSize> property
	@return The renderbuffer actual resolution for the STENCIL component*/
	GLsizei GetStencilSize()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_STENCIL_SIZE);
	}

	/*(3.0) Query the width in pixels of a renderbuffer object. MSVC getter for <width> property
	@return The width in pixels of a renderbuffer object*/
	GLsizei GetWidth()
	{
		return get_renderbuffer_parameter(GL_RENDERBUFFER_WIDTH);
	}

	/*(3.0) Determines if the renderbuffer object is currently bound to its target. MSVC getter for <binding> property
	@return True if renderbuffer object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_RENDERBUFFER_BINDING, Get());
	}

	/*(3.0) Determines if a valid OpenGL renderbuffer object name corresponds to a renderbuffer object. MSVC getter for <renderbuffer> property
	@return True if active renderbuffer object, false otherwise*/
	GLboolean IsRenderbuffer() const
	{
		return object_is(glIsRenderbuffer);
	}

	/*(3.0) Establishes data storage, format and dimensions of a renderbuffer object's image
	@param Specifies the renderbuffer color-renderable, depth-renderable, or stencil-renderable internal format
	@param Specifies the width of the renderbuffer, in pixels
	@param Specifies the height of the renderbuffer, in pixels*/
	void Storage(ColorDepthStencil internalformat, GLsizei width, GLsizei height);

	/*(3.0) Establishes data storage, format, dimensions and sample count of a renderbuffer object's image
	@param Specifies the number of samples to be used for the renderbuffer object's storage
	@param Specifies the renderbuffer color-renderable, depth-renderable, or stencil-renderable internal format
	@param Specifies the width of the renderbuffer, in pixels
	@param Specifies the height of the renderbuffer, in pixels*/
	void StorageMultisample(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height);

	/*(3.0) Unbinds any renderbuffer object bound to its target. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER_BINDING, 0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property for renderbuffer actual resolution for the ALPHA component*/
	__declspec(property(get = GetAlphaSize)) GLsizei alphaSize;

	/*(3.0) Read-only property for renderbuffer binding flag*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.0) Read-only property for renderbuffer actual resolution for the BLUE component*/
	__declspec(property(get = GetBlueSize)) GLsizei blueSize;

	/*(3.0) Read-only property for renderbuffer actual resolution for the DEPTH component*/
	__declspec(property(get = GetDepthSize)) GLsizei depthSize;

	/*(3.0) Read-only property for renderbuffer actual resolution for the GREEN component*/
	__declspec(property(get = GetGreenSize)) GLsizei greenSize;

	/*(3.0) Read-only property for height in pixels of a renderbuffer object*/
	__declspec(property(get = GetHeight)) GLsizei height;

	/*(3.0) Read-only property for internal format of a renderbuffer object*/
	__declspec(property(get = GetInternalFormat)) ColorDepthStencil internalFormat;

	/*(3.0) Read-only property for renderbuffer actual resolution for the RED component*/
	__declspec(property(get = GetRedSize)) GLsizei redSize;

	/*(3.0) Read-only property to check if active renderbuffer object*/
	__declspec(property(get = IsRenderbuffer)) GLboolean renderbuffer;

	/*(3.0) Read-only property for number of samples of a renderbuffer object*/
	__declspec(property(get = GetSamples)) GLint samples;

	/*(3.0) Read-only property for renderbuffer actual resolution for the STENCIL component*/
	__declspec(property(get = GetStencilSize)) GLsizei stencilSize;

	/*(3.0) Read-only property for width in pixels of a renderbuffer object*/
	__declspec(property(get = GetWidth)) GLsizei width;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	void auto_delete() { if (IsRenderbuffer()) Delete(); }
	GLint get_renderbuffer_parameter(GLenum pname);
	void create_renderbuffer(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
}; // class Renderbuffer : public Object

#ifdef YAGLPP_IMPLEMENTATION
void Renderbuffer::create_renderbuffer(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	// INVALID WIDTH VALUE
	YAGLPP_ASSERT((width > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	// INVALID HEIGHT VALUE
	YAGLPP_ASSERT((height > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	object_gen(glGenRenderbuffers);
	object_bind(glBindRenderbuffer, GL_RENDERBUFFER);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLint Renderbuffer::get_renderbuffer_parameter(GLenum pname)
{
	// RENDERBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(GL_RENDERBUFFER_BINDING, Get()));

	GLint iResult;
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void Renderbuffer::Storage(ColorDepthStencil internalformat, GLsizei width, GLsizei height)
{
	// INVALID WIDTH VALUE
	YAGLPP_ASSERT((width > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	// INVALID HEIGHT VALUE
	YAGLPP_ASSERT((height > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	// RENDERBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(GL_RENDERBUFFER_BINDING, Get()));

	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
	YAGLPP_GLAD_ERROR;
}

void Renderbuffer::StorageMultisample(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height)
{
	// INVALID WIDTH VALUE
	YAGLPP_ASSERT((width > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	// INVALID HEIGHT VALUE
	YAGLPP_ASSERT((height > 0) && ((GLuint)width <= GetMaxRenderbufferSize()));

	// INVALID SAMPLES VALUE
	YAGLPP_ASSERT((samples > 0) && (samples <= (GLsizei)GetMaxSamples()));

	// RENDERBUFFER OBJECT IS NOT BOUND TO TARGET
	YAGLPP_ASSERT(object_binding(GL_RENDERBUFFER_BINDING, Get()));

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLint Renderbuffer::get_renderbuffer_parameter(GLenum pname)
{
	GLint i; glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &i); return i;
}

inline void Renderbuffer::Storage(ColorDepthStencil internalformat, GLsizei width, GLsizei height)
{
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
}

inline void Renderbuffer::StorageMultisample(GLsizei samples, ColorDepthStencil internalformat, GLsizei width, GLsizei height)
{
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_RENDERBUFFER_H
