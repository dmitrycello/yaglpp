#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_BUFFERS_T_H
#define YAGLPP_BUFFERS_T_H

namespace gl {
template <GLenum T, GLenum B> class Buffers_1 : public Buffers
{
public:
	using Buffers::Buffers;
	/*(1) Constructs an empty buffer object*/
	Buffers_1() : Buffers() {}

	/*(2) Constructs array buffer and initializes buffer object's data store with <Data>*/
	Buffers_1(DataStore& dataStore, Usage usage) : Buffers()
	{
		Buffers::buffer_create(T, (GLenum)usage, dataStore);
	}

	/*(3) Constructs array buffer and initializes buffer object's data store with <Data>*/
	Buffers_1(GLsizeiptr size, _Pre_maybenull_ const void* data, Usage usage) : Buffers()
	{
		Buffers::buffer_create(T, size, data, (GLenum)usage);
	}

	/*Binds buffer object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		Objects::object_bind(glBindBuffer, T);
	}

	/*(1) Creates and initializes buffer object's data store with the valid data DataStore object
	@param Specifies the DataStore object who's data and size will be used for the buffer initialization
	@param Specifies the expected usage pattern of the data store enumerator*/
	void Data(DataStore& dataStore, Usage usage)
	{
		Buffers::buffer_data(T, B, (GLenum)usage, dataStore);
	}

	/*(2) Creates and initializes buffer object's data store
	@param Specifies the size in bytes of the buffer object's new data store
	@param [in] Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied
	@param Specifies the expected usage pattern of the data store enumerator*/
	void Data(GLsizeiptr size, _Pre_maybenull_ const void* data, Usage usage)
	{
		Buffers::buffer_data(T, B, size, data, (GLenum)usage);
	}

	/*Generates OpenGL buffer object name in an empty buffer class object, and bind it to its target in one function call*/
	void GenBind()
	{
		Objects::object_gen_bind(glGenBuffers, glBindBuffer, T);
	}

	/*Gets the access policy parameter value set while mapping the buffer object, the value of the access parameter enum passed to <Map>. If the buffer was mapped with <MapRange>, the access policy is determined by translating the bits in that access parameter to one of the supported enums for <Map> as described in the OpenGL specification. MSVC getter for <access> property
	@return The buffer access policy enumerator*/
	Access GetAccess()
	{
		return (Access)Buffers::get_buffer_parameter(T, B, GL_BUFFER_ACCESS);
	}

	/*Returns the pointer to a mapped buffer object's data store
	@return The pointer to a mapped buffer object's data store, or NULL if the named buffer is unmapped*/
	_Ret_maybenull_ void* GetPointer()
	{
		return Buffers::get_buffer_pointer(T, B);
	}

	/*Gets the size parameter value of the buffer object parameter value, measured in bytes. The initial value is 0. MSVC getter for <size> property
	@return The size of the buffer object*/
	GLint GetSize()
	{
		return Buffers::get_buffer_parameter(T, B, GL_BUFFER_SIZE);
	}

	/*(1) Returns a subset of a buffer object into DataStore object
	@param Specifies the associated DataStore object who's region will receive the buffer object data
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned*/
	void GetSubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		Buffers::get_buffer_sub_data(T, B, offset, size, data);
	}

	/*(2) Returns a subset of a buffer object's data store
	@param Specifies the offset into the buffer object's data store from which data will be returned, measured in bytes
	@param Specifies the size in bytes of the data store region being returned
	@param [out] Specifies a pointer to the location where buffer object data is returned*/
	void GetSubData(GLintptr offset, GLsizeiptr size, _Out_ void* data)
	{
		Buffers::get_buffer_sub_data(T, B, offset, size, data);
	}

	/*Gets the buffer object's usage pattern parameter value. The initial value is <StaticDraw>. MSVC getter for <usage> property
	@return The buffer expected usage pattern enumerator*/
	Usage GetUsage()
	{
		return (Usage)Buffers::get_buffer_parameter(T, B, GL_BUFFER_USAGE);
	}

	/*Determines if the buffer object is currently bound to its target. MSVC getter for <binding> property
	@return True if buffer object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return Objects::object_binding(B, Get());
	}

	/*Gets a parameter flag indicating whether the buffer object is currently mapped. The initial value is false. MSVC getter for <mapped> property
	@return The mapped flag*/
	GLboolean IsMapped()
	{
		return Buffers::get_buffer_parameter(T, B, GL_BUFFER_MAPPED);
	}

	/*Maps all of a buffer object's data store into the client's address space
	@param Specifies the buffer access policy enumerator
	@return A pointer to the beginning of the buffer mapped range*/
	_Ret_maybenull_ void* Map(Access access)
	{
		return Buffers::map_buffer(T, B, (GLenum)access);
	}

	/*(1) Updates a subset of a buffer object data store from DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer*/
	void SubData(DataStore& data)
	{
		Buffers::buffer_sub_data(T, B, data);
	}

	/*(2) Updates a subset of a buffer object data store from a part of DataStore object
	@param Specifies the associated DataStore object who's region will be copied into the buffer
	@param Specifies the integer offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the integer size in bytes of the data store region being replaced*/
	void SubData(DataStore& data, GLintptr offset, GLsizeiptr size)
	{
		Buffers::buffer_sub_data(T, B, offset, size, data);
	}

	/*(3) Updates a subset of a buffer object's data store
	@param Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes
	@param Specifies the size in bytes of the data store region being replaced
	@param [in] Specifies a pointer to the new data that will be copied into the data store*/
	void SubData(GLintptr offset, GLsizeiptr size, _Pre_notnull_ const void* data)
	{
		Buffers::buffer_sub_data(T, B, offset, size, data);
	}

	/*Unbinds any buffer object bound to particular target. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindBuffer(T, 0);
	}

	/*Releases the mapping of a buffer object's data store into the client's address space
	@return True unless the data store contents have become corrupt during the time the data store was mapped*/
	GLboolean Unmap()
	{
		return Buffers::unmap_buffer(T, B);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for access policy parameter value set while mapping the buffer object*/
	__declspec(property(get = GetAccess)) Access access;

	/*Read-only property for buffer binding flag*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*Read-only property for parameter flag indicating whether the buffer object is currently mapped*/
	__declspec(property(get = IsMapped)) GLboolean mapped;

	/*Read-only property for size parameter value of the buffer object parameter value*/
	__declspec(property(get = GetSize)) GLint size;

	/*Read-only property for buffer object's usage pattern parameter*/
	__declspec(property(get = GetUsage)) Usage usage;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) Indicates modifications to a range of a mapped buffer
	@param Specifies the start of the buffer subrange, in basic machine units
	@param Specifies the length of the buffer subrange, in basic machine units*/
	void FlushMappedRange(GLintptr offset, GLsizeiptr length)
	{
		Buffers::flush_mapped_buffer_range(T, B, offset, length);
	}

	/*(3.0) Gets the access policy flag parameter set while mapping the buffer object (the value of the access parameter bitfield passed to <MapRange>). If the buffer was mapped with <Map>, the access policy is determined by translating the enums in that access parameter to the corresponding bits for <MapRange> as described in the OpenGL Specification. The initial value is zero. MSVC getter for <accessFlags> property
	@return The buffer access policy flag bitmask enumerator*/
	AccessFlags GetAccessFlags()
	{
		return (AccessFlags)Buffers::get_buffer_parameter(T, B, GL_BUFFER_ACCESS_FLAGS);
	}

	/*(3.0) Maps all or part of a buffer object's data store into the client's address space
	@param Specifies the starting offset within the buffer of the range to be mapped
	@param Specifies the length of the range to be mapped
	@param Specifies a combination bitmask enumerator of access buffer flags indicating the desired access to the mapped range*/
	_Ret_maybenull_ void* MapRange(GLintptr offset, GLsizeiptr length, AccessFlags access)
	{
		return Buffers::map_buffer_range(T, B, offset, length, (GLbitfield)access);
	}
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.0) Read-only property for access policy flag parameter set while mapping the buffer object*/
	__declspec(property(get = GetAccessFlags)) AccessFlags accessFlags;
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_1
	/*(3.1) (2) Copies all or part of the data store of a buffer object into the data store of a buffer object bound to copy write buffer target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, readOffset, writeOffset, size);
	}

	/*(3.1) (3) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. Must be bound to its target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(ArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (4) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(ElementArrayBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (5) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(PixelPackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (6) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(PixelUnpackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (7) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(TransformFeedbackBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_TRANSFORM_FEEDBACK_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (8) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(TextureBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}

	/*(3.1) (9) Copies all or part of the data store of a buffer object into the data store of specified buffer object
	@param Specifies the destination buffer object. If unbound from its target, the object is being bind to copy-write target
	@param Specifies the offset, in basic machine units, within the data store of the source buffer object from which data will be read
	@param Specifies the offset, in basic machine units, within the data store of the destination buffer object into which data will be written
	@param Specifies the size, in basic machine units, of the data to be copied from the source buffer object to the destination buffer object*/
	void CopySubData(UniformBuffer& writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		Buffers::copy_buffer_sub_data(T, B, GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING, ((Buffers&)writeBuffer).Get(), readOffset, writeOffset, size);
	}
#endif // #ifdef YAGLPP_VERSION_3_1

#ifdef YAGLPP_VERSION_3_2
	/*(3.2) Gets the length parameter value of the mapping into the buffer object established with <Map>. The initial value is zero. MSVC getter for <mapLength> property
	@return The 64-bit length of the buffer mapping*/
	GLint64 GetMapLength()
	{
		return Buffers::get_buffer_parameter64(T, B, GL_BUFFER_MAP_LENGTH);
	}

	/*(3.2) Gets the offset parameter value of the mapping into the buffer object established with <Map>. The initial value is zero. MSVC getter for <mapOffset> property
	@return The 64-bit offset of the buffer mapping*/
	GLint64 GetMapOffset()
	{
		return Buffers::get_buffer_parameter64(T, B, GL_BUFFER_MAP_OFFSET);
	}

	/*(3.2) Gets the size 64-bit parameter value of the buffer object parameter value, measured in bytes. The initial value is 0. MSVC getter for <size64> property
	@return The size of the buffer object*/
	GLint64 GetSize64()
	{
		return Buffers::get_buffer_parameter64(T, B, GL_BUFFER_SIZE);
	}
#endif // #ifdef YAGLPP_VERSION_3_2

#if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.2) Read-only property for length 64-bit parameter value of the mapping into the buffer object established with <Map>*/
	__declspec(property(get = GetMapLength)) GLint64 mapLength;

	/*(3.2) Read-only property for offset 64-bit parameter value of the mapping into the buffer object established with <Map>*/
	__declspec(property(get = GetMapOffset)) GLint64 mapOffset;

	/*(3.2) Read-only property for size 64-bit parameter value of the buffer object parameter value*/
	__declspec(property(get = GetSize64)) GLint64 size64;
#endif // #if defined (YAGLPP_VERSION_3_2) && defined (YAGLPP_CLASS_PROPERTIES)
}; // template <GLenum T, GLenum B> class Buffers_1 : public Buffers

typedef Buffers_1<GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING> ArrayBuffer_1;
/*OpenGL array buffer or vertex buffer object class (VBO) derived from <Buffers>*/
class ArrayBuffer : public ArrayBuffer_1
{
public:
	using Buffers_1::Buffers_1;
	/*Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static ArrayBuffer GetBinding()
	{
		return ArrayBuffer(yaglpp_glad_integer(GL_ARRAY_BUFFER_BINDING));
	}
};

typedef Buffers_1<GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING> ElementArrayBuffer_1;
/*OpenGL element array or element index buffer object class (EBO) derived from <Buffers>*/
class ElementArrayBuffer : public ElementArrayBuffer_1
{
public:
	using Buffers_1::Buffers_1;
	/*Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static ElementArrayBuffer GetBinding()
	{
		return ElementArrayBuffer(yaglpp_glad_integer(GL_ELEMENT_ARRAY_BUFFER_BINDING));
	}
};

#ifdef YAGLPP_VERSION_2_1
typedef Buffers_1<GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING> PixelPackBuffer_1;
/*(2.1) OpenGL pixel pack buffer or pixel download buffer object class (PBO) derived from <Buffers>*/
class PixelPackBuffer : public PixelPackBuffer_1
{
public:
	using Buffers_1::Buffers_1;
	/*(2.1) Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static PixelPackBuffer GetBinding()
	{
		return PixelPackBuffer(yaglpp_glad_integer(GL_PIXEL_PACK_BUFFER_BINDING));
	}
};

typedef Buffers_1<GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING> PixelUnpackBuffer_1;
/*(2.1) OpenGL pixel unpack buffer or pixel upload buffer object class (PBO) derived from <Buffers>*/
class PixelUnpackBuffer : public PixelUnpackBuffer_1
{
public:
	using Buffers_1::Buffers_1;
	/*(2.1) Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static PixelUnpackBuffer GetBinding()
	{
		return PixelUnpackBuffer(yaglpp_glad_integer(GL_PIXEL_UNPACK_BUFFER_BINDING));
	}
};
#endif // #ifdef YAGLPP_VERSION_2_1

#ifdef YAGLPP_VERSION_3_0
template <GLenum T, GLenum B> class Buffers_2 : public Buffers_1<T, B>
{
public:
	using Buffers_1<T, B>::Buffers_1;
	/*(3.0) Binds a buffer object to an indexed buffer target
	@param Specifies the index of the binding point within the array specified by target*/
	void BindBase(GLuint index)
	{
		Buffers::bind_buffer_base(T, index);
	}

	/*(3.0) Binds a range within a buffer object to an indexed buffer target
	@param Specifies the index of the binding point within the array specified by target
	@param The starting offset in basic machine units into the buffer object
	@param The amount of data in machine units that can be read from the buffer object while used as an indexed target*/
	void BindRange(GLuint index, GLintptr offset, GLsizeiptr size)
	{
		Buffers::bind_buffer_range(T, index, offset, size);
	}
}; // template <GLenum T, GLenum B> class Buffers_2 : public Buffers_1<T, B>

typedef Buffers_1<GL_TRANSFORM_FEEDBACK_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING> TransformFeedbackBuffer_1;
typedef Buffers_2<GL_TRANSFORM_FEEDBACK_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER_BINDING> TransformFeedbackBuffer_2;
/*(3.0) OpenGL transform feedback buffer object class (TFO) derived from <Buffers>*/
class TransformFeedbackBuffer : public TransformFeedbackBuffer_2
{
public:
	using Buffers_2::Buffers_2;
	/*(3.0) Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static TransformFeedbackBuffer GetBinding()
	{
		return TransformFeedbackBuffer(yaglpp_glad_integer(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING));
	}
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_1
typedef Buffers_1<GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_BINDING> TextureBuffer_1;
/*(3.1) OpenGL texture buffer object class (TBO) derived from <Buffers>*/
class TextureBuffer : public TextureBuffer_1
{
public:
	using Buffers_1::Buffers_1;
	/*(3.1) Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static TextureBuffer GetBinding()
	{
		return TextureBuffer(yaglpp_glad_integer(GL_TEXTURE_BUFFER_BINDING));
	}
};

typedef Buffers_1<GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING> UniformBuffer_1;
typedef Buffers_2<GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING> UniformBuffer_2;
/*(3.1) OpenGL uniform block storage buffer or uniform buffer object class (UBO) derived from <Buffers>*/
class UniformBuffer : public UniformBuffer_2
{
public:
	using Buffers_2::Buffers_2;
	/*(3.1) Returns the buffer object currently bound to particular target
	@return The bound buffer object, or empty object*/
	static UniformBuffer GetBinding()
	{
		return UniformBuffer(yaglpp_glad_integer(GL_UNIFORM_BUFFER_BINDING));
	}
};
#endif // #ifdef YAGLPP_VERSION_3_1
} // namespace gl
#endif // #ifndef YAGLPP_BUFFERS_T_H
