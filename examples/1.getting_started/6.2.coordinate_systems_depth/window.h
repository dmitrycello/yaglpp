/*LearnOpenGL: window class derived from glfw::Window*/
class Window : public glfw::Window
{
    using glfw::Window::Window; // base constructors
    /*LearnOpenGL: whenever the window size changed (by OS or user resize) this callback function executes*/
    void onFramebufferSize(int width, int height)
    {
        gl::viewport(0, 0, width, height);
    }
    /*LearnOpenGL: whenever keys are pressed/released this callback function executes*/
    void onKey(glfw::KeyboardKey key, int scancode, glfw::KeyAction action, glfw::KeyModifier mods)
    {
        if (key == glfw::KeyboardKey::KeyEscape) windowShouldClose = true;
        if (key == glfw::KeyboardKey::KeyF1) windowFullscreen = true; // fullscreen mode on/off
        if (key == glfw::KeyboardKey::KeyF2) windowFullscreen = false;
    }

public:
    /*LearnOpenGL: get current window aspect ratio*/
    float getAspectRatio() const
    {
        return (float)getWindowWidth() / (float)getWindowHeight();
    }
};
