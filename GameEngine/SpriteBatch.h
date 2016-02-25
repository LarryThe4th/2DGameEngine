#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

#include "Vertex.h"

namespace GameEngine {

	enum SortType {
		NONE,
		DEPTH_FRONT_TO_BACK,
		DEPTH_BACK_TO_FRONT,
		TEXTURE_ID
	};

	struct SingleSprite
	{
		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
		GLuint textureID;
		float depth;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumberOfVertices, GLuint TextureID) :
			offset(Offset),
			numberOfVertices(NumberOfVertices),
			textureID(TextureID) {}
		
		GLuint offset;
		GLuint numberOfVertices;
		GLuint textureID;
	};

	// This a Opengl version of sprite batch, which the Microsoft Xna provides almost the some function as this one.
	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void InitSpriteBatch();

		void Begin(SortType sortType = SortType::TEXTURE_ID);

		// The destination rectangle actually just a combination of position X, Y and the size of width and height.
		void AddSprite(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, GLuint textureID, float depth, const Color& color);

		void End();

		void RenderBatches();

	private:
		void CreateVertexArray();
		void CreateRenderBatches();
		void SortSprites();

		// The different sorting methods.
		static bool CompareDepthFrontToBack(SingleSprite* spriteA, SingleSprite* spriteB);
		static bool CompareDepthBackToFront(SingleSprite* spriteA, SingleSprite* spriteB);
		static bool CompareTextureID(SingleSprite* spriteA, SingleSprite* spriteB);

		GLuint _vertexBufferObjectID;
		GLuint _vertexArrayObjectID;

		SortType _sortType;

		// Always remenber to use pointer to save calculation!
		std::vector<SingleSprite*> _sprites;
		std::vector<RenderBatch> _renderBatches;
	};
}

