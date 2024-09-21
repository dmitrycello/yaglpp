// coordinate_systems_exercise3.cpp
#include "config.h"
#include "window.h"
#include "shader.h"
#include "resource.h"

extern float vertices[]; // cube data defined in cube.cpp
extern size_t verticesSize;
const unsigned int SCR_WIDTH = 800; // settings
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL"); // glfw window creation
    window.makeContextCurrent();
    gl::enableDepthTest(); // configure global opengl state
    Shader ourShader(IDT_VERT_SHADER, IDT_FRAG_SHADER); // we load resources to keep the application portable
    glm::vec3 cubePositions[] = { // world space positions of our cubes
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    gl::VertexArray VAO;
    gl::ArrayBuffer VBO;
    VAO.bindVertexArray(); // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
    VBO.bufferData(verticesSize, vertices, gl::BufferUsage::StaticDraw);

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
    ourShader.setInt("texture1", 0); // set 0 to sampler2D uniform
    ourShader.getUniformLocation("texture2").uniformTextureUnit(1); // set 1 to sampler2D using uniformTextureUnit
    gl::Uniform uModel(ourShader, "model"), uView(ourShader, "view"); // retrieve the matrix uniform locations

    while (!window.windowShouldClose) // render loop
    {
        gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f); // render
        gl::clear(gl::BufferBitMask::ColorBufferBit | gl::BufferBitMask::DepthBufferBit); // also clear the depth buffer now!

        texture1.activeTexture(0); // bind textures on corresponding texture units
        texture2.activeTexture(1);
        ourShader.useProgram(); // use shader

        glm::mat4 view = glm::mat4(1.0f); // create transformations: make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

        VAO.bindVertexArray(); // render boxes
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f); // calculate the model matrix for each object and pass it to shader before drawing
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = (float)glfw::getTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 36);
        }
        window.swapBuffers(); // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfw::pollEvents();
    }
    return 0;
}
