// coordinate_systems_depth.cpp
#include "stdafx.h"
#include "window.h"
#include "shader.h"
#include "resource.h"
#include "vertices.h"
const unsigned int SCR_WIDTH = 800; // settings
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.makeContextCurrent();
    Shader ourShader(IDT_VERT_SHADER, IDT_FRAG_SHADER); // we load resources to keep the application portable
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);

    gl::VertexAttrib aPos(0), aTexCoord(1); // or use direct attribute location assignment
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 5 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // position attribute
    aTexCoord.vertexAttribPointer(gl::VertexAttribSize::Double, gl::VertexAttribType::Float, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));
    aTexCoord.enableVertexAttribArray(); // texture coord attribute

    gl::Texture2D texture1, texture2; // create textures
    StbImage::setFlipVerticallyOnLoad(true); // tell stb_image library to flip loaded texture's on the y-axis
    StbImage image1(IDI_CONTAINER), image2(IDI_AWESOMEFACE); // load images
    texture1.textureWrapS = gl::TextureWrapMode::Repeat; // set texture wrapping parameters
    texture1.textureWrapT = gl::TextureWrapMode::Repeat;
    texture1.textureMinFilter = gl::TextureMinFilter::Linear; // set texture filtering parameters
    texture1.textureMagFilter = gl::TextureMagFilter::Linear;
    texture1.texImage(image1, 0); // take the format and type from StbImage object
    texture1.generateMipmap();

    texture2.textureWrapS = gl::TextureWrapMode::Repeat; // set texture wrapping parameters
    texture2.textureWrapT = gl::TextureWrapMode::Repeat;
    texture2.textureMinFilter = gl::TextureMinFilter::Linear; // set texture filtering parameters
    texture2.textureMagFilter = gl::TextureMagFilter::Linear;
    texture2.texImage(image2, 0); // take the format and type from StbImage object
    texture2.generateMipmap();

    ourShader.useProgram(); // activate shader
    gl::Uniform uModel(ourShader, "model"), uView(ourShader, "view"); // retrieve the matrix uniform locations
    ourShader.setInt("texture1", 0); // set 0 to sampler2D uniform
    ourShader.getUniformLocation("texture2").uniformTextureUnit(1); // set 1 to sampler2D using uniformTextureUnit
    //gl::enableDepthTest(); // uncomment this line and use 2nd clear line to enable depth testing

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit); // use next line instead to apply depth testing
        //gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit); // also clear the depth buffer now!

        texture1.activeTexture(0); // bind textures on corresponding texture units
        texture2.activeTexture(1);
        ourShader.useProgram(); // use shader

        glm::mat4 model = glm::mat4(1.0f); // create transformations: make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfw::getTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);

        uModel.uniformMatrix4(1, GL_FALSE, glm::value_ptr(model));
        uView.uniformMatrix4(1, GL_FALSE, &view[0][0]);
        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once

        VAO.bindVertexArray(); // render container
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
