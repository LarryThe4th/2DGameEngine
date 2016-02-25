#pragma once
#include <string>
#include "TextureCache.h"
#include "GLTexture.h"

namespace GameEngine {

	// This is a way for us to access all out resources.
	// Such as models or textures.
	class ResourceManager
	{
	public:
		static GLTexture GetTexture(std::string texturePath);

	private:
		static TextureCache _TextureCache;

	};

}


