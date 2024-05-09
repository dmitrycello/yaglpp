#pragma once
#include "gladpp.h"
#include "_Query.h"
#ifdef GL_VERSION_3_3
namespace gl {
/*(3.3) OpenGL any passed samples query object class derived from <_Query>*/
class AnySamplesPassed : public _Query
{
public:
	/*(3.3) (1) Constructs an empty query object*/
	AnySamplesPassed() : _Query() {}

	/*(3.3) (2) Constucts a query object with <assignQuery>*/
	AnySamplesPassed(Queries& queries, GLuint index)
	{
		assignQuery(queries, index);
	}

	/*(3.3) Assigns an empty query object with the object name from the query multi-object
	@param The query multi-object
	@param The index of the object name*/
	void assignQuery(Queries& queries, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)queries, index, GL_ANY_SAMPLES_PASSED);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)queries, index);
#endif // #ifdef _DEBUG
	}

	/*(3.3) Starts conditional rendering
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

	/*(3.3) End conditional rendering*/
	static void endConditionalRender()
	{
		_endConditionalRender();
	}

	/*(3.3) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_ANY_SAMPLES_PASSED);
	}

	/*(3.3) Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_ANY_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.3) Determines via API if the query object is currently an active query
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery()
	{
		return _object_id() == (GLuint)_getQuery(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY);
	}
}; // class AnySamplesPassed : public _Query
} // namespace gl
#endif // #ifdef GL_VERSION_3_3
