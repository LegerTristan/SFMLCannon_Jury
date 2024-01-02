#include "TimeManager.h"

TimeManager::TimeManager() :
	clock(sf::Clock()),
	currentTime(sf::Time()),
	lastTime(sf::Time()),
	deltaTime(0.0f)
{
	currentTime = clock.getElapsedTime();
}

void TimeManager::UpdateCurrentTime()
{
	currentTime = clock.getElapsedTime();
}

void TimeManager::UpdateLastTime()
{
	lastTime = currentTime;
}

float TimeManager::ComputeDeltaTime()
{
	return deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
}
