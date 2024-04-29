## DETAILS
[&nwarr; README](../README.md)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value); // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case for the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### Objects
All classes of the glpp library have the default constructor creating an empty class object. This allows to create class objects even before OpenGL initialization. Every class has minimum data members, such as an _id_. This allows to easily combine them into a stucture or another class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The glpp class created as a **`single object`** does destroy the OpenGL object, where as **`reference object`** doesn't. There are also **`multi-objects`**, they create and destroy many OpenGL objects at once. The _single object_ is just a usual one creating its own OpenGL object as following:
```
gl::Renderbuffer rbuff; // Single object before being created
rbuff.renderbufferStorage(gl::ColorDepthStencilFormat::Rgb8, 800, 600); // Created and binded
```
The _reference object_ could be created from another object with **`share..`**, or from a multi-object with **`assing..`** method:
```
gl::Renderbuffers rbuffs; // Multi-object before being created
arrays.genRenderbuffers(10);

gl::Renderbuffer rbuff1, rbuff2; // Reference objects before being created
rbuff1.shareRenderbuffer(rbuff); // Same id as rbuff, destroyed by rbuff
rbuff2.assignRenderbuffer(rbuffs, 0); // Destroyed by rbuffs
```
To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a single object, use the **`isSingle()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created from already valid object.

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are those derived from **`gl::_Objects`**, they cannot be referenced as a whole. The framebuffer, query and vertex array objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method.

```
_Object +-> _Buffer ------> ArrayBuffer, ElementArrayBuffer,
        |                   PixelPackBuffer, PixelUnpackBuffer,
        |                   TransformFeedbackBuffer, TextureBuffer, UniformBuffer
        +-> _Framebuffer -> DrawFramebuffer, Framebuffer, ReadFramebuffer
        +-> _Query -------> AnySamplesPassed, PrimitivesGenerated, SamplesPassed,
        |                   TimeElapsed, TransformFeedbackPrimitivesWritten
        +-> _Shader ------> VertexShader, FragmentShader, GeometryShader
        +-> _Texture -----> Texture1D, Texture2D, Texture3D, TextureCubeMap,
        |                   Texture1DArray, Texture2DArray, BufferTexture, TextureRectangle,
        |                   Texture2DMultisample, Texture2DMultisampleArray
        +-> Program
        +-> Sampler
        +-> Renderbuffer
        +-> VertexArray
_Objects -> Queries, Textures, Buffers, Framebuffers, Samplers, Renderbuffers, VertexArrays
```

[&uarr; TOP](DETAILS.md#details)
