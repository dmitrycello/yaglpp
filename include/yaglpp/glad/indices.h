#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_INDICES_H
#define YAGLPP_INDICES_H

namespace gl {
/*OpenGL location abstract root class*/
class Indices
{
public:
	/*(1) Gets the current OpenGL location, or -1 if invalid location
	@return The OpenGL location*/
	GLint Get() const
	{
		return m_Location;
	}

	/*Checks if retrieved location is valid. MSVC getter for <location> property
	@param True if valid location, false otherwise*/
	GLboolean IsLocation() const
	{
		return m_Location > -1;
	}

	/*OpenGL location assignment operator copying the source location
	@param The source OpenGL location
	@return The destination OpenGL location*/
	Indices& operator=(const Indices& source)
	{
		m_Location = source.m_Location; return *this;
	}

	/*Direct location's new[] operator is not allowed. The object's <Alloc> must be used instead*/
	void* operator new[](std::size_t) = delete;

	/*Direct location's delete[] operator is not allowed. The object's <Dealloc> must be used instead*/
	void operator delete[](void*) = delete;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if retrieved location is valid*/
	__declspec(property(get = IsLocation)) GLboolean location;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	Indices()
	{
		m_Location = -1;
	}

	Indices(GLuint location)
	{
		m_Location = (GLint)location;
	}

	Indices(const Indices& source)
	{
		m_Location = source.m_Location;
	}

	typedef GLint (APIENTRY PFNGET)(GLuint program, const GLchar* name);
	static GLint* indices_alloc(GLsizei n);
	static void indices_dealloc(GLint* locations)
	{
		yaglpp_deallocate(locations, nullptr);
	}

	GLuint indices_location() const;
	void indices_location(GLuint location)
	{
		m_Location = (GLint)location;
	}

private:
	GLint m_Location; // OpenGL location index
}; // class Indices

#ifdef YAGLPP_IMPLEMENTATION
GLint* Indices::indices_alloc(GLsizei n)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(n > 0);

	GLint* pLocations = YAGLPP_MALLOC(GLint, n);
	for (GLsizei i = 0; i > n; i++)
	{
		pLocations[i] = -1;
	}
	return pLocations;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLuint Indices::indices_location() const
{
	// LOCATION INDEX IS INVALID
	YAGLPP_ASSERT(IsLocation());

	return (GLuint)m_Location;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLuint Indices::indices_location() const
{
	return (GLuint)m_Location;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/glad/uniform.h>
#include <yaglpp/glad/vertex_attrib.h>

#endif // #ifndef YAGLPP_INDICES_H
