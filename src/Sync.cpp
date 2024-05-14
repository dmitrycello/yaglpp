#define YAGLPP_BUILD_LIB
#include <yaglpp/Sync.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_2
namespace gl {
SyncStatus Sync::clientWaitSync(GLuint64 timeout)
{
	GLenum eStatus = glClientWaitSync(_sync_ptr(), GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
	YAGLPP_GLAD_ERROR;
	return (SyncStatus)eStatus;
}

void Sync::deleteSync()
{
	YAGLPP_ASSERT(m_pSync != nullptr); // OPENGL SYNC OBJECT IS EMPTY
	glDeleteSync(m_pSync);
	m_pSync = nullptr;
	YAGLPP_GLAD_ERROR;
}

void Sync::fenceSync()
{
	YAGLPP_ASSERT(m_pSync == nullptr); // OPENGL SYNC OBJECT IS NOT EMPTY
	m_pSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	YAGLPP_GLAD_ERROR;
}

GLboolean Sync::getSync()
{
	GLint iData = 0;
	glGetSynciv(_sync_ptr(), GL_SYNC_STATUS, 1, nullptr, &iData);
	YAGLPP_GLAD_ERROR;
	return iData == GL_SIGNALED;
}

void Sync::waitSync()
{
	glWaitSync(_sync_ptr(), 0, GL_TIMEOUT_IGNORED);
	YAGLPP_GLAD_ERROR;
}
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
