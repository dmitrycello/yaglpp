#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL buffer multi-object class derived from <_Objects>*/
class Buffers : public _Objects
{
public:
	/*(1) Constructs an empty buffer multi-object*/
	Buffers() : _Objects() {}

	/*(2) Constucts a buffer multi-object with <genBuffers>*/
	Buffers(GLuint num)
	{
		genBuffers(num);
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

	/*Generates one or more buffer object names in an empty multi-object
	@param Specifies the number of buffer object names to be generated*/
	void genBuffers(GLuint num)
	{
		_objects_gen(glGenBuffers, num);
	}
}; // class Buffers : public _Object
} // namespace gl
