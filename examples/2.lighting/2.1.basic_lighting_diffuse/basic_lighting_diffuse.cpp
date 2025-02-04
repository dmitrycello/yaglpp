// basic_lighting_diffuse.cpp
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

    gl::VertexArray cubeVAO, lightCubeVAO; // first, configure the cube's VAO (and VBO)
    gl::ArrayBuffer VBO;
    cubeVAO.bindVertexArray();
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);

    gl::VertexAttrib aPos(0), aNormal(1); // position attribute
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // position attribute
    aNormal.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
    aNormal.enableVertexAttribArray(); // normal attribute

    lightCubeVAO.bindVertexArray(); // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    VBO.bindBuffer(); // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // note that we update the lamp's position attribute's stride to reflect the updated buffer data

    while (!window.windowShouldClose) // render loop
    {
        window.processInput();
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit);

        lightingShader.useProgram(); // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        glm::mat4 projection = window.camera.getProjectionMatrix(window.getAspectRatio()); // view/projection transformations
        glm::mat4 view = window.camera.getViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f); // world transformation
        lightingShader.setMat4("model", model);
        cubeVAO.bindVertexArray(); // render the cube
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);

        lightCubeShader.useProgram(); // also draw the lamp object
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
