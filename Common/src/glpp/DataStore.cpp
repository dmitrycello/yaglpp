#define GLPP_BUILD_LIB
#include <glpp/DataStore.h>
void DataStore::createDataStore(int size, bool init)
{
	GLPP_ASSERT(m_lpData == nullptr); // DATA STORE OBJECT IS NOT EMPTY
	GLPP_ASSERT(size > 0); // SIZE MUST BE GREATER THAN ZERO
	m_lpData = (init) ? (_LPDATA)GLPP_CALLOC(sizeof(_DATA) + size) : (_LPDATA)GLPP_MALLOC(sizeof(_DATA) + size);
	if (m_lpData)
	{
		m_lpData->size = size;
	}
}

void DataStore::deleteDataStore()
{
	GLPP_ASSERT(m_lpData != nullptr); // DATA STORE OBJECT IS EMPTY
	GLPP_FREE(m_lpData);
	m_lpData = nullptr;
}

#ifdef _DEBUG
void* DataStore::getData(int length)
{
	GLPP_ASSERT(getSize() >= length); // REQUESTED MEMORY BLOCK IS TOO BIG
	return &m_lpData->data[0];
}

void* DataStore::getSubData(int start, int length)
{
	GLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	return &m_lpData->data[start];
}

int DataStore::getSize()
{
	GLPP_ASSERT(m_lpData != nullptr); // DATA STORE OBJECT IS EMPTY
	return m_lpData->size;
}
#endif // #ifdef _DEBUG
