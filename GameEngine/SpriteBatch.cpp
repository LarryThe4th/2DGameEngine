#include "SpriteBatch.h"
#include <algorithm>

namespace GameEngine {

	SpriteBatch::SpriteBatch() :
		_vertexBufferObjectID(0),
		_vertexArrayObjectID(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::InitSpriteBatch() {
		CreateVertexArray();
	}

	void SpriteBatch::CreateVertexArray() {
		// In case of preventing memory leak, cheak if the buffer ID is already in use.
		// If the buffer ID is empty(0) then generate a new buffer ID.
		if (_vertexArrayObjectID == 0) {
			glGenVertexArrays(1, &_vertexArrayObjectID);
		}
		// Bind the vertex array object. 
		// All subsequent opengl calls will modify it's state.
		glBindVertexArray(_vertexArrayObjectID);

		// Generate the vertex buffer object if it isn't already generated.
		if (_vertexBufferObjectID == 0) {
			glGenBuffers(1, &_vertexBufferObjectID);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectID);

		// Tell opengl that we want to uew the first attribute array.
		// Since we have three attribute: position, color and UV, we need enbale three attribute in the array.
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// This is the position attribute pointer.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// This is the color attribute pointer.
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// This is the UV attribute pointer.
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// Unbind the vertex array.
		// This will disable all the arrtibute array and unbind the vertex buffer object.
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches() {
		// Store all the vertices that we need to upload later.
		std::vector<Vertex> vertices;
		// The number of vertices for render a quad.
		const size_t numVertices = 6;
		// The total number of vertices will be the number of sprites times 6. 
		vertices.resize(_sprites.size() * numVertices);

		// If there has no sprite then we don't need to do anything.
		if (_sprites.empty()) { return; }

		// Keep tracking the index of the vertices.
		unsigned int vertexIndex = 0;

		for (size_t currentSpriteIndex = 0; currentSpriteIndex < _sprites.size(); currentSpriteIndex++) {
			if (currentSpriteIndex == 0) {
				// Since this is the frist batch, offset will be 0, have 6 verties and the first texture ID in the list.
				_renderBatches.emplace_back(0, numVertices, _sprites[currentSpriteIndex]->textureID);
			}
			else {
				// Ckeck if the current sprite is not the same one as the previous one.
				if (_sprites[currentSpriteIndex]->textureID != _sprites[currentSpriteIndex - 1]->textureID) {
					// Then the vertex offset of this sprite will be the sprite index times number of vertices for a quad.
					_renderBatches.emplace_back(currentSpriteIndex * numVertices, numVertices, _sprites[currentSpriteIndex]->textureID);
				}
				else {
					// If the current sprite is the same one as the previous one, then just add more vertices in it.
					// The offset of the sprite and the texture ID no need to change.
					_renderBatches.back().numberOfVertices += numVertices;
				}
			} 

			// Notice that in order to render a triangle, those 3 vertices has to be count in anti-clockwise order.
			// So basiclly the order to render a quad is:
			// topLeft -> bottomLeft -> bottomRight (First triangle)
			// bottomRight -> topRight -> topLeft	(Second triangle)
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->topLeft;
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->bottomLeft;
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->bottomRight;
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->bottomRight;
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->topRight;
			vertices[vertexIndex++] = _sprites[currentSpriteIndex]->topLeft;
		}

		// Bind the vertex buffer object.
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectID);
		// Orphan the buffer, delete the old buffer that we don't need anymore.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data.
		// Lream more about glBufferSubData see the link below:
		// https://www.opengl.org/sdk/docs/man2/xhtml/glBufferSubData.xml
		// vertices.data() is the same as &vertices[0].
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Always remenber to unbind the buffer.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::Begin(SortType sortType) {
		_sortType = sortType;
		_renderBatches.clear();
		// Delete all the sprites to prevent form memory leaks.
		for (size_t i = 0; i < _sprites.size(); i++) {
			delete _sprites[i];
		}
		// Don't forget that only delete the memory is not enough!
		_sprites.clear();
	}

	void SpriteBatch::AddSprite(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, GLuint textureID, float depth, const Color& color) {
		SingleSprite* newSprite = new SingleSprite;
		// The same thing we did when creating a sprite.
		newSprite->topLeft.color = color;
		newSprite->topLeft.SetPosition(destinationRectangle.x, destinationRectangle.y + destinationRectangle.w);
		newSprite->topLeft.SetUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

		newSprite->bottomLeft.color = color;
		newSprite->bottomLeft.SetPosition(destinationRectangle.x, destinationRectangle.y);
		newSprite->bottomLeft.SetUV(uvRectangle.x, uvRectangle.y);

		newSprite->bottomRight.color = color;
		newSprite->bottomRight.SetPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y);
		newSprite->bottomRight.SetUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

		newSprite->topRight.color = color;
		newSprite->topRight.SetPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y + destinationRectangle.w);
		newSprite->topRight.SetUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);

		newSprite->textureID = textureID;
		newSprite->depth = depth;

		_sprites.push_back(newSprite);
	}

	void SpriteBatch::End() {
		SortSprites();
		CreateRenderBatches();
	}

	void SpriteBatch::SortSprites() {
		switch (_sortType)
		{
			case DEPTH_FRONT_TO_BACK:
				// Stable sort in sure that if two elements are equal then maintain the order in the list. 
				std::stable_sort(_sprites.begin(), _sprites.end(), CompareDepthFrontToBack);
				break;
			case DEPTH_BACK_TO_FRONT:
				std::stable_sort(_sprites.begin(), _sprites.end(), CompareDepthBackToFront);
				break;
			case TEXTURE_ID:
				std::stable_sort(_sprites.begin(), _sprites.end(), CompareTextureID);
				break;
			default:
				break;
		}
	}

	bool SpriteBatch::CompareDepthFrontToBack(SingleSprite* spriteA, SingleSprite* spriteB) {
		return (spriteA->depth < spriteB->depth);
	}

	bool SpriteBatch::CompareDepthBackToFront(SingleSprite* spriteA, SingleSprite* spriteB) {
		return (spriteA->depth > spriteB->depth);
	}

	bool SpriteBatch::CompareTextureID(SingleSprite* spriteA, SingleSprite* spriteB) {
		return (spriteA->textureID < spriteB->textureID);
	}

	void SpriteBatch::RenderBatches() {

		// Bind the vertex array object. 
		// This sets up the opengl state we need, including vertex attribute pointers and it binds the vertex buffer object.
		glBindVertexArray(_vertexArrayObjectID);

		for (size_t i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].textureID);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numberOfVertices);
		}

		// Unbind the vertex array object.
		glBindVertexArray(0);
	}
}