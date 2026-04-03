#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_VERTEX_ARRAY_H
#define YAGLPP_VERTEX_ARRAY_H

#ifdef YAGLPP_VERSION_3_0
namespace gl {
/*(3.0) OpenGL vertex array object class (VAO) derived from <Objects>*/
class VertexArray : public Objects
{
public:
	using Objects::Objects;
	/*(3.0) Allocates an array of vertex array objects of a given size, and generates their object names. Must be deallocated with <VertexArray::Dealloc> after use
	@param The number of the array elements
	@return The pointer to allocated array*/
	static VertexArray* Alloc(GLsizei n)
	{
		return (VertexArray*)object_alloc(glGenVertexArrays, n);
	}

	/*(3.0) Binds vertex array object to its target. Does nothing if specified object is bound*/
	void Bind()
	{
		object_bind(gl_bind_vertex_array, 0);
	}

	/*(3.0) Deletes previously allocated array of vertex array object names, and deallocates its memory block
	@param The pointer to allocated array*/
	static void Dealloc(VertexArray* vertexArrays)
	{
		object_dealloc(glDeleteVertexArrays, (GLuint*)vertexArrays);
	}

	/*(3.0) Deletes valid OpenGL vertex array object name and sets the vertex array class object in empty state*/
	void Delete()
	{
		object_delete(glDeleteVertexArrays);
	}

	/*(3.0) Deletes previously generated OpenGL vertex array object names in a static array or a user-defined structure of vertex arrays, namely vertex array map, and sets its class objects in empty state. Allows to unset multiple vertex arrays in one function call. The class objects previously set in empty state are silently ignored
	@param The size in bytes of vertex array map returned by sizeof operator
	@param [in-out] Pointer to vertex array map*/
	static void DeleteMap(GLsizei n, _Inout_updates_(n) void* vertexArrayMap)
	{
		object_delete_map(glDeleteVertexArrays, n, vertexArrayMap);
	}

	/*(3.0) Generates OpenGL vertex array object name in an empty vertex array class object*/
	void Gen()
	{
		object_gen(glGenVertexArrays);
	}

	/*(3.0) Generates OpenGL vertex array object name in an empty vertex array class object, and bind it to its target in one function call*/
	void GenBind()
	{
		object_gen_bind(glGenVertexArrays, gl_bind_vertex_array, 0);
	}

	/*(3.0) Generates OpenGL vertex array object names in a static array or a user-defined structure of vertex arrays, namely vertex array map. Allows to set multiple vertex arrays in one function call. All class objects are silently overwritten
	@param The size in bytes of vertex array map returned by sizeof operator
	@param [out] Pointer to vertex array map*/
	static void GenMap(GLsizei n, _Out_writes_(n) void* vertexArrayMap)
	{
		object_gen_map(glGenVertexArrays, n, vertexArrayMap);
	}

	/*(3.0) Returns VertexArray object currently bound to its target
	@return The VertexArray object bound to its target, or empty object*/
	static VertexArray GetBinding()
	{
		return VertexArray(yaglpp_glad_integer(GL_VERTEX_ARRAY_BINDING));
	}

	/*(3.0) Determines if the vertex array object is currently bound to its target. MSVC getter for <binding> property
	@return True if vertex array object currently bound to its target, or false otherwise*/
	GLboolean IsBinding() const
	{
		return object_binding(GL_VERTEX_ARRAY_BINDING, Get());
	}

	/*(3.0) Determines if a valid OpenGL vertex array object name corresponds to a vertex array object. MSVC getter for <vertexArray> property
	@return True if active renderbuffer object, false otherwise*/
	GLboolean IsVertexArray() const
	{
		return object_is(glIsVertexArray);
	}

	/*(3.0) Unbinds any vertex array object bound to its target. Does nothing if no such object is bound*/
	static void Unbind()
	{
		glBindVertexArray(0);
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*(3.0) Read-only property for vertex array binding flag*/
	__declspec(property(get = IsBinding)) GLboolean binding;

	/*(3.0) Read-only property to check if active vertex array object*/
	__declspec(property(get = IsVertexArray)) GLboolean vertexArray;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

protected:
	void auto_delete() { if (IsVertexArray()) Delete(); }
	static void APIENTRY gl_bind_vertex_array(GLenum unused, GLuint id);
}; // class VertexArray : public Object

#ifdef YAGLPP_IMPLEMENTATION
void APIENTRY VertexArray::gl_bind_vertex_array(GLenum unused, GLuint id)
{
	glBindVertexArray(id);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_0
#endif // #ifndef YAGLPP_VERTEX_ARRAY_H
