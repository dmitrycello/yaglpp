#pragma once
#include "gladpp.h"
#include "_Buffer.h"
#ifdef GL_VERSION_3_1
namespace gl {
/*(3.1) OpenGL texture buffer object class (TBO) derived from <_Buffer>*/
class TextureBuffer : public _Buffer
{
public:
	/*(3.1) (1) Constructs an empty buffer object*/
	TextureBuffer() {}

	/*(3.1) (2) Constucts a buffer object with <shareBuffer>*/
	TextureBuffer(TextureBuffer& buffer)
	{
		shareBuffer(buffer);
	}

	/*(3.1) (3) Constucts a buffer object with <assignBuffer>*/
	TextureBuffer(Buffers& buffers, GLuint index)
	{
		assignBuffer(buffers, index);
	}

	/*(3.1) Set an empty buffer object as a reference to an element of the buffer multi-object
	@param The buffer multi-object
	@param The index of the object name*/
	void assignBuffer(Buffers& buffers, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)buffers, index, GL_TEXTURE_BUFFER);
#else // #ifdef _DEBUG
		_object_assign((_Objects&)buffers, index);
#endif // #ifdef _DEBUG
	}

	/*(3.1) Explicitly binds buffer object to its target*/
	void bindBuffer()
	{
		_buffer_rebind(_tlsTextureBuffer(), GL_TEXTURE_BUFFER);
	}

	/*(3.1) Explicitly binds buffer object to copy-read target, the previous binding is lost*/
	void bindCopyReadBuffer()
	{
		_buffer_copy(_tlsTextureBuffer(), _tlsCopyReadBuffer(), GL_COPY_READ_BUFFER);
	}

	/*(3.1) Explicitly binds buffer object to copy-write target, the previous binding is lost*/
	void bindCopyWriteBuffer()
	{
		_buffer_copy(_tlsTextureBuffer(), _tlsCopyWriteBuffer(), GL_COPY_WRITE_BUFFER);
	}

	/*(3.1) (1) Creates and initializes buffer object data store with the valid DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void bufferData(DataStore& dataStore, BufferUsage usage)
	{
		_bufferData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, (GLsizeiptr)dataStore.getSize(), dataStore.getData(), (GLenum)usage);
	}

	/*(3.1) (2) Creates and initializes buffer object's data store
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void bufferData(GLsizeiptr size, _Pre_maybenull_ const void* data, BufferUsage usage)
	{
		_bufferData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, size, data, (GLenum)usage);
	}

	/*(3.1) (1) Updates a subset of a buffer object data store from DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer*/
	void bufferSubData(DataStore& data)
	{
		_bufferSubData(_tlsArrayBuffer(), GL_TEXTURE_BUFFER, 0, data.getSize(), data.getData());
	}

	/*(3.1) (2) Updates a subset of a buffer object data store from a part of DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer
	@param Specifies the integer offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the integer size in bytes of the data store region being replaced*/
	void bufferSubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		_bufferSubData(_tlsArrayBuffer(), GL_TEXTURE_BUFFER, offset, size, data.getSubData((int)offset, (int)size));
	}

	/*(3.1) (3) Updates a subset of a buffer object's data store
	@param Specifies the integer offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the integer size in bytes of the data store region being replaced
	@param [in] Specifies a pointer to the new data that will be copied into the data store*/
	void bufferSubData(GLintptr offset, GLsizeiptr size, _Pre_notnull_ const void* data)
	{
		_bufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, offset, size, data);
	}

	/*(3.1) (1) Copies all or part of the data store of a buffer object into the data store of the ArrayBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(ArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsArrayBuffer(), GL_ARRAY_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (2) Copies all or part of the data store of a buffer object into the data store of the ElementArrayBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(ElementArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsElementArrayBuffer(), GL_ELEMENT_ARRAY_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (3) Copies all or part of the data store of a buffer object into the data store of the PixelPackBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(PixelPackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsPixelPackBuffer(), GL_PIXEL_PACK_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (4) Copies all or part of the data store of a buffer object into the data store of the PixelUnackBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(PixelUnpackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsPixelUnpackBuffer(), GL_PIXEL_UNPACK_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
 	}

	/*(3.1) (5) Copies all or part of the data store of a buffer object into the data store of the TransformFeedbackBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(TransformFeedbackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsTransformFeedbackBuffer(), GL_TRANSFORM_FEEDBACK_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (6) Copies all or part of the data store of a buffer object into the data store of the TextureBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(TextureBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		GLuint* tls = _tlsTextureBuffer();
		_copyBufferSubData(tls, GL_TEXTURE_BUFFER, tls, GL_TEXTURE_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (7) Copies all or part of the data store of a buffer object into the data store of the UniformBuffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(UniformBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, _tlsUniformBuffer(), GL_UNIFORM_BUFFER, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (1) Directly binds and initializes buffer object using copy-write target with the valid DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void copyWriteBufferData(DataStore& dataStore, BufferUsage usage)
	{
		_copyWriteBufferData(_tlsTextureBuffer(), (GLsizeiptr)dataStore.getSize(), dataStore.getData(0), (GLenum)usage);
	}

	/*(3.1) (2) Directly binds and initializes buffer object using copy-write target
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void copyWriteBufferData(GLsizeiptr size, _Pre_maybenull_ const void* data, BufferUsage usage)
	{
		_copyWriteBufferData(_tlsTextureBuffer(), size, data, (GLenum)usage);
	}

	/*(3.1) Indicates modifications to a range of a mapped buffer
	@param Specifies the start of the buffer subrange, in basic machine units
	@param Specifies the length of the buffer subrange, in basic machine units*/
	void flushMappedBufferRange(GLintptr offset, GLsizeiptr length)
	{
		_flushMappedBufferRange(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, offset, length);
	}

	/*(3.1) Gets the access policy parameter value set while mapping the buffer object, the value of the access parameter enum passed to <MapBuffer>. If the buffer was mapped with <mapBufferRange>, the access policy is determined by translating the bits in that access parameter to one of the supported enums for <mapBuffer> as described in the OpenGL specification
	@return The buffer access policy enumerator*/
	BufferAccess getBufferAccess()
	{
		return (BufferAccess)_getBufferParameter(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_ACCESS);
	}

	/*(3.1) Gets the access policy flag parameter value set while mapping the buffer object (the value of the access parameter bitfield passed to <mapBufferRange>). If the buffer was mapped with <mapBuffer>, the access policy is determined by translating the enums in that access parameter to the corresponding bits for <mapBufferRange> as described in the OpenGL Specification. The initial value is zero
	@return The buffer access policy flag bitmask enumerator*/
	BufferFlags getBufferAccessFlags()
	{
		return (BufferFlags)_getBufferParameter(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_ACCESS_FLAGS);
	}

	/*(3.1) Gets a parameter flag indicating whether the buffer object is currently mapped. The initial value is false
	@return The mapped flag*/
	GLboolean getBufferMapped()
	{
		return _getBufferParameter(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_MAPPED);
	}

	/*(3.1) Returns the pointer to a mapped buffer object's data store
	@return The pointer to a mapped buffer object's data store, or NULL if the named buffer is unmapped*/
	_Ret_maybenull_ void* getBufferPointer()
	{
		return _getBufferPointer(_tlsTextureBuffer(), GL_TEXTURE_BUFFER);
	}

	/*(3.1) Gets the size of the buffer object parameter value, measured in bytes. The initial value is 0
	@return The size of the buffer object*/
	GLint getBufferSize()
	{
		return _getBufferParameter(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_SIZE);
	}

	/*(3.1) (1) Returns a subset of a buffer object into DataStore object
	@param Specifies the associated DataStore object who's region will receive the buffer object data
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned*/
	void getBufferSubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		_getBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, offset, size, data.getSubData((int)offset, (int)size));
	}

	/*(3.1) (2) Returns a subset of a buffer object's data store
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned
	@param [out] Specifies a pointer to the location where buffer object data is returned*/
	void getBufferSubData(GLintptr offset, GLsizeiptr size, _Out_ void* data)
	{
		_getBufferSubData(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, offset, size, data);
	}

	/*(3.1) Gets the buffer object's usage pattern parameter value. The initial value is <StaticDraw>
	@return Buffer expected usage pattern enumerator*/
	BufferUsage getBufferUsage()
	{
		return (BufferUsage)_getBufferParameter(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_USAGE);
	}

	/*(3.1) The maximum number of texels allowed in the texel array of a texture buffer object
	@param The maximum allowed number of texels. Value must be at least 65536*/
	static GLsizei getMaxTextureBufferSize()
	{
		return _getInteger(GL_MAX_TEXTURE_BUFFER_SIZE);
	}

	/*(3.1) Determines if the buffer object is currently bound to its target. Used as a getter of <bufferBinding> property
	@return True if buffer object currently bound to its target, or false otherwise*/
	GLboolean isBufferBinding()
	{
		return _object_id() == _getInteger(GL_TEXTURE_BUFFER_BINDING);
	}

	/*(3.1) Maps all of a buffer object's data store into the client's address space
	@param Specifies the buffer access policy enumerator
	@return A pointer to the beginning of the buffer mapped range*/
	_Ret_maybenull_ void* mapBuffer(BufferAccess access)
	{
		return _mapBuffer(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, (GLenum)access);
	}

	/*(3.1) Maps all or part of a buffer object's data store into the client's address space
	@param Specifies the starting offset within the buffer of the range to be mapped
	@param Specifies the length of the range to be mapped
	@param Specifies a combination bitmask enumerator of access buffer flags indicating the desired access to the mapped range*/
	_Ret_maybenull_ void* mapBufferRange(GLintptr offset, GLsizeiptr length, BufferFlags access)
	{
		return _mapBufferRange(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, offset, length, (GLbitfield)access);
	}

	/*(3.1) Set an empty buffer object as a reference to the buffer object from another context
	@param The buffer object to share, must not be empty*/
	void shareBuffer(TextureBuffer& buffer)
	{
		_object_share((_Object&)buffer);
	}

	/*(3.1) Unbinds any previously bound buffer object, and restores client memory usage for that buffer object target. Does nothing if no such buffer is bound*/
	static void unbindBuffer()
	{
		_buffer_unbind(_tlsTextureBuffer(), GL_TEXTURE_BUFFER);
	}

	/*(3.1) Releases the mapping of a buffer object's data store into the client's address space
	@return True unless the data store contents have become corrupt during the time the data store was mapped*/
	GLboolean unmapBuffer()
	{
		return _unmapBuffer(_tlsTextureBuffer(), GL_TEXTURE_BUFFER);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.1) Read-only property for access policy parameter value set while mapping the buffer object*/
	__declspec(property(get = getBufferAccess)) BufferAccess bufferAccess;

	/*(3.1) Read-only property for access policy flag parameter set while mapping the buffer object*/
	__declspec(property(get = getBufferAccessFlags)) BufferFlags bufferAccessFlags;

	/*(3.1) Read-only property to determine if the buffer object is currently bound to its target*/
	__declspec(property(get = isBufferBinding)) GLboolean bufferBinding;

	/*(3.1) Read-only property for parameter flag indicating whether the buffer object is currently mapped*/
	__declspec(property(get = getBufferMapped)) GLboolean bufferMapped;

	/*(3.1) Read-only property for size parameter value of the buffer object parameter value*/
	__declspec(property(get = getBufferSize)) GLint bufferSize;

	/*(3.1) Read-only property for buffer object's usage pattern parameter*/
	__declspec(property(get = getBufferUsage)) BufferUsage bufferUsage;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef GL_VERSION_3_2
	/*(3.2) Gets the length parameter value of the mapping into the buffer object established with <mapBuffer>. The initial value is zero
	@return The 64-bit length of the buffer mapping*/
	GLsizeiptr getBufferMapLength()
	{
		return (GLsizeiptr)_getBufferParameter64(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_MAP_LENGTH);
	}

	/*(3.2) Gets the offset parameter value of the mapping into the buffer object established with <mapBuffer>. The initial value is zero
	@return The 64-bit offset of the buffer mapping*/
	GLintptr getBufferMapOffset()
	{
		return (GLintptr)_getBufferParameter64(_tlsTextureBuffer(), GL_TEXTURE_BUFFER, GL_BUFFER_MAP_OFFSET);
	}
#endif // #ifdef GL_VERSION_3_2
}; // class TextureBuffer : public _Buffer
} // namespace gl
#endif // #ifdef GL_VERSION_3_1
