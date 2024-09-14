#pragma once
#include "_Object.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer object class derived from <_Object>*/
class Renderbuffer : public _Object
{
protected:
	friend _Framebuffer;
	GLint _getRenderbufferParameter(GLenum pname);
	GLuint _renderbuffer_id()
	{
		return _object_id(glGenRenderbuffers);
	}

public:
	/*(3.0) (1) Constructs an empty renderbuffer object*/
	Renderbuffer() {}

	/*(3.0) (2) Constucts a renderbuffer object with <shareRenderbuffer>*/
	Renderbuffer(Renderbuffer& renderbuffer)
	{
		shareRenderbuffer(renderbuffer);
	}

	/*(3.0) (3) Constucts a renderbuffer object with <assignRenderbuffer>*/
	Renderbuffer(Renderbuffers& renderbuffers, GLuint index)
	{
		assignRenderbuffer(renderbuffers, index);
	}

	/*(3.0) Cleans up the valid renderbuffer object*/
	~Renderbuffer()
	{
		if (isObject())
		{
			deleteRenderbuffer();
		}
	}

	/*(3.0) Set an empty renderbuffer object as a reference to an element of the renderbuffer multi-object
	@param The renderbuffer multi-object
	@param The index of the object name*/
	void assignRenderbuffer(Renderbuffers& renderbuffers, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)renderbuffers, index, GL_RENDERBUFFER); // Single target
#else // #ifdef _DEBUG
		_object_assign((_Objects&)renderbuffers, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Explicitly binds renderbuffer object to its target. Does nothing if specified renderbuffer is bound*/
	void bindRenderbuffer();

	/*(3.0) Explicitly deletes previously generated single renderbuffer object*/
	void deleteRenderbuffer()
	{
		_object_delete(glDeleteRenderbuffers);
	}

	/*(3.0) Explicitly generates single renderbuffer object*/
	void genRenderbuffer()
	{
		_object_gen(glGenRenderbuffers);
	}

	/*(3.0) Get the maximum supported size for render-buffers
	@return The maximum renderbuffer size*/
	static GLsizei getMaxRenderbufferSize()
	{
		return _getInteger(GL_MAX_RENDERBUFFER_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the ALPHA component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferAlphaSize> property
	@return The renderbuffer actual resolution for the ALPHA component*/
	GLsizei getRenderbufferAlphaSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_ALPHA_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the BLUE component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferBlueSize> property
	@return The renderbuffer actual resolution for the BLUE component*/
	GLsizei getRenderbufferBlueSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_BLUE_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the DEPTH component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferDepthSize> property
	@return The renderbuffer actual resolution for the DEPTH component*/
	GLsizei getRenderbufferDepthSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_DEPTH_SIZE);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the GREEN component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferGreenSize> property
	@return The renderbuffer actual resolution for the GREEN component*/
	GLsizei getRenderbufferGreenSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_GREEN_SIZE);
	}

	/*(3.0) Query the height in pixels of a renderbuffer object. Used as a getter of <renderbufferHeight> property. Used as a getter of <renderbufferHeight> property
	@return The height in pixels of a renderbuffer object*/
	GLsizei getRenderbufferHeight()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_HEIGHT);
	}

	/*(3.0) Query the internal format of a renderbuffer object. Used as a getter of <renderbufferInternalFormat> property. Used as a getter of <renderbufferHeight> property
	@return The internal format of a renderbuffer object*/
	ColorDepthStencilFormat getRenderbufferInternalFormat()
	{
		return (ColorDepthStencilFormat)_getRenderbufferParameter(GL_RENDERBUFFER_INTERNAL_FORMAT);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the RED component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferRedSize> property
	@return The renderbuffer actual resolution for the RED component*/
	GLsizei getRenderbufferRedSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_RED_SIZE);
	}

	/*(3.0) Query the number of samples of a renderbuffer object. Used as a getter of <renderbufferSamples> property
	@return The number of samples of a renderbuffer object*/
	GLint getRenderbufferSamples()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_SAMPLES);
	}

	/*(3.0) Query the actual resolution (not the resolution specified when the image array was defined) for the STENCIL component of the image of the renderbuffer currently bound to target. Used as a getter of <renderbufferStencilSize> property
	@return The renderbuffer actual resolution for the STENCIL component*/
	GLsizei getRenderbufferStencilSize()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_STENCIL_SIZE);
	}

	/*(3.0) Query the width in pixels of a renderbuffer object. Used as a getter of <renderbufferWidth> property
	@return The width in pixels of a renderbuffer object*/
	GLsizei getRenderbufferWidth()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_WIDTH);
	}

	/*(3.0) Determines if a name corresponds to a renderbuffer object. Used as a getter of <renderbuffer> property
	@return True if active renderbuffer object, false otherwise*/
	GLboolean isRenderbuffer()
	{
		return glIsRenderbuffer(_object_id());
	}

	/*(3.0) Determines if the renderbuffer object is currently bound to its target
	@return True if renderbuffer object currently bound to its target, or false otherwise*/
	GLboolean isRenderbufferBinding()
	{
		return _object_id() == _getInteger(GL_RENDERBUFFER_BINDING);
	}

	/*(3.0) Establishes data storage, format and dimensions of a renderbuffer object's image
	@param Specifies the renderbuffer color-renderable, depth-renderable, or stencil-renderable internal format
	@param Specifies the width of the renderbuffer, in pixels
	@param Specifies the height of the renderbuffer, in pixels*/
	void renderbufferStorage(ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height);

	/*(3.0) Establishes data storage, format, dimensions and sample count of a renderbuffer object's image
	@param Specifies the number of samples to be used for the renderbuffer object's storage
	@param Specifies the renderbuffer color-renderable, depth-renderable, or stencil-renderable internal format
	@param Specifies the width of the renderbuffer, in pixels
	@param Specifies the height of the renderbuffer, in pixels*/
	void renderbufferStorageMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height);

	/*(3.0) Sets the creation state of the renderbuffer object, only if current state is opposite. Depending of the flag value, calls <genRenderbuffer> or <deleteRenderbuffer> functions. Used as a setter of <renderbuffer> property
	@param True to generate renderbuffer object name, false to delete renderbuffer object*/
	void setRenderbuffer(GLboolean gen);

	/*(3.0) Sets the binding state of the buffer object, only if current state is opposite. Used as a setter of <bufferBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setRenderbufferBinding(GLboolean bind)
	{
		(bind) ? bindRenderbuffer() : unbindRenderbuffer();
	}

	/*(3.0) Set an empty renderbuffer object as a reference to the renderbuffer object from another context
	@param The renderbuffer object to share, must not be empty*/
	void shareRenderbuffer(Renderbuffer& renderbuffer)
	{
		_object_share((_Object&)renderbuffer);
	}

	/*(3.0) Explicitly unbinds specified renderbuffer object from its target. Does nothing if specified renderbuffer is not bound*/
	void unbindRenderbuffer();

	/*(3.0) Explicitly unbinds any renderbuffer object of specified type bound to its target. Does nothing if no such renderbuffer is bound*/
	static void unbindTarget();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for creation state of the renderbuffer object*/
	__declspec(property(get = isRenderbuffer, put = setRenderbuffer)) GLboolean renderbuffer;

	/*(3.0) Read-only property for renderbuffer actual resolution for the ALPHA component*/
	__declspec(property(get = getRenderbufferAlphaSize)) GLsizei renderbufferAlphaSize;

	/*(3.0) Read-write property for binding state of the renderbuffer object*/
	__declspec(property(get = isRenderbufferBinding, put = setRenderbufferBinding)) GLboolean renderbufferBinding;

	/*(3.0) Read-only property for renderbuffer actual resolution for the BLUE component*/
	__declspec(property(get = getRenderbufferBlueSize)) GLsizei renderbufferBlueSize;

	/*(3.0) Read-only property for renderbuffer actual resolution for the DEPTH component*/
	__declspec(property(get = getRenderbufferDepthSize)) GLsizei renderbufferDepthSize;

	/*(3.0) Read-only property for renderbuffer actual resolution for the GREEN component*/
	__declspec(property(get = getRenderbufferGreenSize)) GLsizei renderbufferGreenSize;

	/*(3.0) Read-only property for height in pixels of a renderbuffer object*/
	__declspec(property(get = getRenderbufferHeight)) GLsizei renderbufferHeight;

	/*(3.0) Read-only property for internal format of a renderbuffer object*/
	__declspec(property(get = getRenderbufferInternalFormat)) ColorDepthStencilFormat renderbufferInternalFormat;

	/*(3.0) Read-only property for renderbuffer actual resolution for the RED component*/
	__declspec(property(get = getRenderbufferRedSize)) GLsizei renderbufferRedSize;

	/*(3.0) Read-only property for number of samples of a renderbuffer object*/
	__declspec(property(get = getRenderbufferSamples)) GLint renderbufferSamples;

	/*(3.0) Read-only property for renderbuffer actual resolution for the STENCIL component*/
	__declspec(property(get = getRenderbufferStencilSize)) GLsizei renderbufferStencilSize;

	/*(3.0) Read-only property for width in pixels of a renderbuffer object*/
	__declspec(property(get = getRenderbufferWidth)) GLsizei renderbufferWidth;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class Renderbuffer : public _Object

/*(3.0) Explicitly unbinds any renderbuffer object bound to its target. Does nothing if no renderbuffer is bound*/
inline void unbindRenderbuffer()
{
	Renderbuffer::unbindTarget();
}

#ifdef YAGLPP_IMPLEMENTATION
GLint Renderbuffer::_getRenderbufferParameter(GLenum pname)
{
	GLint iResult;
	bindRenderbuffer();
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void Renderbuffer::bindRenderbuffer()
{
	GLuint uBound, uId = _renderbuffer_id();
	glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	if (uBound != uId)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, uId);
		YAGLPP_GLAD_ERROR;
	}
}

void Renderbuffer::renderbufferStorage(ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	bindRenderbuffer();
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
	YAGLPP_GLAD_ERROR;
}

void Renderbuffer::renderbufferStorageMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	bindRenderbuffer();
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
	YAGLPP_GLAD_ERROR;
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
	YAGLPP_GLAD_ERROR;
	if (uBound == uId)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		YAGLPP_GLAD_ERROR;
	}
}

void Renderbuffer::unbindTarget()
{
	GLuint uBound;
	glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	if (uBound != 0)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		YAGLPP_GLAD_ERROR;
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
