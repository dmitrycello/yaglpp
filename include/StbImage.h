#pragma once
#include "yaglpp.h"
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
		void* pPixels = nullptr; // Pixel data
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
		if (isImage())
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

	/*Gets the height of last loaded image. The multi-image height is multiplied by the number of layers
	@return The image height in pixels*/
	int getHeight() const
	{
		return _m.iHeight;
	}

	/*Gets a pointer to the pixel array of last loaded image
	@return Pointer to the image pixel array*/
	_Ret_notnull_ void* getPixels() const;

	/*Gets the width of last loaded image
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
	bool isImage() const
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
}; // class StbImage

#ifndef _DEBUG
_Ret_notnull_ inline void* StbImage::getPixels() const
{
	return _m.pPixels;
}
#endif // #ifdef _DEBUG
