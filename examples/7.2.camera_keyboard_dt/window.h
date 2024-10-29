/*LearnOpenGL: window class derived from glfw::Window*/
class Window : public glfw::Window
{
    using glfw::Window::Window; // base constructors
    glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // camera vecs (private)
    glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
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
    /*LearnOpenGL: get camera/view transformation using glm::lookAt*/
    glm::mat4 getView()
    {
        return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
    }
    /*LearnOpenGL: input processing from the render loop gives immediate effect*/
    void processInput()
    {
        static float lastFrame = 0.0f; // use static instead of global
        float currentFrame = (float)glfw::getTime();
        float deltaTime = currentFrame - lastFrame; // time between current frame and last frame
        lastFrame = currentFrame;

        float cameraSpeed = (2.5f * deltaTime);
        if (getKey(glfw::KeyboardKey::KeyLeftControl) == glfw::KeyAction::Press)
            m_CameraPos += cameraSpeed * m_CameraFront;
        if (getKey(glfw::KeyboardKey::KeyLeftAlt) == glfw::KeyAction::Press)
            m_CameraPos -= cameraSpeed * m_CameraFront;
        if (getKey(glfw::KeyboardKey::KeyUp) == glfw::KeyAction::Press)
            m_CameraPos += cameraSpeed * m_CameraUp;
        if (getKey(glfw::KeyboardKey::KeyDown) == glfw::KeyAction::Press)
            m_CameraPos -= cameraSpeed * m_CameraUp;
        if (getKey(glfw::KeyboardKey::KeyLeft) == glfw::KeyAction::Press)
            m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
        if (getKey(glfw::KeyboardKey::KeyRight) == glfw::KeyAction::Press)
            m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    }
};
