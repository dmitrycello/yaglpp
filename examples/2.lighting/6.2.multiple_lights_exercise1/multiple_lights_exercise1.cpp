// multiple_lights.cpp
#include "config.h"
#include "camera.h"
#include "window.h"
#include "shader.h"
#include "resource.h"

#define MULTIPLE_LIGHTS_DESERT 1 
#define MULTIPLE_LIGHTS_FACTORY 2
#define MULTIPLE_LIGHTS_HORROR 3
#define MULTIPLE_LIGHTS_BIOCHEMICAL_LAB 4

// Define exercise theme
#define MULTIPLE_LIGHTS_THEME MULTIPLE_LIGHTS_DESERT

extern float vertices[]; // extern vertex data
extern size_t verticesSize;
const unsigned int SCR_WIDTH = 800; // settings
const unsigned int SCR_HEIGHT = 600;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f); // lighting

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.cursorMode = glfw::CursorMode::CursorDisabled; // tell GLFW to capture our mouse
    window.makeContextCurrent();
    gl::enableDepthTest(); // configure global opengl state

    Shader lightingShader(IDT_VERT_SHADER, IDT_FRAG_SHADER); // build and compile our shader programs
    Shader lightCubeShader(IDT_VERT_LIGHT_CUBE, IDT_FRAG_LIGHT_CUBE); // we load resources to keep the application portable

    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    gl::VertexArray cubeVAO, lightCubeVAO;
    gl::ArrayBuffer VBO;
    cubeVAO.bindVertexArray(); // first, configure the cube's VAO (and VBO)
    VBO.bufferData(verticesSize, vertices, gl::BufferUsage::StaticDraw);

    gl::VertexAttrib aPos(0), aNormal(1), aTexCoord(2);
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // position attribute
    aNormal.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
    aNormal.enableVertexAttribArray(); // normal attribute
    aTexCoord.vertexAttribPointer(gl::VertexAttribSize::Double, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));
    aTexCoord.enableVertexAttribArray(); // normal attribute

    lightCubeVAO.bindVertexArray(); // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    VBO.bindBuffer(); // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // note that we update the lamp's position attribute's stride to reflect the updated buffer data

    // load textures (we now use a utility function to keep the code more organized)
    gl::Texture2D diffuseMap, specularMap;
    load_texture(diffuseMap, IDI_CONTAINER2);
    load_texture(specularMap, IDI_CONTAINER2_S);

    // shader configuration
    lightingShader.useProgram();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    while (!window.windowShouldClose) // render loop
    {
        window.processInput();

#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        gl::clearColor(0.75f, 0.52f, 0.3f, 1.0f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        gl::clearColor(0.1f, 0.1f, 0.1f, 1.0f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        gl::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        gl::clearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit);


#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        glm::vec3 pointLightColors[] = {
            glm::vec3(1.0f, 0.6f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),
            glm::vec3(0.2f, 0.2f, 1.0f)
        };
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        glm::vec3 pointLightColors[] = {
            glm::vec3(0.2f, 0.2f, 0.6f),
            glm::vec3(0.3f, 0.3f, 0.7f),
            glm::vec3(0.0f, 0.0f, 0.3f),
            glm::vec3(0.4f, 0.4f, 0.4f)
        };
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        glm::vec3 pointLightColors[] = {
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.3f, 0.1f, 0.1f)
        };
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        glm::vec3 pointLightColors[] = {
            glm::vec3(0.4f, 0.7f, 0.1f),
            glm::vec3(0.4f, 0.7f, 0.1f),
            glm::vec3(0.4f, 0.7f, 0.1f),
            glm::vec3(0.4f, 0.7f, 0.1f)
        };
#endif

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.useProgram();
        lightingShader.setVec3("viewPos", window.camera.getPosition());
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.direction", 0.3f, 0.24f, 0.14f);
        lightingShader.setVec3("dirLight.direction", 0.7f, 0.42f, 0.26f);
        lightingShader.setVec3("dirLight.direction", 0.5f, 0.5f, 0.5f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.direction", 0.05f, 0.05f, 0.1f);
        lightingShader.setVec3("dirLight.direction", 0.2f, 0.2f, 0.7f);
        lightingShader.setVec3("dirLight.direction", 0.7f, 0.7f, 0.7f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.direction", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("dirLight.direction", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("dirLight.direction", 0.2f, 0.2f, 0.2f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.direction", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("dirLight.direction", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("dirLight.direction", 1.0f, 1.0f, 1.0f);
#endif

        // point light 1
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
        lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09f);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
        lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09f);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
        lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.14f);
        lightingShader.setFloat("pointLights[0].quadratic", 0.07f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
        lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.07f);
        lightingShader.setFloat("pointLights[0].quadratic", 0.017f);
#endif

        // point light 2
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
        lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.09f);
        lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
        lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.09f);
        lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
        lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.14f);
        lightingShader.setFloat("pointLights[1].quadratic", 0.07f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
        lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.07f);
        lightingShader.setFloat("pointLights[1].quadratic", 0.017f);
#endif

        // point light 3
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
        lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.09f);
        lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
        lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.09f);
        lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
        lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.22f);
        lightingShader.setFloat("pointLights[2].quadratic", 0.20f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
        lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.07f);
        lightingShader.setFloat("pointLights[2].quadratic", 0.017f);
#endif

        // point light 4
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
        lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.09f);
        lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
        lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.09f);
        lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
        lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.14f);
        lightingShader.setFloat("pointLights[3].quadratic", 0.07f);
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
        lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.07f);
        lightingShader.setFloat("pointLights[3].quadratic", 0.017f);
#endif

        // spotLight
#if MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_DESERT
        lightingShader.setVec3("spotLight.position", window.camera.getPosition().x, window.camera.getPosition().y, window.camera.getPosition().z);
        lightingShader.setVec3("spotLight.direction", window.camera.getFront().x, window.camera.getFront().y, window.camera.getFront().z);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.0f);
        lightingShader.setVec3("spotLight.specular", 0.8f, 0.8f, 0.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09f);
        lightingShader.setFloat("spotLight.quadratic", 0.032f);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(13.0f)));
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_FACTORY
        lightingShader.setVec3("spotLight.position", window.camera.getPosition().x, window.camera.getPosition().y, window.camera.getPosition().z);
        lightingShader.setVec3("spotLight.direction", window.camera.getFront().x, window.camera.getFront().y, window.camera.getFront().z);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.009f);
        lightingShader.setFloat("spotLight.quadratic", 0.0032f);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(12.5f)));
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_HORROR
        lightingShader.setVec3("spotLight.position", window.camera.getPosition().x, window.camera.getPosition().y, window.camera.getPosition().z);
        lightingShader.setVec3("spotLight.direction", window.camera.getFront().x, window.camera.getFront().y, window.camera.getFront().z);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09f);
        lightingShader.setFloat("spotLight.quadratic", 0.032f);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
#elif MULTIPLE_LIGHTS_THEME == MULTIPLE_LIGHTS_BIOCHEMICAL_LAB
        lightingShader.setVec3("spotLight.position", window.camera.getPosition().x, window.camera.getPosition().y, window.camera.getPosition().z);
        lightingShader.setVec3("spotLight.direction", window.camera.getFront().x, window.camera.getFront().y, window.camera.getFront().z);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 0.0f, 1.0f, 0.0f);
        lightingShader.setVec3("spotLight.specular", 0.0f, 1.0f, 0.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.07f);
        lightingShader.setFloat("spotLight.quadratic", 0.017f);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(7.0f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(10.0f)));
#endif

        // view/projection transformations
        glm::mat4 projection = window.camera.getProjectionMatrix(window.getAspectRatio());
        glm::mat4 view = window.camera.getViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // bind diffuse map, specular map
        diffuseMap.activeTexture(0);
        specularMap.activeTexture(1);

        // render containers
        cubeVAO.bindVertexArray();
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);
            gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);
        }

        // also draw the lamp object(s)
        lightCubeShader.useProgram();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        lightCubeVAO.bindVertexArray();
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubeShader.setMat4("model", model);
            gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);
        }

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
