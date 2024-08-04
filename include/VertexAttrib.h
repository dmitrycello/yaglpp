#pragma once
#include "gladpp.h"
namespace gl {
/*GLAD active attribute type enumerator*/
enum class ActiveAttribType : GLenum
{
	/*Attribute of <Float> type*/
	Float = GL_FLOAT,

	/*Attribute of <FloatVec2> type*/
	FloatVec2 = GL_FLOAT_VEC2,

	/*Attribute of <FloatVec3> type*/
	FloatVec3 = GL_FLOAT_VEC3,

	/*Attribute of <FloatVec4> type*/
	FloatVec4 = GL_FLOAT_VEC4,

	/*Attribute of <FloatMat2> type*/
	FloatMat2 = GL_FLOAT_MAT2,

	/*Attribute of <FloatMat3> type*/
	FloatMat3 = GL_FLOAT_MAT3,

	/*Attribute of <FloatMat4> type*/
	FloatMat4 = GL_FLOAT_MAT4,

	/*Attribute of <Double> type*/
	Double = GL_DOUBLE,

	/*Attribute of <Int> type*/
	Int = GL_INT,

	/*Attribute of <IntVec2> type*/
	IntVec2 = GL_INT_VEC2,

	/*Attribute of <IntVec3> type*/
	IntVec3 = GL_INT_VEC3,

	/*Attribute of <IntVec4> type*/
	IntVec4 = GL_INT_VEC4,

	/*Attribute of <UnsignedInt> type*/
	UnsignedInt = GL_UNSIGNED_INT,

#ifdef GL_VERSION_2_1
	/*(2.1) Attribute of <FloatMat2x3> type*/
	FloatMat2x3 = GL_FLOAT_MAT2x3,

	/*(2.1) Attribute of <FloatMat2x4> type*/
	FloatMat2x4 = GL_FLOAT_MAT2x4,

	/*(2.1) Attribute of <FloatMat3x2> type*/
	FloatMat3x2 = GL_FLOAT_MAT3x2,

	/*(2.1) Attribute of <FloatMat3x2> type*/
	FloatMat3x4 = GL_FLOAT_MAT3x4,

	/*(2.1) Attribute of <FloatMat4x2> type*/
	FloatMat4x2 = GL_FLOAT_MAT4x2,

	/*(2.1) Attribute of <FloatMat4x3> type*/
	FloatMat4x3 = GL_FLOAT_MAT4x3,
#endif // #ifdef GL_VERSION_2_1

#ifdef GL_VERSION_3_0
	/*(3.0) Attribute of <UnsignedIntVec2> type*/
	UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,

	/*(3.0) Attribute of <UnsignedIntVec2> type*/
	UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,

	/*(3.0) Attribute of <UnsignedIntVec2> type*/
	UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,
#endif // #ifdef GL_VERSION_3_0
};

/*GLAD vertex attribute data size enumerator (1 to 4 or <Bgra>), default 4*/
enum class VertexAttribSize : GLsizei
{
	/*One-component attribute value*/
	Single = 1,
	
	/*Two-component attribute value*/
	Double = 2,
	
	/*Three-component attribute value*/
	Triple = 3,
	
	/*Four-component attribute value, this is initial value*/
	Quadruple = 4,
	
	/*Additionally accepted reversed four-component attribute value*/
	Bgra = GL_BGRA,
};

/*GLAD vertex attribute data type enumerator*/
enum class VertexAttribType : GLenum
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
	PackedUint = GL_UNSIGNED_INT_2_10_10_10_REV,

#ifdef GL_VERSION_3_0
	/*(3.0) 16-bit IEEE-754 floating-point value*/
	HalfFloat = GL_HALF_FLOAT,

	/*(3.0) 32-bit unsigned integer value packed as three float numbers 10:11:11*/
	PackedFloat = GL_UNSIGNED_INT_10F_11F_11F_REV,
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
	/*(3.3) 32-bit signed integer value packed as four numbers 2:10:10:10*/
	PackedInt = GL_INT_2_10_10_10_REV,
#endif // #ifdef GL_VERSION_3_3
};

#ifdef GL_VERSION_3_0
/*(3.0) GLAD vertex attribute integer data size enumerator (1 to 4)*/
enum class VertexAttribISize : GLsizei
{
	/*(3.0) One-component attribute value*/
	Single = 1,

	/*(3.0) Two-component attribute value*/
	Double = 2,

	/*(3.0) Three-component attribute value*/
	Triple = 3,

	/*(3.0) Four-component attribute value*/
	Quadruple = 4,
};

/*(3.0) GLAD vertex attribute integer data type enumerator*/
enum class VertexAttribIType : GLenum
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
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
/*(3.3) GLAD vertex attribute packed data type enumerator*/
enum class VertexAttribPType : GLenum
{
	/*(3.3) 32-bit unsigned integer value packed as four numbers 2:10:10:10*/
	PackedUint = GL_UNSIGNED_INT_2_10_10_10_REV,

	/*(3.3) 32-bit unsigned integer value packed as three float numbers 10:11:11*/
	PackedFloat = GL_UNSIGNED_INT_10F_11F_11F_REV,

	/*(3.3) 32-bit signed integer value packed as four numbers 2:10:10:10*/
	PackedInt = GL_INT_2_10_10_10_REV,
};
#endif // #ifdef GL_VERSION_3_3

/*OpenGL vertex attribute object root class*/
class VertexAttrib
{
private:
	GLint m_iLocation; // Attribute index
	GLint _getVertexAttrib(GLenum ePname);
	GLuint _location();

public:
	/*(1) Constructs unassigned vertex attribute object*/
	VertexAttrib()
	{
		m_iLocation = -1;
	}

	/*(2) Constructs vertex attribute object with <setAttribLocation>*/
	VertexAttrib(GLuint location)
	{
		setAttribLocation(location);
	}

	/*(3) Constructs vertex attribute object with <getAttribLocation>*/
	VertexAttrib(Program& program, _In_z_ const GLchar* name)
	{
		getAttribLocation(program, name);
	}

	/*Associates a generic vertex attribute object with a named attribute variable
	@param Specifies the program object in which the association is to be made
	@param [in] Specifies a null terminated string containing the name of the vertex shader attribute variable to which object is to be bound*/
	void bindAttribLocation(Program& program, _In_z_ const GLchar* name);

	/*Disables a generic vertex attribute array*/
	void disableVertexAttribArray();

	/*Enables a generic vertex attribute array*/
	void enableVertexAttribArray();

	/*Queries the previously linked program object for the location of a vertex attribute object
	@param Specifies the program object to be queried
	@param [in] Points to a null terminated string containing the name of the attribute variable whose location is to be queried
	@return True if attribute location retrieved, false otherwise*/
	GLboolean getAttribLocation(Program& program, _In_z_ const GLchar* name);

	/*(1) Returns four integer values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested integer data*/
	void getCurrentVertexAttrib(_Out_writes_(4) GLint* params);

	/*(2) Returns four float values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested float data*/
	void getCurrentVertexAttrib(_Out_writes_(4) GLfloat* params);

	/*(3) Returns four double values that represent the current value for the generic vertex attribute
	@param [out] Returns the requested double data*/
	void getCurrentVertexAttrib(_Out_writes_(4) GLdouble* params);

	/*Returns maximum number of 4-component generic vertex attributes accessible to vertex shader, must be at least 16
	@return The maximum number of vertex attributes*/
	static GLuint getMaxVertexAttribs()
	{
		return _getInteger(GL_MAX_VERTEX_ATTRIBS);
	}

	/*Gets tha vertex attribute enabled flag
	@return True if vertex attribute is enabled*/
	GLboolean getVertexAttribArrayEnabled()
	{
		return _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_ENABLED);
	}

	/*Gets the data size of the vertex attribute array for current vertex attribute
	@return The number of values for each element of the vertex attribute array*/
	VertexAttribSize getVertexAttribArraySize()
	{
		return (VertexAttribSize)_getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_SIZE);
	}

	/*Gets the array stride for the vertex attribute array for current vertex attribute. A value of 0 indicates that the array elements are stored sequentially in memory
	@return The number of bytes between successive elements in the vertex attribute array*/
	GLsizei getVertexAttribArrayStride()
	{
		return _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_STRIDE);
	}

	/*Gets a boolean value that is true if fixed-point data type for the vertex attribute is normalized when converted to floating point, and false otherwise
	@return The vertex attribute normalized flag*/
	GLboolean getVertexAttribArrayNormalized()
	{
		return _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED);
	}

	/*Gets a value indicating the array type for the vertex attribute
	@return The type of vertex attribute*/
	VertexAttribType getVertexAttribArrayType()
	{
		return (VertexAttribType)_getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_TYPE);
	}

	/*Returns the vertex attribute's memory byte offset into the data store of the array buffer object that was bound to target when the desired pointer was previously specified
	@return The attribute's previously specified memory byte offset*/
	GLintptr getVertexAttribPointer();

	/*Checks if retrieved attribute is valid
	@return True if valid attribute, false otherwise*/
	GLboolean isVertexAttrib()
	{
		return m_iLocation > -1;
	}

	/*Checks if the vertex array buffer object is currently bound to the binding point corresponding to generic vertex attribute array
	@param The vertex array buffer object (VBO)
	@return True if the VBO is currently bound to the VAO's binding point, false otherwise*/
	GLboolean isVertexAttribArrayBufferBinding(ArrayBuffer& buffer);

	/*Directly assigns the location of a vertex attribute object
	@param Location value of the vertex attribute, must be less than the value returned by <getMaxVertexAttribs>*/
	void setAttribLocation(GLuint location);

	/*(1) Specifies the single float value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLfloat x);

	/*(2) Specifies the two float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLfloat x, GLfloat y);

	/*(3) Specifies the three float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLfloat x, GLfloat y, GLfloat z);

	/*(4) Specifies the four float values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	/*(5) Specifies the single short value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLshort x);

	/*(6) Specifies the two short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLshort x, GLshort y);

	/*(7) Specifies the three short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLshort x, GLshort y, GLshort z);

	/*(8) Specifies the four short values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLshort x, GLshort y, GLshort z, GLshort w);

	/*(9) Specifies the single double value of a generic vertex attribute
	@param Specifies the new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLdouble x);

	/*(10) Specifies the two double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLdouble x, GLdouble y);

	/*(11) Specifies the three double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLdouble x, GLdouble y, GLdouble z);

	/*(12) Specifies the four double values of a generic vertex attribute
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttrib(GLdouble x, GLdouble y, GLdouble z, GLdouble w);

	/*(13) Specifies the float array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const GLfloat* value);

	/*(14) Specifies the two-component float array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::vec2* value);

	/*(15) Specifies the three-component float array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::vec3* value);

	/*(16) Specifies the four-component float array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::vec4* value);

	/*(17) Specifies the short array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const GLshort* value);

	/*(18) Specifies the two-component short array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::svec2* value);

	/*(19) Specifies the three-component short array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::svec3* value);

	/*(20) Specifies the four-component short array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::svec4* value);

	/*(21) Specifies the double array of a generic vertex attribute
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const GLdouble* value);

	/*(22) Specifies the two-component double array of a generic vertex attribute
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::dvec2* value);

	/*(23) Specifies the three-component double array of a generic vertex attribute
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::dvec3* value);

	/*(24) Specifies the four-component double array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::dvec4* value);

	/*(25) Specifies the four-component char array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::cvec4* value);

	/*(26) Specifies the four-component unsigned char array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::ucvec4* value);

	/*(28) Specifies the four-component unsigned short array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::usvec4* value);

	/*(28) Specifies the four-component integer array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::ivec4* value);

	/*(29) Specifies the four-component unsigned integer array of a generic vertex attribute
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib(_In_ const glm::uvec4* value);

	/*(1) Specifies the four normalized unsigned char values of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttrib4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	/*(2) Specifies the normalized four-component char array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLbyte* xyzw);

	/*(3) Specifies the normalized four-component unsigned char array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLubyte* xyzw);

	/*(4) Specifies the normalized four-component short array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLshort* xyzw);

	/*(5) Specifies the normalized four-component unsigned short array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLushort* xyzw);

	/*(6) Specifies the normalized four-component integer array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLint* xyzw);

	/*(7) Specifies the normalized four-component unsigned integer array of a generic vertex attribute. The arguments will be passed as fixed-point values that are scaled to a normalized range according to the component conversion rules defined by the OpenGL specification
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttrib4N(_In_reads_(4) const GLuint* xyzw);

	/*Defines the generic vertex attribute data
	@param Specifies the number of components per generic vertex attribute
	@param Specifies the data type of each component in the array
	@param Specifies whether fixed-point data values should be normalized (true) or converted directly as fixed-point values (false) when they are accessed
	@param Specifies the byte offset between consecutive generic vertex attributes
	@param Specifies the byte offset of the first component of the first generic vertex attribute in the vertex array buffer data store*/
	void vertexAttribPointer(VertexAttribSize size, VertexAttribType type, GLboolean normalized, GLsizei stride, GLintptr offset);

#ifdef GL_VERSION_3_0
	/*(3.0) (1) Gets four integer values that represent the current value for the generic vertex attribute extended to full signed integer
	@param [out] Returns the requested integer data*/
	void getCurrentVertexAttribI(_Out_writes_(4) GLint* params);

	/*(3.0) (2) Gets four unsigned integer values that represent the current value for the generic vertex attribute extended to full unsigned integer
	@param [out] Returns the requested unsigned integer data*/
	void getCurrentVertexAttribI(_Out_writes_(4) GLuint* params);

	/*(3.0) Gets a boolean value that is true if fixed-point data type for the vertex attribute have integer data types, and false otherwise
	@return The vertex attribute integer flag*/
	GLboolean getVertexAttribArrayInteger()
	{
		return _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_INTEGER);
	}

	/*(3.0) (1) Specifies the single integer value of a generic vertex attribute. The argument is extended to full signed integer
	@param Specifies the new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLint x);

	/*(3.0) (2) Specifies the two integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLint x, GLint y);

	/*(3.0) (3) Specifies the three integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLint x, GLint y, GLint z);

	/*(3.0) (4) Specifies the four integer values of a generic vertex attribute. The arguments are extended to full signed integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLint x, GLint y, GLint z, GLint w);

	/*(3.0) (5) Specifies the single unsigned integer value of a generic vertex attribute. The argument is extended to full unsigned integer
	@param Specifies the new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLuint x);

	/*(3.0) (6) Specifies the two unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLuint x, GLuint y);

	/*(3.0) (7) Specifies the three unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLuint x, GLuint y, GLuint z);

	/*(3.0) (8) Specifies the four unsigned integer values of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param Specifies the first new value to be used for the specified vertex attribute
	@param Specifies the second new value to be used for the specified vertex attribute
	@param Specifies the third new value to be used for the specified vertex attribute
	@param Specifies the fourth new value to be used for the specified vertex attribute*/
	void vertexAttribI(GLuint x, GLuint y, GLuint z, GLuint w);

	/*(3.0) (9) Specifies the integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const GLint* value);

	/*(3.0) (10) Specifies the two-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::ivec2* value);

	/*(3.0) (11) Specifies the three-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::ivec3* value);

	/*(3.0) (12) Specifies the four-component integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::ivec4* value);

	/*(3.0) (13) Specifies the unsigned integer array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const GLuint* value);

	/*(3.0) (14) Specifies the two-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of two-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::uvec2* value);

	/*(3.0) (15) Specifies the three-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of three-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::uvec3* value);

	/*(3.0) (16) Specifies the four-component unsigned integer array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::uvec4* value);

	/*(3.0) (17) Specifies the four-component char array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::cvec4* value);

	/*(3.0) (18) Specifies the four-component unsigned char array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::ucvec4* value);

	/*(3.0) (19) Specifies the four-component short array of a generic vertex attribute. The arguments are extended to full signed integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::svec4* value);

	/*(3.0) (20) Specifies the four-component unsigned short array of a generic vertex attribute. The arguments are extended to full unsigned integers
	@param [in] Pointer to an array of four-component values to be used for the generic vertex attribute*/
	void vertexAttribI(_In_ const glm::usvec4* value);

	/*(3.0) Defines the generic vertex attribute data. Values are always left as integer values
	@param Specifies the number of components per generic vertex attribute
	@param Specifies the integer data type of each component in the array
	@param Specifies the byte offset between consecutive generic vertex attributes
	@param Specifies the byte offset of the first component of the first generic vertex attribute in the vertex array buffer data store*/
	void vertexAttribIPointer(VertexAttribISize size, VertexAttribIType type, GLsizei stride, GLintptr offset);
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
	/*(3.3) Gets a value that is the frequency divisor used for instanced rendering
	@return The vertex attribute divisor value. The initial value is 0*/
	GLuint getVertexAttribArrayDivisor()
	{
		return _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_DIVISOR);
	}

	/*(3.3) Modify the rate at which generic vertex attributes advance during instanced rendering
	@param Specify the number of instances that will pass between updates of the generic attribute*/
	void vertexAttribDivisor(GLuint divisor);

	/*(3.3) (1) Specifies the packed value of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void vertexAttribP1(VertexAttribPType type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of packed values of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of the new packed values to be used for the specified vertex attribute*/
	void vertexAttribP1(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with two packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void vertexAttribP2(VertexAttribPType type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of values with two packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with two packed components to be used for the specified vertex attribute*/
	void vertexAttribP2(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with three packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void vertexAttribP3(VertexAttribPType type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the array of values with three packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with three packed components to be used for the specified vertex attribute*/
	void vertexAttribP3(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value);

	/*(3.3) (1) Specifies the value with four packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param Specifies the new packed value to be used for the specified vertex attribute*/
	void vertexAttribP4(VertexAttribPType type, GLboolean normalized, GLuint value);

	/*(3.3) (2) Specifies the packed value with four packed components of a generic vertex attribute
	@param Specifies the packed data type of each component
	@param If true, then the values are to be converted to floating point values by normalizing. Otherwise, they are converted directly to floating-point values
	@param [in] Pointer to array of new values with three packed components to be used for the specified vertex attribute*/
	void vertexAttribP4(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value);
#endif // #ifdef GL_VERSION_3_3
}; // class VertexAttrib
} // namespace gl

#include "_Buffer.h"
#include "Program.h"
namespace gl {
inline GLboolean VertexAttrib::isVertexAttribArrayBufferBinding(ArrayBuffer& buffer)
{
	return ((_Buffer&)buffer)._buffer_id() == _getVertexAttrib(GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
}

#ifndef _DEBUG
inline GLuint VertexAttrib::_location()
{
	return m_iLocation;
}

inline GLint VertexAttrib::_getVertexAttrib(GLenum ePname)
{
	GLint i; glGetVertexAttribiv(_location(), ePname, &i); return i;
}

inline void VertexAttrib::bindAttribLocation(Program& program, _In_z_ const GLchar* name)
{
	glBindAttribLocation(program._program_id(), _location(), name);
}

inline void VertexAttrib::disableVertexAttribArray()
{
	glDisableVertexAttribArray(_location());
}

inline void VertexAttrib::enableVertexAttribArray()
{
	glEnableVertexAttribArray(_location());
}

inline GLboolean VertexAttrib::getAttribLocation(Program& program, _In_z_ const GLchar* name)
{
	m_iLocation = glGetAttribLocation(program._program_id(), name);
	return m_iLocation > -1;
}

inline void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLfloat* params)
{
	glGetVertexAttribfv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLdouble* params)
{
	glGetVertexAttribdv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
}

inline GLintptr VertexAttrib::getVertexAttribPointer()
{
	void* p; glGetVertexAttribPointerv(_location(), GL_VERTEX_ATTRIB_ARRAY_POINTER, &p); return (GLintptr)p;
}

inline void VertexAttrib::setAttribLocation(GLuint location)
{
	m_iLocation = (GLint)location;
}

inline void VertexAttrib::vertexAttrib(GLfloat x)
{
	glVertexAttrib1f(_location(), x);
}

inline void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y)
{
	glVertexAttrib2f(_location(), x, y);
}

inline void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y, GLfloat z)
{
	glVertexAttrib3f(_location(), x, y, z);
}

inline void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glVertexAttrib4f(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttrib(GLshort x)
{
	glVertexAttrib1s(_location(), x);
}

inline void VertexAttrib::vertexAttrib(GLshort x, GLshort y)
{
	glVertexAttrib2s(_location(), x, y);
}

inline void VertexAttrib::vertexAttrib(GLshort x, GLshort y, GLshort z)
{
	glVertexAttrib3s(_location(), x, y, z);
}

inline void VertexAttrib::vertexAttrib(GLshort x, GLshort y, GLshort z, GLshort w)
{
	glVertexAttrib4s(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttrib(GLdouble x)
{
	glVertexAttrib1d(_location(), x);
}

inline void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y)
{
	glVertexAttrib2d(_location(), x, y);
}

inline void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y, GLdouble z)
{
	glVertexAttrib3d(_location(), x, y, z);
}

inline void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	glVertexAttrib4d(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttrib(_In_ const GLfloat* value)
{
	glVertexAttrib1fv(_location(), value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::vec2* value)
{
	glVertexAttrib2fv(_location(), (GLfloat*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::vec3* value)
{
	glVertexAttrib3fv(_location(), (GLfloat*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::vec4* value)
{
	glVertexAttrib4fv(_location(), (GLfloat*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const GLshort* value)
{
	glVertexAttrib1sv(_location(), value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::svec2* value)
{
	glVertexAttrib2sv(_location(), (GLshort*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::svec3* value)
{
	glVertexAttrib3sv(_location(), (GLshort*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::svec4* value)
{
	glVertexAttrib4sv(_location(), (GLshort*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const GLdouble* value)
{
	glVertexAttrib1dv(_location(), value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::dvec2* value)
{
	glVertexAttrib2dv(_location(), (GLdouble*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::dvec3* value)
{
	glVertexAttrib3dv(_location(), (GLdouble*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::dvec4* value)
{
	glVertexAttrib4dv(_location(), (GLdouble*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::cvec4* value)
{
	glVertexAttrib4bv(_location(), (GLbyte*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::ucvec4* value)
{
	glVertexAttrib4ubv(_location(), (GLubyte*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::usvec4* value)
{
	glVertexAttrib4usv(_location(), (GLushort*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::ivec4* value)
{
	glVertexAttrib4iv(_location(), (GLint*)value);
}

inline void VertexAttrib::vertexAttrib(_In_ const glm::uvec4* value)
{
	glVertexAttrib4uiv(_location(), (unsigned int*)value);
}

inline void VertexAttrib::vertexAttrib4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	glVertexAttrib4Nub(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLbyte* xyzw)
{
	glVertexAttrib4Nbv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLubyte* xyzw)
{
	glVertexAttrib4Nubv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLshort* xyzw)
{
	glVertexAttrib4Nsv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLushort* xyzw)
{
	glVertexAttrib4Nusv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLint* xyzw)
{
	glVertexAttrib4Niv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLuint* xyzw)
{
	glVertexAttrib4Nuiv(_location(), xyzw);
}

inline void VertexAttrib::vertexAttribPointer(VertexAttribSize size, VertexAttribType type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer(_location(), (GLint)size, (GLenum)type, normalized, stride, (void*)offset);
}

#ifdef GL_VERSION_3_0
inline void VertexAttrib::getCurrentVertexAttribI(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribIiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::getCurrentVertexAttribI(_Out_writes_(4) GLuint* params)
{
	glGetVertexAttribIuiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
}

inline void VertexAttrib::vertexAttribI(GLint x)
{
	glVertexAttribI1i(_location(), x);
}

inline void VertexAttrib::vertexAttribI(GLint x, GLint y)
{
	glVertexAttribI2i(_location(), x, y);
}

inline void VertexAttrib::vertexAttribI(GLint x, GLint y, GLint z)
{
	glVertexAttribI3i(_location(), x, y, z);
}

inline void VertexAttrib::vertexAttribI(GLint x, GLint y, GLint z, GLint w)
{
	glVertexAttribI4i(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttribI(GLuint x)
{
	glVertexAttribI1ui(_location(), x);
}

inline void VertexAttrib::vertexAttribI(GLuint x, GLuint y)
{
	glVertexAttribI2ui(_location(), x, y);
}

inline void VertexAttrib::vertexAttribI(GLuint x, GLuint y, GLuint z)
{
	glVertexAttribI3ui(_location(), x, y, z);
}

inline void VertexAttrib::vertexAttribI(GLuint x, GLuint y, GLuint z, GLuint w)
{
	glVertexAttribI4ui(_location(), x, y, z, w);
}

inline void VertexAttrib::vertexAttribI(_In_ const GLint* value)
{
	glVertexAttribI1iv(_location(), value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::ivec2* value)
{
	glVertexAttribI2iv(_location(), (GLint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::ivec3* value)
{
	glVertexAttribI3iv(_location(), (GLint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::ivec4* value)
{
	glVertexAttribI4iv(_location(), (GLint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const GLuint* value)
{
	glVertexAttribI1uiv(_location(), value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::uvec2* value)
{
	glVertexAttribI2uiv(_location(), (GLuint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::uvec3* value)
{
	glVertexAttribI3uiv(_location(), (GLuint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::uvec4* value)
{
	glVertexAttribI4uiv(_location(), (GLuint*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::cvec4* value)
{
	glVertexAttribI4bv(_location(), (GLbyte*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::ucvec4* value)
{
	glVertexAttribI4ubv(_location(), (GLubyte*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::svec4* value)
{
	glVertexAttribI4sv(_location(), (GLshort*)value);
}

inline void VertexAttrib::vertexAttribI(_In_ const glm::usvec4* value)
{
	glVertexAttribI4usv(_location(), (GLushort*)value);
}

inline void VertexAttrib::vertexAttribIPointer(VertexAttribISize size, VertexAttribIType type, GLsizei stride, GLintptr offset)
{
	glVertexAttribIPointer(_location(), (GLint)size, (GLenum)type, stride, (void*)offset);
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
inline void VertexAttrib::vertexAttribDivisor(GLuint divisor)
{
	glVertexAttribDivisor(_location(), divisor);
}

inline void VertexAttrib::vertexAttribP1(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP1ui(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP1(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP1uiv(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP2(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP2ui(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP2(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP2uiv(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP3(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP3ui(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP3(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP3uiv(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP4(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP4ui(_location(), (GLenum)type, normalized, value);
}

inline void VertexAttrib::vertexAttribP4(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP4uiv(_location(), (GLenum)type, normalized, value);
}
#endif // #ifdef GL_VERSION_3_3
#endif // #ifdef _DEBUG
} // namespace gl
