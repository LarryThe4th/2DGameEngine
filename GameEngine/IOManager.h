#pragma once
#include <vector>

namespace GameEngine {

	class IOManager
	{
	public:
		static bool ReadFileToBuffer(const std::string filePath, std::vector<unsigned char>& buffer);
	};
}

