#include "ResourceManager.h"
#include "TextureCache.h"

namespace GameEngine {
	TextureCache ResourceManager::_TextureCache;

	GLTexture ResourceManager::GetTexture(std::string texturePath) {
		return _TextureCache.GetTexture(texturePath);
	}
}
