// textures.cpp
#include "config.h"
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
         // positions         // colors            // texture coords
         0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // top right
         0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, // bottom right
        -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, // bottom left
        -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    gl::ElementArrayBuffer EBO;
    //gl::VertexAttrib aPos(0), aColor(1), aTexCoord(2); // or use direct attribute location assignment
    gl::VertexAttrib aPos(ourShader, "aPos"), aColor(ourShader, "aColor"), aTexCoord(ourShader, "aTexCoord");
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    EBO.bufferData(sizeof(indices), indices, gl::BufferUsage::StaticDraw);

    aPos.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 0);
    aPos.enableVertexAttribArray(); // position attribute
    aColor.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
    aColor.enableVertexAttribArray(); // color attribute
    aTexCoord.vertexAttribPointer(gl::VertexAttribSize::Double, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));
    aTexCoord.enableVertexAttribArray(); // texture coord attribute

    gl::Texture2D texture; // load and create a texture, all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    texture.textureWrapS = gl::TextureWrapMode::Repeat; // set the texture wrapping parameters using properties
    texture.textureWrapT = gl::TextureWrapMode::Repeat; // set texture wrapping to GL_REPEAT (default wrapping method)
    texture.textureMinFilter = gl::TextureMinFilter::LinearMipmapLinear; // set texture filtering parameters
    texture.textureMagFilter = gl::TextureMagFilter::Linear; // or: texture.setTextureMagFilter(gl::TextureMagFilter::Linear);
    StbImage image(IDI_CONTAINER); // load image, create texture and generate mipmaps
    texture.texImage(image, 0); // take the format and type from StbImage object
    texture.generateMipmap();

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit);

        //texture.bindTexture(); // not necessary since it is bound
        ourShader.useProgram(); // render container
        VAO.bindVertexArray();
        gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);

        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
