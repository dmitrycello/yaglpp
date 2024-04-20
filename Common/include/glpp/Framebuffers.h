#pragma once
#include "gladpp.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL framebuffer multi-object class derived from <_Objects>*/
class Framebuffers : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty framebuffer multi-object*/
	Framebuffers() : _Objects() {}

	/*(3.0) (2) Constucts a framebuffer multi-object with <genFramebuffers>*/
	Framebuffers(GLuint num)
	{
		genFramebuffers(num);
	}

	/*(3.0) Cleans up the valid framebuffer multi-object*/
	~Framebuffers()
	{
		if (isObject())
		{
			deleteFramebuffers();
		}
	}

	/*(3.0) Deletes valid framebuffer multi-object*/
	void deleteFramebuffers()
	{
		_objects_delete(glDeleteFramebuffers);
	}

	/*(3.0) Generates one or more framebuffer object names in an empty multi-object
	@param Specifies the number of framebuffer object names to be generated*/
	void genFramebuffers(GLuint num)
	{
		_objects_gen(glGenFramebuffers, num);
	}
}; // class Framebuffers : public _Objects
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
