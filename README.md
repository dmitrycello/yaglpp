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
- [Helper classes](README.md#helper-classes)

YAGL++ is _"yet another"_ attempt to develop a C++ gear for the OpenGL API, merging its assets into the C++ objects. There are plenty of similar projects on the GitHub. So, why another one? The present project was meant to fill the gap as a _thoughtful_, _transparent_ and _complete_ library, meaning that not a single API asset is missing in its code. Primarily, YAGL++ was designed as a tool to help [learning OpenGL 3.3 API](https://learnopengl.com/), but after a while it turned out to be quite efficient. It takes care of the routine work, allowing to develop the OpenGL application in less complicated manner without substantial overhead. The library requires the C++ 11 compiler or later. It also impliments the [SAL](https://learn.microsoft.com/en-us/cpp/code-quality/using-sal-annotations-to-reduce-c-cpp-code-defects) concept (Microsoft Source Code Annotation Language) in Debug build only. At the moment, it is developped for Visual Studio under OS Windows. The code of the library can be viewed in the repository's [include](include) and [src](src) directories. To install and use the library, follow the instructions in the [INSTALLATION](docs/INSTALLATION.md) and [USAGE](docs/USAGE.md) documents.

The library works with GLAD version 2.0 to 3.3, and GLFW version 3.4+. The version of the GLAD header file affects the build, hiding the unsupported API assets. The C++ features make the OpenGL programming more compact, clear and stable, it allows the [function overloading](https://learn.microsoft.com/en-us/cpp/cpp/function-overloading), which is much easier than to recall the every exact API name, such as **`glUniform3fv`**. The library uses two ways of data input: the _files_ and the _binary resources_, which have to be of **`RCDATA`** type. Every call to the API function in the library is provided with the appropriate error checking, which has an effect only in Debug build. On the contrary, the Release build attempts to impliment the inline calls, depending on the compiler setting. Here is the average YAGL++ class member implementation:
```
void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value); // GLAD API call
	YAGLPP_GLAD_ERROR;                                 // Error checking macro
}
```
The most valuable library's feature is the **_"lasy" creation and binding concept_**. It means, the OpenGL object is automatically created and binded only when required. The creation of a class object does not mean the OpenGL object immediate creation or binding. This allows to use a YAGL++ object in situations where the immediate creation of OpenGL object would produce an error. The appropriate functions for creation and bindind are no longer needed, but still preserved to allow the programmer to create or bind the OpenGL object at anytime. The object status is saved using [Thread Local Storage](https://learn.microsoft.com/en-us/cpp/c-language/thread-local-storage), which makes the library thread safe.

> [!NOTE]
> Not every YAGL++ object follows this rule. For example, **`gl::VertexArray`** and **`gl::Sampler`** objects must be _binded_ explicitly, where as multi-objects and **`glfw::`** objects have to be _created_ with specified parameters.

### Naming concept
For the sake of transparency, the original API names are carefully preserved, except very rare cases, e.g, _BufferTexture_ is a texture, but _TextureBuffer_ is a buffer. The most of the object names are based on the OpenGL _targets_, such as **`Texture2D`** class based on **`GL_TEXTURE_2D`** target. As the API functions are grouped around the classes, the API constants are grouped around the enum classes. This approach allows to clearly understand what the _object_ is, what the _function_ does, and what the _enum_ class member means. It also makes the library less error-prone, since the usage of a wrong object type or enumerator value simply won't compile.

The library assets are defined within **`gl::`** and **`glfw::`** namespaces for GLAD and GLFW APIs respectively. The few helper classes, such as **`StbImage`**, reside in the global namespace. You may bypass the **`gl::`** and **`glfw::`** prefixes with **`using namespace`** directives, but it is advised to keep them at least while learning the OpenGL API. The prefixes will also prevent name conflict while managing large projects. 

The names in YAGL++ library are obtained by stripping _gl_ and _glwf_ prefixes of the original API names, and by applying the camil-case rule for the rest. For the constant names, every underscore symbol is used as a word delimiter. Such an approach ensures the library's _transparency_, it helps learning the original API symbols for potential switching to OpenGL C programming. Some of the API functions such as **`glDisable`**, **`glEnable`**, **`glGet`**, **`glIsEnabled`**, and **`glPixelStore`** are used with the names of their constant values. For example:
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
Some classes are supplied with the [Class Properties](https://learn.microsoft.com/en-us/cpp/cpp/property-cpp?view=msvc-170), which is rather a syntactical "suger", but could also simplify the access to the object with a number of getters and setters. In case if this feature is not supported by the compiler, it is possible to comment the appropriate main switch in the [yaglpp.h](include/yaglpp.h) file, and then use only the respective functions. The property name is obtained by stripping the "set" or "get" prefix. For simplicity, the only read-write properties are provided. The two following lines are equivalent:
```
texture2D.setTextureMaxLod() = 1000.0f; // Usual way
texture2D.textureMaxLod = 1000.0f;      // Using class property
```

> [!CAUTION]
> The underscore at the beginning of a name means a private assignment, you should NOT be using these names. The global symbols starting with **`YAGLPP_`** are also preserved by the library.

### IntelliSense
Every methode or enum member in the library is provided with the comment shown in Visual Studio by the [IntelliSense](https://learn.microsoft.com/en-us/visualstudio/ide/using-intellisense) with the description, parameter list and return value. So it could be a nice way to briefly recap what the function does, instead of going online time after time. All information is taken from [Khronos website](https://registry.khronos.org/OpenGL-Refpages/gl4/).

If the description starts with the number in parentheses, it means either the supported OpenGL context version (as floating point number), or the number of overloaded function (as integer number). If the version number is missing, OpenGL 2.0 support is assumed. For example, the description of a function starting with **`(3.0) (18)`** means the support of OpenGL 3.0 and above, plus it specifies that this is the 18's overloaded function.

> [!IMPORTANT]
> If you don't know the function, you should visit Khronos website to read its whole dedicated info.

### The main switches
The symbols defined right after **`#pragma once`** directive in the [yaglpp.h](include/yaglpp.h) file are the library switches, they affect the build of the library. The first eight switches could be commented, the others could be only altered:
- Switches **`YAGLPP_COCOA_CHDIR_RESOURCES`**, **`YAGLPP_COCOA_MENUBAR`** and **`YAGLPP_JOYSTICK_HAT_BUTTONS`** are the GLFW hints set at the initialization, they are on by default;
- Commenting the **`YAGLPP_CLASS_PROPERTIES`** switch will exlude the class properties from the library;
- Commenting the **`YAGLPP_GLM_HEADERS`** switch will exclude GLM library headers, this allows to include only required GLM headers, while reducing the compile time;
- Commenting the **`YAGLPP_NO_AFX_LAYOUT`** switch will transform the YAGL++ into the AFX-alike environment, without the **`main`** function. Instead, the code must contain the global variable of a class derived from **`glfw::Thread`**. Otherwise, classical layout with the **`main`** function is preserved;
- Commenting the **`YAGLPP_NO_FREEIMAGE`** switch will add **`FreeImage`** class to the build. This library is no longer maintained, but can deal with more formats compared to included **`StbImage`**;
- Commenting the **`YAGLPP_NO_GLFW_LEGACY`** switch allows to build YAGL++ with GLFW v3.3.10, the latest version supporting Windows XP. In this case, the recent GLFW features become unavailable;
- The **`YAGLPP_CONTEXT_VERSION_MAJOR`** and **`YAGLPP_CONTEXT_VERSION_MINOR`** switches indicate the OpenGL context version supported by the library. Accepted combination of these values are: 2/0, 2/1, 3/0, 3/1, 3/2 and 3/3 to represent the versions 2.0 to 3.3 respectively. In order to change these switches, it is necessary to add other versions of the GLAD header file to **`glad`** folder, as described at the end of the [INSTALLATION](docs/INSTALLATION.md) section;
- The **`YAGLPP_GLFW_DEBUG`**, **`YAGLPP_GLFW_RELEASE`**, **`YAGLPP_LIB_DEBUG`** and **`YAGLPP_LIB_RELEASE`** switches contain the GLFW and YAGL++ library output paths.

> [!WARNING]
> Do not alter the last 4 switches, unless you really need to recalibrate the library path layout.

### GLAD objects
All classes in _::gl_ namespace are counterparts of GLAD API. They all have the default constructor creating an empty class object, this allows to create these objects even before OpenGL initialization. Every class has a single data member, such as a 4-byte _id_ integer. This allows to easily combine them into a stucture or another class. All derived classes have the same data size as their parent classes. The lifetime of the OpenGL object is controlled by the class destructor. It does not always destroy OpenGL object, depening on how this object was created. The class created as a _single object_ does destroy the OpenGL object, where as _reference object_ doesn't. The _multi-object_ creates and destroys many OpenGL objects at once.

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
> This concept is implemented in every class derived from **`gl::_Object`**. All multi-object classes are childs of **`gl::_Objects`**, they cannot be referenced as a whole, so they don't have their **`share..`** method. The [Framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [Query](https://www.khronos.org/opengl/wiki/Query_Object) and [Vertex Array](https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object) objects cannot be shared between OpenGL contexts, so they don't have their **`share..`** method either. Lastly, the Vertex Array and [Sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) objects should be binded explicitly with their **`bind..`** methods, since the Vertex Array should be binded at the specific point of a program, and the Sampler object binding takes a parameter.

### Class tree
The most of classes in **`::gl`** namespace are derived from **`gl::_Object`**, operating a single id. These classes control the OpenGL [Buffer](https://www.khronos.org/opengl/wiki/Buffer_Object), [Texture](https://www.khronos.org/opengl/wiki/Texture), [Framebuffer](https://www.khronos.org/opengl/wiki/Framebuffer_Object), [Renderbuffer](https://www.khronos.org/opengl/wiki/Renderbuffer_Object), [Query](https://www.khronos.org/opengl/wiki/Query_Object), [Sampler](https://www.khronos.org/opengl/wiki/Sampler_Object) and [Vertex Array](https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object) objects, they could be automatically _created_ and _binded_ when applicable, their ids could be generated once in big number via their _multi-object_ counterparts, which are the classes derived from **`gl::_Objects`**, carriyng an array of OpenGL object ids of varriyng length. The multi-object class data member is single pointer, this is also the case for _Sync_ and _UniformBlock_ classes. Its **`NULL`** value means an empty object. The OpenGL [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) and [Shader](https://www.khronos.org/opengl/wiki/Shader) objects could be automatically _created_, they do not have their multi-object counterparts, but still could be referenced. The Program object has to be explicitly _linked_, where as the Shader object must be explicitly _compiled_, the appropriate constructors exist as well. The data member of _Uniform_ and _VertexAttrib_ classes is a single signed integer, operating a location value. It could be **`-1`**, meaning an invalid index, or an empty object. The following class tree exposes the classes's inheritance, as well as their data size in bytes:

![25.png](docs/25.png)

> [!NOTE]
> Despite the OpenGL id is unsigned integer, the data member **`m_iId`** is signed integer. This allows to differentiate single and reference objects, being negative or positive value. Zero value means an empty object. The pointers in Win32 application are 4-byte long. So will be the size of the class object being a pointer.

> [!CAUTION]
> The names starting with underscore character stand for the base abstract classes, they could NOT be used.

The ***Uniform*** and ***VertexAttrib*** classes have no destructors, they operate the location index value of a [Uniform](https://www.khronos.org/opengl/wiki/Uniform_(GLSL)) and a [Vertex Attribute](https://www.khronos.org/opengl/wiki/Vertex_Specification) respectively, which remains valid as long as the [Program](https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects) object remains linked. Since the location value must be set, they cannot be created automatically. The **`getUniformLocation`** and **`getAttribLocation`** methods aquire the location using a program object and the uniform or attribute name. If the location index is known, it could be set directly with **`setUniformLocation`** and **`setAttribLocation`** methods. The appropriate constructors exist as well. To find out if the location value was set successfully, use **`isUniform`** and **`isVertexAttrib`** methods.

The ***Sync*** class operates the OpenGL [Synchronization](https://www.khronos.org/opengl/wiki/Sync_Object) object, which is the pointer to an opaque API object. It must be created at the specific point of a program with **`fenceSync`** method. Its methods **`clientWaitSync`**, **`getSync`** and **`waitSync`** automatically create the synchronization object.

The ***UniformBlock*** class allows to operate many uniform variables at once, it works closely with [Uniform Buffer Object](https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object). The class data has a uniform block index, which is aquired with **`getUniformBlockIndex`** or set with **`setUniformBlockIndex`** methods, or by the appropriate constructor. These methods save as well program id, number of uniforms, data block size and copy uniform block indices. This allows to use the saved data in next operations without the need to save it outside of a class. Since the number of indices is unknown, the whole class data is created dynamically, and the class object has the size of a pointer. The _offset map_ is a unique class feature allowing much easier uniform block data exchange. It is a user-defined stucture of pointers of the type specified in GLSL shader. The **`uniformBlockOffsetMap`** method calculates all uniform offsets in the specified memory block, and sets the absolute addresses to the stucture pointers, allowing to interchange uniform values directly through these pointers.

### GLFW objects
The classes in _::glfw_ namespace are counterparts of GLFW API. They all have the default constructor creating an empty class object, but unlike the GLAD objects, GLFW objects do not require binding, they always control their lifetime, and thus, they must be explicitly created or selected via their methods. Consisting of multiple data members, these cumbersome objects are less suitable to be combined into a stucture or another class. The most of the GLFW API functions are intended to be called only from the main thread. Despite that the GLFW library does not raise an error, the YAGL++ library will assert the proper calling of those functions in Debug mode only.

The **_Cursor_** class operates a GLFW [Cursor](https://www.glfw.org/docs/3.3/input_guide.html#cursor_object) object. It has only **`createStandardCursor`** method and five overloaded **`createCursor`** methods to explicitly create the GLFW cursor object from different sources. The appropriate constructors exist as well. The **`destroyCursor`** method is called from the class destructor, if the object was not cleared before.

The **_Joystick_** class controls a GLFW [Joystick](https://www.glfw.org/docs/3.3/input_guide.html#joystick) input functionality, which exist from the GLFW initialization, and terefore its lifetime could not be controlled. Instead, the joystick device could be _selected_ via appropriate constructor, two overloaded **`selectJoystick`** or **`selectJoystickGUID`** methods, and _deselected_ via class destructor or **`deselectJoystick`** method. It is not possible to have multiple Joystick classes referencing the same joystick device, the class previously selecting that device will be automatically deselected when another class picks it up. The _gamepad_ methods work only for the devices supporting the [Gamepad](https://www.glfw.org/docs/3.3/input_guide.html#gamepad) input, to find out if this is the case, call **`joystickIsGamepad`** method. The Joystick class supports event handling, the single **`onDisconnect`** virtual function notifies the class object when associated physical device is disconnected, before that object is being voided. It is also possible to catch the joystick device connected event by setting **`JoystickConnectedCallback`** procedure via **`setJoystickConnectedCallback`** global function or static method.

> [!TIP]
> In order to use the joystick disconnected event handler, it is necessary to derive a class from **`glfw::Joystick`**, and overwrite its **`onDisconnect`** virtual function.

The **_Monitor_** class is somewhat similar to Joystick class, it controls GLFW [Monitor](https://www.glfw.org/docs/3.3/monitor_guide.html#monitor_object) object used to set the OpenGL application into fullscreen mode, it exist from the GLFW initialization. The monitor device could be _selected_ via appropriate constructor or three overloaded **`selectMonitor`** methods, and _deselected_ via class destructor or **`deselectMonitor`** method. As for Joystick class, it is not possible to have multiple Monitor classes referencing the same monitor device, so the same mechanism is applied here. As Joystick class, Monitor class has **`onDisconnect`** virtual function. To catch monitor connected event, set **`MonitorConnectedCallback`** procedure via **`setMonitorkConnectedCallback`** global function or static method.

The **_Thread_** class is not a part of GLFW library, it is added to **`glfw::`** namespace exclusively to handle the OS Windows [Threads](https://learn.microsoft.com/en-us/windows/win32/procthread/processes-and-threads) and thread syncronization. Its default constructor sets up an empty object, except that the main application Thread object exists since the GLFW initialization, it can be retreived through **`getMainThread`** global function or a static method. If the YAGL++ library is set into an AFX-alike mode, this function returns a pointer to a global application variable. Every other class object can start a new application thread. The Thread class allows to set up inter-thread communication, as well as to handle thread specific parameters, such as thread status, priority etc. The main working loop can be overwritten by overloading the **`onRun`** virtual function. The other virtual functions **`onInit`**, **`onInput`**, **`onRender`**, **`onMessage`**, **`onIdle`**, and **`onExit`** are called from the main working loop, notifying the class object at every corresponding thread stage. It is recommended to call these function names in the overwritten **`onRun`** function. This will prevent the unnecessary growth of the class virtual table of the derived class.

> [!TIP]
> While the YAGL++ library is not in AFX-alike mode, the **`getMainThread`** function returns the pointer to **`glfw::Thread`** base class. Despite its virtual functions could not be overwritten, there is still way to handle its posted messages within the window rendering loop by calling **`dispatchMessage`** method.

The **_Window_** class operates a GLFW [Window](https://www.glfw.org/docs/3.3/window_guide.html#window_object) object. This is the largest library object, and the most of the GLFW API functions are merged around it. The window object is created via appropriate constructor or four overloaded **`createWindow`** methods, and deleted via class destructor or **`destroyWindow`** method. The **`createWindow`** method has an optional **`setting`** parameter, which is the pointer to **`ContextSetting`** structure, this allows to set all GLFW window hints at once. After creation, it is important to call one of the two overloaded **`makeContextCurrent`** methods, to make the OpenGL context current on the calling thread. The second overloaded method takes the pointer to Thread object as parameter, which must be the calling thread. The associated thread object is saved in Window class data, and could be later retreived via **`getContextThread`** method. The very first call of **`makeContextCurrent`** method initialize the OpenGL, it is very important to made it on the main calling thread. A context must only be made current on a single thread at a time and each thread can have only a single current context at a time. The **`makeContextNonCurrent`** method dissociates the window from the calling thread. The Window object has 17 virtual functions to handle the GLFW window original events. The library automatically transfers the event to the secondary thread, if the window operates outside of the main thread context. In this case the event handler is called twice: in main application thread, and then in the window host threads. The class saves the associated window data, such as the cursor position, it is possible to retreive this data via inline methods. These values are updated on background at the appropriate event, or at direct API call:
```
double x = glWindow.getCursorPosX(); // Value since last cursor position event
glWindow.getCursorPos();             // Updates class X and Y values via API call
double y = glWindow.getCursorPosY(); // Value since the actual API call
```
Some of the class members allows the _API transfer_ feature, which is the possibility to perform the API call the from secondary thread by sending the appropriate message to the main thread. This requires the use of **`dispatchMessage`** and **`translateMessage`** functions within the main rendering loop. After the API transfer is complete, the main thread is sending a **`onWindowTransfer`** notification back to the sender window:
```
glfw::Message msg;
while (dispatchMessage(&msg))
{
    if (!translateMessage(&msg))
    {
        // Custom thread messages
    }
}
```

### Helper classes
The YAGL++ library classes in global namespace are not a part of GLAD or GLFW API, they are included to simplify the I/O data handling. The _DataStore_ class is managing the client memory block, the _FreeImage_ and _StbImage_ are designed to manage the image data. All these helper classes have a default constructor building an empty object. There are two global helper functions: **`fileExists`** checks if the file with given path exists using _stat_ structure, and **`freeMemory`** deallocates the memory block previously allocated by the library.

The **_DataStore_** class controls the lifetime of allocated memory block. It could be used while working with the [Buffer](https://www.khronos.org/opengl/wiki/Buffer_Object) object classes, with _UniformBlock_ class, or in any custom implementation. The **`createDataStore`** and **`deleteDataStore`** methods create and destroy the memory block. The **`getData`** and **`getSubData`** methods are used to get the pointer to a whole or a part of memory block. The **`loadData`** overloaded member functions allocate the memory and load data from a binary resource of **`RCDATA`** type, from a file, or from another DataStore object. At the same time, **`loadSubData`** loads a part of a source DataStore object. The appropriate constructors exist as well. The **`writeData`** and  **`writeSubData`** methods can save the memory block or its part into a file. The **`copySubData`** method replaces a part of destination memory block with a part of source memory block.

The **_FreeImage_** class is a C++ interface of the [FreeImage](https://freeimage.sourceforge.io/) library, by default it is not included in the library's build. Its advantage is the ability to work with more image formats, and the multi-page support. At almost every class method there is an optional **`page`** parameter, selecting a page to work with. The **`getPageCount`** method returns the page number of loaded image, usually 1. The **`findLargestPage`** method loops through the pages and returns the index of the page with largest dimensions, in case when all image have same dimensions, it returns 0. The library allows an error callback function, so any error will be printed out in Debug build. The FreeImage library manages its memory internally, so in order to have writing access to pixel data, it should be copied into a buffer with **`allocateImage`**, **`allocateRegion`** or **`allocateSprite`** methods, allocating the memory and copying the pixel data in the reversed order of the _entire image_, of an _image region_, or of the _indexed image sprite_. The last method allows to calculate the region of the images with similar dimensions by the given index. The returned pointer should be cleaned up after use with a global **`freeMemory`** function. The **`getBits`**, **`getWidth`** and **`getHeight`** methods directly retreive the pixel data and dimensions of an image page. The FreeImage class can automatically determine image format, and load image media using **`loadImage`** method from a binary resource of **`RCDATA`** type, or from a file. It also has various **`load..`** methods for the specific formats, e.g. _loadCursor_, which originally isn't provided. The class object can be freed with **`unloadImage`** method, returning it into an empty state. At the moment, the FreeImage class is working only with the _RGBA32_ pixel format, does not have the ability to resize the image, and does not write into a file.

> [!NOTE]
> The FreeImage library does not have any updates since 2015, besides it has only DLL version, which requires the library DLL file destribution. Therefore, FreeImage is an optional YAGL++ image helper class, but it could be included to the build by commenting the **`YAGLPP_NO_FREEIMAGE`** switch.

The **_StbImage_** class is a C++ interface of [stb_image](https://github.com/nothings/stb/tree/master) library, the lightweight and the most popular among the OpenGL programmers. This is the main YAGL++ image helper class, uniting several library's components around the same object. StbImage class works closely with the [Cursor](https://www.glfw.org/docs/3.3/input_guide.html#cursor_object), [Texture](https://www.khronos.org/opengl/wiki/Texture) and [Window](https://www.glfw.org/docs/3.3/window_guide.html#window_object) object classes, it supports various internal pixel formats, it can resize the image, and it does write into a file. The stb_image library allows an error callback function, so any error will be printed out in Debug build. After personal communication with its creator, [Sean Barrett](https://github.com/nothings), the class has been rewritten to better fit the library's maintenance. It means, the next version of a library's files will most likely work with the current class. According to the stb_image developers, the gif multi-layered loader is now depricated, and should come out one day. Nevertheless, the StbImage class will try to maintain this functionality as long as possible. The class handles tree ways of data input: _binary resource_, _phisical file_ and _I/O callbacks_. The I/O callbacks data input uses the **`StbCallbacks`** stucture, it allows to read from arbitrary sources, like packaged files etc. The stb_image library has internal conversion functions allowing to load an image in many pixel formats. The number of channels can be from 1 to 4, and each channel can be _8-bit unsigned integer_, _16-bit unsigned integer_ or _32-bit float_. The **`StbFormat`** enum class selects the desired pixel format, allowing to load as well the original format without any conversion.

The image could be loaded with overloaded **`load`**, or **`loadGif`** methods for generic or multi-layered gif images. The image information could be retreived with overloaded **`info`** methods, setting the class data without loading an actual image. This image data could be retreived with inline **`getWidth`**, **`getHeight`**, **`getChannels`**, **`getDepth`**, and **`getFormat`** methods, where as the **`getFormat`** method returns both channels and depth as the StbFormat enum class value. The static overloaded **`is16bit`**, and **`isHdr`** methods allow to find out, if the image source has _16-bit unsigned integer_ or _32-bit float_ pixel format. There are also various static members, setting up the global class parameters, e.g. _setFlipVerticallyOnLoad_. The **`create`** method allocates memory for the required dimensions and pixel format, and the **`imageFree`** method unloads any previously loaded image, returning the class object into an empty state. The **`copy`**, **`copyRegion`**, and **`copySprite`** methods create memory block and copy from the source object an _entire image_, an _image region_, or the _indexed image sprite_. The image could be resized with **`resize`** and **`resizeRegion`** methods, and written into a file with **`writeBmp`**, **`writeHdr`**, **`writeJpg`**, **`writePng`**, and **`writeTga`** methods. The **`writeHdr`** requires the _32-bit float_ pixel data, otherwise it should be _8-bit unsigned_ integer.

> [!NOTE]
> The **`isImage`** method of the StbImage class only returns true, if the memory block for an image was allocated. This is the case for **`load`**, **`loadGif`**, and **`create`** methods. The **`info`** methods do not allocate a memory block, therefore the **`isImage`** returns false.

[&uarr; TOP](README.md#yet-another-gl-library)
