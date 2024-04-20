#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL texture multi-object class derived from <_Objects>*/
class Textures : public _Objects
{
public:
	/*(1) Constructs an empty texture multi-object*/
	Textures() : _Objects() {}

	/*(2) Constucts a texture multi-object with <genTextures>*/
	Textures(GLuint num)
	{
		genTextures(num);
	}

	/*Cleans up the valid texture multi-object*/
	~Textures()
	{
		if (isObject())
		{
			deleteTextures();
		}
	}

	/*Deletes valid texture multi-object*/
	void deleteTextures()
	{
		_objects_delete(glDeleteTextures);
	}

	/*Generates one or more texture object names in an empty multi-object
	@param Specifies the number of texture object names to be generated*/
	void genTextures(GLuint num)
	{
		_objects_gen(glGenTextures, num);
	}
}; // class Textures : public _Objects
} // namespace gl
