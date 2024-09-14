#pragma once
#include "gladpp.h"
namespace gl {
#ifdef GL_VERSION_3_3
/*(3.3) OpenGL sampler multi-object class derived from <_Objects>*/
class Samplers : public _Objects
{
public:
	/*(3.3) (1) Constructs an empty sampler multi-object*/
	Samplers() {}

	/*(3.3) (2) Constucts a sampler multi-object with <genSamplers>*/
	Samplers(GLsizei n)
	{
		genSamplers(n);
	}

	/*(3.3) Cleans up the valid sampler multi-object*/
	~Samplers()
	{
		if (isObject())
		{
			deleteSamplers();
		}
	}

	/*(3.3) Deletes valid sampler multi-object*/
	void deleteSamplers()
	{
		_objects_delete(glDeleteSamplers);
	}

	/*(3.3) Generates one or more sampler object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genSamplers(GLsizei n)
	{
		_objects_gen(glGenSamplers, n);
	}

	/*(3.3) Insert one or more sampler object names at specified position into the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertSamplers(GLsizei n, GLint pos)
	{
		_objects_insert(glGenSamplers, n, pos);
	}

	/*(3.3) Remove one or more sampler object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeSamplers(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteSamplers, n, pos);
	}
}; // class Samplers : public _Objects
#endif // #ifdef GL_VERSION_3_3
} // namespace gl
