#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_DATA_STORE_H
#define YAGLPP_DATA_STORE_H

/*YAGL++ data store helper root class*/
class DataStore
{
public:
	/*(1) Constructs an empty data store object*/
	DataStore()
	{
		m_Size = 0; m_Data = nullptr;
	}

	/*(2) Constructs a copy of data store object with <Copy>*/
	DataStore(const DataStore& source) : DataStore()
	{
		Copy(source);
	}

	/*(3) Construct a new data store object with <Create>*/
	DataStore(int size, bool init) : DataStore()
	{
		Create(size, init);
	}

	/*(4) Construct a copy of data store object with <CopyRegion>*/
	DataStore(const DataStore& source, int start, int length) : DataStore()
	{
		CopyRegion(source, start, length);
	}

	/*(4) Construct data store object with <LoadFromFile>*/
	DataStore(_In_z_ const char* file) : DataStore()
	{
		LoadFromFile(file);
	}

	/*(5) Construct data store object with <LoadFromMemory>*/
	DataStore(_In_ unsigned char* data, unsigned int size) : DataStore()
	{
		LoadFromMemory(data, size);
	}

	/*Cleans up the valid data store object*/
	~DataStore()
	{
		Delete();
	}

	/*Blits the entire source memory block into a sub-block of the destination memory block. Does nothing if empty source object. Acts as <Copy> if empty destination object
	@param [in] The source data store object
	@param The starting byte offset in destination memory block
	@param The memory sub-block size in bytes, must be greater then 0*/
	void Blit(const DataStore& source, int start, int length)
	{
		BlitRegion(source, 0, start, length);
	}

	/*Blits a sub-block of the source memory block into a sub-block of the destination memory block. Does nothing if empty source object. Acts as <CopyRegion> if empty destination object
	@param [in] The source data store object
	@param The starting byte offset in source memory block
	@param The starting byte offset in destination memory block
	@param The memory sub-block size in bytes, must be greater then 0*/
	void BlitRegion(const DataStore& source, int startSrc, int startDst, int length);

	/*Copies the entire source memory block into a new destination memory block
	@param [in] The source data store object*/
	void Copy(const DataStore& source)
	{
		CopyRegion(source, 0, source.GetSize());
	}

	/*Copies a sub-block of the source memory block into a new destination memory block
	@param [in] The source data store object
	@param The starting byte offset in source memory block
	@param The starting byte offset in destination memory block
	@param The memory sub-block size in bytes, must be greater then 0*/
	void CopyRegion(const DataStore& source, int start, int length);

	/*Creates memory block in the empty DataStore object
	@param The memory block size in bytes
	@param True to initialize the memory block with zeros, false otherwise (default)*/
	void Create(int size, bool init = false);

	/*Frees and re-initialize the memory block object*/
	void Delete();

	/*Returns the pointer to memory block
	@param The requested memory block size in bytes, default 0 means no verification, ignored in release build
	@return The pointer to memory block*/
	_Ret_notnull_ unsigned char* Get(int length = 0)
	{
		return GetRegion(0, length);
	}

	/*Returns the pointer to the memory sub-block
	@param The starting byte offset of the requested memory block
	@param The requested memory block size in bytes, default 0 means no verification, ignored in release build
	@return The pointer to memory sub-block*/
	_Ret_notnull_ unsigned char* GetRegion(int start, int length = 0) const;

	/*Returns memory block size of the valid data store object. MSVC getter for <size> property
	@return The memory block size in bytes*/
	inline int GetSize() const
	{
		return m_Size;
	}

	/*Checks if data store object has memory block. MSVC getter for <data> property
	@param True if object has memory block, false otherwise*/
	inline bool IsData() const
	{
		return m_Data != nullptr;
	}

	/*(1) Loads memory block from file into empty DataStore object
	@param [in] Path to the source file*/
	void LoadFromFile(_In_z_ const char* file);
	
	/*(2) Loads memory block from memory resource into empty DataStore object
	@param [in] The memory resource data location
	@param The memory resource data size*/
	void LoadFromMemory(_In_ unsigned char* data, unsigned int size);

	/*Resize existing or empty memory block. It can expand or shrink the memory, potentially moving it to a new location while copying existing content
	@param New size of the memory block, or 0 to free memory block*/
	void Resize(int size);

	/*Writes the whole memory block into file
	@param [in] Path to the destination file*/
	void Write(_In_z_ const char* file) const
	{
		WriteRegion(file, 0, GetSize());
	}

	/*Writes the whole or a part of memory block into file
	@param [in] Path to the destination file
	@param The starting byte offset in memory block
	@param The memory block size in bytes, must be greater then 0*/
	void WriteRegion(_In_z_ const char* file, int start, int length) const;

#ifdef YAGLPP_MSVC
	/*(6) Construct data store object with <LoadFromResource>*/
	DataStore(int rcid) : DataStore()
	{
		LoadFromResource(rcid);
	}

	/*(3) Loads memory block from binary resource into empty DataStore object (Windows only)
	@param The binary resource id of <RC_DATA> type*/
	void LoadFromResource(int rcid)
	{
		unsigned int s = 0; LoadFromMemory(yaglpp_load_resource(rcid, &s), s);
	}
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if data store object has memory block*/
	__declspec(property(get = IsData)) bool data;

	/*Read-only property for memory block size of the valid data store object*/
	__declspec(property(get = GetSize)) int size;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

private:
	int m_Size; // Data size
	unsigned char* m_Data; // Data array
}; // class DataStore

#ifdef YAGLPP_IMPLEMENTATION
void DataStore::BlitRegion(const DataStore& source, int startSrc, int startDst, int length)
{
	if (source.m_Data)
	{
		// MEMORY SUB-BLOCK SIZE MUST BE GREATER THAN ZERO
		YAGLPP_ASSERT(length > 0);

		if (m_Data)
		{
			unsigned char
				*pDst = GetRegion(startDst, length),
				*pSrc = source.GetRegion(startSrc, length);
			std::memcpy(pDst, pSrc, length);
		}
		else CopyRegion(source, startSrc, length);
	}
}

void DataStore::CopyRegion(const DataStore& source, int start, int length)
{
	if (&source != this)
	{
		// MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
		YAGLPP_ASSERT(length > 0);

		unsigned char* pSrc = source.GetRegion(start, length);
		Create(length, false);
		std::memcpy(&m_Data[0], pSrc, length);
	}
}

void DataStore::Create(int size, bool init)
{
	// SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(size > 0);

	YAGLPP_FREE(m_Data);
	m_Size = size;
	m_Data = (init) ?
		YAGLPP_CALLOC(unsigned char, size) :
		YAGLPP_MALLOC(unsigned char, size);
}

void DataStore::Delete()
{
	YAGLPP_FREE(m_Data);
	m_Size = 0;
	m_Data = nullptr;
}

void DataStore::LoadFromFile(_In_z_ const char* file)
{
	YAGLPP_FREE(m_Data);
	m_Data = yaglpp_load_file(file, &m_Size, nullptr);
}

void DataStore::LoadFromMemory(_In_ unsigned char* data, unsigned int size)
{
	Create(size, false);
	std::memcpy(&m_Data[0], data, size);
}

void DataStore::Resize(int size)
{
	// SIZE MUST NOT BE NEGATIVE
	YAGLPP_ASSERT(size >= 0);

	m_Size = size;
	m_Data = YAGLPP_REALLOC(unsigned char, m_Data, size);
}

void DataStore::WriteRegion(_In_z_ const char* file, int start, int length) const
{
	// MEMORY SUB BLOCK SIZE MUST BE GREATER THAN ZERO
	YAGLPP_ASSERT(length > 0);

	unsigned char* pData = GetRegion(start, length);
	yaglpp_write_file(file, pData, length);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
_Ret_notnull_ unsigned char* DataStore::GetRegion(int start, int length) const
{
	// DATA OBJECT IS EMPTY
	YAGLPP_ASSERT(IsData());

	// REQUESTED MEMORY SUB BLOCK IS TOO BIG
	YAGLPP_ASSERT(GetSize() >= start + length);

	return &m_Data[start];
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
_Ret_notnull_ inline unsigned char* DataStore::GetRegion(int start, int unused) const
{
	return &m_Data[start];
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
#endif // #ifndef YAGLPP_DATA_STORE_H
