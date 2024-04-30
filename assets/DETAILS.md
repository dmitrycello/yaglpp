## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case in the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### GLAD objects
All classes in _::gl_ namespace of the glpp library are counterpart of GLAD API. They all have the default constructor creating an empty class object. This allows to create class objects even before OpenGL initialization. Every class has minimum data members, such as an _id_, the 4-byte unsigned integer. This allows to easily combine them into a stucture or another class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The class created as a **`single object`** does destroy the OpenGL object, where as **`reference object`** doesn't. The **`multi-object`** creates and destroys many OpenGL objects at once. The _single object_ is the one creating its own OpenGL object as following:
```
gl::Renderbuffer rb; // Empty object before creation
rb.renderbufferStorage(gl::ColorDepthStencilFormat::Rgb8, 800, 600); // Created single object
```
The _reference object_ simply copies the id from already created object. It does not take any mesures to handle the OpenGL object lifetime, leaving it to the source object. When it is deleted, it become an empty object without clearing an id. The reference object could be used as temporary asset in a current or another OpenGL context. It could be obtained from a single or reference object with **`share..`**, or from a multi-object with **`assing..`** methods:
```
gl::Renderbuffers rbs;    // Empty multi-object before creation
rbs.genRenderbuffers(10);

gl::Renderbuffer rb1, rb2;      // Empty objects before copying
rb1.shareRenderbuffer(rb);      // Same id as rb, will be destroyed by rb
rb2.assignRenderbuffer(rbs, 0); // Same id as rbs[0], will be destroyed by rbs
```

> [!TIP]
> The classes can be shared or assigned directly in a constructor, and the last three lines of the above example could be merged into one:  **`gl::Renderbuffer rb1(rb), rb2(rbs, 0);`**

The _multi-object_ has the size of a pointer, creating the required array of object ids dynamically in the client memory. In Debug mode, it also checks the object type at every assignment, since the usage of the same id as different object type is not allowed (e.g. _ArrayBuffer_ sould not be later used as _ElementArrayBuffer_). The multi-object could not be used by itself, every object name (id) sould be assigned to a reference object, and then used through that object. In addition to its original pair of **`gen..`** and **`delete..`** methods creating and deleting the entire array, muti-object possesses as well **`insert..`** and **`remove..`** methods modifying only its part, and thus allowing more flexible array manipulation.

To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a single object, use the **`isSingle()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created only from already created object. The **`is..`** methods of child classes do not automatically create or bind an OpenGL object, they work exactly as their API counterpart:
```
GLboolean b1 = rb.isRenderbuffer();        // glIsRenderbuffer(id)
GLboolean b2 = rb.isRenderbufferBinding(); // glGetIntegerv(GL_RENDERBUFFER_BINDING..) == id
```

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The [framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [query](https://www.khronos.org/opengl/wiki/Query_Object) and [vertex array](https://www.khronos.org/opengl/wiki/Vertex_Specification) objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either. Lastly, the vertex array and [sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) objects should be binded explicitly with their **`bind..`** methods, since vertex array should be binded at the specific point of a program, and sampler object binding takes a parameter.

### GLAD classes tree
The following classes tree exposes the classes inheritance, as well as their data size in bytes.
```
_Object -> _Buffer  - - -> ArrayBuffer, ElementArrayBuffer,
 4 (id) |                  PixelPackBuffer, PixelUnpackBuffer,
        |                  TransformFeedbackBuffer, TextureBuffer, UniformBuffer
        -> _Framebuffer -> DrawFramebuffer, Framebuffer, ReadFramebuffer
        -> _Query - - - -> AnySamplesPassed, PrimitivesGenerated, SamplesPassed,
        |                  TimeElapsed, TransformFeedbackPrimitivesWritten
        -> _Shader  - - -> VertexShader, FragmentShader, GeometryShader
        -> _Texture - - -> Texture1D, Texture2D, Texture3D, TextureCubeMap,
        |                  Texture1DArray, Texture2DArray, BufferTexture, TextureRectangle,
        |                  Texture2DMultisample, Texture2DMultisampleArray
        -> Program, Sampler, Renderbuffer, VertexArray

_Objects -> Queries, Textures, Buffers, Framebuffers, Samplers, Renderbuffers, VertexArrays
            8 (ptr64)
Uniform, VertexAttrib
            4 (location)
Sync, UniformBlock
            8 (ptr64)
```

> [!CAUTION]
> The names starting with underscore character are standing for a base abstract classes, they could NOT be created.

The _Uniform_ and _VertexAttrib_ classes have no destructors, they operate the location index value of a [uniform variable](https://www.khronos.org/opengl/wiki/Uniform_(GLSL)) and a [vertex attribute](https://www.khronos.org/opengl/wiki/Vertex_Specification) respectively. The location is a 4-byte signed integer, which remains valid as long as the [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) object remains linked. Since the location value must be set, they cannot be created automatically. The **`getUniformLocation`** and **`getAttribLocation`** methods aquire the location using a program object and the uniform or attribute name. If the location index is known, it could be set directly with **`setUniformLocation`** and **`setAttribLocation`** methods. The appropriate constructors exist as well. To find out if the location value was set successfully, use **`isUniform`** and **`isVertexAttrib`** methods.

The _Sync_ class operates the OpenGL [synchronization object](https://www.khronos.org/opengl/wiki/Sync_Object), which is the 8-byte pointer to an opaque API object. It must be created at the specific point of a program with **`fenceSync`** method. Its methods **`clientWaitSync`**, **`getSync`** and **`waitSync`** automatically create the synchronization object.

The _UniformBlock_ class allows to operate many uniform variables at once, it works closely with [uniform buffer object](https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object). The class operates with uniform block index, which is aquired with **`getUniformBlockIndex`** or set with **`setUniformBlockIndex`** methods, or by the appropriate constructor. The methods save as well program id, number of uniforms, data block size and copies uniform block indices. This allows to use the saved data in next operations without the need to save it outside of a class. Since the number of indices is unknown, the whole class data is created dynamically, and the class object size is the 8-byte pointer. The _offset map_, a unique class feature allowing much easier uniform block data exchange, is a user-defined stucture of pointers of the type specified in GLSL shader. The **`setUniformOffsetMap`** method calculates all uniform offsets in the specified memory block, and sets the absolute addresses to the stucture pointers, allowing to interchange uniform values directly through these pointers.

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
} map;                                          // Offset map

gl::UniformBlock block(program, "BlobSetting"); // Uniform block
block.uniformBlockBinding(0);                   // Binding point 0

DataStore data(block.getUniformBlockDataSize(), true); // Zeroed memory block
block.setUniformOffsetMap(&map, data);                 // Set the map

gl::UniformBuffer ubo;                              // Uniform buffer object
ubo.bufferData(data, gl::BufferUsage::DynamicDraw); // Associate with data
ubo.bindBufferBase(0);                              // Binding point 0
```
Usage code:
```
*map.value1 = 1;    // Set integer
*map.value2 = 2.0f; // Set float
*map.value3 = 3.0;  // Set double
ubo.bufferSubData(data, 0, data.getSize()); // Update uniform block
```
> [!NOTE]
> The pointers in Win32 application are 4-byte long. So will be the size of the class object being a pointer.

### Global functions

[&uarr; TOP](DETAILS.md#details)
