#pragma once
#include <yaglpp/glad/_object.h>
#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer object class derived from <_Object>*/
class Renderbuffer : public _Object
{
private:
	friend class _Framebuffer;
	friend class Renderbuffers;
	Renderbuffer(GLint name) { _object_set(name); }
	void _renderbuffer_delete() {
		_object_delete(glDeleteRenderbuffers);
	}
	void _renderbuffer_dup(_Object& source) {
		_object_dup(glDeleteRenderbuffers, source);
	}
	void _renderbuffer_gen() {
		_object_gen(glGenRenderbuffers, glDeleteRenderbuffers, 1);
	}
	GLuint _renderbuffer_id() {
		return _object_id(glGenRenderbuffers, 1);
	}
	void _renderbuffer_refer(_Object& source) {
		_object_refer(glDeleteRenderbuffers, source);
	}
	GLint _getRenderbufferParameter(GLenum pname);

public:
	/*(3.0) (1) Constructs an empty renderbuffer object*/
	Renderbuffer() {}

	/*(3.0) (2) Constructs a copy of renderbuffer object*/
	Renderbuffer(const Renderbuffer& source)
	{
		_renderbuffer_dup((_Object&)source);
	}

	/*(3.0) Cleans up the valid renderbuffer object*/
	~Renderbuffer()
	{
		_renderbuffer_delete();
	}

	/*(3.0) Explicitly binds renderbuffer object to its target. Does nothing if specified renderbuffer is bound*/
	void bindRenderbuffer();

	/*(3.0) Closes the inctance of OpenGL renderbuffer object, decreasing its reference count. The last instance is being deleted, while the reference object is only being voided*/
	void deleteRenderbuffer()
	{
		_renderbuffer_delete();
	}

	/*(3.0) Duplicates a renderbuffer object, increasing its reference count. The reference source object is being copied
	@param Specifies the source renderbuffer object*/
	void duplicateRenderbuffer(const Renderbuffer& source)
	{
		_renderbuffer_dup((_Object&)source);
	}

	/*(3.0) Explicitly generates OpenGL renderbuffer object name*/
	void genRenderbuffer()
	{
		_renderbuffer_gen();
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

	/*(3.0) Returns a reference renderbuffer object currently bound to its target
	@return The reference renderbuffer object, or empty object*/
	static Renderbuffer getRenderbufferBinding()
	{
		return Renderbuffer(_getInteger(GL_RENDERBUFFER_BINDING));
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

	/*(3.0) Checks if the source renderbuffer object is referencing the same OpenGL object
	@param Specifies the source buffer object
	@return True if duplicate object*/
	GLboolean isDuplicate(const Renderbuffer& source) const
	{
		return _object_is((_Object&)source);
	}

	/*(3.0) Determines if a name corresponds to a renderbuffer object. Used as a getter of <renderbuffer> property
	@return True if active renderbuffer object, false otherwise*/
	GLboolean isRenderbuffer() const
	{
		return glIsRenderbuffer(_object_id());
	}

	/*(3.0) Determines if the renderbuffer object is currently bound to its target
	@return True if renderbuffer object currently bound to its target, or false otherwise*/
	GLboolean isRenderbufferBinding() const
	{
		return _object_binding(GL_RENDERBUFFER_BINDING);
	}

	/*(3.0) Creates a thread-safe reference object from the source renderbuffer object
	@param Specifies the source renderbuffer object*/
	void referRenderbuffer(const Renderbuffer& source)
	{
		_renderbuffer_refer((_Object&)source);
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

/*(3.0) OpenGL renderbuffer multi-object class derived from <_Objects>*/
class Renderbuffers : public _Objects
{
private:
	void _renderbuffers_delete() {
		_objects_delete(glDeleteRenderbuffers);
	}
	void _renderbuffers_dup(_Objects& source) {
		_objects_dup(glDeleteRenderbuffers, source);
	}
	void _renderbuffers_gen(GLsizei num) {
		_objects_gen(glGenRenderbuffers, glDeleteRenderbuffers, num);
	}

public:
	/*(3.0) (1) Constructs an empty renderbuffer multi-object*/
	Renderbuffers() {}

	/*(3.0) (2) Constructs a copy of renderbuffer multi-object*/
	Renderbuffers(const Renderbuffers& source)
	{
		_renderbuffers_dup((_Objects&)source);
	}

	/*(3.0) (3) Constucts an initialized renderbuffer multi-object*/
	Renderbuffers(GLsizei num)
	{
		_renderbuffers_gen(num);
	}

	/*(3.0) Cleans up the renderbuffer multi-object*/
	~Renderbuffers()
	{
		_renderbuffers_delete();
	}

	/*(3.0) Closes the inctance of OpenGL renderbuffer multi-object, decreasing its reference count. The last instance is being deleted*/
	void deleteRenderbuffers()
	{
		_renderbuffers_delete();
	}

	/*(3.0) Duplicates a renderbuffer multi-object, increasing its reference count
	@param Specifies the source renderbuffer multi-object*/
	void duplicateRenderbuffers(const Renderbuffers& source)
	{
		_renderbuffers_dup((_Objects&)source);
	}

	/*(3.0) Generates one or more renderbuffer object names in the renderbuffer multi-object
	@param Specifies the number of object names to be generated*/
	void genRenderbuffers(GLsizei num)
	{
		_renderbuffers_gen(num);
	}

	/*(3.0) Retrieves a reference renderbuffer object from a valid multi-object
	@param Specifies the object name index
	@return The reference renderbuffer object, or empty object*/
	Renderbuffer getRenderbuffer(GLuint index) const
	{
#ifdef _DEBUG
		return Renderbuffer(_objects_get(index, GL_RENDERBUFFER));
#else // #ifdef _DEBUG
		return Renderbuffer(_objects_get(index));
#endif // #ifdef _DEBUG
	}

	/*(3.0) Checks if the source Renderbuffers object is referencing the same multi-object
	@param The source multi-object
	@return True if duplicate multi-object*/
	GLboolean isDuplicate(const Renderbuffers& source) const
	{
		return _objects_is((_Objects&)source);
	}
}; // class Renderbuffers : public _Objects

/*(3.0) Returns a reference renderbuffer object currently bound to its target
@return The reference renderbuffer object, or empty object*/
inline Renderbuffer getRenderbufferBinding()
{
	return Renderbuffer::getRenderbufferBinding();
}

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
	if (!_object_binding(GL_RENDERBUFFER_BINDING))
	{
		glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer_id());
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
			_renderbuffer_delete();
		}
	}
	else if (gen == GL_TRUE)
	{
		_renderbuffer_gen();
	}
}

void Renderbuffer::unbindRenderbuffer()
{
	if (_object_binding(GL_RENDERBUFFER_BINDING))
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		YAGLPP_GLAD_ERROR;
	}
}

void Renderbuffer::unbindTarget()
{
	if (_getInteger(GL_RENDERBUFFER_BINDING) != 0)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		YAGLPP_GLAD_ERROR;
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
