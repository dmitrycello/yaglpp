#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_SHADERS_T_H
#define YAGLPP_SHADERS_T_H

namespace gl {
template <GLenum T> class Shaders_1 : public Shaders
{
public:
	using Shaders::Shaders;
	/*(1) Constructs default fragment shader object*/
	Shaders_1() : Shaders() {}

	/*(2) Constructs shader object with <SourceFromFile>*/
	Shaders_1(_In_z_ const char* filepath) : Shaders()
	{
		Shaders::source_from_file(T, filepath);
	}

	/*(3) Constructs shader object with <SourceFromMemory>*/
	Shaders_1(_In_ unsigned char* data, unsigned int size) : Shaders()
	{
		Shaders::source_from_memory(T, data, size);
	}

	/*(4) Constructs shader object with <Source>*/
	Shaders_1(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length) : Shaders()
	{
		Shaders::source(T, count, string, length);
	}

	/*Creates OpenGL fragment shader object name in an empty class object*/
	void Create()
	{
		Objects::object_shader(T);
	}

#ifdef YAGLPP_MSVC
	/*(5) Constructs shader object with <SourceFromResource> (Windows only)*/
	Shaders_1(int rcid) : Shaders()
	{
		Shaders::source_from_resource(T, rcid);
	}
#endif // #ifdef YAGLPP_MSVC
};

typedef Shaders_1<GL_FRAGMENT_SHADER> FragmentShader_1;
/*OpenGL fragment shader object class derived from <Shaders>*/
class FragmentShader : public FragmentShader_1
{
public:
	using Shaders_1::Shaders_1;
};

typedef Shaders_1<GL_VERTEX_SHADER> VertexShader_1;
/*OpenGL vertex shader object class derived from <Shaders>*/
class VertexShader : public VertexShader_1
{
public:
	using Shaders_1::Shaders_1;
};

#ifdef YAGLPP_VERSION_3_2
typedef Shaders_1<GL_GEOMETRY_SHADER> GeometryShader_1;
/*(3.2) OpenGL geometry shader object class derived from <Shaders>*/
class GeometryShader : public GeometryShader_1
{
public:
	using Shaders_1::Shaders_1;
};
#endif // #ifdef YAGLPP_VERSION_3_2
} // namespace gl
#endif //#ifndef YAGLPP_SHADERS_T_H
