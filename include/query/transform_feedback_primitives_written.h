#pragma once
#include <yaglpp/query/_query.h>
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL written primitives transform feedback query object class derived from <_Query>*/
class TransformFeedbackPrimitivesWritten : public _Query
{
public:
	/*(3.0) (1) Constructs an empty query object*/
	TransformFeedbackPrimitivesWritten() {}

	/*(3.0) (2) Constucts a query object with <assignQuery>*/
	TransformFeedbackPrimitivesWritten(Queries& queries, GLuint index)
	{
		assignQuery(queries, index);
	}

	/*(3.0) Assigns an empty query object with the object name from the query multi-object
	@param The query multi-object
	@param The index of the object name*/
	void assignQuery(Queries& queries, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)queries, index, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)queries, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	}

	/*(3.0) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	}

	/*(3.0) Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_QUERY_COUNTER_BITS);
	}

	/*(3.0) Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery()
	{
		return _object_id() == (GLuint)_getQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*(3.0) Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class TransformFeedbackPrimitivesWritten : public _Query
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
