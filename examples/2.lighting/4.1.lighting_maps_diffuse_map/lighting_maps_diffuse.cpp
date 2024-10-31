// lighting_maps_diffuse.cpp
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

    gl::Texture2D diffuseMap;
    load_texture(diffuseMap, IDI_CONTAINER2);
    lightingShader.useProgram();
    lightingShader.setInt("material.diffuse", 0);

    while (!window.windowShouldClose) // render loop
    {
        window.processInput();
        gl::clearColor(0.1f, 0.1f, 0.1f, 1.0f);
        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit);

        // light cube position changes
        lightPos.x = 1.0f + (float)sin(glfw::getTime()) * 2.0f;
        lightPos.y = (float)sin(glfw::getTime() / 2.0f) * 1.0f;

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.useProgram();
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", window.camera.getPosition());

        // light properties
        lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f); // note that all light colors are set at full intensity
        lightingShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.setFloat("material.shininess", 64.0f);

        // view/projection transformations
        glm::mat4 projection = window.camera.getProjectionMatrix(window.getAspectRatio());
        glm::mat4 view = window.camera.getViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // bind diffuse map and render the cube
        diffuseMap.activeTexture(0);
        cubeVAO.bindVertexArray();
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);

        // also draw the lamp object
        lightCubeShader.useProgram();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);
        lightCubeVAO.bindVertexArray();
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
