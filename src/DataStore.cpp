#define YAGLPP_BUILD_LIB
#include <yaglpp/DataStore.h>
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
extern void _writeFile(const char*, const void*, int);
void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(source.getSize() >= startSrc + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	YAGLPP_ASSERT(getSize() >= startDst + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	memcpy(&m_lpData[startDst], &source.m_lpData[startSrc], length);
}

void DataStore::createDataStore(int size, bool init)
{
	YAGLPP_ASSERT(m_lpData == nullptr); // DATA STORE OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(size > 0); // SIZE MUST BE GREATER THAN ZERO
	m_lpData = (init) ? (LPBYTE)YAGLPP_CALLOC(size) : (LPBYTE)YAGLPP_MALLOC(size);
	m_iSize = size;
}

void DataStore::deleteDataStore()
{
	YAGLPP_ASSERT(m_lpData != nullptr); // DATA STORE OBJECT IS EMPTY
	YAGLPP_FREE(m_lpData);
	m_lpData = nullptr;
	m_iSize = 0;
}

void DataStore::loadData(int rcid)
{
	YAGLPP_ASSERT(m_lpData == nullptr); // DATA STORE OBJECT IS NOT EMPTY
	LPBYTE lpData = _loadResource(rcid, &m_iSize);
	m_lpData = (LPBYTE)YAGLPP_MALLOC(m_iSize);
	memcpy(m_lpData, lpData, m_iSize);
}

void DataStore::loadData(_In_z_ const char* file)
{
	YAGLPP_ASSERT(m_lpData == nullptr); // DATA STORE OBJECT IS NOT EMPTY
	m_lpData = _loadFile(file, &m_iSize);
}

void DataStore::loadSubData(const DataStore& source, int start, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(m_lpData == nullptr); // DESTINATION DATA STORE OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(source.getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	m_iSize = length;
	m_lpData = (LPBYTE)YAGLPP_MALLOC(m_iSize);
	memcpy(m_lpData, &source.m_lpData[start], m_iSize);
}

void DataStore::writeSubData(_In_z_ const char* file, int start, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	_writeFile(file, &m_lpData[start], length);
}

#ifdef _DEBUG
void* DataStore::getSubData(int start, int length)
{
	YAGLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	return &m_lpData[start];
}

int DataStore::getSize() const
{
	YAGLPP_ASSERT(isDataStore()); // DATA STORE OBJECT IS EMPTY
	return m_iSize;
}
#endif // #ifdef _DEBUG
