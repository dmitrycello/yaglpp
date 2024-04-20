#pragma once
#include "gladpp.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL renderbuffer multi-object class derived from <_Objects>*/
class Renderbuffers : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty renderbuffer multi-object*/
	Renderbuffers() : _Objects() {}

	/*(3.0) (2) Constucts a renderbuffer multi-object with <genRenderbuffers>*/
	Renderbuffers(GLuint num)
	{
		genRenderbuffers(num);
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

	/*(3.0) Generates one or more renderbuffer object names in an empty multi-object
	@param Specifies the number of renderbuffer object names to be generated*/
	void genRenderbuffers(GLuint num)
	{
		_objects_gen(glGenRenderbuffers, num);
	}
}; // class Renderbuffers : public _Objects
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
