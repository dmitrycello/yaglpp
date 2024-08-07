#pragma once
#include "gladpp.h"
#ifdef GL_VERSION_3_2
namespace gl {
/*(3.2) GLAD synchronization status enumerator*/
enum class SyncStatus : GLenum
{
	/*(3.2) Indicates that synchronization object was signaled at the time that <clientWaitSync> was called*/
	AlreadySignaled = GL_ALREADY_SIGNALED,

	/*(3.2) Indicates that at least timeout nanoseconds passed and synchronization object did not become signaled*/
	TimeoutExpired = GL_TIMEOUT_EXPIRED,

	/*(3.2) Indicates that synchronization object was signaled before the timeout expired*/
	ConditionSatisfied = GL_CONDITION_SATISFIED,

	/*(3.2) Indicates that an error occurred, and an OpenGL error will be generated*/
	WaitFailed = GL_WAIT_FAILED,
};

/*(3.2) OpenGL synchronization object root class*/
class Sync
{
private:
	GLsync _mpSync = nullptr; // Sync object
	GLsync _sync_ptr()
	{
		if (_mpSync == nullptr)
		{
			fenceSync();
		}
		return _mpSync;
	}

public:
	/*(3.2) Constructs an empty sync object*/
	Sync() {}

	/*(3.2) Cleans up the valid synchronization object*/
	~Sync()
	{
		if (isSync())
		{
			deleteSync();
		}
	}

	/*(3.2) Block and wait for a synchronization object to become signaled within given timeout
	@param The timeout in nanoseconds, for which the implementation should wait for synchronization object to become signaled
	@return The synchronization status value*/
	SyncStatus clientWaitSync(GLuint64 timeout);

	/*(3.2) Delete synchronization object*/
	void deleteSync();

	/*(3.2) Create a new fence synchronization object that was previously deleted, and insert it into the GL command stream*/
	void fenceSync();

	/*(3.2) Returns the maximum timeout interval used by sync object
	@return The maximum sync timeout interval*/
	static GLuint getMaxServerWaitTimeout()
	{
		return _getInteger(GL_MAX_SERVER_WAIT_TIMEOUT);
	}

	/*(3.2) Retrieves flag representing the status of the synchronization object
	@return True if synchronization object became signaled, false otherwise*/
	GLboolean getSync();

	/*(3.2) Determines via API if an object name corresponds to a sync object
	@return True if valid synchronization object, false otherwise*/
	GLboolean isSync()
	{
		return glIsSync(_mpSync);
	}

	/*(3.2) Instruct the GL server to block until the specified synchronization object becomes signaled*/
	void waitSync();
}; // class Sync

#ifndef _DEBUG
inline SyncStatus Sync::clientWaitSync(GLuint64 timeout)
{
	return (SyncStatus)glClientWaitSync(_sync_ptr(), GL_SYNC_FLUSH_COMMANDS_BIT, timeout);;
}

inline void Sync::deleteSync()
{
	glDeleteSync(_mpSync);
	_mpSync = nullptr;
}

inline void Sync::fenceSync()
{
	_mpSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

inline GLboolean Sync::getSync()
{
	GLint i; glGetSynciv(_sync_ptr(), GL_SYNC_STATUS, 1, nullptr, &i); return (i == GL_SIGNALED);
}

inline void Sync::waitSync()
{
	glWaitSync(_sync_ptr(), 0, GL_TIMEOUT_IGNORED);
}
#endif // #ifndef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_2
