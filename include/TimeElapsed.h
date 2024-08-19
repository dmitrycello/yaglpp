#pragma once
#include "gladpp.h"
#include "_Query.h"
namespace gl {
#ifdef GL_VERSION_3_3
/*(3.3) OpenGL elapsed time query object class derived from <_Query>*/
class TimeElapsed : public _Query
{
public:
	/*(3.3) (1) Constructs an empty query object*/
	TimeElapsed() {}

	/*(3.3) (2) Constucts a query object with <assignQuery>*/
	TimeElapsed(Queries& queries, GLuint index)
	{
		assignQuery(queries, index);
	}

	/*(3.3) Assigns an empty query object with the object name from the query multi-object
	@param The query multi-object
	@param The index of the object name*/
	void assignQuery(Queries& queries, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)queries, index, GL_TIME_ELAPSED);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)queries, index);
#endif // #ifdef _DEBUG
	}

	/*(3.3) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_TIME_ELAPSED);
	}

	/*(3.3) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_TIME_ELAPSED);
	}

	/*(3.3) Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_TIME_ELAPSED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.3) Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery()
	{
		return _object_id() == (GLuint)_getQuery(GL_TIME_ELAPSED, GL_CURRENT_QUERY);
	}

	/*(3.3) Records the GL time into an elapsed time query object after all previous commands have reached the GL server, but have not yet necessarily executed*/
	void queryCounter()
	{
		_queryCounter();
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*(3.3) Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class TimeElapsed : public _Query
#endif // #ifdef GL_VERSION_3_3
} // namespace gl
