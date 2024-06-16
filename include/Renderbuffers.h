#pragma once
#include "gladpp.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer multi-object class derived from <_Objects>*/
class Renderbuffers : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty renderbuffer multi-object*/
	Renderbuffers() {}

	/*(3.0) (2) Constucts a renderbuffer multi-object with <genRenderbuffers>*/
	Renderbuffers(GLsizei n)
	{
		genRenderbuffers(n);
	}

	/*(3.0) Cleans up the valid renderbuffer multi-object*/
	~Renderbuffers()
	{
		if (isObject())
		{
			deleteRenderbuffers();
		}
	}

	/*(3.0) Deletes valid renderbuffer multi-object*/
	void deleteRenderbuffers()
	{
		_objects_delete(glDeleteRenderbuffers);
	}

	/*(3.0) Generates one or more renderbuffer object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genRenderbuffers(GLsizei n)
	{
		_objects_gen(glGenRenderbuffers, n);
	}

	/*(3.0) Insert one or more renderbuffer object names at specified position in the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertRenderbuffers(GLsizei n, GLint pos)
	{
		_objects_insert(glGenRenderbuffers, n, pos);
	}

	/*(3.0) Remove one or more renderbuffer object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeRenderbuffers(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteRenderbuffers, n, pos);
	}
}; // class Renderbuffers : public _Objects
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
