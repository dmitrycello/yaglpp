// transformations_exercise2.cpp
#include "stdafx.h"
#include "window.h"
#include "shader.h"
#include "resource.h"
const unsigned int SCR_WIDTH = 800; // settings
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.makeContextCurrent();
    Shader ourShader(IDT_VERT_SHADER, IDT_FRAG_SHADER); // we load resources to keep the application portable
    float vertices[] = { // set up vertex data (and buffer(s)) and configure vertex attributes
         // positions          // texture coords
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    gl::ElementArrayBuffer EBO;
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    EBO.bufferData(sizeof(indices), indices, gl::BufferUsage::StaticDraw);

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
    gl::Uniform uTransform(ourShader, "transform");
    ourShader.setInt("texture1", 0); // set 0 to sampler2D uniform
    ourShader.getUniformLocation("texture2").uniformTextureUnit(1); // same thing using uniformTextureUnit

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        texture1.activeTexture(0); // bind textures on corresponding texture units
        texture2.activeTexture(1);

        glm::mat4 transform = glm::mat4(1.0f); // first container: make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // first container
        transform = glm::rotate(transform, (float)glfw::getTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        uTransform.uniformMatrix4(1, GL_FALSE, glm::value_ptr(transform));

        VAO.bindVertexArray();
        gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);

        transform = glm::mat4(1.0f); // second transformation: reset it to identity matrix
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin((float)glfw::getTime());
        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        uTransform.uniformMatrix4(1, GL_FALSE, &transform[0][0]); // this time take the matrix value array's first element as its memory pointer value
        gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
