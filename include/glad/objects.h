#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_OBJECTS_H
#define YAGLPP_OBJECTS_H

namespace gl {
/*OpenGL object abstract root class*/
class Objects
{
public:
	/*Gets the current OpenGL object's id, or zero if empty object
	@return The OpenGL object name*/
	GLuint Get() const
	{
		return m_Object;
	}

	/*Checks if valid OpenGL object. MSVC getter for <object> property
	@return True if not an empty OpenGL object, false otherwise*/
	GLboolean IsObject() const
	{
		return m_Object > 0;
	}

	/*OpenGL object assignment operator copying the object id
	@param The source OpenGL object
	@return The destination OpenGL object*/
	Objects& operator=(const Objects& source)
	{
		m_Object = source.m_Object; return *this;
	}

	/*Using the object's new operator is not allowed. The object's <Alloc> should be used instead*/
	void* operator new(std::size_t) = delete;

	/*Using the object's new[] operator is not allowed. The object's <Alloc> should be used instead*/
	void* operator new[](std::size_t) = delete;

	/*Using the object's delete operator is not allowed. The object's <Dealloc> should be used instead*/
	void operator delete(void*) = delete;

	/*Using the object's delete[] operator is not allowed. The object's <Dealloc> should be used instead*/
	void operator delete[](void*) = delete;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if valid OpenGL object*/
	__declspec(property(get = IsObject)) GLboolean object;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	Objects()
	{
		m_Object = 0;
	}

	Objects(GLint id)
	{
		m_Object = (GLuint)id;
	}

	Objects(const Objects& source)
	{
		m_Object = source.m_Object;
	}

	typedef void (APIENTRY PFNBIND)(GLenum target, GLuint id);
	typedef void (APIENTRY PFNDELETE)(GLsizei n, const GLuint* ids);
	typedef void (APIENTRY PFNGEN)(GLsizei n, GLuint* ids);
	typedef GLboolean(APIENTRY PFNIS)(GLuint id);
	static GLuint* object_alloc(PFNGEN pfnGen, GLsizei n);
	void object_bind(PFNBIND pfnBind, GLenum target);
	static GLboolean object_binding(GLenum binding, GLuint name);
	static void object_dealloc(PFNDELETE pfnDelete, GLuint* objects);
	void object_delete(PFNDELETE pfnDelete);
	static void object_delete_map(PFNDELETE pfnDelete, GLsizei n, void* map);
	void object_gen(PFNGEN pfnGen);
	void object_gen_bind(PFNGEN pfnGen, PFNBIND pfnBind, GLenum target);
	static void object_gen_map(PFNGEN pfnGen, GLsizei n, void* map);
	GLuint object_id() const;
	GLboolean object_is(PFNIS pfnIs) const;

private:
	GLuint m_Object; // OpenGL object id
}; // class Objects

#ifdef YAGLPP_IMPLEMENTATION
GLuint* Objects::object_alloc(PFNGEN pfnGen, GLsizei n)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(n > 0);

	GLuint* pObjects = (GLuint*)yaglpp_allocate(n * sizeof(GLuint), (void*)sizeof(GLuint));
	*(pObjects - 1) = (GLuint)n; // store size
	pfnGen(n, pObjects);
	YAGLPP_GLAD_ERROR;
	return pObjects;
}

void Objects::object_dealloc(PFNDELETE pfnDelete, GLuint* objects)
{
	GLsizei n = *(objects - 1); // load size
	pfnDelete(n, objects);
	YAGLPP_GLAD_ERROR;
	yaglpp_deallocate(objects, (void*)sizeof(GLuint));
}

void Objects::object_delete_map(PFNDELETE pfnDelete, GLsizei bytes, void* objects)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(bytes > 0);

	pfnDelete(bytes / sizeof(GLuint), (GLuint*)objects);
	YAGLPP_GLAD_ERROR;
	std::memset(objects, 0, bytes);
}

void Objects::object_gen_bind(PFNGEN pfnGen, PFNBIND pfnBind, GLenum target)
{
	// OPENGL OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(m_Object == 0);

	pfnGen(1, &m_Object);
	pfnBind(target, m_Object);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Objects::object_bind(PFNBIND pfnBind, GLenum target)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Object != 0);

	pfnBind(target, m_Object);
	YAGLPP_GLAD_ERROR;
}

GLboolean Objects::object_binding(GLenum binding, GLuint name)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(name != 0);

	GLint iResult;
	glGetIntegerv(binding, &iResult);
	YAGLPP_GLAD_ERROR;
	return name == (GLuint)iResult;
}

void Objects::object_delete(PFNDELETE pfnDelete)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Object != 0);

	pfnDelete(1, &m_Object);
	YAGLPP_GLAD_ERROR;
	m_Object = 0;
}

void Objects::object_gen(PFNGEN pfnGen)
{
	// OPENGL OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(m_Object == 0);

	pfnGen(1, &m_Object);
	YAGLPP_GLAD_ERROR;
}

void Objects::object_gen_map(PFNGEN pfnGen, GLsizei bytes, void* map)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(bytes > 0);

	pfnGen(bytes / sizeof(GLuint), (GLuint*)map);
	YAGLPP_GLAD_ERROR;
}

GLuint Objects::object_id() const
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Object != 0);

	return m_Object;
}

GLboolean Objects::object_is(PFNIS pfnIs) const
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Object != 0);

	GLboolean bResult = pfnIs(m_Object);
	YAGLPP_GLAD_ERROR;
	return bResult;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Objects::object_bind(PFNBIND pfnBind, GLenum target)
{
	pfnBind(target, m_Object);
}

inline GLboolean Objects::object_binding(GLenum binding, GLuint name)
{
	GLint i; glGetIntegerv(binding, &i); return name == (GLuint)i;
}

inline void Objects::object_delete(PFNDELETE pfnDelete)
{
	pfnDelete(1, &m_Object); m_Object = 0;
}

inline void Objects::object_gen(PFNGEN pfnGen)
{
	pfnGen(1, &m_Object);
}

inline void Objects::object_gen_map(PFNGEN pfnGen, GLsizei bytes, void* objects)
{
	pfnGen(bytes / sizeof(GLuint), (GLuint*)objects);
}

inline GLuint Objects::object_id() const
{
	return m_Object;
}

inline GLboolean Objects::object_is(PFNIS pfnIs) const
{
	return pfnIs(m_Object);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/query/queries.h>
#include <yaglpp/glad/program.h>
#include <yaglpp/buffer/buffers.h>
#include <yaglpp/shader/shaders.h>
#include <yaglpp/texture/textures.h>
#include <yaglpp/glad/renderbuffer.h>
#include <yaglpp/framebuffer/framebuffers.h>
#include <yaglpp/glad/sampler.h>
#include <yaglpp/glad/vertex_array.h>

namespace gl {
#ifdef YAGLPP_IMPLEMENTATION
Program::Program(VertexShader& vs, FragmentShader& fs) : Objects()
{
	Create();
	vs.Attach(*this);
	fs.Attach(*this);
	Link();
}
void Program::AttachShaders(VertexShader& vs, FragmentShader& fs)
{
	vs.Attach(*this);
	fs.Attach(*this);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
Program::Program(VertexShader& vs, GeometryShader& gs, FragmentShader& fs) : Objects()
{
	Create();
	vs.Attach(*this);
	gs.Attach(*this);
	fs.Attach(*this);
	Link();
}

void Program::AttachShaders(VertexShader& vs, GeometryShader& gs, FragmentShader& fs)
{
	vs.Attach(*this);
	gs.Attach(*this);
	fs.Attach(*this);
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_OBJECTS_H
