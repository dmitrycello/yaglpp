# glpp: OpenGL C++ extension library 24.4.1

This project is an attempt to develop a C++ OpenGL library, combining the API calls around the C++ objects. Initially, its main goal was to help learning GLAD/GLFW API, but it definatelly could to be used as an efficient tool, allowing to develop the OpenGL applications in less complicated manner with minimal overhead.

It requires the C++ 11 compiler or later, it also impliments the concept of SAL (Microsoft Source Code Annotation Language) in Debug build only, any warnings in the Release mode should be ignored. At the moment, it is developped for Windows OS only using Visual Studio 2019+.

The library works with GLAD version from 2.0 to 3.3, and GLFW version 3.4+. The used GLAD version affects the build, hiding the unsupported API functions. C++ allows to use the overloaded functions, which is much easier than to find the every exact API function, such as **`glUniform3fv`**. Usage of C++ classes makes the OpenGL programming more compact, clear and stable. Every call to the API function in the library is provided with the appropriate error checking, which has an effect only in Debug build. The Release build attempts to impliment the inline calls, depending on the compiler setting.

The library functions are defined within ***gl::*** and ***glfw::*** namespaces for GLAD and GLFW API functions respectively. The few helper classes, such as ***StbImage***, reside in the global namespace. The API functions are grouped around the objects, and the API constants are grouped around the enum classes. The original API names are carefully preserved, except very rare cases (e.g. ***BufferTexture*** is a texture, but ***TextureBuffer*** is a buffer).

The API name prefixes gl and glwf are stripped, and the camil-case roule is applied. For the constant names, every underscore symbol is used as a word delimiter. Such an approach helps learning the original API symbols for potential switching to OpenGL C programming. The underscore at the beginning of the name means a private assignment, you should NOT be using these names. Some of the API functions such as ***glDisable***, ***glEnable***, ***glGet***, ***glIsEnabled***, and ***glPixelStore*** are used with the names of their constant values. For example:

```
glDepthFunc(func)
glDisable(GL_SAMPLE_COVERAGE)
glEnable(GL_SCISSOR_TEST)
glGetIntegerv(GL_COLOR_CLEAR_VALUE, color)
glIsEnabled(GL_POLYGON_SMOOTH)
glPixelStoref(GL_UNPACK_ROW_LENGTH, length)
glfwWindowHint(GLFW_VISIBLE, visible)
```

in glpp library become:
```
gl::depthFunc(func)
gl::disableSampleCoverage()
gl::enableScissorTest()
gl::getColorClearValue(color)
gl::isPolygonSmooth()
gl::setUnpackRowLength(length)
glfw::setVisible(visible)
```

You can bypass the **gl::** and **glfw::** prefixes with **using namespace** directives, but it is advised to keep them at least while learning the API. The prefixes will also prevent name conflict while managing large projects. Some of the functions are duplicated as a static members of a class, it helps to find them on the context basis. The global symbols starting with **GLPP_** are preserved by the library.

The most valuable library's feature is the ***"lasy" creation and binding concept***. It means, the OpenGL object is created and binded only when it is required. The creation of glpp class object does not mean the OpenGL object immediate creation or binding. The appropriate functions for creation and bindind are no longer needed, but still preserved to allow the programmer to create or bind the OpenGL object at anytime. The object status is saved in thread local memory, which makes the library thread safe.

Every methode or enum member in the library is provided with the comment
shown by the IntelliSense with the description, parameter list and return
value. So it could be a nice way to briefly recap what the function does,
instead of going online time after time. All information is taken from
Khronos website: https://registry.khronos.org/OpenGL-Refpages/gl4/
If you don't know the function, you should visit this website to read the
whole dedicated info. If the comment starts with the number in parentheses,
it means either the minimum supported OpenGL version (2.1-3.3), or the
number of overloaded method (1-x). If the version is missing, OpenGL 2.0
support is assumed. For example, (3.0) (18) means OpenGL 3.0 is required,
and this is the 18's overloaded member.

The swithes following #pragma once directive affect the build of the
library. The first six could be commented, the others may only be altered:
	- Switches **GLPP_COCOA_CHDIR_RESOURCES**, **GLPP_COCOA_MENUBAR** and
**GLPP_JOYSTICK_HAT_BUTTONS** are the GLFW flags set at the initialization,
they are on by default;
	- Commenting the **GLPP_NO_AFX_LAYOUT** switch will transform the glpp
into the AFX-like environment, without the main function. Instead, you have
to inherit a class from ThreadWnd, and overwrite its virtual functions.
Otherwise, classical layout with the main function is preserved;
	- Commenting the **GLPP_NO_GLFW_LEGACY** switch allows to build glpp
with GLFW v3.3.10, the latest supporting Windows XP. In this case, some
functions and constants of the recent GLFW library become unavailable;
	- When commenting the **GLPP_FREEIMAGE_LIB** switch, the FreeImage
class won't be included in the build. This library is no longer maintained,
but can deal with more formats compared to included StbImage;
	- The **GLPP_CONTEXT_VERSION_MAJOR** and **GLPP_CONTEXT_VERSION_MINOR**
switches indicate the minimum supporeted OpenGL context verion of the
library. Accepted combination of these values are: 2/0, 2/1, 3/0, 3/1, 3/2
and 3/3 to represent the OpenGL versions from 2.0 to 3.3 respectively;
	- The last 3 switches contain the key file paths. You don't have to
touch them, unless you really need to recalibrate the library path layout.

## INSTALLATION

The installation of glpp library isn't much more complicated than the setup
of original OpenGL API components. It actually includes those, while
#pragma comments sets the linking of all libraries. Once installation is
complete, the user no longer has to set it up in project proprieties, just
include THIS header **glpp.h** in the source file. The library must be built
within the application project's solution, it helps understanding the way
the library works. The path layout can be different, but it is advised to
use all suggested paths (at least for the first time). The offered setup
supports x64 and Win32 platforms, producing the console application in
Debug mode, and Windows application in Release mode.

1. Download the required OpenGL components from the Internet:	
    A. GLAD archive generated on https://glad.dav1d.de
	Choose Specification OpenGL, Profile Core, API: gl set to Version 3.3, Keep gles1, gles2 and glsc2 as None,
		Do not select any extension!
    B. GLFW archives v3.4 or later from https://www.glfw.org/download
	    64-bit Windows binaries, 32-bit Windows binaries
		Older versions are here: https://github.com/glfw/glfw/releases
    C. GLM header pack v1.0.1 or later from https://github.com/g-truc/glm
	The header files (.hpp/.h) from glm subfolder
    D. stb_image library from https://github.com/nothings/stb/tree/master
	It is important to use the specific versions of files. Every newer
		version of a file requires additional testings. If there is no such
		version, try using newer version (it usually works), or get the one
		preserved in Common subfolders:
		**stb_image.h** v2.29
		**stb_image_resize2.h** v2.06
		**stb_image_write.h** v1.16
    E. FreeImage library (optional) from https://freeimage.sourceforge.io
	The only DLL distribution is supported [WIN32/WIN64]
	
2. Create a new solution for the main project:
    File -> New -> Project... (Ctrl+Shift+N)
    Choose any name and path, e.g. OpenGL on the appropriate drive.

3. Within the solution directory create a folder named 'Common'. Put all
    unpacked components of the library in following sub-directories:
```
    $(SolutionDir)\Common\bin <- GLFW and FreeImage 64-bit Dlls
    $(SolutionDir)\Common\bin\Win32 <- GLFW and FreeImage 32-bit Dlls
    $(SolutionDir)\Common\include\glpp <- glpp include folder
    $(SolutionDir)\Common\include\glad <- Subfolder from GLAD 3.3 archive
    $(SolutionDir)\Common\include\GLFW <- 2 GLFW include headers
    $(SolutionDir)\Common\include\glm <- The whole <glm> subfolder
    $(SolutionDir)\Common\include\KHR <- Subfolder from GLAD 3.3 archive
    $(SolutionDir)\Common\include\stb <- 3 stb_image headers
    $(SolutionDir)\Common\include\FreeImage.h <- Single FreeImage header
    $(SolutionDir)\Common\lib <- GLFW, FreeImage 64-bit Libs
    $(SolutionDir)\Common\lib\Debug <- Empty, the glpp Dbg output
    $(SolutionDir)\Common\lib\Win32 <- GLFW, FreeImage 32-bit Libs
    $(SolutionDir)\Common\lib\Win32\Debug <- Empty, glpp 32-bit Dbg output
    $(SolutionDir)\Common\src\glpp <- glpp source folder
    $(SolutionDir)\Common\src\glad.c <- Source file from GLAD 3.3 archive
```

4. From the Solution explorer, right-click the solution name (1st line):
    Add -> New project..., select <Static Library (C++)>, press Next,
	choose the name <glpp>, which must be exactly so, press Create.
	
5. In the Solution Explorer remove all header and source files (Del).
	Right-click Header Files: Add -> Existing Item (Shift+Alt+A),
	Navigate to $(SolutionDir)\Common\include\glpp, select THIS <glpp.h>.
	Right-click Source Files, navigate the same way and select all .cpp
	files in the $(SolutionDir)\Common\src\glpp folder. Finally, add the
	same way to Source Files the $(SolutionDir)\Common\src\glad.c

6. Right-click glpp project name and press Proprties (Alt+Enter). In the
    Properties window set Configuration and Platform to Debug / x64. In
	the left frame under Configuration Properties set the following options
	and hit Apply after setting up any of 4 following configurations.
```
	Debug / x64 (LIB):
	    General -> Output Directory:
		    $(SolutionDir)\Common\lib\Debug\
	    VC++ Directories -> Include Directories
		    $(SolutionDir)\Common\include\;$(IncludePath)
	    VC++ Directories -> Library Directories
		    $(SolutionDir)\Common\lib\;$(LibraryPath)
	    C/C++ -> Precompiled Headers -> Precompiled Header
		    'Not Using Precompiled Headers'

	Release / x64 (LIB):
	    General -> Output Directory:
		    $(SolutionDir)\Common\lib\
	    VC++ Directories -> Include Directories
		    $(SolutionDir)\Common\include\;$(IncludePath)
	    VC++ Directories -> Library Directories
		    $(SolutionDir)\Common\lib\;$(LibraryPath)
	    C/C++ -> Precompiled Headers -> Precompiled Header
		    'Not Using Precompiled Headers'

	Debug / Win32 (LIB):
	    General -> Output Directory:
		    $(SolutionDir)\Common\lib\Win32\Debug\
	    VC++ Directories -> Include Directories
		    $(SolutionDir)\Common\include\;$(IncludePath)
	    VC++ Directories -> Library Directories
		    $(SolutionDir)\Common\lib\Win32\;$(LibraryPath)
	    C/C++ -> Precompiled Headers -> Precompiled Header
		    'Not Using Precompiled Headers'

	Release / Win32 (LIB):
	    General -> Output Directory:
		    $(SolutionDir)\Common\lib\Win32\
	    VC++ Directories -> Include Directories
		    $(SolutionDir)\Common\include\;$(IncludePath)
	    VC++ Directories -> Library Directories
		    $(SolutionDir)\Common\lib\Win32\;$(LibraryPath)
	    C/C++ -> Precompiled Headers -> Precompiled Header
		    'Not Using Precompiled Headers'
```

7. Close the Properties window. Now open any of library's source files,
   so the IDA focuses on glpp project within the solution. Select any of
   the 4 configurations on the top of IDE. Build the library.

The library supports OpenGL versions 2.0 to 3.3. To downgrade the default
version (3.3), you must generate a new GLAD archive, rename its **glad.h**
file to **gladXX.h** and move it into <glad> directory, do not use other
files from the downgraded archives, keep the files from v3.3. The XX is
the number of GLAD version: 20, 21, 30, 31, 32 for versions 2.0 to 3.2.
The context version control could be great for compatible coding. It is
recommended to generate all earlier versions of **glad.h** from 2.0 to 3.2
with **Core** profile, no extension selected, and to place them into **glad**
directory. Then you just need to change the **GLPP_CONTEXT_VERSION_MAJOR**
and **GLPP_CONTEXT_VERSION_MINOR** switches. Remember to rebuild the libeary
to make any changes come into effect. But to learn OpenGL, always stick to
default version 3.3!

By default glpp uses Dll version of GLFW library. It is much easier
to use pre-compiled .lib files of GLFW, rather than build from the sratch.
But when using Static GLFW build, while Debugging, if you by some accident
Step Into the function, you will get an unpleasant screen '.pdb not found',
it is because the .lib file does not have the right path of the source
files. While using Dll version, the function is simply stepped out. When
compiling the final version of your project, you may switch to the Static
GLFW build by setting the **GLPP_GLFW_LIB** switch to glfw3.lib/glfw3_mt.lib.
Note that using Dlls decreases the application file size, and saves the
computer RAM while running several applications using that Dll, but the
appropriate Dll must be distributed with the application.

## USAGE

1. To add the application project to the solution, use the same way as for
    the glpp library: in the Solution Explorer right-click the solution
	name (1st line), Add -> New project..., select <Empty Project (C++)>,
	press Next, choose any name, press Create

2. In the Solution Explorer, right-click the project's name and press
    Set as Startup Project, to set default running output application

3. Right-click the project's name and press Proprties (Alt+Enter). In the
    Properties window set Configuration and Platform to Debug / x64. In
	the left frame under Configuration Properties set the following options
	and hit Apply after setting up any of 4 following configurations.
```
	Debug / x64 (EXE):
	Debugging -> Environment -> <Edit...>
			In the first edit box enter the line and hit Ok:
		path=%path%;$(SolutionDir)\Common\bin\
	    VC++ Directories -> Include Directories
	    $(SolutionDir)\Common\include\;$(IncludePath)
	VC++ Directories -> Library Directories
	    $(SolutionDir)\Common\lib\;$(LibraryPath)
	Linker -> System -> SubSystem
		    'Console (/SUBSYSTEM:CONSOLE)'
	
	Release / x64 (EXE):
	Debugging -> Environment -> **Edit...**
			In the first edit box enter the line and hit Ok:
			path=%path%;$(SolutionDir)\Common\bin\
	    VC++ Directories -> Include Directories
	    $(SolutionDir)\Common\include\;$(IncludePath)
	VC++ Directories -> Library Directories
	    $(SolutionDir)\Common\lib\;$(LibraryPath)
	Linker -> System -> SubSystem,
		    'Windows (/SUBSYSTEM:WINDOWS)'
		Linker -> Advanced -> Entry Point
		    mainCRTStartup

	Debug / Win32 (EXE):
	Debugging -> Environment -> **Edit...**
			In the first edit box enter the line and hit Ok:
			path=%path%;$(SolutionDir)\Common\bin\Win32\
	    VC++ Directories -> Include Directories
	    $(SolutionDir)\Common\include\;$(IncludePath)
	VC++ Directories -> Library Directories
	    $(SolutionDir)\Common\lib\;$(LibraryPath)
	Linker -> System -> SubSystem,
		    'Console (/SUBSYSTEM:CONSOLE)'

	Release / Win32 (EXE):
	Debugging -> Environment -> **Edit...**
			In the first edit box enter the line and hit Ok:
			path=%path%;$(SolutionDir)\Common\bin\Win32\
	    VC++ Directories -> Include Directories
	    $(SolutionDir)\Common\include\;$(IncludePath)
	VC++ Directories -> Library Directories
	    $(SolutionDir)\Common\lib\;$(LibraryPath)
	Linker -> System -> SubSystem,
		    'Windows (/SUBSYSTEM:WINDOWS)'
		Linker -> Advanced -> Entry Point
		    mainCRTStartup
```

4. In the Solution Explorer, right-click the project's Source Files folder:
    Add -> New Item... (Ctrl+Shift+A), select C++ File (.cpp), type any
	name it as 'main.cpp' or other, press Add
	
5. In opened file type the minimal glpp application code:
```
	// main.cpp
	#include <glpp/glpp.h>
	int main(int argc, char** argv)
	{
		glfw::Window glWindow(800, 600, "LearnOpenGL");
		glWindow.makeContextCurrent();
		while (!glWindow.windowShouldClose())
		{
			gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
			gl::clear(gl::BufferBitMask::ColorBufferBit);
			glWindow.swapBuffers();
			glfw::pollEvents();
		}
		return 0;
	}
```

6. To overload window events, create new window class before main function:
```
	// main.cpp
	class LearnOpenGL : public glfw::Window
	{
		using Window::Window; // Base constructors
		void onFramebuffer(int width, int height)
		{
			gl::viewport(0, 0, width, height);
		}
	};
```

7. And lastly, the example of the library usage in AFX-like layout:
```
	// main.cpp
	class GLApplication : public glfw::ThreadWnd
	{
		void onInitThread()
		{
			m_pWindow = new LearnOpenGL(1280, 720, "LearnOpenGL");
			m_pWindow->makeContextCurrent(this);
		}
		void onRenderWindow()
		{
			gl::clearColor(0.3f, 0.2f, 0.2f, 1.0f);
			gl::clear(gl::BufferBitMask::ColorBufferBit);
		}
	};
	GLApplication glApplication;
```
