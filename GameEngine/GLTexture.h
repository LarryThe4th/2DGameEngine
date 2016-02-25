#pragma once
#include <GL\glew.h>
namespace GameEngine {

	// The data sturct of a texture.
	struct GLTexture
	{
		// The id of the texture.
		GLuint id;
		// Size of the texture.
		int width;
		int height;
	};
}
