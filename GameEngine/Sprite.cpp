#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

/*
The workflow of a Vertex buffer object (VBO) requires following steps:
	1. Create a new vertex buffer object ID, the ID that use in opengl will allways be GLuint.
	For example: GLuint _vertexBufferObjectID;

	2. Generate the buffer.
	For example: void glGenBuffers(	GLsizei n, GLuint * buffers);
	------------------------------------------------
	Noitce that there has a "glCreateBuffers" function as well.
	The difference between "glGenBuffers" and "glCreateBuffers" is that glGenBuffers only returns an unused name.
	While glCreateBuffers also creates and initializes the state vector described above.

	The reason of using "glGenBuffers" rather than "glCreateBuffers" is that Since in "glCreateBuffers" no initial binding is given.
	Learn more about generating a vertex buffer object name see the link below:
	https://www.opengl.org/sdk/docs/man/html/glGenBuffers.xhtml
	------------------------------------------------

	3. Binds a buffer object to the specified buffer binding point.
	For example: void glBindBuffer(	GLenum target, GLuint buffer);

	------------------------------------------------
	Learn more about binding a buffer object see the link below:
	https://www.opengl.org/sdk/docs/man/html/glBindBuffer.xhtml
	------------------------------------------------

	4. Update the Vertex buffer object (VBO) data to GPU.
	For example: void glBufferData(	GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);

	------------------------------------------------
	Learn more about creates and initializes a buffer object's data store, see the link below:
	https://www.opengl.org/sdk/docs/man/html/glBufferData.xhtml
	------------------------------------------------

	5. Unbind the buffer for reless the resouce.
	For example: glBindBuffer(GL_ARRAY_BUFFER, 0);

	6. Delete buffer when the object is no longer in use.
	For example: void glDeleteBuffers(GLsizei n, const GLuint * buffers);

	------------------------------------------------
	Learn more about delete buffers see the link below:
	https://www.opengl.org/sdk/docs/man/html/glBufferData.xhtml
	------------------------------------------------
*/

namespace GameEngine {

	// Consturctor.
	Sprite::Sprite() :
		// Sprite position
		_xPosition(0),
		_yposition(0),
		// Sprite size.
		_width(0),
		_height(0),
		// Always initialize your buffer IDs to zero.
		_vertexBufferObjectID(0)
	{

	}

	// Destructor.
	Sprite::~Sprite()
	{
		// Allwats remenber to delete your buffers when you are done with the sprite.
		if (_vertexBufferObjectID != 0) {
			glDeleteBuffers(1, &_vertexBufferObjectID);
		}
	}

	// Initializes the sprite vertex buffer object. 
	// The X position, Y position, width and height value are in the normalized decive coordinate space. 
	void Sprite::InitSprite(float xPosition, float yPosition, float width, float height, std::string textureFilePath) {
		// Setup our private variables.
		_xPosition = xPosition;
		_yposition = yPosition;
		_width = width;
		_height = height;

		// Load the texture form the file path.
		_texture = ResourceManager::GetTexture(textureFilePath);

		// Generate the buffer if it hasn't aleady been generated.
		if (_vertexBufferObjectID == 0) {
			glGenBuffers(1, &_vertexBufferObjectID);
		}

		// This array will hold our vertex data.
		// We need 6 vertices, and each vertex has 2 floats for X and Y.
		Vertex vertexData[6];

		// First triangle
		vertexData[0].SetPosition(_xPosition + _width, _yposition + _height);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(_xPosition, _yposition + _height);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(_xPosition, _yposition);
		vertexData[2].SetUV(0.0f, 0.0f);

		// Second triangle
		vertexData[3].SetPosition(_xPosition, _yposition);
		vertexData[3].SetUV(0.0f, 0.0f);

		vertexData[4].SetPosition(_xPosition + _width, _yposition);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5].SetPosition(_xPosition + _width, _yposition + _height);
		vertexData[5].SetUV(1.0f, 1.0f);

		// Set all the color at once.
		for (int i = 0; i < 6; i++)
		{
			vertexData[i].SetColor(255, 255, 255, 255);
		}

		// Tell opengl to bind our vertex buffer object.
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectID);

		// Upload the data to the GPU.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);

		// Unbind the buffer for reless the resouce.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::DrawSprite() {
		// Bind a named texture to a texturing target
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		// Bind the buffer object.
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectID);

		// Draw the 6 vertices to the screen.
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//// Disbale the vertex attribute array.
		//glDisableVertexAttribArray(0);

		// Unbind the vertex buffer object.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
