#define YAGLPP_BUILD_LIB
#include <yaglpp/_Object.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void _Object::_object_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
    if (m_iId < 0)
    {
        GLuint uId = -(m_iId);
        pfnDelete(1, &uId); // glDelete..
        _YAGLPP_GLAD_ERROR_;
    }
    m_iId = 0;
}

void _Object::_object_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param)
{
    if (m_iId >= 0)
    {
        GLuint uId;
        pfnGen((GLsizei)param, &uId); // glGen..
        _YAGLPP_GLAD_ERROR_;
        m_iId = -((GLint)uId);
    }
}

GLuint _Object::_object_id(YAGLPP_GLAD_PFNGEN pfnGen, GLenum param)
{
    GLuint uId;
    if (m_iId > 0)
    {
        return m_iId;
    }
    if (m_iId < 0)
    {
        return -(m_iId);
    }
    pfnGen((GLsizei)param, &uId); // glGen..
    _YAGLPP_GLAD_ERROR_;
    m_iId = -((GLint)uId);
    return uId;
}

void _Objects::_objects_delete(YAGLPP_GLAD_PFNDELETE pfnDelete)
{
    _YAGLPP_ASSERT_(m_lpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    pfnDelete(m_lpData->n, m_lpData->ids); // glDelete..
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(m_lpData);
    m_lpData = nullptr;
}

void _Objects::_objects_gen(YAGLPP_GLAD_PFNGEN pfnGen, GLsizei n)
{
    _YAGLPP_ASSERT_(m_lpData == nullptr); // OPENGL MULTI-OBJECT IS NOT EMPTY

#ifdef _DEBUG
    m_lpData = (_LPDATA)_YAGLPP_CALLOC_(sizeof(_DATA) + n * sizeof(GLuint) * 2);
#else // #ifdef _DEBUG
    m_lpData = (_LPDATA)_YAGLPP_MALLOC_(sizeof(_DATA) + n * sizeof(GLuint));
#endif // #ifdef _DEBUG

    m_lpData->n = n;
    pfnGen(n, m_lpData->ids); // glGen..
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
    memcpy(lpNew->ids, m_lpData->ids, iSize);

#ifdef _DEBUG
    memcpy(&lpNew->ids[iNew], &m_lpData->ids[iOld], iSize);
#endif // #ifdef _DEBUG

    iSize = ((size_t)iOld - (size_t)pos) * sizeof(GLint);
    memcpy(&lpNew->ids[pos + n], &m_lpData->ids[pos], iSize);

#ifdef _DEBUG
    memcpy(&lpNew->ids[iNew + pos + n], &m_lpData->ids[iOld + pos], iSize);
#endif // #ifdef _DEBUG

    pfnGen(n, &lpNew->ids[pos]); // glGen..
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(m_lpData);
    m_lpData = lpNew;
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
    memcpy(lpNew->ids, m_lpData->ids, iSize);

#ifdef _DEBUG
    memcpy(&lpNew->ids[iNew], &m_lpData->ids[iOld], iSize);
#endif // #ifdef _DEBUG

    iSize = ((size_t)iOld - (size_t)pos - (size_t)n) * sizeof(GLint);
    memcpy(&lpNew->ids[pos], &m_lpData->ids[pos + n], iSize);

#ifdef _DEBUG
    memcpy(&lpNew->ids[iNew + pos], &m_lpData->ids[iOld + pos + n], iSize);
#endif // #ifdef _DEBUG

    pfnDelete(n, &m_lpData->ids[pos]); // glDelete..
    _YAGLPP_GLAD_ERROR_;
    _YAGLPP_FREE_(m_lpData);
    m_lpData = lpNew;
}

#ifdef _DEBUG
GLuint _Objects::_objects_assign(GLuint index, GLenum target)
{
    _YAGLPP_ASSERT_(getObjectCount() > (GLsizei)index); // OPENGL OBJECT INDEX IS INVALID
    GLuint uTindex = index + m_lpData->n;
    GLenum eTarget = m_lpData->ids[uTindex];
    if (eTarget == 0)
    {
        m_lpData->ids[uTindex] = target;
    }
    else _YAGLPP_ASSERT_(eTarget == target); // OPENGL OBJECT IS ASSIGNED TO DIFFERENT TARGET
    return m_lpData->ids[index];
}

void _Object::_object_assign(_Objects& objects, GLuint index, GLenum target)
{
    _YAGLPP_ASSERT_(m_iId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
    m_iId = objects._objects_assign(index, target);
}

void _Object::_object_share(_Object& object)
{
    GLint iId = object.m_iId;
    _YAGLPP_ASSERT_(m_iId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
    _YAGLPP_ASSERT_(iId != 0); // OPENGL EMPTY OBJECT COULD NOT BE SHARED
    m_iId = (iId < 0) ? -iId : iId;
}

GLsizei _Objects::getObjectCount()
{
    _YAGLPP_ASSERT_(m_lpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    return m_lpData->n;
}
#endif // #ifdef _DEBUG
} // namespace gl
