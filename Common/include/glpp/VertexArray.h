#pragma once
#include "gladpp.h"
#include "_Object.h"
#ifdef GL_VERSION_3_0
namespace gl {
/*(3.0) OpenGL vertex array object class (VAO) derived from <_Object>*/
class VertexArray : public _Object
{
protected:
	GLuint _array_id()
	{
		return _object_id(glGenVertexArrays);
	}

public:
	/*(3.0) (1) Constructs an empty vertex array object*/
	VertexArray() : _Object() {}

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

	/*(3.0) Binds a vertex array object. Vertex array object must call this method explicitly*/
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

	/*(3.0) Determines via API if vertex array object is currently active
	@return True if active vertex array object, false otherwise*/
	GLboolean isVertexArray()
	{
		return glIsVertexArray(_array_id());
	}

	/*(3.0) Determines via API if the vertex array object is currently bound to its target
	@return True if vertex array object currently bound to its target, or false otherwise*/
	GLboolean isVertexArrayBinding()
	{
		return _array_id() == _getInteger(GL_VERTEX_ARRAY_BINDING);
	}

	/*(3.0) Breaks the existing vertex array object binding*/
	static void unbindVertexArray();
}; // class VertexArray : public _Object

#ifndef _DEBUG
inline void VertexArray::bindVertexArray()
{
	glBindVertexArray(_array_id());
}

inline void VertexArray::unbindVertexArray()
{
	glBindVertexArray(0);
}
#endif // #ifndef _DEBUG
} // namespace gl
#endif // #ifdef GL_VERSION_3_0
