#pragma once
#include "gladpp.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL vertex array multi-object class derived from <_Objects>*/
class VertexArrays : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty vertex array multi-object*/
	VertexArrays() : _Objects() {}

	/*(3.0) (2) Constucts a vertex array multi-object with <genVertexArrays>*/
	VertexArrays(GLuint num)
	{
		genVertexArrays(num);
	}

	/*(3.0) Cleans up the valid vertex array multi-object*/
	~VertexArrays()
	{
		if (isObject())
		{
			deleteVertexArrays();
		}
	}

	/*(3.0) Deletes valid vertex array multi-object*/
	void deleteVertexArrays()
	{
		_objects_delete(glDeleteVertexArrays);
	}

	/*(3.0) Generates one or more vertex array object names in an empty multi-object
	@param Specifies the number of vertex array object names to be generated*/
	void genVertexArrays(GLuint num)
	{
		_objects_gen(glGenVertexArrays, num);
	}
}; // class VertexArrays : public _Objects
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
