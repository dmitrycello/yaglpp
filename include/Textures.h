#pragma once
#include "gladpp.h"
namespace gl {
/*OpenGL texture multi-object class derived from <_Objects>*/
class Textures : public _Objects
{
public:
	/*(1) Constructs an empty texture multi-object*/
	Textures() {}

	/*(2) Constucts a texture multi-object with <genTextures>*/
	Textures(GLsizei n)
	{
		genTextures(n);
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

	/*Generates one or more texture object names in the empty multi-object
	@param Specifies the number of object names to be generated*/
	void genTextures(GLsizei n)
	{
		_objects_gen(glGenTextures, n);
	}

	/*Insert one or more texture object names at specified position in the valid multi-object
	@param Specifies the number of object names to be inserted
	@param Specifies the position index where to insert created object names*/
	void insertTextures(GLsizei n, GLint pos)
	{
		_objects_insert(glGenTextures, n, pos);
	}

	/*Remove one or more texture object names from specified position in the valid multi-object
	@param Specifies the number of object names to be removed
	@param Specifies the position index from where to remove object names*/
	void removeTextures(GLsizei n, GLint pos)
	{
		_objects_remove(glDeleteTextures, n, pos);
	}
}; // class Textures : public _Objects
} // namespace gl
