#pragma once
#include <GL\glew.h>
#include <string>

#include "GLTexture.h"

namespace GameEngine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void InitSprite(float xPosition, float yPostion, float widht, float height, std::string textureFilePath);
		void DrawSprite();

	private:
		// The position of the sprite.
		float _xPosition;
		float _yposition;

		// The size of the sprite.
		float _width;
		float _height;

		// Vertex buffer object (VBO) creates "buffer objects" for vertex attributes 
		// in high-performance memory on the server side and provides same access functions 
		// to reference the arrays.
		// Learn more about Vertex buffer object (VBO): 
		// https://www.opengl.org/wiki/Vertex_Specification
		GLuint _vertexBufferObjectID;

		// The texture of the sprite.
		GLTexture _texture;
	};
}