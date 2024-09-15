#pragma once
#include <yaglpp/glpp.h>
/*YAGL++ stb_image I/O callback structure*/
struct StbCallbacks
{
	/*Fills 'data' with 'size' bytes. Returns number of bytes actually read*/
	int (*read)(void* user, char* data, int size);

	/*Skips the next 'n' bytes, or 'unget' the last -n bytes if negative*/
	void (*skip)(void* user, int n);

	/*Returns nonzero if at end of file/data*/
	int (*eof)(void* user);
};

/*YAGL++ stb_image pixel format enumerator*/
enum class StbFormat : int
{
	/*Default channels per pixel and channel depth*/
	Default = 0x00,

	/*One channel per pixel with the default channel depth: grey*/
	Grey = 0x01,

	/*Two channels per pixel with the default channel depth, alpha*/
	GreyAlpha = 0x02,

	/*Three channels per pixel with the default channel depth: red, green, blue*/
	Rgb = 0x03,

	/*Four channels per pixel with the default channel depth: red, green, blue, alpha*/
	RgbAlpha = 0x04,

	/*Unsigned 8-bit channel depth with the default channels per pixel*/
	Unsigned8 = 0x10,

	/*One unsigned 8-bit channel per pixel: grey-8u*/
	Grey8 = 0x11,

	/*Two unsigned 8-bit channels per pixel: grey-8u, alpha-8u*/
	GreyAlpha8 = 0x12,

	/*Three unsigned 8-bit channels per pixel: red-8u, green-8u, blue-8u*/
	Rgb8 = 0x13,

	/*Four unsigned 8-bit channels per pixel: red-8u, green-8u, blue-8u, alpha-8u*/
	RgbAlpha8 = 0x14,

	/*Unsigned 16-bit channel depth with the default channels per pixel*/
	Unsigned16 = 0x20,

	/*One unsigned 16-bit channel per pixel: grey-16u*/
	Grey16 = 0x21,

	/*Two unsigned 16-bit channels per pixel: grey-16u, alpha-16u*/
	GreyAlpha16 = 0x22,

	/*Three unsigned 16-bit channels per pixel: red-16u, green-16u, blue-16u*/
	Rgb16 = 0x23,

	/*Four unsigned 16-bit channels per pixel: red-16u, green-16u, blue-16u, alpha-16u*/
	RgbAlpha16 = 0x24,

	/*Float 32-bit channel depth with the default channels per pixel*/
	Float32 = 0x40,

	/*One float 32-bit channel per pixel: grey-32f*/
	GreyF = 0x41,

	/*Two float 32-bit channels per pixel: grey-32f, alpha-32f*/
	GreyAlphaF = 0x42,

	/*Three float 32-bit channels per pixel: red-32f, green-32f, blue-32f*/
	RgbF = 0x43,

	/*Four float 32-bit channels per pixel: red-32f, green-32f, blue-32f, alpha-32f*/
	RgbAlphaF = 0x44,
};

/*YAGL++ stb_image helper root class*/
class StbImage
{
private:
	// Thread object member data structure
	struct _MDATA {
		int iByte; // Bytes p/channel
		int iComp; // Channels p/pixel
		int iWidth; // Image width
		int iHeight; // Image height
		void* pPixels; // Pixel data
	} _m;

public:
	/*(1) Constructs an empty StbImage object*/
	StbImage()
	{
		memset(&_m, 0, sizeof(_MDATA));
	}

	/*(2) Constructs a copy StbImage object with <copy>*/
	StbImage(const StbImage& source) : StbImage()
	{
		copy(source);
	}

	/*(3) Constructs a copy StbImage object with <copySprite>*/
	StbImage(const StbImage& source, int width, int height, int index) : StbImage()
	{
		copySprite(source, width, height, index);
	}

	/*(4) Constructs a copy StbImage object with <copyRegion>*/
	StbImage(const StbImage& source, int rleft, int rtop, int rwidth, int rheight) : StbImage()
	{
		copyRegion(source, rleft, rtop, rwidth, rheight);
	}

	/*(5) Constructs StbImage object with <load>*/
	StbImage(int rcid, StbFormat format = StbFormat::Default) : StbImage()
	{
		load(rcid, format);
	}

	/*(6) Constructs StbImage object with <load>*/
	StbImage(_In_z_ const char* file, StbFormat format = StbFormat::Default) : StbImage()
	{
		load(file, format);
	}

	/*(7) Constructs StbImage object with <load>*/
	StbImage(_In_ StbCallbacks const* clbk, _In_ void* user, StbFormat format = StbFormat::Default) : StbImage()
	{
		load(clbk, user, format);
	}

	/*Cleans up the StbImage object*/
	~StbImage()
	{
		if (isStbImage())
		{
			imageFree();
		}
	}

	/*Sets the global flag indicating whether to process iphone images back to canonical format, or pass them through as is
	@param True to convert BGR to RGB for PNG files, default false*/
	static void convertIphonePngToRgb(bool convert);

	/*Copies the source StbImage object
	@param [in] The source StbImage object*/
	void copy(const StbImage& source);

	/*(1) Copies a region of currently loaded image replacing the old image
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region*/
	void copyRegion(int rleft, int rtop, int rwidth, int rheight)
	{
		copyRegion(*this, rleft, rtop, rwidth, rheight);
	}

	/*(2) Copies a region of the image currently loaded into the source StbImage object
	@param [in] The source StbImage object
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region*/
	void copyRegion(const StbImage& source, int rleft, int rtop, int rwidth, int rheight);

	/*Duplicates one of the inbound sprites in the source StbImage object selected by index value. The sprite's dimentions must by multiple of the image's dimentions, and remain the same within the image
	@param The width of the sprite
	@param The height of the sprite
	@param The index of the sprite*/
	void copySprite(const StbImage& source, int width, int height, int index);

	/*Creates an empty image pixel data array within StbImage object. The object must be empty, and the pixel format has to be determined, which means no default values such as <Rgb> or <Unsigned8> should be used
	@param The new image width
	@param The new image height
	@param The new image format
	@param True to initialize the memory block with zeros, default false*/
	void create(int width, int height, StbFormat format, bool init = false);

	/*Sets the global image writing direction flag
	@param True to set writing direction from bottom to top, default false*/
	static void flipVerticallyOnWrite(bool flip);

	/*Gets the number of channels per pixel of loaded or queried image. Possible values are: <Grey>, <GreyAlpha>, <Rgb> or <RgbAlpha>
	@return The number of channels per pixel*/
	StbFormat getChannels() const
	{
		return (StbFormat)_m.iComp;
	}

	/*Gets the channel depth of loaded or queried image. Possible values are: <Unsigned8>, <Unsigned16> or <Float32>
	@return The pixel channel depth*/
	StbFormat getDepth() const
	{
		return (StbFormat)(_m.iByte << 4);
	}

	/*Gets the number of channels per pixel and the channel depth of loaded or queried image
	@return The pixel format*/
	StbFormat getFormat() const
	{
		return (StbFormat)((_m.iByte << 4) | _m.iComp);
	}

	/*Gets the height of last loaded or queried image. The multi-image height is multiplied by the number of layers
	@return The image height in pixels*/
	int getHeight() const
	{
		return _m.iHeight;
	}

	/*Gets a pointer to the pixel array of last loaded image
	@return Pointer to the image pixel array*/
	_Ret_notnull_ void* getPixels() const;

	/*Gets the width of last loaded or queried image
	@return The image width in pixels*/
	int getWidth() const
	{
		return _m.iWidth;
	}

	/*Sets the global gamma value used in hdr-to-ldr conversion
	@param New hdr-to-ldr gamma value, default 1/2.2f*/
	static void hdrToLdrGamma(float gamma);

	/*Sets the global scale value used in hdr-to-ldr conversion
	@param New hdr-to-ldr scale value, default 1.0f*/
	static void hdrToLdrScale(float scale);

	/*Unloads previously loaded image and reset StbImage object*/
	void imageFree();

	/*(1) Retrives image binary resource information. Sets width, height and pixel format without image loading
	@param The image binary resource id of <RCDATA> type
	@return True if image information loaded successfully, false otherwise*/
	bool info(int rcid);

	/*(2) Retrives image file information. Sets width, height and pixel format without image loading
	@param [in] Path to the image file
	@return True if image information loaded successfully, false otherwise*/
	bool info(_In_z_ const char* file);

	/*(3) Retrives image information using I/O callback while reading from arbitrary sources. Sets width, height and pixel format without image loading
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@return True if image information loaded successfully, false otherwise*/
	bool info(_In_ StbCallbacks const* clbk, _In_ void* user);

	/*(1) Checks if the binary resource is a 16-bit image
	@param The image binary resource id of <RCDATA> type
	@return True if binary resource is 16-bit image, false otherwise*/
	static bool is16bit(int rcid);

	/*(2) Checks if the file is a 16-bit image
	@param [in] Path to the image file
	@return True if file is 16-bit image, false otherwise*/
	static bool is16bit(_In_z_ const char* file);

	/*(3) Checks if the image is 16-bit using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@return True if file is 16-bit image, false otherwise*/
	static bool is16bit(_In_ StbCallbacks const* clbk, _In_ void* user);

	/*(1) Checks if the binary resource is a 32-bit float image
	@param The image binary resource id of <RCDATA> type
	@return True if binary resource is 32-bit float image, false otherwise*/
	static bool isHdr(int rcid);

	/*(2) Checks if the file is a 32-bit float image
	@param [in] Path to the image file
	@return True if file is 32-bit float image, false otherwise*/
	static bool isHdr(_In_z_ const char* file);

	/*(3) Checks if the image is 32-bit float using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@return True if file is 32-bit float image, false otherwise*/
	static bool isHdr(_In_ StbCallbacks const* clbk, _In_ void* user);

	/*Checks if the StbImage object has loaded image
	@return True if the image is loaded, false otherwise*/
	bool isStbImage() const
	{
		return _m.pPixels != nullptr;
	}

	/*Sets the global gamma value used in ldr-to-hdr conversion
	@param New ldr-to-hdr gamma value, default 2.2f*/
	static void ldrToHdrGamma(float gamma);

	/*Sets the global scale value used in ldr-to-hdr conversion
	@param New ldr-to-hdr scale value, default 1.0f*/
	static void ldrToHdrScale(float scale);

	/*(1) Loads image binary resource
	@param The image resource id of <RCDATA> type
	@param The storing pixel format, default is the image source pixel format*/
	void load(int rcid, StbFormat format = StbFormat::Default);

	/*(2) Loads image from file
	@param [in] Path to the image file
	@param The storing pixel format, default is the image source pixel format*/
	void load(_In_z_ const char* file, StbFormat format = StbFormat::Default);

	/*(3) Loads image using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param The storing pixel format, default is the image source pixel format*/
	void load(_In_ StbCallbacks const* clbk, _In_ void* user, StbFormat format = StbFormat::Default);

	/*(1) Loads GIF image binary resource
	@param The image resource id of <RCDATA> type
	@param [out] Pointer to the array of image delays
	@param The storing pixel format, default is the image source pixel format
	@return The number of loaded layers*/
	int loadGif(int rcid, _Outptr_opt_ int** delays, StbFormat format = StbFormat::Default);

	/*(2) Loads GIF image from file
	@param [in] Path to the image file
	@param [out] Pointer to the array of image delays
	@param The storing pixel format, default is the image source pixel format
	@return The number of loaded layers*/
	int loadGif(_In_z_ const char* file, _Outptr_opt_ int** delays, StbFormat format = StbFormat::Default);

	/*(3) Loads GIF image using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param [out] Pointer to the array of image delays
	@param The storing pixel format, default is the image source pixel format
	@return The number of loaded layers*/
	int loadGif(_In_ StbCallbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays, StbFormat format = StbFormat::Default);

	/*(1) Resizes loaded image replacing the current image
	@param The width of a new image
	@param The height of a new image
	@return True if success, false otherwise*/
	bool resize(int width, int height)
	{
		return resizeRegion(width, height, 0, 0, _m.iWidth, _m.iHeight);
	}

	/*(2) Resizes an image loaded into the source StbImage object
	@param [in] The source StbImage object
	@param The width of a new image
	@param The height of a new image
	@return True if success, false otherwise*/
	bool resize(const StbImage& source, int width, int height)
	{
		return resizeRegion(source, width, height, 0, 0, source._m.iWidth, source._m.iHeight);
	}

	/*(1) Resizes a region of loaded image replacing the current image
	@param The width of a new image
	@param The height of a new image
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region
	@return True if success, false otherwise*/
	bool resizeRegion(int width, int height, int rleft, int rtop, int rwidth, int rheight)
	{
		return resizeRegion(*this, width, height, rleft, rtop, rwidth, rheight);
	}

	/*(2) Resizes a region of the image loaded into the source StbImage object
	@param [in] The source StbImage object
	@param The width of a new image
	@param The height of a new image
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region
	@return True if success, false otherwise*/
	bool resizeRegion(const StbImage& source, int width, int height, int rleft, int rtop, int rwidth, int rheight);

	/*Sets the global image loading direction flag
	@param True to set loading direction from bottom to top, default false*/
	static void setFlipVerticallyOnLoad(bool flip);

	/*Sets the global image loading alpha unpremultiplication flag
	@param True to force removing any premultiplied alpha, default false*/
	static void setUnpremultiplyOnLoad(bool unpremultiply);

	/*Sets the global PNG filter mode value. Forces the PNG filter mode if from 0 to 5
	@param The new filter mode value, default -1*/
	static void writeForcePngFilter(int filter);

	/*Writes currently loaded image into the BMP file. The image data must be 8-bit per channel
	@param [in] Path to the written BMP file
	@return True if operation successful, false otherwise*/
	bool writeBmp(_In_z_ const char* filepath);

	/*Writes currently loaded image into the HDR file. The image data must be 32f-bit per channel
	@param [in] Path to the written HDR file
	@return True if operation successful, false otherwise*/
	bool writeHdr(_In_z_ const char* filepath);

	/*Writes currently loaded image into the JPG file. The image data must be 8-bit per channel
	@param [in] Path to the written JPG file*/
	bool writeJpg(_In_z_ const char* filepath);

	/*Sets global JPEG quality value for writing JPG files. Higher value gives more quality, must be 1..100
	@param The new JPEG quality value, default 80*/
	static void writeJpegQuality(int quality);

	/*Writes currently loaded image into the PNG file. The image data must be 8-bit per channel
	@param [in] Path to the written PNG file
	@return True if operation successful, false otherwise*/
	bool writePng(_In_z_ const char* filepath);

	/*Sets global PNG compession level value for writing PNG files. Higher value gives more compression, must be 0..9
	@param The new PNG compession level value, default 8*/
	static void writePngCompressionLevel(int comp);

	/*Writes currently loaded image into the TGA file. The image data must be 8-bit per channel
	@param [in] Path to the written TGA file
	@return True if operation successful, false otherwise*/
	bool writeTga(_In_z_ const char* filepath);

	/*Sets global RLE compression flag for writing TGA files. Default true
	@param True to enable RLE, false otherwise*/
	static void writeTgaWithRle(bool rle);

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for number of channels per pixel*/
	__declspec(property(get = getChannels)) StbFormat channels;

	/*Read-only property for channel depth of loaded or queried image*/
	__declspec(property(get = getDepth)) StbFormat depth;

	/*Read-only property for number of channels per pixel and the channel depth of loaded or queried image*/
	__declspec(property(get = getFormat)) StbFormat format;

	/*Read-only property for height of last loaded image*/
	__declspec(property(get = getHeight)) int height;

	/*Read-only property for pointer to the pixel array of last loaded image*/
	__declspec(property(get = getPixels)) void* pixels;

	/*Read-only property to check if the StbImage object has loaded image*/
	__declspec(property(get = isStbImage)) bool stbImage;

	/*Read-only property for width of last loaded image*/
	__declspec(property(get = getWidth)) int width;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class StbImage

#ifdef YAGLPP_IMPLEMENTATION
#define YAGLPP_STBIMAGE_BYTE 0xF0
#define YAGLPP_STBIMAGE_COMP 0x0F

#ifdef _DEBUG
#define STBI_FAILURE_USERMSG
#define YAGLPP_STBIMAGE_ASSERT if (_m.pPixels == nullptr) { std::cout << "STB IMAGE ERROR: " << stbi_failure_reason() << std::endl; YAGLPP_ASSERT(false); }
#else // #ifdef _DEBUG
#define STBI_NO_FAILURE_STRINGS
#define YAGLPP_STBIMAGE_ASSERT
#endif // #ifdef _DEBUG

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(e) YAGLPP_ASSERT(e)
#define STBI_MALLOC(s) YAGLPP_MALLOC(s)
#define STBI_REALLOC(p,s) YAGLPP_REALLOC(p,s)
#define STBI_FREE(p) YAGLPP_FREE(p)
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STBIR_ASSERT(e) YAGLPP_ASSERT(e)
#define STBIR_FREE(p,c) ((void)(c), YAGLPP_FREE(p))
#define STBIR_MALLOC(s,c) ((void)(c), YAGLPP_MALLOC(s))
#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(e) YAGLPP_ASSERT(e)
#define STBIW_FREE(p) YAGLPP_FREE(p)
#define STBIW_MALLOC(s) YAGLPP_MALLOC(s)
#define STBIW_REALLOC(p,s) YAGLPP_REALLOC(p,s)
#endif // #ifdef YAGLPP_IMPLEMENTATION

#include <stb/stb_image.h> // v2.29
#include <stb/stb_image_resize2.h> // v2.06
#include <stb/stb_image_write.h> // v1.16
static int YAGLPP_STBIMAGE_JPEG = 80;
inline void StbImage::convertIphonePngToRgb(bool convert)
{
	stbi_convert_iphone_png_to_rgb((int)convert);
}

inline void StbImage::flipVerticallyOnWrite(bool flip)
{
	stbi_flip_vertically_on_write((int)flip);
}

inline void StbImage::hdrToLdrGamma(float gamma)
{
	stbi_hdr_to_ldr_gamma(gamma);
}

inline void StbImage::hdrToLdrScale(float scale)
{
	stbi_hdr_to_ldr_scale(scale);
}

inline void StbImage::imageFree()
{
	stbi_image_free(getPixels()); memset(&_m, 0, sizeof(_MDATA));
}

inline bool StbImage::is16bit(int rcid)
{
	int iLen; return (bool)stbi_is_16_bit_from_memory(_loadResource(rcid, &iLen), iLen);
}

inline bool StbImage::is16bit(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user);
}

inline bool StbImage::isHdr(int rcid)
{
	int iLen; return (bool)stbi_is_hdr_from_memory(_loadResource(rcid, &iLen), iLen);
}

inline bool StbImage::isHdr(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user);
}

inline void StbImage::ldrToHdrGamma(float gamma)
{
	stbi_ldr_to_hdr_gamma(gamma);
}

inline void StbImage::ldrToHdrScale(float scale)
{
	stbi_ldr_to_hdr_scale(scale);
}

inline void StbImage::setFlipVerticallyOnLoad(bool flip)
{
	stbi_set_flip_vertically_on_load((int)flip);
}

inline void StbImage::setUnpremultiplyOnLoad(bool unpremultiply)
{
	stbi_set_unpremultiply_on_load((int)unpremultiply);
}

inline void StbImage::writeTgaWithRle(bool rle)
{
	stbi_write_tga_with_rle = (int)rle;
}

#ifdef YAGLPP_IMPLEMENTATION
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

void StbImage::copy(const StbImage& source)
{
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE DESTINATION OBJECT HAS LOADED IMAGE
	void* lpSource = source.getPixels(); // Pixels
	_m.iByte = source._m.iByte;
	_m.iComp = source._m.iComp;
	_m.iWidth = source._m.iWidth;
	_m.iHeight = source._m.iHeight;
	size_t iSize = static_cast<size_t>(_m.iWidth) * _m.iHeight * _m.iComp * _m.iByte;
	_m.pPixels = YAGLPP_MALLOC(iSize);
	memcpy(_m.pPixels, lpSource, iSize);
}

void StbImage::copyRegion(const StbImage& source, int rleft, int rtop, int rwidth, int rheight)
{
	YAGLPP_ASSERT((this == &source) || (_m.pPixels == nullptr)); // STB DESTINATION IMAGE OBJECT HAS LOADED IMAGE
	void* lpSource = source.getPixels(); // Pixels
	_m.iByte = source._m.iByte;
	_m.iComp = source._m.iComp;
	YAGLPP_ASSERT((rwidth > 0) && (rleft >= 0) && (source._m.iWidth >= (rleft + rwidth))); // INVALID WIDTH OR LEFT PARAMETERS OF ALLOCATING SPRITE
	YAGLPP_ASSERT((rheight > 0) && (rtop >= 0) && (source._m.iHeight >= (rtop + rheight))); // INVALID HEIGHT OR TOP PARAMETERS OF ALLOCATING SPRITE
	int iDstPos = 0,
		iPixel = _m.iByte * _m.iComp,
		iDstLine = rwidth * iPixel,
		iSrcLine = source._m.iWidth * iPixel,
		iSrcPos = (iSrcLine * rtop) + (rleft * iPixel);
	_m.pPixels = YAGLPP_MALLOC(static_cast<size_t>(iDstLine) * rheight);
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
	YAGLPP_ASSERT((iRemC == 0) && (iRemR == 0) && (index < (iCol* iRow))); // SPRITE CANNOT FIT INTO THE IMAGE
	int iTop = index / iCol, iLeft = index % iCol; // Find sprite position in image
	return copyRegion(source, iLeft * width, iTop * height, width, height);
}

void StbImage::create(int width, int height, StbFormat format, bool init)
{
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	YAGLPP_ASSERT((width > 0) && (height > 0) && ((width * height) <= STBI_MAX_DIMENSIONS)); // IMAGE DIMENSIONS ARE INVALID
	_m.iWidth = width;
	_m.iHeight = height;
	_m.iByte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	_m.iComp = (int)format & YAGLPP_STBIMAGE_COMP;
	YAGLPP_ASSERT((_m.iByte > 0) && (_m.iComp > 0)); // IMAGE PIXEL FORMAT MUST BE NON-DEFAULT
	int iSize = _m.iWidth * _m.iHeight * _m.iByte * _m.iComp;
	_m.pPixels = (init) ? YAGLPP_CALLOC(iSize) : YAGLPP_MALLOC(iSize);
}

bool StbImage::info(int rcid)
{
	int iLen;
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	unsigned char* pBuffer = _loadResource(rcid, &iLen);
	_m.iByte =
		(stbi_is_hdr_from_memory(pBuffer, iLen)) ? 4 :
		(stbi_is_16_bit_from_memory(pBuffer, iLen)) ? 2 : 1;
	return (bool)stbi_info_from_memory(pBuffer, iLen, &_m.iWidth, &_m.iHeight, &_m.iComp);
}

bool StbImage::info(_In_z_ const char* file)
{
	FILE* pFile;
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
	_m.iByte =
		(stbi_is_hdr_from_file(pFile)) ? 4 :
		(stbi_is_16_bit_from_file(pFile)) ? 2 : 1;
	bool bResult = (bool)stbi_info_from_file(pFile, &_m.iWidth, &_m.iHeight, &_m.iComp);
	fclose(pFile);
	return bResult;
}

bool StbImage::info(_In_ StbCallbacks const* clbk, _In_ void* user)
{
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	_m.iByte =
		(stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 4 :
		(stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 2 : 1;
	return (bool)stbi_info_from_callbacks((stbi_io_callbacks*)clbk, user, &_m.iWidth, &_m.iHeight, &_m.iComp);
}

bool StbImage::is16bit(_In_z_ const char* file)
{
	FILE* pFile;
	errno_t iError = fopen_s(&pFile, file, "rb");
	YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
	bool bResult = (bool)stbi_is_16_bit_from_file(pFile);
	fclose(pFile);
	return bResult;
}

bool StbImage::isHdr(_In_z_ const char* file)
{
	FILE* pFile;
	errno_t iError = fopen_s(&pFile, file, "rb");
	YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
	bool bResult = (bool)stbi_is_hdr_from_file(pFile);
	fclose(pFile);
	return bResult;
}

void StbImage::load(int rcid, StbFormat format)
{
	int iLen;
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
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
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
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
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
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
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
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
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
	errno_t iError = fopen_s(&pFile, file, "rb");
	YAGLPP_ASSERT(iError == 0); // FAILED TO LOAD IMAGE FILE
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
	YAGLPP_ASSERT(_m.pPixels == nullptr); // STB IMAGE OBJECT HAS LOADED IMAGE
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
	YAGLPP_ASSERT((this == &source) || (_m.pPixels == nullptr)); // STB DESTINATION IMAGE OBJECT HAS LOADED IMAGE
	YAGLPP_ASSERT((width > 0) && (height > 0) && ((width * height) <= STBI_MAX_DIMENSIONS)); // OUTPUT IMAGE DIMENSIONS ARE INVALID
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
	_m.pPixels = YAGLPP_MALLOC(static_cast<size_t>(width) * height * _m.iByte * _m.iComp);
	stbir_resize_init(&resize, lpSource, source._m.iWidth, source._m.iHeight, 0, _m.pPixels, width, height, 0, comp, byte);
	stbir_set_edgemodes(&resize, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP);
	stbir_set_filters(&resize, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT);
	double s0 = (double)rleft / source._m.iWidth;
	double t0 = (double)rtop / source._m.iHeight;
	double s1 = s0 + (double)rwidth / source._m.iWidth;
	double t1 = t0 + (double)rheight / source._m.iHeight;
	YAGLPP_ASSERT(stbir_set_input_subrect(&resize, s0, t0, s1, t1)); // THE IMAGE REGION IN NOT INBOUND
	bool bResult = (bool)stbir_resize_extended(&resize);
	_m.iWidth = width;
	_m.iHeight = height;
	if (this == &source)
	{
		STBI_FREE(lpSource);
	}
	return bResult;
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
_Ret_notnull_ void* StbImage::getPixels() const
{
	YAGLPP_ASSERT(_m.pPixels != nullptr); // STB IMAGE OBJECT HAS NO LOADED IMAGE
	return _m.pPixels;
}

bool StbImage::writeBmp(_In_z_ const char* filepath)
{
	YAGLPP_ASSERT(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_bmp(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}

void StbImage::writeForcePngFilter(int filter)
{
	YAGLPP_ASSERT((filter >= -1) && (filter <= 5)); // INVALID PNG FILTER MODE PARAMETER
	stbi_write_force_png_filter = filter;
}

bool StbImage::writeHdr(_In_z_ const char* filepath)
{
	YAGLPP_ASSERT(_m.iByte == 4); // STB IMAGE DATA MUST BE 32F-BITS PER CHANNEL
	return (bool)stbi_write_hdr(filepath, _m.iWidth, _m.iHeight, _m.iComp, (float*)getPixels());
}

bool StbImage::writeJpg(_In_z_ const char* filepath)
{
	YAGLPP_ASSERT(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_jpg(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), YAGLPP_STBIMAGE_JPEG);
}

void StbImage::writeJpegQuality(int quality)
{
	YAGLPP_ASSERT((quality >= 1) && (quality <= 100)); // INVALID JPEG QUALITY PARAMETER
	YAGLPP_STBIMAGE_JPEG = quality;
}

bool StbImage::writePng(_In_z_ const char* filepath)
{
	YAGLPP_ASSERT(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_png(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), _m.iWidth * _m.iComp);
}

void StbImage::writePngCompressionLevel(int comp)
{
	YAGLPP_ASSERT((comp >= 0) && (comp <= 9)); // INVALID PNG COMPESSION LEVEL PARAMETER
	stbi_write_png_compression_level = comp;
}

bool StbImage::writeTga(_In_z_ const char* filepath)
{
	YAGLPP_ASSERT(_m.iByte == 1); // STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	return (bool)stbi_write_tga(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}
#endif // YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline _Ret_notnull_ void* StbImage::getPixels() const
{
	return _m.pPixels;
}

inline bool StbImage::writeBmp(_In_z_ const char* filepath)
{
	return (bool)stbi_write_bmp(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}

inline void StbImage::writeForcePngFilter(int filter)
{
	stbi_write_force_png_filter = filter;
}

inline bool StbImage::writeHdr(_In_z_ const char* filepath)
{
	return (bool)stbi_write_hdr(filepath, _m.iWidth, _m.iHeight, _m.iComp, (float*)getPixels());
}

inline bool StbImage::writeJpg(_In_z_ const char* filepath)
{
	return (bool)stbi_write_jpg(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), YAGLPP_STBIMAGE_JPEG);
}

inline void StbImage::writeJpegQuality(int quality)
{
	YAGLPP_STBIMAGE_JPEG = quality;
}

inline bool StbImage::writePng(_In_z_ const char* filepath)
{
	return (bool)stbi_write_png(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels(), _m.iWidth * _m.iComp);
}

inline void StbImage::writePngCompressionLevel(int comp)
{
	stbi_write_png_compression_level = comp;
}

inline bool StbImage::writeTga(_In_z_ const char* filepath)
{
	return (bool)stbi_write_tga(filepath, _m.iWidth, _m.iHeight, _m.iComp, getPixels());
}
#endif // YAGLPP_INLINE_IMPLEMENTATION
