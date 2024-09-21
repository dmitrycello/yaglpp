// hello_triangle_exercise3.cpp
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
    gl::FragmentShader fragmentShaderOrange(IDT_FRAG_SHADER); // the first fragment shader that outputs the color orange
    fragmentShaderOrange.compileShader();
    gl::FragmentShader fragmentShaderYellow(IDT_FRAG_SHADER_2); // the second fragment shader that outputs the color yellow
    fragmentShaderYellow.compileShader();
    gl::Program shaderProgramOrange(vertexShader, fragmentShaderOrange); // the first shader program
    shaderProgramOrange.linkProgram();
    gl::Program shaderProgramYellow(vertexShader, fragmentShaderYellow); // the second shader program
    shaderProgramYellow.linkProgram();

    float secondTriangle[] = { // set up vertex data (and buffer(s)) and configure vertex attributes
        0.0f, -0.5f,  0.0f,  // left
        0.9f, -0.5f,  0.0f,  // right
        0.45f, 0.5f,  0.0f   // top 
    };
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    gl::VertexArrays VAOs(2); // we can also generate multiple VAOs or buffers at the same time
    gl::Buffers VBOs(2);
    gl::VertexArray VAO_0(VAOs, 0), VAO_1(VAOs, 1); // reference VAO objects
    gl::ArrayBuffer VBO_0(VBOs, 0), VBO_1(VBOs, 1); // reference VBO objects
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
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        shaderProgramOrange.useProgram(); // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
        VAO_0.bindVertexArray();
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3); // this call should output an orange triangle

        shaderProgramYellow.useProgram(); // when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader
        VAO_1.bindVertexArray(); // then we draw the second triangle using the data from the second VAO
        gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3); // this call should output a yellow triangle

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
