#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_QUERIES_H
#define YAGLPP_QUERIES_H

namespace gl {
/*OpenGL untyped query object class derived from <Objects>. Can be used as a temporary asset before its reference is casted to any valid query type*/
class Queries : public Objects
{
public:
	using Objects::Objects;
	enum class ConditionalRender : GLenum;
	/*Allocates an array of query objects of a given size, and generates their object names. Must be deallocated with <Queries::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static Queries* Alloc(GLsizei n)
	{
		return (Queries*)object_alloc(glGenQueries, n);
	}

	/*Deletes previously allocated array of query object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(Queries* queries)
	{
		object_dealloc(glDeleteQueries, (GLuint*)queries);
	}

	/*Deletes valid OpenGL query object name and sets the query class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteQueries);
	}

	/*Deletes previously generated OpenGL query object names in a static array or a user-defined structure of queries, namely query map, and sets its class objects in empty state. Allows to unset multiple queries of various types in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of query map returned by sizeof operator
	@param [in-out] Pointer to query map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* queryMap)
	{
		object_delete_map(glDeleteQueries, n, queryMap);
	}

	/*Generates OpenGL query object name in an empty query class object*/
	void Gen()
	{
		object_gen(glGenQueries);
	}

	/*Generates OpenGL query object names in a static array or a user-defined structure of queries, namely query map. Allows to set multiple queries of various types in one function call. All class objects are silently overwritten
	@param The size in bytes of query map returned by sizeof operator
	@param [out] Pointer to query map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* queryMap)
	{
		object_gen_map(glGenQueries, n, queryMap);
	}

	/*Returns the value of the query object's passed samples counter. The initial value is 0. MSVC getter for <result> property
	@return The query object's result*/
	GLint GetResult()
	{
		return get_query_object(GL_QUERY_RESULT);
	}

	/*Returns whether the passed samples counter is immediately available. MSVC getter for <resultAvailable> property
	@return False if a delay would occur waiting for the query result, true otherwise*/
	GLboolean GetResultAvailable()
	{
		return get_query_object(GL_QUERY_RESULT_AVAILABLE);
	}

	/*Determines if a valid OpenGL query object name corresponds to a query object. MSVC getter for <query> property
	@return True if active query object, false otherwise*/
	GLboolean IsQuery() const
	{
		return object_is(glIsQuery);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if active query object*/
	__declspec(property(get = IsQuery)) GLboolean query;

	/*Read-only property for value of the query object's passed samples counter*/
	__declspec(property(get = GetResult)) GLint result;

	/*Read-only property for boolean value whether the passed samples counter is immediately available*/
	__declspec(property(get = GetResultAvailable)) GLboolean resultAvailable;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) Returns the 8-byte value of the query object's passed samples counter. The initial value is 0. MSVC getter for <result64> property
	@return The query object's 64-bit result*/
	GLint64 GetResult64();
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*Read-only property for 8-byte value of the query object's passed samples counter*/
	__declspec(property(get = GetResult64)) GLint64 result64;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)

protected:
	static void end_query(GLenum target);
	GLint get_query_object(GLenum pname);
	static GLint get_query(GLenum target, GLenum pname)
	{
		GLint i; glGetQueryiv(target, pname, &i); return i;
	}

#ifdef YAGLPP_VERSION_3_0
	void begin_conditional_render(GLenum mode);

	//TODO move to gladpp
	static void end_conditional_render();
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_2
	void query_counter();
#endif // #ifdef YAGLPP_VERSION_3_2
}; // class Queries : public Object

#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD query conditional rendering mode enumerator*/
enum class Queries::ConditionalRender : GLenum
{
	/*(3.0) The GL waits for the results of the query to be available and then uses the results to determine if subsequent rendering commands are discarded*/
	Wait = GL_QUERY_WAIT,

	/*(3.0) The GL may choose to unconditionally execute the subsequent rendering commands without waiting for the query to complete*/
	NoWait = GL_QUERY_NO_WAIT,

	/*(3.0) The GL will also wait for occlusion query results and discard rendering commands if the result of the occlusion query is zero. If the query result is non-zero, subsequent rendering commands are executed, but the GL may discard the results of the commands for any region of the framebuffer that did not contribute to the sample count in the specified occlusion query. Any such discarding is done in an implementation-dependent manner, but the rendering command results may not be discarded for any samples that contributed to the occlusion query sample count*/
	ByRegionWait = GL_QUERY_BY_REGION_WAIT,

	/*(3.0) The GL operates as in <QUERY_BY_REGION_NO_WAIT>, but may choose to unconditionally execute the subsequent rendering commands without waiting for the query to complete*/
	ByRegionNoWait = GL_QUERY_BY_REGION_NO_WAIT,
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Queries::end_query(GLenum target)
{
	// OPENGL QUERY TARGET IS NOT ACTIVE
	YAGLPP_ASSERT(get_query(target, GL_CURRENT_QUERY) != 0);

	glEndQuery(target);
	YAGLPP_GLAD_ERROR;
}

GLint Queries::get_query_object(GLenum pname)
{
	GLint iResult;
	glGetQueryObjectiv(object_id(), pname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}
#endif // YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Queries::end_query(GLenum target)
{
	glEndQuery(target);
}

inline GLint Queries::get_query_object(GLenum pname)
{
	GLint i; glGetQueryObjectiv(object_id(), pname, &i); return i;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Queries::begin_conditional_render(GLenum mode)
{
	glBeginConditionalRender(object_id(), mode); // GL_SAMPLES_PASSED or GL_ANY_SAMPLES_PASSED only
	YAGLPP_GLAD_ERROR;
}

void Queries::end_conditional_render()
{
	glEndConditionalRender();
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Queries::begin_conditional_render(GLenum mode)
{
	glBeginConditionalRender(object_id(), mode);
}

inline void Queries::end_conditional_render()
{
	glEndConditionalRender();
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void Queries::query_counter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void Queries::query_counter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
GLint64 Queries::GetResult64()
{
	GLint64 iResult;
	glGetQueryObjecti64v(object_id(), GL_QUERY_RESULT, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline GLint64 Queries::GetResult64()
{
	GLint64 i; glGetQueryObjecti64v(object_id(), GL_QUERY_RESULT, &i); return i;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_QUERIES_H
