#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace GameEngine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::GetTexture(std::string texturePath) {
		// The auto is the same thing as "std::map<std::string, GLTexture>::iterator"
		// Just like var in java if im not thinking it wrong.
		auto iterator = _textureMap.find(texturePath);

		// Check if its not in the map.
		if (iterator == _textureMap.end()) {
			// Then load the texture and use it to create a new texture.
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			// Insert it into the map just like how you use a dictionary in C#.
			_textureMap.insert(std::make_pair(texturePath, newTexture));

			std::cout << "Loaded texture!" << std::endl;
			return newTexture;
		}
		std::cout << "Loaded cached texture!" << std::endl;
		return iterator->second;
	}
}