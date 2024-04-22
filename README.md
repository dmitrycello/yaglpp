# glpp: OpenGL C++ extension library 24.4.1
## (README under development, currently solving formatting issues, adding pics etc.)

This project is an attempt to develop a C++ OpenGL library, combining the API calls within the C++ objects. Initially, its main goal was to help learning GLAD/GLFW API, but it definatelly could to be used as an efficient tool, allowing to develop the OpenGL applications in less complicated manner with minimal overhead.

It requires the C++ 11 compiler or later, it also impliments the concept of SAL (Microsoft Source Code Annotation Language) in Debug build only, any warnings in the Release mode should be ignored. At the moment, it is developped for Windows OS only using Visual Studio 2019+.

The library works with GLAD version from 2.0 to 3.3, and GLFW version 3.4+. The used GLAD version affects the build, hiding the unsupported API functions. C++ allows to use the overloaded functions, which is much easier than to find the every exact API function, such as **`glUniform3fv`**. Usage of C++ classes makes the OpenGL programming more compact, clear and stable. Every call to the API function in the library is provided with the appropriate error checking, which has an effect only in Debug build. The Release build attempts to impliment the inline calls, depending on the compiler setting.

The library functions are defined within **`gl::`** and **`glfw::`** namespaces for GLAD and GLFW API functions respectively. The few helper classes, such as **`StbImage`**, reside in the global namespace. The API functions are grouped around the objects, and the API constants are grouped around the enum classes. The original API names are carefully preserved, except very rare cases (e.g. **`BufferTexture`** is a texture, but **`TextureBuffer`** is a buffer).

The API name prefixes gl and glwf are stripped, and the camil-case roule is applied. For the constant names, every underscore symbol is used as a word delimiter. Such an approach helps learning the original API symbols for potential switching to OpenGL C programming. The underscore at the beginning of the name means a private assignment, you should NOT be using these names. Some of the API functions such as **`glDisable`**, **`glEnable`**, **`glGet`**, **`glIsEnabled`**, and **`glPixelStore`** are used with the names of their constant values. For example:
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
You can bypass the **`gl::`** and **`glfw::`** prefixes with **`using namespace`** directives, but it is advised to keep them at least while learning the API. The prefixes will also prevent name conflict while managing large projects. Some of the functions are duplicated as a static members of a class, it helps to find them on the context basis. The global symbols starting with **`GLPP_`** are preserved by the library.

The most valuable library's feature is the **`"lasy" creation and binding concept`**. It means, the OpenGL object is created and binded only when it is required. The creation of glpp class object does not mean the OpenGL object immediate creation or binding. The appropriate functions for creation and bindind are no longer needed, but still preserved to allow the programmer to create or bind the OpenGL object at anytime. The object status is saved in thread local memory, which makes the library thread safe.

Every methode or enum member in the library is provided with the comment shown by the IntelliSense with the description, parameter list and return value. So it could be a nice way to briefly recap what the function does, instead of going online time after time. All information is taken from [Khronos website](https://registry.khronos.org/OpenGL-Refpages/gl4/).

If you don't know the function, you should visit this website to read the whole dedicated info. If the comment starts with the number in parentheses, it means either the minimum supported OpenGL version (2.1-3.3), or the number of overloaded method (1-x). If the version is missing, OpenGL 2.0 support is assumed. For example, if the comment starts with **`(3.0) (18)`** , it means that OpenGL 3.0 is required, and this is the 18's overloaded member.

The swithes following **`#pragma once`** directive in the **`glpp.h`** file affect the build of the library. The first six could be commented, the others may only be altered:
- Switches **`GLPP_COCOA_CHDIR_RESOURCES`**, **`GLPP_COCOA_MENUBAR`** and **`GLPP_JOYSTICK_HAT_BUTTONS`** are the GLFW flags set at the initialization, they are on by default;
- Commenting the **`GLPP_NO_AFX_LAYOUT`** switch will transform the glpp into the AFX-like environment, without the **`main`** function. Instead, you have to inherit a class from **`ThreadWnd`**, and overwrite its virtual functions. Otherwise, classical layout with the **`main`** function is preserved;
- Commenting the **`GLPP_NO_GLFW_LEGACY`** switch allows to build glpp with GLFW v3.3.10, the latest version supporting Windows XP. In this case, some functions and constants of the recent GLFW libraries become unavailable;
- When commenting the **`GLPP_FREEIMAGE_LIB`** switch, the **`FreeImage`** class won't be included in the build. This library is no longer maintained, but can deal with more formats compared to included **`StbImage`**;
- The **`GLPP_CONTEXT_VERSION_MAJOR`** and **`GLPP_CONTEXT_VERSION_MINOR`** switches indicate the minimum supporeted OpenGL context verion of the library. Accepted combination of these values are: 2/0, 2/1, 3/0, 3/1, 3/2 and 3/3 to represent the OpenGL versions from 2.0 to 3.3 respectively;
- The last 3 switches contain the key file paths. You don't have to touch them, unless you really need to recalibrate the library path layout.

## INSTALLATION

The installation of glpp library isn't much more complicated than the setup of original OpenGL API components. It actually includes those, while **`#pragma comments`** sets the linking of all libraries. Once installation is complete, the user no longer has to set it up in project proprieties, just to include the **`glpp.h`** file in the source. The library must be built within the application project's solution, it helps understanding the way the library works. The path layout can be different, but it is advised to use all suggested paths (at least for the first time). The offered setup supports **`x64`** and **`Win32`** platforms, producing the console application in Debug mode, and Windows application in Release mode.

> [!TIP]
> You may skip step 1 and 2, if you decide to use the files from the repository, in which case you only need to download ZIP archive (big green **`Code`** button on the main repository page), extract the whole **`Common`** subdirectory, and proceed to step 3. However, it is still recommended to get all components from the Internet, at least for the first time to feel the process. This is also the way the most programmers do, to ensure that the versions are up to date.

### 1. Download the required OpenGL components from the Internet
- [GLAD](https://glad.dav1d.de) archive generated with Specification set to **`OpenGL`**, Profile set to **`Core`**, API **`gl`** set to **`Version 3.3`**. Keep gles1, gles2 and glsc2 as **`None`**. Do not select any extension!
- [GLFW](https://www.glfw.org/download) archives v3.4 or later from  the 64-bit and 32-bit Windows binaries. Older versions are [here](https://github.com/glfw/glfw/releases).
- [GLM](https://github.com/g-truc/glm) pack v1.0.1 or later.
- [stb_image](https://github.com/nothings/stb/tree/master) library. It is important to use the specific versions of its files. Every newer version of a file requires additional testings. If there is no such version, try using newer version (it usually works), or get the one preserved in this repository. The required files are:
	+ **stb_image.h** v2.29
	+ **stb_image_resize2.h** v2.06
	+ **stb_image_write.h** v1.16
- [FreeImage](https://freeimage.sourceforge.io) library (optional). The only DLL distribution is supported [WIN32/WIN64]. The project is not being updated since 2015, so if you decide not to include it, make sure to comment the **`GLPP_FREEIMAGE_LIB`** switch in the **`glpp.h`** file.

### 2. Prepare the OpenGL components's folder
Create the new folder anywhere on your PC, and name it **`Common`**. Extract all downloaded OpenGL components, and move them into its following subdirectories:
```
Common\bin\ <- GLFW and FreeImage 64-bit Dlls
Common\bin\Win32\ <- GLFW and FreeImage 32-bit Dlls
Common\include\glpp\ <- glpp include headers
Common\include\glad\glad.h <- header from GLAD archive
Common\include\GLFW\ <- 2 GLFW include headers
Common\include\glm\ <- The whole <glm> subfolder
Common\include\KHR\khrplatform.h <- header from GLAD archive
Common\include\stb\ <- 3 stb_image above mentionned headers
Common\include\FreeImage.h <- FreeImage header
Common\lib\ <- GLFW, FreeImage 64-bit Libs
Common\lib\Debug\ <- Empty (glpp 64-bit Debug output)
Common\lib\Win32\ <- GLFW, FreeImage 32-bit Libs
Common\lib\Win32\Debug\ <- Empty (glpp 32-bit Debug output)
Common\src\glpp\ <- glpp source files
Common\src\glad.c <- Source file from GLAD archive
```
### 3. Create a new solution for the library and the main project
On the Visual Studio click **`File -> New -> Project... (Ctrl+Shift+N)`**:

> [!NOTE]
> You can later create mutiple projects under the same solution, so the reinstallation of the library in not required.

![01.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/01.png)

Select **`Blanc Solution`**, hit **`Next`**:

![02.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/02.png)

Choose any name and path to solution, e.g. OpenGL on the appropriate drive, hit **`Create`**:

![03.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/03.png)

Finally, move the previously created **`Common`** directory into the solution directory.

### 4. Create new static library project under the newly created solution
In the Solution explorer, right-click the solution name bar (1st line). Click **`Add -> New project...`**:

![04.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/04.png)

Select **`Static Library (C++)`**, hit **`Next`**:

![05.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/05.png)

Type the static library project name, which must be exactly **`glpp`**, check the path to the solution, and hit **`Create`**:

![06.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/06.png)

### 5. Add files to the glpp library project
In the Solution Explorer remove all header and source files **`(Del)`**. These files no longer needed, so they could be deleted permanently:

![07.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/07.png)

Right-click **`Header Files`** filter icon, click **`Add -> Existing Item (Shift+Alt+A)`**. Navigate to **`$(SolutionDir)\Common\include\glpp`** directory, select **`glpp.h`** file, it has to be here just to toggle the switches:

![08.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/08.png)

Next, right-click **`Source Files`** filter icon, click **`Add -> Existing Item (Shift+Alt+A)`**. Navigate to **`$(SolutionDir)\Common\src\glpp`** directory, and select all **`.cpp`** files:

![09.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/09.png)

Finally, add the same way the **`$(SolutionDir)\Common\src\glad.c`** file to **`Source Files`** filter. The Solution Explorer should now look like this:

![10.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/10.png)

### 6. Set the project proprties
Right-click glpp project name bar and press **`Proprties (Alt+Enter)`**:

![11.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/11.png)

In the Properties window set **`Configuration`** and **`Platform`** drop-down menus to **`Debug`** and **`x64`**. It is going to be our first platform configuration to set up:

![12.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/12.png)

Now we need to set up 4 configuration options for that platform configuration and hit the **`Apply`** button. To set up an option, select the category at the left-hand side, then select the option at the right-hand side, click the drop-down menu at the right, and hit **`<Edit...>`**, or set the available option:

![13.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/13.png)

The library supports 4 platform configurations: **`Debug / x64`**, **`Release / x64`**, **`Debug / Win32`**, **`Release / Win32`**. Here is the list of the required options under each of the 4 platform configurations in form **`category -> name: value`**:

> [!IMPORTANT]
> You may never use the last two configurations. But it is recommended to set it up now, to avoid the mess later.

- **`Debug / x64 (LIB)`**:
```
General -> Output Directory: $(SolutionDir)\Common\lib\Debug\
VC++ Directories -> Include Directories: $(SolutionDir)\Common\include\;$(IncludePath)
VC++ Directories -> Library Directories: $(SolutionDir)\Common\lib\;$(LibraryPath)
C/C++ -> Precompiled Headers -> Precompiled Header: 'Not Using Precompiled Headers'
```
- **Release / x64 (LIB)**:
```
General -> Output Directory: $(SolutionDir)\Common\lib\
VC++ Directories -> Include Directories: $(SolutionDir)\Common\include\;$(IncludePath)
VC++ Directories -> Library Directories: $(SolutionDir)\Common\lib\;$(LibraryPath)
C/C++ -> Precompiled Headers -> Precompiled Header: 'Not Using Precompiled Headers'
```
- **`Debug / Win32 (LIB)`**:
```
General -> Output Directory: $(SolutionDir)\Common\lib\Win32\Debug\
VC++ Directories -> Include Directories: $(SolutionDir)\Common\include\;$(IncludePath)
VC++ Directories -> Library Directories: $(SolutionDir)\Common\lib\Win32\;$(LibraryPath)
C/C++ -> Precompiled Headers -> Precompiled Header: 'Not Using Precompiled Headers'
```
- **`Release / Win32 (LIB)`**:
```
General -> Output Directory: $(SolutionDir)\Common\lib\Win32\
VC++ Directories -> Include Directories: $(SolutionDir)\Common\include\;$(IncludePath)
VC++ Directories -> Library Directories: $(SolutionDir)\Common\lib\Win32\;$(LibraryPath)
C/C++ -> Precompiled Headers -> Precompiled Header: 'Not Using Precompiled Headers'
```
> [!WARNING]
> Do not forget to hit the **`Apply`** button after setting up the options for each platform configuration.

### 7. Build the library
Now close the Properties window. In the Solution Explorer open **`glpp.h`** file, so the IDA focuses on glpp project within the solution. Select any of the 4 configurations on the top of IDE:

![14.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/14.png)

Click **`Build -> Rebuild glpp`**:

![15.png](https://github.com/dmitrycello/dmitrycello/blob/main/glpp/15.png)

The rebuild ensures to process every source from scratch. The outpud should look like this:
```
Rebuild started...
1>------ Rebuild All started: Project: glpp, Configuration: Debug x64 ------
1>glad.c
1>Buffer.cpp
1>Cursor.cpp
1>DataStore.cpp
1>Framebuffer.cpp
1>FreeImage.cpp
1>gladpp.cpp
1>gladpp.cpp: Compiling with GLAD version 3.3 support...
1>glfw3pp.cpp
1>glfw3pp.cpp: Compiling with GLFW version 3.4 nonlegacy support...
1>glpp.cpp
1>Joystick.cpp
1>Monitor.cpp
1>Object.cpp
1>Program.cpp
1>Query.cpp
1>Renderbuffer.cpp
1>Sampler.cpp
1>Shader.cpp
1>StbImage.cpp
1>Sync.cpp
1>Texture.cpp
1>Thread.cpp
1>Generating Code...
1>Compiling...
1>Uniform.cpp
1>UniformBlock.cpp
1>VertexArray.cpp
1>VertexAttrib.cpp
1>Window.cpp
1>Generating Code...
1>glpp.vcxproj -> D:\Path_to_solution\OpenGL\Common\lib\Debug\glpp.lib
========== Rebuild All: 1 succeeded, 0 failed, 0 skipped ==========
```
The library supports OpenGL versions 2.0 to 3.3. To downgrade the default version (3.3), you must generate a new GLAD archive, rename its **`glad.h`** file to **`gladXX.h`** and move it into **`glad`** directory, do not use other files from the downgraded archives. The XX is the number of GLAD version: 20, 21, 30, 31, 32 for versions 2.0 to 3.2. The context version control could be great for backward compatible coding.

It is recommended to generate all earlier versions of **`glad.h`** from 2.0 to 3.2 with **`Core`** profile, no extension selected, and to place them into **`glad`** directory. Now you just need to change the **`GLPP_CONTEXT_VERSION_MAJOR`** and **`GLPP_CONTEXT_VERSION_MINOR`** switches, and rebuild the libeary. But to learn OpenGL, always stick to default version 3.3!

By default glpp uses Dll version of GLFW library. It is much easier to use pre-compiled .lib files of GLFW, rather than build them from sratch. But when using Static GLFW build, while Debugging, if you by some accident Step Into the function, you will get an unpleasant screen '.pdb not found', it is because the .lib file does not have the right path of the source file. While using Dll version, the function is simply stepped out. When compiling the final version of your project, you may switch to the Static GLFW build by setting the **`GLPP_GLFW_LIB`** switch to **`glfw3.lib/glfw3_mt.lib`**. Note that using Dlls decreases the application file size, and saves the computer RAM while running several applications using that Dll, but the appropriate Dll must be distributed with the application.

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
