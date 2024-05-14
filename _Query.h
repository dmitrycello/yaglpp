#pragma once
#include "gladpp.h"
#include "_Object.h"
namespace gl {
#ifdef GL_VERSION_3_0
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
#endif // #ifdef GL_VERSION_3_0

/*OpenGL query object abstract class derived from <_Object>*/
class _Query : public _Object
{
protected:
	_Query() : _Object() {}

	GLuint _query_id()
	{
		return _object_id(glGenQueries);
	}

	void _beginQuery(GLenum target);
	static void _endQuery(GLenum target);
	static GLint _getQuery(GLenum target, GLenum pname);
	GLint _getQueryObject(GLenum pname);

#ifdef GL_VERSION_3_0
	void _beginConditionalRender(QueryConditionalRenderMode mode);
	static void _endConditionalRender();
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
	void _queryCounter();
#endif // #ifdef GL_VERSION_3_3

public:
	/*Cleans up the valid query object*/
	~_Query()
	{
		if (isObject())
		{
			deleteQuery();
		}
	}

	/*Explicitly deletes previously generated single buffer object*/
	void deleteQuery()
	{
		_object_delete(glDeleteQueries);
	}

	/*Explicitly generates single buffer object*/
	void genQuery()
	{
		_object_gen(glGenQueries);
	}

	/*Returns the value of the query object's passed samples counter
	@return The query object's result. The initial value is 0*/
	GLint getQueryResult()
	{
		return _getQueryObject(GL_QUERY_RESULT);
	}

	/*Returns whether the passed samples counter is immediately available
	@return False if a delay would occur waiting for the query result, true otherwise*/
	GLboolean getQueryResultAvailable()
	{
		return _getQueryObject(GL_QUERY_RESULT_AVAILABLE);
	}

	/*Checks if valid OpenGL query object
	@return True if valid query object, false otherwise*/
	GLboolean isQuery()
	{
		return glIsQuery(_object_id());
	}

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the 8-byte value of the query object's passed samples counter
	@return The query object's 64-bit result. The initial value is 0*/
	GLint64 getQueryResult64();
#endif // #ifdef GL_VERSION_3_3
}; // class _Query : public _Object

#ifndef _DEBUG
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

#ifdef GL_VERSION_3_0
inline void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
}

inline void _Query::_endConditionalRender()
{
	glEndConditionalRender();
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
inline void _Query::_queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
}

inline GLint64 _Query::getQueryResult64()
{
	GLint64 i; glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &i); return i;
}
#endif // #ifdef GL_VERSION_3_3
#endif // #ifndef _DEBUG
} // namespace gl

#ifndef YAGLPP_BUILD_LIB
#include "AnySamplesPassed.h"
#include "PrimitivesGenerated.h"
#include "SamplesPassed.h"
#include "TimeElapsed.h"
#include "TransformFeedbackPrimitivesWritten.h"
#endif // #ifdef YAGLPP_BUILD
