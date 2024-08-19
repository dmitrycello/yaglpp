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
	_LPDATA _mpData = nullptr;	// Class data

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
	/*Returns the number of allocated OpenGL names in the multi-object. Used as a getter of <objectCount> property
	@return The number of elements in the multi-object*/
	GLsizei getObjectCount();

	/*Checks if valid OpenGL multi-object. Used as a getter of <object> property
	@return True if not an empty OpenGL multi-object, false otherwise*/
	GLboolean isObject()
	{
		return _mpData != nullptr;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if valid OpenGL multi-object*/
	__declspec(property(get = isObject)) GLboolean object;

	/*Read-only property for number of allocated OpenGL names in the multi-object*/
	__declspec(property(get = getObjectCount)) GLsizei objectCount;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Objects

#ifndef _DEBUG
inline GLuint _Objects::_objects_assign(GLuint index)
{
	return _mpData->ids[index];
}

inline GLsizei _Objects::getObjectCount()
{
	return _mpData->n;
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
	GLint _miId;

protected:
	_Object()
	{
		_miId = 0;
	}

	void _object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param = 1); // param used by Shader class
	GLuint _object_id();
	GLuint _object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param = 1); // param used by Shader class
	void _object_share(_Object& object);

#ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index, GLenum target);
#else // #ifdef _DEBUG
	void _object_assign(_Objects& objects, GLuint index);
#endif // #ifdef _DEBUG

public:
	/*Checks if the OpenGL object name was generated. Used as a getter of <object> property
	@return True if generated OpenGL object, false otherwise*/
	GLboolean isObject()
	{
		return _miId != 0;
	}

	/*Checks if the object is a reference of another object. Used as a getter of <reference> property
	@return True if reference object, false otherwise*/
	GLboolean isReference()
	{
		return _miId > 0;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if the OpenGL object name was generated*/
	__declspec(property(get = isObject)) GLboolean object;

	/*Read-only property to check if the object is a reference of another object*/
	__declspec(property(get = isReference)) GLboolean reference;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Object

#ifndef _DEBUG
inline void _Object::_object_assign(_Objects& objects, GLuint index)
{
	_miId = objects._objects_assign(index);
}

inline void _Object::_object_share(_Object& object)
{
	GLint i = object._miId; _miId = (i < 0) ? -i : i;
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
