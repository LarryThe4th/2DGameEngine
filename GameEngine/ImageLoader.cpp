#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "ErrorMessage.h"

namespace GameEngine {
	GLTexture ImageLoader::loadPNG(std::string filePath) {
		// Create a GLTexture and initialize all its fields to 0.
		GLTexture texture = {};

		// This is the input data to decodePNG, which we load form a file.
		std::vector<unsigned char>in;
		// This is the output data form decodePNG, which is the pixel data for our texture.
		std::vector<unsigned char>out;
		// The width and height form the texture.
		unsigned long width, height;

		// Read in the image file contents into a buffer.
		if (IOManager::ReadFileToBuffer(filePath, in) == false) {
			FatalError("Failed to load PNG file to buffer!");
		}

		// Decode the png format into an array of pixels.
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size(), true);
		if (errorCode != 0) {
			FatalError("Decode png failed with error: " + std::to_string(errorCode));
		}

		// Generate the opengl texture object.
		glGenTextures(1, &(texture.id));

		// Bind the texture object.
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// Upload the pixels to the texture.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		// Set some texture parameters.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate the mipmaps.
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture.
		glBindTexture(GL_TEXTURE_2D, 0);

		// Don't forget to asign the width and height.
		texture.width = width;
		texture.height = height;

		// Return a copy of the texture data.
		return texture;
	}
}