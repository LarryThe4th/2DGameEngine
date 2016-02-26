#pragma once
#include <glm\glm.hpp>
// This header provides a useful function to build orthographic Projection Matrix (AKA ortho).
// Use ortho matrix to map world space coordinate to normalized device coordinates.
#include <glm\gtc\matrix_transform.hpp>

namespace GameEngine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		// Sets up the orthographic matrix and screen dimensions.
		void InitCamera(int screenWidth, int screenHeight);

		// Updates the camera matrix.
		void UpdateCamera();

		// Take the screen coordinate and convert to into world coordinate.
		glm::vec2 GetWorldFormScreen(glm::vec2 screenPoint);

		// Setters
		void SetCameraPosition(const glm::vec2& newPosition) { _cameraPosition = newPosition; _updateCamera = true; }
		void SetCameraScale(float newScale) { 
			// You can't zoom in less or equal to 0.
			if (newScale <= 0.0f) 
				_cameraScale = 0.001f;
			else
				_cameraScale = newScale; 
			_updateCamera = true; 
		}

		// Getters
		float GetCurrentScale() { return _cameraScale; }
		glm::vec2 GetCameraPosition() { return _cameraPosition; }
		glm::mat4 GetCameraMatrix() { return _cameraMatrix; }

	private:
		// The size of the screen.
		int _screenWidth, _screenHeight;
		// If the camera needs to update set it to true.
		bool _updateCamera;
		// The scale of the camera.
		float _cameraScale;
		// Same as a glsl vec2 that stores 2 floats.
		glm::vec2 _cameraPosition;
		// The orthographic Projection Matrix.
		glm::mat4 _orthoMatrix;
		glm::mat4 _cameraMatrix;
	};
}
