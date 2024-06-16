#pragma once
#include "gladpp.h"
#include "_Object.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer object class derived from <_Object>*/
class Renderbuffer : public _Object
{
protected:
	friend _Framebuffer;
	GLuint _renderbuffer_id()
	{
		return _object_id(glGenRenderbuffers);
	}

	void _renderbuffer_bind(GLuint* tls)
	{
		_bindRenderbuffer(tls, _renderbuffer_id());
	}

	void _renderbuffer_rebind(GLuint* tls)
	{
		*tls = 0;  _renderbuffer_bind(tls);
	}

	static GLuint* _tlsRenderbuffer()
	{
		thread_local GLuint tls = 0; return &tls;
	}

	static void _bindRenderbuffer(GLuint* tls, GLuint renderbuffer);
	GLint _getRenderbufferParameter(GLenum pname);

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

	/*(3.0) Explicitly binds renderbuffer object to its target*/
	void bindRenderbuffer()
	{
		_renderbuffer_rebind(_tlsRenderbuffer());
	}

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

	/*(3.0) Query the height in pixels of a renderbuffer object
	@return The height in pixels of a renderbuffer object*/
	GLsizei getRenderbufferHeight()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_HEIGHT);
	}

	/*(3.0) Query the number of samples of a renderbuffer object
	@return The number of samples of a renderbuffer object*/
	int getRenderbufferSamples()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_SAMPLES);
	}

	/*(3.0) Query the width in pixels of a renderbuffer object
	@return The width in pixels of a renderbuffer object*/
	GLsizei getRenderbufferWidth()
	{
		return _getRenderbufferParameter(GL_RENDERBUFFER_WIDTH);
	}

	/*(3.0) Determines via API if renderbuffer object is currently active
	@return True if active renderbuffer object, false otherwise*/
	GLboolean isRenderbuffer()
	{
		return glIsRenderbuffer(_object_id());
	}

	/*(3.0) Determines via API if the renderbuffer object is currently bound to its target
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

	/*(3.0) Set an empty renderbuffer object as a reference to the renderbuffer object from another context
	@param The renderbuffer object to share, must not be empty*/
	void shareRenderbuffer(Renderbuffer& renderbuffer)
	{
		_object_share((_Object&)renderbuffer);
	}

	/*(3.0) Unbinds any previously bound renderbuffer object from its target. Does nothing if no renderbuffer is bound*/
	static void unbindRenderbuffer()
	{
		_bindRenderbuffer(_tlsRenderbuffer(), 0);
	}
}; // class Renderbuffer : public _Object

#ifndef _DEBUG
inline void Renderbuffer::_bindRenderbuffer(GLuint* tls, GLuint renderbuffer)
{
	if (*tls == renderbuffer) return;
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer); *tls = renderbuffer;
}

inline GLint Renderbuffer::_getRenderbufferParameter(GLenum pname)
{
	_renderbuffer_bind(_tlsRenderbuffer());
	GLint i; glGetRenderbufferParameteriv(GL_RENDERBUFFER, pname, &i); return i;
}

inline void Renderbuffer::renderbufferStorage(ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	_renderbuffer_bind(_tlsRenderbuffer());
	glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)internalformat, width, height);
}

inline void Renderbuffer::renderbufferStorageMultisample(GLsizei samples, ColorDepthStencilFormat internalformat, GLsizei width, GLsizei height)
{
	_renderbuffer_bind(_tlsRenderbuffer());
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internalformat, width, height);
}
#endif // #ifndef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
