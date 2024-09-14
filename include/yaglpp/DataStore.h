#pragma once
#include <yaglpp.h>
/*YAGL++ data store helper root class*/
class DataStore
{
private:
	int m_iSize = 0;
	LPBYTE _mpData = nullptr;

public:
	/*(1) Construct an empty data store object*/
	DataStore() {}

	/*(2) Construct data store object with <loadData>*/
	DataStore(int rcid)
	{
		loadData(rcid);
	}

	/*(3) Construct data store object with <loadData>*/
	DataStore(_In_z_ const char* file)
	{
		loadData(file);
	}

	/*(4) Construct data store object with <loadData>*/
	DataStore(const DataStore& source)
	{
		loadData(source);
	}

	/*(5) Construct data store object with <loadSubData>*/
	DataStore(const DataStore& source, int start, int length)
	{
		loadSubData(source, start, length);
	}

	/*(6) Construct data store object with <createDataStore>*/
	DataStore(int size, bool init)
	{
		createDataStore(size, init);
	}

	/*Cleans up the valid data store object*/
	~DataStore()
	{
		if (isDataStore())
		{
			deleteDataStore();
		}
	}

	/*Copies the whole or a part of the source DataStore object into the whole or a part of valid DataStore object
	@param [in] Path to the source file
	@param The starting byte offset in source memory block
	@param The starting byte offset in destination memory block
	@param The memory block size in bytes, must be greater then 0*/
	void copySubData(const DataStore& source, int startSrc, int startDst, int length);

	/*Creates memory block in the empty DataStore object
	@param The memory block size in bytes
	@param True to initialize the memory block with zeros, false otherwise (default)*/
	void createDataStore(int size, bool init = false);

	/*Deletes memory block in the valid DataStore object*/
	void deleteDataStore();

	/*Returns the pointer to memory block
	@param The requested memory block size in bytes, default 0 means no limit, ignored in release build
	@return The pointer to memory block*/
	void* getData(int length = 0)
	{
		return getSubData(0, length);
	}

	/*Returns the pointer to the whole or a part of memory block
	@param The starting byte offset of the requested memory block
	@param The requested memory block size in bytes, default 0 means no limit, ignored in release build
	@return The pointer to memory block*/
	void* getSubData(int start, int length = 0);

	/*Returns memory block size of the valid data store object. Used as a getter of <size> property
	@return The memory block size in bytes*/
	int getSize() const;

	/*Checks if data store object has memory block. Used as a getter of <dataStore> property
	@param True if object has memory block, false otherwise*/
	bool isDataStore() const
	{
		return _mpData != nullptr;
	}

	/*(1) Loads memory block from binary resource into empty DataStore object
	@param The data resource id of <RCDATA> type*/
	void loadData(int rcid);

	/*(2) Loads memory block from file into empty DataStore object
	@param [in] Path to the source file*/
	void loadData(_In_z_ const char* file);
	
	/*(3) Loads memory block from the source DataStore object into empty DataStore object
	@param [in] Path to the source file*/
	void loadData(const DataStore& source)
	{
		loadSubData(source, 0, source.m_iSize);
	}

	/*Loads the whole or a part of the source DataStore object into empty DataStore object
	@param [in] Path to the source file
	@param The starting byte offset in source memory block
	@param The memory block size in bytes, must be greater then 0*/
	void loadSubData(const DataStore& source, int start, int length);

	/*Writes memory block into file
	@param [in] Path to the destination file*/
	void writeData(_In_z_ const char* file)
	{
		writeSubData(file, 0, m_iSize);
	}

	/*Writes the whole or a part of memory block into file
	@param The starting byte offset in memory block
	@param The memory block size in bytes, must be greater then 0*/
	void writeSubData(_In_z_ const char* file, int start, int length);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if data store object has memory block*/
	__declspec(property(get = isDataStore)) bool dataStore;

	/*Read-only property for memory block size of the valid data store object*/
	__declspec(property(get = getSize)) int size;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class DataStore

#ifdef YAGLPP_IMPLEMENTATION
void DataStore::createDataStore(int size, bool init)
{
	YAGLPP_ASSERT(!isDataStore()); // DATA STORE OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(size > 0); // SIZE MUST BE GREATER THAN ZERO
	_mpData = (init) ? (LPBYTE)YAGLPP_CALLOC(size) : (LPBYTE)YAGLPP_MALLOC(size);
	m_iSize = size;
}

void DataStore::loadData(int rcid)
{
	YAGLPP_ASSERT(!isDataStore()); // DATA STORE OBJECT IS NOT EMPTY
	LPBYTE lpData = _loadResource(rcid, &m_iSize);
	_mpData = (LPBYTE)YAGLPP_MALLOC(m_iSize);
	memcpy(_mpData, lpData, m_iSize);
}

void DataStore::loadSubData(const DataStore& source, int start, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(!isDataStore()); // DATA STORE OBJECT IS NOT EMPTY
	YAGLPP_ASSERT(source.getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	m_iSize = length;
	_mpData = (LPBYTE)YAGLPP_MALLOC(m_iSize);
	memcpy(_mpData, &source._mpData[start], m_iSize);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(source.getSize() >= startSrc + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	YAGLPP_ASSERT(getSize() >= startDst + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	memcpy(&_mpData[startDst], &source._mpData[startSrc], length);
}

void DataStore::deleteDataStore()
{
	YAGLPP_ASSERT(isDataStore()); // DATA STORE OBJECT IS EMPTY
	YAGLPP_FREE(_mpData);
	_mpData = nullptr; m_iSize = 0;
}

void* DataStore::getSubData(int start, int length)
{
	YAGLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	return &_mpData[start];
}

int DataStore::getSize() const
{
	YAGLPP_ASSERT(isDataStore()); // DATA STORE OBJECT IS EMPTY
	return m_iSize;
}

void DataStore::loadData(_In_z_ const char* file)
{
	YAGLPP_ASSERT(!isDataStore()); // DATA STORE OBJECT IS NOT EMPTY
	_mpData = _loadFile(file, &m_iSize);
}

void DataStore::writeSubData(_In_z_ const char* file, int start, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	_writeFile(file, &_mpData[start], length);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	memcpy(&_mpData[startDst], &source._mpData[startSrc], length);
}

inline void DataStore::deleteDataStore()
{
	_mpData = nullptr; m_iSize = 0;
}

inline void* DataStore::getSubData(int start, int length)
{
	return &_mpData[start];
}

inline int DataStore::getSize() const
{
	return m_iSize;
}

inline void DataStore::loadData(_In_z_ const char* file)
{
	_mpData = _loadFile(file, &m_iSize);
}

inline void DataStore::writeSubData(_In_z_ const char* file, int start, int length)
{
	_writeFile(file, &_mpData[start], length);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
