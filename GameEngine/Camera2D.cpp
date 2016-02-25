#include "Camera2D.h"

/*
Learn more about the matrices and how these works. See the link below:
https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/
*/

namespace GameEngine {
	// Consturctor, initializes private member variables
	Camera2D::Camera2D() :
		_screenWidth(500), 
		_screenHeight(500),
		_updateCamera(true),
		// REMENBER!!!! Don't set the camera scale to 0!!!
		// This little bug cost me about a half hour!!!
		_cameraScale(1.0f),
		_cameraPosition(0.0f, 0.0f),
		_orthoMatrix(1.0f),
		_cameraMatrix(1.0f)
	{
	}

	// Destructor
	Camera2D::~Camera2D()
	{
	}

	// Initialize the camera.
	void Camera2D::InitCamera(int screenWidth, int screenHeight) {
		// Set up the camera size.
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		// Set up the orthographic Projection Matrix.
		_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	}

	void Camera2D::UpdateCamera() {
		if (_updateCamera) {
			// Translate the ortho Matrix into camera matrix.
			// The reason of using minus position value is because:
			// For example, if the object in the view of the camera is moving to the RIGHT.
			// In fact that is same as the camera itself move to the LEFT.
			glm::vec3 translate = glm::vec3(-_cameraPosition.x, -_cameraPosition.y, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			// Scale the camera, notice that you have to do the scale AFTER the translation.
			glm::vec3 scale = glm::vec3(_cameraScale, _cameraScale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			
			_updateCamera = false;
		}
	}
}
