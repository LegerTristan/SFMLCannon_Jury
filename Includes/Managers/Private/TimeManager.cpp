#include "TimeManager.h"

TimeManager::TimeManager()
{
	currentTime = clock.getElapsedTime();
	deltaTime = 0.0f;
}

float TimeManager::GetDeltaTime() const
{
	return deltaTime;
}

float TimeManager::GetCurrentTime() const
{
	return currentTime.asSeconds();
}

void TimeManager::SetPause(const bool& _pause)
{
	isPaused = _pause;

	if (isPaused)
	{
		runTime = currentTime;
	}
	else
	{
		clock.restart();
	}
}

void TimeManager::UpdateCurrentTime()
{
	if(!isPaused)
		currentTime = clock.getElapsedTime() + runTime;
}

void TimeManager::UpdateLastTime()
{
	if(!isPaused)
		lastTime = currentTime;
}

float TimeManager::CalculateDeltaTime()
{
	if(!isPaused)
		deltaTime = currentTime.asSeconds() - lastTime.asSeconds();

	return deltaTime;
}
