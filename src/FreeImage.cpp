#define YAGLPP_BUILD_LIB
#include <yaglpp/FreeImage.h>
#ifndef YAGLPP_NO_FREEIMAGE
#include <FreeImage.h>
#pragma comment(lib, "FreeImage.lib")
#pragma message("FreeImage.cpp: Compiling with FreeImage library support...")
extern LPBYTE _loadFile(const char*, int*);
extern LPBYTE _loadResource(int, int*);
FreeImage::_SDATA FreeImage::s_Data;
FreeImage::_SDATA::_SDATA()
{
	FreeImage_Initialise(); // Initialize FreeImage

#ifdef _DEBUG
	FreeImage_SetOutputMessage((FreeImage_OutputMessageFunction)errorCallback);
#endif // #ifdef _DEBUG
}

FreeImage::_SDATA::~_SDATA()
{
	FreeImage_DeInitialise();
}

int FreeImage::_loadCursor(LPBYTE data, int size, LPPOINT* hotspot)
{
	int iCount = 0;
	_LPICONDIR pIconDir = (_LPICONDIR)data; // Icondir struct
	YAGLPP_ASSERT((pIconDir->idReserved == 0) && (pIconDir->idType == 2) && (pIconDir->idCount > 0)); // INVALID CURSOR FORMAT
	pIconDir->idType = 1; // Set ICON value
	*hotspot = (LPPOINT)YAGLPP_MALLOC(pIconDir->idCount * sizeof(POINT));
	for (int i = 0; i < pIconDir->idCount; i++)
	{
		_LPICONDIRENTRY lpIconDirEntry = (_LPICONDIRENTRY)&data[sizeof(_ICONDIR) + sizeof(_ICONDIRENTRY) * i];
		hotspot[i]->x = lpIconDirEntry->wPlanes; // Save X-hotspot & Y-hotspot
		hotspot[i]->y = lpIconDirEntry->wBitCount;
		LPBITMAPINFOHEADER lpBitmapInfoHeader = (LPBITMAPINFOHEADER)&data[lpIconDirEntry->dwImageOffset];
		lpIconDirEntry->wPlanes = lpBitmapInfoHeader->biPlanes; // Set wPlanes & wBitCount to ICON values
		lpIconDirEntry->wBitCount = lpBitmapInfoHeader->biBitCount;
	}
	FIMEMORY* hMemory = FreeImage_OpenMemory(data, size);
	if (hMemory)
	{
		iCount = _loadFormat(hMemory, NULL, FIF_ICO);
		FreeImage_CloseMemory(hMemory);
	}
	return iCount;
}

int FreeImage::_loadFormat(int rcid, int format)
{
	int iSize;
	LPBYTE lpData = _loadResource(rcid, &iSize);
	FIMEMORY* hMemory = FreeImage_OpenMemory(lpData, iSize);
	int iCount = _loadFormat(hMemory, NULL, format);
	FreeImage_CloseMemory(hMemory);
	return iCount;
}

int FreeImage::_loadFormat(void* memory, const char* filepath, int format)
{
	YAGLPP_ASSERT(!isImage()); // FREE IMAGE OBJECT MUST BE EMPTY
	int iCount = 0, iFlag = 0;
	switch (format)
	{
	case FIF_GIF:
		iFlag = GIF_PLAYBACK;
		break;
	case FIF_ICO:
		iFlag = ICO_MAKEALPHA;
		break;
	case FIF_JPEG:
		iFlag = JPEG_ACCURATE;
		break;
	case FIF_PNG:
		iFlag = PNG_IGNOREGAMMA;
	}
	if ((format == FIF_ICO) || (format == FIF_GIF) || (format == FIF_TIFF))
	{
		FIMULTIBITMAP* hMultiBitmap = (memory) ?
			FreeImage_LoadMultiBitmapFromMemory((FREE_IMAGE_FORMAT)format, (FIMEMORY*)memory, iFlag) :
			FreeImage_OpenMultiBitmap((FREE_IMAGE_FORMAT)format, filepath, FALSE, TRUE, TRUE, iFlag);
		if (hMultiBitmap)
		{
			iCount = FreeImage_GetPageCount(hMultiBitmap);
			m_lpData = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + (sizeof(LPVOID) * iCount));
			for (int i = 0; i < iCount; i++)
			{
				FIBITMAP* hLock = FreeImage_LockPage(hMultiBitmap, i);
				m_lpData->data[i] = FreeImage_ConvertTo32Bits(hLock);
				FreeImage_UnlockPage(hMultiBitmap, hLock, FALSE);
			}
			FreeImage_CloseMultiBitmap(hMultiBitmap, 0);
			m_lpData->count = iCount;
		}
	}
	else
	{
		FIBITMAP* hBitmap = (memory) ?
			FreeImage_LoadFromMemory((FREE_IMAGE_FORMAT)format, (FIMEMORY*)memory, iFlag) :
			FreeImage_Load((FREE_IMAGE_FORMAT)format, filepath, iFlag);
		if (hBitmap)
		{
			m_lpData = (_LPDATA)YAGLPP_MALLOC(sizeof(_DATA) + sizeof(LPVOID));
			iCount = (m_lpData->count = 1);
			m_lpData->data[0] = FreeImage_ConvertTo32Bits(hBitmap);
			FreeImage_Unload(hBitmap);
		}
	}
	return iCount;
}

_Ret_notnull_ LPBYTE FreeImage::allocateImage(_Out_ int* width, _Out_ int* height, unsigned int page)
{
	FIBITMAP* pBitmap = (FIBITMAP*)_bitmap(page); // Assert image
	UINT* pSrc = (UINT*)FreeImage_GetBits(pBitmap);
	int iFullWidth = FreeImage_GetWidth(pBitmap);
	int iFullHeight = FreeImage_GetHeight(pBitmap);
	int iFullSize = iFullWidth * iFullHeight;
	UINT* pDst = (UINT*)YAGLPP_MALLOC(iFullSize * sizeof(UINT));
	int iSrc = 0, iDst = iFullSize - iFullWidth;
	while (iSrc < iFullSize)
	{
		for (int i = 0; i < iFullWidth; i++)
		{
			UINT uRGBA = pSrc[iSrc + i];
			*(pDst + iDst + i) = (uRGBA & (FI_RGBA_ALPHA_MASK | FI_RGBA_GREEN_MASK)) |
				((uRGBA & FI_RGBA_RED_MASK) >> 16) | ((uRGBA & FI_RGBA_BLUE_MASK) << 16);
		}
		iSrc += iFullWidth;
		iDst -= iFullHeight;
	}
	*width = iFullWidth;
	*height = iFullHeight;
	return (LPBYTE)pDst;
}

_Ret_notnull_ LPBYTE FreeImage::allocateRegion(int left, int top, int width, int height, unsigned int page)
{
	FIBITMAP* pBitmap = (FIBITMAP*)_bitmap(page); // Assert image
	int iFullWidth = FreeImage_GetWidth(pBitmap);
	YAGLPP_ASSERT((width > 0) && (left >= 0) && (iFullWidth >= (left + width))); // INVALID WIDTH OR LEFT PARAMETERS OF ALLOCATING SPRITE
	int iFullHeight = FreeImage_GetHeight(pBitmap);
	YAGLPP_ASSERT((height > 0) && (top >= 0) && (iFullHeight >= (top + height))); // INVALID HEIGHT OR TOP PARAMETERS OF ALLOCATING SPRITE
	UINT* pSrc = (UINT*)FreeImage_GetBits(pBitmap);
	int iSize = width * height;
	int iFullSize = iFullWidth * iFullHeight;
	UINT* pDst = (UINT*)YAGLPP_MALLOC(iFullSize * sizeof(UINT));
	int iDst = 0, iSrc = iFullSize - (iFullWidth * (top + 1)) + left;
	while (iDst < iSize)
	{
		for (int i = 0; i < width; i++)
		{
			UINT uRGBA = pSrc[iSrc + i];
			*(pDst + iDst + i) = (uRGBA & (FI_RGBA_ALPHA_MASK | FI_RGBA_GREEN_MASK)) |
				((uRGBA & FI_RGBA_RED_MASK) >> 16) | ((uRGBA & FI_RGBA_BLUE_MASK) << 16);
		}
		iDst += width;
		iSrc -= iFullWidth;
	}
	return (LPBYTE)pDst;
}

_Ret_notnull_ LPBYTE FreeImage::allocateSprite(int width, int height, int index, unsigned int page)
{
	FIBITMAP* pBitmap = (FIBITMAP*)_bitmap(page); // Assert image
	int iFullWidth = FreeImage_GetWidth(pBitmap);
	int iFullHeight = FreeImage_GetHeight(pBitmap);
	int iCol = iFullWidth / width, iRemC = iFullWidth % width; // Calculate number of sprites in row and reminder
	int iRow = iFullHeight / height, iRemR = iFullHeight % height; // Calculate number of rows in image and reminder
	YAGLPP_ASSERT((iRemC == 0) && (iRemR == 0) && (index < (iCol* iRow))); // ALLOCATING SPRITE CAN'T FIT INTO THE IMAGE
	int iTop = index / iCol, iLeft = index % iCol; // Find sprite position in image
	return allocateRegion(iLeft * width, iTop * height, width, height, page);
}

int FreeImage::findLargestPage()
{
	int iPage = 0, iSize = 0, iCount = getPageCount();
	for (int i = 0; i < iCount; i++)
	{
		FIBITMAP* pDib = (FIBITMAP*)m_lpData->data[i];
		int iResult = FreeImage_GetWidth(pDib) * FreeImage_GetHeight(pDib);
		if (iSize < iResult)
		{
			iPage = i;
			iSize = iResult;
		}
	}
	return iPage;
}

_Ret_notnull_ LPBYTE FreeImage::getBits(unsigned int page)
{
	return FreeImage_GetBits((FIBITMAP*)_bitmap(page)); // Assert image
}

int FreeImage::getHeight(unsigned int page) const
{
	return FreeImage_GetHeight((FIBITMAP*)_bitmap(page));
}

int FreeImage::getWidth(unsigned int page) const
{
	return FreeImage_GetWidth((FIBITMAP*)_bitmap(page));
}

int FreeImage::loadCursor(int rcid, _Out_ LPPOINT* hotspot)
{
	int iSize;
	LPBYTE pResource = _loadResource(rcid, &iSize);
	LPBYTE lpData = (LPBYTE)YAGLPP_MALLOC(iSize);
	memcpy(lpData, pResource, iSize);
	int iCount = _loadCursor(lpData, iSize, hotspot);
	YAGLPP_FREE(lpData);
	return iCount;
}

int FreeImage::loadCursor(_In_z_ const char* filepath, _Out_ LPPOINT* hotspot)
{
	int iSize;
	LPBYTE lpData = _loadFile(filepath, &iSize);
	int iCount = _loadCursor(lpData, iSize, hotspot);
	YAGLPP_FREE(lpData);
	return iCount;
}

int FreeImage::loadImage(int rcid)
{
	int iSize;
	LPBYTE lpData = _loadResource(rcid, &iSize);
	FIMEMORY* hMemory = FreeImage_OpenMemory(lpData, (DWORD)iSize);
#pragma warning(push)
#pragma warning(disable : 26812) // Enum type limitation
	int iFormat = (int)FreeImage_GetFileTypeFromMemory(hMemory);
#pragma warning(pop)
	YAGLPP_ASSERT((iFormat != FIF_UNKNOWN) && FreeImage_FIFSupportsReading((FREE_IMAGE_FORMAT)iFormat)); // FREE IMAGE UNKNOWN RESOURCE FORMAT
	int iCount = _loadFormat(hMemory, NULL, iFormat);
	FreeImage_CloseMemory(hMemory);
	return iCount;
}

int FreeImage::loadImage(_In_z_ const char* filepath)
{
	int iFormat = (int)FreeImage_GetFileType(filepath);
	if (iFormat == FIF_UNKNOWN)
	{
#pragma warning(push)
#pragma warning(disable : 26812) // Enum type limitation
		iFormat = FreeImage_GetFIFFromFilename(filepath);
#pragma warning(pop)
		YAGLPP_ASSERT((iFormat != FIF_UNKNOWN) && FreeImage_FIFSupportsReading((FREE_IMAGE_FORMAT)iFormat)); // FREE IMAGE UNKNOWN FILE FORMAT
	}
	return _loadFormat(NULL, filepath, iFormat);
}

void FreeImage::unloadImage()
{
	int iCount = getPageCount();
	for (int i = 0; i < iCount; i++)
	{
		FIBITMAP* dib = (FIBITMAP*)m_lpData->data[i];
		FreeImage_Unload(dib);
	}
	YAGLPP_FREE(m_lpData);
	m_lpData = nullptr;
}

#ifdef _DEBUG
void FreeImage::_SDATA::errorCallback(int format, const char* description)
{
	const char* pFormat = ((FREE_IMAGE_FORMAT)format != FIF_UNKNOWN) ? FreeImage_GetFormatFromFIF((FREE_IMAGE_FORMAT)format) : "Unknown";
	std::cout << "FREE IMAGE ERROR USING <" << pFormat << "> FORMAT: " << description << std::endl;
	YAGLPP_ASSERT(false); // FREE IMAGE LIBRARY ERROR
}

LPVOID FreeImage::_bitmap(unsigned int page) const
{
	YAGLPP_ASSERT(getPageCount() > (int)page); // PAGE INDEX IS INVALID
	return m_lpData->data[page];
}

int FreeImage::getPageCount() const
{
	YAGLPP_ASSERT(isImage()); // FREE IMAGE OBJECT IS EMPTY
	return m_lpData->count;
}
#endif // #ifdef _DEBUG
#endif // #ifndef YAGLPP_NO_FREEIMAGE
