#pragma once
#include <yaglpp/gladpp.h>
/*GLAD object autodelete flag*/
#define YAGLPP_GLAD_SIZE 256
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
	friend class _Objects;
	/*GLAD object data cell structure*/
	typedef struct {
		GLuint id; // Object id
		GLuint ref; // Ref count
		GLuint free; // Free cell
	} _CELL, *_LPCELL;

	/*GLAD object static data structure*/
	static struct _SDATA {
		GLuint size; // Block size
		GLuint added; // Next cell to add
		GLuint removed; // Next cell to remove
		_LPCELL cells; // Cell block
		~_SDATA() {
			_deallocate(cells, nullptr);
		}
		GLuint add(GLuint id);
		GLboolean remove(GLuint index);
	} _s;

	/*GLAD object member data: cell index + flag | id*/
	GLuint _m = 0;

protected:
	GLboolean _object_is(_Object& source) const {
		return (_m != 0) && (_object_id() == source._object_id());
	}
	void _object_set(GLuint name) {
		_m = name;
	}
	GLboolean _object_binding(GLenum binding) const;
	void _object_close(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source);
	void _object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param);
	GLuint _object_id() const;
	GLuint _object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param);
	void _object_refer(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source);

public:
	/*Retrieves the number of active instances of an OpenGL object, or zero if empty or reference object
	@return The number of object's active instances, or zero*/
	GLuint getObjectRef() const;

	/*Checks if the object is not empty, and refers to a generated OpenGL object name, or to zero if another inctance of the object has deleted the OpenGL object name. Used as a getter of <object> property
	@return True if the object is not empty, false otherwise*/
	GLboolean isObject() const;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if the object is not empty*/
	__declspec(property(get = isObject)) GLboolean object;

	/*Read-only property for number of object's active instances*/
	__declspec(property(get = getObjectRef)) GLuint objectRef;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Object

/*OpenGL multi-object abstract root class*/
class _Objects
{
private:
	/*GLAD multi-object data structure*/
	typedef struct {
		GLuint ref; // Ref count
		GLuint num; // Object count
#pragma warning(push)
#pragma warning(disable : 4200)
		GLuint ids[0]; // Zero array
#pragma warning(pop)
	} _DATA, *_LPDATA;

	/*GLAD multi-object member data: pointer to allocated structure*/
	_LPDATA _m = nullptr;

protected:
	void _objects_close(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete);
	void _objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source);
	void _objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLuint num);
	GLboolean _objects_is(_Objects& source) const { return (_m != nullptr) && (_m == source._m); }

#ifdef _DEBUG
	GLuint _objects_get(GLuint index, GLenum target) const;
#else // #ifdef _DEBUG
	GLuint _objects_get(GLuint index) const;
#endif // #ifdef _DEBUG

public:
	/*Returns the number of allocated OpenGL object names in the multi-object. Used as a getter of <objectNum> property
	@return The number of elements in the multi-object*/
	GLuint getObjectNum() const;

	/*Retrieves the number of active instances of an OpenGL multi-object
	@return The number of object's active instances*/
	GLuint getObjectRef() const;

	/*Checks if valid OpenGL multi-object. Used as a getter of <object> property
	@return True if not an empty OpenGL multi-object, false otherwise*/
	GLboolean isObject() const
	{
		return _m != nullptr;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if valid OpenGL multi-object*/
	__declspec(property(get = isObject)) GLboolean object;

	/*Read-only property for number of allocated OpenGL names in the multi-object*/
	__declspec(property(get = getObjectNum)) GLuint objectNum;

	/*Read-only property for number of multi-object's active instances*/
	__declspec(property(get = getObjectRef)) GLuint objectRef;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class _Objects

#ifdef YAGLPP_IMPLEMENTATION
_Object::_SDATA _Object::_s;
GLuint _Object::_SDATA::add(GLuint id)
{
	GLuint uIndex;
	if (removed == 0)
	{
		if (added == size)
		{
			size = (size << 1) + YAGLPP_GLAD_SIZE;
			cells = (_LPCELL)_reallocate(cells, size * sizeof(_CELL), nullptr);
		}
		uIndex = added;
		added++; // post-inc
	}
	else
	{
		--removed; // pre-dec
		uIndex = cells[removed].free;
	}
	YAGLPP_ASSERT(cells != nullptr); // SAL REQUIREMENT
	cells[uIndex].id = id;
	cells[uIndex].ref = 0;
	return uIndex | YAGLPP_GLAD_AUTO;
}

GLboolean _Object::_SDATA::remove(GLuint index)
{
	if (cells[index].ref == 0)
	{
		cells[removed].free = index;
		removed++; // post-inc
		return GL_TRUE;
	}
	cells[index].ref--;
	return GL_FALSE;
}

GLboolean _Object::_object_binding(GLenum binding) const
{
	GLuint uBound;
	glGetIntegerv(binding, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	return (uBound > 0) && (uBound == _object_id());
}

void _Object::_object_close(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_m & YAGLPP_GLAD_AUTO)
	{
		GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
		if (_s.remove(uIndex))
		{
			GLuint& rId = _s.cells[uIndex].id;
			if (rId != 0)
			{
				pfnDelete(1, &rId); // glDelete..
				YAGLPP_GLAD_ERROR;
				rId = 0;
			}
		}
	}
	_m = 0;
}

void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_m & YAGLPP_GLAD_AUTO)
	{
		GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
		GLuint& rId = _s.cells[uIndex].id;
		if (rId != 0)
		{
			pfnDelete(1, &rId); // glDelete..
			YAGLPP_GLAD_ERROR;
			rId = 0;
		}
		_s.remove(uIndex);
	}
	_m = 0;
}

void _Object::_object_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source)
{
	if (&source != this)
	{
		_object_close(pfnDelete);
		_m = source._m;
		if (_m & YAGLPP_GLAD_AUTO)
		{
			GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
			_s.cells[uIndex].ref++;
		}
	}
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei param)
{
	_object_close(pfnDelete);
	pfnGen(param, &_m); // glGen..
	YAGLPP_GLAD_ERROR;
	_m = _s.add(_m);
}

GLuint _Object::_object_id() const
{
	if (_m & YAGLPP_GLAD_AUTO)
	{
		GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
		return _s.cells[uIndex].id;
	}
	else return _m;
}

GLuint _Object::_object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei param)
{
	GLuint uId = _object_id();
	if (uId == 0)
	{
		pfnGen(param, &uId); // glGen..
		YAGLPP_GLAD_ERROR;
		_m = _s.add(uId);
	}
	return uId;
}

void _Object::_object_refer(YAGLPP_GLAD_PFNDELETE pfnDelete, _Object& source)
{
	if (&source != this)
	{
		_object_close(pfnDelete);
		_m = source._object_id();
	}
}

void _Objects::_objects_close(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_m != nullptr)
	{
		if (_m->ref == 0)
		{
			if (_m->ids[0] != 0)
			{
				pfnDelete((GLsizei)_m->num, _m->ids); // glDelete..
				YAGLPP_GLAD_ERROR;
			}
			_deallocate(_m, nullptr);
		}
		else _m->ref--;
		_m = nullptr;
	}
}

void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
	if (_m != nullptr)
	{
		if (_m->ids[0] != 0)
		{
			pfnDelete((GLsizei)_m->num, _m->ids); // glDelete..
			YAGLPP_GLAD_ERROR;
			memset(_m->ids, 0, _m->num * sizeof(GLuint));
		}
		if (_m->ref == 0)
		{
			_deallocate(_m, nullptr);
		}
		else _m->ref--;
		_m = nullptr;
	}
}

void _Objects::_objects_dup(YAGLPP_GLAD_PFNDELETE pfnDelete, _Objects& source)
{
	if (&source != this)
	{
		_objects_close(pfnDelete);
		_m = source._m;
		if (_m != nullptr)
		{
			_m->ref++;
		}
	}
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, YAGLPP_GLAD_PFNDELETE pfnDelete, GLuint num)
{
	_objects_close(pfnDelete);

#ifdef _DEBUG
	_m = (_LPDATA)_callocate(sizeof(_DATA) + num * sizeof(GLuint) * 2, nullptr);
#else // #ifdef _DEBUG
	_m = (_LPDATA)_allocate(sizeof(_DATA) + num * sizeof(GLuint), nullptr);
	_m->ref = 0;
#endif // #ifdef _DEBUG

	_m->num = num;
	pfnGen((GLsizei)num, _m->ids); // glGen..
	YAGLPP_GLAD_ERROR;
}

GLuint _Object::getObjectRef() const
{
	if (_m & YAGLPP_GLAD_AUTO)
	{
		GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
		return _s.cells[uIndex].ref + 1;
	}
	else return 0;
}

GLboolean _Object::isObject() const
{
	if (_m & YAGLPP_GLAD_AUTO)
	{
		GLuint uIndex = _m & ~YAGLPP_GLAD_AUTO;
		return _s.cells[uIndex].id != 0;
	}
	else return _m != 0;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLuint _Objects::_objects_get(GLuint index, GLenum target) const
{
	GLuint uNum = getObjectNum();
	YAGLPP_ASSERT(index < uNum); // OPENGL MULTI-OBJECT INVALID INDEX
	GLuint uTindex = index + uNum;
	GLenum eTarget = _m->ids[uTindex];
	if (eTarget == 0)
	{
		_m->ids[uTindex] = target;
	}
	else YAGLPP_ASSERT(eTarget == target); // OPENGL MULTI-OBJECT INVALID TARGET
	return _m->ids[index];
}

GLuint _Objects::getObjectNum() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL MULTI-OBJECT IS EMPTY
	return _m->num;
}

GLuint _Objects::getObjectRef() const
{
	YAGLPP_ASSERT(isObject()); // OPENGL MULTI-OBJECT IS EMPTY
	return _m->ref + 1;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLuint _Objects::_objects_get(GLuint index) const
{
	return _m->ids[index];
}

inline GLuint _Objects::getObjectNum() const
{
	return _m->num;
}

inline GLuint _Objects::getObjectRef() const
{
	return _m->ref + 1;
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
