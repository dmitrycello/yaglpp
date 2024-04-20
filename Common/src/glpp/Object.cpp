#define GLPP_BUILD_LIB
#include <glpp/_Object.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
void _Object::_object_delete(GLPP_GLAD_PFNDELETE pfnDelete)
{
    if (m_iId < 0)
    {
        GLuint uId = -(m_iId);
        pfnDelete(1, &uId); // glDelete..
        GLPP_GLAD_ERROR;
    }
    m_iId = 0;
}

void _Object::_object_gen(GLPP_GLAD_PFNGEN pfnGen)
{
    if (m_iId >= 0)
    {
        GLuint uId;
        pfnGen(1, &uId); // glGen..
        GLPP_GLAD_ERROR;
        m_iId = -((GLint)uId);
    }
}

GLuint _Object::_object_id(GLPP_GLAD_PFNGEN pfnGen)
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
    pfnGen(1, &uId); // glGen..
    GLPP_GLAD_ERROR;
    m_iId = -((GLint)uId);
    return uId;
}

void _Objects::_objects_append(GLPP_GLAD_PFNGEN pfnGen, GLuint num)
{
    GLPP_ASSERT(num > 0); // OBJECT NUM VALUE MUST BE GREATER THAN ZERO
    GLuint uOld = getObjectNum();
    GLuint uNew = uOld + num;

#ifdef _DEBUG
    _LPDATA lpNew = (_LPDATA)GLPP_CALLOC(sizeof(_DATA) + uNew * (sizeof(GLuint) * 2));
    size_t iSize = uOld * sizeof(GLuint);
    void* pDst1 = lpNew->ids;
    void* pSrc1 = m_lpData->ids;
    memcpy(pDst1, pSrc1, iSize);
    void* pDst2 = &lpNew->ids[uNew];
    void* pSrc2 = &m_lpData->ids[uOld];
    memcpy(pDst2, pSrc2, iSize);
    GLPP_FREE(m_lpData);
    m_lpData = lpNew;

#else // #ifdef _DEBUG
    m_lpData = (_LPDATA)GLPP_REALLOC(m_lpData, sizeof(_DATA) + uNew * sizeof(GLuint));
#endif // #ifdef _DEBUG

    m_lpData->num = uNew;
    pfnGen(num, &(m_lpData->ids[uOld])); // glGen..
    GLPP_GLAD_ERROR;
}

void _Objects::_objects_delete(GLPP_GLAD_PFNDELETE pfnDelete)
{
    GLPP_ASSERT(m_lpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    pfnDelete(m_lpData->num, m_lpData->ids); // glDelete..
    GLPP_GLAD_ERROR;
    GLPP_FREE(m_lpData);
    m_lpData = nullptr;
}

void _Objects::_objects_gen(GLPP_GLAD_PFNGEN pfnGen, GLuint num)
{
    GLPP_ASSERT(m_lpData == nullptr); // OPENGL MULTI-OBJECT IS NOT EMPTY

#ifdef _DEBUG
    m_lpData = (_LPDATA)GLPP_CALLOC(sizeof(_DATA) + num * sizeof(GLuint) * 2);
#else // #ifdef _DEBUG
    m_lpData = (_LPDATA)GLPP_MALLOC(sizeof(_DATA) + num * sizeof(GLuint));
#endif // #ifdef _DEBUG

    m_lpData->num = num;
    pfnGen(num, m_lpData->ids); // glGen..
    GLPP_GLAD_ERROR;
}

#ifdef _DEBUG
GLuint _Objects::_objects_assign(GLuint index, GLenum target)
{
    GLPP_ASSERT(getObjectNum() > index); // OPENGL OBJECT INDEX IS INVALID
    GLuint uTindex = index + m_lpData->num;
    GLenum eTarget = m_lpData->ids[uTindex];
    if (eTarget == 0)
    {
        m_lpData->ids[uTindex] = target;
    }
    else GLPP_ASSERT(eTarget == target); // OPENGL OBJECT IS ASSIGNED TO DIFFERENT TARGET
    return m_lpData->ids[index];
}

void _Object::_object_assign(_Objects& objects, GLuint index, GLenum target)
{
    GLPP_ASSERT(m_iId >= 0); // OPENGL SINGLE OBJECT NAME WAS NOT CLEARED
    m_iId = objects._objects_assign(index, target);
}

GLuint _Objects::getObjectNum()
{
    GLPP_ASSERT(m_lpData != nullptr); // OPENGL MULTI-OBJECT IS EMPTY
    return m_lpData->num;
}
#endif // #ifdef _DEBUG
} // namespace gl
