#define YAGLPP_BUILD_LIB
#include <yaglpp/Sync.h>
#pragma comment(lib, "opengl32.lib")
#if defined _DEBUG && defined GL_VERSION_3_2
namespace gl {
SyncStatus Sync::clientWaitSync(GLuint64 timeout)
{
	GLenum eStatus = glClientWaitSync(_sync(), GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
	_YAGLPP_GLAD_ERROR_;
	return (SyncStatus)eStatus;
}

void Sync::deleteSync()
{
	_YAGLPP_ASSERT_(_mpSync != nullptr); // OPENGL SYNC OBJECT IS EMPTY
	glDeleteSync(_mpSync);
	_mpSync = nullptr;
	_YAGLPP_GLAD_ERROR_;
}

void Sync::fenceSync()
{
	_YAGLPP_ASSERT_(_mpSync == nullptr); // OPENGL SYNC OBJECT IS NOT EMPTY
	_mpSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	_YAGLPP_GLAD_ERROR_;
}

GLboolean Sync::getSyncStatus()
{
	GLint iData = 0;
	glGetSynciv(_sync(), GL_SYNC_STATUS, 1, nullptr, &iData);
	_YAGLPP_GLAD_ERROR_;
	return iData == GL_SIGNALED;
}

void Sync::waitSync()
{
	glWaitSync(_sync(), 0, GL_TIMEOUT_IGNORED);
	_YAGLPP_GLAD_ERROR_;
}

#ifdef _DEBUG
GLsync Sync::_sync()
{
	_YAGLPP_ASSERT_(_mpSync != NULL); // OPENGL SYNC OBJECT IS EMPTY
	return _mpSync;
}
#endif // #ifdef _DEBUG
} // namespace gl
#endif // #if defined _DEBUG && defined GL_VERSION_3_2
