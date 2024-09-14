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

#ifdef YAGLPP_IMPLEMENTATION
void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	YAGLPP_ASSERT(_mpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
	pfnDelete(_mpData->n, _mpData->ids); // glDelete..
	YAGLPP_GLAD_ERROR;
	YAGLPP_FREE(_mpData);
	_mpData = nullptr;
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n)
{
	YAGLPP_ASSERT(_mpData == nullptr); // OPENGL MULTI-OBJECT IS NOT EMPTY

#ifdef _DEBUG
	_mpData = (_LPDATA)YAGLPP_CALLOC(sizeof(_DATA) + n * sizeof(GLuint) * 2);
#else // #ifdef _DEBUG
	_mpData = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + n * sizeof(GLuint));
#endif // #ifdef _DEBUG

	_mpData->n = n;
	pfnGen(n, _mpData->ids); // glGen..
	YAGLPP_GLAD_ERROR;
}

void _Objects::_objects_insert(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n, GLint pos)
{
	GLsizei iOld = getObjectCount();
	YAGLPP_ASSERT(n > 0); // OBJECT NUMBER VALUE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT((pos >= 0) && (pos <= iOld)); // POSITION VALUE MUST BE WITHIN OBJECT SIZE
	GLsizei iNew = iOld + n;

#ifdef _DEBUG
	_LPDATA lpNew = (_LPDATA)YAGLPP_CALLOC(sizeof(_DATA) + iNew * (sizeof(GLuint) * 2));
#else // #ifdef _DEBUG
	_LPDATA lpNew = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + iNew * sizeof(GLuint));
#endif // #ifdef _DEBUG

	lpNew->n = iNew;
	size_t iSize = pos * sizeof(GLuint);
	memcpy(lpNew->ids, _mpData->ids, iSize);

#ifdef _DEBUG
	memcpy(&lpNew->ids[iNew], &_mpData->ids[iOld], iSize);
#endif // #ifdef _DEBUG

	iSize = ((size_t)iOld - (size_t)pos) * sizeof(GLint);
	memcpy(&lpNew->ids[pos + n], &_mpData->ids[pos], iSize);

#ifdef _DEBUG
	memcpy(&lpNew->ids[iNew + pos + n], &_mpData->ids[iOld + pos], iSize);
#endif // #ifdef _DEBUG

	pfnGen(n, &lpNew->ids[pos]); // glGen..
	YAGLPP_GLAD_ERROR;
	YAGLPP_FREE(_mpData);
	_mpData = lpNew;
}

void _Objects::_objects_remove(YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei n, GLint pos)
{
	GLsizei iOld = getObjectCount();
	YAGLPP_ASSERT((n > 0) && (n < iOld)); // OBJECT NUMBER VALUE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT((pos >= 0) && (pos <= iOld)); // POSITION VALUE MUST BE WITHIN OBJECT SIZE
	GLsizei iNew = iOld - n;

#ifdef _DEBUG
	_LPDATA lpNew = (_LPDATA)YAGLPP_CALLOC(sizeof(_DATA) + iNew * (sizeof(GLuint) * 2));
#else // #ifdef _DEBUG
	_LPDATA lpNew = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + iNew * sizeof(GLuint));
#endif // #ifdef _DEBUG

	lpNew->n = iNew;
	size_t iSize = pos * sizeof(GLuint);
	memcpy(lpNew->ids, _mpData->ids, iSize);

#ifdef _DEBUG
	memcpy(&lpNew->ids[iNew], &_mpData->ids[iOld], iSize);
#endif // #ifdef _DEBUG

	iSize = ((size_t)iOld - (size_t)pos - (size_t)n) * sizeof(GLint);
	memcpy(&lpNew->ids[pos], &_mpData->ids[pos + n], iSize);

#ifdef _DEBUG
	memcpy(&lpNew->ids[iNew + pos], &_mpData->ids[iOld + pos + n], iSize);
#endif // #ifdef _DEBUG

	pfnDelete(n, &_mpData->ids[pos]); // glDelete..
	YAGLPP_GLAD_ERROR;
	YAGLPP_FREE(_mpData);
	_mpData = lpNew;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLuint _Objects::_objects_assign(GLuint index, GLenum target)
{
	YAGLPP_ASSERT(getObjectCount() > (GLsizei)index); // OPENGL OBJECT INDEX IS INVALID
	GLuint uTindex = index + _mpData->n;
	GLenum eTarget = _mpData->ids[uTindex];
	if (eTarget == 0)
	{
		_mpData->ids[uTindex] = target;
	}
	else YAGLPP_ASSERT(eTarget == target); // OPENGL OBJECT IS ASSIGNED TO DIFFERENT TARGET
	return _mpData->ids[index];
}

GLsizei _Objects::getObjectCount()
{
	YAGLPP_ASSERT(_mpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
	return _mpData->n;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLuint _Objects::_objects_assign(GLuint index)
{
	return _mpData->ids[index];
}

inline GLsizei _Objects::getObjectCount()
{
	return _mpData->n;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include "Queries.h"
#include "Buffers.h"
#include "Textures.h"
#include "Framebuffers.h"
#include "Renderbuffers.h"
#include "Samplers.h"
#include "VertexArrays.h"

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

#ifdef YAGLPP_IMPLEMENTATION
void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	YAGLPP_ASSERT(_miId != 0); // OPENGL OBJECT WAS ALREADY DELETED
	if (_miId < 0)
	{
		GLuint uId = -(_miId);
		pfnDelete(1, &uId); // glDelete..
		YAGLPP_GLAD_ERROR;
	}
	_miId = 0;
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param)
{
	GLuint uId;
	YAGLPP_ASSERT(_miId == 0); // OPENGL OBJECT WAS ALREADY CREATED
	pfnGen((GLsizei)param, &uId); // glGen..
	YAGLPP_GLAD_ERROR;
	_miId = -((GLint)uId);
}

GLuint _Object::_object_id()
{
	if (_miId > 0)
	{
		return _miId;
	}
	if (_miId < 0)
	{
		return -(_miId);
	}
	return (GLuint)-1;
}

GLuint _Object::_object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param)
{
	GLuint uId = _object_id();
	if (uId == (GLuint)-1)
	{
		pfnGen((GLsizei)param, &uId); // glGen..
		YAGLPP_GLAD_ERROR;
		_miId = -((GLint)uId);
	}
	return uId;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void _Object::_object_assign(_Objects& objects, GLuint index, GLenum target)
{
	YAGLPP_ASSERT(_miId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
	_miId = objects._objects_assign(index, target);
}

void _Object::_object_share(_Object& object)
{
	GLint iId = object._miId;
	YAGLPP_ASSERT(_miId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
	YAGLPP_ASSERT(iId != 0); // OPENGL EMPTY OBJECT COULD NOT BE SHARED
	_miId = (iId < 0) ? -iId : iId;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void _Object::_object_assign(_Objects& objects, GLuint index)
{
	_miId = objects._objects_assign(index);
}

inline void _Object::_object_share(_Object& object)
{
	GLint i = object._miId; _miId = (i < 0) ? -i : i;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include "_Query.h"
#include "_Buffer.h"
#include "_Shader.h"
#include "_Texture.h"
#include "_Framebuffer.h"
#include "Program.h"
#include "Sampler.h"
#include "Renderbuffer.h"
#include "VertexArray.h"
