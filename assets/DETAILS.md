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
The **`multi-object`** creates and destroys many OpenGL objects at once. In addition to its usual pair of **`gen..`** and **`delete..`** methods, muti-object possesses as well **`insert..`** and **`remove..`** methods allowing more flexible array manipulation. To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a single object, use the **`isSingle()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created only from an already valid object.

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The framebuffer, query and vertex array objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either.

> [!TIP]
> The classes can be shared or assigned directly in a constructor. The last two lines of the above example may look like this:  **`gl::Renderbuffer rb1(rb);`** and **`gl::Renderbuffer rb2(rbs, 0);`**

### The class tree
```
_Object *-> _Buffer  - - -> ArrayBuffer, ElementArrayBuffer,
        |                   PixelPackBuffer, PixelUnpackBuffer,
        |                   TransformFeedbackBuffer, TextureBuffer, UniformBuffer
        *-> _Framebuffer -> DrawFramebuffer, Framebuffer, ReadFramebuffer
        *-> _Query - - - -> AnySamplesPassed, PrimitivesGenerated, SamplesPassed,
        |                   TimeElapsed, TransformFeedbackPrimitivesWritten
        *-> _Shader  - - -> VertexShader, FragmentShader, GeometryShader
        *-> _Texture - - -> Texture1D, Texture2D, Texture3D, TextureCubeMap,
        |                   Texture1DArray, Texture2DArray, BufferTexture, TextureRectangle,
        |                   Texture2DMultisample, Texture2DMultisampleArray
        *-> Program, Sampler, Renderbuffer, VertexArray

_Objects -> Queries, Textures, Buffers, Framebuffers, Samplers, Renderbuffers, VertexArrays
```

[&uarr; TOP](DETAILS.md#details)
