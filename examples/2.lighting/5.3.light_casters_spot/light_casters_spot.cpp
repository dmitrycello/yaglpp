// light_casters_spot.cpp
#include "stdafx.h"
#include "camera.h"
#include "window.h"
#include "shader.h"
#include "resource.h"
#include "vertices.h"
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
    gl::VertexArray cubeVAO, lightCubeVAO;
    gl::ArrayBuffer VBO;
    cubeVAO.bindVertexArray(); // first, configure the cube's VAO (and VBO)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);

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
        gl::clearColor(0.1f, 0.1f, 0.1f, 1.0f);
        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit);

        // light cube position changes, may be commented to fix it
        lightPos.x = 1.0f + (float)sin(glfw::getTime()) * 2.0f;
        lightPos.y = (float)sin(glfw::getTime() / 2.0f) * 1.0f;

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.useProgram();
        lightingShader.setVec3("light.position", window.camera.getPosition());
        lightingShader.setVec3("light.direction", window.camera.getFront());
        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setVec3("viewPos", window.camera.getPosition());

        // light properties
        lightingShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
        // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
        // each environment and lighting type requires some tweaking to get the best out of your environment.
        lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("light.constant", 1.0f);
        lightingShader.setFloat("light.linear", 0.09f);
        lightingShader.setFloat("light.quadratic", 0.032f);

        // material properties
        lightingShader.setFloat("material.shininess", 32.0f);

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

        // again, a lamp object is weird when we only have a spot light, don't render the light object
        //lightCubeShader.useProgram();
        //lightCubeShader.setMat4("projection", projection);
        //lightCubeShader.setMat4("view", view);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        //lightCubeShader.setMat4("model", model);
        //lightCubeVAO.bindVertexArray();
        //gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
