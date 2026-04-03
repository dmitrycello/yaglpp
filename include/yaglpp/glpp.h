/*
    +---------------------------------------+
    |   YAGL++: Yet Another GL++ library    |
    +---------------------------------------+
    Project dependencies:
    - GLAD 4.6
    - GLFW 3.4
    - GLM 1.0.1
    - Assimp 5.4.3
    - stb_image.h 2.30
    - stb_image_write.h 1.16
    - stb_image_resize2.h 2.17
    All information can be found here:
    https://github.com/dmitrycello/yaglpp/blob/main/README.md
*/

#ifndef YAGLPP_GLPP_H
#define YAGLPP_GLPP_H

/*Custom project config override*/
#ifndef YAGLPP_CONFIG
/*
    +-------------------------+
    |   MAIN SWITCHES BEGIN   |
    +-------------------------+
*/

/*Include Assimp library headers, comment to exclude Assimp*/
#define YAGLPP_ASSIMP

/*Define <CocoaChdirResources> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_CHDIR_RESOURCES

/*Define <CocoaMenubar> pre-initialize GLFW hint*/
#define YAGLPP_COCOA_MENUBAR

/*Define <JoystickHatButtons> pre-initialize GLFW hint*/
#define YAGLPP_JOYSTICK_HAT_BUTTONS

/*Include the class properties along with existing getters and setters*/
#define YAGLPP_CLASS_PROPERTIES

/*Include GLFW library headers, comment to exclude GLFW*/
#define YAGLPP_GLFW

/*Include all GLM library headers, slightly affects the compilation time*/
#define YAGLPP_GLM_HEADERS

/*Override the global new and delete operators, using the library allocator*/
#define YAGLPP_GLOBAL_ALLOCATOR

/*Do not include main entry point into YAGL++ library*/
#define YAGLPP_NO_AFX_LAYOUT

/*Compile with the most recent GLFW nonlegacy library*/
#define YAGLPP_NO_GLFW_LEGACY

/*Define the minimum supported OpenGL context major version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MAJOR 3

/*Define the minimum supported OpenGL context minor version value, do not comment*/
#define YAGLPP_CONTEXT_VERSION_MINOR 3

/*
    +-----------------------+
    |   MAIN SWITCHES END   |
    +-----------------------+
*/
#endif

#ifdef _MSC_VER
    #if !defined(__cplusplus) || (_MSC_VER < 1700)
        #error "YAGL++ requires C++ 11 compiler or later"
    #endif
    #define YAGLPP_MSVC
    #include <sal.h>
#else
    #if !defined(__cplusplus) || (__cplusplus < 201103L)
        #error "YAGL++ requires C++ 11 compiler or later"
    #endif
    #ifdef YAGLPP_CLASS_PROPERTIES
        #error "Microsoft class properties cannot be used in non-MSVC environment"
    #endif
    #include <yaglpp/no_msvc.h>
#endif

#define _CRT_SECURE_NO_WARNINGS
#include <mutex>
#include <queue>
#include <cstdio>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <condition_variable>

#ifdef _DEBUG
    #include <cassert>
    #include <iostream>
#endif

#ifdef YAGLPP_IMPLEMENTATION
    #ifdef _DEBUG
        #define YAGLPP_DEBUG_IMPLEMENTATION
        #define YAGLPP_ASSERT(e) assert(e)
    #else
        #define YAGLPP_INLINE_IMPLEMENTATION
        #define YAGLPP_ASSERT(e) ((void)0)
    #endif
    #define YAGLPP_MALLOC(t,s) (t*)yaglpp_allocate(s*sizeof(t),nullptr)
    #define YAGLPP_CALLOC(t,s) (t*)yaglpp_callocate(s*sizeof(t),nullptr)
    #define YAGLPP_REALLOC(t,p,s) (t*)yaglpp_reallocate(p,s*sizeof(t),nullptr)
    #define YAGLPP_FREE(p) yaglpp_deallocate(p,nullptr)
    #define YAGLPP_RUNTIME(e,s) if (e) throw std::runtime_error(s)
#elif !defined (_DEBUG)
    #define YAGLPP_INLINE_IMPLEMENTATION
#endif

#include <glm/fwd.hpp>
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

extern const char* yaglpp_delete_str;
extern const char* yaglpp_delete_arr_str;
extern const char* yaglpp_new_str;
extern const char* yaglpp_new_arr_str;
void yaglpp_atexit_handler() noexcept;
std::size_t yaglpp_block_size(void* block, void* user);
_Ret_notnull_ void* yaglpp_allocate(std::size_t size, void* user);
_Ret_notnull_ void* yaglpp_callocate(std::size_t size, void* user);
void yaglpp_deallocate(void* block, void* user);
_Ret_notnull_ FILE* yaglpp_load_file(const char* file);
_Ret_notnull_ unsigned char* yaglpp_load_file(const char* file, int* size, void* user);
_Ret_maybenull_ void* yaglpp_reallocate(void* block, std::size_t size, void* user);
void yaglpp_write_file(const char* file, const void* data, int size);

#ifdef YAGLPP_MSVC
    _Ret_notnull_ unsigned char* yaglpp_load_resource(int rcid, unsigned int* size);
#endif

#ifdef YAGLPP_GLOBAL_ALLOCATOR
    #ifdef YAGLPP_MSVC
        #pragma warning(push)
        #pragma warning(disable : 28252 28301)
    #endif
    _Ret_notnull_ void* operator new(std::size_t size);
    _Ret_notnull_ void* operator new[](std::size_t size);
    void operator delete(_In_opt_ void* ptr) noexcept;
    void operator delete[](_In_opt_ void* ptr) noexcept;
    #ifdef YAGLPP_MSVC
        #pragma warning(pop)
    #endif
#endif

class DataStore;
class StbImage;

/*YAGL++ helper function, deallocates the memory block previously allocated by the YAGL++ library
@param [in] The pointer to the memory block being freed*/
inline void FreeMemory(_In_opt_ void* block)
{
    yaglpp_deallocate(block, nullptr);
}

#include <yaglpp/data_store.h>
#include <yaglpp/stb_image.h>
#include <yaglpp/gladpp.h>

#ifdef YAGLPP_GLFW
    #include <yaglpp/glfw3pp.h>
#endif

#ifdef YAGLPP_GLM_HEADERS
    #include <glm/glm.hpp>
    #include <glm/ext.hpp>
#endif

#ifdef YAGLPP_ASSIMP
    #include <assimp/Importer.hpp>
    #include <assimp/cimport.h>
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
#endif

#ifdef YAGLPP_IMPLEMENTATION
static std::atomic<std::size_t> yaglpp_alloc_size{0};
const char* yaglpp_new_str = "YAGL++: improper use of object's new operator";
const char* yaglpp_new_arr_str = "YAGL++: improper use of object's new[] operator";
const char* yaglpp_delete_str = "YAGL++: improper use of object's delete operator";
const char* yaglpp_delete_arr_str = "YAGL++: improper use of object's delete[] operator";
_Ret_notnull_ void* yaglpp_allocate(std::size_t size, void* user)
{
    std::size_t iSize = size + (std::size_t)user + sizeof(std::size_t);
    void* pNew = std::malloc(iSize);

    // UNINITIALIZED MEMORY ALLOCATION FAILED
    YAGLPP_RUNTIME(!pNew, "YAGL++: uninitialized memory allocation failed");

    *((std::size_t*)pNew) = iSize;
    yaglpp_alloc_size.fetch_add(iSize);
    void* pReturn = (char*)pNew + (std::size_t)user + sizeof(std::size_t);
    return pReturn;
}

void yaglpp_atexit_handler() noexcept
{
    std::size_t iSize = yaglpp_alloc_size.load();
    if (iSize > 0)
    {
#ifdef _DEBUG
        std::cout << "YAGL++ memory leak detected: " << iSize << " bytes" << std::endl;
#endif // #ifdef _DEBUG

        // MEMORY LEAK DETECTED
        YAGLPP_ASSERT(0);
    }
}

std::size_t yaglpp_block_size(void* block, void* user)
{
    void* pOld = (char*)block - (std::size_t)user - sizeof(std::size_t);
    return *((std::size_t*)pOld);
}

_Ret_notnull_ void* yaglpp_callocate(std::size_t size, void* user)
{
    std::size_t iSize = size + (std::size_t)user + sizeof(std::size_t);
    void* pNew = std::calloc(iSize, 1);

    // INITIALIZED MEMORY ALLOCATION FAILED
    YAGLPP_RUNTIME(!pNew, "YAGL++: initialized memory allocation failed");

    *((std::size_t*)pNew) = iSize;
    yaglpp_alloc_size.fetch_add(iSize);
    void* pReturn = (char*)pNew + (std::size_t)user + sizeof(std::size_t);
    return pReturn;
}

void yaglpp_deallocate(void* block, void* user)
{
    if (block != nullptr)
    {
        void* pOld = (char*)block - (std::size_t)user - sizeof(std::size_t);
        std::size_t iSize = *((std::size_t*)pOld);
        yaglpp_alloc_size.fetch_sub(iSize);
        free(pOld);
    }
}

_Ret_notnull_ FILE* yaglpp_load_file(const char* file)
{
    // FILE PARAMETER COULD NOT BE NULL
    YAGLPP_ASSERT(file);

#ifdef YAGLPP_MSVC
    FILE* hFile;
    fopen_s(&hFile, file, "rb");
#else
    std::FILE* hFile = std::fopen(file, "rb");
#endif

    // FAILED TO READ FROM FILE
    YAGLPP_RUNTIME(!hFile, "YAGL++: failed to read from file");

    return hFile;
}

_Ret_notnull_ unsigned char* yaglpp_load_file(const char* file, int* size, void* user)
{
    std::FILE* hFile = yaglpp_load_file(file);
    std::fseek(hFile, 0, SEEK_END);
    *size = std::ftell(hFile);
    std::fseek(hFile, 0, SEEK_SET);

    unsigned char* pData = (unsigned char*)yaglpp_allocate(*size, user);
    std::fread(pData, 1, *size, hFile);
    std::fclose(hFile);
    return pData;
}

_Ret_maybenull_ void* yaglpp_reallocate(void* block, std::size_t size, void* user)
{
    if (block == nullptr)
    {
        return yaglpp_allocate(size, user);
    }
    else if (size == 0)
    {
        yaglpp_deallocate(block, user);
        return nullptr;
    }
    void* pOld = (char*)block - (std::size_t)user - sizeof(std::size_t);
    std::size_t iSize = *((std::size_t*)pOld);
    yaglpp_alloc_size.fetch_sub(iSize);
    iSize = size + (std::size_t)user + sizeof(std::size_t);
    void* pNew = std::realloc(pOld, iSize);

    // MEMORY REALLOCATION FAILED
    YAGLPP_RUNTIME(!pNew, "YAGL++: memory reallocation failed");

    *((std::size_t*)pNew) = iSize;
    yaglpp_alloc_size.fetch_add(iSize);
    void* pReturn = (char*)pNew + (std::size_t)user + sizeof(std::size_t);
    return pReturn;
}

void yaglpp_write_file(const char* file, const void* data, int size)
{
    // FILE PARAMETER COULD NOT BE NULL
    YAGLPP_ASSERT(file);

#ifdef YAGLPP_MSVC
    FILE* hFile;
    fopen_s(&hFile, file, "wb");
#else
    std::FILE* hFile = std::fopen(file, "wb");
#endif

    // FAILED TO WRITE INTO FILE
    YAGLPP_RUNTIME(!hFile, "YAGL++: failed to write into file");

    std::fwrite(data, 1, size, hFile);
    std::fclose(hFile);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_GLOBAL_ALLOCATOR)
#ifdef YAGLPP_MSVC
    #pragma warning(push)
    #pragma warning(disable : 28252 28301)
#endif
_Ret_notnull_ void* operator new(std::size_t size)
{
    return yaglpp_allocate(size, nullptr);
}

_Ret_notnull_ void* operator new[](std::size_t size)
{
    return yaglpp_allocate(size, nullptr);
}

void operator delete(_In_opt_ void* ptr) noexcept
{
    yaglpp_deallocate(ptr, nullptr);
}

void operator delete[](_In_opt_ void* ptr) noexcept
{
    yaglpp_deallocate(ptr, nullptr);
}
#ifdef YAGLPP_MSVC
    #pragma warning(pop)
#endif
#endif // #if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_GLOBAL_ALLOCATOR)

#if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_MSVC)
#ifndef _WINDOWS_
    #undef APIENTRY
    #include <Windows.h>
#endif
_Ret_notnull_ unsigned char* yaglpp_load_resource(int rcid, unsigned int* size)
{
    static HMODULE hModule = GetModuleHandleA(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(rcid), RT_RCDATA);

    // FAILED TO FIND APPLICATION RESOURCE
    YAGLPP_RUNTIME(!hResource, "YAGL++: failed to find application resource");

    *size = SizeofResource(hModule, hResource);
    HGLOBAL hMemory = LoadResource(hModule, hResource);

    // FAILED TO LOAD APPLICATION RESOURCE
    YAGLPP_RUNTIME(!hMemory, "YAGL++: failed to load application resource");

    return (unsigned char*)LockResource(hMemory);
}
#endif // #if defined (YAGLPP_IMPLEMENTATION) && defined (YAGLPP_MSVC)
#endif // #ifndef YAGLPP_GLPP_H
