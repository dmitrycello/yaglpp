## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and most of its assets do the same as API assets:
```
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
```
With the location being a class member does the same:
```
void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value);
```

[&uarr; TOP](DETAILS.md#details)
