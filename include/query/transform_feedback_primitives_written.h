#pragma once
#include <yaglpp/query/_query.h>
#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL written primitives transform feedback query object class derived from <_Query>*/
class TransformFeedbackPrimitivesWritten : public _Query
{
private:
	friend class Queries;
	TransformFeedbackPrimitivesWritten(GLint name) { _object_set(name); }

public:
	/*(3.0) (1) Constructs an empty query object*/
	TransformFeedbackPrimitivesWritten() {}

	/*(3.0) (2) Constructs a copy of query object*/
	TransformFeedbackPrimitivesWritten(const TransformFeedbackPrimitivesWritten& source)
	{
		_query_dup((_Object&)source);
	}

	/*(3.0) Delimits the starting boundary of a query object*/
	void beginQuery()
	{
		_beginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	}

	/*(3.0) Duplicates a query object, increasing its reference count. The reference source object is being copied
	@param Specifies the source query object*/
	void duplicateQuery(const TransformFeedbackPrimitivesWritten& source)
	{
		_query_dup((_Object&)source);
	}

	/*(3.0) Delimits the ending boundary of a query object*/
	static void endQuery()
	{
		_endQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	}

	/*(3.0) Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static TransformFeedbackPrimitivesWritten getCurrentQuery()
	{
		return TransformFeedbackPrimitivesWritten(_getQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_CURRENT_QUERY));
	}

	/*(3.0) Gets the API implementation-dependent number of bits used to hold the result for query's target. Used as a getter of <queryCounterBits> property
	@return The result bit number for query's target*/
	static GLsizei getQueryCounterBits()
	{
		_getQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_QUERY_COUNTER_BITS);
	}

	/*(3.0) Determines if the query object is currently an active query. Used as a getter of <currentQuery> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean isCurrentQuery() const
	{
		return _isCurrentQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	}

	/*(3.0) Checks if the source query object is referencing the same OpenGL object
	@param Specifies the source query object
	@return True if duplicate object*/
	GLboolean isDuplicate(const TransformFeedbackPrimitivesWritten& source) const
	{
		return _object_is((_Object&)source);
	}

	/*(3.0) reates a thread-safe reference object from the source query object
	@param Specifies the source query object*/
	void referQuery(const TransformFeedbackPrimitivesWritten& source)
	{
		_query_refer((_Object&)source);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = isCurrentQuery)) GLboolean currentQuery;

	/*(3.0) Read-only property for implementation-dependent number of bits used to hold the result for query's target*/
	__declspec(property(get = getQueryCounterBits)) GLsizei queryCounterBits;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class TransformFeedbackPrimitivesWritten : public _Query

/*(3.0) Returns a reference TransformFeedbackPrimitivesWritten query object of currently active query
@return The reference TransformFeedbackPrimitivesWritten object, or empty object*/
inline TransformFeedbackPrimitivesWritten getTransformFeedbackPrimitivesWrittenQuery()
{
	return TransformFeedbackPrimitivesWritten::getCurrentQuery();
}
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
