// hello_triangle_indexed.cpp
#include "stdafx.h"
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
         0.5f,  0.5f,  0.0f,  // top right
         0.5f, -0.5f,  0.0f,  // bottom right
        -0.5f, -0.5f,  0.0f,  // bottom left
        -0.5f,  0.5f,  0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    gl::ElementArrayBuffer EBO;
    gl::VertexAttrib aPos(0);
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    EBO.bufferData(sizeof(indices), indices, gl::BufferUsage::StaticDraw);
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 3 * sizeof(float), 0);
    aPos.enableVertexAttribArray();

    VBO.unbindBuffer(); // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //EBO.unbindBuffer(); // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound
    VAO.unbindVertexArray(); // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary
    //gl::polygonMode(gl::PolygonMode::Line); // uncomment this call to draw in wireframe polygons

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        shaderProgram.useProgram(); // draw our first triangle
        VAO.bindVertexArray(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);
        gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);
        //VAO.unbindVertexArray(); // no need to unbind it every time
        
        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
