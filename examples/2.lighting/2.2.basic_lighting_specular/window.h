/*LearnOpenGL: window class derived from glfw::Window*/
class Window : public glfw::Window
{
    using glfw::Window::Window; // base constructors
    float m_LastX = 0.0f;
    float m_LastY = 0.0f;
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
    /*LearnOpenGL: whenever the mouse moves, this callback is called*/
    void onCursorPos(double xposIn, double yposIn)
    {
        static bool firstMouse = true; // use static instead of global
        float xpos = (float)xposIn;
        float ypos = (float)yposIn;

        if (firstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top
        m_LastX = xpos;
        m_LastY = ypos;

        if (getMouseButton(glfw::MouseButton::MouseButtonLeft) == glfw::MouseAction::Press)
            camera.ProcessMouseMovement(xoffset, yoffset);
    }
    /*LearnOpenGL: whenever the mouse scroll wheel scrolls, this callback is called*/
    void onScroll(double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll((float)yoffset);
    }

public:
    /*LearnOpenGL: camera object*/
    Camera camera = glm::vec3(0.0f, 0.0f, 3.0f);
    /*LearnOpenGL: get current window aspect ratio*/
    float getAspectRatio() const
    {
        return (float)getWindowWidth() / (float)getWindowHeight();
    }
    /*LearnOpenGL: process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly*/
    void processInput()
    {
        static bool firstInput = true; // use static instead of global
        static float lastFrame = 0.0f;
        float currentFrame = (float)glfw::getTime();

        if (firstInput)
        {
            lastFrame = currentFrame;
            firstInput = false;
        }
        float deltaTime = currentFrame - lastFrame; // time between current frame and last frame
        lastFrame = currentFrame;

        if (getKey(glfw::KeyboardKey::KeyLeftControl) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        if (getKey(glfw::KeyboardKey::KeyLeftAlt) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);

        if (getKey(glfw::KeyboardKey::KeyLeft) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        if (getKey(glfw::KeyboardKey::KeyRight) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);

        if (getKey(glfw::KeyboardKey::KeyUp) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::UP, deltaTime);
        if (getKey(glfw::KeyboardKey::KeyDown) == glfw::KeyAction::Press)
            camera.ProcessKeyboard(CameraMovement::DOWN, deltaTime);
    }
};
