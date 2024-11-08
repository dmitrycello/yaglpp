#pragma once
#include <yaglpp/query/_query.h>
#ifdef YAGLPP_VERSION_3_3
namespace gl {
/*(3.3) OpenGL any passed samples occlusion query object class derived from <_Query>*/
class AnySamplesPassed : public _Query
{
private:
	AnySamplesPassed(GLint name) { _object_set(name); }

public:
	/*(3.3) (1) Constructs an empty query object*/
	AnySamplesPassed() {}

	/*(3.3) (2) Constructs a copy of query object*/
	AnySamplesPassed(const AnySamplesPassed& query)
	{
		_query_dup((_Object&)query);
	}

	/*(3.3) Starts conditional rendering using an occlusion query
	@param Specifies how function interprets the results of the occlusion query*/
	void beginConditionalRender(QueryConditionalRenderMode mode)
	{
		_beginConditionalRender(mode);
	}

	/*(3.3) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_ANY_SAMPLES_PASSED);
	}

	/*(3.3) Duplicates a query object. If the source is a single object, it unconditionally becomes a reference object
	@param Specifies the source query object*/
	void duplicateQuery(const AnySamplesPassed& query)
	{
		_query_dup((_Object&)query);
	}

	/*(3.3) End conditional rendering*/
	static void endConditionalRender()
	{
		gl::endConditionalRender();
	}

	/*(3.3) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_ANY_SAMPLES_PASSED);
	}

	/*(3.3) Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static AnySamplesPassed getCurrentQuery()
	{
		return AnySamplesPassed(_getQuery(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}

	/*(3.3) Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_ANY_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.3) Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery() const
	{
		return _isCurrentQuery(GL_ANY_SAMPLES_PASSED);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*(3.3) Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class AnySamplesPassed : public _Query

/*(3.3) Returns a reference AnySamplesPassed query object of currently active query
@return The reference AnySamplesPassed object, or empty object*/
inline AnySamplesPassed getAnySamplesPassedQuery()
{
	return AnySamplesPassed::getCurrentQuery();
}
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_3
