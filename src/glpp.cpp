#define GLPP_BUILD_LIB
#include <glpp/glpp.h>
LPBYTE _loadFile(const char* file, int* size)
{
    FILE* pFile;
    errno_t iError = fopen_s(&pFile, file, "rb");
    GLPP_ASSERT(iError == 0); // FAILED TO LOAD FILE
    fseek(pFile, 0, SEEK_END);
    *size = ftell(pFile);
    rewind(pFile);
    LPBYTE lpData = (LPBYTE)GLPP_MALLOC(*size);
    fread(lpData, 1, *size, pFile);
    fclose(pFile);
    return lpData;
}

LPBYTE _loadResource(int rcid, int* size)
{
    static HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(rcid), RT_RCDATA);
    GLPP_ASSERT(hResource != NULL); // FAILED TO FIND RESOURCE ID
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    GLPP_ASSERT(hMemory != NULL); // FAILED TO LOAD RESOURCE ID
    *size = SizeofResource(hModule, hResource);
    return (LPBYTE)LockResource(hMemory);
}

bool fileExists(_In_z_ const char* file)
{
    struct stat buffer;
    return stat(file, &buffer) == 0;
}

#ifdef _DEBUG
_Ret_notnull_ void* _assertCalloc(size_t size)
{
    void* pNew = calloc(size, 1);
    GLPP_ASSERT(pNew); // FAILED TO ALLOCATE ZEROED MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertMalloc(size_t size)
{
    void* pNew = malloc(size);
    GLPP_ASSERT(pNew); // FAILED TO ALLOCATE RAW MEMORY
    return pNew;
}

_Ret_notnull_ void* _assertRealloc(void* ptr, size_t size)
{
    void* pNew = realloc(ptr, size);
    GLPP_ASSERT(pNew); // FAILED TO REALLOCATE MEMORY
    return pNew;
}

void _clock(const char* zCode)
{
    static LARGE_INTEGER liClock = { 0,0 };
    LARGE_INTEGER liElapsed;
    QueryPerformanceCounter(&liElapsed);
    if (zCode)
    {
        LONGLONG lDiff = liElapsed.QuadPart - liClock.QuadPart;
        std::cout << "CODE BLOCK <" << zCode << "> ELAPSED IN: " << lDiff << " CPU CLOCKS" << std::endl;
    }
    QueryPerformanceCounter(&liClock);
}
#endif // #ifdef _DEBUG
