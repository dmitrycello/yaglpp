#define YAGLPP_BUILD_LIB
#include <yaglpp/VertexAttrib.h>
#pragma comment(lib, "opengl32.lib")
namespace gl {
#ifdef _DEBUG
GLuint VertexAttrib::_location()
{
	_YAGLPP_ASSERT_(_miLocation > -1); // OPENGL VERTEX ATTRIBUTE LOCATION INDEX IS INVALID
	return _miLocation;
}

GLint VertexAttrib::_getVertexAttrib(GLenum ePname)
{
	GLint iResult;
	glGetVertexAttribiv(_location(), ePname, &iResult);
	_YAGLPP_GLAD_ERROR_;
	return iResult;
}

void VertexAttrib::bindAttribLocation(Program& program, _In_z_ const GLchar* name)
{
	glBindAttribLocation(program._program_id(), _location(), name);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::disableVertexAttribArray()
{
	glDisableVertexAttribArray(_location());
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::enableVertexAttribArray()
{
	glEnableVertexAttribArray(_location());
	_YAGLPP_GLAD_ERROR_;
}

GLboolean VertexAttrib::getAttribLocation(Program& program, _In_z_ const GLchar* name)
{
	_miLocation = glGetAttribLocation(program._program_id(), name);
	_YAGLPP_GLAD_ERROR_;
	return isVertexAttrib();
}

void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLfloat* params)
{
	glGetVertexAttribfv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::getCurrentVertexAttrib(_Out_writes_(4) GLdouble* params)
{
	glGetVertexAttribdv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	_YAGLPP_GLAD_ERROR_;
}

GLintptr VertexAttrib::getVertexAttribPointer()
{
	void* pData;
	glGetVertexAttribPointerv(_location(), GL_VERTEX_ATTRIB_ARRAY_POINTER, &pData);
	_YAGLPP_GLAD_ERROR_;
	return (GLintptr)pData;
}

void VertexAttrib::setAttribLocation(GLuint location)
{
	_YAGLPP_ASSERT_(location < getMaxVertexAttribs()); // OPENGL VERTEX ATTRIBUTE LOCATION VALUE IS UNSUPPORTED
	_miLocation = (GLint)location;
}

void VertexAttrib::vertexAttrib(GLfloat x)
{
    glVertexAttrib1f(_location(), x);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y)
{
    glVertexAttrib2f(_location(), x, y);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y, GLfloat z)
{
    glVertexAttrib3f(_location(), x, y, z);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glVertexAttrib4f(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLshort x)
{
    glVertexAttrib1s(_location(), x);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLshort x, GLshort y)
{
    glVertexAttrib2s(_location(), x, y);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLshort x, GLshort y, GLshort z)
{
    glVertexAttrib3s(_location(), x, y, z);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLshort x, GLshort y, GLshort z, GLshort w)
{
    glVertexAttrib4s(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLdouble x)
{
    glVertexAttrib1d(_location(), x);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y)
{
    glVertexAttrib2d(_location(), x, y);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y, GLdouble z)
{
    glVertexAttrib3d(_location(), x, y, z);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    glVertexAttrib4d(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const GLfloat* value)
{
    glVertexAttrib1fv(_location(), value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::vec2* value)
{
    glVertexAttrib2fv(_location(), (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::vec3* value)
{
    glVertexAttrib3fv(_location(), (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::vec4* value)
{
    glVertexAttrib4fv(_location(), (GLfloat*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const GLshort* value)
{
	glVertexAttrib1sv(_location(), value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::svec2* value)
{
	glVertexAttrib2sv(_location(), (GLshort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::svec3* value)
{
	glVertexAttrib3sv(_location(), (GLshort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::svec4* value)
{
	glVertexAttrib4sv(_location(), (GLshort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const GLdouble* value)
{
	glVertexAttrib1dv(_location(), value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::dvec2* value)
{
	glVertexAttrib2dv(_location(), (GLdouble*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::dvec3* value)
{
	glVertexAttrib3dv(_location(), (GLdouble*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::dvec4* value)
{
	glVertexAttrib4dv(_location(), (GLdouble*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::cvec4* value)
{
	glVertexAttrib4bv(_location(), (GLbyte*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::ucvec4* value)
{
	glVertexAttrib4ubv(_location(), (GLubyte*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::usvec4* value)
{
	glVertexAttrib4usv(_location(), (GLushort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::ivec4* value)
{
	glVertexAttrib4iv(_location(), (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib(_In_ const glm::uvec4* value)
{
	glVertexAttrib4uiv(_location(), (unsigned int*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	glVertexAttrib4Nub(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLbyte* xyzw)
{
	glVertexAttrib4Nbv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLubyte* xyzw)
{
	glVertexAttrib4Nubv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLshort* xyzw)
{
	glVertexAttrib4Nsv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLushort* xyzw)
{
	glVertexAttrib4Nusv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLint* xyzw)
{
	glVertexAttrib4Niv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttrib4N(_In_reads_(4) const GLuint* xyzw)
{
	glVertexAttrib4Nuiv(_location(), xyzw);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribPointer(VertexAttribSize size, VertexAttribType type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer(_location(), (GLint)size, (GLenum)type, normalized, stride, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}

#ifdef GL_VERSION_3_0
void VertexAttrib::getCurrentVertexAttribI(_Out_writes_(4) GLint* params)
{
	glGetVertexAttribIiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::getCurrentVertexAttribI(_Out_writes_(4) GLuint* params)
{
	glGetVertexAttribIuiv(_location(), GL_CURRENT_VERTEX_ATTRIB, params);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLint x)
{
    glVertexAttribI1i(_location(), x);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLint x, GLint y)
{
    glVertexAttribI2i(_location(), x, y);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLint x, GLint y, GLint z)
{
    glVertexAttribI3i(_location(), x, y, z);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLint x, GLint y, GLint z, GLint w)
{
    glVertexAttribI4i(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLuint x)
{
    glVertexAttribI1ui(_location(), x);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLuint x, GLuint y)
{
    glVertexAttribI2ui(_location(), x, y);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLuint x, GLuint y, GLuint z)
{
    glVertexAttribI3ui(_location(), x, y, z);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(GLuint x, GLuint y, GLuint z, GLuint w)
{
    glVertexAttribI4ui(_location(), x, y, z, w);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const GLint* value)
{
	glVertexAttribI1iv(_location(), value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::ivec2* value)
{
	glVertexAttribI2iv(_location(), (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::ivec3* value)
{
	glVertexAttribI3iv(_location(), (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::ivec4* value)
{
	glVertexAttribI4iv(_location(), (GLint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const GLuint* value)
{
	glVertexAttribI1uiv(_location(), value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::uvec2* value)
{
	glVertexAttribI2uiv(_location(), (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::uvec3* value)
{
	glVertexAttribI3uiv(_location(), (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::uvec4* value)
{
	glVertexAttribI4uiv(_location(), (GLuint*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::cvec4* value)
{
	glVertexAttribI4bv(_location(), (GLbyte*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::ucvec4* value)
{
	glVertexAttribI4ubv(_location(), (GLubyte*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::svec4* value)
{
	glVertexAttribI4sv(_location(), (GLshort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribI(_In_ const glm::usvec4* value)
{
	glVertexAttribI4usv(_location(), (GLushort*)value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribIPointer(VertexAttribISize size, VertexAttribIType type, GLsizei stride, GLintptr offset)
{
	glVertexAttribIPointer(_location(), (GLint)size, (GLenum)type, stride, (void*)offset);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_0

#ifdef GL_VERSION_3_3
void VertexAttrib::vertexAttribDivisor(GLuint divisor)
{
	glVertexAttribDivisor(_location(), divisor);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP1(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP1ui(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP1(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP1uiv(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP2(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP2ui(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP2(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP2uiv(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP3(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP3ui(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP3(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP3uiv(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP4(VertexAttribPType type, GLboolean normalized, GLuint value)
{
	glVertexAttribP4ui(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}

void VertexAttrib::vertexAttribP4(VertexAttribPType type, GLboolean normalized, _In_ GLuint* value)
{
	glVertexAttribP4uiv(_location(), (GLenum)type, normalized, value);
	_YAGLPP_GLAD_ERROR_;
}
#endif // #ifdef GL_VERSION_3_3
#endif // #ifdef _DEBUG
} // namespace gl
