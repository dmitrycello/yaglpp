#pragma once
#include <yaglpp/query/_query.h>
#ifdef YAGLPP_VERSION_3_3
namespace gl {
/*(3.3) OpenGL elapsed time query object class derived from <_Query>*/
class TimeElapsed : public _Query
{
private:
	TimeElapsed(GLint name) { _object_set(name); }

public:
	/*(3.3) (1) Constructs an empty query object*/
	TimeElapsed() {}

	/*(3.3) (2) Constructs a copy of query object*/
	TimeElapsed(const TimeElapsed& query)
	{
		_query_dup((_Object&)query);
	}

	/*(3.3) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_TIME_ELAPSED);
	}

	/*(3.3) Duplicates a query object. If the source is a single object, it unconditionally becomes a reference object
	@param Specifies the source query object*/
	void duplicateQuery(const TimeElapsed& query)
	{
		_query_dup((_Object&)query);
	}

	/*(3.3) Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static TimeElapsed getCurrentQuery()
	{
		return TimeElapsed(_getQuery(GL_TIME_ELAPSED, GL_CURRENT_QUERY));
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
	GLboolean isCurrentQuery() const
	{
		return _isCurrentQuery(GL_TIME_ELAPSED);
	}

	/*(3.3) Records the GL time into an elapsed time query object after all previous commands have reached the GL server, but have not yet necessarily executed*/
	void queryCounter();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*(3.3) Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class TimeElapsed : public _Query

/*(3.3) Returns a reference TimeElapsed query object of currently active query
@return The reference TimeElapsed object, or empty object*/
inline TimeElapsed getTimeElapsedQuery()
{
	return TimeElapsed::getCurrentQuery();
}

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void TimeElapsed::queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void TimeElapsed::queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_3
