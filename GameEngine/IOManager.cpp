#include "IOManager.h"
#include <fstream>

namespace GameEngine {

	bool IOManager::ReadFileToBuffer(const std::string filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			// Failed to read the file.
			return false;
		}

		// Seek into the end of the file.
		file.seekg(0, std::ios::end);

		// Get the file size.
		// More about std::istream::tellg() can be find in the link below.
		// http://www.cplusplus.com/reference/istream/istream/tellg/
		std::streamoff fileSize = file.tellg();

		// After getting the file size, reset the file "pointer" back to the beginning of the file.
		// So that we can read the file form the beginning but not the endding.
		file.seekg(0, std::ios::beg);

		// Becuse at the very beginning of the file there will be some file header.
		// File header stores some information such as when this file been created etc.
		// So we can delete that part becuse we don't need it.
		// Reduce the file size any header bytes that might be present.( Tho its optional )
		fileSize -= file.tellg();

		// Resizes the container so that it contains without file header.
		buffer.resize(fileSize);

		// Read into the file.
		file.read((char *)&(buffer[0]), fileSize);

		// After reading the file, close the file and release resources that it's using.
		file.close();

		// Successfully read the file.
		return true;
	}
}