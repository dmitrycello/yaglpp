#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_VERTEX_ATTRIB_H
#define YAGLPP_VERTEX_ATTRIB_H

namespace gl {
/*OpenGL vertex attribute object root class*/
class VertexAttrib
{
public:
	enum class Size : GLsizei;
	enum class Type : GLenum;
	/*(1) Constructs unassigned vertex attribute object*/
	VertexAttrib()
	{
		m_Location = -1;
	}

	/*(2) Constructs a copy of vertex attribute object*/
	VertexAttrib(const VertexAttrib& source)
	{
		m_Location = source.m_Location;
	}

	/*(3) Constructs vertex attribute object with <SetLocation>*/
	VertexAttrib(GLuint location)
	{
		SetLocation(location);
	}

	/*(4) Constructs vertex attribute object with <GetLocation>*/
	VertexAttrib(Program& program, _In_z_ const GLchar* name)
	{
		GetLocation(program, name);
	}

	/*Associates a generic vertex attribute object with a named attribute variable
	@param Specifies the program object in which the association is to be made
	@param Specifies the index of the generic vertex attribute to be bound
	@param [in] Specifies a null terminated string containing the name of the vertex shader attribute variable to which object is to be bound*/
	void BindLocation(Program& program, GLuint index, _In_z_ const GLchar* name);

	/*Associates two generic vertex attribute objects with a named attribute variable of <mat2> type
	@param Specifies the program object in which the association is to be made
	@param Specifies the index of the generic vertex attribute to be bound as the first column of the matrix
	@param Specifies the vertex attribute object to be bound as the second column of the matrix
	@param [in] Specifies a null terminated string containing the name of the vertex shader attribute variable to which object is to be bound*/
	void BindMatrix2(Program& program, GLuint index, VertexAttrib mat2, _In_z_ const GLchar* name);

	/*Associates three generic vertex attribute objects with a named attribute variable of <mat3> type
	@param Specifies the program object in which the association is to be made
	@param Specifies the index of the generic vertex attribute to be bound as the first column of the matrix
	@param Specifies the vertex attribute object to be bound as the second column of the matrix
	@param Specifies the vertex attribute object to be bound as the third column of the matrix
	@param [in] Specifies a null terminated string containing the name of the vertex shader attribute variable to which object is to be bound*/
	void BindMatrix3(Program& program, GLuint index, VertexAttrib mat2, VertexAttrib mat3, _In_z_ const GLchar* name);

	/*Associates four generic vertex attribute objects with a named attribute variable of <mat4> type
	@param Specifies the program object in which the association is to be made
	@param Specifies the index of the generic vertex attribute to be bound as the first column of the matrix
	@param Specifies the vertex attribute object to be bound as the second column of the matrix
	@param Specifies the vertex attribute object to be bound as the third column of the matrix
	@param Specifies the vertex attribute object to be bound as the fourth column of the matrix
	@param [in] Specifies a null terminated string containing the name of the vertex shader attribute variable to which object is to be bound*/
	void BindMatrix4(Program& program, GLuint index, VertexAttrib mat2, VertexAttrib mat3, VertexAttrib mat4, _In_z_ const GLchar* name);

	/*Disables a generic vertex attribute array*/
	void DisableArray();

	/*Enables a generic vertex attribute array*/
	void EnableArray();

	/*Gets the vertex attribute enabled flag. MSVC getter for <arrayEnabled> property
	@return True if vertex attribute is enabled*/
	GLboolean GetArrayEnabled()
	{
		return get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_ENABLED);
	}

	/*Gets a boolean value that is true if fixed-point data type for the vertex attribute is normalized when converted to floating point, and false otherwise. MSVC getter for <arrayNormalized> property
	@return The vertex attribute normalized flag*/
	GLboolean GetArrayNormalized()
	{
		return get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
	}

	/*Gets the data size of the vertex attribute array for current vertex attribute. MSVC getter for <arraySize> property
	@return The number of values for each element of the vertex attribute array*/
	Size GetArraySize()
	{
		return (Size)get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_SIZE);
	}

	/*Gets the array stride for the vertex attribute array for current vertex attribute. A value of 0 indicates that the array elements are stored sequentially in memory. MSVC getter for <arrayStride> property
	@return The number of bytes between successive elements in the vertex attribute array*/
	GLsizei GetArrayStride()
	{
		return get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_STRIDE);
	}

	/*Gets a value indicating the array type for the vertex attribute. MSVC getter for <arrayType> property
	@return The type of vertex attribute*/
	Type GetArrayType()
	{
		return (Type)get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_TYPE);
	}

	/*(1) Returns four integer values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested integer data*/
	void GetCurrent(_Out_writes_(4) GLint* params);

	/*(2) Returns four float values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested float data*/
	void GetCurrent(_Out_writes_(4) GLfloat* params);

	/*(3) Returns four double values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested double data*/
	void GetCurrent(_Out_writes_(4) GLdouble* params);

	/*Queries the previously linked program object for the location of a vertex attribute object
	@param Specifies the program object to be queried
	@param [in] Points to a null terminated string containing the name of the attribute variable whose location is to be queried*/
	void GetLocation(Program& program, _In_z_ const GLchar* name);

	/*Returns the vertex attribute's memory byte offset into the data store of the array buffer object that was bound to target when the desired pointer was previously specified
	@return The attribute's previously specified memory byte offset*/
	GLintptr GetPointer();

	/*Checks if retrieved attribute location is valid. MSVC getter for <vertexAttrib> property
	@return True if valid attribute, false otherwise*/
	GLboolean IsVertexAttrib()
	{
		return m_Location > -1;
	}

	/*Checks if the vertex array buffer object (VBO) is currently bound to the binding point corresponding to generic vertex attribute array
	@param The vertex array buffer object (VBO)
	@return True if the VBO is currently bound to the VAO's binding point, false otherwise*/
	GLboolean IsArrayBufferBinding(ArrayBuffer& vbo)
	{
		return vbo.Get() == (GLuint)get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
	}

	/*Defines the generic vertex attribute data
	@param Specifies the number of components per generic vertex attribute
	@param Specifies the data type of each component in the array
	@param Specifies whether fixed-point data values should be normalized (true) or converted directly as fixed-point values (false) when they are accessed
	@param Specifies the byte offset between consecutive generic vertex attributes
	@param Specifies the byte offset of the first component of the first generic vertex attribute in the vertex array buffer data store*/
	void Pointer(Size size, Type type, GLboolean normalized, GLsizei stride, GLintptr offset);

	/*(1) Specifies the single float value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void Set(GLfloat x);

	/*(2) Specifies the two float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void Set(GLfloat x, GLfloat y);

	/*(3) Specifies the three float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void Set(GLfloat x, GLfloat y, GLfloat z);

	/*(4) Specifies the four float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void Set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	/*(5) Specifies the single short value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void Set(GLshort x);

	/*(6) Specifies the two short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void Set(GLshort x, GLshort y);

	/*(7) Specifies the three short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void Set(GLshort x, GLshort y, GLshort z);

	/*(8) Specifies the four short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void Set(GLshort x, GLshort y, GLshort z, GLshort w);

	/*(9) Specifies the single double value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void Set(GLdouble x);

	/*(10) Specifies the two double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void Set(GLdouble x, GLdouble y);

	/*(11) Specifies the three double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void Set(GLdouble x, GLdouble y, GLdouble z);

	/*(12) Specifies the four double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void Set(GLdouble x, GLdouble y, GLdouble z, GLdouble w);

	/*(13) Specifies the float array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void Set(_In_ const GLfloat* value);

	/*(14) Specifies the two-component float array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::vec2* value);

	/*(15) Specifies the three-component float array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::vec3* value);

	/*(16) Specifies the four-component float array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::vec4* value);

	/*(17) Specifies the short array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void Set(_In_ const GLshort* value);

	/*(18) Specifies the two-component short array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::svec2* value);

	/*(19) Specifies the three-component short array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::svec3* value);

	/*(20) Specifies the four-component short array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::svec4* value);

	/*(21) Specifies the double array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void Set(_In_ const GLdouble* value);

	/*(22) Specifies the two-component double array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::dvec2* value);

	/*(23) Specifies the three-component double array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::dvec3* value);

	/*(24) Specifies the four-component double array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::dvec4* value);

	/*(25) Specifies the four-component char array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::cvec4* value);

	/*(26) Specifies the four-component unsigned char array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::ucvec4* value);

	/*(28) Specifies the four-component unsigned short array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::usvec4* value);

	/*(28) Specifies the four-component integer array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::ivec4* value);

	/*(29) Specifies the four-component unsigned integer array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set(_In_ const glm::uvec4* value);

	/*(1) Specifies the four normalized unsigned char values of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void Set4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	/*(2) Specifies the normalized four-component char array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLbyte* xyzw);

	/*(3) Specifies the normalized four-component unsigned char array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLubyte* xyzw);

	/*(4) Specifies the normalized four-component short array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLshort* xyzw);

	/*(5) Specifies the normalized four-component unsigned short array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLushort* xyzw);

	/*(6) Specifies the normalized four-component integer array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLint* xyzw);

	/*(7) Specifies the normalized four-component unsigned integer array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void Set4N(_In_reads_(4) const GLuint* xyzw);

	/*Directly assigns the location of a vertex attribute object
	@param Location value of the vertex attribute, must be less than the value returned by <GetMaxVertexAttribs>*/
	void SetLocation(GLuint location);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if retrieved attribute location is valid*/
	__declspec(property(get = IsVertexAttrib)) GLboolean vertexAttrib;

	/*Read-only property for vertex attribute enabled flag*/
	__declspec(property(get = GetArrayEnabled)) GLboolean arrayEnabled;

	/*Read-only property for boolean value that is true if fixed-point data type for the vertex attribute is normalized when converted to floating point, and false otherwise*/
	__declspec(property(get = GetArrayNormalized)) GLboolean arrayNormalized;

	/*Read-only property for data size of the vertex attribute array for current vertex attribute*/
	__declspec(property(get = GetArraySize)) Size arraySize;

	/*Read-only property for array stride for the vertex attribute array for current vertex attribute*/
	__declspec(property(get = GetArrayStride)) GLsizei arrayStride;

	/*Read-only property for value indicating the array type for the vertex attribute*/
	__declspec(property(get = GetArrayType)) Type arrayType;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

#ifdef YAGLPP_VERSION_3_0
	enum class SizeI : GLsizei;
	enum class TypeI : GLenum;
	/*(3.0) Gets a boolean value that is true if fixed-point data type for the vertex attribute have integer data types, and false otherwise. MSVC getter for <arrayInteger> property
	@return The vertex attribute integer flag*/
	GLboolean GetArrayInteger()
	{
		return get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_INTEGER);
	}

	/*(3.0) (1) Gets four integer values that represent the current value for the generic vertex attribute extended to full signed integer
	@param [out] Returns the requested integer data*/
	void GetCurrentI(_Out_writes_(4) GLint* params);

	/*(3.0) (2) Gets four unsigned integer values that represent the current value for the generic vertex attribute extended to full unsigned integer
	@param [out] Returns the requested unsigned integer data*/
	void GetCurrentI(_Out_writes_(4) GLuint* params);

	/*(3.0) Defines the generic vertex attribute data. Values are always left as integer values
	@param Specifies the number of components per generic vertex attribute
	@param Specifies the integer data type of each component in the array
	@param Specifies the byte offset between consecutive generic vertex attributes
	@param Specifies the byte offset of the first component of the first generic vertex attribute in the vertex array buffer data store*/
	void PointerI(SizeI size, TypeI type, GLsizei stride, GLintptr offset);

	/*(3.0) (1) Specifies the single integer value of a generic vertex attribute. The argument is extended to full signed integer
	@param Specifies the new value to be used for the specified vertex attribute*/
	void SetI(GLint x);

	/*(3.0) (2) Specifies the two integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void SetI(GLint x, GLint y);

	/*(3.0) (3) Specifies the three integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void SetI(GLint x, GLint y, GLint z);

	/*(3.0) (4) Specifies the four integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void SetI(GLint x, GLint y, GLint z, GLint w);

	/*(3.0) (5) Specifies the single unsigned integer value of a generic vertex attribute. The argument is extended to full unsigned integer
	@param Specifies the new value to be used for the specified vertex attribute*/
	void SetI(GLuint x);

	/*(3.0) (6) Specifies the two unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void SetI(GLuint x, GLuint y);

	/*(3.0) (7) Specifies the three unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void SetI(GLuint x, GLuint y, GLuint z);

	/*(3.0) (8) Specifies the four unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void SetI(GLuint x, GLuint y, GLuint z, GLuint w);

	/*(3.0) (9) Specifies the integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void SetI(_In_ const GLint* value);

	/*(3.0) (10) Specifies the two-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::ivec2* value);

	/*(3.0) (11) Specifies the three-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::ivec3* value);

	/*(3.0) (12) Specifies the four-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::ivec4* value);

	/*(3.0) (13) Specifies the unsigned integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void SetI(_In_ const GLuint* value);

	/*(3.0) (14) Specifies the two-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::uvec2* value);

	/*(3.0) (15) Specifies the three-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::uvec3* value);

	/*(3.0) (16) Specifies the four-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::uvec4* value);

	/*(3.0) (17) Specifies the four-component char array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::cvec4* value);

	/*(3.0) (18) Specifies the four-component unsigned char array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::ucvec4* value);

	/*(3.0) (19) Specifies the four-component short array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::svec4* value);

	/*(3.0) (20) Specifies the four-component unsigned short array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void SetI(_In_ const glm::usvec4* value);
#endif // #ifdef YAGLPP_VERSION_3_0

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.0) Read-only property for boolean value that is true if fixed-point data type for the vertex attribute have integer data types, and false otherwise*/
	__declspec(property(get = GetArrayInteger)) GLboolean arrayInteger;
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_CLASS_PROPERTIES)

#ifdef YAGLPP_VERSION_3_3
	enum class TypeP : GLenum;
	/*(3.3) Modify the rate at which generic vertex attributes advance during instanced rendering
	@param Specify the number of instances that will pass between updates of the generic attribute*/
	void Divisor(GLuint divisor);

	/*(3.3) Gets a value that is the frequency divisor used for instanced rendering. MSVC getter for <arrayDivisor> property
	@return The vertex attribute divisor value. The initial value is 0*/
	GLuint GetArrayDivisor()
	{
		return get_vertex_attrib(GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
	}

	/*(3.3) (1) Specifies the packed value of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void SetP1(TypeP type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of packed values of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of the new packed values to be used for the specified vertex attribute*/
	void SetP1(TypeP type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with two packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void SetP2(TypeP type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of values with two packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with two packed components to be used for the specified vertex attribute*/
	void SetP2(TypeP type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with three packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void SetP3(TypeP type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of values with three packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with three packed components to be used for the specified vertex attribute*/
	void SetP3(TypeP type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with four packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void SetP4(TypeP type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the packed value with four packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with three packed components to be used for the specified vertex attribute*/
	void SetP4(TypeP type, GLboolean normalized, _In_ GLuint* value);
#endif // #ifdef YAGLPP_VERSION_3_3

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)
	/*(3.3) Read-only property for value that is the frequency divisor used for instanced rendering*/
	__declspec(property(get = GetArrayDivisor)) GLuint arrayDivisor;
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_CLASS_PROPERTIES)

private:
	GLint m_Location; // Attribute index
	GLuint get_location();
	GLint get_vertex_attrib(GLenum ePname);
}; // class VertexAttrib

/*GLAD vertex attribute data size enumerator (1 to 4 or <Bgra>), default 4*/
enum class VertexAttrib::Size : GLsizei
{
	/*One-component attribute value*/
	Single = 1,

	/*Two-component attribute value*/
	Double = 2,

	/*Three-component attribute value*/
	Triple = 3,

	/*Four-component attribute value, this is initial value*/
	Quad = 4,

	/*Additionally accepted reversed four-component attribute value*/
	Bgra = GL_BGRA,
};

/*GLAD vertex attribute data type enumerator*/
enum class VertexAttrib::Type : GLenum
{
	/*8-bit signed 2's complement binary integer*/
	Byte = GL_BYTE,

	/*8-bit unsigned binary integer*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*16-bit signed 2's complement binary integer*/
	Short = GL_SHORT,

	/*16-bit unsigned binary integer*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*32-bit signed 2's complement binary integer*/
	Int = GL_INT,

	/*32-bit unsigned binary integer*/
	UnsignedInt = GL_UNSIGNED_INT,

	/*32-bit IEEE-754 floating-point value*/
	Float = GL_FLOAT,

	/*64-bit IEEE-754 floating-point value*/
	Double = GL_DOUBLE,

	/*32-bit unsigned integer value packed as four numbers 2:10:10:10*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

#ifdef YAGLPP_VERSION_3_0
	/*(3.0) 16-bit IEEE-754 floating-point value*/
	HalfFloat = GL_HALF_FLOAT,

	/*(3.0) 32-bit unsigned integer value packed as three float numbers 10:11:11*/
	UnsignedInt10f11f11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
	/*(3.3) 32-bit signed integer value packed as four numbers 2:10:10:10*/
	Int2101010Rev = GL_INT_2_10_10_10_REV,
#endif // #ifdef YAGLPP_VERSION_3_3
};

#ifdef YAGLPP_VERSION_3_0
/*(3.0) GLAD vertex attribute integer data size enumerator (1 to 4)*/
enum class VertexAttrib::SizeI : GLsizei
{
	/*(3.0) One-component attribute value*/
	Single = 1,

	/*(3.0) Two-component attribute value*/
	Double = 2,

	/*(3.0) Three-component attribute value*/
	Triple = 3,

	/*(3.0) Four-component attribute value*/
	Quad = 4,
};

/*(3.0) GLAD vertex attribute integer data type enumerator*/
enum class VertexAttrib::TypeI : GLenum
{
	/*(3.0) 8-bit signed 2's complement binary integer*/
	Byte = GL_BYTE,

	/*(3.0) 8-bit unsigned binary integer*/
	UnsignedByte = GL_UNSIGNED_BYTE,

	/*(3.0) 16-bit signed 2's complement binary integer*/
	Short = GL_SHORT,

	/*(3.0) 16-bit unsigned binary integer*/
	UnsignedShort = GL_UNSIGNED_SHORT,

	/*(3.0) 32-bit signed 2's complement binary integer*/
	Int = GL_INT,

	/*(3.0) 32-bit unsigned binary integer*/
	UnsignedInt = GL_UNSIGNED_INT,
};
#endif // #ifdef YAGLPP_VERSION_3_0

#ifdef YAGLPP_VERSION_3_3
/*(3.3) GLAD vertex attribute packed data type enumerator*/
enum class VertexAttrib::TypeP : GLenum
{
	/*(3.3) 32-bit unsigned integer value packed as four numbers 2:10:10:10*/
	UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

	/*(3.3) 32-bit unsigned integer value packed as three float numbers 10:11:11*/
	UnsignedInt10f11f11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,

	/*(3.3) 32-bit signed integer value packed as four numbers 2:10:10:10*/
	Int2101010Rev = GL_INT_2_10_10_10_REV,
};
#endif // #ifdef YAGLPP_VERSION_3_3

#ifdef YAGLPP_IMPLEMENTATION
void VertexAttrib::BindLocation(Program& program, GLuint index, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	// VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	YAGLPP_ASSERT(index < GetMaxVertexAttribs());

	glBindAttribLocation(program.Get(), index, name);
	YAGLPP_GLAD_ERROR;
	m_Location = (GLint)index;
}

void VertexAttrib::BindMatrix2(Program& program, GLuint index, VertexAttrib mat2, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	// VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	YAGLPP_ASSERT(index < GetMaxVertexAttribs());

	glBindAttribLocation(program.Get(), index, name);
	YAGLPP_GLAD_ERROR;
	m_Location = (GLint)index;
	mat2.m_Location = m_Location + 1;
}


void VertexAttrib::BindMatrix3(Program& program, GLuint index, VertexAttrib mat2, VertexAttrib mat3, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	// VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	YAGLPP_ASSERT(index < GetMaxVertexAttribs());

	glBindAttribLocation(program.Get(), index, name);
	YAGLPP_GLAD_ERROR;
	m_Location = (GLint)index;
	mat2.m_Location = m_Location + 1;
	mat3.m_Location = m_Location + 2;
}

void VertexAttrib::BindMatrix4(Program& program, GLuint index, VertexAttrib mat2, VertexAttrib mat3, VertexAttrib mat4, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	// VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	YAGLPP_ASSERT(index < GetMaxVertexAttribs());

	glBindAttribLocation(program.Get(), index, name);
	YAGLPP_GLAD_ERROR;
	m_Location = (GLint)index;
	mat2.m_Location = m_Location + 1;
	mat3.m_Location = m_Location + 2;
	mat4.m_Location = m_Location + 3;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLuint VertexAttrib::get_location()
{
	// VERTEX ATTRIBUTE LOCATION INDEX IS INVALID
	YAGLPP_ASSERT(m_Location > -1);

	return m_Location;
}

GLint VertexAttrib::get_vertex_attrib(GLenum ePname)
{
	GLint iResult;
	glGetVertexAttribiv(get_location(), ePname, &iResult);
	YAGLPP_GLAD_ERROR;
	return iResult;
}

void VertexAttrib::DisableArray()
{
	glDisableVertexAttribArray(get_location());
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::EnableArray()
{
	glEnableVertexAttribArray(get_location());
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::GetCurrent(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribiv(get_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::GetCurrent(_Out_writes_(4) GLfloat* params)
{
	glGetVertexAttribfv(get_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::GetCurrent(_Out_writes_(4) GLdouble* params)
{
	glGetVertexAttribdv(get_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	// INVALID PROGRAM OBJECT
	YAGLPP_ASSERT(program.IsProgram());

	m_Location = glGetAttribLocation(program.Get(), name);
	YAGLPP_GLAD_ERROR;
}

GLintptr VertexAttrib::GetPointer()
{
	void* pData;
	glGetVertexAttribPointerv(get_location(), GL_VERTEX_ATTRIB_ARRAY_POINTER, &pData);
	YAGLPP_GLAD_ERROR;
	return (GLintptr)pData;
}

void VertexAttrib::Pointer(Size size, Type type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer(get_location(), (GLint)size, (GLenum)type, normalized, stride, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLfloat x)
{
	glVertexAttrib1f(get_location(), x);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLfloat x, GLfloat y)
{
	glVertexAttrib2f(get_location(), x, y);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLfloat x, GLfloat y, GLfloat z)
{
	glVertexAttrib3f(get_location(), x, y, z);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glVertexAttrib4f(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLshort x)
{
	glVertexAttrib1s(get_location(), x);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLshort x, GLshort y)
{
	glVertexAttrib2s(get_location(), x, y);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLshort x, GLshort y, GLshort z)
{
	glVertexAttrib3s(get_location(), x, y, z);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLshort x, GLshort y, GLshort z, GLshort w)
{
	glVertexAttrib4s(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLdouble x)
{
	glVertexAttrib1d(get_location(), x);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLdouble x, GLdouble y)
{
	glVertexAttrib2d(get_location(), x, y);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLdouble x, GLdouble y, GLdouble z)
{
	glVertexAttrib3d(get_location(), x, y, z);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	glVertexAttrib4d(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const GLfloat* value)
{
	glVertexAttrib1fv(get_location(), value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::vec2* value)
{
	glVertexAttrib2fv(get_location(), (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::vec3* value)
{
	glVertexAttrib3fv(get_location(), (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::vec4* value)
{
	glVertexAttrib4fv(get_location(), (GLfloat*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const GLshort* value)
{
	glVertexAttrib1sv(get_location(), value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::svec2* value)
{
	glVertexAttrib2sv(get_location(), (GLshort*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::svec3* value)
{
	glVertexAttrib3sv(get_location(), (GLshort*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::svec4* value)
{
	glVertexAttrib4sv(get_location(), (GLshort*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const GLdouble* value)
{
	glVertexAttrib1dv(get_location(), value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::dvec2* value)
{
	glVertexAttrib2dv(get_location(), (GLdouble*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::dvec3* value)
{
	glVertexAttrib3dv(get_location(), (GLdouble*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::dvec4* value)
{
	glVertexAttrib4dv(get_location(), (GLdouble*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::cvec4* value)
{
	glVertexAttrib4bv(get_location(), (GLbyte*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::ucvec4* value)
{
	glVertexAttrib4ubv(get_location(), (GLubyte*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::usvec4* value)
{
	glVertexAttrib4usv(get_location(), (GLushort*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::ivec4* value)
{
	glVertexAttrib4iv(get_location(), (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set(_In_ const glm::uvec4* value)
{
	glVertexAttrib4uiv(get_location(), (unsigned int*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	glVertexAttrib4Nub(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLbyte* xyzw)
{
	glVertexAttrib4Nbv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLubyte* xyzw)
{
	glVertexAttrib4Nubv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLshort* xyzw)
{
	glVertexAttrib4Nsv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLushort* xyzw)
{
	glVertexAttrib4Nusv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLint* xyzw)
{
	glVertexAttrib4Niv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::Set4N(_In_reads_(4) const GLuint* xyzw)
{
	glVertexAttrib4Nuiv(get_location(), xyzw);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetLocation(GLuint location)
{
	// VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	YAGLPP_ASSERT(location < GetMaxVertexAttribs());

	m_Location = (GLint)location;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLuint VertexAttrib::get_location()
{
	return m_Location;
}

inline GLint VertexAttrib::get_vertex_attrib(GLenum ePname)
{
	GLint i; glGetVertexAttribiv(m_Location, ePname, &i); return i;
}

inline void VertexAttrib::DisableArray()
{
	glDisableVertexAttribArray(m_Location);
}

inline void VertexAttrib::EnableArray()
{
	glEnableVertexAttribArray(m_Location);
}

inline void VertexAttrib::GetCurrent(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribiv(m_Location, GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::GetCurrent(_Out_writes_(4) GLfloat* params)
{
	glGetVertexAttribfv(m_Location, GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::GetCurrent(_Out_writes_(4) GLdouble* params)
{
	glGetVertexAttribdv(m_Location, GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::GetLocation(Program& program, _In_z_ const GLchar* name)
{
	m_Location = glGetAttribLocation(program.Get(), name);
}

inline GLintptr VertexAttrib::GetPointer()
{
	void* p; glGetVertexAttribPointerv(m_Location, GL_VERTEX_ATTRIB_ARRAY_POINTER, &p); return (GLintptr)p;
}

inline void VertexAttrib::Pointer(Size size, Type type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer(m_Location, (GLint)size, (GLenum)type, normalized, stride, (void*)offset);
}

inline void VertexAttrib::Set(GLfloat x)
{
	glVertexAttrib1f(m_Location, x);
}

inline void VertexAttrib::Set(GLfloat x, GLfloat y)
{
	glVertexAttrib2f(m_Location, x, y);
}

inline void VertexAttrib::Set(GLfloat x, GLfloat y, GLfloat z)
{
	glVertexAttrib3f(m_Location, x, y, z);
}

inline void VertexAttrib::Set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glVertexAttrib4f(m_Location, x, y, z, w);
}

inline void VertexAttrib::Set(GLshort x)
{
	glVertexAttrib1s(m_Location, x);
}

inline void VertexAttrib::Set(GLshort x, GLshort y)
{
	glVertexAttrib2s(m_Location, x, y);
}

inline void VertexAttrib::Set(GLshort x, GLshort y, GLshort z)
{
	glVertexAttrib3s(m_Location, x, y, z);
}

inline void VertexAttrib::Set(GLshort x, GLshort y, GLshort z, GLshort w)
{
	glVertexAttrib4s(m_Location, x, y, z, w);
}

inline void VertexAttrib::Set(GLdouble x)
{
	glVertexAttrib1d(m_Location, x);
}

inline void VertexAttrib::Set(GLdouble x, GLdouble y)
{
	glVertexAttrib2d(m_Location, x, y);
}

inline void VertexAttrib::Set(GLdouble x, GLdouble y, GLdouble z)
{
	glVertexAttrib3d(m_Location, x, y, z);
}

inline void VertexAttrib::Set(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	glVertexAttrib4d(m_Location, x, y, z, w);
}

inline void VertexAttrib::Set(_In_ const GLfloat* value)
{
	glVertexAttrib1fv(m_Location, value);
}

inline void VertexAttrib::Set(_In_ const glm::vec2* value)
{
	glVertexAttrib2fv(m_Location, (GLfloat*)value);
}

inline void VertexAttrib::Set(_In_ const glm::vec3* value)
{
	glVertexAttrib3fv(m_Location, (GLfloat*)value);
}

inline void VertexAttrib::Set(_In_ const glm::vec4* value)
{
	glVertexAttrib4fv(m_Location, (GLfloat*)value);
}

inline void VertexAttrib::Set(_In_ const GLshort* value)
{
	glVertexAttrib1sv(m_Location, value);
}

inline void VertexAttrib::Set(_In_ const glm::svec2* value)
{
	glVertexAttrib2sv(m_Location, (GLshort*)value);
}

inline void VertexAttrib::Set(_In_ const glm::svec3* value)
{
	glVertexAttrib3sv(m_Location, (GLshort*)value);
}

inline void VertexAttrib::Set(_In_ const glm::svec4* value)
{
	glVertexAttrib4sv(m_Location, (GLshort*)value);
}

inline void VertexAttrib::Set(_In_ const GLdouble* value)
{
	glVertexAttrib1dv(m_Location, value);
}

inline void VertexAttrib::Set(_In_ const glm::dvec2* value)
{
	glVertexAttrib2dv(m_Location, (GLdouble*)value);
}

inline void VertexAttrib::Set(_In_ const glm::dvec3* value)
{
	glVertexAttrib3dv(m_Location, (GLdouble*)value);
}

inline void VertexAttrib::Set(_In_ const glm::dvec4* value)
{
	glVertexAttrib4dv(m_Location, (GLdouble*)value);
}

inline void VertexAttrib::Set(_In_ const glm::cvec4* value)
{
	glVertexAttrib4bv(m_Location, (GLbyte*)value);
}

inline void VertexAttrib::Set(_In_ const glm::ucvec4* value)
{
	glVertexAttrib4ubv(m_Location, (GLubyte*)value);
}

inline void VertexAttrib::Set(_In_ const glm::usvec4* value)
{
	glVertexAttrib4usv(m_Location, (GLushort*)value);
}

inline void VertexAttrib::Set(_In_ const glm::ivec4* value)
{
	glVertexAttrib4iv(m_Location, (GLint*)value);
}

inline void VertexAttrib::Set(_In_ const glm::uvec4* value)
{
	glVertexAttrib4uiv(m_Location, (unsigned int*)value);
}

inline void VertexAttrib::Set4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	glVertexAttrib4Nub(m_Location, x, y, z, w);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLbyte* xyzw)
{
	glVertexAttrib4Nbv(m_Location, xyzw);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLubyte* xyzw)
{
	glVertexAttrib4Nubv(m_Location, xyzw);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLshort* xyzw)
{
	glVertexAttrib4Nsv(m_Location, xyzw);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLushort* xyzw)
{
	glVertexAttrib4Nusv(m_Location, xyzw);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLint* xyzw)
{
	glVertexAttrib4Niv(m_Location, xyzw);
}

inline void VertexAttrib::Set4N(_In_reads_(4) const GLuint* xyzw)
{
	glVertexAttrib4Nuiv(m_Location, xyzw);
}

inline void VertexAttrib::SetLocation(GLuint location)
{
	m_Location = (GLint)location;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void VertexAttrib::GetCurrentI(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribIiv(get_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::GetCurrentI(_Out_writes_(4) GLuint* params)
{
	glGetVertexAttribIuiv(get_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::PointerI(SizeI size, TypeI type, GLsizei stride, GLintptr offset)
{
	glVertexAttribIPointer(get_location(), (GLint)size, (GLenum)type, stride, (void*)offset);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLint x)
{
	glVertexAttribI1i(get_location(), x);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLint x, GLint y)
{
	glVertexAttribI2i(get_location(), x, y);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLint x, GLint y, GLint z)
{
	glVertexAttribI3i(get_location(), x, y, z);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLint x, GLint y, GLint z, GLint w)
{
	glVertexAttribI4i(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLuint x)
{
	glVertexAttribI1ui(get_location(), x);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLuint x, GLuint y)
{
	glVertexAttribI2ui(get_location(), x, y);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLuint x, GLuint y, GLuint z)
{
	glVertexAttribI3ui(get_location(), x, y, z);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(GLuint x, GLuint y, GLuint z, GLuint w)
{
	glVertexAttribI4ui(get_location(), x, y, z, w);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const GLint* value)
{
	glVertexAttribI1iv(get_location(), value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::ivec2* value)
{
	glVertexAttribI2iv(get_location(), (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::ivec3* value)
{
	glVertexAttribI3iv(get_location(), (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::ivec4* value)
{
	glVertexAttribI4iv(get_location(), (GLint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const GLuint* value)
{
	glVertexAttribI1uiv(get_location(), value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::uvec2* value)
{
	glVertexAttribI2uiv(get_location(), (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::uvec3* value)
{
	glVertexAttribI3uiv(get_location(), (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::uvec4* value)
{
	glVertexAttribI4uiv(get_location(), (GLuint*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::cvec4* value)
{
	glVertexAttribI4bv(get_location(), (GLbyte*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::ucvec4* value)
{
	glVertexAttribI4ubv(get_location(), (GLubyte*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::svec4* value)
{
	glVertexAttribI4sv(get_location(), (GLshort*)value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetI(_In_ const glm::usvec4* value)
{
	glVertexAttribI4usv(get_location(), (GLushort*)value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void VertexAttrib::GetCurrentI(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribIiv(m_Location, GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::GetCurrentI(_Out_writes_(4) GLuint* params)
{
	glGetVertexAttribIuiv(m_Location, GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::PointerI(SizeI size, TypeI type, GLsizei stride, GLintptr offset)
{
	glVertexAttribIPointer(m_Location, (GLint)size, (GLenum)type, stride, (void*)offset);
}

inline void VertexAttrib::SetI(GLint x)
{
	glVertexAttribI1i(m_Location, x);
}

inline void VertexAttrib::SetI(GLint x, GLint y)
{
	glVertexAttribI2i(m_Location, x, y);
}

inline void VertexAttrib::SetI(GLint x, GLint y, GLint z)
{
	glVertexAttribI3i(m_Location, x, y, z);
}

inline void VertexAttrib::SetI(GLint x, GLint y, GLint z, GLint w)
{
	glVertexAttribI4i(m_Location, x, y, z, w);
}

inline void VertexAttrib::SetI(GLuint x)
{
	glVertexAttribI1ui(m_Location, x);
}

inline void VertexAttrib::SetI(GLuint x, GLuint y)
{
	glVertexAttribI2ui(m_Location, x, y);
}

inline void VertexAttrib::SetI(GLuint x, GLuint y, GLuint z)
{
	glVertexAttribI3ui(m_Location, x, y, z);
}

inline void VertexAttrib::SetI(GLuint x, GLuint y, GLuint z, GLuint w)
{
	glVertexAttribI4ui(m_Location, x, y, z, w);
}

inline void VertexAttrib::SetI(_In_ const GLint* value)
{
	glVertexAttribI1iv(m_Location, value);
}

inline void VertexAttrib::SetI(_In_ const glm::ivec2* value)
{
	glVertexAttribI2iv(m_Location, (GLint*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::ivec3* value)
{
	glVertexAttribI3iv(m_Location, (GLint*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::ivec4* value)
{
	glVertexAttribI4iv(m_Location, (GLint*)value);
}

inline void VertexAttrib::SetI(_In_ const GLuint* value)
{
	glVertexAttribI1uiv(m_Location, value);
}

inline void VertexAttrib::SetI(_In_ const glm::uvec2* value)
{
	glVertexAttribI2uiv(m_Location, (GLuint*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::uvec3* value)
{
	glVertexAttribI3uiv(m_Location, (GLuint*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::uvec4* value)
{
	glVertexAttribI4uiv(m_Location, (GLuint*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::cvec4* value)
{
	glVertexAttribI4bv(m_Location, (GLbyte*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::ucvec4* value)
{
	glVertexAttribI4ubv(m_Location, (GLubyte*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::svec4* value)
{
	glVertexAttribI4sv(m_Location, (GLshort*)value);
}

inline void VertexAttrib::SetI(_In_ const glm::usvec4* value)
{
	glVertexAttribI4usv(m_Location, (GLushort*)value);
}
#endif // #if defined (YAGLPP_VERSION_3_0) && defined (YAGLPP_INLINE_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)
void VertexAttrib::Divisor(GLuint divisor)
{
	glVertexAttribDivisor(get_location(), divisor);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP1(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP1ui(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP1(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP1uiv(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP2(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP2ui(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP2(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP2uiv(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP3(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP3ui(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP3(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP3uiv(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP4(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP4ui(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}

void VertexAttrib::SetP4(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP4uiv(get_location(), (GLenum)type, normalized, value);
	YAGLPP_GLAD_ERROR;
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_DEBUG_IMPLEMENTATION)

#if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
inline void VertexAttrib::Divisor(GLuint divisor)
{
	glVertexAttribDivisor(m_Location, divisor);
}

inline void VertexAttrib::SetP1(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP1ui(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP1(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP1uiv(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP2(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP2ui(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP2(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP2uiv(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP3(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP3ui(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP3(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP3uiv(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP4(TypeP type, GLboolean normalized, GLuint value)
{
	glVertexAttribP4ui(m_Location, (GLenum)type, normalized, value);
}

inline void VertexAttrib::SetP4(TypeP type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP4uiv(m_Location, (GLenum)type, normalized, value);
}
#endif // #if defined (YAGLPP_VERSION_3_3) && defined (YAGLPP_INLINE_IMPLEMENTATION)
} // namespace gl
#endif // #ifndef YAGLPP_VERTEX_ATTRIB_H
