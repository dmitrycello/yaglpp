/*LearnOpenGL: window class derived from glfw::Window*/
class Window : public glfw::Window
{
    float m_fMixValue = 0.2f; // mixer value
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
    }

public:
    /*LearnOpenGL: read-only mix value getter*/
    float getMixValue() { return m_fMixValue; }
    /*LearnOpenGL: input processing from the render loop gives immediate effect*/
    void processInput()
    {
        if (getKey(glfw::KeyboardKey::KeyUp) == glfw::KeyAction::Press)
        {
            if (m_fMixValue < 1.0f) m_fMixValue += 0.001f;
        } // change this value accordingly (might be too slow or too fast based on system hardware)
        if (getKey(glfw::KeyboardKey::KeyDown) == glfw::KeyAction::Press)
        {
            if (m_fMixValue > 0.0f) m_fMixValue -= 0.001f;
        }
    }
};
