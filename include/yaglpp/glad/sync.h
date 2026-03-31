#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_SYNC_H
#define YAGLPP_SYNC_H

#ifdef YAGLPP_VERSION_3_2
namespace gl {
/*(3.2) OpenGL synchronization object root class*/
class Sync
{
public:
	enum class Status : GLenum;
	/*(3.2) (1) Constructs an empty sync object*/
	Sync()
	{
		m_Sync = nullptr;
	}

	/*(3.2) (2) Constructs a copy of sync object*/
	Sync(const Sync& source)
	{
		m_Sync = source.m_Sync;
	}

	/*(3.2) Block and wait for a synchronization object to become signaled within given timeout
	@param The timeout in nanoseconds, for which the implementation should wait for synchronization object to become signaled
	@return The synchronization status value*/
	Status ClientWait(GLuint64 timeout);

	/*(3.2) Delete synchronization object*/
	void Delete();

	/*(3.2) Create a new fence synchronization object that was previously deleted, and insert it into the GL command stream*/
	void Fence();

	/*(3.2) Retrieves the flag representing the status of the synchronization object. MSVC getter for <status> property
	@return True if synchronization object became signaled, false otherwise*/
	GLboolean GetStatus();

	/*(3.2) Checks if valid OpenGL sync object. MSVC getter for <object> property
	@return True if not an empty OpenGL sync object, false otherwise*/
	GLboolean IsObject() const
	{
		return m_Sync != nullptr;
	}

	/*(3.2) Determines if a name corresponds to a sync object. MSVC getter for <sync> property
	@return True if valid synchronization object, false otherwise*/
	GLboolean IsSync() const
	{
		return glIsSync(m_Sync);
	}

	/*(3.2) Instruct the GL server to block until the specified synchronization object becomes signaled*/
	void Wait();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.2) Read-only property to check if valid OpenGL sync object*/
	__declspec(property(get = IsObject)) GLboolean object;

	/*(3.2) Read-only property for creation state of the sync object*/
	__declspec(property(get = IsSync)) GLboolean sync;

	/*(3.2) Read-only property for flag representing the status of the synchronization object*/
	__declspec(property(get = GetStatus)) GLboolean status;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	void auto_delete() { if (IsSync()) Delete(); }
	GLsync get_sync();

private:
	GLsync m_Sync; // Sync object
}; // class Sync

/*(3.2) GLAD synchronization status enumerator*/
enum class Sync::Status : GLenum
{
	/*(3.2) Indicates that synchronization object was signaled at the time that <ClientWait> was called*/
	AlreadySignaled = GL_ALREADY_SIGNALED,

	/*(3.2) Indicates that at least timeout nanoseconds passed and synchronization object did not become signaled*/
	TimeoutExpired = GL_TIMEOUT_EXPIRED,

	/*(3.2) Indicates that synchronization object was signaled before the timeout expired*/
	ConditionSatisfied = GL_CONDITION_SATISFIED,

	/*(3.2) Indicates that an error occurred, and an OpenGL error will be generated*/
	WaitFailed = GL_WAIT_FAILED,
};

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLsync Sync::get_sync()
{
	// OPENGL SYNC OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Sync != nullptr);

	return m_Sync;
}

Sync::Status Sync::ClientWait(GLuint64 timeout)
{
	GLenum eStatus = glClientWaitSync(get_sync(), GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
	YAGLPP_GLAD_ERROR;
	return (Status)eStatus;
}

void Sync::Delete()
{
	// OPENGL SYNC OBJECT IS EMPTY
	YAGLPP_ASSERT(m_Sync != nullptr);

	glDeleteSync(m_Sync);
	YAGLPP_GLAD_ERROR;
	m_Sync = nullptr;
}

void Sync::Fence()
{
	// OPENGL SYNC OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(m_Sync == nullptr);

	m_Sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	YAGLPP_GLAD_ERROR;
}

GLboolean Sync::GetStatus()
{
	GLint iData;
	glGetSynciv(get_sync(), GL_SYNC_STATUS, 1, nullptr, &iData);
	YAGLPP_GLAD_ERROR;
	return iData == GL_SIGNALED;
}

void Sync::Wait()
{
	glWaitSync(get_sync(), 0, GL_TIMEOUT_IGNORED);
	YAGLPP_GLAD_ERROR;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLsync Sync::get_sync()
{
	return m_Sync;
}

inline Sync::Status Sync::ClientWait(GLuint64 timeout)
{
	return (Status)glClientWaitSync(m_Sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
}

inline void Sync::Delete()
{
	glDeleteSync(m_Sync); m_Sync = nullptr;
}

inline void Sync::Fence()
{
	m_Sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

inline GLboolean Sync::GetStatus()
{
	GLint i; glGetSynciv(m_Sync, GL_SYNC_STATUS, 1, nullptr, &i); return i == GL_SIGNALED;
}

inline void Sync::Wait()
{
	glWaitSync(m_Sync, 0, GL_TIMEOUT_IGNORED);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_2
#endif // #ifndef YAGLPP_SYNC_H
