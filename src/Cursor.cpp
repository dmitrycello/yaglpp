#define YAGLPP_BUILD_LIB
#include <yaglpp/Cursor.h>
#include <yaglpp/StbImage.h>
#include <yaglpp/FreeImage.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
namespace glfw {
void Cursor::createCursor(StbImage& si, int xhot, int yhot)
{
	YAGLPP_ASSERT(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	_cursor_set(glfwCreateCursor(&glfwImage, xhot, yhot));
}

#ifdef YAGLPP_FREEIMAGE_LIB
void Cursor::createCursor(FreeImage& fi, int xhot, int yhot, unsigned int page)
{
	GLFWimage glfwImage;
	glfwImage.pixels = fi.allocateImage(&glfwImage.width, &glfwImage.height, page);
	GLFWcursor* pCursor = glfwCreateCursor(&glfwImage, xhot, yhot);
	_cursor_set(pCursor);
	YAGLPP_FREE(glfwImage.pixels); // Free allocated buffer
}

void Cursor::createCursor(int rcid, unsigned int page)
{
	LPPOINT lpHotspot;
	FreeImage freeImage;
	if (freeImage.loadCursor(rcid, &lpHotspot) > (int)page)
	{
		createCursor(freeImage, lpHotspot[page].x, lpHotspot[page].y, page);
	}
	YAGLPP_FREE(lpHotspot); // Free allocated buffer
}

void Cursor::createCursor(_In_z_ const char* filepath, unsigned int page)
{
	LPPOINT lpHotspot;
	FreeImage freeImage;
	if (freeImage.loadCursor(filepath, &lpHotspot) > (int)page)
	{
		createCursor(freeImage, lpHotspot[page].x, lpHotspot[page].y, page);
	}
	YAGLPP_FREE(lpHotspot); // Free allocated buffer
}
#endif // #ifdef YAGLPP_FREEIMAGE_LIB

#ifdef _DEBUG
GLFWcursor* Cursor::_cursor()
{
	YAGLPP_ASSERT(m_pCursor != nullptr); // GLFW CURSOR OBJECT IS EMPTY
	return m_pCursor;
}

void Cursor::_cursor_set(GLFWcursor* cursor)
{
	YAGLPP_ASSERT(m_pCursor == nullptr); // GLFW CURSOR OBJECT IS NOT EMPTY
	m_pCursor = cursor;
}
#endif // _DEBUG
} // namespace glfw
