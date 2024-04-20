#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL query multi-object class derived from <_Objects>*/
class Queries : public _Objects
{
public:
	/*(1) Constructs an empty query multi-object*/
	Queries() : _Objects() {}

	/*(2) Constucts a query multi-object with <genBuffers>*/
	Queries(GLuint num)
	{
		genQueries(num);
	}

	/*Cleans up the valid query multi-object*/
	~Queries()
	{
		if (isObject())
		{
			deleteQueries();
		}
	}

	/*Deletes valid query multi-object*/
	void deleteQueries()
	{
		_objects_delete(glDeleteQueries);
	}

	/*Generates one or more query object names in an empty multi-object
	@param Specifies the number of query object names to be generated*/
	void genQueries(GLuint num)
	{
		_objects_gen(glGenQueries, num);
	}
}; // class Queries : public _Object
} // namespace gl
