#define YAGLPP_BUILD_LIB
#include <yaglpp/yaglpp.h>
LPBYTE _loadFile(const char* file, int* size)
{
    FILE* pFile;
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

void _writeFile(_In_z_ const char* file, const void* data, int size)
{
    FILE* pFile;
    errno_t iError = fopen_s(&pFile, file, "wb");
    YAGLPP_ASSERT(iError == 0); // FAILED TO WRITE FILE
    fwrite(data, 1, size, pFile);
    fclose(pFile);
}

bool fileExists(_In_z_ const char* file)
{
    struct stat buffer;
    return stat(file, &buffer) == 0;
}

void freeMemory(_In_ void* block)
{
    YAGLPP_FREE(block);
}

#ifdef _DEBUG
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
#endif // #ifdef _DEBUG
