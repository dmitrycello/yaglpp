## DETAILS
[&nwarr; README](../README.md)<br>
- [GLAD objects](DETAILS.md#glad-objects)
- [GLAD classes tree](DETAILS.md#glad-class-tree)

This section outlines specific traits of glpp library. As it was mentionned before, glpp is a C++ gear for the OpenGL API, and its most every asset does the same as the original API asset. In the following example the glpp class member uses location as a class data:
```
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value);             // Original API
void gl::Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value); // Class member
```
In addition, glpp library has an error checking procedure after every API call, which is not the case in the Release build. Of corse, there are many gems whose purpose is to save programmer's time. Let's begin with basic.

### GLAD objects
All classes in _::gl_ namespace of the glpp library are counterparts of GLAD API. They all have the default constructor creating an empty class object, this allows to create these objects even before OpenGL initialization. Every class has a single data member, such as a 4-byte _id_ integer. This allows to easily combine them into a stucture or another class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The class created as a **`single object`** does destroy the OpenGL object, where as **`reference object`** doesn't. The **`multi-object`** creates and destroys many OpenGL objects at once.

The _single object_ is the one creating its own _single_ OpenGL object as following:
```
gl::Renderbuffer rb;                                                 // Empty object
rb.renderbufferStorage(gl::ColorDepthStencilFormat::Rgb8, 800, 600); // Created single object
```
The _reference object_ is another kind of a single object, operating as well a single OpenGL object name, but it simply copies the id from already created object. It does not take any mesures to handle the OpenGL object lifetime, leaving it to the source object. When it is deleted, it become an empty object without clearing an id. The reference object could be used as temporary asset in a current or another OpenGL context. It could be obtained from a single or reference object with **`share..`**, or from a multi-object with **`assing..`** methods:
```
gl::Renderbuffers rbs;    // Empty multi-object
rbs.genRenderbuffers(10); // Generates 10 object names

gl::Renderbuffer rb1, rb2;      // Empty objects
rb1.shareRenderbuffer(rb);      // Reference of rb, will be destroyed by rb
rb2.assignRenderbuffer(rbs, 0); // Reference of rbs[0], will be destroyed by rbs
```

> [!TIP]
> The classes can be shared or assigned directly in a constructor, and the last three lines of the above example could be merged into one:  **`gl::Renderbuffer rb1(rb), rb2(rbs, 0);`**

The _multi-object_ has the size of a pointer, creating the required array of object ids dynamically in the client memory. In Debug mode, it also checks the object type at every assignment, since the usage of the same id as different object type is not allowed by OpenGL (e.g. _ArrayBuffer_ sould not be later used as _ElementArrayBuffer_). The multi-object could not be used by itself, every object name (id) should be assigned to a reference object, and then used through that object. In addition to its original pair of **`gen..`** and **`delete..`** methods creating and deleting the entire array, muti-object possesses as well **`insert..`** and **`remove..`** methods modifying only its part, and thus allowing more flexible array manipulation:
```
                               // rbs: 1,2,3,4,5,6,7,8,9,10
rbs.insertRenderbuffers(3, 3); // Generates 3 ids, insert from pos 3
                               // rbs: 1,2,3,11,12,13,4,5,6,7,8,9,10
rbs.removeRenderbuffers(3, 6); // Deletes 3 ids, remove from pos 6
                               // rbs: 1,2,3,11,12,13,7,8,9,10
```
To find out whether or not the class has an OpenGL object, use the **`isObject()`** method, and to find out whether or not the class is a reference object, use the **`isReference()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created from already created one. The classes derived from **`gl::_Object`**, are single objects, most of their methods automatically create and bind an OpenGL object if necessary, except the **`is..`** methods, they work exactly as their API counterparts:
```
GLboolean b1 = rb.isRenderbuffer();        // glIsRenderbuffer(id)
GLboolean b2 = rb.isRenderbufferBinding(); // glGetIntegerv(GL_RENDERBUFFER_BINDING..) == id
```

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The [framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [query](https://www.khronos.org/opengl/wiki/Query_Object) and [vertex array](https://www.khronos.org/opengl/wiki/Vertex_Specification) objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either. Lastly, the vertex array and [sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) objects should be binded explicitly with their **`bind..`** methods, since vertex array should be binded at the specific point of a program, and sampler object binding takes a parameter.

### GLAD class tree
The most of classes in **`::gl`** namespace are derived from **`gl::_Object`**, operating a single _id_. The data member of **`Uniform`** and **`VertexAttrib`** classes is a single signed integer, operating a location value. It could be **`-1`**, meaning an invalid index, or an empty object. The classes derived from **`gl::_Objects`** are multi-objects, carriyng an array of OpenGL object _ids_ of varriyng length. Their class data member is single pointer, which is also the case for **`Sync`** and **`UniformBlock`** classes. Its **`NULL`** value means an empty object. The following class tree exposes the classes's inheritance, as well as their data size in bytes:

> [!TIP]
> Despite the OpenGL _id_ is unsigned integer, the data member of **`gl::_Object`** class is signed integer. This allows to differentiate single and reference objects, being negative or positive value. Zero value means an empty object.

![25.png](25.png)

> [!CAUTION]
> The names starting with underscore character are standing for a base abstract classes, they could NOT be created.

The _Uniform_ and _VertexAttrib_ classes have no destructors, they operate the location index value of a [uniform variable](https://www.khronos.org/opengl/wiki/Uniform_(GLSL)) and a [vertex attribute](https://www.khronos.org/opengl/wiki/Vertex_Specification) respectively, which remains valid as long as the [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) object remains linked. Since the location value must be set, they cannot be created automatically. The **`getUniformLocation`** and **`getAttribLocation`** methods aquire the location using a program object and the uniform or attribute name. If the location index is known, it could be set directly with **`setUniformLocation`** and **`setAttribLocation`** methods. The appropriate constructors exist as well. To find out if the location value was set successfully, use **`isUniform`** and **`isVertexAttrib`** methods.

The _Sync_ class operates the OpenGL [synchronization object](https://www.khronos.org/opengl/wiki/Sync_Object), which is the pointer to an opaque API object. It must be created at the specific point of a program with **`fenceSync`** method. Its methods **`clientWaitSync`**, **`getSync`** and **`waitSync`** automatically create the synchronization object.

The _UniformBlock_ class allows to operate many uniform variables at once, it works closely with [uniform buffer object](https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object). The class data has a uniform block index, which is aquired with **`getUniformBlockIndex`** or set with **`setUniformBlockIndex`** methods, or by the appropriate constructor. These methods save as well program id, number of uniforms, data block size and copy uniform block indices. This allows to use the saved data in next operations without the need to save it outside of a class. Since the number of indices is unknown, the whole class data is created dynamically, and the class object has the size of a pointer. The _offset map_, a unique class feature allowing much easier uniform block data exchange, is a user-defined stucture of pointers of the type specified in GLSL shader. The **`setUniformOffsetMap`** method calculates all uniform offsets in the specified memory block, and sets the absolute addresses to the stucture pointers, allowing to interchange uniform values directly through these pointers.

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
