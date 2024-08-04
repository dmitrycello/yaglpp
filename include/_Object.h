#pragma once
#include "gladpp.h"
namespace gl {
/*GLAD pointer to <glDelete..> functions*/
typedef void (WINAPI YAGLPP_GLAD_PFNDELETE)(GLsizei n, const GLuint* ids);

/*GLAD pointer to <glGen..> functions*/
typedef void (WINAPI YAGLPP_GLAD_PFNGEN)(GLsizei n, GLuint* ids);

/*OpenGL multi-object abstract root class*/
class _Objects
{
private:
	friend class _Object;
	typedef struct {
		GLsizei n;		// Object count
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint ids[0];	// Zero data array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA m_lpData = nullptr;	// Class data

#ifdef _DEBUG
	GLuint _objects_assign(GLuint index, GLenum target);
#else // #ifdef _DEBUG
	GLuint _objects_assign(GLuint index);
#endif // #ifdef _DEBUG

protected:
	void _objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n);
	void _objects_insert(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n, GLint pos);
	void _objects_remove(YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei n, GLint pos);

public:
	/*Returns the number of allocated OpenGL names in the multi-object
	@return The number of elements in the multi-object*/
	GLsizei getObjectCount();

	/*Checks if valid OpenGL multi-object
	@return True if not an empty OpenGL multi-object, false otherwise*/
	GLboolean isObject()
	{
		return m_lpData != nullptr;
	}
}; // class _Objects

#ifndef _DEBUG
inline GLuint _Objects::_objects_assign(GLuint index)
{
	return m_lpData->ids[index];
}

inline GLsizei _Objects::getObjectCount()
{
	return m_lpData->n;
}
#endif // #ifndef _DEBUG
} // namespace gl

#ifndef YAGLPP_BUILD_LIB
#include "Queries.h"
#include "Buffers.h"
#include "Textures.h"
#include "Framebuffers.h"
#include "Renderbuffers.h"
#include "Samplers.h"
#include "VertexArrays.h"
#endif // #ifdef YAGLPP_BUILD

namespace gl {
/*OpenGL object abstract root class*/
class _Object
{
private:
	GLint m_iId;

protected:
	_Object()
	{
		m_iId = 0;
	}

	GLuint _object_id()
	{
		return (m_iId < 0) ? -(m_iId) : m_iId;
	}

	void _object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param = 1); // param used by Shader class
	GLuint _object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param = 1); // param used by Shader class
	void _object_share(_Object& object);

#ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index, GLenum target);
#else // #ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index);
#endif // #ifdef _DEBUG

public:
	/*Checks if the OpenGL object name was generated
	@return True if generated OpenGL object, false otherwise*/
	GLboolean isObject()
	{
		return m_iId != 0;
	}

	/*Checks if the object is a reference of another object
	@return True if reference object, false otherwise*/
	GLboolean isReference()
	{
		return m_iId > 0;
	}
}; // class _Object

#ifndef _DEBUG
inline void _Object::_object_assign(_Objects& objects, GLuint index)
{
	m_iId = objects._objects_assign(index);
}

inline void _Object::_object_share(_Object& object)
{
	GLint i = object.m_iId; m_iId = (i < 0) ? -i : i;
}
#endif // #ifndef _DEBUG
} // namespace gl

#ifndef YAGLPP_BUILD_LIB
#include "_Query.h"
#include "_Buffer.h"
#include "_Shader.h"
#include "_Texture.h"
#include "_Framebuffer.h"
#include "Program.h"
#include "Sampler.h"
#include "Renderbuffer.h"
#include "VertexArray.h"
#endif // #ifdef YAGLPP_BUILD
