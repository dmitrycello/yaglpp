/*
	+-----------------------------------------+
	|   glpp: OpenGL C++ extension library    |
	+-----------------------------------------+

	All information/instructions can be found here:
	https://github.com/dmitrycello/glpp/blob/main/README.md
*/
#pragma once

/*Define <CocoaChdirResources> pre-initialize hint*/
#define GLPP_COCOA_CHDIR_RESOURCES

/*Define <CocoaMenubar> pre-initialize hint*/
#define GLPP_COCOA_MENUBAR

/*Define <JoystickHatButtons> pre-initialize hint*/
#define GLPP_JOYSTICK_HAT_BUTTONS

/*Do not include main entry point into glpp library*/
#define GLPP_NO_AFX_LAYOUT

/*Compile with the most recent GLFW nonlegacy library*/
#define GLPP_NO_GLFW_LEGACY

/*Use FreeImage library, define path to Static/Dll build*/
#define GLPP_FREEIMAGE_LIB "FreeImage.lib"

/*Define the minimum supported glpp context major version value*/
#define GLPP_CONTEXT_VERSION_MAJOR 3

/*Define the minimum supported glpp context minor version value*/
#define GLPP_CONTEXT_VERSION_MINOR 3

/*Define path to Static/Dll/MT build of GLFW3 library*/
#define GLPP_GLFW_LIB "glfw3dll.lib"

/*Define glpp library debug output path*/
#define GLPP_DEBUG_LIB "Debug/glpp.lib"

/*Define glpp library release output path*/
#define GLPP_RELEASE_LIB "glpp.lib"

/* END OF ADJUSTABLE SWITCHES */
#include <windows.h>
#include <iostream>
#include <glm/glm.hpp>
#ifdef __cplusplus
namespace glm {
/*Two-component char vector type defined by glpp*/
typedef tvec2<char> cvec2;

/*Two-component unsigned char vector type defined by glpp*/
typedef tvec2<unsigned char> ucvec2;

/*Two-component short vector type defined by glpp*/
typedef tvec2<short> svec2;

/*Two-component unsigned short vector type defined by glpp*/
typedef tvec2<unsigned short> usvec2;

/*Three-component char vector type defined by glpp*/
typedef tvec3<char> cvec3;

/*Three-component unsigned char vector type defined by glpp*/
typedef tvec3<unsigned char> ucvec3;

/*Three-component short vector type defined by glpp*/
typedef tvec3<short> svec3;

/*Three-component unsigned short vector type defined by glpp*/
typedef tvec3<unsigned short> usvec3;

/*Four-component char vector type defined by glpp*/
typedef tvec4<char> cvec4;

/*Four-component unsigned char vector type defined by glpp*/
typedef tvec4<unsigned char> ucvec4;

/*Four-component short vector type defined by glpp*/
typedef tvec4<short> svec4;

/*Four-component unsigned short vector type defined by glpp*/
typedef tvec4<unsigned short> usvec4;
} // namespace glm

/*glpp helper function, checks if the file with given path exists using <stat> structure
@param [in] The requested file with given path
@return True if file exists, false otherwise*/
bool fileExists(_In_z_ const char* file);

class DataStore;
class StbImage;
enum class StbFormat : int;

#ifdef GLPP_FREEIMAGE_LIB
class FreeImage;
#endif // #ifdef GLPP_USE_FREEIMAGE

#ifdef GLPP_BUILD_LIB
/*glpp memory deallocation macro*/
#define GLPP_FREE(p) free(p)

#ifdef _DEBUG
_Ret_notnull_ void* _assertCalloc(size_t);
_Ret_notnull_ void* _assertMalloc(size_t);
_Ret_notnull_ void* _assertRealloc(void*, size_t);
void _clock(const char*);

/*glpp assertion macro, does nothing in Release mode*/
#define GLPP_ASSERT(e) assert(e)

/*glpp CPU clock counter macro, does nothing in Release mode*/
#define GLPP_CLOCK(c) _clock(c)

/*glpp Debug only statement macro, does nothing in Release mode*/
#define GLPP_DEBUG(s) s

/*glpp zeroed memory allocation macro, does nothing in Release mode*/
#define GLPP_CALLOC(s) _assertCalloc(s)

/*glpp raw memory allocation macro, does nothing in Release mode*/
#define GLPP_MALLOC(s) _assertMalloc(s)

/*glpp memory reallocation macro, does nothing in Release mode*/
#define GLPP_REALLOC(p, s) _assertRealloc(p, s)

#else // #ifdef _DEBUG
#define GLPP_ASSERT(e)
#define GLPP_CLOCK(c)
#define GLPP_DEBUG(s)
#define GLPP_CALLOC(s) calloc(s, 1)
#define GLPP_MALLOC(s) malloc(s)
#define GLPP_REALLOC(p, s) realloc(p, s)
#endif // #ifdef _DEBUG

#else // #ifdef GLPP_BUILD_LIB
#include "DataStore.h"
#include "FreeImage.h"
#include "StbImage.h"
#include "gladpp.h"
#include "glfw3pp.h"

#ifdef _DEBUG
#pragma comment(lib, GLPP_DEBUG_LIB)
#else // #ifdef _DEBUG
#pragma comment(lib, GLPP_RELEASE_LIB)
#endif // #ifdef _DEBUG
#endif // #ifndef GLPP_BUILD_LIB

#else // #ifdef __cplusplus
#error glpp requires C++ compiler
#endif // #ifdef __cplusplus
