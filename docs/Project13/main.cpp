// Poject 13: Textures
#include <yaglpp/yaglpp.h>
#include "resource.h"

class GLWindow : public glfw::Window
{
	using glfw::Window::Window;
	void onFramebuffer(int width, int height)
	{
		gl::viewport(0, 0, width, height);
	}
	void onKeyDown(glfw::KeyboardKey key, int scancode)
	{
		if (key == glfw::KeyboardKey::KeyEscape) setWindowShouldClose(true);
	}
};

int main(int argc, char** argv)
{
	GLWindow window(800, 600, "YAGL++ Application");
	window.makeContextCurrent();

	gl::VertexShader vertShader(IDT_VERT_SHADER);
	vertShader.compileShader();
	gl::FragmentShader fragShader(IDT_FRAG_SHADER);
	fragShader.compileShader();
	gl::Program program(vertShader, fragShader);
	program.linkProgram();

	float vertices[] = {
		// positions       // colors         // texture coords
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
	   -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	gl::VertexArray VAO;
	VAO.bindVertexArray();
	gl::ArrayBuffer VBO;
	VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
	gl::ElementArrayBuffer EBO;
	EBO.bufferData(sizeof(indices), indices, gl::BufferUsage::StaticDraw);

	gl::VertexAttrib VA0(0), VA1(1), VA2(2);
	VA0.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 0);
	VA0.enableVertexAttribArray();
	VA1.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
	VA1.enableVertexAttribArray();
	VA2.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));
	VA2.enableVertexAttribArray();

	gl::Texture2D texture2D;
	texture2D.setTextureWrapS(gl::TextureWrapMode::Repeat);
	texture2D.setTextureWrapT(gl::TextureWrapMode::Repeat);
	texture2D.setTextureMinFilter(gl::TextureMinFilter::Linear);
	texture2D.setTextureMagFilter(gl::TextureMagFilter::Linear);
	StbImage image(IDI_CONTAINER);
	texture2D.texImage2D(image, 0, gl::TexInternalformat::Rgb);

	while (!window.windowShouldClose())
	{
		gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clear(gl::BufferBitMask::ColorBufferBit);

		program.useProgram();
		VAO.bindVertexArray();
		gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);

		window.swapBuffers();
		glfw::pollEvents();
	}
	return 0;
}