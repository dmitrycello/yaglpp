#pragma once
#include "_Query.h"
namespace gl {
/*OpenGL samples passed query object class derived from <_Query>*/
class SamplesPassed : public _Query
{
public:
	/*(3.3) (1) Constructs an empty query object*/
	SamplesPassed() {}

	/*(3.3) (2) Constucts a query object with <assignQuery>*/
	SamplesPassed(Queries& queries, GLuint index)
	{
		assignQuery(queries, index);
	}

	/*(3.3) Assigns an empty query object with the object name from the query multi-object
	@param The query multi-object
	@param The index of the object name*/
	void assignQuery(Queries& queries, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)queries, index, GL_SAMPLES_PASSED);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)queries, index);
#endif // #ifdef _DEBUG
	}

	/*Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_SAMPLES_PASSED);
	}

	/*Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_SAMPLES_PASSED);
	}

	/*Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery()
	{
		return _object_id() == (GLuint)_getQuery(GL_SAMPLES_PASSED, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_0
	/*(3.0) Start conditional rendering
	@param Specifies how function interprets the results of the occlusion query*/
	void beginConditionalRender(QueryConditionalRenderMode mode)
	{
		_beginConditionalRender(mode);
	}

	/*(3.0) End conditional rendering*/
	static void endConditionalRender()
	{
		_endConditionalRender();
	}
#endif // #ifdef GL_VERSION_3_0
}; // class SamplesPassed : public _Query
} // namespace gl
