#pragma once
#include "glfw3pp.h"
namespace glfw {
/*GLFW standard cursor shape enumerator*/
enum class CursorShape : int
{
	/*The regular arrow cursor shape*/
	ArrowCursor = GLFW_ARROW_CURSOR,

	/*The regular arrow cursor shape*/
	IbeamCursor = GLFW_IBEAM_CURSOR,

	/*The crosshair cursor shape*/
	CrosshairCursor = GLFW_CROSSHAIR_CURSOR,

	/*The hand cursor shape. This is an alias to <PointingHandCursor> in later versions*/
	HandCursor = GLFW_HAND_CURSOR,

	/*The horizontal resize arrow cursor shape. This is an alias to <ResizeEwCursor> in later versions*/
	HresizeCursor = GLFW_HRESIZE_CURSOR,

	/*The vertical resize arrow cursor shape. This is an alias to <ResizeNsCursor> in later versions*/
	VresizeCursor = GLFW_VRESIZE_CURSOR,

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*The pointing hand cursor shape*/
	PointingHandCursor = GLFW_POINTING_HAND_CURSOR,

	/*The horizontal resize/move arrow shape. This is usually a horizontal double-headed arrow*/
	ResizeEwCursor = GLFW_RESIZE_EW_CURSOR,

	/*The vertical resize/move shape. This is usually a vertical double-headed arrow*/
	ResizeNsCursor = GLFW_RESIZE_NS_CURSOR,

	/*The top-left to bottom-right diagonal resize/move shape. This is usually a diagonal double-headed arrow. May be unavailable under macOS, Wayland and X11*/
	ResizeNwseCursor = GLFW_RESIZE_NWSE_CURSOR,

	/*The top-right to bottom-left diagonal resize/move shape. This is usually a diagonal double-headed arrow. May be unavailable under macOS, Wayland and X11*/
	ResizeNeswCursor = GLFW_RESIZE_NESW_CURSOR,

	/*The omni-directional resize cursor/move shape. This is usually either a combined horizontal and vertical double-headed arrow or a grabbing hand*/
	ResizeAllCursor = GLFW_RESIZE_ALL_CURSOR,
	
	/*The operation-not-allowed shape. This is usually a circle with a diagonal line through it. May be unavailable under Wayland and X11*/
	NotAllowedCursor = GLFW_NOT_ALLOWED_CURSOR,
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
};

/*(M) GLFW cursor object root class*/
class Cursor
{
private:
	friend class Window;
	GLFWcursor* _mpCursor = nullptr;
	GLFWcursor* _cursor();
	void _cursor_set(GLFWcursor* cursor);

public:
	/*(1) Constructs empty cursor object*/
	Cursor() {}

	/*(M) (2) Constructs cursor object with <createStandardCursor>*/
	Cursor(CursorShape shape)
	{
		createStandardCursor(shape);
	}

	/*(M) (3) Constructs cursor object with <createCursor>*/
	Cursor(_In_ const GLFWimage* image, int xhot, int yhot)
	{
		createCursor(image, xhot, yhot);
	}

	/*(M) (4) Constructs cursor object with <createCursor>*/
	Cursor(StbImage& si, int xhot, int yhot)
	{
		createCursor(si, xhot, yhot);
	}

	/*(M) Cleans up the valid cursor object*/
	~Cursor()
	{
		if (isCursor())
		{
			destroyCursor();
		}
	}

	/*(M) (1) Creates a new custom cursor image object that can be set to a window with <setCursor>
	@param [in] The desired cursor image
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void createCursor(_In_ const GLFWimage* image, int xhot, int yhot)
	{
		_cursor_set(glfwCreateCursor(image, xhot, yhot));
	}

	/*(M) (2) Creates a new custom cursor image object that can be set to a window
	@param [in] The stb image object
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void createCursor(StbImage& si, int xhot, int yhot);

	/*(M) Creates a cursor with a standard shape, that can be set to a window
	@param Standard cursor shape enumerator*/
	void createStandardCursor(CursorShape shape)
	{
		_cursor_set(glfwCreateStandardCursor((int)shape));
	}

	/*(M) Destroys previously created cursor object*/
	void destroyCursor()
	{
		glfwDestroyCursor(_cursor());
		_mpCursor = nullptr;
	}

	/*Check if valid cursor object. Used as a getter of <cursor> property
	@return True if valid cursor object, false otherwise*/
	bool isCursor() const
	{
		return _mpCursor != nullptr;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if valid cursor object*/
	__declspec(property(get = isCursor)) bool cursor;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES
}; // class Cursor
} // namespace glfw

#include "Thread.h"
#include "StbImage.h"

namespace glfw {
#ifdef YAGLPP_IMPLEMENTATION
void Cursor::createCursor(StbImage& si, int xhot, int yhot)
{
	YAGLPP_ASSERT(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	_cursor_set(glfwCreateCursor(&glfwImage, xhot, yhot));
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
GLFWcursor* Cursor::_cursor()
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(_mpCursor != nullptr); // GLFW CURSOR OBJECT IS EMPTY
	return _mpCursor;
}

void Cursor::_cursor_set(GLFWcursor* cursor)
{
	YAGLPP_ASSERT(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(_mpCursor == nullptr); // GLFW CURSOR OBJECT IS NOT EMPTY
	_mpCursor = cursor;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline GLFWcursor* Cursor::_cursor()
{
	return _mpCursor;
}

inline void Cursor::_cursor_set(GLFWcursor* cursor)
{
	_mpCursor = cursor;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
