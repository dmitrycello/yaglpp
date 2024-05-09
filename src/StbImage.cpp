#define GLPP_BUILD_LIB
#include <glpp/StbImage.h>
#define GLPP_STBIMAGE_BYTE 0xF0
#define GLPP_STBIMAGE_COMP 0x0F
extern LPBYTE _loadResource(int, int*);

#ifdef _DEBUG
#define STBI_FAILURE_USERMSG
#define GLPP_STBIMAGE_ASSERT if (m_lpPixels == nullptr) { std::cout << "STB IMAGE ERROR: " << stbi_failure_reason() << std::endl; GLPP_ASSERT(false); }
#else // #ifdef _DEBUG
#define STBI_NO_FAILURE_STRINGS
#define GLPP_STBIMAGE_ASSERT
#endif // #ifdef _DEBUG

static int GLPP_STBIMAGE_JPEG = 80;
thread_local void* GLPP_STBIMAGE_TLSLOCK = nullptr;
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(e) GLPP_ASSERT(e)
#define STBI_FREE(p) if (GLPP_STBIMAGE_TLSLOCK != p) GLPP_FREE(p)
#define STBI_MALLOC(s) GLPP_MALLOC(s)
#define STBI_REALLOC(p,s) GLPP_REALLOC(p,s)
#include <stb/stb_image.h> // v2.29

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STBIR_ASSERT(e) GLPP_ASSERT(e)
#define STBIR_FREE(p,c) ((void)(c), GLPP_FREE(p))
#define STBIR_MALLOC(s,c) ((void)(c), GLPP_MALLOC(s))
#include <stb/stb_image_resize2.h> // v2.06

#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(e) GLPP_ASSERT(e)
#define STBIW_FREE(p) GLPP_FREE(p)
#define STBIW_MALLOC(s) GLPP_MALLOC(s)
#define STBIW_REALLOC(p,s) GLPP_REALLOC(p,s)
#include <stb/stb_image_write.h> // v1.16

/*Callback version of deprecated animated gif loader, missing in official release :(*/
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

/*File version of deprecated animated gif loader, missing in official release :(*/
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

void StbImage::_byte(_LPDATA data)
{
	int iResult = (data->len) ?
		stbi_is_hdr_from_memory(data->buffer, data->len) :
		stbi_is_hdr_from_file(data->file);
	if (iResult)
	{
		m_iByte = 4;
	}
	else
	{
		iResult = (data->len) ?
			stbi_is_16_bit_from_memory(data->buffer, data->len) :
			stbi_is_16_bit_from_file(data->file);
		m_iByte = (iResult) ? 2 : 1;
	}
}

void StbImage::_c168(void* data)
{
	GLPP_ASSERT(m_iByte == 2); // LOADED IMAGE IS NOT 16-BIT
	m_lpPixels = stbi__convert_16_to_8((stbi__uint16*)data, m_iWidth, m_iHeight, m_iComp);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT 16-BIT TO 8-BIT
	m_iByte = 1;
}

void StbImage::_c816(void* data)
{
	GLPP_ASSERT(m_iByte == 1); // LOADED IMAGE IS NOT 8-BIT
	m_lpPixels = stbi__convert_8_to_16((stbi_uc*)data, m_iWidth, m_iHeight, m_iComp);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT 8-BIT TO 16-BIT
	m_iByte = 2;
}

void StbImage::_cf08(void* data, int format)
{
	int iReqComp = format & GLPP_STBIMAGE_COMP;
	GLPP_ASSERT(m_iByte == 1); // LOADED IMAGE IS NOT 8-BIT
	GLPP_ASSERT((iReqComp != 0) && (iReqComp != m_iComp)); // NO CONVERSION IS TO PERFORM AT CURRENT SETTING
	m_lpPixels = stbi__convert_format((stbi_uc*)data, m_iComp, iReqComp, m_iWidth, m_iHeight);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT 8-BIT PIXEL FORMAT
	m_iComp = iReqComp;
}

void StbImage::_cf16(void* data, int format)
{
	int iReqComp = format & GLPP_STBIMAGE_COMP;
	GLPP_ASSERT(m_iByte == 2); // LOADED IMAGE IS NOT 16-BIT
	GLPP_ASSERT((iReqComp != 0) && (iReqComp != m_iComp)); // NO CONVERSION IS TO PERFORM AT CURRENT SETTING
	m_lpPixels = stbi__convert_format16((stbi__uint16*)data, m_iComp, iReqComp, m_iWidth, m_iHeight);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT 16-BIT PIXEL FORMAT
	m_iComp = iReqComp;
}

void StbImage::_conv(void* source, int format)
{
	void* lpSource = source;
	int iReqByte = (format & GLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = format & GLPP_STBIMAGE_COMP;
	if (iReqByte == m_iByte) iReqByte = 0; // Reset equal depth
	if (iReqComp == m_iComp) iReqComp = 0; // Reset equal channels

	// From 8-bit depth (reqbyte = 0,2,4)
	if (m_iByte == 1)
	{
		if (iReqComp > 0) // Different comp
		{
			m_lpPixels = stbi__convert_format((stbi_uc*)lpSource, m_iComp, iReqComp, m_iWidth, m_iHeight);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			m_iComp = iReqComp;
		}
		if (iReqByte == 2) // Directly to 16-bit
		{
			m_lpPixels = stbi__convert_8_to_16((stbi_uc*)lpSource, m_iWidth, m_iHeight, m_iComp);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			m_iByte = 2;
		}
		else if (iReqByte == 4)  // Directly to float
		{
			m_lpPixels = stbi__ldr_to_hdr((stbi_uc*)lpSource, m_iWidth, m_iHeight, m_iComp);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			m_iByte = 4;
		}
	}

	// From 16-bit depth (reqbyte = 0,1,4)
	else if (m_iByte == 2)
	{
		if (iReqComp > 0) // Different comp
		{
			m_lpPixels = stbi__convert_format16((stbi__uint16*)lpSource, m_iComp, iReqComp, m_iWidth, m_iHeight);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			m_iComp = iReqComp;
		}
		if (iReqByte > 0) // Not equal depth (reqbyte = 1,4)
		{
			m_lpPixels = stbi__convert_16_to_8((stbi__uint16*)lpSource, m_iWidth, m_iHeight, m_iComp);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			if (iReqByte == 4) // 2nd conversions
			{
				m_lpPixels = stbi__ldr_to_hdr((stbi_uc*)lpSource, m_iWidth, m_iHeight, m_iComp);
				GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			}
			m_iByte = iReqByte;
		}
	}

	// From 32-bit depth (reqbyte = 0,1,2), if any change
	else if ((iReqComp > 0) || (iReqByte > 0))
	{
		m_lpPixels = stbi__hdr_to_ldr((float*)lpSource, m_iWidth, m_iHeight, m_iComp);
		GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
		lpSource = m_lpPixels;
		if (iReqComp > 0) // Different comp
		{
			m_lpPixels = stbi__convert_format((stbi_uc*)lpSource, m_iComp, iReqComp, m_iWidth, m_iHeight);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			lpSource = m_lpPixels;
			m_iComp = iReqComp;
		}
		if (iReqByte == 2) // 16-bit 2nd conversion
		{
			m_lpPixels = stbi__convert_8_to_16((stbi_uc*)lpSource, m_iWidth, m_iHeight, m_iComp);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			m_iByte = 2;
		}
		else if (iReqByte == 0) // Float 3rd conversion
		{
			m_lpPixels = stbi__ldr_to_hdr((stbi_uc*)lpSource, m_iWidth, m_iHeight, m_iComp);
			GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
			m_iByte = 4;
		}
		else // Keep 8-bit
		{
			m_iByte = 1;
		}
	}
	GLPP_ASSERT(lpSource != source); // NO CONVERSION IS TO PERFORM AT CURRENT SETTING
}

void StbImage::_copy(const StbImage* source)
{
	GLPP_ASSERT(m_lpPixels == nullptr); // STB IMAGE DESTINATION OBJECT HAS LOADED IMAGE
	GLPP_ASSERT(source->m_lpPixels != nullptr); // STB IMAGE SOURCE OBJECT HAS NO LOADED IMAGE
	m_iByte = source->m_iByte;
	m_iComp = source->m_iComp;
	m_iWidth = source->m_iWidth;
	m_iHeight = source->m_iHeight;
}

void StbImage::_file(_LPDATA data, const char* file)
{
	GLPP_ASSERT(m_lpPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&data->file, file, "rb");
	GLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
	data->len = 0;
	if (m_lpPixels)
	{
		stbi_image_free(m_lpPixels);
	}
}

void StbImage::_h2ld(void* data)
{
	GLPP_ASSERT(m_iByte == 4); // LOADED IMAGE IS NOT HDR
	m_lpPixels = stbi__hdr_to_ldr((float*)data, m_iWidth, m_iHeight, m_iComp);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT HDR TO LDR
	m_iByte = 1;
}

int StbImage::_info(_LPDATA data)
{
	_byte(data);
	return (data->len) ?
		stbi_info_from_memory(data->buffer, data->len, &m_iWidth, &m_iHeight, &m_iComp) :
		stbi_info_from_file(data->file, &m_iWidth, &m_iHeight, &m_iComp);
}

int StbImage::_lgif(_LPDATA data, int format, int** delays)
{
	m_iByte = (format & GLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = format & GLPP_STBIMAGE_COMP;
	m_lpPixels = (data->len) ?
		stbi_load_gif_from_memory(data->buffer, data->len, delays, &m_iWidth, &m_iHeight, &iLayers, &m_iComp, iReqComp) :
		stbi_load_gif_from_file(data->file, delays, &m_iWidth, &m_iHeight, &iLayers, &m_iComp, iReqComp);
	GLPP_STBIMAGE_ASSERT; // FAILED TO LOAD GIF IMAGE
	if (iReqComp > 0)
	{
		m_iComp = iReqComp;
	}
	switch (m_iByte)
	{
	case 2:
		m_lpPixels = stbi__convert_8_to_16((stbi_uc*)m_lpPixels, m_iWidth, m_iHeight, m_iComp);
		GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
		break;

	case 4:
		m_lpPixels = stbi__ldr_to_hdr((stbi_uc*)m_lpPixels, m_iWidth, m_iHeight, m_iComp);
		GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT IMAGE
		break;

	case 0:
		m_iByte = 1;
	}
	m_iHeight *= iLayers; // Interleaved images
	return iLayers;
}

void StbImage::_l2hd(void* data)
{
	GLPP_ASSERT(m_iByte == 1); // LOADED IMAGE IS NOT LDR
	m_lpPixels = stbi__ldr_to_hdr((stbi_uc*)data, m_iWidth, m_iHeight, m_iComp);
	GLPP_STBIMAGE_ASSERT; // FAILED TO CONVERT LDR TO HDR
	m_iByte = 4;
}

void StbImage::_load(_LPDATA data, int format)
{
	m_iByte = (format & GLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = format & GLPP_STBIMAGE_COMP;
	if (m_iByte == 0) // Load original depth
	{
		_byte(data);
	}
	switch (m_iByte)
	{
	case 1: // Load 8-bit depth
		m_lpPixels = (data->len) ?
			stbi_load_from_memory(data->buffer, data->len, &m_iWidth, &m_iHeight, &m_iComp, iReqComp) :
			stbi_load_from_file(data->file, &m_iWidth, &m_iHeight, &m_iComp, iReqComp);
		break;

	case 2: // Load 16-bit depth
		m_lpPixels = (data->len) ?
			stbi_load_16_from_memory(data->buffer, data->len, &m_iWidth, &m_iHeight, &m_iComp, iReqComp) :
			stbi_load_from_file_16(data->file, &m_iWidth, &m_iHeight, &m_iComp, iReqComp);
		break;

	default: // Load 32-bit depth
		m_lpPixels = (data->len) ?
			stbi_loadf_from_memory(data->buffer, data->len, &m_iWidth, &m_iHeight, &m_iComp, iReqComp) :
			stbi_loadf_from_file(data->file, &m_iWidth, &m_iHeight, &m_iComp, iReqComp);
	}
	GLPP_STBIMAGE_ASSERT; // FAILED TO LOAD IMAGE
	if (iReqComp > 0)
	{
		m_iComp = iReqComp;
	}
}

void StbImage::_rcid(_LPDATA data, int rcid)
{
	GLPP_ASSERT(m_lpPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	data->buffer = _loadResource(rcid, &data->len);
}

bool StbImage::_resz(void* source, int ow, int oh, int rx, int ry, int rw, int rh)
{
	GLPP_ASSERT((ow > 0) && (oh > 0) && ((ow * oh) <= STBI_MAX_DIMENSIONS)); // OUTPUT IMAGE DIMENSIONS ARE INVALID
	stbir_datatype byte; // Depth
	switch (m_iByte)
	{
	case  1: byte = STBIR_TYPE_UINT8; break;
	case  2: byte = STBIR_TYPE_UINT16; break;
	default: byte = STBIR_TYPE_FLOAT; // 4
	}
	stbir_pixel_layout comp; // Channels
	switch (m_iComp)
	{
	case  1: comp = STBIR_1CHANNEL; break;
	case  2: comp = STBIR_2CHANNEL; break;
	case  3: comp = STBIR_RGB; break;
	default: comp = STBIR_RGBA; // 4
	}
	STBIR_RESIZE resize;
	m_lpPixels = GLPP_MALLOC(static_cast<size_t>(ow) * oh * m_iByte * m_iComp);
	stbir_resize_init(&resize, source, m_iWidth, m_iHeight, 0, m_lpPixels, ow, oh, 0, comp, byte);
	stbir_set_edgemodes(&resize, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP);
	stbir_set_filters(&resize, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT);
	double s0 = (double)rx / m_iWidth;
	double t0 = (double)ry / m_iHeight;
	double s1 = s0 + (double)rw / m_iWidth;
	double t1 = t0 + (double)rh / m_iHeight;
	GLPP_ASSERT(stbir_set_input_subrect(&resize, s0, t0, s1, t1)); // THE IMAGE REGION IN NOT INBOUND
 	m_iWidth = ow;
	m_iHeight = oh;
	return (bool)stbir_resize_extended(&resize);
}

StbImage::StbImage()
{
	m_iByte = 0;
	m_iComp = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	m_lpPixels = nullptr;
}

void StbImage::convert(_In_ const StbImage& source, StbFormat format)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_conv(source.m_lpPixels, (int)format);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
}

void StbImage::convert16To8(_In_ const StbImage& source)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_c168(source.m_lpPixels);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
}

void StbImage::convert8To16(_In_ const StbImage& source)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_c816(source.m_lpPixels);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
}

void StbImage::convertFormat(_In_ const StbImage& source, StbFormat format)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_cf08(source.m_lpPixels, (int)format);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
}

void StbImage::convertFormat16(_In_ const StbImage& source, StbFormat format)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_cf16(source.m_lpPixels, (int)format);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
}

void StbImage::convertIphonePngToRgb(bool convert)
{
	stbi_convert_iphone_png_to_rgb((int)convert);
}

void StbImage::copy(_In_ const StbImage& source)
{
	_copy(&source);
	size_t iSize = static_cast<size_t>(m_iWidth) * m_iHeight * m_iComp * m_iByte;
	m_lpPixels = GLPP_MALLOC(iSize);
	memcpy(m_lpPixels, source.m_lpPixels, iSize);
}

void StbImage::copyRegion(_In_ const StbImage& source, int rleft, int rtop, int rwidth, int rheight)
{
	_copy(&source);
	GLPP_ASSERT((rwidth > 0) && (rleft >= 0) && (m_iWidth >= (rleft + rwidth))); // INVALID WIDTH OR LEFT PARAMETERS OF ALLOCATING SPRITE
	GLPP_ASSERT((rheight > 0) && (rtop >= 0) && (m_iHeight >= (rtop + rheight))); // INVALID HEIGHT OR TOP PARAMETERS OF ALLOCATING SPRITE
	int iDstPos = 0,
		iPixel = m_iByte * m_iComp,
		iDstLine = rwidth * iPixel,
		iSrcLine = m_iWidth * iPixel,
		iSrcPos = (iSrcLine * rtop) + (rleft * iPixel);
	m_lpPixels = GLPP_MALLOC(static_cast<size_t>(iDstLine) * rheight);
	for (int iHscan = 0; iHscan < rheight; iHscan++)
	{
		memcpy((char*)m_lpPixels + iDstPos, (char*)source.m_lpPixels + iSrcPos, iDstLine);
		iDstPos += iDstLine;
		iSrcPos += iSrcLine;
	}
	m_iWidth = rwidth;
	m_iHeight = rheight;
}

void StbImage::copySprite(_In_ const StbImage& source, int width, int height, int index)
{
	int iCol = source.m_iWidth / width, iRemC = source.m_iWidth % width; // Number of sprites in row + reminder
	int iRow = source.m_iHeight / height, iRemR = source.m_iHeight % height; // Number of rows in image + reminder
	GLPP_ASSERT((iRemC == 0) && (iRemR == 0) && (index < (iCol* iRow))); // SPRITE CANNOT FIT INTO THE IMAGE
	int iTop = index / iCol, iLeft = index % iCol; // Find sprite position in image
	return copyRegion(source, iLeft * width, iTop * height, width, height);
}

void StbImage::create(int width, int height, StbFormat format, bool init)
{
	GLPP_ASSERT(m_lpPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	GLPP_ASSERT((width > 0) && (height > 0) && ((width * height) <= STBI_MAX_DIMENSIONS)); // IMAGE DIMENSIONS ARE INVALID
	m_iWidth = width;
	m_iHeight = height;
	m_iByte = ((int)format & GLPP_STBIMAGE_BYTE) >> 4;
	m_iComp = (int)format & GLPP_STBIMAGE_COMP;
	GLPP_ASSERT((m_iByte > 0) && (m_iComp > 0)); // IMAGE PIXEL FORMAT MUST BE NON-DEFAULT
	int iSize = m_iWidth * m_iHeight * m_iByte * m_iComp;
	m_lpPixels = (init) ? GLPP_CALLOC(iSize) : GLPP_MALLOC(iSize);
}

void StbImage::flipVerticallyOnWrite(bool flip)
{
	stbi_flip_vertically_on_write((int)flip);
}

void StbImage::hdrToLdr(_In_ const StbImage& source)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_h2ld(source.m_lpPixels);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
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
	m_iByte = 0;
	m_iComp = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	m_lpPixels = nullptr;
}

bool StbImage::info(int rcid)
{
	_DATA data;
	_rcid(&data, rcid);
	return (bool)_info(&data);
}

bool StbImage::info(_In_z_ const char* file)
{
	_DATA data;
	_file(&data, file);
	bool bResult = (bool)_info(&data);
	fclose(data.file);
	return bResult;
}

void StbImage::ldrToHdr(_In_ const StbImage& source)
{
	_copy(&source);
	GLPP_STBIMAGE_TLSLOCK = source.m_lpPixels;
	_l2hd(source.m_lpPixels);
	GLPP_STBIMAGE_TLSLOCK = nullptr;
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
	_DATA data;
	_rcid(&data, rcid);
	_load(&data, (int)format);
}

void StbImage::load(_In_z_ const char* file, StbFormat format)
{
	_DATA data;
	_file(&data, file);
	_load(&data, (int)format);
	fclose(data.file);
}

int StbImage::loadGif(int rcid, _Outptr_opt_ int** delays, StbFormat format)
{
	_DATA data;
	_rcid(&data, rcid);
	return _lgif(&data, (int)format, delays);
}

int StbImage::loadGif(_In_z_ const char* file, _Outptr_opt_ int** delays, StbFormat format)
{
	_DATA data;
	_file(&data, file);
	int iLayers = _lgif(&data, (int)format, delays);
	fclose(data.file);
	return iLayers;
}

bool StbImage::resizeRegion(int width, int height, int rleft, int rtop, int rwidth, int rheight)
{
	void* lpSource = getPixels();
	bool bResult = _resz(lpSource, width, height, rleft, rtop, rwidth, rheight);
	stbi_image_free(lpSource);
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

void StbImage::verticalFlip()
{
	stbi__vertical_flip(getPixels(), m_iWidth, m_iHeight, m_iComp * m_iByte);
}

void StbImage::verticalFlipSlices(int layers)
{
	stbi__vertical_flip_slices(getPixels(), m_iWidth, m_iHeight, layers, m_iComp * m_iByte);
}

void StbImage::writeForcePngFilter(int filter)
{
	GLPP_ASSERT((filter >= -1) && (filter <= 5)); // INVALID PNG FILTER MODE PARAMETER
	stbi_write_force_png_filter = filter;
}

bool StbImage::writeBmp(_In_z_ const char* filepath)
{
	GLPP_ASSERT(m_iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_bmp(filepath, m_iWidth, m_iHeight, m_iComp, getPixels());
}

bool StbImage::writeHdr(_In_z_ const char* filepath)
{
	GLPP_ASSERT(m_iByte == 4); // STB IMAGE DATA MUST BE 32F-BITS PER CHANNEL
	return (bool)stbi_write_hdr(filepath, m_iWidth, m_iHeight, m_iComp, (float*)getPixels());
}

bool StbImage::writeJpg(_In_z_ const char* filepath)
{
	GLPP_ASSERT(m_iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_jpg(filepath, m_iWidth, m_iHeight, m_iComp, getPixels(), GLPP_STBIMAGE_JPEG);
}

void StbImage::writeJpegQuality(int quality)
{
	GLPP_ASSERT((quality >= 1) && (quality <= 100)); // INVALID JPEG QUALITY PARAMETER
	GLPP_STBIMAGE_JPEG = quality;
}

bool StbImage::writePng(_In_z_ const char* filepath)
{
	GLPP_ASSERT(m_iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_png(filepath, m_iWidth, m_iHeight, m_iComp, getPixels(), m_iWidth * m_iComp);
}

void StbImage::writePngCompressionLevel(int comp)
{
	GLPP_ASSERT((comp >= 0) && (comp <= 9)); // INVALID PNG COMPESSION LEVEL PARAMETER
	stbi_write_png_compression_level = comp;
}

bool StbImage::writeTga(_In_z_ const char* filepath)
{
	GLPP_ASSERT(m_iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_tga(filepath, m_iWidth, m_iHeight, m_iComp, getPixels());
}

void StbImage::writeTgaWithRle(bool rle)
{
	stbi_write_tga_with_rle = (int)rle;
}

#ifdef _DEBUG
_Ret_notnull_ void* StbImage::getPixels()
{
	GLPP_ASSERT(m_lpPixels != nullptr); // STB IMAGE OBJECT HAS NO LOADED IMAGE
	return m_lpPixels;
}
#endif // #ifdef _DEBUG
