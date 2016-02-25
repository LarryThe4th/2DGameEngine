#pragma once
#include <string>
#include "GLTexture.h"

namespace GameEngine {

	// Load images into GLTextures.
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}

