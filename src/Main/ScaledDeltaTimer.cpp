#include "ScaledDeltaTimer.h"

#include <SDL.h>

void ScaledDeltaTimer::Start()
{
	lastFrameTime = SDL_GetTicks();
}

void ScaledDeltaTimer::Update()
{
	std::uint32_t ticks = SDL_GetTicks();
	unscaledDelta = (ticks - static_cast<float>(lastFrameTime)) / 1000;
	scaledDelta = unscaledDelta * timeScale;
	lastFrameTime = ticks;
}

void ScaledDeltaTimer::SetScaleFactor(double newScale)
{
	timeScale = newScale;
}

double ScaledDeltaTimer::GetScaleFactor() const
{
	return timeScale;
}

double ScaledDeltaTimer::GetScaledTime() const
{
	return scaledDelta;
}

double ScaledDeltaTimer::GetUnscaledTime() const
{
	return unscaledDelta;
}

std::uint32_t ScaledDeltaTimer::GetFrameStart() const
{
	return lastFrameTime;
}