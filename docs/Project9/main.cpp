// Poject 9: Shaders. More attributes!
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
		 // positions       // colors
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
	};
	gl::VertexArray VAO;
	VAO.bindVertexArray();
	gl::ArrayBuffer VBO;
	VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);

	gl::VertexAttrib VA0(0), VA1(1);
	VA0.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 0);
	VA0.enableVertexAttribArray();
	VA1.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
	VA1.enableVertexAttribArray();

	while (!window.windowShouldClose())
	{
		gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clear(gl::BufferBitMask::ColorBufferBit);

		program.useProgram();
		VAO.bindVertexArray();
		gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);

		window.swapBuffers();
		glfw::pollEvents();
	}
	return 0;
}
