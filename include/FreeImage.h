#pragma once
#include "yaglpp.h"
#ifndef YAGLPP_NO_FREEIMAGE
/*YAGL++ FreeImage helper root class*/
class FreeImage
{
private:
	typedef struct {
		WORD idReserved;		// Reserved (must be 0)
		WORD idType;			// Resource Type (1 = ico, 2 = cur)
		WORD idCount;			// Number of images
	} _ICONDIR, *_LPICONDIR;

	typedef struct {
		BYTE bWidth;			// Image width in pixels, 0 means image width is 256 pixels or more
		BYTE bHeight;			// Image height in pixels, 0 means image height is 256 pixels or more
		BYTE bColorCount;		// Number of colors in image, 0 if no palette (>=8bpp)
		BYTE bReserved;			// Reserved (must be 0)
		WORD wPlanes;			// Icon color planes / Cursor X-hotspot
		WORD wBitCount;			// Icon bits per pixel / Cursor Y-hotspot
		DWORD dwBytesInRes;		// How many bytes in this resource?
		DWORD dwImageOffset;	// Where in the file is this image?
	} _ICONDIRENTRY, *_LPICONDIRENTRY;

	static struct _SDATA		// Static data
	{
		_SDATA();
		~_SDATA();

#ifdef _DEBUG
		static void errorCallback(int format, const char* description);
#endif // #ifdef _DEBUG
	} s_Data;

	typedef struct {
		int count;		// Page count
#pragma warning(push)
#pragma warning(disable : 4200)
		LPVOID data[0];	// Zero data array
#pragma warning(pop)
	} _DATA, *_LPDATA;
	_LPDATA m_lpData = nullptr;	// Class data

	LPVOID _bitmap(unsigned int page) const;
	int _loadCursor(LPBYTE data, int size, LPPOINT* hotspot);
	int _loadFormat(int rcid, int format);
	int _loadFormat(void* memory, const char* filepath, int format);

public:
	/*(1) Construct an empty free image object*/
	FreeImage() {}

	/*(2) Construct free image object with <loadImage>*/
	FreeImage(int rcid)
	{
		loadImage(rcid);
	}

	/*(3) Construct free image object with <loadImage>*/
	FreeImage(_In_z_ const char* filepath)
	{
		loadImage(filepath);
	}

	/*Cleans up the FreeImage object*/
	~FreeImage()
	{
		if (isImage())
		{
			unloadImage();
		}
	}

	/*Return pixel array of an entire image, reversing the byte order
	@param [out] Pointer to store the width of allocated image
	@param [out] Pointer to store the height of allocated image
	@param Image page index in the object. Must be less than the image count
	@return The allocated RGBA pixel array. Must be cleaned up after use*/
	_Ret_notnull_ LPBYTE allocateImage(_Out_ int* width, _Out_ int* height, unsigned int page = 0);

	/*Return pixel array of a part of an image, reversing the byte order
	@param Image sprite left x-offset in pixels
	@param Image sprite top y-offset in pixels
	@param Image sprite width in pixels
	@param Image sprite height in pixels
	@param Image page index in the object. less than the
	@return The allocated RGBA pixel array. Must be cleaned up after use*/
	_Ret_notnull_ LPBYTE allocateRegion(int left, int top, int width, int height, unsigned int page = 0);

	/*Return pixel array of one of the sprites with similar dimensions, reversing the byte order. The image dimentions must be mutiple of those of the sprites.
	@param The width of indexed image, must be the same within the image
	@param The height of indexed image, must be the same within the image
	@param The index of the sprite. Must be less than the number of sprites fit into image
	@param Image page index in the object. Must be less than the image count
	@return The allocated RGBA pixel array. Must be cleaned up after use*/
	_Ret_notnull_ LPBYTE allocateSprite(int width, int height, int index, unsigned int page = 0);

	/*Return index of largest image page in the object
	@return The largest page index in the object*/
	int findLargestPage();

	/*Returns a pointer to RGBA pixel data of the image page in top-to-bottom order
	@param Image page index in the object. Must be less than the image count
	@return The image page pixel data, cleaned up by the library*/
	_Ret_notnull_ LPBYTE getBits(unsigned int page = 0);

	/*Returns the width of the image page
	@param Image page index in the object. Must be less than the image count
	@return The image page width*/
	int getHeight(unsigned int page = 0) const;

	/*Returns the width of the image page
	@param Image page index in the object. Must be less than the image count
	@return The image page width*/
	int getWidth(unsigned int page = 0) const;

	/*Return FreeImage object page count
	@return The number of image pages in the FreeImage object*/
	int getPageCount() const;

	/*Check if FreeImage object contains one or more images
	@return True if FreeImage object contains images, false otherwise*/
	bool isImage() const
	{
		return m_lpData != nullptr;
	}

	/*(1) Load image from cursor binary resource
	@param The cursor resource id of <RCDATA> type
	@param [out] Pointer to store an allocated array of cursor hotspots. Must be cleaned up after use if successful
	@return The number of image pages loaded into FreeImage object*/
	int loadCursor(int rcid, _Out_ LPPOINT* hotspot);

	/*(2) Load image from cursor file
	@param [in] Path to the cursor file
	@param [out] Pointer to store an allocated array of cursor hotspots. Must be cleaned up after use if successful
	@return The number of image pages loaded into FreeImage object*/
	int loadCursor(_In_z_ const char* filepath, _Out_ LPPOINT* hotspot);

	/*(1) Load image from gif binary resource with common flag
	@param The gif resource id of <RCDATA> type
	@return The number of image pages loaded into FreeImage object*/
	int loadGif(int rcid)
	{
		return _loadFormat(rcid, 25); // FIF_GIF
	}

	/*(2) Load image from gif file
	@param [in] Path to the gif file
	@return The number of image pages loaded into FreeImage object*/
	int loadGif(_In_z_ const char* filepath)
	{
		return _loadFormat(NULL, filepath, 25); // FIF_GIF
	}

	/*(1) Load image from icon binary resource
	@param The icon resource id of <RCDATA> type
	@return The number of image pages loaded into FreeImage object*/
	int loadIcon(int rcid)
	{
		return _loadFormat(rcid, 1); // FIF_ICO
	}

	/*(2) Load image from icon file
	@param [in] Path to the icon file
	@return The number of image pages loaded into FreeImage object*/
	int loadIcon(_In_z_ const char* filepath)
	{
		return _loadFormat(NULL, filepath, 1); // FIF_ICO
	}

	/*(1) Load image from binary resource and determine format
	@param The cursor resource id of <RCDATA> type
	@return The number of image pages loaded into FreeImage object*/
	int loadImage(int rcid);

	/*(2) Load image from file and determine format
	@param [in] Path to the cursor file
	@return The number of image pages loaded into FreeImage object*/
	int loadImage(_In_z_ const char* filepath);

	/*(1) Load image from jpeg binary resource
	@param The jpeg resource id of <RCDATA> type
	@return The number of image pages loaded into FreeImage object*/
	int loadJpeg(int rcid)
	{
		return _loadFormat(rcid, 2); // FIF_JPEG
	}

	/*(2) Load image from jpeg file
	@param [in] Path to the jpeg file
	@return The number of image pages loaded into FreeImage object*/
	int loadJpeg(_In_z_ const char* filepath)
	{
		return _loadFormat(NULL, filepath, 2); // FIF_JPEG
	}

	/*(1) Load image from png binary resource
	@param The png resource id of <RCDATA> type
	@return The number of image pages loaded into FreeImage object*/
	int loadPng(int rcid)
	{
		return _loadFormat(rcid, 13); // FIF_PNG
	}

	/*(2) Load image from png file
	@param [in] Path to the png file
	@return The number of image pages loaded into FreeImage object*/
	int loadPng(_In_z_ const char* filepath)
	{
		return _loadFormat(NULL, filepath, 13); // FIF_PNG
	}

	/*Unload image pages and free resources*/
	void unloadImage();
}; // class FreeImage

#ifndef _DEBUG
inline LPVOID FreeImage::_bitmap(unsigned int page) const
{
	return m_lpData->data[page];
}

inline int FreeImage::getPageCount() const
{
	return m_lpData->count;
}
#endif // #ifndef _DEBUG
#endif // #ifndef YAGLPP_NO_FREEIMAGE
