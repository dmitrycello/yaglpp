#pragma once
#include "yaglpp.h"
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
		if (isData())
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

	/*Returns memory block size of the valid data store object
	@return The memory block size in bytes*/
	int getSize() const;

	/*Checks if data store object has memory block
	@param True if object has memory block, false otherwise*/
	bool isData() const
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
}; // class DataStore

#ifndef _DEBUG
inline void* DataStore::getSubData(int start, int length)
{
	return &_mpData[start];
}

inline int DataStore::getSize() const
{
	return m_iSize;
}
#endif // #ifndef _DEBUG
