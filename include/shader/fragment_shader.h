#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_FRAGMENT_SHADER_H
#define YAGLPP_FRAGMENT_SHADER_H

namespace gl {
// OpenGL fragment shader object class derived from <Shaders>
class FragmentShader : public Shaders
{
public:
	using Shaders::Shaders;
	/*(1) Constructs default fragment shader object*/
	FragmentShader() : Shaders() {}

	/*(2) Constructs shader object with <SourceFromFile>*/
	FragmentShader(_In_z_ const char* filepath) : Shaders()
	{
		source_from_file(gl_create_fragment_shader, filepath);
	}

	/*(3) Constructs shader object with <SourceFromMemory>*/
	FragmentShader(_In_ unsigned char* data, unsigned int size) : Shaders()
	{
		source_from_memory(gl_create_fragment_shader, data, size);
	}

	/*(4) Constructs shader object with <Source>*/
	FragmentShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length) : Shaders()
	{
		source(gl_create_fragment_shader, count, string, length);
	}

	/*Creates OpenGL fragment shader object name in an empty class object*/
	void Create()
	{
		object_gen(gl_create_fragment_shader);
	}

#ifdef YAGLPP_MSVC
	/*(5) Constructs shader object with <SourceFromResource> (Windows only)*/
	FragmentShader(int rcid) : Shaders()
	{
		source_from_resource(gl_create_fragment_shader, rcid);
	}
#endif // #ifdef YAGLPP_MSVC
}; // class FragmentShader : public Shaders
} // namespace gl
#endif // #ifndef YAGLPP_FRAGMENT_SHADER_H
