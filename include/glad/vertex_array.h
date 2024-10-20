#pragma once
#include <yaglpp/glad/_object.h>
#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL vertex array object class (VAO) derived from <_Object>*/
class VertexArray : public _Object
{
protected:
	VertexArray(GLint name) { _object_set(name); }
	void _vertex_delete() {
		_object_delete(glDeleteVertexArrays);
	}
	void _vertex_dup(_Object& source) {
		_object_dup(glDeleteVertexArrays, source);
	}
	void _vertex_gen() {
		_object_gen(glGenVertexArrays, glDeleteVertexArrays, 1);
	}
	GLuint _vertex_id() {
		return _object_id(glGenVertexArrays, 1);
	}
	void _vertex_ref(_Object& source) {
		_object_ref(glDeleteVertexArrays, source);
	}

public:
	/*(3.0) (1) Constructs an empty vertex array object*/
	VertexArray() {}

	/*(3.0) (2) Constructs a copy of vertex array object*/
	VertexArray(const VertexArray& vertex)
	{
		_vertex_dup((_Object&)vertex);
	}

	/*(3.0) Cleans up the valid vertex array object*/
	~VertexArray()
	{
		_vertex_delete();
	}

	/*(3.0) Explicitly binds vertex array object to its target. Does nothing if specified vertex array is bound*/
	void bindVertexArray();

	/*(3.0) Explicitly deletes previously generated single vertex array object*/
	void deleteVertexArray()
	{
		_vertex_delete();
	}

	/*(3.0) Duplicates a vertex array object. If the source is a single object, its reference flag become true, while setting the destination as a single object (reference flag transfer)
	@param Specifies the source vertex array object*/
	void duplicateVertexArray(const VertexArray& vertex)
	{
		_vertex_dup((_Object&)vertex);
	}

	/*(3.0) Explicitly generates single vertex array object*/
	void genVertexArray()
	{
		_vertex_gen();
	}

	/*(3.0) Returns a reference vertex array object currently bound to the context
	@return The reference vertex array object, or empty object*/
	static VertexArray getVertexArrayBinding()
	{
		return VertexArray(_getInteger(GL_VERTEX_ARRAY_BINDING));
	}

	/*(3.0) Determines if a name corresponds to a vertex array object. Used as a getter of <vertexArray> property
	@return True if active vertex array object, false otherwise*/
	GLboolean isVertexArray()
	{
		return glIsVertexArray(_object_id());
	}

	/*(3.0) Determines if the vertex array object is currently bound to the context. Used as a getter of <vertexArrayBinding> property
	@return True if vertex array object currently bound to its target, or false otherwise*/
	GLboolean isVertexArrayBinding()
	{
		return _object_id() == _getInteger(GL_VERTEX_ARRAY_BINDING);
	}

	/*(3.0) Makes a reference of a vertex array object, regardless of the source object's reference flag
	@param Specifies the source vertex array object*/
	void referenceVertexArray(const VertexArray& vertex)
	{
		_vertex_ref((_Object&)vertex);
	}

	/*(3.0) Sets the creation state of the vertex array object, only if current state is opposite. Depending of the flag value, calls <genVertexArray> or <deleteVertexArray> functions. Used as a setter of <vertexArray> property
	@param True to generate vertex array object name, false to delete vertex array object*/
	void setVertexArray(GLboolean gen);

	/*(3.0) Sets the binding state of the vertex array object, only if current state is opposite. Used as a setter of <vertexArrayBinding> property
	@param True to bind the object to its target, false to unbind*/
	void setVertexArrayBinding(GLboolean bind)
	{
		(bind) ? bindVertexArray() : unbindVertexArray();
	}

	/*(3.0) Explicitly unbinds specified vertex array object from its target. Does nothing if specified vertex array is not bound*/
	void unbindVertexArray();

	/*(3.0) Explicitly unbinds any vertex array object of specified type bound to its target. Does nothing if no such vertex array is bound*/
	static void unbindTarget();

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-write property for creation state of the vertex array object*/
	__declspec(property(get = isVertexArray, put = setVertexArray)) GLboolean vertexArray;

	/*(3.0) Read-write property for binding state of the vertex array object*/
	__declspec(property(get = isVertexArrayBinding, put = setVertexArrayBinding)) GLboolean vertexArrayBinding;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class VertexArray : public _Object


/*(3.0) OpenGL vertex array multi-object class derived from <_Objects>*/
class VertexArrays : public _Objects
{
protected:
	void _vertices_delete() {
		_objects_delete(glDeleteVertexArrays);
	}
	void _vertices_dup(_Objects& source) {
		_objects_dup(glDeleteVertexArrays, source);
	}
	void _vertices_gen(GLsizei n) {
		_objects_gen(glGenVertexArrays, glDeleteVertexArrays, n);
	}
public:
	/*(3.0) (1) Constructs an empty vertex array multi-object*/
	VertexArrays() {}

	/*(3.0) (2) Constructs a copy of vertex array multi-object*/
	VertexArrays(const VertexArrays& vertices)
	{
		_vertices_dup((_Objects&)vertices);
	}

	/*(3.0) (3) Constucts an initialized vertex array multi-object*/
	VertexArrays(GLsizei n)
	{
		_vertices_gen(n);
	}

	/*(3.0) Cleans up the valid vertex array multi-object*/
	~VertexArrays()
	{
		_vertices_delete();
	}

	/*(3.0) Deletes valid vertex array multi-object*/
	void deleteVertexArrays()
	{
		_vertices_delete();
	}

	/*(3.0) Duplicates a vertex array object. If the source is a single object, its reference flag become true, while setting the destination as a single object (reference flag transfer)
	@param Specifies the source vertex array object*/
	void duplicateVertexArrays(const VertexArrays& vertices)
	{
		_vertices_dup((_Objects&)vertices);
	}

	/*(3.0) Generates one or more vertex array object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genVertexArrays(GLsizei n)
	{
		_vertices_gen(n);
	}
}; // class VertexArrays : public _Objects

/*(3.0) Returns a reference vertex array object currently bound to the context
@return The reference vertex array object, or empty object*/
inline VertexArray getVertexArrayBinding()
{
	return VertexArray::getVertexArrayBinding();
}

/*(3.0) Explicitly unbinds any vertex array object bound to its target. Does nothing if no vertex array is bound*/
inline void unbindVertexArray()
{
	VertexArray::unbindTarget();
}

#ifdef YAGLPP_IMPLEMENTATION
void VertexArray::bindVertexArray()
{
	GLuint uBound, uId = _object_id(glGenVertexArrays, 1);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	if (uBound != uId)
	{
		glBindVertexArray(uId);
		YAGLPP_GLAD_ERROR;
	}
}

void VertexArray::setVertexArray(GLboolean gen)
{
	if (isObject())
	{
		if (gen == GL_FALSE)
		{
			_vertex_delete();
		}
	}
	else if (gen == GL_TRUE)
	{
		_vertex_gen();
	}
}

void VertexArray::unbindVertexArray()
{
	GLuint uBound, uId = _object_id();
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	if (uBound == uId)
	{
		glBindVertexArray(0);
		YAGLPP_GLAD_ERROR;
	}
}

void VertexArray::unbindTarget()
{
	GLuint uBound;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&uBound);
	YAGLPP_GLAD_ERROR;
	if (uBound != 0)
	{
		glBindVertexArray(0);
		YAGLPP_GLAD_ERROR;
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
