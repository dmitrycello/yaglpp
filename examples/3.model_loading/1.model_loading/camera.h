#pragma once
/*LearnOpenGL: Custom implementation of the LookAt function*/
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -position.x; // Fourth column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

/*LearnOpenGL: Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods*/
enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

const float YAW         = -90.0f; // Default camera values
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

/*LearnOpenGL: An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL*/
class Camera
{
    glm::vec3 m_Position; // camera Attributes
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    float m_Yaw; // euler Angles
    float m_Pitch;
    float m_MovementSpeed; // camera options
    float m_MouseSensitivity;
    float m_Zoom;

    void _updateCameraVectors()
    {
        glm::vec3 front; // calculates the front vector from the Camera's (updated) Euler Angles
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)); // calculate the new Front vector
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp)); // also re-calculate the Right and Up vector
        m_Up = glm::normalize(glm::cross(m_Right, m_Front)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    }

public:
    /*LearnOpenGL: (1) constructor with vectors*/
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
    {
        m_Position = position;
        m_WorldUp = up;
        m_Yaw = yaw;
        m_Pitch = pitch;
        _updateCameraVectors();
    }
    /*LearnOpenGL: (2) constructor with scalar values*/
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
    {
        m_Position = glm::vec3(posX, posY, posZ);
        m_WorldUp = glm::vec3(upX, upY, upZ);
        m_Yaw = yaw;
        m_Pitch = pitch;
        _updateCameraVectors();
    }
    /*LearnOpenGL: vec3 position getter*/
    glm::vec3 getPosition() const
    {
        return m_Position;
    }
    /*LearnOpenGL: vec3 front getter*/
    glm::vec3 getFront() const
    {
        return m_Front;
    }
    /*LearnOpenGL: get projection transformation using glm::perspective*/
    glm::mat4 getProjectionMatrix(float aspect)
    {
        return glm::perspective(glm::radians(m_Zoom), aspect, 0.1f, 100.0f);
    }
    /*LearnOpenGL: returns the view matrix calculated using Euler Angles and the LookAt Matrix*/
    glm::mat4 getViewMatrix()
    {
        return calculate_lookAt_matrix(m_Position, m_Position + m_Front, m_Up);
        //return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }
    /*LearnOpenGL: processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)*/
    void ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD)
            m_Position += m_Front * velocity;
        if (direction == CameraMovement::BACKWARD)
            m_Position -= m_Front * velocity;

        if (direction == CameraMovement::RIGHT)
            m_Position += m_Right * velocity;
        if (direction == CameraMovement::LEFT)
            m_Position -= m_Right * velocity;

        if (direction == CameraMovement::UP)
            m_Position += m_Up * velocity;
        if (direction == CameraMovement::DOWN)
            m_Position -= m_Up * velocity;
    }
    /*LearnOpenGL: processes input received from a mouse input system. Expects the offset value in both the x and y direction.*/
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw   += xoffset;
        m_Pitch += yoffset;

        if (constrainPitch) // make sure that when pitch is out of bounds, screen doesn't get flipped
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }
        _updateCameraVectors(); // update Front, Right and Up Vectors using the updated Euler angles
    }
    /*LearnOpenGL: processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis*/
    void ProcessMouseScroll(float yoffset)
    {
        m_Zoom -= (float)yoffset;
        if (m_Zoom < 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom > 45.0f)
            m_Zoom = 45.0f;
    }
};
