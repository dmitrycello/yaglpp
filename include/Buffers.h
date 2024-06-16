#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL buffer multi-object class derived from <_Objects>*/
class Buffers : public _Objects
{
public:
	/*(1) Constructs an empty buffer multi-object*/
	Buffers() {}

	/*(2) Constucts a buffer multi-object with <genBuffers>*/
	Buffers(GLsizei n)
	{
		genBuffers(n);
	}

	/*Cleans up the valid buffer multi-object*/
	~Buffers()
	{
		if (isObject())
		{
			deleteBuffers();
		}
	}

	/*Deletes valid buffer multi-object*/
	void deleteBuffers()
	{
		_objects_delete(glDeleteBuffers);
	}

	/*Generates one or more buffer object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genBuffers(GLsizei n)
	{
		_objects_gen(glGenBuffers, n);
	}

	/*Insert one or more buffer object names at specified position in the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertBuffers(GLsizei n, GLint pos)
	{
		_objects_insert(glGenBuffers, n, pos);
	}

	/*Remove one or more buffer object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeBuffers(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteBuffers, n, pos);
	}
}; // class Buffers : public _Object
} // namespace gl
