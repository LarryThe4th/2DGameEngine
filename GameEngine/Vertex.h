#pragma once

#include <gl\glew.h>

namespace GameEngine {
	// Position is the type.
	struct Position
	{
		float x;
		float y;
	};

	// 4 bytes for red, green, blue, alpha color.
	struct Color
	{
		GLubyte red;
		GLubyte green;
		GLubyte blue;
		GLubyte alpha;
	};

	// The uv coordinate of the texture.
	struct UV
	{
		float u;
		float v;
	};

	// The vertex definition
	struct Vertex
	{
		// This is the position sturct.
		// When you store a struct or class inside of another struct or class, its called composition.
		// The layed out exactly the same in memory as if we had a float position[2].
		// But doing it this way makes more sense.
		Position position;

		Color color;

		// UV texture coordinates.
		UV uv;

		void SetPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void SetColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
			color.red = red;
			color.blue = blue;
			color.green = green;
			color.alpha = alpha;
		}

		void SetUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};
}