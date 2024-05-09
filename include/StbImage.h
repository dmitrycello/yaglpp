#pragma once
#include "glpp.h"
/*glpp stb_image callback structure*/
typedef struct
{
	/*Fills 'data' with 'size' bytes. Returns number of bytes actually read*/
	int (*read)(void* user, char* data, int size);

	/*Skips the next 'n' bytes, or 'unget' the last -n bytes if negative*/
	void (*skip)(void* user, int n);

	/*Returns nonzero if at end of file/data*/
	int (*eof)(void* user);
} StbCallbacks;

/*glpp stb_image pixel format enumerator*/
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

/*glpp stb_image helper root class*/
class StbImage
{
private:
	typedef struct {
		union
		{
			FILE* file;
			BYTE* buffer;
		};
		int len;
	} _DATA, *_LPDATA;
	int m_iByte; // Bytes p/channel
	int m_iComp; // Channels p/pixel
	int m_iWidth; // Image width
	int m_iHeight; // Image height
	void* m_lpPixels; // Pixel data

	void _byte(_LPDATA data);
	void _c168(void* data);
	void _c816(void* data);
	void _cf08(void* data, int format);
	void _cf16(void* data, int format);
	void _conv(void* source, int format);
	void _copy(const StbImage* source);
	void _file(_LPDATA data, const char* file);
	void _h2ld(void* data);
	int  _info(_LPDATA data);
	void _l2hd(void* data);
	void _load(_LPDATA data, int format);
	int  _lgif(_LPDATA data, int format, int** delays);
	void _rcid(_LPDATA data, int rcid);
	bool _resz(void* source, int ow, int oh, int rx, int ry, int rw, int rh);

public:
	/*(1) Constructs an empty StbImage object*/
	StbImage();

	/*(2) Constructs a copy StbImage object with <convert>*/
	StbImage(_In_ const StbImage& source)
	{
		m_lpPixels = nullptr;
		convert(source, StbFormat::Default);
	}

	/*(3) Constructs StbImage object with <load>*/
	StbImage(int rcid, StbFormat format = StbFormat::Default)
	{
		load(rcid, format);
	}

	/*(4) Constructs StbImage object with <load>*/
	StbImage(_In_z_ const char* file, StbFormat format = StbFormat::Default)
	{
		load(file, format);
	}

	/*Cleans up the StbImage object*/
	~StbImage()
	{
		if (isImage())
		{
			imageFree();
		}
	}

	/*(1) Converts loaded image to the new pixel format. Although it might be necessary, often better to choose the right pixel format at image loading. Direct conversions are 8u-16u, 16u-8u, 8u-32f, 32f-8u. Conversions 16u-32f and 32f-16u are performed in two steps. The 32-bit float format conversion isn't provided by <stb_image>, so it is performed in three steps: downgraded to 8-bit, remapped and then converted back to 32-bit float
	@param The new pixel format, must differ from the source*/
	void convert(StbFormat format)
	{
		_conv(getPixels(), (int)format);
	}

	/*(2) Converts the image currently loaded into the source StbImage object to the new pixel format. Although it might be necessary, often better to choose the right pixel format at image loading. Direct conversions are 8u-16u, 16u-8u, 8u-32f, 32f-8u. Conversions 16u-32f and 32f-16u are performed in two steps. The 32-bit float format conversion isn't provided by <stb_image>, so it is performed in three steps: downgraded to 8-bit, remapped and then converted back to 32-bit float
	@param [in] The source StbImage object 
	@param The new pixel format, must differ from the source*/
	void convert(_In_ const StbImage& source, StbFormat format);

	/*(1) Converts loaded 16-bit image to the 8-bit pixel depth*/
	void convert16To8()
	{
		_c168(getPixels());
	}

	/*(2) Converts 16-bit image currently loaded into the source StbImage object to the 8-bit pixel depth
	@param [in] The source StbImage object*/
	void convert16To8(_In_ const StbImage& source);

	/*(1) Converts loaded 8-bit image to the 16-bit pixel depth*/
	void convert8To16()
	{
		_c816(getPixels());
	}

	/*(2) Converts 8-bit image currently loaded into the source StbImage object to the 16-bit pixel depth
	@param [in] The source StbImage object*/
	void convert8To16(_In_ const StbImage& source);

	/*(1) Converts loaded 8-bit image to new channel per pixel format
	@param The new channel per pixel format, must be non-default and differ from the source*/
	void convertFormat(StbFormat format)
	{
		_cf08(getPixels(), (int)format);
	}

	/*(2) Converts 8-bit image currently loaded into the source StbImage object to new channel per pixel format
	@param [in] The source StbImage object
	@param The new channel per pixel format, must be non-default and differ from the source*/
	void convertFormat(_In_ const StbImage& source, StbFormat format);

	/*(1) Converts loaded 16-bit image to new channel per pixel format
	@param The new channel per pixel format, must be non-default and differ from the source*/
	void convertFormat16(StbFormat format)
	{
		_cf16(getPixels(), (int)format);
	}

	/*(2) Converts 16-bit image currently loaded into the source StbImage object to new channel per pixel format
	@param [in] The source StbImage object
	@param The new channel per pixel format, must be non-default and differ from the source*/
	void convertFormat16(_In_ const StbImage& source, StbFormat format);
	
	/*Sets the global flag indicating whether to process iphone images back to canonical format, or pass them through as is
	@param True to convert BGR to RGB for PNG files, default false*/
	static void convertIphonePngToRgb(bool convert);

	/*Duplicates the source StbImage object
	@param [in] The source StbImage object*/
	void copy(_In_ const StbImage& source);

	/*Duplicates a region of the source StbImage object
	@param [in] The source StbImage object
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region*/
	void copyRegion(_In_ const StbImage& source, int rleft, int rtop, int rwidth, int rheight);

	/*Duplicates one of the inbound sprites in the source StbImage object selected by index value. The sprite's dimentions must by multiple of the image's dimentions, and remain the same within the image
	@param The width of the sprite
	@param The height of the sprite
	@param The index of the sprite*/
	void copySprite(_In_ const StbImage& source, int width, int height, int index);

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
	StbFormat getChannels()
	{
		return (StbFormat)m_iComp;
	}

	/*Gets the channel depth of loaded or queried image. Possible values are: <Unsigned8>, <Unsigned16> or <Float32>
	@return The pixel channel depth*/
	StbFormat getDepth()
	{
		return (StbFormat)(m_iByte << 4);
	}

	/*Gets the number of channels per pixel and the channel depth of loaded or queried image
	@return The pixel format*/
	StbFormat getFormat()
	{
		return (StbFormat)((m_iByte << 4) | m_iComp);
	}

	/*Gets the height of last loaded image. The multi-image height is multiplied by the number of layers
	@return The image height in pixels*/
	int getHeight()
	{
		return m_iHeight;
	}

	/*Gets the pointer of pixel array of last loaded image
	@return Pointer to the image pixel array*/
	_Ret_notnull_ void* getPixels();

	/*Gets the width of last loaded image
	@return The image width in pixels*/
	int getWidth()
	{
		return m_iWidth;
	}

	/*(1) Converts loaded 32-bit float (HDR) image to the 8-bit unsigned (LDR) pixel depth*/
	void hdrToLdr()
	{
		_h2ld(getPixels());
	}

	/*(2) Converts 32-bit float (HDR) image currently loaded into the source StbImage object to the 8-bit unsigned (LDR) pixel depth
	@param [in] The source StbImage object*/
	void hdrToLdr(_In_ const StbImage& source);

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

	/*Checks if the StbImage object has loaded image
	@return True if the image is loaded, false otherwise*/
	bool isImage()
	{
		return m_lpPixels != nullptr;
	}

	/*(1) Converts loaded 8-bit unsigned (LDR) image to the 32-bit float (HDR) pixel depth*/
	void ldrToHdr()
	{
		_l2hd(getPixels());
	}

	/*(2) Converts 8-bit unsigned (LDR) image currently loaded into the source StbImage object to the 32-bit float (HDR) pixel depth
	@param [in] The source StbImage object*/
	void ldrToHdr(_In_ const StbImage& source);

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

	/*(1) Resizes currently loaded image
	@param The width of a new image
	@param The height of a new image
	@return True if success, false otherwise*/
	bool resize(int width, int height)
	{
		return resizeRegion(width, height, 0, 0, m_iWidth, m_iHeight);
	}

	/*(2) Resizes an image currently loaded into the source StbImage object
	@param [in] The source StbImage object
	@param The width of a new image
	@param The height of a new image
	@return True if success, false otherwise*/
	bool resize(_In_ const StbImage& source, int width, int height)
	{
		return resizeRegion(source, width, height, 0, 0, source.m_iWidth, source.m_iHeight);
	}

	/*(1) Resizes a region of currently loaded image
	@param The width of a new image
	@param The height of a new image
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region
	@return True if success, false otherwise*/
	bool resizeRegion(int width, int height, int rleft, int rtop, int rwidth, int rheight);

	/*(2) Resizes a region of the image currently loaded into the source StbImage object
	@param [in] The source StbImage object
	@param The width of a new image
	@param The height of a new image
	@param The region top-left corner x coordinate on the image
	@param The region top-left corner y coordinate on the image
	@param The width of the region
	@param The height of the region
	@return True if success, false otherwise*/
	bool resizeRegion(_In_ const StbImage& source, int width, int height, int rleft, int rtop, int rwidth, int rheight)
	{
		_copy(&source);
		return _resz(source.m_lpPixels, width, height, rleft, rtop, rwidth, rheight);
	}

	/*Sets the global image loading direction flag
	@param True to set loading direction from bottom to top, default false*/
	static void setFlipVerticallyOnLoad(bool flip);

	/*Sets the global image loading alpha unpremultiplication flag
	@param True to force removing any premultiplied alpha, default false*/
	static void setUnpremultiplyOnLoad(bool unpremultiply);

	/*Vertically flips loaded image*/
	void verticalFlip();

	/*Vertically flips layers of loaded GIF image
	@param The number of loaded layers*/
	void verticalFlipSlices(int layers);

	/*Sets the global PNG filter mode value. Forces the PNG filter mode if from 0 to 5
	@param The new filter mode value, default -1*/
	static void writeForcePngFilter(int filter);

	/*Writes currently loaded image into the BMP file. The image data must be 8-bit per channel
	@param [in] Path to the written BMP file*/
	bool writeBmp(_In_z_ const char* filepath);

	/*Writes currently loaded image into the HDR file. The image data must be 32f-bit per channel
	@param [in] Path to the written HDR file*/
	bool writeHdr(_In_z_ const char* filepath);

	/*Writes currently loaded image into the JPG file. The image data must be 8-bit per channel
	@param [in] Path to the written JPG file*/
	bool writeJpg(_In_z_ const char* filepath);

	/*Sets global JPEG quality value for writing JPG files. Higher value gives more quality, must be 1..100
	@param The new JPEG quality value, default 80*/
	static void writeJpegQuality(int quality);

	/*Writes currently loaded image into the PNG file. The image data must be 8-bit per channel
	@param [in] Path to the written PNG file*/
	bool writePng(_In_z_ const char* filepath);

	/*Sets global PNG compession level value for writing PNG files. Higher value gives more compression, must be 0..9
	@param The new PNG compession level value, default 8*/
	static void writePngCompressionLevel(int comp);

	/*Writes currently loaded image into the TGA file. The image data must be 8-bit per channel
	@param [in] Path to the written TGA file*/
	bool writeTga(_In_z_ const char* filepath);

	/*Sets global RLE compression flag for writing TGA files
	@param True to enable RLE, default true*/
	static void writeTgaWithRle(bool rle);
}; // class StbImage

#ifndef _DEBUG
_Ret_notnull_ inline void* StbImage::getPixels()
{
	return m_lpPixels;
}
#endif // #ifdef _DEBUG
