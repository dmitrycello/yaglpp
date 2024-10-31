#pragma once
#include <yaglpp/glad/_object.h>
namespace gl {
#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD query conditional rendering mode enumerator*/
enum class QueryConditionalRenderMode : GLenum
{
	/*(3.0) The GL waits for the results of the query to be available and then uses the results to determine if subsequent rendering commands are discarded*/
	QueryWait = GL_QUERY_WAIT,

	/*(3.0) The GL may choose to unconditionally execute the subsequent rendering commands without waiting for the query to complete*/
	QueryNoWait = GL_QUERY_NO_WAIT,

	/*(3.0) The GL will also wait for occlusion query results and discard rendering commands if the result of the occlusion query is zero. If the query result is non-zero, subsequent rendering commands are executed, but the GL may discard the results of the commands for any region of the framebuffer that did not contribute to the sample count in the specified occlusion query. Any such discarding is done in an implementation-dependent manner, but the rendering command results may not be discarded for any samples that contributed to the occlusion query sample count*/
	QueryByRegionWait = GL_QUERY_BY_REGION_WAIT,

	/*(3.0) The GL operates as in <QueryByRegionWait>, but may choose to unconditionally execute the subsequent rendering commands without waiting for the query to complete*/
	QueryByRegionNoWait = GL_QUERY_BY_REGION_NO_WAIT,
};
#endif // #ifdef YAGLPP_VERSION_3_0

/*OpenGL query object abstract class derived from <_Object>*/
class _Query : public _Object
{
protected:
	void _query_delete() {
		_object_delete(glDeleteQueries);
	}
	void _query_dup(_Object& source) {
		_object_dup(glDeleteQueries, source);
	}
	void _query_gen() {
		_object_gen(glGenQueries, glDeleteQueries, 1);
	}
	GLuint _query_id() {
		return _object_id(glGenQueries, 1);
	}
	void _query_ref(_Object& source) {
		_object_ref(glDeleteQueries, source);
	}
	void _beginQuery(GLenum target);
	static void _endQuery(GLenum target);
	static GLint _getQuery(GLenum target, GLenum pname);
	GLint _getQueryObject(GLenum pname);
	GLboolean _isCurrentQuery(GLenum target) const;

#ifdef YAGLPP_VERSION_3_0
	void _beginConditionalRender(QueryConditionalRenderMode mode);
	static void _endConditionalRender();
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
	void _queryCounter();
#endif // #ifdef YAGLPP_VERSION_3_3

public:
	/*Cleans up the valid query object*/
	~_Query()
	{
		_query_delete();
	}

	/*Explicitly deletes previously generated single buffer object*/
	void deleteQuery()
	{
		_query_delete();
	}

	/*Explicitly generates single buffer object*/
	void genQuery()
	{
		_query_gen();
	}

	/*Returns the value of the query object's passed samples counter. Used as a getter of <queryResult> property
	@return The query object's result. The initial value is 0*/
	GLint getQueryResult()
	{
		return _getQueryObject(GL_QUERY_RESULT);
	}

	/*Returns whether the passed samples counter is immediately available. Used as a getter of <queryResultAvailable> property
	@return False if a delay would occur waiting for the query result, true otherwise*/
	GLboolean getQueryResultAvailable()
	{
		return _getQueryObject(GL_QUERY_RESULT_AVAILABLE);
	}

	/*Determines if a name corresponds to a query object. Used as a getter of <query> property
	@return True if active query object, false otherwise*/
	GLboolean isQuery() const
	{
		return glIsQuery(_object_id());
	}

	/*Sets the creation state of the query object, only if current state is opposite. Depending of the flag value, calls <genQuery> or <deleteQuery> functions. Used as a setter of <query> property
	@param True to generate query object name, false to delete query object*/
	void setQuery(GLboolean gen);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-write property for creation state of the query object*/
	__declspec(property(get = isQuery, put = setQuery)) GLboolean query;

	/*Read-only property for value of the query object's passed samples counter*/
	__declspec(property(get = getQueryResult)) GLint queryResult;

	/*Read-only property for boolean value whether the passed samples counter is immediately available*/
	__declspec(property(get = getQueryResultAvailable)) GLboolean queryResultAvailable;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Returns the 8-byte value of the query object's passed samples counter. Used as a getter of <queryResult64> property
	@return The query object's 64-bit result. The initial value is 0*/
	GLint64 getQueryResult64();
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*Read-only property for 8-byte value of the query object's passed samples counter*/
	__declspec(property(get = getQueryResult64)) GLint64 queryResult64;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
}; // class _Query : public _Object

/*OpenGL query multi-object class derived from <_Objects>*/
class Queries : public _Objects
{
protected:
	void _queries_delete() {
		_objects_delete(glDeleteQueries);
	}
	void _queries_dup(_Objects& source) {
		_objects_dup(glDeleteQueries, source);
	}
	void _queries_gen(GLsizei n) {
		_objects_gen(glGenQueries, glDeleteQueries, n);
	}

public:
	/*(1) Constructs an empty query multi-object*/
	Queries() {}

	/*(2) Constructs a copy of query multi-object*/
	Queries(const Queries& queries)
	{
		_queries_dup((_Objects&)queries);
	}

	/*(3) Constucts an initialized query multi-object*/
	Queries(GLsizei n)
	{
		_queries_gen(n);
	}

	/*Cleans up the valid query multi-object*/
	~Queries()
	{
		_queries_delete();
	}

	/*Deletes valid query multi-object*/
	void deleteQueries()
	{
		_queries_delete();
	}

	/*Duplicates a query multi-object increasing its reference count
	@param Specifies the source query multi-object*/
	void duplicateQueries(const Queries& queries)
	{
		_queries_dup((_Objects&)queries);
	}

	/*Generates one or more query object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genQueries(GLsizei n)
	{
		_queries_gen(n);
	}

	/*Retrieves a reference to the SamplesPassed object from a valid multi-object
	@param Specifies the object name index*/
	SamplesPassed& getSamplesPassed(GLuint index) const
	{
#ifdef _DEBUG
		return (SamplesPassed&)_objects_get(index, GL_SAMPLES_PASSED);
#else // #ifdef _DEBUG
		return (SamplesPassed&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*Checks if the source Queries object is referencing the same multi-object
	@param The source multi-object
	@return True if duplicate multi-object*/
	GLboolean isDuplicate(const Queries& source) const
	{
		return _objects_is((Queries&)source);
	}

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Retrieves a reference to the PrimitivesGenerated object from a valid multi-object
	@param Specifies the object name index*/
	PrimitivesGenerated& getPrimitivesGenerated(GLuint index) const
	{
#ifdef _DEBUG
		return (PrimitivesGenerated&)_objects_get(index, GL_PRIMITIVES_GENERATED);
#else // #ifdef _DEBUG
		return (PrimitivesGenerated&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Retrieves a reference to the TransformFeedbackPrimitivesWritten object from a valid multi-object
	@param Specifies the object name index*/
	TransformFeedbackPrimitivesWritten& getTransformFeedbackPrimitivesWritten(GLuint index) const
	{
#ifdef _DEBUG
		return (TransformFeedbackPrimitivesWritten&)_objects_get(index, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
#else // #ifdef _DEBUG
		return (TransformFeedbackPrimitivesWritten&)_objects_get(index);
#endif // #ifdef _DEBUG
	}
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Retrieves a reference to the AnySamplesPassed object from a valid multi-object
	@param Specifies the object name index*/
	AnySamplesPassed& getAnySamplesPassed(GLuint index) const
	{
#ifdef _DEBUG
		return (AnySamplesPassed&)_objects_get(index, GL_ANY_SAMPLES_PASSED);
#else // #ifdef _DEBUG
		return (AnySamplesPassed&)_objects_get(index);
#endif // #ifdef _DEBUG
	}

	/*(3.3) Retrieves a reference to the TimeElapsed object from a valid multi-object
	@param Specifies the object name index*/
	TimeElapsed& getTimeElapsed(GLuint index) const
	{
#ifdef _DEBUG
		return (TimeElapsed&)_objects_get(index, GL_TIME_ELAPSED);
#else // #ifdef _DEBUG
		return (TimeElapsed&)_objects_get(index);
#endif // #ifdef _DEBUG
	}
#endif // #ifdef YAGLPP_VERSION_3_3
}; // class Queries : public _Object

#ifdef YAGLPP_IMPLEMENTATION
GLboolean _Query::_isCurrentQuery(GLenum target) const
{
	GLuint uBound, uId = _object_id();
	glGetQueryiv(target, GL_CURRENT_QUERY, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	return (uBound > 0) && (uBound == uId);
}

void _Query::setQuery(GLboolean gen)
{
	if (gen == GL_FALSE)
	{
		_query_delete();
	}
	else if (!isObject())
	{
		_query_gen();
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void _Query::_beginQuery(GLenum target)
{
	YAGLPP_ASSERT(_getQuery(target, GL_CURRENT_QUERY) == 0); // OPENGL QUERY TARGET IS ACTIVE
	glBeginQuery(target, _query_id());
	YAGLPP_GLAD_ERROR;
}

void _Query::_endQuery(GLenum target)
{
	YAGLPP_ASSERT(_getQuery(target, GL_CURRENT_QUERY) != 0); // OPENGL QUERY TARGET IS NOT ACTIVE
	glEndQuery(target);
	YAGLPP_GLAD_ERROR;
}

GLint _Query::_getQuery(GLenum target, GLenum pname)
{
	GLint iData;
	glGetQueryiv(target, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

GLint _Query::_getQueryObject(GLenum pname)
{
	GLint iData;
	glGetQueryObjectiv(_query_id(), pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void _Query::_beginQuery(GLenum target)
{
	glBeginQuery(target, _query_id());
}

inline void _Query::_endQuery(GLenum target)
{
	glEndQuery(target);
}

inline GLint _Query::_getQuery(GLenum target, GLenum pname)
{
	GLint i; glGetQueryiv(target, pname, &i); return i;
}

inline GLint _Query::_getQueryObject(GLenum pname)
{
	GLint i; glGetQueryObjectiv(_query_id(), pname, &i); return i;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void _Query::_endConditionalRender()
{
	glEndConditionalRender();
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
}

inline void _Query::_endConditionalRender()
{
	glEndConditionalRender();
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
GLint64 _Query::getQueryResult64()
{
	GLint64 iData;
	glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline GLint64 _Query::getQueryResult64()
{
	GLint64 i; glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &i); return i;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl

#include <yaglpp/query/any_samples_passed.h>
#include <yaglpp/query/primitives_generated.h>
#include <yaglpp/query/samples_passed.h>
#include <yaglpp/query/time_elapsed.h>
#include <yaglpp/query/transform_feedback_primitives_written.h>
