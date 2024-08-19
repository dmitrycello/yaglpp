#define YAGLPP_BUILD_LIB
#include <yaglpp/_Object.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
    _YAGLPP_ASSERT_(_miId != 0); // OPENGL OBJECT WAS ALREADY DELETED
    if (_miId < 0)
    {
        GLuint uId = -(_miId);
        pfnDelete(1, &uId); // glDelete..
        _YAGLPP_GLAD_ERROR_;
    }
    _miId = 0;
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param)
{
    GLuint uId;
    _YAGLPP_ASSERT_(_miId == 0); // OPENGL OBJECT WAS ALREADY CREATED
    pfnGen((GLsizei)param, &uId); // glGen..
    _YAGLPP_GLAD_ERROR_;
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
        _YAGLPP_GLAD_ERROR_;
        _miId = -((GLint)uId);
    }
    return uId;
}

void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
    _YAGLPP_ASSERT_(_mpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    pfnDelete(_mpData->n, _mpData->ids); // glDelete..
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(_mpData);
    _mpData = nullptr;
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n)
{
    _YAGLPP_ASSERT_(_mpData == nullptr); // OPENGL MULTI-OBJECT IS NOT EMPTY

#ifdef _DEBUG
    _mpData = (_LPDATA)_YAGLPP_CALLOC_(sizeof(_DATA) + n * sizeof(GLuint) * 2);
#else // #ifdef _DEBUG
    _mpData = (_LPDATA)_YAGLPP_MALLOC_(sizeof(_DATA) + n * sizeof(GLuint));
#endif // #ifdef _DEBUG

    _mpData->n = n;
    pfnGen(n, _mpData->ids); // glGen..
    _YAGLPP_GLAD_ERROR_;
}

void _Objects::_objects_insert(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n, GLint pos)
{
    GLsizei iOld = getObjectCount();
    _YAGLPP_ASSERT_(n > 0); // OBJECT NUMBER VALUE MUST BE GREATER THAN ZERO
    _YAGLPP_ASSERT_((pos >= 0) && (pos <= iOld)); // POSITION VALUE MUST BE WITHIN OBJECT SIZE
    GLsizei iNew = iOld + n;

#ifdef _DEBUG
    _LPDATA lpNew = (_LPDATA)_YAGLPP_CALLOC_(sizeof(_DATA) + iNew * (sizeof(GLuint) * 2));
#else // #ifdef _DEBUG
    _LPDATA lpNew = (_LPDATA)_YAGLPP_MALLOC_(sizeof(_DATA) + iNew * sizeof(GLuint));
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
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(_mpData);
    _mpData = lpNew;
}

void _Objects::_objects_remove(YAGLPP_GLAD_PFNDELETE pfnDelete, GLsizei n, GLint pos)
{
    GLsizei iOld = getObjectCount();
    _YAGLPP_ASSERT_((n > 0) && (n < iOld)); // OBJECT NUMBER VALUE MUST BE GREATER THAN ZERO
    _YAGLPP_ASSERT_((pos >= 0) && (pos <= iOld)); // POSITION VALUE MUST BE WITHIN OBJECT SIZE
    GLsizei iNew = iOld - n;

#ifdef _DEBUG
    _LPDATA lpNew = (_LPDATA)_YAGLPP_CALLOC_(sizeof(_DATA) + iNew * (sizeof(GLuint) * 2));
#else // #ifdef _DEBUG
    _LPDATA lpNew = (_LPDATA)_YAGLPP_MALLOC_(sizeof(_DATA) + iNew * sizeof(GLuint));
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
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(_mpData);
    _mpData = lpNew;
}

#ifdef _DEBUG
GLuint _Objects::_objects_assign(GLuint index, GLenum target)
{
    _YAGLPP_ASSERT_(getObjectCount() > (GLsizei)index); // OPENGL OBJECT INDEX IS INVALID
    GLuint uTindex = index + _mpData->n;
    GLenum eTarget = _mpData->ids[uTindex];
    if (eTarget == 0)
    {
        _mpData->ids[uTindex] = target;
    }
    else _YAGLPP_ASSERT_(eTarget == target); // OPENGL OBJECT IS ASSIGNED TO DIFFERENT TARGET
    return _mpData->ids[index];
}

void _Object::_object_assign(_Objects& objects, GLuint index, GLenum target)
{
    _YAGLPP_ASSERT_(_miId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
    _miId = objects._objects_assign(index, target);
}

void _Object::_object_share(_Object& object)
{
    GLint iId = object._miId;
    _YAGLPP_ASSERT_(_miId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
    _YAGLPP_ASSERT_(iId != 0); // OPENGL EMPTY OBJECT COULD NOT BE SHARED
    _miId = (iId < 0) ? -iId : iId;
}

GLsizei _Objects::getObjectCount()
{
    _YAGLPP_ASSERT_(_mpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    return _mpData->n;
}
#endif // #ifdef _DEBUG
} // namespace gl
