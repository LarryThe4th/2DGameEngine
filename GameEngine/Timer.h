#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

namespace GameEngine {
	class FpsLimiter
	{
	public:

		FpsLimiter();
		// ~FpsLimiter();

		// By defualt target fps will be set as 60 fps.
		void InitFpsLimiter(float targetFps = 60.0f);
		void SetTargetFPS(float targetFps);

		void OnFrameBegin();
		float OnFrameEnd();

		void FpsCounter();
	private:
		void CalculateFPS();

		float _targetFps;
		Uint32 _frameTime;
		float _fps;

		Uint32 _startTicks;
	};
}
