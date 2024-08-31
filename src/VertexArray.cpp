#define YAGLPP_BUILD_LIB
#include <yaglpp/VertexArray.h>
#pragma comment(lib, "opengl32.lib")
#ifdef GL_VERSION_3_0
namespace gl {
void VertexArray::bindVertexArray()
{
	GLuint uBound, uId = _object_id(glGenVertexArrays);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != uId)
	{
		glBindVertexArray(uId);
		_YAGLPP_GLAD_ERROR_;
	}
}

void VertexArray::setVertexArray(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			genVertexArray();
		}
	}
	else if (gen == GL_TRUE)
	{
		deleteVertexArray();
	}
}

void VertexArray::unbindVertexArray()
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound == uId)
	{
		glBindVertexArray(0);
		_YAGLPP_GLAD_ERROR_;
	}
}

void VertexArray::unbindTarget()
{
	GLuint uBound;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	_YAGLPP_GLAD_ERROR_;
	if (uBound != 0)
	{
		glBindVertexArray(0);
		_YAGLPP_GLAD_ERROR_;
	}
}
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
