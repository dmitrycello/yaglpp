## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case for the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### Objects
All classes of the glpp library have the default constructor creating an empty class object. This allows to create class object even before OpenGL initialization. Every class has minimum data members, such as an _id_. This allows to easily combine them in a stucture or another class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The glpp class created as a **`single object`** does destroy the OpenGL object, where as **`reference object`** doesn't. There are also **`multi-objects`**, they create and destroy many OpenGL objects at once. The _single object_ is just a usual one creating its own OpenGL object as following:
```
gl::VertexArray varr;
varr.bindVertexArray();
```
The _reference object_ could be created from another object with **`share..`**, or from a multi-object with **`assing..`** method:
```
gl::VertexArrays arrays; // Multi-object
arrays.genVertexArrays(10);

gl::VertexArray varr2, varr3;
varr2.shareVertexArray(varr); // Destroyed by varr
varr3.assignVertexArray(arrays, 0); // Destroyed by arrays
```
To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a single object, use the **`isSingle()`** method.

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**, all multi-object classes derived from **`gl::_Objects`**.

[&uarr; TOP](DETAILS.md#details)
