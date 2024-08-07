#define YAGLPP_BUILD_LIB
#include <yaglpp/StbImage.h>
#define YAGLPP_STBIMAGE_BYTE 0xF0
#define YAGLPP_STBIMAGE_COMP 0x0F
static int YAGLPP_STBIMAGE_JPEG = 80;
extern LPBYTE _loadResource(int, int*);

#ifdef _DEBUG
#define STBI_FAILURE_USERMSG
#define YAGLPP_STBIMAGE_ASSERT if (_m.pPixels == nullptr) { std::cout << "STB IMAGE ERROR: " << stbi_failure_reason() << std::endl; _YAGLPP_ASSERT_(false); }
#else // #ifdef _DEBUG
#define STBI_NO_FAILURE_STRINGS
#define YAGLPP_STBIMAGE_ASSERT
#endif // #ifdef _DEBUG

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(e) _YAGLPP_ASSERT_(e)
#define STBI_FREE(p) _YAGLPP_FREE_(p)
#define STBI_MALLOC(s) _YAGLPP_MALLOC_(s)
#define STBI_REALLOC(p,s) _YAGLPP_REALLOC_(p,s)
#include <stb/stb_image.h> // v2.29

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STBIR_ASSERT(e) _YAGLPP_ASSERT_(e)
#define STBIR_FREE(p,c) ((void)(c), _YAGLPP_FREE_(p))
#define STBIR_MALLOC(s,c) ((void)(c), _YAGLPP_MALLOC_(s))
#include <stb/stb_image_resize2.h> // v2.06

#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(e) _YAGLPP_ASSERT_(e)
#define STBIW_FREE(p) _YAGLPP_FREE_(p)
#define STBIW_MALLOC(s) _YAGLPP_MALLOC_(s)
#define STBIW_REALLOC(p,s) _YAGLPP_REALLOC_(p,s)
#include <stb/stb_image_write.h> // v1.16

/*Deprecated animated gif loader, missing in official release*/
STBIDEF stbi_uc* stbi_load_gif_from_callbacks(stbi_io_callbacks const* clbk, void* user, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result;
	stbi__context s;
	stbi__start_callbacks(&s, (stbi_io_callbacks*)clbk, user);
	result = (unsigned char*)stbi__load_gif_main(&s, delays, x, y, z, comp, req_comp);
	if (stbi__vertically_flip_on_load) {
		stbi__vertical_flip_slices(result, *x, *y, *z, *comp);
	}
	return result;
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF stbi_uc* stbi_load_gif_from_file(FILE* f, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result;
	stbi__context s;
	stbi__start_file(&s, f);
	result = (unsigned char*)stbi__load_gif_main(&s, delays, x, y, z, comp, req_comp);
	if (stbi__vertically_flip_on_load) {
		stbi__vertical_flip_slices(result, *x, *y, *z, *comp);
	}
	if (result) {
		// need to 'unget' all the characters in the IO buffer
		fseek(f, -(int)(s.img_buffer_end - s.img_buffer), SEEK_CUR);
	}
	return result;
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF stbi_us* stbi_load_16_gif_from_callbacks(stbi_io_callbacks const* clbk, void* user, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_callbacks(clbk, user, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__convert_8_to_16(result, *x, *y, *comp);
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF stbi_us* stbi_load_16_gif_from_file(FILE* f, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_file(f, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__convert_8_to_16(result, *x, *y, *comp);
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF stbi_us* stbi_load_16_gif_from_memory(stbi_uc const* buffer, int len, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_memory(buffer, len, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__convert_8_to_16(result, *x, *y, *comp);
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF float* stbi_loadf_gif_from_callbacks(stbi_io_callbacks const* clbk, void* user, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_callbacks(clbk, user, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__ldr_to_hdr(result, *x, *y, *comp);
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF float* stbi_loadf_gif_from_file(FILE* f, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_file(f, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__ldr_to_hdr(result, *x, *y, *comp);
}

/*Deprecated animated gif loader, missing in official release*/
STBIDEF float* stbi_loadf_gif_from_memory(stbi_uc const* buffer, int len, int** delays, int* x, int* y, int* z, int* comp, int req_comp)
{
	unsigned char* result = stbi_load_gif_from_memory(buffer, len, delays, x, y, z, comp, req_comp);
	if (!result) return NULL;
	return stbi__ldr_to_hdr(result, *x, *y, *comp);
}

void StbImage::convertIphonePngToRgb(bool convert)
{
	stbi_convert_iphone_png_to_rgb((int)convert);
}

void StbImage::copy(const StbImage& source)
{
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE DESTINATION OBJECT HAS LOADED IMAGE
	void* lpSource = source.getPixels(); // Pixels
	_m.iByte = source._m.iByte;
	_m.iComp = source._m.iComp;
	_m.iWidth = source._m.iWidth;
	_m.iHeight = source._m.iHeight;
	size_t iSize = static_cast<size_t>(_m.iWidth) * _m.iHeight * _m.iComp * _m.iByte;
	_m.pPixels = _YAGLPP_MALLOC_(iSize);
	memcpy(_m.pPixels, lpSource, iSize);
}

void StbImage::copyRegion(const StbImage& source, int rleft, int rtop, int rwidth, int rheight)
{
	_YAGLPP_ASSERT_((this == &source) || (_m.pPixels == nullptr)); // STB DESTINATION IMAGE OBJECT HAS LOADED IMAGE
	void* lpSource = source.getPixels(); // Pixels
	_m.iByte = source._m.iByte;
	_m.iComp = source._m.iComp;
	_YAGLPP_ASSERT_((rwidth > 0) && (rleft >= 0) && (source._m.iWidth >= (rleft + rwidth))); // INVALID WIDTH OR LEFT PARAMETERS OF ALLOCATING SPRITE
	_YAGLPP_ASSERT_((rheight > 0) && (rtop >= 0) && (source._m.iHeight >= (rtop + rheight))); // INVALID HEIGHT OR TOP PARAMETERS OF ALLOCATING SPRITE
	int iDstPos = 0,
		iPixel = _m.iByte * _m.iComp,
		iDstLine = rwidth * iPixel,
		iSrcLine = source._m.iWidth * iPixel,
		iSrcPos = (iSrcLine * rtop) + (rleft * iPixel);
	_m.pPixels = _YAGLPP_MALLOC_(static_cast<size_t>(iDstLine) * rheight);
	for (int iHscan = 0; iHscan < rheight; iHscan++)
	{
		memcpy((char*)_m.pPixels + iDstPos, (char*)lpSource + iSrcPos, iDstLine);
		iDstPos += iDstLine;
		iSrcPos += iSrcLine;
	}
	_m.iWidth = rwidth;
	_m.iHeight = rheight;
	if (this == &source)
	{
		STBI_FREE(lpSource);
	}
}

void StbImage::copySprite(const StbImage& source, int width, int height, int index)
{
	int iCol = source._m.iWidth / width, iRemC = source._m.iWidth % width; // Number of sprites in row + reminder
	int iRow = source._m.iHeight / height, iRemR = source._m.iHeight % height; // Number of rows in image + reminder
	_YAGLPP_ASSERT_((iRemC == 0) && (iRemR == 0) && (index < (iCol* iRow))); // SPRITE CANNOT FIT INTO THE IMAGE
	int iTop = index / iCol, iLeft = index % iCol; // Find sprite position in image
	return copyRegion(source, iLeft * width, iTop * height, width, height);
}

void StbImage::create(int width, int height, StbFormat format, bool init)
{
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	_YAGLPP_ASSERT_((width > 0) && (height > 0) && ((width * height) <= STBI_MAX_DIMENSIONS)); // IMAGE DIMENSIONS ARE INVALID
	_m.iWidth = width;
	_m.iHeight = height;
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	_m.iComp = (int)format & YAGLPP_STBIMAGE_COMP;
	_YAGLPP_ASSERT_((_m.iByte > 0) && (_m.iComp > 0)); // IMAGE PIXEL FORMAT MUST BE NON-DEFAULT
	int iSize = _m.iWidth * _m.iHeight * _m.iByte * _m.iComp;
	_m.pPixels = (init) ? _YAGLPP_CALLOC_(iSize) : _YAGLPP_MALLOC_(iSize);
}

void StbImage::flipVerticallyOnWrite(bool flip)
{
	stbi_flip_vertically_on_write((int)flip);
}

void StbImage::hdrToLdrGamma(float gamma)
{
	stbi_hdr_to_ldr_gamma(gamma);
}

void StbImage::hdrToLdrScale(float scale)
{
	stbi_hdr_to_ldr_scale(scale);
}

void StbImage::imageFree()
{
	stbi_image_free(getPixels());
	memset(&_m, 0, sizeof(_MDATA));
}

bool StbImage::info(int rcid)
{
	int iLen;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	_m.iByte =
		(stbi_is_hdr_from_memory(pBuffer, iLen)) ? 4 :
		(stbi_is_16_bit_from_memory(pBuffer, iLen)) ? 2 : 1;
	return (bool)stbi_info_from_memory(pBuffer, iLen, &_m.iWidth, &_m.iHeight, &_m.iComp);
}

bool StbImage::info(_In_z_ const char* file)
{
	FILE* pFile;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	_YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD IMAGE FILE
	_m.iByte =
		(stbi_is_hdr_from_file(pFile)) ? 4 :
		(stbi_is_16_bit_from_file(pFile)) ? 2 : 1;
	bool bResult = (bool)stbi_info_from_file(pFile, &_m.iWidth, &_m.iHeight, &_m.iComp);
	fclose(pFile);
	return bResult;
}

bool StbImage::info(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	_m.iByte =
		(stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 4 :
		(stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 2 : 1;
	return (bool)stbi_info_from_callbacks((stbi_io_callbacks*)clbk, user, &_m.iWidth, &_m.iHeight, &_m.iComp);
}

bool StbImage::is16bit(int rcid)
{
	int iLen;
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	return (bool)stbi_is_16_bit_from_memory(pBuffer, iLen);
}

bool StbImage::is16bit(_In_z_ const char* file)
{
	FILE* pFile;
	errno_t iError = fopen_s(&pFile, file, "rb");
	_YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD IMAGE FILE
	bool bResult = (bool)stbi_is_16_bit_from_file(pFile);
	fclose(pFile);
	return bResult;
}

bool StbImage::is16bit(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user);
}

bool StbImage::isHdr(int rcid)
{
	int iLen;
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	return (bool)stbi_is_hdr_from_memory(pBuffer, iLen);
}

bool StbImage::isHdr(_In_z_ const char* file)
{
	FILE* pFile;
	errno_t iError = fopen_s(&pFile, file, "rb");
	_YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD IMAGE FILE
	bool bResult = (bool)stbi_is_hdr_from_file(pFile);
	fclose(pFile);
	return bResult;
}

bool StbImage::isHdr(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user);
}

void StbImage::ldrToHdrGamma(float gamma)
{
	stbi_ldr_to_hdr_gamma(gamma);
}

void StbImage::ldrToHdrScale(float scale)
{
	stbi_ldr_to_hdr_scale(scale);
}

void StbImage::load(int rcid, StbFormat format)
{
	int iLen;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) // Load original depth
	{
		_m.iByte =
			(stbi_is_hdr_from_memory(pBuffer, iLen)) ? 4 :
			(stbi_is_16_bit_from_memory(pBuffer, iLen)) ? 2 : 1;
	}
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_from_memory(pBuffer, iLen, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_16_from_memory(pBuffer, iLen, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_from_memory(pBuffer, iLen, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
}

void StbImage::load(_In_z_ const char* file, StbFormat format)
{
	FILE* pFile;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	_YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD IMAGE FILE
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) // Load original depth
	{
		_m.iByte =
			(stbi_is_hdr_from_file(pFile)) ? 4 :
			(stbi_is_16_bit_from_file(pFile)) ? 2 : 1;
	}
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_from_file(pFile, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_from_file_16(pFile, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_from_file(pFile, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
	fclose(pFile);
}

void StbImage::load(_In_ StbCallbacks const* clbk, _In_ void* user, StbFormat format)
{
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) // Load original depth
	{
		_m.iByte =
			(stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 4 :
			(stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 2 : 1;
	}
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_from_callbacks((stbi_io_callbacks*)clbk, user, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_16_from_callbacks((stbi_io_callbacks*)clbk, user, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_from_callbacks((stbi_io_callbacks*)clbk, user, &_m.iWidth, &_m.iHeight, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
}

int StbImage::loadGif(int rcid, _Outptr_opt_ int** delays, StbFormat format)
{
	int iLen;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) _m.iByte = 1; // Original depth always 1
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_gif_from_memory(pBuffer, iLen, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_16_gif_from_memory(pBuffer, iLen, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_gif_from_memory(pBuffer, iLen, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD GIF IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
	_m.iHeight *= iLayers; // Interleaved images
	return iLayers;
}

int StbImage::loadGif(_In_z_ const char* file, _Outptr_opt_ int** delays, StbFormat format)
{
	FILE* pFile;
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	_YAGLPP_ASSERT_(iError == 0); // FAILED TO LOAD IMAGE FILE
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) _m.iByte = 1; // Original depth always 1
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_gif_from_file(pFile, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_16_gif_from_file(pFile, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_gif_from_file(pFile, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD GIF IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
	_m.iHeight *= iLayers; // Interleaved images
	return iLayers;
}

int StbImage::loadGif(_In_ StbCallbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays, StbFormat format)
{
	_YAGLPP_ASSERT_(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (_m.iByte == 0) _m.iByte = 1; // Original depth always 1
	_m.pPixels =
		(_m.iByte == 1) ? stbi_load_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(_m.iByte == 2) ? stbi_load_16_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp) :
		(void*)stbi_loadf_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &_m.iWidth, &_m.iHeight, &iLayers, &_m.iComp, iReqComp);
	YAGLPP_STBIMAGE_ASSERT; // FAILED TO LOAD GIF IMAGE
	if (iReqComp > 0) _m.iComp = iReqComp;
	_m.iHeight *= iLayers; // Interleaved images
	return iLayers;
}

bool StbImage::resizeRegion(const StbImage& source, int width, int height, int rleft, int rtop, int rwidth, int rheight)
{
	_YAGLPP_ASSERT_((this == &source) || (_m.pPixels == nullptr)); // STB DESTINATION IMAGE OBJECT HAS LOADED IMAGE
	_YAGLPP_ASSERT_((width > 0) && (height > 0) && ((width * height) <= STBI_MAX_DIMENSIONS)); // OUTPUT IMAGE DIMENSIONS ARE INVALID
	void* lpSource = source.getPixels(); // Pixels
	_m.iByte = source._m.iByte;
	_m.iComp = source._m.iComp;
	stbir_datatype byte =
		(_m.iByte == 1) ? STBIR_TYPE_UINT8 :
		(_m.iByte == 2) ? STBIR_TYPE_UINT16 : STBIR_TYPE_FLOAT; // Depth
	stbir_pixel_layout comp =
		(_m.iComp == 1) ? STBIR_1CHANNEL :
		(_m.iComp == 2) ? STBIR_2CHANNEL :
		(_m.iComp == 3) ? STBIR_RGB : STBIR_RGBA; // Channels
	STBIR_RESIZE resize;
	_m.pPixels = _YAGLPP_MALLOC_(static_cast<size_t>(width) * height * _m.iByte * _m.iComp);
	stbir_resize_init(&resize, lpSource, source._m.iWidth, source._m.iHeight, 0, _m.pPixels, width, height, 0, comp, byte);
	stbir_set_edgemodes(&resize, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP);
	stbir_set_filters(&resize, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT);
	double s0 = (double)rleft / source._m.iWidth;
	double t0 = (double)rtop / source._m.iHeight;
	double s1 = s0 + (double)rwidth / source._m.iWidth;
	double t1 = t0 + (double)rheight / source._m.iHeight;
	_YAGLPP_ASSERT_(stbir_set_input_subrect(&resize, s0, t0, s1, t1)); // THE IMAGE REGION IN NOT INBOUND
	bool bResult = (bool)stbir_resize_extended(&resize);
	_m.iWidth = width;
	_m.iHeight = height;
	if (this == &source)
	{
		STBI_FREE(lpSource);
	}
	return bResult;
}

void StbImage::setFlipVerticallyOnLoad(bool flip)
{
	stbi_set_flip_vertically_on_load((int)flip);
}

void StbImage::setUnpremultiplyOnLoad(bool unpremultiply)
{
	stbi_set_unpremultiply_on_load((int)unpremultiply);
}

void StbImage::writeForcePngFilter(int filter)
{
	_YAGLPP_ASSERT_((filter >= -1) && (filter <= 5)); // INVALID PNG FILTER MODE PARAMETER
	stbi_write_force_png_filter = filter;
}

bool StbImage::writeBmp(_In_z_ const char* filepath)
{
	_YAGLPP_ASSERT_(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_bmp(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}

bool StbImage::writeHdr(_In_z_ const char* filepath)
{
	_YAGLPP_ASSERT_(_m.iByte == 4); // STB IMAGE DATA MUST BE 32F-BITS PER CHANNEL
	return (bool)stbi_write_hdr(filepath, _m.iWidth, _m.iHeight, _m.iComp, (float*)getPixels());
}

bool StbImage::writeJpg(_In_z_ const char* filepath)
{
	_YAGLPP_ASSERT_(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_jpg(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), YAGLPP_STBIMAGE_JPEG);
}

void StbImage::writeJpegQuality(int quality)
{
	_YAGLPP_ASSERT_((quality >= 1) && (quality <= 100)); // INVALID JPEG QUALITY PARAMETER
	YAGLPP_STBIMAGE_JPEG = quality;
}

bool StbImage::writePng(_In_z_ const char* filepath)
{
	_YAGLPP_ASSERT_(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_png(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), _m.iWidth * _m.iComp);
}

void StbImage::writePngCompressionLevel(int comp)
{
	_YAGLPP_ASSERT_((comp >= 0) && (comp <= 9)); // INVALID PNG COMPESSION LEVEL PARAMETER
	stbi_write_png_compression_level = comp;
}

bool StbImage::writeTga(_In_z_ const char* filepath)
{
	_YAGLPP_ASSERT_(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_tga(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}

void StbImage::writeTgaWithRle(bool rle)
{
	stbi_write_tga_with_rle = (int)rle;
}

#ifdef _DEBUG
_Ret_notnull_ void* StbImage::getPixels() const
{
	_YAGLPP_ASSERT_(_m.pPixels != nullptr); // STB IMAGE OBJECT HAS NO LOADED IMAGE
	return _m.pPixels;
}
#endif // #ifdef _DEBUG
