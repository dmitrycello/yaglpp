/*LearnOpenGL: window class derived from glfw::Window*/
class Window : public glfw::Window
{
    using glfw::Window::Window; // base constructors
    float m_Fov = 45.0f;
    float m_Pitch = 0.0f;
    float m_LastX = 0.0f;
    float m_LastY = 0.0f;
    float m_Yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // camera (private)
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

        if (getMouseButton(glfw::MouseButton::MouseButtonLeft) != glfw::MouseAction::Press)
        {
            return; // let's react only when left mouse is pressed
        }

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f) m_Pitch = 89.0f; // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_CameraFront = glm::normalize(front);
    }
    /*LearnOpenGL: whenever the mouse scroll wheel scrolls, this callback is called*/
    void onScroll(double xoffset, double yoffset)
    {
        m_Fov -= (float)yoffset;
        if (m_Fov < 1.0f)
            m_Fov = 1.0f;
        if (m_Fov > 45.0f)
            m_Fov = 45.0f;
    }

public:
    /*LearnOpenGL: get current window aspect ratio*/
    float getAspectRatio() const
    {
        return (float)getWindowWidth() / (float)getWindowHeight();
    }
    /*LearnOpenGL: get projection transformation using glm::perspective*/
    glm::mat4 getProjection()
    {
        return glm::perspective(glm::radians(m_Fov), getAspectRatio(), 0.1f, 100.0f);
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
