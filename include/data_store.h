#pragma once
#include <yaglpp/glpp.h>
/*YAGL++ data store helper root class*/
class DataStore
{
private:
	typedef struct {
		int ref; // Ref count
		int size; // Block size
#pragma warning(push)
#pragma warning(disable : 4200)
		char data[0]; // Zero array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA _mpData = nullptr; // Class data

public:
	/*(1) Constructs an empty data store object*/
	DataStore() {}

	/*(2) Constructs a duplicate of data store object*/
	DataStore(const DataStore& source)
	{
		duplicateData(source);
	}

	/*(3) Construct data store object with <loadData>*/
	DataStore(int rcid)
	{
		loadData(rcid);
	}

	/*(4) Construct data store object with <loadData>*/
	DataStore(_In_z_ const char* file)
	{
		loadData(file);
	}

	/*(5) Construct data store object with <createData>*/
	DataStore(int size, bool init)
	{
		createData(size, init);
	}

	/*(6) Construct data store object with <loadSubData>*/
	DataStore(const DataStore& source, int start, int length)
	{
		loadSubData(source, start, length);
	}

	/*Cleans up the valid data store object*/
	~DataStore()
	{
		deleteData();
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
	void createData(int size, bool init = false);

	/*Deletes the last inctance of a memory block, or decrements its reference count*/
	void deleteData();

	/*Creates a reference to the source memory block, and increments its reference count
	@param The source data store object*/
	void duplicateData(const DataStore& source);

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
	void* getSubData(int start, int length = 0) const;

	/*Returns memory block size of the valid data store object. Used as a getter of <size> property
	@return The memory block size in bytes*/
	int getSize() const;

	/*Checks if data store object has memory block. Used as a getter of <data> property
	@param True if object has memory block, false otherwise*/
	bool isData() const
	{
		return _mpData != nullptr;
	}

	/*Checks if the source object is referencing the same memory block
	@param The source data store object
	@return True if duplicate object*/
	bool isDuplicate(const DataStore& source) const
	{
		return (_mpData != nullptr) && (_mpData == source._mpData);
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
		loadSubData(source, 0, source.getSize());
	}

	/*Loads the whole or a part of the source DataStore object into empty DataStore object
	@param [in] Path to the source file
	@param The starting byte offset in source memory block
	@param The memory block size in bytes, must be greater then 0*/
	void loadSubData(const DataStore& source, int start, int length);

	/*Writes the whole memory block into file
	@param [in] Path to the destination file*/
	void writeData(_In_z_ const char* file) const
	{
		writeSubData(file, 0, getSize());
	}

	/*Writes the whole or a part of memory block into file
	@param The starting byte offset in memory block
	@param The memory block size in bytes, must be greater then 0*/
	void writeSubData(_In_z_ const char* file, int start, int length) const;

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if data store object has memory block*/
	__declspec(property(get = isData)) bool data;

	/*Read-only property for memory block size of the valid data store object*/
	__declspec(property(get = getSize)) int size;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class DataStore

#ifdef YAGLPP_IMPLEMENTATION
void DataStore::createData(int size, bool init)
{
	YAGLPP_ASSERT(size > 0); // SIZE MUST BE GREATER THAN ZERO
	deleteData();
	int iSize = size + sizeof(_DATA);
	if (init)
	{
		_mpData = (_LPDATA)_callocate(iSize, nullptr);
	}
	else
	{
		_mpData = (_LPDATA)_allocate(iSize, nullptr);
		_mpData->ref = 0;
	}
	_mpData->size = size;
}

void DataStore::deleteData()
{
	if (_mpData != nullptr)
	{
		if (_mpData->ref == 0)
		{
			_deallocate(_mpData, nullptr);
		}
		else _mpData->ref--;
		_mpData = nullptr;
	}
}

void DataStore::duplicateData(const DataStore& source)
{
	if (&source != this)
	{
		deleteData();
		_mpData = source._mpData;
		if (_mpData != nullptr)
		{
			_mpData->ref++;
		}
	}
}

void DataStore::loadData(int rcid)
{
	int iSize;
	deleteData();
	LPBYTE lpData = (LPBYTE)yaglpp_loadResource(rcid, &iSize);
	_mpData = (_LPDATA)_allocate(iSize + sizeof(_DATA), nullptr);
	_mpData->ref = 0;
	_mpData->size = iSize;
	memcpy(&_mpData->data[0], lpData, iSize);
}

void DataStore::loadData(_In_z_ const char* file)
{
	int iSize;
	deleteData();
	_mpData = (_LPDATA)_loadFile(file, &iSize, (void*)sizeof(_DATA)) - 1;
	_mpData->ref = 0;
	_mpData->size = iSize;
}

void DataStore::loadSubData(const DataStore& source, int start, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	if (&source != this)
	{
		deleteData();
		_mpData = (_LPDATA)_allocate(length + sizeof(_DATA), nullptr);
		_mpData->ref = 0;
		_mpData->size = length;
		memcpy(&_mpData->data[0], source.getSubData(start, length), length);
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	memcpy(getSubData(startDst, length), source.getSubData(startSrc, length), length);
}

void* DataStore::getSubData(int start, int length) const
{
	YAGLPP_ASSERT(getSize() >= start + length); // REQUESTED MEMORY SUB BLOCK IS TOO BIG
	return &_mpData->data[start];
}

int DataStore::getSize() const
{
	YAGLPP_ASSERT(isData()); // DATA STORE OBJECT IS EMPTY
	return _mpData->size;
}

void DataStore::writeSubData(_In_z_ const char* file, int start, int length) const
{
	YAGLPP_ASSERT(length > 0); // MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	yaglpp_writeFile(file, getSubData(start, length), length);
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline void DataStore::copySubData(const DataStore& source, int startSrc, int startDst, int length)
{
	memcpy(&_mpData->data[startDst], &source._mpData->data[startSrc], length);
}

inline void* DataStore::getSubData(int start, int length) const
{
	return &_mpData->data[start];
}

inline int DataStore::getSize() const
{
	return _mpData->size;
}

inline void DataStore::writeSubData(_In_z_ const char* file, int start, int length) const
{
	yaglpp_writeFile(file, &_mpData->data[start], length);
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
