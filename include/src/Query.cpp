#define YAGLPP_BUILD_LIB
#include <yaglpp/_Query.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
void _Query::_beginQuery(GLenum target)
{
	_YAGLPP_ASSERT_(_getQuery(target, GL_CURRENT_QUERY) == 0); // OPENGL QUERY TARGET IS ACTIVE
	glBeginQuery(target, _query_id());
	_YAGLPP_GLAD_ERROR_;
}

void _Query::_endQuery(GLenum target)
{
	_YAGLPP_ASSERT_(_getQuery(target, GL_CURRENT_QUERY) != 0); // OPENGL QUERY TARGET IS NOT ACTIVE
	glEndQuery(target);
	_YAGLPP_GLAD_ERROR_;
}

GLint _Query::_getQuery(GLenum target, GLenum pname)
{
	GLint iData = 0;
	glGetQueryiv(target, pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

GLint _Query::_getQueryObject(GLenum pname)
{
	GLint iData = 0;
	glGetQueryObjectiv(_query_id(), pname, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}

#ifdef GL_VERSION_3_0
void _Query::_beginConditionalRender(QueryConditionalRenderMode mode)
{
	glBeginConditionalRender(_query_id(), (GLenum)mode);
	_YAGLPP_GLAD_ERROR_;
}

void _Query::_endConditionalRender()
{
	glEndConditionalRender();
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
void _Query::_queryCounter()
{
	glQueryCounter(_query_id(), GL_TIMESTAMP);
	_YAGLPP_GLAD_ERROR_;
}

GLint64 _Query::getQueryResult64()
{
	GLint64 iData = 0;
	glGetQueryObjecti64v(_query_id(), GL_QUERY_RESULT, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData;
}
#endif // #ifdef GL_VERSION_3_3
#endif // #ifdef _DEBUG
} // namespace gl
