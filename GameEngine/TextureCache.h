#pragma once
#include <map>
#include "GLTexture.h"

namespace GameEngine {
	// This caches the textures so that multiple sprites can use the same textures.
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		// Get texture data by file path.
		GLTexture GetTexture(std::string texturePath);

	private:
		// The data struct of the textures.
		std::map<std::string, GLTexture> _textureMap;
	};
}
