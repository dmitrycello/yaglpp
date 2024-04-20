#pragma once
#include "gladpp.h"
#include "_Query.h"
namespace gl {
#ifdef GL_VERSION_3_0
/*(3.0) OpenGL generated primitives query object class derived from <_Query>*/
class PrimitivesGenerated : public _Query
{
public:
	/*(3.0) (1) Constructs an empty query object*/
	PrimitivesGenerated() : _Query() {}

	/*(3.0) (2) Constucts a query object with <assignQuery>*/
	PrimitivesGenerated(Queries& queries, GLuint index)
	{
		assignQuery(queries, index);
	}

	/*(3.0) Assigns an empty query object with the object name from the query multi-object
	@param The query multi-object
	@param The index of the object name*/
	void assignQuery(Queries& queries, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)queries, index, GL_PRIMITIVES_GENERATED);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)queries, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_PRIMITIVES_GENERATED);
	}

	/*(3.0) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_PRIMITIVES_GENERATED);
	}

	/*(3.0) Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_PRIMITIVES_GENERATED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.0) Determines via API if the query object is currently an active query
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery()
	{
		return _query_id() == (GLuint)_getQuery(GL_PRIMITIVES_GENERATED, GL_CURRENT_QUERY);
	}
}; // class PrimitivesGenerated : public _Query
#endif // #ifdef GL_VERSION_3_0
} // namespace gl
