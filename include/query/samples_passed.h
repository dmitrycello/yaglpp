#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_SAMPLES_PASSED_H
#define YAGLPP_SAMPLES_PASSED_H

namespace gl {
/*OpenGL samples passed occlusion query object class derived from <Queries>*/
class SamplesPassed : public Queries
{
public:
	using Queries::Queries;
	/*Delimits the starting boundary of a query object. The query object must be inactive*/
	void Begin()
	{
		object_bind(glBeginQuery, GL_SAMPLES_PASSED);
	}

	/*Delimits the ending boundary of an occlusion query object. The query object must be active*/
	static void End()
	{
		end_query(GL_SAMPLES_PASSED);
	}

	/*Generates OpenGL query object name in an empty query class object, and delimits the starting boundary of a query object in one function call*/
	void GenBegin()
	{
		object_gen_bind(glGenQueries, glBeginQuery, GL_PRIMITIVES_GENERATED);
	}

	/*Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static SamplesPassed GetCurrent()
	{
		return SamplesPassed(get_query(GL_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}

	/*Gets the API implementation-dependent number of bits used to hold the result for query's target
	@return The result bit number for query's target*/
	static GLsizei GetCounterBits()
	{
		get_query(GL_SAMPLES_PASSED, GL_QUERY_COUNTER_BITS);
	}

	/*Determines if the query object is currently an active query. MSVC getter for <current> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean IsCurrent() const
	{
		return object_id() == get_query(GL_SAMPLES_PASSED, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = IsCurrent)) GLboolean current;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Start conditional rendering using an occlusion query
	@param Specifies how function interprets the results of the occlusion query*/
	void beginConditionalRender(ConditionalRender mode)
	{
		begin_conditional_render((GLenum)mode);
	}

	/*(3.0) End conditional rendering started using occlusion query object*/
	static void endConditionalRender()
	{
		end_conditional_render();
	}
#endif // #ifdef YAGLPP_VERSION_3_0
}; // class SamplesPassed : public Queries
} // namespace gl
#endif // #ifndef YAGLPP_SAMPLES_PASSED_H
