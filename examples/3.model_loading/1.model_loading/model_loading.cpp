// model_loading.cpp
#include "stdafx.h"
#include "helper.h"
#include "camera.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "model.h"
#include "resource.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    std::string path, dir;
    if (!open_file(path, dir,
        "Select 3D Model Object File",
        "Object Files (*.obj)\0*.obj\0All Files (*.*)\0*.*\0\0"))
    {
        return -1; // no file selected
    }
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.cursorMode = glfw::CursorMode::CursorDisabled; // tell GLFW to capture our mouse
    window.makeContextCurrent();
    gl::enableDepthTest(); // configure global opengl state
    StbImage::setFlipVerticallyOnLoad(true); // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    Shader ourShader(IDT_VERT_SHADER, IDT_FRAG_SHADER); // build and compile shaders
    Model ourModel(path, dir); // load models
    //gl::polygonMode(gl::PolygonMode::Line); // draw in wireframe

    while (!window.windowShouldClose) // render loop
    {
        window.processInput();
        gl::clearColor(0.05f, 0.05f, 0.05f, 1.0f);
        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit);
        ourShader.useProgram(); // don't forget to enable shader before setting uniforms

        // view/projection transformations
        glm::mat4 projection = window.camera.getProjectionMatrix(window.getAspectRatio());
        glm::mat4 view = window.camera.getViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
