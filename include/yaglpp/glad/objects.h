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
		return m_Id;
	}

	/*Checks if not an empty OpenGL object. MSVC getter for <object> property
	@return True if not an empty OpenGL object, false otherwise*/
	GLboolean IsObject() const
	{
		return m_Id > 0;
	}

	/*OpenGL object assignment operator copying the source id
	@param The source OpenGL object
	@return The destination OpenGL object*/
	Objects& operator=(const Objects& source)
	{
		m_Id = source.m_Id; return *this;
	}

	/*Direct object's new[] operator is not allowed. The object's <Alloc> must be used instead*/
	void* operator new[](std::size_t) = delete;

	/*Direct object's delete[] operator is not allowed. The object's <Dealloc> must be used insteade*/
	void operator delete[](void*) = delete;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if not an empty OpenGL object*/
	__declspec(property(get = IsObject)) GLboolean object;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	Objects()
	{
		m_Id = 0;
	}

	Objects(GLint id)
	{
		m_Id = (GLuint)id;
	}

	Objects(const Objects& source)
	{
		m_Id = source.m_Id;
	}

	typedef void (APIENTRY PFNBIND)(GLenum target, GLuint id);
	typedef void (APIENTRY PFNDELETE)(GLsizei n, const GLuint* ids);
	typedef void (APIENTRY PFNGEN)(GLsizei n, GLuint* ids);
	typedef GLboolean(APIENTRY PFNIS)(GLuint id);
	static GLuint* object_alloc(PFNGEN pfnGen, GLsizei n);
	void object_bind(PFNBIND pfnBind, GLenum target);
	static GLboolean object_binding(GLenum binding, GLuint id);
	static void object_dealloc(PFNDELETE pfnDelete, GLuint* objects);
	void object_delete(PFNDELETE pfnDelete);
	static void object_delete_map(PFNDELETE pfnDelete, GLsizei n, void* map);
	void object_gen(PFNGEN pfnGen);
	void object_gen_bind(PFNGEN pfnGen, PFNBIND pfnBind, GLenum target);
	static void object_gen_map(PFNGEN pfnGen, GLsizei n, void* map);
	GLuint object_id() const;
	GLboolean object_is(PFNIS pfnIs) const;
	void object_shader(GLenum type);

private:
	GLuint m_Id; // OpenGL object id
}; // class Objects

#ifdef YAGLPP_IMPLEMENTATION
GLuint* Objects::object_alloc(PFNGEN pfnGen, GLsizei n)
{
	// INVALID SIZE VALUE
	YAGLPP_ASSERT(n > 0);

	GLuint* pObjects = YAGLPP_MALLOC(GLuint, n);
	pfnGen(n, pObjects);
	YAGLPP_GLAD_ERROR;
	return pObjects;
}

void Objects::object_dealloc(PFNDELETE pfnDelete, GLuint* objects)
{
	GLsizei n = (GLsizei)yaglpp_block_size(objects, nullptr) / sizeof(GLuint);
	pfnDelete(n, objects);
	YAGLPP_GLAD_ERROR;
	YAGLPP_FREE(objects);
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
	YAGLPP_ASSERT(m_Id == 0);

	pfnGen(1, &m_Id);
	pfnBind(target, m_Id);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void Objects::object_bind(PFNBIND pfnBind, GLenum target)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Id != 0);

	pfnBind(target, m_Id);
	YAGLPP_GLAD_ERROR;
}

GLboolean Objects::object_binding(GLenum binding, GLuint id)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(id != 0);

	GLint iResult;
	glGetIntegerv(binding, &iResult);
	YAGLPP_GLAD_ERROR;
	return id == (GLuint)iResult;
}

void Objects::object_delete(PFNDELETE pfnDelete)
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Id != 0);

	pfnDelete(1, &m_Id);
	YAGLPP_GLAD_ERROR;
	m_Id = 0;
}

void Objects::object_gen(PFNGEN pfnGen)
{
	// OPENGL OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(m_Id == 0);

	pfnGen(1, &m_Id);
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
	YAGLPP_ASSERT(m_Id != 0);

	return m_Id;
}

GLboolean Objects::object_is(PFNIS pfnIs) const
{
	// OPENGL OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Id != 0);

	GLboolean bResult = pfnIs(m_Id);
	YAGLPP_GLAD_ERROR;
	return bResult;
}

void Objects::object_shader(GLenum type)
{
	// OPENGL SHADER OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(m_Id == 0);

	m_Id = glCreateShader(type);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void Objects::object_bind(PFNBIND pfnBind, GLenum target)
{
	pfnBind(target, m_Id);
}

inline GLboolean Objects::object_binding(GLenum binding, GLuint id)
{
	GLint i; glGetIntegerv(binding, &i); return id == (GLuint)i;
}

inline void Objects::object_delete(PFNDELETE pfnDelete)
{
	pfnDelete(1, &m_Id); m_Id = 0;
}

inline void Objects::object_gen(PFNGEN pfnGen)
{
	pfnGen(1, &m_Id);
}

inline void Objects::object_gen_map(PFNGEN pfnGen, GLsizei bytes, void* objects)
{
	pfnGen(bytes / sizeof(GLuint), (GLuint*)objects);
}

inline GLuint Objects::object_id() const
{
	return m_Id;
}

inline GLboolean Objects::object_is(PFNIS pfnIs) const
{
	return pfnIs(m_Id);
}

inline void Objects::object_shader(GLenum type)
{
	m_Id = glCreateShader(type);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/glad/queries.h>
#include <yaglpp/glad/queries_t.h>
#include <yaglpp/glad/program.h>
#include <yaglpp/glad/buffers.h>
#include <yaglpp/glad/buffers_t.h>
#include <yaglpp/glad/shaders.h>
#include <yaglpp/glad/shaders_t.h>
#include <yaglpp/glad/textures.h>
#include <yaglpp/glad/textures_t.h>
#include <yaglpp/glad/renderbuffer.h>
#include <yaglpp/glad/framebuffers.h>
#include <yaglpp/glad/framebuffers_t.h>
#include <yaglpp/glad/sampler.h>
#include <yaglpp/glad/vertex_array.h>

namespace gl {
#ifdef YAGLPP_IMPLEMENTATION
Program::Program(VertexShader& vs, FragmentShader& fs) : Objects()
{
	Create();
	AttachShaders(vs, fs);
}

void Program::AttachShaders(VertexShader& vs, FragmentShader& fs)
{
	vs.Attach(*this);
	fs.Attach(*this);
	Link();
	vs.Delete();
	fs.Delete();
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void ReadPixels(PixelPackBuffer& ppb, GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, GLintptr offset)
{
	// PIXEL PACK BUFFER IS UNBOUND
	YAGLPP_ASSERT(ppb.IsBinding());

	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, (void*)offset);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void ReadPixels(PixelPackBuffer& ppb, GLint x, GLint y, GLsizei width, GLsizei height, ReadFormat format, ReadType type, GLintptr offset)
{
	glReadPixels(x, y, width, height, (GLenum)format, (GLenum)type, (void*)offset);
}
#endif // #if defined (YAGLPP_VERSION_2_1) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
Program::Program(VertexShader& vs, GeometryShader& gs, FragmentShader& fs) : Objects()
{
	Create();
	AttachShaders(vs, gs, fs);
}

void Program::AttachShaders(VertexShader& vs, GeometryShader& gs, FragmentShader& fs)
{
	vs.Attach(*this);
	gs.Attach(*this);
	fs.Attach(*this);
	Link();
	vs.Delete();
	gs.Delete();
	fs.Delete();
}
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_OBJECTS_H
