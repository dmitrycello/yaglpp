#define YAGLPP_BUILD_LIB
#include <yaglpp/VertexArray.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_0
namespace gl {
void VertexArray::bindVertexArray()
{
	glBindVertexArray(_array_id());
	_YAGLPP_GLAD_ERROR_;
}

void VertexArray::unbindVertexArray()
{
	glBindVertexArray(0);
	_YAGLPP_GLAD_ERROR_;
}
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_0
