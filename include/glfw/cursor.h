#ifndef YAGLPP_GLPP_H
#error YAGL++: The header cannot be directly included
#endif

#ifndef YAGLPP_CURSOR_H
#define YAGLPP_CURSOR_H

namespace glfw {
/*(M) GLFW cursor object root class*/
class Cursor
{
public:
	enum class Mode : int;
	enum class Shape : int;

	/*(1) Constructs empty cursor object*/
	Cursor()
	{
		m_Cursor = nullptr;
	}

	/*(M) (2) Constructs standard cursor object with <Create>*/
	Cursor(Shape shape) : Cursor()
	{
		Create(shape);
	}

	/*(M) (3) Constructs cursor object with <Create>*/
	Cursor(_In_ const GLFWimage* image, int xhot, int yhot) : Cursor()
	{
		Create(image, xhot, yhot);
	}

	/*(M) (4) Constructs cursor object with <Create>*/
	Cursor(StbImage& si, int xhot, int yhot) : Cursor()
	{
		Create(si, xhot, yhot);
	}

	/*(M) Cleans up the valid cursor object*/
	~Cursor()
	{
		Destroy();
	}

	/*(M) (1) Creates a cursor with a standard shape, that can be set to a window
	@param Standard cursor shape enumerator*/
	void Create(Shape shape);

	/*(M) (2) Creates a new custom cursor image object that can be set to a window with <SetCursor>
	@param [in] The desired cursor image
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void Create(_In_ const GLFWimage* image, int xhot, int yhot);

	/*(M) (3) Creates a new custom cursor image object that can be set to a window. The image format must be <RgbAlpfa8>
	@param [in] The stb image object
	@param The desired x-coordinate, in pixels, of the cursor hotspot
	@param The desired y-coordinate, in pixels, of the cursor hotspot*/
	void Create(StbImage& stb, int xhot, int yhot);

	/*(M) Destroys previously created cursor object*/
	void Destroy();

	/*Gets the last loaded opaque cursor object
	@return The opaque GLFW cursor object*/
	_Ret_notnull_ GLFWcursor* Get() const;

	/*Check if valid cursor object. MSVC getter for <cursor> property
	@return True if valid cursor object, false otherwise*/
	bool IsCursor() const
	{
		return m_Cursor != nullptr;
	}

#ifdef YAGLPP_CLASS_PROPERTIES
	/*Read-only property to check if valid cursor object*/
	__declspec(property(get = IsCursor)) bool cursor;
#endif // #ifdef YAGLPP_CLASS_PROPERTIES

private:
	GLFWcursor* m_Cursor;
}; // class Cursor

/*GLFW cursor input mode enumerator*/
enum class Cursor::Mode : int
{
	/*Normal cursor value (default). Makes the cursor visible and behaving normally*/
	Normal = GLFW_CURSOR_NORMAL,

	/*Hidden cursor value. Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving*/
	Hidden = GLFW_CURSOR_HIDDEN,

	/*Disabled cursor value. Hides and grabs the cursor, providing virtual and unlimited cursor movement. This is useful for implementing for example 3D camera controls*/
	Disabled = GLFW_CURSOR_DISABLED,

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*Captured cursor value. Makes the cursor visible but confined to the content area of the window*/
	Captured = GLFW_CURSOR_CAPTURED,
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
};

/*GLFW standard cursor shape enumerator*/
enum class Cursor::Shape : int
{
	/*The regular arrow cursor shape*/
	Arrow = GLFW_ARROW_CURSOR,

	/*The regular arrow cursor shape*/
	Ibeam = GLFW_IBEAM_CURSOR,

	/*The crosshair cursor shape*/
	Crosshair = GLFW_CROSSHAIR_CURSOR,

	/*The hand cursor shape. This is an alias to <PointingHand> in later versions*/
	Hand = GLFW_HAND_CURSOR,

	/*The horizontal resize arrow cursor shape. This is an alias to <ResizeEw> in later versions*/
	Hresize = GLFW_HRESIZE_CURSOR,

	/*The vertical resize arrow cursor shape. This is an alias to <ResizeNs> in later versions*/
	Vresize = GLFW_VRESIZE_CURSOR,

#ifdef YAGLPP_NO_GLFW_LEGACY
	/*The pointing hand cursor shape*/
	PointingHand = GLFW_POINTING_HAND_CURSOR,

	/*The horizontal resize/move arrow shape. This is usually a horizontal double-headed arrow*/
	ResizeEw = GLFW_RESIZE_EW_CURSOR,

	/*The vertical resize/move shape. This is usually a vertical double-headed arrow*/
	ResizeNs = GLFW_RESIZE_NS_CURSOR,

	/*The top-left to bottom-right diagonal resize/move shape. This is usually a diagonal double-headed arrow. May be unavailable under macOS, Wayland and X11*/
	ResizeNwse = GLFW_RESIZE_NWSE_CURSOR,

	/*The top-right to bottom-left diagonal resize/move shape. This is usually a diagonal double-headed arrow. May be unavailable under macOS, Wayland and X11*/
	ResizeNesw = GLFW_RESIZE_NESW_CURSOR,

	/*The omni-directional resize cursor/move shape. This is usually either a combined horizontal and vertical double-headed arrow or a grabbing hand*/
	ResizeAll = GLFW_RESIZE_ALL_CURSOR,

	/*The operation-not-allowed shape. This is usually a circle with a diagonal line through it. May be unavailable under Wayland and X11*/
	NotAllowed = GLFW_NOT_ALLOWED_CURSOR,
#endif // #ifdef YAGLPP_NO_GLFW_LEGACY
};

#ifdef YAGLPP_IMPLEMENTATION
void Cursor::Create(Shape shape)
{
	Destroy();
	m_Cursor = glfwCreateStandardCursor((int)shape);
}

void Cursor::Create(_In_ const GLFWimage* image, int xhot, int yhot)
{
	Destroy();
	m_Cursor = glfwCreateCursor(image, xhot, yhot);
}

void Cursor::Create(StbImage& stb, int xhot, int yhot)
{
	// IVALID IMAGE PIXEL FORMAT
	YAGLPP_ASSERT(stb.GetFormat() == StbImage::Format::RgbAlpha8);

	GLFWimage glfwImage = { stb.GetWidth(), stb.GetHeight(), stb.GetPixels() };
	Create(&glfwImage, xhot, yhot);
}

void Cursor::Destroy()
{
	// MUST BE CALLED ONLY FROM THE MAIN THREAD
	YAGLPP_ASSERT(Thread::IsMainCurrent());

	if (m_Cursor != nullptr)
	{
		glfwDestroyCursor(m_Cursor);
		m_Cursor = nullptr;
	}
}
#endif // #ifdef YAGLPP_IMPLEMENTATION

#ifdef YAGLPP_DEBUG_IMPLEMENTATION
_Ret_notnull_ GLFWcursor* Cursor::Get() const
{
	// CURSOR OBJECT IS EMPTY
	YAGLPP_ASSERT(IsCursor());

	return m_Cursor;
}
#endif // #ifdef YAGLPP_DEBUG_IMPLEMENTATION

#ifdef YAGLPP_INLINE_IMPLEMENTATION
inline _Ret_notnull_ GLFWcursor* Cursor::Get() const
{
	return m_Cursor;
}
#endif // #ifdef YAGLPP_INLINE_IMPLEMENTATION
} // namespace glfw
#endif // #ifndef YAGLPP_CURSOR_H
