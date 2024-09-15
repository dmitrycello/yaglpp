#pragma once
#include <yaglpp/glad/_object.h>
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
	void _beginQuery(GLenum target);
	static void _endQuery(GLenum target);
	static GLint _getQuery(GLenum target, GLenum pname);
	GLint _getQueryObject(GLenum pname);
	GLuint _query_id()
	{
		return _object_id(glGenQueries);
	}

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
	GLboolean isQuery()
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

#ifdef GL_VERSION_3_3
	/*(3.3) Returns the 8-byte value of the query object's passed samples counter. Used as a getter of <queryResult64> property
	@return The query object's 64-bit result. The initial value is 0*/
	GLint64 getQueryResult64();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for 8-byte value of the query object's passed samples counter*/
	__declspec(property(get = getQueryResult64)) GLint64 queryResult64;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef GL_VERSION_3_3
}; // class _Query : public _Object

#ifdef YAGLPP_IMPLEMENTATION
void _Query::setQuery(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			deleteQuery();
		}
	}
	else if (gen == GL_TRUE)
	{
		genQuery();
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

#if defined (GL_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
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
#endif // #if defined (GL_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (GL_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
}

inline void _Query::_endConditionalRender()
{
	glEndConditionalRender();
}
#endif // #if defined (GL_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (GL_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void _Query::_queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}

GLint64 _Query::getQueryResult64()
{
	GLint64 iData;
	glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #if defined (GL_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (GL_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void _Query::_queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
}

inline GLint64 _Query::getQueryResult64()
{
	GLint64 i; glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &i); return i;
}
#endif // #if defined (GL_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl

#include <yaglpp/query/any_samples_passed.h>
#include <yaglpp/query/primitives_generated.h>
#include <yaglpp/query/samples_passed.h>
#include <yaglpp/query/time_elapsed.h>
#include <yaglpp/query/transform_feedback_primitives_written.h>
