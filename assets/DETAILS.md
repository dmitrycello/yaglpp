## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // glpp class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case for the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### Objects
All classes of the library have the default constructor creating an empty class object. This allows to create class object before OpenGL initialization. Every class has minimum data members, such as an _id_ for all classes derived from **`gl::_Object`**. This allows to easily combine them in a stucture or another class. The lifetime of the glpp object is controlled by its destructor, which not always destroys OpenGL object. It depense on how this object was created.

[&uarr; TOP](DETAILS.md#details)
