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

#ifdef GLPP_NO_GLFW_LEGACY
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
#endif // #ifdef GLPP_NO_GLFW_LEGACY
};

/*GLFW cursor object root class*/
class Cursor
{
private:
	friend class Window;
	GLFWcursor* m_pCursor;
	GLFWcursor* _cursor();
	void _cursor_set(GLFWcursor* cursor);

public:
	/*(1) Constructs empty cursor object*/
	Cursor()
	{
		m_pCursor = nullptr;
	}

	/*(2) Constructs cursor object with <createStandardCursor>*/
	Cursor(CursorShape shape)
	{
		createStandardCursor(shape);
	}

	/*(3) Constructs cursor object with <createCursor>*/
	Cursor(_In_ const GLFWimage* image, int xhot, int yhot)
	{
		createCursor(image, xhot, yhot);
	}

	/*(4) Constructs cursor object with <createCursor>*/
	Cursor(StbImage& si, int xhot, int yhot)
	{
		createCursor(si, xhot, yhot);
	}

	/*Cleans up the valid cursor object*/
	~Cursor()
	{
		if (isCursor())
		{
			destroyCursor();
		}
	}

	/*(1) Creates a new custom cursor image object that can be set to a window with <setCursor>
	@param [in] The desired cursor image
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void createCursor(_In_ const GLFWimage* image, int xhot, int yhot)
	{
		_cursor_set(glfwCreateCursor(image, xhot, yhot));
	}

	/*(2) Creates a new custom cursor image object that can be set to a window
	@param [in] The stb image object
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void createCursor(StbImage& si, int xhot, int yhot);

	/*Creates a cursor with a standard shape, that can be set to a window
	@param Standard cursor shape enumerator*/
	void createStandardCursor(CursorShape shape)
	{
		_cursor_set(glfwCreateStandardCursor((int)shape));
	}

	/*Destroys previously created cursor object*/
	void destroyCursor()
	{
		glfwDestroyCursor(_cursor());
		m_pCursor = nullptr;
	}

	/*Check if valid cursor object
	@return True if valid cursor object, false otherwise*/
	bool isCursor()
	{
		return m_pCursor != nullptr;
	}

#ifdef GLPP_FREEIMAGE_LIB
	/*(5) Constructs cursor object with <createCursor>*/
	Cursor(FreeImage& fi, int xhot, int yhot, unsigned int page = 0)
	{
		createCursor(fi, xhot, yhot, page);
	}

	/*(6) Constructs cursor object with <createCursor>*/
	Cursor(int rcid, unsigned int page = 0)
	{
		createCursor(rcid, page);
	}

	/*(7) Constructs cursor object with <createCursor>*/
	Cursor(_In_z_ const char* filepath, unsigned int page = 0)
	{
		createCursor(filepath, page);
	}

	/*(3) Creates a new custom cursor image object that can be set to a window
	@param [in] The free image object
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot
	@param Page index of the free image object. Must be less than the image count*/
	void createCursor(FreeImage& fi, int xhot, int yhot, unsigned int page = 0);

	/*(4) Creates a new custom cursor image object that can be set to a window
	@param The cursor resource id of <RCDATA> type
	@param Page index in the cursor resource. Must be less than the image count*/
	void createCursor(int rcid, unsigned int page = 0);

	/*(5) Creates a new custom cursor image object that can be set to a window
	@param [in] The cursor file path
	@param Page index in the cursor file. Must be less than the image count*/
	void createCursor(_In_z_ const char* filepath, unsigned int page = 0);
#endif // #ifdef GLPP_FREEIMAGE_LIB
}; // class Cursor

#ifndef _DEBUG
inline GLFWcursor* Cursor::_cursor()
{
	return m_pCursor;
}

inline void Cursor::_cursor_set(GLFWcursor* cursor)
{
	m_pCursor = cursor;
}
#endif // #ifndef _DEBUG
} // namespace glfw
