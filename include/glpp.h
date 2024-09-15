/*
    +---------------------------------------+
    |   YAGL++: Yet Another GL++ library    |
    +---------------------------------------+
    v24.9.1
    Project dependencies:
    - GLAD v2.0-3.3
    - GLFW v3.4
    - GLM v1.0.1
    - stb_image.h v2.29
    - stb_image_resize2.h v2.06
    - stb_image_write.h v1.16
    - Assimp v5.4.3
    All information can be found here:
    https://github.com/dmitrycello/yaglpp/blob/main/README.md
*/
#pragma once
/*Custom project config override*/
#ifndef YAGLPP_CONFIG

/*---------------------*/
/* MAIN SWITCHES BEGIN */
/*---------------------*/

/*Define <CocoaChdirResources> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_CHDIR_RESOURCES

/*Define <CocoaMenubar> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_MENUBAR

/*Define <JoystickHatButtons> pre-initialize GLFW hint*/
#define YAGLPP_JOYSTICK_HAT_BUTTONS

/*Include the class properties along with existing getters and setters*/
#define YAGLPP_CLASS_PROPERTIES

/*Include all GLM library headers, slightly affects the compilation time*/
#define YAGLPP_GLM_HEADERS

/*Do not include main entry point into YAGL++ library*/
#define YAGLPP_NO_AFX_LAYOUT

/*Compile with the most recent GLFW nonlegacy library*/
#define YAGLPP_NO_GLFW_LEGACY

/*Define the minimum supported OpenGL context major version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MAJOR 3

/*Define the minimum supported OpenGL context minor version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MINOR 3

/*Define Assimp library file name, comment to exclude Assimp*/
#define YAGLPP_ASSIMP "assimp-vc142-mt.lib"

/*Define GLFW library file name, comment to exclude GLFW*/
#define YAGLPP_GLFW "glfw3.lib"

/*-------------------*/
/* MAIN SWITCHES END */
/*-------------------*/

#endif // #ifndef YAGLPP_CONFIG
#include <windows.h>
#include <iostream>
#include <glm/fwd.hpp>
#ifdef __cplusplus
namespace glm {
/*Two-component char vector type defined by YAGL++*/
typedef tvec2<char> cvec2;

/*Two-component unsigned char vector type defined by YAGL++*/
typedef tvec2<unsigned char> ucvec2;

/*Two-component short vector type defined by YAGL++*/
typedef tvec2<short> svec2;

/*Two-component unsigned short vector type defined by YAGL++*/
typedef tvec2<unsigned short> usvec2;

/*Three-component char vector type defined by YAGL++*/
typedef tvec3<char> cvec3;

/*Three-component unsigned char vector type defined by YAGL++*/
typedef tvec3<unsigned char> ucvec3;

/*Three-component short vector type defined by YAGL++*/
typedef tvec3<short> svec3;

/*Three-component unsigned short vector type defined by YAGL++*/
typedef tvec3<unsigned short> usvec3;

/*Four-component char vector type defined by YAGL++*/
typedef tvec4<char> cvec4;

/*Four-component unsigned char vector type defined by YAGL++*/
typedef tvec4<unsigned char> ucvec4;

/*Four-component short vector type defined by YAGL++*/
typedef tvec4<short> svec4;

/*Four-component unsigned short vector type defined by YAGL++*/
typedef tvec4<unsigned short> usvec4;
} // namespace glm

class DataStore;
class StbImage;
struct StbCallbacks;
enum class StbFormat : int;
char* _copyString(const char* source);
LPBYTE _loadFile(const char* file, int* size);
LPBYTE _loadResource(int rcid, int* size);
void _writeFile(const char* file, const void* data, int size);

/*YAGL++ memory deallocation macro*/
#define YAGLPP_FREE(p) free(p)

#ifdef _DEBUG
_Ret_notnull_ void* _assertCalloc(size_t size);
_Ret_notnull_ void* _assertMalloc(size_t size);
_Ret_notnull_ void* _assertRealloc(void* ptr, size_t size);
#ifdef YAGLPP_IMPLEMENTATION
#define YAGLPP_DEBUG_IMPLEMENTATION
#endif // #ifdef YAGLPP_IMPLEMENTATION

/*YAGL++ assertion macro, does nothing in Release mode*/
#define YAGLPP_ASSERT(e) assert(e)

/*YAGL++ zeroed memory allocation macro, does no assertion in Debug mode*/
#define YAGLPP_CALLOC(s) _assertCalloc(s)

/*YAGL++ raw memory allocation macro, does no assertion in Debug mode*/
#define YAGLPP_MALLOC(s) _assertMalloc(s)

/*YAGL++ memory reallocation macro, does no assertion in Debug mode*/
#define YAGLPP_REALLOC(p, s) _assertRealloc(p, s)

#else // #ifdef _DEBUG (RELEASE)
#define YAGLPP_INLINE_IMPLEMENTATION
#define YAGLPP_ASSERT(e) ((void)0)
#define YAGLPP_CALLOC(s) calloc(s, 1)
#define YAGLPP_MALLOC(s) malloc(s)
#define YAGLPP_REALLOC(p, s) realloc(p, s)
#endif // #ifdef _DEBUG

/*YAGL++ helper function, checks if the file with given path exists using <stat> structure
@param [in] The requested file with given path
@return True if file exists, false otherwise*/
inline bool fileExists(_In_z_ const char* file)
{
    struct stat buffer; return stat(file, &buffer) == 0;
}

/*YAGL++ helper function, deallocates the memory block previously allocated by the library
@param [in] The pointer to freed memory block*/
inline void freeMemory(_In_ void* block)
{
    YAGLPP_FREE(block);
}

#ifdef YAGLPP_IMPLEMENTATION
char* _copyString(const char* source)
{
    if (source == nullptr) return nullptr;
    size_t iLen = strlen(source);
    char* pBuffer = (char*)YAGLPP_MALLOC(iLen);
    errno_t iError = strcpy_s(pBuffer, iLen, source);
    YAGLPP_ASSERT(iError == 0); // FAILED TO COPY STRING
    return pBuffer;
}

LPBYTE _loadFile(const char* file, int* size)
{
    FILE* pFile;
    YAGLPP_ASSERT(file != nullptr); // FILE PARAMETER COULD NOT BE NULL
    errno_t iError = fopen_s(&pFile, file, "rb");
    YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD FILE
    fseek(pFile, 0, SEEK_END);
    *size = ftell(pFile);
    rewind(pFile);
    LPBYTE lpData = (LPBYTE)YAGLPP_MALLOC(*size);
    fread(lpData, 1, *size, pFile);
    fclose(pFile);
    return lpData;
}

LPBYTE _loadResource(int rcid, int* size)
{
    static HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(rcid), RT_RCDATA);
    YAGLPP_ASSERT(hResource != NULL); // FAILED TO FIND RESOURCE ID
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    YAGLPP_ASSERT(hMemory != NULL); // FAILED TO LOAD RESOURCE ID
    *size = SizeofResource(hModule, hResource);
    return (LPBYTE)LockResource(hMemory);
}

void _writeFile(const char* file, const void* data, int size)
{
    FILE* pFile;
    YAGLPP_ASSERT(file != nullptr); // FILE PARAMETER COULD NOT BE NULL
    errno_t iError = fopen_s(&pFile, file, "wb");
    YAGLPP_ASSERT(iError == 0); // FAILED TO WRITE FILE
    fwrite(data, 1, size, pFile);
    fclose(pFile);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
_Ret_notnull_ void* _assertCalloc(size_t size)
{
    void* pNew = calloc(size, 1);
    YAGLPP_ASSERT(pNew); // FAILED TO ALLOCATE ZEROED MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertMalloc(size_t size)
{
    void* pNew = malloc(size);
    YAGLPP_ASSERT(pNew); // FAILED TO ALLOCATE RAW MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertRealloc(void* ptr, size_t size)
{
    void* pNew = realloc(ptr, size);
    YAGLPP_ASSERT(pNew); // FAILED TO REALLOCATE MEMORY
    return pNew;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_GLM_HEADERS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif // #ifdef YAGLPP_GLM_HEADERS

#ifdef YAGLPP_ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma comment(lib, YAGLPP_ASSIMP)
#endif // #ifdef YAGLPP_ASSIMP

#include <yaglpp/data_store.h>
#include <yaglpp/stb_image.h>
#include <yaglpp/gladpp.h>
#pragma comment(lib, "opengl32.lib")

#ifdef YAGLPP_GLFW
#include <yaglpp/glfw3pp.h>
#pragma comment(lib, YAGLPP_GLFW)
#endif // #ifdef YAGLPP_GLFW

#else // #ifdef __cplusplus
#error YAGL++ requires C++ compiler
#endif // #ifdef __cplusplus
