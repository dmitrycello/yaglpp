#pragma once
#include <yaglpp/gladpp.h>
namespace gl {
/*GLAD pointer to <glGen..> functions*/
typedef void (WINAPI YAGLPP_GLAD_PFNGEN)(GLsizei n, GLuint* ids);

/*GLAD pointer to <glBind..> functions*/
typedef void (WINAPI YAGLPP_GLAD_PFNBIND)(GLenum target, GLuint id);

/*GLAD pointer to <glDelete..> functions*/
typedef void (WINAPI YAGLPP_GLAD_PFNDELETE)(GLsizei n, const GLuint* ids);

/*OpenGL object abstract root class*/
class _Object
{
private:
	GLint _miId = 0;

protected:
	void _object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source);
	void _object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param);
	GLuint _object_id();
	GLuint _object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param);
	void _object_ref(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source);
	void _object_set(GLint name) { _miId = name; }

public:
	/*Checks if the OpenGL object name was generated. Used as a getter of <object> property
	@return True if generated OpenGL object, false otherwise*/
	GLboolean isObject() const
	{
		return _miId != 0;
	}

	/*Checks if the object is a reference of another object. Used as a getter of <reference> property
	@return True if reference object, false otherwise*/
	GLboolean isReference() const;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if the OpenGL object name was generated*/
	__declspec(property(get = isObject)) GLboolean object;

	/*Read-only property to check if the object is a reference of another object*/
	__declspec(property(get = isReference)) GLboolean reference;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Object

/*OpenGL multi-object abstract root class*/
class _Objects
{
private:
	friend class _Object;
	typedef struct {
		GLsizei n; // Object count
		GLuint ref; // Ref count
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint ids[0]; // Zero array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA _mpData = nullptr; // Class data

protected:
	void _objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source);
	void _objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei n);
	_Object& _objects_get(GLuint index, GLenum target);

public:
	/*Returns the number of allocated OpenGL names in the multi-object. Used as a getter of <objectCount> property
	@return The number of elements in the multi-object*/
	GLsizei getObjectCount() const;

	/*Checks if valid OpenGL multi-object. Used as a getter of <object> property
	@return True if not an empty OpenGL multi-object, false otherwise*/
	GLboolean isObject() const
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
void _Object::_object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source)
{
	_object_delete(pfnDelete);
	_miId = source._miId;
	if (_miId < 0)
	{
		source._miId = -(_miId); // Source ref
	}
}

void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_miId < 0)
	{
		GLuint uId = -(_miId);
		pfnDelete(1, &uId); // glDelete..
		YAGLPP_GLAD_ERROR;
	}
	_miId = 0;
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param)
{
	GLuint uId;
	_object_delete(pfnDelete);
	pfnGen(param, &uId); // glGen..
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
	return GL_INVALID_INDEX;
}

GLuint _Object::_object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param)
{
	GLuint uId = _object_id();
	if (uId == GL_INVALID_INDEX)
	{
		pfnGen(param, &uId); // glGen..
		YAGLPP_GLAD_ERROR;
		_miId = -((GLint)uId);
	}
	return uId;
}

void _Object::_object_ref(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source)
{
	_object_delete(pfnDelete);
	_miId = source._miId;
	if (_miId < 0)
	{
		_miId = -(_miId);
	}
}

void _Objects::_objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source)
{
	_objects_delete(pfnDelete);
	if (&source != this)
	{
		_mpData = source._mpData;
		if (_mpData != nullptr)
		{
			_mpData->ref++;
		}
	}
}

void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_mpData != nullptr)
	{
		if (_mpData->ref == 0)
		{
			pfnDelete(_mpData->n, _mpData->ids); // glDelete..
			YAGLPP_GLAD_ERROR;
			_deallocate(_mpData, nullptr);
		}
		else _mpData->ref--;
		_mpData = nullptr;
	}
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei n)
{
	_objects_delete(pfnDelete);

#ifdef _DEBUG
	_mpData = (_LPDATA)_callocate(sizeof(_DATA) + n * sizeof(GLuint) * 2, nullptr);
#else // #ifdef _DEBUG
	_mpData = (_LPDATA)_allocate(sizeof(_DATA) + n * sizeof(GLuint), nullptr);
	_mpData->ref = 0;
#endif // #ifdef _DEBUG

	_mpData->n = n;
	pfnGen(n, _mpData->ids); // glGen..
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLboolean _Object::isReference() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL OBJECT IS EMPTY
	return _miId > 0;
}

_Object& _Objects::_objects_get(GLuint index, GLenum target)
{
	YAGLPP_ASSERT(index < (GLuint)getObjectCount()); // OPENGL MULTI-OBJECT INVALID INDEX
	GLuint uTindex = index + _mpData->n;
	GLenum eTarget = _mpData->ids[uTindex];
	if (eTarget == 0)
	{
		_mpData->ids[uTindex] = target;
	}
	else YAGLPP_ASSERT(eTarget == target); // OPENGL MULTI-OBJECT INVALID TARGET
	return (_Object&)_mpData->ids[index];
}

GLsizei _Objects::getObjectCount() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL MULTI-OBJECT IS EMPTY
	return _mpData->n;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLboolean _Object::isReference() const
{
	return _miId > 0;
}

inline _Object& _Objects::_objects_get(GLuint index, GLenum target)
{
	return (_Object&)_mpData->ids[index];
}

inline GLsizei _Objects::getObjectCount() const
{
	return _mpData->n;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl

#include <yaglpp/query/_query.h>
#include <yaglpp/buffer/_buffer.h>
#include <yaglpp/shader/_shader.h>
#include <yaglpp/texture/_texture.h>
#include <yaglpp/framebuffer/_framebuffer.h>
#include <yaglpp/glad/program.h>
#include <yaglpp/glad/sampler.h>
#include <yaglpp/glad/renderbuffer.h>
#include <yaglpp/glad/vertex_array.h>
