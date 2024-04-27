## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // glpp class member
```
In addition glpp has an error checking procedure after every API call, which is not the case for Release build.

[&uarr; TOP](DETAILS.md#details)
