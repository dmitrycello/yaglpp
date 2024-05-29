// Poject 6: Triangle exercise 3
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
	gl::FragmentShader fragShader2(IDT_FRAG_SHADER2);
	fragShader2.compileShader();
	gl::Program program(vertShader, fragShader);
	program.linkProgram();
	gl::Program program2(vertShader, fragShader2);
	program2.linkProgram();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, // top left
		 0.0f, -0.5f, 0.0f  // bottom
	};
	float vertices2[] = {
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.0f,  0.5f, 0.0f  // top
	};

	gl::VertexAttrib VA0(0);
	gl::VertexArray VAO;
	VAO.bindVertexArray();
	gl::ArrayBuffer VBO;
	VBO.bufferData(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
	VA0.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 3 * sizeof(float), 0);
	VA0.enableVertexAttribArray();

	gl::VertexArray VAO2;
	VAO2.bindVertexArray();
	gl::ArrayBuffer VBO2;
	VBO2.bufferData(sizeof(vertices2), vertices2, gl::BufferUsage::StaticDraw);
	VA0.vertexAttribPointer(gl::VertexAttribSize::Triple, gl::VertexAttribType::Float, GL_FALSE, 3 * sizeof(float), 0);
	VA0.enableVertexAttribArray();

	while (!window.windowShouldClose())
	{
		gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clear(gl::BufferBitMask::ColorBufferBit);

		program.useProgram();
		VAO.bindVertexArray();
		gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);
		program2.useProgram();
		VAO2.bindVertexArray();
		gl::drawArrays(gl::PrimitiveMode::Triangles, 0, 3);

		window.swapBuffers();
		glfw::pollEvents();
	}
	return 0;
}
