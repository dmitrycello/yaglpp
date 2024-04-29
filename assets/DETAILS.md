## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case for the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### Objects
All classes of the glpp library have the default constructor creating an empty class object. This allows to create class objects even before OpenGL initialization. Every class has minimum data members, such as an _id_. This allows to easily combine them into a stucture or another class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The glpp class created as a **`single object`** does destroy the OpenGL object, where as **`reference object`** doesn't. The _single object_ is just a usual one creating its own OpenGL object as following:
```
gl::Renderbuffer rb; // Empty object before being created
rb.renderbufferStorage(gl::ColorDepthStencilFormat::Rgb8, 800, 600); // Created single object
```
The _reference object_ could be created from another valid object with **`share..`**, or from a _multi-object_ with **`assing..`** method:
```
gl::Renderbuffers rbs; // Empty multi-object before being created
rbs.genRenderbuffers(10);

gl::Renderbuffer rb1, rb2; // Empty objects before copying reference
rb1.shareRenderbuffer(rb); // Same id as rb, will be destroyed by rb
rb2.assignRenderbuffer(rbs, 0); // Same id as rbs[0], will be destroyed by rbs
```

> [!TIP]
> The classes can be shared or assigned directly in a constructor, and the last three lines of the above example may be merged into one:  **`gl::Renderbuffer rb1(rb), rb2(rbs, 0);`**

The **`multi-object`** creates and destroys many OpenGL objects at once. It has the size of a pointer, creating the required array dynamically in the client memory. In addition to its original pair of **`gen..`** and **`delete..`** methods creating and deleting this array, muti-object possesses as well **`insert..`** and **`remove..`** methods modifying the array, allowing more flexible array manipulation. To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a single object, use the **`isSingle()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created only from already valid object. The **`is..`** methods of child classes do not automatically create an OpenGL object, they work exactly as their API counterpart:
```
GLboolean b1 = rb.isRenderbuffer(); // glIsRenderbuffer(id)
GLboolean b2 = rb.isRenderbufferBinding(); // glGetIntegerv(GL_RENDERBUFFER_BINDING..) == id
```

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The framebuffer, query and vertex array objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either.

### The class tree
```
_Object *-> _Buffer  - - -> ArrayBuffer, ElementArrayBuffer,
4 bytes |                   PixelPackBuffer, PixelUnpackBuffer,
(id)    |                   TransformFeedbackBuffer, TextureBuffer, UniformBuffer
        *-> _Framebuffer -> DrawFramebuffer, Framebuffer, ReadFramebuffer
        *-> _Query - - - -> AnySamplesPassed, PrimitivesGenerated, SamplesPassed,
        |                   TimeElapsed, TransformFeedbackPrimitivesWritten
        *-> _Shader  - - -> VertexShader, FragmentShader, GeometryShader
        *-> _Texture - - -> Texture1D, Texture2D, Texture3D, TextureCubeMap,
        |                   Texture1DArray, Texture2DArray, BufferTexture, TextureRectangle,
        |                   Texture2DMultisample, Texture2DMultisampleArray
        *-> Program, Sampler, Renderbuffer, VertexArray

_Objects -> Queries, Textures, Buffers, Framebuffers, Samplers, Renderbuffers, VertexArrays
            8 bytes (ptr)
Uniform, VertexAttrib
            4 bytes (location)
Sync, UniformBlock
            8 bytes (ptr)
```

[&uarr; TOP](DETAILS.md#details)
