## DETAILS (under construction)
[&nwarr; README](../README.md)<br>
- [1]()
- [2]()

This section outlines specific traits of YAGL++ library, which as it was said is a C++ gear for the OpenGL API, and its almost every asset does the same as the original API asset. In the following example the YAGL++ class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value);             // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, YAGL++ library has an error checking procedure after every API call, which is not the case in the Release build. Of corse, there are many gems whose purpose is to save programmer's efforts.

GLSL shader:
```
uniform BlobSetting
{
    int value1;
    float value2;
    double value3;
};
```
Setup code:
```
struct
{
    GLint*    value1;
    GLfloat*  value2;
    GLdouble* value3;
} map;                                                 // Offset map

gl::UniformBlock block(program, "BlobSetting");        // Uniform block
block.uniformBlockBinding(0);                          // Binding point 0
DataStore data(block.getUniformBlockDataSize(), true); // Zeroed memory block
block.setUniformOffsetMap(&map, data);                 // Set the map

gl::UniformBuffer ubo;                                 // Uniform buffer object
ubo.bufferData(data, gl::BufferUsage::DynamicDraw);    // Associate with data
ubo.bindBufferBase(0);                                 // Binding point 0
```
Usage code:
```
*map.value1 = 1;         // Set integer
*map.value2 = 2.0f;      // Set float
*map.value3 = 3.0;       // Set double
ubo.bufferSubData(data); // Update uniform block
```

### Global functions

[&uarr; TOP](DETAILS.md#details)
