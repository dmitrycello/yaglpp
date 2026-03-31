#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_QUERIES_T_H
#define YAGLPP_QUERIES_T_H

namespace gl {
template <GLenum T> class Queries_1 : public Queries
{
public:
	using Queries::Queries;
	/*Delimits the starting boundary of a query object. The query object must be inactive*/
	void Begin()
	{
		Objects::object_bind(glBeginQuery, T);
	}

	/*Delimits the ending boundary of an occlusion query object. The query object must be active*/
	static void End()
	{
		Queries::end_query(T);
	}

	/*Generates OpenGL query object name in an empty query class object, and delimits the starting boundary of a query object in one function call*/
	void GenBegin()
	{
		Objects::object_gen_bind(glGenQueries, glBeginQuery, T);
	}

	/*Gets the API implementation-dependent number of bits used to hold the result for query's target. MSVC getter for <counterBits> property
	@return The result bit number for query's target*/
	static GLint GetCounterBits()
	{
		Queries::get_query(T, GL_QUERY_COUNTER_BITS);
	}

	/*Determines if the query object is currently an active query. MSVC getter for <current> property
	@return True if the query object is currently active query, false otherwise*/
	GLboolean IsCurrent() const
	{
		return Objects::object_id() == Queries::get_query(T, GL_CURRENT_QUERY);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to determine number of bits used to hold query result*/
	__declspec(property(get = GetCounterBits)) GLint counterBits;

	/*Read-only property to determine if the query object is currently an active query*/
	__declspec(property(get = IsCurrent)) GLboolean current;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // template <GLenum T> class Queries_1 : public Queries

template <GLenum T> class Queries_2 : public Queries_1<T>
{
public:
	using Queries_1<T>::Queries_1;

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Start conditional rendering using an occlusion query
	@param Specifies how function interprets the results of the occlusion query*/
	void BeginConditionalRender(Queries::ConditionalRender mode)
	{
		Queries::begin_conditional_render((GLenum)mode);
	}
#endif // #ifdef YAGLPP_VERSION_3_0
}; // template <GLenum T> class Queries_2 : public Queries_1<T>

typedef Queries_1<GL_SAMPLES_PASSED> SamplesPassed_1;
typedef Queries_2<GL_SAMPLES_PASSED> SamplesPassed_2;
/*OpenGL samples passed occlusion query object class derived from <Queries>*/
class SamplesPassed : public SamplesPassed_2
{
public:
	using Queries_2::Queries_2;
	/*Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static SamplesPassed GetCurrent()
	{
		return SamplesPassed(get_query(GL_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}
};

#ifdef YAGLPP_VERSION_3_0
typedef Queries_1<GL_PRIMITIVES_GENERATED> PrimitivesGenerated_1;
/*(3.0) OpenGL generated primitives query object class derived from <Queries>*/
class PrimitivesGenerated : public PrimitivesGenerated_1
{
public:
	using Queries_1::Queries_1;
	/*(3.0) Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static PrimitivesGenerated GetCurrent()
	{
		return PrimitivesGenerated(get_query(GL_PRIMITIVES_GENERATED, GL_CURRENT_QUERY));
	}
};

typedef Queries_1<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN> TransformFeedbackPrimitivesWritten_1;
/*(3.0) OpenGL written primitives transform feedback query object class derived from <Queries>*/
class TransformFeedbackPrimitivesWritten : public TransformFeedbackPrimitivesWritten_1
{
public:
	using Queries_1::Queries_1;
	/*(3.0) Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static TransformFeedbackPrimitivesWritten GetCurrent()
	{
		return TransformFeedbackPrimitivesWritten(get_query(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_CURRENT_QUERY));
	}
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
typedef Queries_1<GL_ANY_SAMPLES_PASSED> AnySamplesPassed_1;
typedef Queries_2<GL_ANY_SAMPLES_PASSED> AnySamplesPassed_2;
/*(3.3) OpenGL any passed samples occlusion query object class derived from <Queries>*/
class AnySamplesPassed : public AnySamplesPassed_2
{
public:
	using Queries_2::Queries_2;
	/*(3.3) Returns the currently active query object associated with particular target
	@return The active query object, or empty object*/
	static AnySamplesPassed GetCurrent()
	{
		return AnySamplesPassed(get_query(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY));
	}
};

typedef Queries_1<GL_ANY_SAMPLES_PASSED> TimeElapsed_1;
/*(3.3) OpenGL elapsed time query object class derived from <Queries>*/
class TimeElapsed : public TimeElapsed_1
{
public:
	using Queries_1::Queries_1;
	/*(3.3) Returns a reference query object of currently active query
	@return The reference query object, or empty object*/
	static TimeElapsed GetCurrent()
	{
		return TimeElapsed(get_query(GL_TIME_ELAPSED, GL_CURRENT_QUERY));
	}

	/*(3.3) Records the GL time into an elapsed time query object after all previous commands have reached the GL server, but have not yet necessarily executed*/
	void queryCounter();
};
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void TimeElapsed::queryCounter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void TimeElapsed::queryCounter()
{
	glQueryCounter(object_id(), GL_TIMESTAMP);
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_QUERIES_T_H
