#include "Timer.h"
#include <iostream>

namespace GameEngine {
	FpsLimiter::FpsLimiter() : 
		_targetFps(60.0f),
		_frameTime(0),
		_fps(0.0f),
		_startTicks(0)
	{
	}

	void FpsLimiter::InitFpsLimiter(float targetFps) {
		SetTargetFPS(targetFps);
	}

	void FpsLimiter::SetTargetFPS(float targetFps) {
		_targetFps = targetFps;
	}

	void FpsLimiter::OnFrameBegin() {
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::OnFrameEnd() {
		CalculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//Limit the FPS to the max FPS
		if (1000.0f / _targetFps > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _targetFps - frameTicks));
		}

		return _fps;
	}

	void FpsLimiter::FpsCounter() {
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter % 10 == 0) {
			std::cout << "FPS: " << _fps << std::endl;
			frameCounter = 0;
		}
	}

	void FpsLimiter::CalculateFPS() {
		// The number of frames to average count.
		static const Uint32 numberOfSamples = 10;
		// Stores all the frametimes for each frame that needs to average
		static Uint32 frameTimes[numberOfSamples];
		// The current frame.
		static Uint32 currentFrame = 0;
		// The ticks of the previous frame.
		static Uint32 previousTicks = SDL_GetTicks();
		// After stored the previous ticks, update current ticks.
		Uint32 currentTicks = SDL_GetTicks();

		// Calculate the number of ticks(ms) for this frame.
		_frameTime = currentTicks - previousTicks;
		frameTimes[currentFrame % numberOfSamples] = _frameTime;

		// current ticks is now the past.
		previousTicks = currentTicks;

		// The number of frames to average.
		Uint32 count;
		currentFrame++;
		count = currentFrame < numberOfSamples ? currentFrame : numberOfSamples;

		// Average all the frame times.
		Uint32 frameTimeAverage = 0;
		for (Uint32 i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		// Calculate fps
		if (frameTimeAverage > 0) {
			_fps = 1000.0f / frameTimeAverage;
		}
	}
}