#define YAGLPP_BUILD_LIB
#include <yaglpp/_Query.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
void _Query::_beginQuery(GLenum target)
{
	YAGLPP_ASSERT(_getQuery(target, GL_CURRENT_QUERY) == 0); // OPENGL QUERY TARGET IS ACTIVE
	glBeginQuery(target, _query_id());
	YAGLPP_GLAD_ERROR;
}

void _Query::_endQuery(GLenum target)
{
	YAGLPP_ASSERT(_getQuery(target, GL_CURRENT_QUERY) != 0); // OPENGL QUERY TARGET IS NOT ACTIVE
	glEndQuery(target);
	YAGLPP_GLAD_ERROR;
}

GLint _Query::_getQuery(GLenum target, GLenum pname)
{
	GLint iData = 0;
	glGetQueryiv(target, pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

GLint _Query::_getQueryObject(GLenum pname)
{
	GLint iData = 0;
	glGetQueryObjectiv(_query_id(), pname, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}

#ifdef GL_VERSION_3_0
void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
	YAGLPP_GLAD_ERROR;
}

void _Query::_endConditionalRender()
{
	glEndConditionalRender();
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
void _Query::_queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
	YAGLPP_GLAD_ERROR;
}

GLint64 _Query::getQueryResult64()
{
	GLint64 iData = 0;
	glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &iData);
	YAGLPP_GLAD_ERROR;
	return iData;
}
#endif // #ifdef GL_VERSION_3_3
#endif // #ifdef _DEBUG
} // namespace gl
