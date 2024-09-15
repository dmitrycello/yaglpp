#pragma once
#include <yaglpp/glad/_object.h>
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL vertex array object class (VAO) derived from <_Object>*/
class VertexArray : public _Object
{
public:
	/*(3.0) (1) Constructs an empty vertex array object*/
	VertexArray() {}

	/*(3.0) (2) Constucts a vertex array object with <assignVertexArray>*/
	VertexArray(VertexArrays& arrays, GLuint index)
	{
		assignVertexArray(arrays, index);
	}

	/*(3.0) Cleans up the valid vertex array object*/
	~VertexArray()
	{
		if (isObject())
		{
			deleteVertexArray();
		}
	}

	/*(3.0) Assigns an empty vertex array object with the object name from the vertex array multi-object
	@param The vertex array multi-object
	@param The index of the object name*/
	void assignVertexArray(VertexArrays& arrays, GLuint index)
	{
#ifdef _DEBUG
		_object_assign((_Objects&)arrays, index, GL_TRUE); // Single target
#else // #ifdef _DEBUG
		_object_assign((_Objects&)arrays, index);
#endif // #ifdef _DEBUG
	}

	/*(3.0) Explicitly binds vertex array object to its target. Does nothing if specified vertex array is bound*/
	void bindVertexArray();

	/*(3.0) Explicitly deletes previously generated single vertex array object*/
	void deleteVertexArray()
	{
		_object_delete(glDeleteVertexArrays);
	}

	/*(3.0) Explicitly generates single vertex array object*/
	void genVertexArray()
	{
		_object_gen(glGenVertexArrays);
	}

	/*(3.0) Determines if a name corresponds to a vertex array object. Used as a getter of <vertexArray> property
	@return True if active vertex array object, false otherwise*/
	GLboolean isVertexArray()
	{
		return glIsVertexArray(_object_id());
	}

	/*(3.0) Determines if the vertex array object is currently bound to its target. Used as a getter of <vertexArrayBinding> property
	@return True if vertex array object currently bound to its target, or false otherwise*/
	GLboolean isVertexArrayBinding()
	{
		return _object_id() == _getInteger(GL_VERTEX_ARRAY_BINDING);
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

/*(3.0) Explicitly unbinds any vertex array object bound to its target. Does nothing if no vertex array is bound*/
inline void unbindVertexArray()
{
	VertexArray::unbindTarget();
}

#ifdef YAGLPP_IMPLEMENTATION
void VertexArray::bindVertexArray()
{
	GLuint uBound, uId = _object_id(glGenVertexArrays);
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
			genVertexArray();
		}
	}
	else if (gen == GL_TRUE)
	{
		deleteVertexArray();
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
#endif // #ifdef GL_VERSION_3_0
