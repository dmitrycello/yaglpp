#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_ANY_SAMPLES_PASSED_H
#define YAGLPP_ANY_SAMPLES_PASSED_H

#ifdef YAGLPP_VERSION_3_3
namespace gl {
/*(3.3) OpenGL any passed samples occlusion query object class derived from <Queries>*/
class AnySamplesPassed : public Queries
{
public:
	using Queries::Queries;
	/*(3.3) Starts conditional rendering using an occlusion query
	@param Specifies how function interprets the results of the occlusion query*/
	void beginConditionalRender(ConditionalRender mode)
	{
		begin_conditional_render((GLenum)mode);
	}

	/*(3.3) Delimits the starting boundary of a query object*/
	void Begin()
	{
		object_bind(glBeginQuery, GL_ANY_SAMPLES_PASSED);
	}

	/*(3.0) End conditional rendering started using occlusion query object*/
	static void endConditionalRender()
	{
		end_conditional_render();
	}

	/*(3.3) Delimits the ending boundary of a query object*/
	static void End()
	{
		end_query(GL_ANY_SAMPLES_PASSED);
	}

	/*(3.3) Generates OpenGL query object name in an empty query class object, and delimits the starting boundary of a query object in one function call*/
	void GenBegin()
	{
		object_gen_bind(glGenQueries, glBeginQuery, GL_PRIMITIVES_GENERATED);
	}

	/*(3.3) Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static AnySamplesPassed GetCurrent()
	{
		return AnySamplesPassed(get_query(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}

	/*(3.3) Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei GetCounterBits()
	{
		get_query(GL_ANY_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*(3.3) Determines if the query object is currently an active query. MSVC getter for <current> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean IsCurrent() const
	{
		return object_id() == get_query(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.3) Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = IsCurrent)) GLboolean current;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class AnySamplesPassed : public Queries
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_3
#endif // #ifndef YAGLPP_ANY_SAMPLES_PASSED_H
