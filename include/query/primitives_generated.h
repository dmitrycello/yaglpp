#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_PRIMITIVES_GENERATED_H
#define YAGLPP_PRIMITIVES_GENERATED_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL generated primitives query object class derived from <Queries>*/
class PrimitivesGenerated : public Queries
{
public:
	using Queries::Queries;
	/*(3.0) Delimits the starting boundary of a query object. The query object must be inactive*/
	void Begin()
	{
		object_bind(glBeginQuery, GL_PRIMITIVES_GENERATED);
	}

	/*(3.0) Delimits the ending boundary of a query object. The query object must be active*/
	static void End()
	{
		end_query(GL_PRIMITIVES_GENERATED);
	}

	/*(3.0)Generates OpenGL query object name in an empty query class object, and delimits the starting boundary of a query object in one function call*/
	void GenBegin()
	{
		object_gen_bind(glGenQueries, glBeginQuery, GL_PRIMITIVES_GENERATED);
	}

	/*(3.0) Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static PrimitivesGenerated GetCurrent()
	{
		return PrimitivesGenerated(get_query(GL_PRIMITIVES_GENERATED, GL_CURRENT_QUERY));
	}

	/*(3.0) Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei GetCounterBits()
	{
		get_query(GL_PRIMITIVES_GENERATED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.0) Determines if the query object is currently an active query. MSVC getter for <current> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean IsCurrent() const
	{
		return object_id() == get_query(GL_PRIMITIVES_GENERATED, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = IsCurrent)) GLboolean current;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class PrimitivesGenerated : public Queries
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_PRIMITIVES_GENERATED_H
