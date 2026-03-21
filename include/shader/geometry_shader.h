#ifndef YAGLPP_GLPP_H
#error YAGL++: The only <glpp.h> main file must be included
#endif

#ifndef YAGLPP_GEOMETRY_SHADER_H
#define YAGLPP_GEOMETRY_SHADER_H

#ifdef YAGLPP_VERSION_3_2
namespace gl {
/*(3.2) OpenGL geometry shader object class derived from <Shaders>*/
class GeometryShader : public Shaders
{
public:
	/*(3.2) (1) Constructs default geometry shader object*/
	GeometryShader() : Shaders() {}

	/*(3.2) (2) Constructs shader object with <SourceFromFile>*/
	GeometryShader(_In_z_ const char* filepath) : Shaders()
	{
		source_from_file(gl_create_geometry_shader, filepath);
	}

	/*(3.2) (3) Constructs shader object with <SourceFromMemory>*/
	GeometryShader(_In_ unsigned char* data, unsigned int size) : Shaders()
	{
		source_from_memory(gl_create_geometry_shader, data, size);
	}

	/*(3.2) (4) Constructs shader object with <Source>*/
	GeometryShader(GLsizei count, _In_reads_(count) const GLchar** string, _In_reads_(count) const GLint* length) : Shaders()
	{
		source(gl_create_geometry_shader, count, string, length);
	}

	/*(3.2) Creates OpenGL shader object name in an empty class object*/
	void Create()
	{
		object_gen(gl_create_geometry_shader);
	}

#ifdef YAGLPP_MSVC
	/*(3.2) (5) Constructs shader object with <SourceFromResource> (Windows only)*/
	GeometryShader(int rcid) : Shaders()
	{
		source_from_resource(gl_create_geometry_shader, rcid);
	}
#endif // #ifdef YAGLPP_MSVC
}; // class GeometryShader : public Shaders
} // namespace gl
#endif // #ifdef YAGLPP_VERSION_3_2
#endif // #ifndef YAGLPP_GEOMETRY_SHADER_H
