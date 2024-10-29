// hello_triangle_exercise2.cpp
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

    float firstTriangle[] = { // set up vertex data (and buffer(s)) and configure vertex attributes
        -0.9f, -0.5f,  0.0f,  // left
        -0.0f, -0.5f,  0.0f,  // right
        -0.45f, 0.5f,  0.0f,  // top
    };
    float secondTriangle[] = {
        0.0f, -0.5f,  0.0f,  // left
        0.9f, -0.5f,  0.0f,  // right
        0.45f, 0.5f,  0.0f   // top
    };
    gl::VertexArrays VAOs(2); // we can also generate multiple VAOs or buffers at the same time
    gl::Buffers VBOs(2);
    gl::VertexArray &VAO_0 = VAOs.getVertexArray(0), &VAO_1 = VAOs.getVertexArray(1); // reference VAO objects
    gl::ArrayBuffer &VBO_0 = VBOs.getArrayBuffer(0), &VBO_1 = VBOs.getArrayBuffer(1); // reference VBO objects
    gl::VertexAttrib aPos(0);
    VAO_0.bindVertexArray(); // first triangle setup
    VBO_0.bufferData(sizeof(firstTriangle), firstTriangle, gl::BufferUsage::StaticDraw);
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 3 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // Vertex attributes stay the same
    //VAO_0.unbindVertexArray(); // no need to unbind at all as we directly bind a different VAO the next few lines

    VAO_1.bindVertexArray(); // second triangle setup, note that we bind to a different VAO now
    VBO_1.bufferData(sizeof(secondTriangle), secondTriangle, gl::BufferUsage::StaticDraw); // and a different VBO
    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 3 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    //VAO_1.unbindVertexArray(); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
    //gl::polygonMode(gl::PolygonMode::Line); // uncomment this call to draw in wireframe polygons

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.3f, 0.2f, 0.3f, 1.0f); // same look as last project, let's change color to purple
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        shaderProgram.useProgram(); // draw our first triangle
        VAO_0.bindVertexArray(); // draw first triangle using the data from the first VAO
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);
        VAO_1.bindVertexArray(); // then we draw the second triangle using the data from the second VAO
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
