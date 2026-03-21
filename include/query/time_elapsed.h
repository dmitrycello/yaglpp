#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_TIME_ELAPSED_H
#define YAGLPP_TIME_ELAPSED_H

#ifdef YAGLPP_VERSION_3_3
namespace gl {
/*(3.3) OpenGL elapsed time query object class derived from <Queries>*/
class TimeElapsed : public Queries
{
public:
	using Queries::Queries;
	/*(3.3) Delimits the starting boundary of a query object. The query object must be inactive*/
	void Begin()
	{
		object_bind(glBeginQuery, GL_TIME_ELAPSED);
	}

	/*(3.3) Delimits the ending boundary of a query object. The query object must be active*/
	static void End()
	{
		end_query(GL_TIME_ELAPSED);
	}

	/*(3.3) Generates OpenGL query object name in an empty query class object, and delimits the starting boundary of a query object in one function call*/
	void GenBegin()
	{
		object_gen_bind(glGenQueries, glBeginQuery, GL_PRIMITIVES_GENERATED);
	}

	/*(3.3) Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static TimeElapsed GetCurrent()
	{
		return TimeElapsed(get_query(GL_TIME_ELAPSED, GL_CURRENT_QUERY));
	}

	/*(3.3) Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei GetCounterBits()
	{
		get_query(GL_TIME_ELAPSED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.3) Determines if the query object is currently an active query. MSVC getter for <current> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean IsCurrent() const
	{
		return object_id() == get_query(GL_TIME_ELAPSED, GL_CURRENT_QUERY);
	}

	/*(3.3) Records the GL time into an elapsed time query object after all previous commands have reached the GL server, but have not yet necessarily executed*/
	void queryCounter();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = IsCurrent)) GLboolean current;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class TimeElapsed : public Queries

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void TimeElapsed::queryCounter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void TimeElapsed::queryCounter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_3
#endif // #ifndef YAGLPP_TIME_ELAPSED_H
