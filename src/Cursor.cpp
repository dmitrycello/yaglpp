#define YAGLPP_BUILD_LIB
#include <yaglpp/Cursor.h>
#include <yaglpp/Thread.h>
#include <yaglpp/StbImage.h>
#include <yaglpp/FreeImage.h>
#pragma comment(lib, YAGLPP_GLFW_LIB)
namespace glfw {
void Cursor::createCursor(StbImage& si, int xhot, int yhot)
{
	_YAGLPP_ASSERT_(si.getFormat() == StbFormat::RgbAlpha8); // IVALID IMAGE PIXEL FORMAT
	GLFWimage glfwImage = { si.getWidth(), si.getHeight(), (LPBYTE)si.getPixels() };
	_cursor_set(glfwCreateCursor(&glfwImage, xhot, yhot));
}

#ifndef YAGLPP_NO_FREEIMAGE
void Cursor::createCursor(FreeImage& fi, int xhot, int yhot, unsigned int page)
{
	GLFWimage glfwImage;
	glfwImage.pixels = fi.allocateImage(&glfwImage.width, &glfwImage.height, page);
	_cursor_set(glfwCreateCursor(&glfwImage, xhot, yhot));
	_YAGLPP_FREE_(glfwImage.pixels); // Free allocated buffer
}

void Cursor::createCursor(int rcid, unsigned int page)
{
	LPPOINT lpHotspot;
	FreeImage freeImage;
	if (freeImage.loadCursor(rcid, &lpHotspot) > (int)page)
	{
		createCursor(freeImage, lpHotspot[page].x, lpHotspot[page].y, page);
	}
	_YAGLPP_FREE_(lpHotspot); // Free allocated buffer
}

void Cursor::createCursor(_In_z_ const char* filepath, unsigned int page)
{
	LPPOINT lpHotspot;
	FreeImage freeImage;
	if (freeImage.loadCursor(filepath, &lpHotspot) > (int)page)
	{
		createCursor(freeImage, lpHotspot[page].x, lpHotspot[page].y, page);
	}
	_YAGLPP_FREE_(lpHotspot); // Free allocated buffer
}
#endif // #ifndef YAGLPP_NO_FREEIMAGE

#ifdef _DEBUG
GLFWcursor* Cursor::_cursor()
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(m_pCursor != nullptr); // GLFW CURSOR OBJECT IS EMPTY
	return m_pCursor;
}

void Cursor::_cursor_set(GLFWcursor* cursor)
{
	_YAGLPP_ASSERT_(isMainThreadCurrent()); // MUST BE CALLED ONLY FROM THE MAIN THREAD
	_YAGLPP_ASSERT_(m_pCursor == nullptr); // GLFW CURSOR OBJECT IS NOT EMPTY
	m_pCursor = cursor;
}
#endif // _DEBUG
} // namespace glfw
