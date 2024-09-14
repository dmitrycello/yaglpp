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
	GLsync _mpSync; // Sync object
	GLsync _sync();

public:
	/*(3.2) Constructs an empty sync object*/
	Sync()
	{
		_mpSync = nullptr;
	}

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

	/*(3.2) Retrieves the flag representing the status of the synchronization object. Used as a getter of <syncStatus> property
	@return True if synchronization object became signaled, false otherwise*/
	GLboolean getSyncStatus();

	/*(3.2) Determines if a name corresponds to a sync object. Used as a getter of <sync> property
	@return True if valid synchronization object, false otherwise*/
	GLboolean isSync()
	{
		return glIsSync(_mpSync);
	}

	/*(3.2) Sets the creation state of the sync object, only if current state is opposite. Depending of the flag value, calls <fenceSync> or <deleteSync> functions. Used as a setter of <sync> property
	@param True to generate sync object name, false to delete sync object*/
	void setSync(GLboolean gen);

	/*(3.2) Instruct the GL server to block until the specified synchronization object becomes signaled*/
	void waitSync();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-write property for creation state of the sync object*/
	__declspec(property(get = isSync, put = setSync)) GLboolean sync;

	/*(3.2) Read-only property for flag representing the status of the synchronization object*/
	__declspec(property(get = getSyncStatus)) GLboolean syncStatus;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class Sync

#ifdef YAGLPP_IMPLEMENTATION
void Sync::setSync(GLboolean gen)
{
	if (isSync())
	{
		if (gen == GL_FALSE)
		{
			deleteSync();
		}
	}
	else if (gen == GL_TRUE)
	{
		fenceSync();
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLsync Sync::_sync()
{
	YAGLPP_ASSERT(_mpSync != NULL); // OPENGL SYNC OBJECT IS EMPTY
	return _mpSync;
}

SyncStatus Sync::clientWaitSync(GLuint64 timeout)
{
	GLenum eStatus = glClientWaitSync(_sync(), GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
	YAGLPP_GLAD_ERROR;
	return (SyncStatus)eStatus;
}

void Sync::deleteSync()
{
	YAGLPP_ASSERT(_mpSync != nullptr); // OPENGL SYNC OBJECT IS EMPTY
	glDeleteSync(_mpSync);
	_mpSync = nullptr;
	YAGLPP_GLAD_ERROR;
}

void Sync::fenceSync()
{
	YAGLPP_ASSERT(_mpSync == nullptr); // OPENGL SYNC OBJECT IS NOT EMPTY
	_mpSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	YAGLPP_GLAD_ERROR;
}

GLboolean Sync::getSyncStatus()
{
	GLint iData;
	glGetSynciv(_sync(), GL_SYNC_STATUS, 1, nullptr, &iData);
	YAGLPP_GLAD_ERROR;
	return iData == GL_SIGNALED;
}

void Sync::waitSync()
{
	glWaitSync(_sync(), 0, GL_TIMEOUT_IGNORED);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLsync Sync::_sync()
{
	return _mpSync;
}

inline SyncStatus Sync::clientWaitSync(GLuint64 timeout)
{
	return (SyncStatus)glClientWaitSync(_mpSync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
}

inline void Sync::deleteSync()
{
	glDeleteSync(_mpSync); _mpSync = nullptr;
}

inline void Sync::fenceSync()
{
	_mpSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

inline GLboolean Sync::getSyncStatus()
{
	GLint i; glGetSynciv(_mpSync, GL_SYNC_STATUS, 1, nullptr, &i); return (i == GL_SIGNALED);
}

inline void Sync::waitSync()
{
	glWaitSync(_mpSync, 0, GL_TIMEOUT_IGNORED);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef GL_VERSION_3_2
