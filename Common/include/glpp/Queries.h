#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL query multi-object class derived from <_Objects>*/
class Queries : public _Objects
{
public:
	/*(1) Constructs an empty query multi-object*/
	Queries() : _Objects() {}

	/*(2) Constucts a query multi-object with <genQueries>*/
	Queries(GLsizei n)
	{
		genQueries(n);
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

	/*Generates one or more query object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genQueries(GLsizei n)
	{
		_objects_gen(glGenQueries, n);
	}

	/*Insert one or more query object names at specified position in the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertQueries(GLsizei n, GLint pos)
	{
		_objects_insert(glGenQueries, n, pos);
	}

	/*Remove one or more query object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeQueries(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteQueries, n, pos);
	}
}; // class Queries : public _Object
} // namespace gl
