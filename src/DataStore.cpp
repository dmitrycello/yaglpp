#define YAGLPP_BUILD_LIB
#include <yaglpp/DataStore.h>
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
extern void _writeFile(const char*, const void*, int);
void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	_YAGLPP_ASSERT_(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	_YAGLPP_ASSERT_(source.getSize() >= startSrc + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	_YAGLPP_ASSERT_(getSize() >= startDst + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	memcpy(&m_lpData[startDst], &source.m_lpData[startSrc], length);
}

void DataStore::createDataStore(int size, bool init)
{
	_YAGLPP_ASSERT_(!isData()); // DATA STORE OBJECT IS NOT EMPTY
	_YAGLPP_ASSERT_(size > 0); // SIZE MUST BE GREATER THAN ZERO
	m_lpData = (init) ? (LPBYTE)_YAGLPP_CALLOC_(size) : (LPBYTE)_YAGLPP_MALLOC_(size);
	m_iSize = size;
}

void DataStore::deleteDataStore()
{
	_YAGLPP_ASSERT_(isData()); // DATA STORE OBJECT IS EMPTY
	_YAGLPP_FREE_(m_lpData);
	m_lpData = nullptr;
	m_iSize = 0;
}

void DataStore::loadData(int rcid)
{
	_YAGLPP_ASSERT_(!isData()); // DATA STORE OBJECT IS NOT EMPTY
	LPBYTE lpData = _loadResource(rcid, &m_iSize);
	m_lpData = (LPBYTE)_YAGLPP_MALLOC_(m_iSize);
	memcpy(m_lpData, lpData, m_iSize);
}

void DataStore::loadData(_In_z_ const char* file)
{
	_YAGLPP_ASSERT_(!isData()); // DATA STORE OBJECT IS NOT EMPTY
	m_lpData = _loadFile(file, &m_iSize);
}

void DataStore::loadSubData(const DataStore& source, int start, int length)
{
	_YAGLPP_ASSERT_(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	_YAGLPP_ASSERT_(!isData()); // DATA STORE OBJECT IS NOT EMPTY
	_YAGLPP_ASSERT_(source.getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	m_iSize = length;
	m_lpData = (LPBYTE)_YAGLPP_MALLOC_(m_iSize);
	memcpy(m_lpData, &source.m_lpData[start], m_iSize);
}

void DataStore::writeSubData(_In_z_ const char* file, int start, int length)
{
	_YAGLPP_ASSERT_(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	_YAGLPP_ASSERT_(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	_writeFile(file, &m_lpData[start], length);
}

#ifdef _DEBUG
void* DataStore::getSubData(int start, int length)
{
	_YAGLPP_ASSERT_(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	return &m_lpData[start];
}

int DataStore::getSize() const
{
	_YAGLPP_ASSERT_(isData()); // DATA STORE OBJECT IS EMPTY
	return m_iSize;
}
#endif // #ifdef _DEBUG
