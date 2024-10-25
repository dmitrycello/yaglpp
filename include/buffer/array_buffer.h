#pragma once
#include <yaglpp/buffer/_buffer.h>
namespace gl {
/*OpenGL array buffer or vertex buffer object class (VBO) derived from <_Buffer>*/
class ArrayBuffer : public _Buffer
{
private:
	ArrayBuffer(GLint name) { _object_set(name); }

public:
	/*(1) Constructs an empty buffer object*/
	ArrayBuffer() {}

	/*(2) Constructs a copy of buffer object*/
	ArrayBuffer(const ArrayBuffer& buffer)
	{
		_buffer_dup((_Object&)buffer);
	}

	/*Explicitly binds buffer object to its target. Does nothing if specified buffer is bound*/
	void bindBuffer()
	{
		_bindBuffer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
	}

	/*(1) Creates and initializes buffer object data store with the valid DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void bufferData(DataStore& dataStore, BufferUsage usage)
	{
		_bufferData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, (GLenum)usage, dataStore);
	}

	/*(2) Creates and initializes buffer object's data store
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void bufferData(GLsizeiptr size, _Pre_maybenull_ const void* data, BufferUsage usage)
	{
		_bufferData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, size, data, (GLenum)usage);
	}

	/*(1) Updates a subset of a buffer object data store from DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer*/
	void bufferSubData(DataStore& data)
	{
		_bufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, data);
	}

	/*(2) Updates a subset of a buffer object data store from a part of DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer
	@param Specifies the integer offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the integer size in bytes of the data store region being replaced*/
	void bufferSubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		_bufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, size, data);
	}

	/*(3) Updates a subset of a buffer object's data store
	@param Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the size in bytes of the data store region being replaced
	@param [in] Specifies a pointer to the new data that will be copied into the data store*/
	void bufferSubData(GLintptr offset, GLsizeiptr size, _Pre_notnull_ const void* data)
	{
		_bufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, size, data);
	}

	/*Duplicates a buffer object. If the source is a single object, its reference flag become true, while setting the destination as a single object (reference flag transfer)
	@param Specifies the source buffer object*/
	void duplicateBuffer(const ArrayBuffer& buffer)
	{
		_buffer_dup((_Object&)buffer);
	}

	/*Gets the access policy parameter value set while mapping the buffer object, the value of the access parameter enum passed to <MapBuffer>. If the buffer was mapped with <mapBufferRange>, the access policy is determined by translating the bits in that access parameter to one of the supported enums for <mapBuffer> as described in the OpenGL specification. Used as a getter of <bufferAccess> property
	@return The buffer access policy enumerator*/
	BufferAccess getBufferAccess()
	{
		return (BufferAccess)_getBufferParameter(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_ACCESS);
	}

	/*Returns a reference buffer object currently bound to its target
	@return The reference buffer object, or empty object*/
	static ArrayBuffer getBufferBinding()
	{
		return ArrayBuffer(_getInteger(GL_ARRAY_BUFFER_BINDING));
	}

	/*Gets a parameter flag indicating whether the buffer object is currently mapped. Used as a getter of <bufferMapped> property
	@return The mapped flag. The initial value is false*/
	GLboolean getBufferMapped()
	{
		return _getBufferParameter(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_MAPPED);
	}

	/*Returns the pointer to a mapped buffer object's data store
	@return The pointer to a mapped buffer object's data store, or NULL if the named buffer is unmapped*/
	_Ret_maybenull_ void* getBufferPointer()
	{
		return _getBufferPointer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
	}

	/*Gets the size parameter value of the buffer object parameter value, measured in bytes. Used as a getter of <bufferSize> property
	@return The size of the buffer object. The initial value is 0*/
	GLint getBufferSize()
	{
		return _getBufferParameter(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_SIZE);
	}

	/*(1) Returns a subset of a buffer object into DataStore object
	@param Specifies the associated DataStore object who's region will receive the buffer object data
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned*/
	void getBufferSubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		_getBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, size, data);
	}

	/*(2) Returns a subset of a buffer object's data store
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned
	@param [out] Specifies a pointer to the location where buffer object data is returned*/
	void getBufferSubData(GLintptr offset, GLsizeiptr size, _Out_ void* data)
	{
		_getBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, size, data);
	}

	/*Gets the buffer object's usage pattern parameter value. Used as a getter of <bufferUsage> property
	@return The buffer expected usage pattern enumerator. The initial value is <StaticDraw>*/
	BufferUsage getBufferUsage()
	{
		return (BufferUsage)_getBufferParameter(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_USAGE);
	}

	/*Determines if the buffer object is currently bound to its target. Used as a getter of <bufferBinding> property
	@return True if buffer object currently bound to its target, or false otherwise*/
	GLboolean isBufferBinding() const
	{
		return _object_binding(GL_ARRAY_BUFFER_BINDING);
	}

	/*Maps all of a buffer object's data store into the client's address space
	@param Specifies the buffer access policy enumerator
	@return A pointer to the beginning of the buffer mapped range*/
	_Ret_maybenull_ void* mapBuffer(BufferAccess access)
	{
		return _mapBuffer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, (GLenum)access);
	}

	/*Makes a reference of a buffer object, regardless of the source object's reference flag
	@param Specifies the source buffer object*/
	void referenceBuffer(const ArrayBuffer& buffer)
	{
		_buffer_ref((_Object&)buffer);
	}

	/*Sets the binding state of the buffer object, only if current state is opposite. Used as a setter of <bufferBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setBufferBinding(GLboolean bind)
	{
		_buffer_set(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, bind);
	}

	/*Explicitly unbinds specified buffer object from its target. Does nothing if specified buffer is not bound*/
	void unbindBuffer()
	{
		_unbindBuffer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
	}

	/*Explicitly unbinds any buffer object of specified type bound to its target. Does nothing if no such buffer is bound*/
	static void unbindTarget()
	{
		_unbindTarget(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
	}

	/*Releases the mapping of a buffer object's data store into the client's address space
	@return True unless the data store contents have become corrupt during the time the data store was mapped*/
	GLboolean unmapBuffer()
	{
		return _unmapBuffer(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for access policy parameter value set while mapping the buffer object*/
	__declspec(property(get = getBufferAccess)) BufferAccess bufferAccess;

	/*Read-write property for state of the buffer binding*/
	__declspec(property(get = isBufferBinding, put = setBufferBinding)) GLboolean bufferBinding;

	/*Read-only property for parameter flag indicating whether the buffer object is currently mapped*/
	__declspec(property(get = getBufferMapped)) GLboolean bufferMapped;

	/*Read-only property for size parameter value of the buffer object parameter value*/
	__declspec(property(get = getBufferSize)) GLint bufferSize;

	/*Read-only property for buffer object's usage pattern parameter*/
	__declspec(property(get = getBufferUsage)) BufferUsage bufferUsage;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Indicates modifications to a range of a mapped buffer
	@param Specifies the start of the buffer subrange, in basic machine units
	@param Specifies the length of the buffer subrange, in basic machine units*/
	void flushMappedBufferRange(GLintptr offset, GLsizeiptr length)
	{
		_flushMappedBufferRange(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, length);
	}

	/*(3.0) Gets the access policy flag parameter set while mapping the buffer object (the value of the access parameter bitfield passed to <mapBufferRange>). If the buffer was mapped with <mapBuffer>, the access policy is determined by translating the enums in that access parameter to the corresponding bits for <mapBufferRange> as described in the OpenGL Specification. Used as a getter of <bufferAccessFlags> property
	@return The buffer access policy flag bitmask enumerator. The initial value is zero*/
	BufferFlags getBufferAccessFlags()
	{
		return (BufferFlags)_getBufferParameter(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_ACCESS_FLAGS);
	}

	/*(3.0) Maps all or part of a buffer object's data store into the client's address space
	@param Specifies the starting offset within the buffer of the range to be mapped
	@param Specifies the length of the range to be mapped
	@param Specifies a combination bitmask enumerator of access buffer flags indicating the desired access to the mapped range*/
	_Ret_maybenull_ void* mapBufferRange(GLintptr offset, GLsizeiptr length, BufferFlags access)
	{
		return _mapBufferRange(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, offset, length, (GLbitfield)access);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property for access policy flag parameter set while mapping the buffer object*/
	__declspec(property(get = getBufferAccessFlags)) BufferFlags bufferAccessFlags;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) (1) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(ArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (2) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(ElementArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (3) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(PixelPackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (4) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(PixelUnpackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (5) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(TransformFeedbackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_TRANSFORM_FEEDBACK_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (6) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(TextureBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}

	/*(3.1) (7) Copies all or part of the data store of a buffer object into the data store of another buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void copyBufferSubData(UniformBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		_copyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING, (_Buffer&)writeBuffer, readOffset, writeOffset, size);
	}
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Gets the length parameter value of the mapping into the buffer object established with <mapBuffer>. Used as a getter of <bufferMapLength> property
	@return The 64-bit length of the buffer mapping. The initial value is zero*/
	GLsizeiptr getBufferMapLength()
	{
		return (GLsizeiptr)_getBufferParameter64(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_MAP_LENGTH);
	}

	/*(3.2) Gets the offset parameter value of the mapping into the buffer object established with <mapBuffer>. Used as a getter of <bufferMapOffset> property
	@return The 64-bit offset of the buffer mapping. The initial value is zero*/
	GLintptr getBufferMapOffset()
	{
		return (GLintptr)_getBufferParameter64(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, GL_BUFFER_MAP_OFFSET);
	}
#endif // #ifdef YAGLPP_VERSION_3_2

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.2) Read-only property for length 64-bit parameter value of the mapping into the buffer object established with <mapBuffer>*/
	__declspec(property(get = getBufferMapLength)) GLsizeiptr bufferMapLength;

	/*(3.2) Read-only property for offset 64-bit parameter value of the mapping into the buffer object established with <mapBuffer>*/
	__declspec(property(get = getBufferMapOffset)) GLintptr bufferMapOffset;
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)
}; // class ArrayBuffer : public _Buffer

/*Returns a reference ArrayBuffer object currently bound to its target
@return The reference ArrayBuffer object, or empty object*/
inline ArrayBuffer getArrayBufferBinding()
{
	return ArrayBuffer::getBufferBinding();
}

/*Explicitly unbinds any buffer object of specified type bound to its target. Does nothing if no such buffer is bound*/
inline void unbindArrayBuffer()
{
	ArrayBuffer::unbindTarget();
}
} // namespace gl
