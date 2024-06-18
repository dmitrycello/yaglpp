// Poject 18: Textures exercise 4
#include <yaglpp/yaglpp.h>
#include "resource.h"

class GLWindow : public glfw::Window
{
	float m_fMixer = 0.5f;
	using glfw::Window::Window;
	void onFramebuffer(int width, int height)
	{
		gl::viewport(0, 0, width, height);
	}
	void onKeyDown(glfw::KeyboardKey key, int scancode)
	{
		if (key == glfw::KeyboardKey::KeyUp) m_fMixer += 0.1f;
		if (key == glfw::KeyboardKey::KeyDown) m_fMixer -= 0.1f;
		if (key == glfw::KeyboardKey::KeyEscape) setWindowShouldClose(true);
	}

public:
	float getMixer() { return m_fMixer; }
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

	gl::Texture2D texture1, texture2;
	StbImage::setFlipVerticallyOnLoad(true);
	StbImage image1(IDI_CONTAINER), image2(IDI_AWESOMEFACE);

	texture1.setTextureWrapS(gl::TextureWrapMode::Repeat);
	texture1.setTextureWrapT(gl::TextureWrapMode::Repeat);
	texture1.setTextureMinFilter(gl::TextureMinFilter::Linear);
	texture1.setTextureMagFilter(gl::TextureMagFilter::Linear);
	texture1.texImage2D(image1, 0, gl::TexInternalformat::Rgb);

	texture2.setTextureWrapS(gl::TextureWrapMode::Repeat);
	texture2.setTextureWrapT(gl::TextureWrapMode::Repeat);
	texture2.setTextureMinFilter(gl::TextureMinFilter::Linear);
	texture2.setTextureMagFilter(gl::TextureMagFilter::Linear);
	texture2.texImage2D(image2, 0, gl::TexInternalformat::Rgb);

	program.useProgram();
	gl::Uniform mixer(program, "mixer");
	program.getUniformLocation("texture1").uniformTextureUnit(0);
	program.getUniformLocation("texture2").uniformTextureUnit(1);

	while (!window.windowShouldClose())
	{
		gl::clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clear(gl::BufferBitMask::ColorBufferBit);

		texture1.activeTexture(0);
		texture2.activeTexture(1);
		VAO.bindVertexArray();
		mixer.uniform(window.getMixer());
		gl::drawElements(gl::PrimitiveMode::Triangles, 6, gl::PrimitiveType::UnsignedInt, 0);

		window.swapBuffers();
		glfw::pollEvents();
	}
	return 0;
}
