# yaglpp: Yet Another GLAD/GLFW C++ library v24.5.1
[INSTALLATION &rarr;](docs/INSTALLATION.md)<br>
[USAGE &rarr;](docs/USAGE.md)<br>
[DETAILS &rarr;](docs/DETAILS.md)<br>
- [Naming concept](README.md#naming-concept)
- [IntelliSense](README.md#intellisense)
- [The main switches](README.md#the-main-switches)

This project is _"yet another"_ attempt to develop a C++ gear for the OpenGL API, merging its assets into the C++ objects. Its initial goal was to help learning [GLAD/GLFW API 3.3](https://learnopengl.com/), but it definatelly became an efficient tool, taking care of the routine work, allowing to develop the OpenGL application in less complicated manner with minimal overhead. It requires the C++ 11 compiler or later. The library also impliments the [SAL](https://learn.microsoft.com/en-us/cpp/code-quality/using-sal-annotations-to-reduce-c-cpp-code-defects) concept (Microsoft Source Code Annotation Language) only in Debug mode, any warnings in the Release mode should be ignored. At the moment, it is developped for Windows OS using Visual Studio.

The library works with GLAD version 2.0 to 3.3, and GLFW version 3.4+. The version of the GLAD header file affects the build, hiding the unsupported API assets. The C++ features make the OpenGL programming more compact, clear and stable, it allows the [function overloading](https://learn.microsoft.com/en-us/cpp/cpp/function-overloading), which is much easier than to recall the every exact API name, such as **`glUniform3fv`**. Every call to the API function in the library is provided with the appropriate error checking, which has an effect only in Debug build. The Release build attempts to impliment the inline calls, depending on the compiler setting. Here is the average glpp class member implementation:
```
void Uniform::uniform(GLsizei count, _In_reads_(count) const glm::vec3* value)
{
	glUniform3fv(_location(), count, (GLfloat*)value); // GLAD API call
	GLPP_GLAD_ERROR; // Error checking macro
}
```
The most valuable library's feature is the **`"lasy" creation and binding concept`**. It means, the OpenGL object is automatically created and binded only when required. The creation of a class object does not mean the OpenGL object immediate creation or binding. This allows to use a glpp object as class member in situations where the immediate creation of OpenGL object would produce an error. The appropriate functions for creation and bindind are no longer needed, but still preserved to allow the programmer to create or bind the OpenGL object at anytime. The object status is saved in [thread local memory](https://learn.microsoft.com/en-us/cpp/c-language/thread-local-storage), which makes the library thread safe.

> [!NOTE]
> Not every glpp object follows this rule: **`gl::VertexArray`** and **`gl::Sampler`** objects must be _binded_ explicitly, where as all multi-objects and **`glfw::`** objects have to be _created_ with specified parameters.

### Naming concept
The original API names are carefully preserved, except very rare cases (e.g. _BufferTexture_ is a texture, but _TextureBuffer_ is a buffer). As the API functions are grouped around the C++ classes, the API constants are grouped around the enum classes. The library assets are defined within **`gl::`** and **`glfw::`** namespaces for GLAD and GLFW APIs respectively. The few helper classes, such as **`StbImage`**, reside in the global namespace. You may bypass the **`gl::`** and **`glfw::`** prefixes with **`using namespace`** directives, but it is advised to keep them at least while learning the API. The prefixes will also prevent name conflict while managing large projects. 

The names in glpp library are obtained by stripping gl and glwf prefixes of the original API names, and by applying the camil-case roule for the rest. For the constant names, every underscore symbol is used as a word delimiter. Such an approach helps learning the original API symbols for potential switching to OpenGL C programming. Some of the API functions such as **`glDisable`**, **`glEnable`**, **`glGet`**, **`glIsEnabled`**, and **`glPixelStore`** are used with the names of their constant values. For example:
```
glDisable(GL_SAMPLE_COVERAGE)
glEnable(GL_SCISSOR_TEST)
glGetIntegerv(GL_COLOR_CLEAR_VALUE, color)
glIsEnabled(GL_POLYGON_SMOOTH)
glPixelStoref(GL_UNPACK_ROW_LENGTH, length)
glfwWindowHint(GLFW_VISIBLE, visible)
```
in glpp library become:
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
> The underscore at the beginning of a name means a private assignment, you should NOT be using these names. The global symbols starting with **`GLPP_`** are also preserved by the library.

### IntelliSense
Every methode or enum member in the library is provided with the comment shown in Visual Studio by the [IntelliSense](https://learn.microsoft.com/en-us/visualstudio/ide/using-intellisense) with the description, parameter list and return value. So it could be a nice way to briefly recap what the function does, instead of going online time after time. All information is taken from [Khronos website](https://registry.khronos.org/OpenGL-Refpages/gl4/).

If the description starts with the number in parentheses, it means either the minimum required OpenGL version (as floating point number), or the number of overloaded function (as integer number). If the version number is missing, OpenGL 2.0 support is assumed. For example, the description of a function starting with **`(3.0) (18)`** means the support of OpenGL 3.0 and above, plus it specifies that this is the 18's overloaded function.

> [!IMPORTANT]
> If you don't know the function, you should visit Khronos website to read its whole dedicated info.

### The main switches
The symbols defined right after **`#pragma once`** directive in the [glpp.h](include/glpp.h) file are the library switches, they affect the build of the library. The first six could be commented, the others may only be altered:
- Switches **`GLPP_COCOA_CHDIR_RESOURCES`**, **`GLPP_COCOA_MENUBAR`** and **`GLPP_JOYSTICK_HAT_BUTTONS`** are the GLFW flags set at the initialization, they are on by default;
- Commenting the **`GLPP_NO_AFX_LAYOUT`** switch will transform the glpp into the AFX-alike environment, without the **`main`** function. Instead, you have to inherit a class from **`glfw::Thread`** or **`glfw::ThreadWnd`**, and overwrite its virtual functions. Otherwise, classical layout with the **`main`** function is preserved;
- Commenting the **`GLPP_NO_GLFW_LEGACY`** switch allows to build glpp with GLFW v3.3.10, the latest version supporting Windows XP. In this case, some functions and constants of the recent GLFW libraries become unavailable;
- When commenting the **`GLPP_FREEIMAGE_LIB`** switch, the **`FreeImage`** class won't be included in the build. This library is no longer maintained, but can deal with more formats compared to included **`StbImage`**;
- The **`GLPP_CONTEXT_VERSION_MAJOR`** and **`GLPP_CONTEXT_VERSION_MINOR`** switches indicate the minimum supporeted OpenGL context verion of the library. Accepted combination of these values are: 2/0, 2/1, 3/0, 3/1, 3/2 and 3/3 to represent the OpenGL versions 2.0 to 3.3 respectively. To change these switches, it is necessary to add other versions of the GLAD header file to **`glad`** folder, as described in last step of the [INSTALLATION](assets/INSTALLATION.md) section;
- The **`GLPP_GLFW_LIB`** switch selects the GLFW library file used in the build. It could be **`"glfw3dll.lib`"** (dll), **`"glfw3.lib`"** (static), or **`"glfw3_mt.lib`"** (static multi-threaded);
- The last 2 switches contain the library output paths.

>[!NOTE]
> The **`GLPP_GLFW_LIB`** switch also conains the library folder (e.g. _lib-vc2019/glfw3dll.lib_). It is important to change the year in folder name while using another IDE, to link the appropriate library. At the moment GLFW supports Visual Studio 2013, 2015, 2017, 2019 and 2022.

> [!WARNING]
> Do not alter the last 2 switches, unless you really need to recalibrate the library path layout.

[&uarr; TOP](README.md#glpp-opengl-c-library-v2441)
