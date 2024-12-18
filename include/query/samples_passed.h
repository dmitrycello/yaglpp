#pragma once
#include <yaglpp/query/_query.h>
namespace gl {
/*OpenGL samples passed occlusion query object class derived from <_Query>*/
class SamplesPassed : public _Query
{
private:
	friend class Queries;
	SamplesPassed(GLint name) { _object_set(name); }

public:
	/*(1) Constructs an empty query object*/
	SamplesPassed() {}

	/*(2) Constructs a copy of query object*/
	SamplesPassed(const SamplesPassed& source)
	{
		_query_dup((_Object&)source);
	}

	/*Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_SAMPLES_PASSED);
	}

	/*Duplicates a query object, increasing its reference count. The reference source object is being copied
	@param Specifies the source query object*/
	void duplicateQuery(const SamplesPassed& source)
	{
		_query_dup((_Object&)source);
	}

	/*Delimits the ending boundary of an occlusion query object*/
	static void endQuery()
	{
		_endQuery(GL_SAMPLES_PASSED);
	}

	/*Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static SamplesPassed getCurrentQuery()
	{
		return SamplesPassed(_getQuery(GL_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}

	/*Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery() const
	{
		return _isCurrentQuery(GL_SAMPLES_PASSED);
	}

	/*Checks if the source query object is referencing the same OpenGL object
	@param Specifies the source query object
	@return True if duplicate object*/
	GLboolean isDuplicate(const SamplesPassed& source) const
	{
		return _object_is((_Object&)source);
	}

	/*Creates a thread-safe reference object from the source query object
	@param Specifies the source query object*/
	void referQuery(const SamplesPassed& source)
	{
		_query_refer((_Object&)source);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Start conditional rendering using an occlusion query
	@param Specifies how function interprets the results of the occlusion query*/
	void beginConditionalRender(QueryConditionalRenderMode mode)
	{
		_beginConditionalRender(mode);
	}

	/*(3.0) End conditional rendering*/
	static void endConditionalRender()
	{
		gl::endConditionalRender();
	}
#endif // #ifdef YAGLPP_VERSION_3_0
}; // class SamplesPassed : public _Query

/*(3.0) Returns a reference SamplesPassed query object of currently active query
@return The reference SamplesPassed object, or empty object*/
inline SamplesPassed getSamplesPassedQuery()
{
	return SamplesPassed::getCurrentQuery();
}
} // namespace gl
