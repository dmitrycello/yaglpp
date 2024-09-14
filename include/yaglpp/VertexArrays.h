#pragma once
#include "gladpp.h"
namespace gl {
#ifdef GL_VERSION_3_0
/*(3.0) OpenGL vertex array multi-object class derived from <_Objects>*/
class VertexArrays : public _Objects
{
public:
	/*(3.0) (1) Constructs an empty vertex array multi-object*/
	VertexArrays() {}

	/*(3.0) (2) Constucts a vertex array multi-object with <genVertexArrays>*/
	VertexArrays(GLsizei n)
	{
		genVertexArrays(n);
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

	/*(3.0) Generates one or more vertex array object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genVertexArrays(GLsizei n)
	{
		_objects_gen(glGenVertexArrays, n);
	}

	/*(3.0) Insert one or more vertex array object names at specified position into the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertVertexArrays(GLsizei n, GLint pos)
	{
		_objects_insert(glGenVertexArrays, n, pos);
	}

	/*(3.0) Remove one or more vertex array object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeVertexArrays(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteVertexArrays, n, pos);
	}
}; // class VertexArrays : public _Objects
#endif // #ifdef GL_VERSION_3_0
} // namespace gl
