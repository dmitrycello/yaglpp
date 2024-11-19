#pragma once
#include <yaglpp/gladpp.h>
/*GLAD object autodelete flag*/
#define YAGLPP_GLAD_AUTO 0x80000000
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
	GLuint _muId = 0;

protected:
	GLuint _object_id() const {
		return _muId & ~YAGLPP_GLAD_AUTO;
	}
	void _object_set(GLint name) {
		_muId = (GLuint)name;
	}
	GLboolean _object_binding(GLenum binding) const;
	void _object_clean(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source);
	void _object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param, GLboolean autodelete);
	GLuint _object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param);

public:
	/*Checks if the OpenGL object name was generated. Used as a getter of <object> property
	@return True if generated OpenGL object, false otherwise*/
	GLboolean isObject() const
	{
		return _muId != 0;
	}

	/*Checks if the object's automatic cleanup flag is set. Used as a getter of <autodelete> property
	@return True if autodelete flag is set, false otherwise*/
	GLboolean isAutodelete() const;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if the object if autodelete flag is set*/
	__declspec(property(get = isAutodelete)) GLboolean autodelete;

	/*Read-only property to check if the OpenGL object name was generated*/
	__declspec(property(get = isObject)) GLboolean object;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Object

/*OpenGL multi-object abstract root class*/
class _Objects
{
private:
	typedef struct {
		GLuint ref; // Ref count
		GLuint num; // Object count
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint ids[0]; // Zero array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA _mpData = nullptr; // Class data

protected:
	void _objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source);
	void _objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLuint num);
	GLboolean _objects_is(_Objects& source) const { return (_mpData != nullptr) && (_mpData == source._mpData); }

#ifdef _DEBUG
	_Object& _objects_get(GLuint index, GLenum target) const;
#else // #ifdef _DEBUG
	_Object& _objects_get(GLuint index) const;
#endif // #ifdef _DEBUG

public:
	/*Returns the number of allocated OpenGL object names in the multi-object. Used as a getter of <objectNum> property
	@return The number of elements in the multi-object*/
	GLuint getObjectNum() const;

	/*Returns the number of duplicate multi-objects. Used as a getter of <objectNum> property
	@return The number of duplicate multi-objects, zero if none*/
	GLuint getObjectRef() const;

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
	__declspec(property(get = getObjectNum)) GLuint objectNum;

	/*Read-only property for number of duplicate multi-objects*/
	__declspec(property(get = getObjectRef)) GLuint objectRef;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Objects

#ifdef YAGLPP_IMPLEMENTATION
GLboolean _Object::_object_binding(GLenum binding) const
{
	GLuint uBound;
	glGetIntegerv(binding, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	return (uBound > 0) && (uBound == _object_id());
}

void _Object::_object_clean(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_muId & YAGLPP_GLAD_AUTO)
	{
		_muId &= ~YAGLPP_GLAD_AUTO;
		pfnDelete(1, &_muId); // glDelete..
		YAGLPP_GLAD_ERROR;
	}
}

void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	_muId &= ~YAGLPP_GLAD_AUTO;
	pfnDelete(1, &_muId); // glDelete..
	YAGLPP_GLAD_ERROR;
	_muId = 0;
}

void _Object::_object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source)
{
	_object_clean(pfnDelete);
	_muId = source._muId & ~YAGLPP_GLAD_AUTO; // ref copy
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param, GLboolean autodelete)
{
	_object_clean(pfnDelete);
	pfnGen(param, &_muId); // glGen..
	YAGLPP_GLAD_ERROR;
	if (autodelete == GL_TRUE)
	{
		_muId |= YAGLPP_GLAD_AUTO;
	}
}

GLuint _Object::_object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param)
{
	GLuint uId = _object_id();
	if (uId == 0)
	{
		pfnGen(param, &uId); // glGen..
		YAGLPP_GLAD_ERROR;
		_muId = uId | YAGLPP_GLAD_AUTO;
	}
	return uId;
}

void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_mpData != nullptr)
	{
		if (_mpData->ref == 0)
		{
			pfnDelete((GLsizei)_mpData->num, _mpData->ids); // glDelete..
			YAGLPP_GLAD_ERROR;
			_deallocate(_mpData, nullptr);
		}
		else _mpData->ref--;
		_mpData = nullptr;
	}
}

void _Objects::_objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source)
{
	if (&source != this)
	{
		_objects_delete(pfnDelete);
		_mpData = source._mpData;
		if (_mpData != nullptr)
		{
			_mpData->ref++;
		}
	}
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLuint num)
{
	_objects_delete(pfnDelete);

#ifdef _DEBUG
	_mpData = (_LPDATA)_callocate(sizeof(_DATA) + num * sizeof(GLuint) * 2, nullptr);
#else // #ifdef _DEBUG
	_mpData = (_LPDATA)_allocate(sizeof(_DATA) + num * sizeof(GLuint), nullptr);
	_mpData->ref = 0;
#endif // #ifdef _DEBUG

	_mpData->num = num | YAGLPP_GLAD_AUTO;
	pfnGen((GLsizei)num, _mpData->ids); // glGen..
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLboolean _Object::isAutodelete() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL OBJECT IS EMPTY
	return (GLboolean)(_muId & YAGLPP_GLAD_AUTO);
}

_Object& _Objects::_objects_get(GLuint index, GLenum target) const
{
	GLuint uNum = getObjectNum();
	YAGLPP_ASSERT(index < uNum); // OPENGL MULTI-OBJECT INVALID INDEX
	GLuint uTindex = index + uNum;
	GLenum eTarget = _mpData->ids[uTindex];
	if (eTarget == 0)
	{
		_mpData->ids[uTindex] = target;
	}
	else YAGLPP_ASSERT(eTarget == target); // OPENGL MULTI-OBJECT INVALID TARGET
	return (_Object&)_mpData->ids[index];
}

GLuint _Objects::getObjectNum() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL MULTI-OBJECT IS EMPTY
	return _mpData->num;
}

GLuint _Objects::getObjectFer() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL MULTI-OBJECT IS EMPTY
	return _mpData->num;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLboolean _Object::isAutodelete() const
{
	return (GLboolean)(_muId & YAGLPP_GLAD_AUTO);
}

inline _Object& _Objects::_objects_get(GLuint index) const
{
	return (_Object&)_mpData->ids[index];
}

inline GLuint _Objects::getObjectNum() const
{
	return _mpData->num;
}

inline GLuint _Objects::getObjectRef() const
{
	return _mpData->ref;
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
