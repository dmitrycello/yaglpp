#define YAGLPP_BUILD_LIB
#include <yaglpp/yaglpp.h>
char* _copyString(const char* source)
{
    if (source == nullptr) return nullptr;
    size_t iLen = strlen(source);
    char* pBuffer = (char*)_YAGLPP_MALLOC_(iLen);
    errno_t iError = strcpy_s(pBuffer, iLen, source);
    _YAGLPP_ASSERT_(iError == 0); // FAILED TO COPY STRING
    return pBuffer;
}

LPBYTE _loadFile(const char* file, int* size)
{
    FILE* pFile;
    _YAGLPP_ASSERT_(file != nullptr); // FILE PARAMETER COULD NOT BE NULL
    errno_t iError = fopen_s(&pFile, file, "rb");
    _YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD FILE
    fseek(pFile, 0, SEEK_END);
    *size = ftell(pFile);
    rewind(pFile);
    LPBYTE lpData = (LPBYTE)_YAGLPP_MALLOC_(*size);
    fread(lpData, 1, *size, pFile);
    fclose(pFile);
    return lpData;
}

LPBYTE _loadResource(int rcid, int* size)
{
    static HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(rcid), RT_RCDATA);
    _YAGLPP_ASSERT_(hResource != NULL); // FAILED TO FIND RESOURCE ID
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    _YAGLPP_ASSERT_(hMemory != NULL); // FAILED TO LOAD RESOURCE ID
    *size = SizeofResource(hModule, hResource);
    return (LPBYTE)LockResource(hMemory);
}

void _writeFile(_In_z_ const char* file, const void* data, int size)
{
    FILE* pFile;
    _YAGLPP_ASSERT_(file != nullptr); // FILE PARAMETER COULD NOT BE NULL
    errno_t iError = fopen_s(&pFile, file, "wb");
    _YAGLPP_ASSERT_(iError == 0); // FAILED TO WRITE FILE
    fwrite(data, 1, size, pFile);
    fclose(pFile);
}

_Ret_maybenull_ char* copyString(_In_opt_z_ const char* source)
{
    if (source == nullptr) return nullptr;
    size_t iLen = strlen(source);
    char* pBuffer = (char*)_YAGLPP_MALLOC_(iLen);
    errno_t iError = strcpy_s(pBuffer, iLen, source);
    _YAGLPP_ASSERT_(iError == 0); // FAILED TO COPY STRING
    return pBuffer;
}

bool fileExists(_In_z_ const char* file)
{
    struct stat buffer;
    return stat(file, &buffer) == 0;
}

void freeMemory(_In_ void* block)
{
    _YAGLPP_FREE_(block);
}

#ifdef _DEBUG
_Ret_notnull_ void* _assertCalloc(size_t size)
{
    void* pNew = calloc(size, 1);
    _YAGLPP_ASSERT_(pNew); // FAILED TO ALLOCATE ZEROED MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertMalloc(size_t size)
{
    void* pNew = malloc(size);
    _YAGLPP_ASSERT_(pNew); // FAILED TO ALLOCATE RAW MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertRealloc(void* ptr, size_t size)
{
    void* pNew = realloc(ptr, size);
    _YAGLPP_ASSERT_(pNew); // FAILED TO REALLOCATE MEMORY
    return pNew;
}
#endif // #ifdef _DEBUG
