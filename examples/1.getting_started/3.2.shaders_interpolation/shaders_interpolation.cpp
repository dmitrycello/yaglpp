// shaders_interpolation.cpp
#include "config.h"
#include "window.h"
#include "resource.h"

const unsigned int SCR_WIDTH = 800; // settings
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.makeContextCurrent();

    gl::VertexShader vertexShader(IDT_VERT_SHADER); // build and compile our shader program
    vertexShader.compileShader();
    gl::FragmentShader fragmentShader(IDT_FRAG_SHADER);
    fragmentShader.compileShader();
    gl::Program shaderProgram(vertexShader, fragmentShader);
    shaderProgram.linkProgram();

    float vertices[] = { // set up vertex data (and buffer(s)) and configure vertex attributes
         // positions         // colors
         0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // bottom right
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, // bottom left
         0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f  // top 
    };
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    gl::VertexAttrib aPos(0), aColor(1);
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // position attribute
    aColor.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
    aColor.enableVertexAttribArray(); // color attribute
    //VAO.unbindVertexArray(); // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary
    shaderProgram.useProgram(); // as we only have a single shader, we could also just activate our shader once beforehand if we want to

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        VAO.bindVertexArray(); // render the triangle
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
