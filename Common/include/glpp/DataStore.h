#pragma once
#include "glpp.h"
/*glpp data store helper root class*/
class DataStore
{
private:
	typedef struct {
		int size;		// Memory block size
#pragma warning(push)
#pragma warning(disable : 4200)
		char data[0];	// Zero data array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA m_lpData;	// Class data

public:
	/*(1) Construct an empty data store object*/
	DataStore()
	{
		m_lpData = nullptr;
	}

	/*(2) Construct data store object with <createDataStore>*/
	DataStore(int size, bool init = false)
	{
		m_lpData = nullptr;
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

	/*Creates a memory block in the empty DataStore object
	@param The memory block size in bytes
	@param True to initialize the memory block with zeros, false otherwise (default)*/
	void createDataStore(int size, bool init = false);

	/*Deletes a memory block in the non-empty DataStore object*/
	void deleteDataStore();

	/*Checks if data store object has memory block
	@param True if object has memory block, false otherwise*/
	bool isDataStore()
	{
		return m_lpData != nullptr;
	}

	/*Returns the pointer to allocated data
	@param The requested memory block size in bytes, default 0 which means no limit, ignored in release build
	@return The pointer to memory block*/
	void* getData(int length = 0);

	/*Returns the pointer to the whole or a part of allocated data
	@param The starting byte offset of the requested memory block
	@param The requested memory block size in bytes, default 0 which means no limit, ignored in release build
	@return The pointer to memory block*/
	void* getSubData(int start, int length = 0);

	/*Returns a memory block size of non-empty data store object
	@return The memory block size in bytes*/
	int getSize();
}; // class DataStore

#ifndef _DEBUG
inline void* DataStore::getData(int length)
{
	return &m_lpData->data[0];
}

inline void* DataStore::getSubData(int start, int length)
{
	return &m_lpData->data[start];
}

inline int DataStore::getSize()
{
	return m_lpData->size;
}
#endif // #ifndef _DEBUG
