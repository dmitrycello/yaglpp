#pragma once
#include <yaglpp/gladpp.h>
namespace gl {
#ifdef YAGLPP_VERSION_3_0
/*(3.0) OpenGL framebuffer multi-object class derived from <_Objects>*/
class Framebuffers : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty framebuffer multi-object*/
	Framebuffers() {}

	/*(3.0) (2) Constucts a framebuffer multi-object with <genFramebuffers>*/
	Framebuffers(GLsizei n)
	{
		genFramebuffers(n);
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

	/*(3.0) Generates one or more framebuffer object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genFramebuffers(GLsizei n)
	{
		_objects_gen(glGenFramebuffers, n);
	}

	/*(3.0) Insert one or more framebuffer object names at specified position into the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertFramebuffers(GLsizei n, GLint pos)
	{
		_objects_insert(glGenFramebuffers, n, pos);
	}

	/*(3.0) Remove one or more framebuffer object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeFramebuffers(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteFramebuffers, n, pos);
	}
}; // class Framebuffers : public _Objects
#endif // #ifdef YAGLPP_VERSION_3_0
} // namespace gl
