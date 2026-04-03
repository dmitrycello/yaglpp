#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_STB_IMAGE_H
#define YAGLPP_STB_IMAGE_H

/*YAGL++ STB image helper root class*/
class StbImage
{
public:
	/*YAGL++ STB image I/O callback structure*/
	struct Callbacks
	{
		/*Fills 'data' with 'size' bytes. Returns number of bytes actually read*/
		int (*read)(void* user, char* data, int size);

		/*Skips the next 'n' bytes, or 'unget' the last -n bytes if negative*/
		void (*skip)(void* user, int n);

		/*Returns nonzero if at end of file/data*/
		int (*eof)(void* user);
	};
	enum class Format : int;

	/*(1) Constructs an empty STB image object*/
	StbImage()
	{
		std::memset(this, 0, sizeof(StbImage));
	}

	/*(2) Constructs a copy of image object with <Copy>*/
	StbImage(const StbImage& source) : StbImage()
	{
		Copy(source);
	}

	/*(3) Constructs a resized copy of image object with <Copy>*/
	StbImage(const StbImage& source, int dw, int dh) : StbImage()
	{
		Copy(source, dw, dh);
	}

	/*(4) Constructs a copy of image sprite with <CopySprite>*/
	StbImage(const StbImage& source, int width, int height, int index) : StbImage()
	{
		CopySprite(source, width, height, index);
	}

	/*(5) Constructs a resized copy of image sprite with <CopySprite>*/
	StbImage(const StbImage& source, int width, int height, int index, int dw, int dh) : StbImage()
	{
		CopySprite(source, width, height, index, dw, dh);
	}

	/*(6) Constructs a copy of image region with <CopyRegion>*/
	StbImage(const StbImage& source, int sx, int sy, int sw, int sh) : StbImage()
	{
		CopyRegion(source, sx, sy, sw, sh);
	}

	/*(7) Constructs a resized copy of image region with <CopyRegion>*/
	StbImage(const StbImage& source, int sx, int sy, int sw, int sh, int dw, int dh) : StbImage()
	{
		CopyRegion(source, sx, sy, sw, sh, dw, dh);
	}

	/*(8) Constructs an STB image object with empty image pixel data array of given size with <Create>*/
	StbImage(int width, int height, Format format, bool init = false) : StbImage()
	{
		Create(width, height, format, init);
	}

	/*(9) Constructs STB image object with <LoadFromFile>*/
	StbImage(_In_z_ const char* file) : StbImage()
	{
		LoadFromFile(file);
	}

	/*(10) Constructs STB image object with <LoadFromFile>*/
	StbImage(_In_z_ const char* file, Format format) : StbImage()
	{
		LoadFromFile(file, format);
	}

	/*(11) Constructs STB image object with <LoadFromMemory>*/
	StbImage(_In_ unsigned char* data, unsigned int size) : StbImage()
	{
		LoadFromMemory(data, size);
	}

	/*(12) Constructs STB image object with <LoadFromMemory>*/
	StbImage(_In_ unsigned char* data, unsigned int size, Format format) : StbImage()
	{
		LoadFromMemory(data, size, format);
	}

	/*(13) Constructs STB image object with <LoadFromCallbacks>*/
	StbImage(_In_ Callbacks const* clbk, _In_ void* user) : StbImage()
	{
		LoadFromCallbacks(clbk, user);
	}

	/*(14) Constructs STB image object with <LoadFromCallbacks>*/
	StbImage(_In_ Callbacks const* clbk, _In_ void* user, Format format) : StbImage()
	{
		LoadFromCallbacks(clbk, user, format);
	}

	/*(15) Constructs STB image object with <LoadGifFromFile>*/
	StbImage(_In_z_ const char* file, _Outptr_opt_ int** delays) : StbImage()
	{
		LoadGifFromFile(file, delays);
	}

	/*(16) Constructs STB image object with <LoadGifFromFile>*/
	StbImage(_In_z_ const char* file, _Outptr_opt_ int** delays, Format format) : StbImage()
	{
		LoadGifFromFile(file, delays, format);
	}

	/*(17) Constructs STB image object with <LoadGifFromMemory>*/
	StbImage(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays) : StbImage()
	{
		LoadGifFromMemory(data, size, delays);
	}

	/*(18) Constructs STB image object with <LoadGifFromMemory>*/
	StbImage(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays, Format format) : StbImage()
	{
		LoadGifFromMemory(data, size, delays, format);
	}

	/*(19) Constructs STB image object with <LoadGifFromCallbacks>*/
	StbImage(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays) : StbImage()
	{
		LoadGifFromCallbacks(clbk, user, delays);
	}

	/*(20) Constructs STB image object with <LoadGifFromCallbacks>*/
	StbImage(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays, Format format) : StbImage()
	{
		LoadGifFromCallbacks(clbk, user, delays, format);
	}

	/*Cleans up the valid STB image object*/
	~StbImage()
	{
		Delete();
	}

	/*(1) Blits the whole source image directly into the destination image, scaled to its dimensions. Does nothing if empty source object. Acts as <Copy> if empty destination object
	@param[in] The source STB image object*/
	void Blit(const StbImage& source)
	{
		BlitRegion(source, 0, 0, source.m_Width, source.m_Height, 0, 0, m_Width, m_Height);
	}

	/*(2) Blits the whole source image directly into an equal region of the destination image. Does nothing if empty source object. Acts as <Copy> if empty destination object
	@param [in] The source STB image object
	@param The destination region top-left corner x coordinate (ignored if empty image)
	@param The destination region top-left corner y coordinate (ignored if empty image)*/
	void Blit(const StbImage& source, int dx, int dy)
	{
		BlitRegion(source, 0, 0, source.m_Width, source.m_Height, dx, dy, source.m_Width, source.m_Height);
	}

	/*(3) Blits the whole source image directly into a region of the destination image, scaled to given dimensions. Does nothing if empty source object. Acts as <Copy> if empty destination object
	@param [in] The source STB image object
	@param The destination region top-left corner x coordinate (ignored if empty image)
	@param The destination region top-left corner y coordinate (ignored if empty image)
	@param The destination region scaled width
	@param The destination region scaled height*/
	void Blit(const StbImage& source, int dx, int dy, int dw, int dh)
	{
		BlitRegion(source, 0, 0, source.m_Width, source.m_Height, dx, dy, dw, dh);
	}

	/*(1) Blits a region of the source image directly into the destination image, scaled to its dimensions. Does nothing if empty source object. Acts as <CopyRegion> if empty destination object
	@param [in] The source STB image object
	@param The source region top-left corner x coordinate
	@param The source region top-left corner y coordinate
	@param The source region width
	@param The source region height*/
	void BlitRegion(const StbImage& source, int sx, int sy, int sw, int sh)
	{
		BlitRegion(source, sx, sy, sw, sh, 0, 0, m_Width, m_Height);
	}

	/*(2) Blits a region of the source image directly into an equal region of the destination image. Does nothing if empty source object. Acts as <CopyRegion> if empty destination object
	@param [in] The source STB image object
	@param The source region top-left corner x coordinate
	@param The source region top-left corner y coordinate
	@param The source and destination region width
	@param The source and destination region height
	@param The destination region top-left corner x coordinate
	@param The destination region top-left corner y coordinate*/
	void BlitRegion(const StbImage& source, int sx, int sy, int sw, int sh, int dx, int dy)
	{
		BlitRegion(source, sx, sy, sw, sh, dx, dy, sw, sh);
	}

	/*(3) Blits a region of the source image directly into a region of the destination image, scaled to given dimensions. Does nothing if empty source object. Acts as <CopyRegion> if empty destination object
	@param [in] The source STB image object
	@param The source region top-left corner x coordinate
	@param The source region top-left corner y coordinate
	@param The source region width
	@param The source region height
	@param The destination region top-left corner x coordinate (ignored if empty image)
	@param The destination region top-left corner y coordinate (ignored if empty image)
	@param The destination region scaled width
	@param The destination region scaled height*/
	void BlitRegion(const StbImage& source, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);

	/*(1) Blits an indexed sprite of the source image into the destination image, scaled to its dimensions. The sprite dimensions must be multiple to the source image dimensions. Does nothing if empty source object. Acts as <CopySprite> if empty destination object
	@param [in] The source STB image object
	@param The source image sprite width
	@param The source image sprite height
	@param The sprite index in the source image*/
	void BlitSprite(const StbImage& source, int width, int height, int index)
	{
		BlitSprite(source, width, height, index, 0, 0, m_Width, m_Height);
	}

	/*(2) Blits an indexed sprite of the source image into an equal region of the destination image. The sprite dimensions must be multiple to the source image dimensions. Does nothing if empty source object. Acts as <CopySprite> if empty destination object
	@param [in] The source STB image object
	@param The source image sprite width
	@param The source image sprite height
	@param The sprite index in the source image
	@param The destination region top-left corner x coordinate
	@param The destination region top-left corner y coordinate*/
	void BlitSprite(const StbImage& source, int width, int height, int index, int dx, int dy)
	{
		BlitSprite(source, width, height, index, dx, dy, width, height);
	}

	/*(3) Blits an indexed sprite of the source image into a region of the destination image, scaled to given dimensions. The sprite dimensions must be multiple to the source image dimensions. Does nothing if empty source object. Acts as <CopySprite> if empty destination object
	@param [in] The source STB image object
	@param The source image sprite width
	@param The source image sprite height
	@param The sprite index in the source image
	@param The destination region top-left corner x coordinate
	@param The destination region top-left corner y coordinate
	@param The destination region scaled width
	@param The destination region scaled height*/
	void BlitSprite(const StbImage& source, int width, int height, int index, int dx, int dy, int dw, int dh);
	
	/*Sets the global flag indicating whether to process iphone images back to canonical format, or pass them through as is
	@param True to convert BGR to RGB for PNG files, default false*/
	static void ConvertIphonePngToRgb(bool convert);

	/*(1) Copies the whole source image into a new equal destination image. Does nothing if self-assignment object. Re-initializes if empty source object
	@param [in] The source STB image object*/
	void Copy(const StbImage& source)
	{
		CopyRegion(source, 0, 0, source.m_Width, source.m_Height, source.m_Width, source.m_Height);
	}

	/*(2) Copies the whole source image into a new destination image, scaled to given dimensions. Does nothing if empty source object. Acts as <Copy> if empty destination object
	@param [in] The source STB image object
	@param The destination region scaled width
	@param The destination region scaled height*/
	void Copy(const StbImage& source, int dw, int dh)
	{
		CopyRegion(source, 0, 0, source.m_Width, source.m_Height, dw, dh);
	}

	/*(1) Copies a region of the source image into a new equal destination image. Does nothing if self-assignment object. Re-initializes if empty source object
	@param [in] The source STB image object
	@param The source region top-left corner x coordinate
	@param The source region top-left corner y coordinate
	@param The source region width
	@param The source region height*/
	void CopyRegion(const StbImage& source, int sx, int sy, int sw, int sh)
	{
		CopyRegion(source, sx, sy, sw, sh, sw, sh);
	}

	/*(2) Copies a region of the source image into a new destination image, scaled to given dimensions. Does nothing if self-assignment object. Re-initializes if empty source object
	@param [in] The source STB image object
	@param The source region top-left corner x coordinate
	@param The source region top-left corner y coordinate
	@param The source region width
	@param The source region height
	@param The destination image scaled width
	@param The destination image scaled height*/
	void CopyRegion(const StbImage& source, int sx, int sy, int sw, int sh, int dw, int dh);

	/*(1) Copies an indexed sprite of the source image into a new equal destination image. The sprite dimensions must be multiple to the source image dimensions. Does nothing if self-assignment object. Re-initializes if empty source object
	@param [in] The source STB image object
	@param The source image sprite width
	@param The source image sprite height
	@param The sprite index in the source image*/
	void CopySprite(const StbImage& source, int width, int height, int index)
	{
		CopySprite(source, width, height, index, width, height);
	}

	/*(2) Copies an indexed sprite of the source image into a new destination image, scaled to given dimensions. The sprite dimensions must be multiple to the source image dimensions. Does nothing if self-assignment object. Re-initializes if empty source object
	@param [in] The source STB image object
	@param The source image sprite width
	@param The source image sprite height
	@param The sprite index in the source image
	@param The destination image scaled width
	@param The destination image scaled height*/
	void CopySprite(const StbImage& source, int width, int height, int index, int dw, int dh);

	/*Creates an empty image pixel data array within STB image object. The pixel format has to be determined, which means no default values such as <Rgb> or <Unsigned8> should be used
	@param The new image width
	@param The new image height
	@param The new image format
	@param True to initialize the memory block with zeros, default false*/
	void Create(int width, int height, Format format, bool init = false);

	/*Frees and re-initialize the STB image object*/
	void Delete();

	/*Sets the global image writing direction flag
	@param True to set writing direction from bottom to top, default false*/
	static void FlipVerticallyOnWrite(bool flip);

	/*Gets the number of channels per pixel of loaded image. Possible values are: <Grey>, <GreyAlpha>, <Rgb> or <RgbAlpha>
	@return The number of channels per pixel*/
	Format GetChannels() const
	{
		return (Format)m_Comp;
	}

	/*Gets the channel depth of loaded image. Possible values are: <Unsigned8>, <Unsigned16> or <Float32>
	@return The pixel channel depth*/
	Format GetDepth() const
	{
		return (Format)(m_Byte << 4);
	}

	/*Gets the number of channels per pixel and the channel depth of loaded image
	@return The pixel format*/
	Format GetFormat() const
	{
		return (Format)((m_Byte << 4) | m_Comp);
	}

	/*Gets the width of last loaded or queried image
	@return The image width in pixels*/
	int GetWidth() const
	{
		return m_Width;
	}

	/*Gets the height of last loaded or queried image. The multi-image height is multiplied by the number of layers
	@return The image height in pixels*/
	int GetHeight() const
	{
		return m_Height;
	}

	/*Gets a pointer to the pixel array of last loaded image
	@return Pointer to the image pixel array*/
	_Ret_notnull_ unsigned char* GetPixels() const;

	/*Sets the global gamma value used in hdr-to-ldr conversion
	@param New hdr-to-ldr gamma value, default 1/2.2f*/
	static void HdrToLdrGamma(float gamma);

	/*Sets the global scale value used in hdr-to-ldr conversion
	@param New hdr-to-ldr scale value, default 1.0f*/
	static void HdrToLdrScale(float scale);

	/*Retrives image file information. Sets object width, height and pixel format without image loading
	@param [in] Path to the image file*/
	void InfoFromFile(_In_z_ const char* file);

	/*Retrives image memory resource information. Sets object width, height and pixel format without image loading
	@param [in] The memory resource data location
	@param The memory resource data size*/
	void InfoFromMemory(_In_ unsigned char* data, unsigned int size);

	/*Retrives image information using I/O callback while reading from arbitrary sources. Sets object width, height and pixel format without image loading
	@param [in] Points to callback structure
	@param [in] Points to user-defined data*/
	void InfoFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user);

	/*Checks if the file is a 16-bit image
	@param [in] Path to the image file
	@return True if file is 16-bit image, false otherwise*/
	static bool Is16BitFromFile(_In_z_ const char* file);

	/*Checks if the memory resource is a 16-bit image
	@param [in] The memory resource data location
	@param The memory resource data size
	@return True if memory resource is 16-bit image, false otherwise*/
	static bool Is16BitFromMemory(_In_ unsigned char* data, unsigned int size);

	/*Checks if the image is 16-bit using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@return True if file is 16-bit image, false otherwise*/
	static bool Is16BitFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user);

	/*Checks if the file is a 32-bit float image
	@param [in] Path to the image file
	@return True if file is 32-bit float image, false otherwise*/
	static bool IsHdrFromFile(_In_z_ const char* file);

	/*Checks if the memory resource is a 32-bit float image
	@param [in] The memory resource data location
	@param The memory resource data size
	@return True if memory resource is 32-bit float image, false otherwise*/
	static bool IsHdrFromMemory(_In_ unsigned char* data, unsigned int size);

	/*Checks if the image is 32-bit float using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@return True if file is 32-bit float image, false otherwise*/
	static bool IsHdrFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user);

	/*Checks if the STB image object has loaded image
	@return True if the image is loaded, false otherwise*/
	bool IsImage() const
	{
		return m_Pixels != nullptr;
	}

	/*Sets the global gamma value used in ldr-to-hdr conversion
	@param New ldr-to-hdr gamma value, default 2.2f*/
	static void LdrToHdrGamma(float gamma);

	/*Sets the global scale value used in ldr-to-hdr conversion
	@param New ldr-to-hdr scale value, default 1.0f*/
	static void LdrToHdrScale(float scale);

	/*(1) Loads image from file with default image source pixel format
	@param [in] Path to the image file*/
	void LoadFromFile(_In_z_ const char* file);

	/*(2) Loads image from file with particular image pixel format
	@param [in] Path to the image file
	@param The storing pixel format*/
	void LoadFromFile(_In_z_ const char* file, Format format);

	/*(1) Loads image memory resource with default image source pixel format
	@param [in] The memory resource data location
	@param The memory resource data size*/
	void LoadFromMemory(_In_ unsigned char* data, unsigned int size);

	/*(2) Loads image memory resource with particular image pixel format
	@param [in] The memory resource data location
	@param The memory resource data size
	@param The storing pixel format*/
	void LoadFromMemory(_In_ unsigned char* data, unsigned int size, Format format);

	/*(1) Loads image with default image source pixel format using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param The storing pixel format*/
	void LoadFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user);

	/*(2) Loads image with particular image pixel format using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param The storing pixel format*/
	void LoadFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, Format format);

	/*(1) Loads GIF image from file with default image source pixel format
	@param [in] Path to the image file
	@param [out] Pointer to the array of image delays
	@return The number of loaded layers*/
	int LoadGifFromFile(_In_z_ const char* file, _Outptr_opt_ int** delays);

	/*(2) Loads GIF image from file with particular image pixel format
	@param [in] Path to the image file
	@param [out] Pointer to the array of image delays
	@param The storing pixel format
	@return The number of loaded layers*/
	int LoadGifFromFile(_In_z_ const char* file, _Outptr_opt_ int** delays, Format format);

	/*(1) Loads GIF image memory resource with default image source pixel format
	@param [in] The memory resource data location
	@param The memory resource data size
	@param [out] Pointer to the array of image delays
	@return The number of loaded layers*/
	int LoadGifFromMemory(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays);

	/*(2) Loads GIF image memory resource with particular image pixel format
	@param [in] The memory resource data location
	@param The memory resource data size
	@param [out] Pointer to the array of image delays
	@param The storing pixel format
	@return The number of loaded layers*/
	int LoadGifFromMemory(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays, Format format);

	/*(1) Loads GIF image with default image source pixel format using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param [out] Pointer to the array of image delays
	@return The number of loaded layers*/
	int LoadGifFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays);

	/*(2) Loads GIF image with particular image pixel format using I/O callback while reading from arbitrary sources
	@param [in] Points to callback structure
	@param [in] Points to user-defined data
	@param [out] Pointer to the array of image delays
	@param The storing pixel format
	@return The number of loaded layers*/
	int LoadGifFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays, Format format);

	/*Sets the global image loading direction flag
	@param True to set loading direction from bottom to top, default false*/
	static void SetFlipVerticallyOnLoad(bool flip);

	/*Sets the global image loading alpha unpremultiplication flag
	@param True to force removing any premultiplied alpha, default false*/
	static void SetUnpremultiplyOnLoad(bool unpremultiply);

	/*Sets the global PNG filter mode value. Forces the PNG filter mode from 0 to 5
	@param The new filter mode value, default -1*/
	static void SetWriteForcePngFilter(int filter);

	/*Sets global JPEG quality value for writing JPG files. Higher value gives more quality, must be 1..100
	@param The new JPEG quality value, default 80*/
	static void SetWriteJpegQuality(int quality);

	/*Sets global PNG compession level value for writing PNG files. Higher value gives more compression, must be 0..9
	@param The new PNG compession level value, default 8*/
	static void SetWritePngCompressionLevel(int comp);

	/*Sets global RLE compression flag for writing TGA files. Default true
	@param True to enable RLE, false otherwise*/
	static void SetWriteTgaWithRle(bool rle);

	/*Writes currently loaded image into the BMP file. The image data must be 8-bit per channel
	@param [in] Path to the written BMP file
	@return True if operation successful, false otherwise*/
	void WriteBmp(_In_z_ const char* file);

	/*Writes currently loaded image into the HDR file. The image data must be 32f-bit per channel
	@param [in] Path to the written HDR file
	@return True if operation successful, false otherwise*/
	void WriteHdr(_In_z_ const char* file);

	/*Writes currently loaded image into the JPG file. The image data must be 8-bit per channel
	@param [in] Path to the written JPG file*/
	void WriteJpg(_In_z_ const char* file);

	/*Writes currently loaded image into the PNG file. The image data must be 8-bit per channel
	@param [in] Path to the written PNG file
	@return True if operation successful, false otherwise*/
	void WritePng(_In_z_ const char* file);

	/*Writes currently loaded image into the TGA file. The image data must be 8-bit per channel
	@param [in] Path to the written TGA file
	@return True if operation successful, false otherwise*/
	void WriteTga(_In_z_ const char* file);

#ifdef YAGLPP_MSVC
	/*(21) Constructs STB image object with <LoadFromResource> (Windows only)*/
	StbImage(int rcid) : StbImage()
	{
		LoadFromResource(rcid);
	}

	/*(22) Constructs STB image object with <LoadFromResource> (Windows only)*/
	StbImage(int rcid, Format format) : StbImage()
	{
		LoadFromResource(rcid, format);
	}

	/*(23) Constructs STB image object with <loadGifFromResource> (Windows only)*/
	StbImage(int rcid, _Outptr_opt_ int** delays) : StbImage()
	{
		LoadGifFromResource(rcid, delays);
	}

	/*(24) Constructs STB image object with <loadGifFromResource> (Windows only)*/
	StbImage(int rcid, _Outptr_opt_ int** delays, Format format) : StbImage()
	{
		LoadGifFromResource(rcid, delays, format);
	}

	/*Retrives image binary resource information. Sets object width, height and pixel format without image loading (Windows only)
	@param The binary resource id of <RC_DATA> type*/
	void InfoFromResource(int rcid);

	/*Checks if the binary resource is a 16-bit image (Windows only)
	@param The binary resource id of <RC_DATA> type
	@return True if binary resource is 16-bit image, false otherwise*/
	static bool Is16bitFromResource(int rcid);

	/*Checks if the memory resource is a 16-bit image (Windows only)
	@param The memory resource id of <RC_DATA> type
	@return True if memory resource is 16-bit image, false otherwise*/
	static bool IsHdrFromResource(int rcid);

	/*(1) Loads image binary resource with default image source pixel format (Windows only)
	@param The binary resource id of <RC_DATA> type*/
	void LoadFromResource(int rcid);

	/*(2) Loads image binary resource with particular image pixel format (Windows only)
	@param The binary resource id of <RC_DATA> type
	@param The storing pixel format*/
	void LoadFromResource(int rcid, Format format);

	/*(1) Loads GIF image binary resource with default image source pixel format (Windows only)
	@param The binary resource id of <RC_DATA> type
	@param [out] Pointer to the array of image delays
	@return The number of loaded layers*/
	int LoadGifFromResource(int rcid, _Outptr_opt_ int** delays);

	/*(2) Loads GIF image binary resource with particular image pixel format (Windows only)
	@param The binary resource id of <RC_DATA> type
	@param [out] Pointer to the array of image delays
	@param The storing pixel format
	@return The number of loaded layers*/
	int LoadGifFromResource(int rcid, _Outptr_opt_ int** delays, Format format);
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property for number of channels per pixel*/
	__declspec(property(get = GetChannels)) Format channels;

	/*Read-only property for channel depth of loaded or queried image*/
	__declspec(property(get = GetDepth)) Format depth;

	/*Read-only property for number of channels per pixel and the channel depth of loaded or queried image*/
	__declspec(property(get = GetFormat)) Format format;

	/*Read-only property for height of last loaded image*/
	__declspec(property(get = GetHeight)) int height;

	/*Read-only property to check if the STB image object has loaded image*/
	__declspec(property(get = IsImage)) bool image;

	/*Read-only property for pointer to the pixel array of last loaded image*/
	__declspec(property(get = GetPixels)) unsigned char* pixels;

	/*Read-only property for width of last loaded image*/
	__declspec(property(get = GetWidth)) int width;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

private:
	int m_Byte; // Bytes p/channel
	int m_Comp; // Channels p/pixel
	int m_Width; // Image width
	int m_Height; // Image height
	unsigned char* m_Pixels; // Image data
}; // class StbImage

/*YAGL++ STB image pixel format enumerator*/
enum class StbImage::Format : int
{
	/*Default channels per pixel and channel depth*/
	Default = 0x00,

	/*One channel per pixel with the default channel depth: grey*/
	Grey = 0x01,

	/*Two channels per pixel with the default channel depth: grey, alpha*/
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

inline void StbImage::LoadFromFile(_In_z_ const char* file)
{
	LoadFromFile(file, Format::Default);
}

inline void StbImage::LoadFromMemory(_In_ unsigned char* data, unsigned int size)
{
	LoadFromMemory(data, size, Format::Default);
}

inline void StbImage::LoadFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user)
{
	LoadFromCallbacks(clbk, user, Format::Default);
}

inline int StbImage::LoadGifFromFile(_In_z_ const char* file, _Outptr_opt_ int** delays)
{
	return LoadGifFromFile(file, delays, Format::Default);
}

inline int StbImage::LoadGifFromMemory(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays)
{
	return LoadGifFromMemory(data, size, delays, Format::Default);
}

inline int StbImage::LoadGifFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays)
{
	return LoadGifFromCallbacks(clbk, user, delays, Format::Default);
}

#ifdef YAGLPP_MSVC
inline void StbImage::LoadFromResource(int rcid)
{
	LoadFromResource(rcid, Format::Default);
}

inline int StbImage::LoadGifFromResource(int rcid, _Outptr_opt_ int** delays)
{
	return LoadGifFromResource(rcid, delays, Format::Default);
}
#endif // #ifdef YAGLPP_MSVC

#ifdef YAGLPP_IMPLEMENTATION
	#ifdef _DEBUG
		#define STBI_FAILURE_USERMSG
		#define YAGLPP_STB_ERROR(e) YAGLPP_ASSERT(yaglpp_stb_error(e))
		static bool yaglpp_stb_error(bool c);
	#else
		#define STBI_NO_FAILURE_STRINGS
		#define YAGLPP_STB_ERROR(e) ((void)0)
	#endif
#define __STDC_LIB_EXT1__
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(e) assert(e)
#define STBI_MALLOC(s) yaglpp_allocate(s,nullptr)
#define STBI_REALLOC(p,s) yaglpp_reallocate(p,s,nullptr)
#define STBI_FREE(p) yaglpp_deallocate(p,nullptr)
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STBIR_ASSERT(e) assert(e)
#define STBIR_MALLOC(s,c) ((void)(c), yaglpp_allocate(s,nullptr))
#define STBIR_FREE(p,c) ((void)(c), yaglpp_deallocate(p,nullptr))
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(e) assert(e)
#define STBIW_MALLOC(s) yaglpp_allocate(s,nullptr)
#define STBIW_REALLOC(p,s) yaglpp_reallocate(p,s,nullptr)
#define STBIW_FREE(p) yaglpp_deallocate(p,nullptr)
#define YAGLPP_STBIMAGE_BYTE 0xF0
#define YAGLPP_STBIMAGE_COMP 0x0F
static int yaglpp_stb_jpeg_quality = 80;
static const char* yaglpp_stb_write_error = "YAGL++: failed to write STB";

#ifdef YAGLPP_MSVC
#pragma warning(push)
	#pragma warning(disable : 4297) // MSVC nothrow false flag
#endif

#include <stb/stb_image.h> // v2.30
#include <stb/stb_image_write.h> // v1.16
#include <stb/stb_image_resize2.h> // v2.17

#ifdef YAGLPP_MSVC
	#pragma warning(pop) // MSVC nothrow false flag
#endif

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

void StbImage::BlitRegion(const StbImage& source, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{
	if (source.m_Pixels)
	{
		// INVALID SOURCE IMAGE LEFT
		YAGLPP_ASSERT((sx >= 0) && ((sx + sw) <= source.GetWidth()));

		// INVALID SOURCE IMAGE TOP
		YAGLPP_ASSERT((sy >= 0) && ((sy + sh) <= source.GetHeight()));

		// INVALID SOURCE IMAGE WIDTH
		YAGLPP_ASSERT((sw > 0) && (sw <= source.GetWidth()));

		// INVALID SOURCE IMAGE HEIGHT
		YAGLPP_ASSERT((sh > 0) && (sh <= source.GetHeight()));

		if (m_Pixels)
		{
			// IMAGE PIXEL FORMAT MISMATCH
			YAGLPP_ASSERT(GetFormat() == source.GetFormat());

			// INVALID DESTINATION IMAGE LEFT
			YAGLPP_ASSERT((dx >= 0) && ((dx + dw) <= GetWidth()));

			// INVALID DESTINATION IMAGE TOP
			YAGLPP_ASSERT((dy >= 0) && ((dy + dh) <= GetHeight()));

			// INVALID DESTINATION IMAGE WIDTH
			YAGLPP_ASSERT((dw > 0) && (dw <= GetWidth()));

			// INVALID DESTINATION IMAGE HEIGHT
			YAGLPP_ASSERT((dh > 0) && (dh <= GetHeight()));
		}
		else
		{
			dx = 0; // reset destination left
			dy = 0; // reset destination top
			Create(dw, dh, source.GetFormat());
		}
		int iPixel = m_Byte * m_Comp;
		int iSrcStride = iPixel * source.m_Width,
			iDstStride = iPixel * m_Width;
		int iSrcOffset = (iPixel * sx) + (iSrcStride * sy),
			iDstOffset = (iPixel * dx) + (iDstStride * dy);
		stbir_datatype byte =
			(source.m_Byte == 1) ? STBIR_TYPE_UINT8 :
			(source.m_Byte == 2) ? STBIR_TYPE_UINT16 : STBIR_TYPE_FLOAT; // depth 8u/16u/32f
		stbir_pixel_layout comp = (stbir_pixel_layout)m_Comp; // channels 1/2/3/4
		STBIR_RESIZE resize;
		stbir_resize_init(&resize,
			&source.m_Pixels[iSrcOffset], sw, sh, iSrcStride,
			&m_Pixels[iDstOffset], dw, dh, iDstStride, comp, byte);
		stbir_set_edgemodes(&resize, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP);
		stbir_set_filters(&resize, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT);
		int iResult = stbir_resize_extended(&resize);

		// FAILED TO RESIZE OR COPY AN IMAGE
		YAGLPP_ASSERT(iResult != 0);
	}
}

void StbImage::BlitSprite(const StbImage& source, int width, int height, int index, int dx, int dy, int dw, int dh)
{
	if (source.m_Pixels)
	{
		int iCol = source.m_Width / width; // sprites in row
		int iRow = source.m_Height / height; // rows in image

		// INVALID SPRITE WIDTH PARAMETER
		YAGLPP_ASSERT(source.GetWidth() % width == 0);

		// INVALID SPRITE HEIGHT PARAMETER
		YAGLPP_ASSERT(source.GetHeight() % height == 0);

		// INVALID SPRITE INDEX PARAMETER
		YAGLPP_ASSERT((index >= 0) && (index < (iCol * iRow)));

		int iTop = index / iCol, iLeft = index % iCol; // sprite position in image
		BlitRegion(source, iLeft * width, iTop * height, width, height, dx, dy, dw, dh);
	}
}

void StbImage::ConvertIphonePngToRgb(bool convert)
{
	stbi_convert_iphone_png_to_rgb((int)convert);
}

void StbImage::CopyRegion(const StbImage& source, int sx, int sy, int sw, int sh, int dw, int dh)
{
	if (&source != this)
	{
		if (source.m_Pixels)
		{
			Create(dw, dh, source.GetFormat());
			BlitRegion(source, sx, sy, sw, sh, 0, 0, dw, dh);
		}
		else Delete();
	}
}

void StbImage::CopySprite(const StbImage& source, int width, int height, int index, int dw, int dh)
{
	if (&source != this)
	{
		if (source.m_Pixels)
		{
			Create(dw, dh, source.GetFormat());
			BlitSprite(source, width, height, index, 0, 0, dw, dh);
		}
		else Delete();
	}
}

void StbImage::Create(int width, int height, Format format, bool init)
{
	// INVALID IMAGE DIMENSIONS
	YAGLPP_ASSERT((width > 0) && (height > 0));

	// INVALID IMAGE DIMENSIONS
	YAGLPP_ASSERT((width * height) <= STBI_MAX_DIMENSIONS);

	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	m_Comp = (int)format & YAGLPP_STBIMAGE_COMP;
	m_Width = width;
	m_Height = height;

	// IMAGE PIXEL FORMAT MUST BE NON-DEFAULT
	YAGLPP_ASSERT((m_Byte > 0) && (m_Comp > 0));

	YAGLPP_FREE(m_Pixels);
	std::size_t iSize = (std::size_t)m_Byte * m_Comp * width * height;
	m_Pixels = (init) ?
		YAGLPP_CALLOC(unsigned char, iSize) :
		YAGLPP_MALLOC(unsigned char, iSize);
}

void StbImage::Delete()
{
	YAGLPP_FREE(m_Pixels);
	std::memset(this, 0, sizeof(StbImage));
}

void StbImage::FlipVerticallyOnWrite(bool flip)
{
	stbi_flip_vertically_on_write((int)flip);
}

void StbImage::HdrToLdrGamma(float gamma)
{
	stbi_hdr_to_ldr_gamma(gamma);
}

void StbImage::HdrToLdrScale(float scale)
{
	stbi_hdr_to_ldr_scale(scale);
}

void StbImage::InfoFromFile(_In_z_ const char* file)
{
	YAGLPP_FREE(m_Pixels);
	m_Pixels = nullptr;
	std::FILE* pFile = yaglpp_load_file(file);
	int r = stbi_info_from_file(pFile, &m_Width, &m_Height, &m_Comp);

	// FAILED TO LOAD INFO FROM FILE
	YAGLPP_STB_ERROR(!r);

	m_Byte = stbi_is_hdr_from_file(pFile) ? 4 :
		(stbi_is_16_bit_from_file(pFile)) ? 2 : 1;
	std::fclose(pFile);
}

void StbImage::InfoFromMemory(_In_ unsigned char* data, unsigned int size)
{
	YAGLPP_FREE(m_Pixels);
	m_Pixels = nullptr;
	int r = stbi_info_from_memory(data, size, &m_Width, &m_Height, &m_Comp);

	// FAILED TO LOAD INFO FROM BINARY RESOURCE
	YAGLPP_STB_ERROR(!r);

	m_Byte = stbi_is_hdr_from_memory(data, size) ? 4 :
		stbi_is_16_bit_from_memory(data, size) ? 2 : 1;
}

void StbImage::InfoFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user)
{
	YAGLPP_FREE(m_Pixels);
	m_Pixels = nullptr;
	int r = stbi_info_from_callbacks((stbi_io_callbacks*)clbk, user, &m_Width, &m_Height, &m_Comp);

	// FAILED TO LOAD INFO FROM I/O CALLBACK
	YAGLPP_STB_ERROR(!r);

	m_Byte = stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user) ? 4 :
		stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user) ? 2 : 1;
}

bool StbImage::Is16BitFromFile(_In_z_ const char* file)
{
	std::FILE* pFile = yaglpp_load_file(file);
	bool b = (bool)stbi_is_16_bit_from_file(pFile);
	std::fclose(pFile);
	return b;
}

bool StbImage::Is16BitFromMemory(_In_ unsigned char* data, unsigned int size)
{
	return (bool)stbi_is_16_bit_from_memory(data, size);
}

bool StbImage::Is16BitFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user);
}

bool StbImage::IsHdrFromFile(_In_z_ const char* file)
{
	std::FILE* pFile = yaglpp_load_file(file);
	bool b = (bool)stbi_is_hdr_from_file(pFile);
	std::fclose(pFile);
	return b;
}

bool StbImage::IsHdrFromMemory(_In_ unsigned char* data, unsigned int size)
{
	return (bool)stbi_is_hdr_from_memory(data, size);
}

bool StbImage::IsHdrFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user)
{
	return (bool)stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user);
}

void StbImage::LdrToHdrGamma(float gamma)
{
	stbi_ldr_to_hdr_gamma(gamma);
}

void StbImage::LdrToHdrScale(float scale)
{
	stbi_ldr_to_hdr_scale(scale);
}

void StbImage::LoadFromFile(_In_z_ const char* file, Format format)
{
	YAGLPP_FREE(m_Pixels);
	std::FILE* pFile = yaglpp_load_file(file);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte =
		(stbi_is_hdr_from_file(pFile)) ? 4 :
		(stbi_is_16_bit_from_file(pFile)) ? 2 : 1;
	m_Pixels =
		(m_Byte == 1) ? stbi_load_from_file(pFile, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_from_file_16(pFile, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_from_file(pFile, &m_Width, &m_Height, &m_Comp, iReqComp);

	// FAILED TO LOAD IMAGE FROM FILE
	YAGLPP_STB_ERROR(!m_Pixels);

	std::fclose(pFile);
	if (iReqComp > 0) m_Comp = iReqComp;
}

void StbImage::LoadFromMemory(_In_ unsigned char* data, unsigned int size, Format format)
{
	YAGLPP_FREE(m_Pixels);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte =
		(stbi_is_hdr_from_memory(data, size)) ? 4 :
		(stbi_is_16_bit_from_memory(data, size)) ? 2 : 1;
	m_Pixels =
		(m_Byte == 1) ? stbi_load_from_memory(data, size, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_16_from_memory(data, size, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_from_memory(data, size, &m_Width, &m_Height, &m_Comp, iReqComp);

	// FAILED TO LOAD IMAGE FROM BINARY RESOURCE
	YAGLPP_STB_ERROR(!m_Pixels);

	if (iReqComp > 0) m_Comp = iReqComp;
}

void StbImage::LoadFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, Format format)
{
	YAGLPP_FREE(m_Pixels);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte =
		(stbi_is_hdr_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 4 :
		(stbi_is_16_bit_from_callbacks((stbi_io_callbacks*)clbk, user)) ? 2 : 1;
	m_Pixels =
		(m_Byte == 1) ? stbi_load_from_callbacks((stbi_io_callbacks*)clbk, user, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_16_from_callbacks((stbi_io_callbacks*)clbk, user, &m_Width, &m_Height, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_from_callbacks((stbi_io_callbacks*)clbk, user, &m_Width, &m_Height, &m_Comp, iReqComp);

	// FAILED TO LOAD IMAGE FROM I/O CALLBACK
	YAGLPP_STB_ERROR(!m_Pixels);

	if (iReqComp > 0) m_Comp = iReqComp;
}

int StbImage::LoadGifFromFile(_In_z_ const char* file, _Outptr_opt_ int** delays, Format format)
{
	YAGLPP_FREE(m_Pixels);
	std::FILE* pFile = yaglpp_load_file(file);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte = 1; // original depth always 1
	m_Pixels =
		(m_Byte == 1) ? stbi_load_gif_from_file(pFile, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_16_gif_from_file(pFile, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_gif_from_file(pFile, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp);

	// FAILED TO LOAD GIF IMAGE FROM FILE
	YAGLPP_STB_ERROR(!m_Pixels);

	std::fclose(pFile);
	if (iReqComp > 0) m_Comp = iReqComp;
	m_Height *= iLayers; // interleaved images
	return iLayers;
}

int StbImage::LoadGifFromMemory(_In_ unsigned char* data, unsigned int size, _Outptr_opt_ int** delays, Format format)
{
	YAGLPP_FREE(m_Pixels);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte = 1; // original depth always 1
	m_Pixels =
		(m_Byte == 1) ? stbi_load_gif_from_memory(data, size, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_16_gif_from_memory(data, size, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_gif_from_memory(data, size, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp);

	// FAILED TO LOAD GIF IMAGE FROM BINARY RESOURCE
	YAGLPP_STB_ERROR(!m_Pixels);

	if (iReqComp > 0) m_Comp = iReqComp;
	m_Height *= iLayers; // interleaved images
	return iLayers;
}

int StbImage::LoadGifFromCallbacks(_In_ Callbacks const* clbk, _In_ void* user, _Outptr_opt_ int** delays, Format format)
{
	YAGLPP_FREE(m_Pixels);
	m_Byte = ((int)format & YAGLPP_STBIMAGE_BYTE) >> 4;
	int iLayers, iReqComp = (int)format & YAGLPP_STBIMAGE_COMP;
	if (m_Byte == 0) m_Byte = 1; // original depth always 1
	m_Pixels =
		(m_Byte == 1) ? stbi_load_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(m_Byte == 2) ? (stbi_uc*)stbi_load_16_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp) :
		(stbi_uc*)stbi_loadf_gif_from_callbacks((stbi_io_callbacks*)clbk, user, delays, &m_Width, &m_Height, &iLayers, &m_Comp, iReqComp);

	// FAILED TO LOAD GIF IMAGE FROM I/O CALLBACK
	YAGLPP_STB_ERROR(!m_Pixels);

	if (iReqComp > 0) m_Comp = iReqComp;
	m_Height *= iLayers; // interleaved images
	return iLayers;
}

void StbImage::SetFlipVerticallyOnLoad(bool flip)
{
	stbi_set_flip_vertically_on_load((int)flip);
}

void StbImage::SetUnpremultiplyOnLoad(bool unpremultiply)
{
	stbi_set_unpremultiply_on_load((int)unpremultiply);
}

void StbImage::SetWriteForcePngFilter(int filter)
{
	// INVALID PNG FILTER MODE PARAMETER
	YAGLPP_ASSERT((filter >= -1) && (filter <= 5));

	stbi_write_force_png_filter = filter;
}

void StbImage::SetWriteJpegQuality(int quality)
{
	// INVALID JPEG QUALITY PARAMETER
	YAGLPP_ASSERT((quality >= 1) && (quality <= 100));

	yaglpp_stb_jpeg_quality = quality;
}

void StbImage::SetWritePngCompressionLevel(int comp)
{
	// INVALID PNG COMPESSION LEVEL PARAMETER
	YAGLPP_ASSERT((comp >= 0) && (comp <= 9));

	stbi_write_png_compression_level = comp;
}

void StbImage::SetWriteTgaWithRle(bool rle)
{
	stbi_write_tga_with_rle = (int)rle;
}

void StbImage::WriteBmp(_In_z_ const char* file)
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	// FILE PARAMETER COULD NOT BE NULL
	YAGLPP_ASSERT(file != nullptr);

	// STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	YAGLPP_ASSERT(GetDepth() == Format::Unsigned8);

	int r = stbi_write_bmp(file, m_Width, m_Height, m_Comp, m_Pixels);

	// STB FAILED TO WRITE INTO BMP FILE
	YAGLPP_RUNTIME(!r, yaglpp_stb_write_error);
}

void StbImage::WriteHdr(_In_z_ const char* file)
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	// FILE PARAMETER COULD NOT BE NULL
	YAGLPP_ASSERT(file != nullptr);

	// STB IMAGE DATA MUST BE 32F-BITS PER CHANNEL
	YAGLPP_ASSERT(GetDepth() == Format::Float32);

	int r = stbi_write_hdr(file, m_Width, m_Height, m_Comp, (float*)m_Pixels);

	// STB FAILED TO WRITE INTO HDR FILE
	YAGLPP_RUNTIME(!r, yaglpp_stb_write_error);
}

void StbImage::WriteJpg(_In_z_ const char* file)
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	// FILE PARAMETER COULD NOT BE NULL
	YAGLPP_ASSERT(file != nullptr);

	// STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	YAGLPP_ASSERT(GetDepth() == Format::Unsigned8);

	int r = stbi_write_jpg(file, m_Width, m_Height, m_Comp, m_Pixels, yaglpp_stb_jpeg_quality);

	// STB FAILED TO WRITE INTO JPEG FILE
	YAGLPP_RUNTIME(!r, yaglpp_stb_write_error);
}

void StbImage::WritePng(_In_z_ const char* file)
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	// FILE PARAMETER COULD NOT BE NULL
	YAGLPP_ASSERT(file != nullptr);

	// STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	YAGLPP_ASSERT(GetDepth() == Format::Unsigned8);

	int r = stbi_write_png(file, m_Width, m_Height, m_Comp, m_Pixels, m_Width * m_Comp);

	// STB FAILED TO WRITE INTO PNG FILE
	YAGLPP_RUNTIME(!r, yaglpp_stb_write_error);
}

void StbImage::WriteTga(_In_z_ const char* file)
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	// FILE PARAMETER COULD NOT BE NULL
	YAGLPP_ASSERT(file != nullptr);

	// STB IMAGE DATA MUST BE 8-BITS PER CHANNEL
	YAGLPP_ASSERT(GetDepth() == Format::Unsigned8);

	int r = stbi_write_tga(file, m_Width, m_Height, m_Comp, m_Pixels);

	// STB FAILED TO WRITE INTO TGA FILE
	YAGLPP_RUNTIME(!r, yaglpp_stb_write_error);
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#if defined (YAGLPP_MSVC) && defined (YAGLPP_IMPLEMENTATION)
void StbImage::InfoFromResource(int rcid)
{
	unsigned int uSize;
	unsigned char* pData = yaglpp_load_resource(rcid, &uSize);
	InfoFromMemory(pData, uSize);
}

bool StbImage::Is16bitFromResource(int rcid)
{
	unsigned int uSize;
	unsigned char* pData = yaglpp_load_resource(rcid, &uSize);
	return Is16BitFromMemory(pData, uSize);
}

bool StbImage::IsHdrFromResource(int rcid)
{
	unsigned int uSize;
	unsigned char* pData = yaglpp_load_resource(rcid, &uSize);
	return IsHdrFromMemory(pData, uSize);
}

void StbImage::LoadFromResource(int rcid, Format format)
{
	unsigned int uSize;
	unsigned char* pData = yaglpp_load_resource(rcid, &uSize);
	LoadFromMemory(pData, uSize, format);
}

int StbImage::LoadGifFromResource(int rcid, _Outptr_opt_ int** delays, Format format)
{
	unsigned int uSize;
	unsigned char* pData = yaglpp_load_resource(rcid, &uSize);
	return LoadGifFromMemory(pData, uSize, delays, format);
}
#endif // #if defined (YAGLPP_MSVC) && defined (YAGLPP_IMPLEMENTATION)

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
bool yaglpp_stb_error(bool c)
{
	if (c) std::cout << "YAGL++ STB image error: " << stbi_failure_reason() << std::endl;
	return !(c);
}

_Ret_notnull_ unsigned char* StbImage::GetPixels() const
{
	// STB IMAGE OBJECT IS EMPTY
	YAGLPP_ASSERT(IsImage());

	return m_Pixels;
}
#endif // YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline _Ret_notnull_ unsigned char* StbImage::GetPixels() const
{
	return m_Pixels;
}
#endif // YAGLPP_INLINE_IMPLEMENTATION
#endif // #ifndef YAGLPP_STB_IMAGE_H
