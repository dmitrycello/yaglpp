![logo2.png](docs/logo2.png)
# Yet Another GL++ library
[INSTALLATION &rarr;](docs/INSTALLATION.md)<br>
[USAGE &rarr;](docs/USAGE.md)<br>
- [Naming concept](README.md#naming-concept)
- [IntelliSense](README.md#intellisense)
- [The main switches](README.md#the-main-switches)
- [GLAD objects](README.md#glad-objects)
- [Class tree](README.md#class-tree)
- [GLFW objects](README.md#glfw-objects)

YAGL++ is _"yet another"_ attempt to develop a C++ gear for the OpenGL API, merging its assets into the C++ objects. There are quite enough of similar projects on the GitHub. So, why another one? The present project was meant to fill the gap as a _thoughtful, transparent and complete_ library, meaning that there should be not a single API asset missing in its code. Primarily, YAGL++ was designed as a tool to help [learning OpenGL 3.3 API](https://learnopengl.com/), but after a while it turned out to be quite efficient. It takes care of the routine work, allowing to develop the OpenGL application in less complicated manner with minimal overhead. The library requires the C++ 11 compiler or later. It also impliments the [SAL](https://learn.microsoft.com/en-us/cpp/code-quality/using-sal-annotations-to-reduce-c-cpp-code-defects) concept (Microsoft Source Code Annotation Language) only in Debug build. At the moment, it is developped for Visual Studio under OS Windows. The code of the library can be viewed here, in the repository's [include](include) and [src](src) folders. To install and use the library, follow the instructions in the [INSTALLATION](docs/INSTALLATION.md) and [USAGE](docs/USAGE.md) documents.

The library works with GLAD version 2.0 to 3.3, and GLFW version 3.4+. The version of the GLAD header file affects the build, hiding the unsupported API assets. The C++ features make the OpenGL programming more compact, clear and stable, it allows the [function overloading](https://learn.microsoft.com/en-us/cpp/cpp/function-overloading), which is much easier than to recall the every exact API name, such as **`glUniform3fv`**. The library uses two ways of data input: the _files_ and the _binary resources_, which have to be of **`RCDATA`** type. Every call to the API function in the library is provided with the appropriate error checking, which has an effect only in Debug build. On the contrary, the Release build attempts to impliment the inline calls, depending on the compiler setting. Here is the average YAGL++ class member implementation:
```
void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value); // GLAD API call
	YAGLPP_GLAD_ERROR;                                 // Error checking macro
}
```
The most valuable library's feature is the **_"lasy" creation and binding concept_**. It means, the OpenGL object is automatically created and binded only when required. The creation of a class object does not mean the OpenGL object immediate creation or binding. This allows to use a YAGL++ object in situations where the immediate creation of OpenGL object would produce an error. The appropriate functions for creation and bindind are no longer needed, but still preserved to allow the programmer to create or bind the OpenGL object at anytime. The object status is saved in [thread local memory](https://learn.microsoft.com/en-us/cpp/c-language/thread-local-storage), which makes the library thread safe.

> [!NOTE]
> Not every YAGL++ object follows this rule: **`gl::VertexArray`** and **`gl::Sampler`** objects must be _binded_ explicitly, where as all multi-objects and **`glfw::`** objects have to be _created_ with specified parameters.

### Naming concept
The original API names are carefully preserved, except very rare cases (e.g. _BufferTexture_ is a texture, but _TextureBuffer_ is a buffer). As the API functions are grouped around the C++ classes, the API constants are grouped around the enum classes. The library assets are defined within **`gl::`** and **`glfw::`** namespaces for GLAD and GLFW APIs respectively. The few helper classes, such as **`StbImage`**, reside in the global namespace. You may bypass the **`gl::`** and **`glfw::`** prefixes with **`using namespace`** directives, but it is advised to keep them at least while learning the OpenGL API. The prefixes will also prevent name conflict while managing large projects. 

The names in YAGL++ library are obtained by stripping _gl_ and _glwf_ prefixes of the original API names, and by applying the camil-case rule for the rest. For the constant names, every underscore symbol is used as a word delimiter. Such an approach helps learning the original API symbols for potential switching to OpenGL C programming. Some of the API functions such as **`glDisable`**, **`glEnable`**, **`glGet`**, **`glIsEnabled`**, and **`glPixelStore`** are used with the names of their constant values. For example:
```
glDisable(GL_SAMPLE_COVERAGE)
glEnable(GL_SCISSOR_TEST)
glGetIntegerv(GL_COLOR_CLEAR_VALUE, color)
glIsEnabled(GL_POLYGON_SMOOTH)
glPixelStoref(GL_UNPACK_ROW_LENGTH, length)
glfwWindowHint(GLFW_VISIBLE, visible)
```
in YAGL++ library become:
```
gl::disableSampleCoverage()
gl::enableScissorTest()
gl::getColorClearValue(color)
gl::isPolygonSmooth()
gl::setUnpackRowLength(length)
glfw::setVisible(visible)
```
Some of the functions are duplicated as a static members of a class, it helps to find them on the context basis, e.g. the two following functions are the same:
```
GLfloat gl::getMaxTextureLodBias();            // Global function
GLfloat gl::Texture2D::getMaxTextureLodBias(); // Static member function
```

> [!CAUTION]
> The underscore at the beginning of a name means a private assignment, you should NOT be using these names. The global symbols starting with **`YAGLPP_`** are also preserved by the library.

### IntelliSense
Every methode or enum member in the library is provided with the comment shown in Visual Studio by the [IntelliSense](https://learn.microsoft.com/en-us/visualstudio/ide/using-intellisense) with the description, parameter list and return value. So it could be a nice way to briefly recap what the function does, instead of going online time after time. All information is taken from [Khronos website](https://registry.khronos.org/OpenGL-Refpages/gl4/).

If the description starts with the number in parentheses, it means either the supported OpenGL context version (as floating point number), or the number of overloaded function (as integer number). If the version number is missing, OpenGL 2.0 support is assumed. For example, the description of a function starting with **`(3.0) (18)`** means the support of OpenGL 3.0 and above, plus it specifies that this is the 18's overloaded function.

> [!IMPORTANT]
> If you don't know the function, you should visit Khronos website to read its whole dedicated info.

### The main switches
The symbols defined right after **`#pragma once`** directive in the [yaglpp.h](include/yaglpp.h) file are the library switches, they affect the build of the library. The first seven could be commented, the others may only be altered:
- Switches **`YAGLPP_COCOA_CHDIR_RESOURCES`**, **`YAGLPP_COCOA_MENUBAR`** and **`YAGLPP_JOYSTICK_HAT_BUTTONS`** are the GLFW hints set at the initialization, they are on by default;
- Commenting the **`YAGLPP_GLM_HEADERS`** switch will exclude GLM library headers, this allows to include only required GLM headers reducing the compile time;
- Commenting the **`YAGLPP_NO_AFX_LAYOUT`** switch will transform the YAGL++ into the AFX-alike environment, without the **`main`** function. Instead, the code must contain the global variable of a class derived from **`glfw::Thread`** or **`glfw::ThreadWnd`**. Otherwise, classical layout with the **`main`** function is preserved;
- Commenting the **`YAGLPP_NO_GLFW_LEGACY`** switch allows to build YAGL++ with GLFW v3.3.10, the latest version supporting Windows XP. In this case, the recent GLFW features become unavailable;
- When commenting the **`YAGLPP_FREEIMAGE_LIB`** switch, the **`FreeImage`** class will be excluded from the build. This library is no longer maintained, but can deal with more formats compared to included **`StbImage`**;
- The **`YAGLPP_CONTEXT_VERSION_MAJOR`** and **`YAGLPP_CONTEXT_VERSION_MINOR`** switches indicate the OpenGL context version supporeted by the library. Accepted combination of these values are: 2/0, 2/1, 3/0, 3/1, 3/2 and 3/3 to represent the versions 2.0 to 3.3 respectively. To change these switches, it is necessary to add other versions of the GLAD header file to **`glad`** folder, as described in last step of the [INSTALLATION](docs/INSTALLATION.md) section;
- The **`YAGLPP_GLFW_LIB`** switch selects the GLFW library file used in the build. It could be **`"glfw3dll.lib`"** (dll), **`"glfw3.lib`"** (static), or **`"glfw3_mt.lib`"** (static multi-threaded);
- The last 2 switches contain the library output paths.

>[!NOTE]
> The **`YAGLPP_GLFW_LIB`** switch also conains the library folder (e.g. _lib-vc2019/glfw3dll.lib_). It is important to change the year in folder name while using another IDE, to link the appropriate library. At the moment GLFW distributes precompiled binaries for Visual Studio 2013, 2015, 2017, 2019 and 2022.

> [!WARNING]
> Do not alter the last 2 switches, unless you really need to recalibrate the library path layout.

### GLAD objects
All classes in _::gl_ namespace are counterparts of GLAD API. They all have the default constructor creating an empty class object, this allows to create these objects even before OpenGL initialization. Every class has a single data member, such as a 4-byte _id_ integer. This allows to easily combine them into a stucture or another class. All derived classes have the same data size as their parent class. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The class created as a _single object_ does destroy the OpenGL object, where as _reference object_ doesn't. The _multi-object_ creates and destroys many OpenGL objects at once.

The **_single object_** is the one creating its own _single_ OpenGL object name as following:
```
gl::Renderbuffer rb;                                                 // Empty object
rb.renderbufferStorage(gl::ColorDepthStencilFormat::Rgb8, 800, 600); // Created single object
```
The **_reference object_** is another kind of a _single_ object. It has the same functionality as single object, but it simply copies the id from already created object. It does not take any mesures to handle the OpenGL object lifetime, leaving it to the source object. When it is deleted, it become an empty object without clearing an id. It is possible to have many objects at the time referencing the same id. The reference object could be used as temporary asset in a current or another OpenGL context. It could be obtained from a single or reference object with **`share..`**, or from a multi-object with **`assing..`** methods:
```
gl::Renderbuffers rbs;    // Empty multi-object
rbs.genRenderbuffers(10); // Generates 10 object names

gl::Renderbuffer rb1, rb2;      // Empty objects
rb1.shareRenderbuffer(rb);      // Reference of rb, will be destroyed by rb
rb2.assignRenderbuffer(rbs, 0); // Reference of rbs[0], will be destroyed by rbs
```

> [!TIP]
> The classes can be shared or assigned directly in a constructor, and the last three lines of the above example could be merged into one:  **`gl::Renderbuffer rb1(rb), rb2(rbs, 0);`**

The **_multi-object_** has the size of a pointer, creating the required array of object ids dynamically in the client memory. In Debug mode, it also checks the object type at every assignment, since the usage of the same id as different object type is not allowed by OpenGL (e.g. _ArrayBuffer_ sould not be later used as _ElementArrayBuffer_). The multi-object could not be used by itself, every object name (id) should be assigned to a reference object, and then used through that object. In addition to its original pair of **`gen..`** and **`delete..`** methods, creating and deleting the entire array, muti-object possesses as well **`insert..`** and **`remove..`** methods modifying its part from the given position, and thus allowing more flexible array manipulation:
```
gl::Renderbuffers rbs(10);     // ids: 1,2,3,4,5,6,7,8,9,10
rbs.insertRenderbuffers(3, 3); // ids: 1,2,3,11,12,13,4,5,6,7,8,9,10
rbs.removeRenderbuffers(3, 6); // ids: 1,2,3,11,12,13,7,8,9,10
```
To find out whether or not the class has the OpenGL object(s), use the **`isObject()`** method. The single object is automatically created as soon as it undergo an OpenGL operation, the reference object must be created from already created one. To find out whether or not the single object is a reference object, use the **`isReference()`** method. The classes derived from **`gl::_Object`**, are single objects, most of their methods automatically create and bind an OpenGL object when necessary, except the **`is..`** methods, they work exactly as their API counterparts:
```
GLboolean b1 = rb.isRenderbuffer();        // glIsRenderbuffer(id)
GLboolean b2 = rb.isRenderbufferBinding(); // glGetIntegerv(GL_RENDERBUFFER_BINDING..) == id
```

> [!NOTE]
> This behavior is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The [framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [query](https://www.khronos.org/opengl/wiki/Query_Object) and [vertex array](https://www.khronos.org/opengl/wiki/Vertex_Specification) objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either. Lastly, the vertex array and [sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) objects should be binded explicitly with their **`bind..`** methods, since vertex array should be binded at the specific point of a program, and sampler object binding takes a parameter.

### Class tree
The most of classes in **`::gl`** namespace are derived from **`gl::_Object`**, operating a single id. These classes control the OpenGL [Buffer](https://www.khronos.org/opengl/wiki/Buffer_Object), [Texture](https://www.khronos.org/opengl/wiki/Texture), [Framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [Renderbuffer](https://www.khronos.org/opengl/wiki/Renderbuffer_Object), [Query](https://www.khronos.org/opengl/wiki/Query_Object), [Sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) and [Vertex array](https://www.khronos.org/opengl/wiki/Vertex_Specification) objects. Their ids could be created (generated) once in big number via their _multi-object_ counterparts, the classes derived from **`gl::_Objects`**, carriyng an array of OpenGL object ids of varriyng length. Their class data member is single pointer, which is also the case for _Sync_ and _UniformBlock_ classes. Its **`NULL`** value means an empty object. The OpenGL [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) and [Shader](https://www.khronos.org/opengl/wiki/Shader) objects do not have their multi-object counterparts, but still could be referenced. The data member of _Uniform_ and _VertexAttrib_ classes is a single signed integer, operating a location value. It could be **`-1`**, meaning an invalid index, or an empty object. The following class tree exposes the classes's inheritance, as well as their data size in bytes:

> [!NOTE]
> Despite the OpenGL id is unsigned integer, the data member of **`gl::_Object`** class is signed integer. This allows to differentiate single and reference objects, being negative or positive value. Zero value means an empty object. The pointers in Win32 application are 4-byte long. So will be the size of the class object being a pointer.

![25.png](docs/25.png)

> [!CAUTION]
> The names starting with underscore character stand for the base abstract classes, they could NOT be used.

The ***Uniform*** and ***VertexAttrib*** classes have no destructors, they operate the location index value of a [uniform variable](https://www.khronos.org/opengl/wiki/Uniform_(GLSL)) and a [vertex attribute](https://www.khronos.org/opengl/wiki/Vertex_Specification) respectively, which remains valid as long as the [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) object remains linked. Since the location value must be set, they cannot be created automatically. The **`getUniformLocation`** and **`getAttribLocation`** methods aquire the location using a program object and the uniform or attribute name. If the location index is known, it could be set directly with **`setUniformLocation`** and **`setAttribLocation`** methods. The appropriate constructors exist as well. To find out if the location value was set successfully, use **`isUniform`** and **`isVertexAttrib`** methods.

The ***Sync*** class operates the OpenGL [synchronization object](https://www.khronos.org/opengl/wiki/Sync_Object), which is the pointer to an opaque API object. It must be created at the specific point of a program with **`fenceSync`** method. Its methods **`clientWaitSync`**, **`getSync`** and **`waitSync`** automatically create the synchronization object.

The ***UniformBlock*** class allows to operate many uniform variables at once, it works closely with [uniform buffer object](https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object). The class data has a uniform block index, which is aquired with **`getUniformBlockIndex`** or set with **`setUniformBlockIndex`** methods, or by the appropriate constructor. These methods save as well program id, number of uniforms, data block size and copy uniform block indices. This allows to use the saved data in next operations without the need to save it outside of a class. Since the number of indices is unknown, the whole class data is created dynamically, and the class object has the size of a pointer. The _offset map_ is a unique class feature allowing much easier uniform block data exchange. It is a user-defined stucture of pointers of the type specified in GLSL shader. The **`setUniformOffsetMap`** method calculates all uniform offsets in the specified memory block, and sets the absolute addresses to the stucture pointers, allowing to interchange uniform values directly through these pointers.

### GLFW objects
The classes in _::glfw_ namespace are counterparts of GLFW API. They all have the default constructor creating an empty class object, but unlike the GLAD objects, GLFW objects do not require binding, they always control their lifetime, and thus, they must be explicitly created or selected via their methods. Consisting of multiple data members, these cumbersome objects are less suitable to combine in a stucture or another class.

The **_Cursor_** class operates a GLFW [cursor object](https://www.glfw.org/docs/3.3/input_guide.html#cursor_object). It has only **`createStandardCursor`** method and five overloaded **`createCursor`** methods to explicitly create the GLFW cursor object from different sources. The appropriate constructors exist as well. The **`destroyCursor`** method is called from the class destructor, if the object was not cleared before.

The **_Joystick_** class controls a GLFW [joystick input](https://www.glfw.org/docs/3.3/input_guide.html#joystick) functionality, which exist from the GLFW initialization, and terefore its lifetime could not be controlled. The joystick device could be _selected_ via appropriate constructor, two overloaded **`selectJoystick`** or **`selectJoystickGUID`** methods, and _deselected_ via class destructor or **`deselectJoystick`** method. It is not possible to have multiple Joystick classes referencing the same joystick device, the class previously selecting that device will be automatically deselected when another class picks it up. The _gamepad_ methods work only for the devices supporting the [gamepad input](https://www.glfw.org/docs/3.3/input_guide.html#gamepad), to find out if this is the case, call **`joystickIsGamepad`** method. The Joystick class supports event handling, the single **`onDisconnect`** virtual function notifies the class object when associated physical device is disconnected, before that object is being voided. It is also possible to catch the joystick device connected event by setting **`JoystickConnectedCallback`** procedure via **`setJoystickConnectedCallback`** global function or static method.

> [!TIP]
> In order to use the joystick disconnected event handler, it is necessary to derive a class from **`glfw::Joystick`**, and overwrite its **`onDisconnect`** virtual function.

The **_Monitor_** class is somewhat similar to Joystick class, it controls GLFW [monitor object](https://www.glfw.org/docs/3.3/monitor_guide.html#monitor_object), which exist from the GLFW initialization. The monitor device could be _selected_ via appropriate constructor or three overloaded **`selectMonitor`** methods, and _deselected_ via class destructor or **`deselectMonitor`** method. As for Joystick class, it is not possible to have multiple Monitor classes referencing the same monitor device, so the same mechanism is applied here. As Joystick class, Monitor class has **`onDisconnect`** virtual function. To catch monitor connected event, set **`MonitorConnectedCallback`** procedure via **`setMonitorkConnectedCallback`** global function or static method. The monitor object is used to set the OpenGL application into fullscreen mode.

The **_Thread_** class is not a part of GLFW library, it is added to **`glfw::`** namespace exclusively to handle OS Windows [application threads](https://learn.microsoft.com/en-us/windows/win32/procthread/processes-and-threads). Its default constructor sets up an empty thread object, except that the main application thread object exist since the GLFW initialization, and can be retreived through **`getMainThread`** global function or static method. If the YAGL++ library is set into an AFX-alike mode, this function returns a pointer to a global application variable. Every other class object can start a new application thread. The Thread class allows to set up inter-thread communication and data synchronization, as well as to handle thread specific parameters, such as thread status, priority etc. Its virtual functions **`onInitThread`**, **`onRunThread`** and **`onExitThread`** notify the class object at every corresponding thread stage. The **_ThreadWnd_** class derived from **`glfw::Thread`**, is designed to work with GLFW window. It has pointer to Window class data member, and two more virtual functions: **`onPostMessage`**, the thread post message event handler, and **`onRenderWindow`**, the event handler triggered at every iteration of GLFW window rendering loop.

> [!TIP]
> While the YAGL++ library is not in AFX-alike mode, the **`getMainThread`** function returns the pointer to **`glfw::Thread`** base class. Despite its virtual functions could not be overwritten, there is still way to handle its post messages within the window rendering loop by calling **`dispatchMessage`** method.

The **_Window_** class operates a GLFW [window object](https://www.glfw.org/docs/3.3/window_guide.html#window_object). This is the largest library object, and the most of the GLFW API functions are merged around it. The window object is created via appropriate constructor or four overloaded **`createWindow`** methods, and deleted via class destructor or **`destroyWindow`** method. The **`createWindow`** method has an optional **`setting`** parameter, which is the pointer to **`ContextSetting`** structure, this allows to set all GLFW window hints at once. After creation it is important to call one of the two overloaded **`makeContextCurrent`** methods, to make the OpenGL context current on the calling thread. The second overloaded method takes the pointer to Thread object as parameter, which must be the calling thread. The associated thread object is saved in Window class data, and could be later retreived via **`getContextThread`** method. The very first call of **`makeContextCurrent`** method initialize the OpenGL, it is very important to made it on the main calling thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. The **`makeContextNonCurrent`** method dissociates the window from the calling thread. The Window object has 27 virtual functions to handle the GLFW window original events, such as **`onFramebuffer`**, and derivative events, such as **`onMouseDrag`**. The class saves the associated window data, such a cursor position, it is possible to retreive it via inline methods. These values could be updated on background at the appropriate event, or at direct API call:
```
double x = glWindow.getCursorPosX(); // Value since last cursor position event
glWindow.getCursorPos();             // Updates class X and Y values via API call
double y = glWindow.getCursorPosY(); // Value since the actual API call
```

### StbImage class

[&uarr; TOP](README.md#yet-another-gl-library)
