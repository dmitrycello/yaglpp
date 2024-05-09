#define GLPP_BUILD_LIB
#include <glpp/VertexArray.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_0
namespace gl {
void VertexArray::bindVertexArray()
{
	glBindVertexArray(_array_id());
	GLPP_GLAD_ERROR;
}

void VertexArray::unbindVertexArray()
{
	glBindVertexArray(0);
	GLPP_GLAD_ERROR;
}
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_0
