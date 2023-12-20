#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Contains the current time and delta time of the engine.
/// Can be accessed via static call through the singleton instance.
/// </summary>
class TimeManager
{
public:
#pragma region Constructor/Destructor
	TimeManager();
	~TimeManager() = default;
#pragma endregion

#pragma region Getters/Setters
	float GetDeltaTime() const;
	float GetCurrentTime() const;
	void SetPause(const bool& pause);
#pragma endregion

#pragma region Methods
	/// <summary>
	/// Update the current via the clock.
	/// </summary>
	void UpdateCurrentTime();

	/// <summary>
	/// Update the last time and set it equal to the current time.
	/// </summary>
	void UpdateLastTime();

	/// <summary>
	/// Calcul the deltaTime.
	/// </summary>
	float CalculateDeltaTime();
#pragma endregion
private:

#pragma region Properties
	/// <summary>
	/// Clock to update the current time and which has the elapsed time since the last restart function called.
	/// </summary>
	sf::Clock clock;

	/// <summary>
	/// The currentTime saved by the manager (current frame) and the last time (last frame)
	/// </summary>
	sf::Time currentTime, lastTime, runTime;

	/// <summary>
	/// DeltaTime of the time between current frame and last frame.
	/// </summary>
	float deltaTime;

	/// <summary>
	/// Is the time currently paused or not.
	/// </summary>
	bool isPaused = false;
#pragma endregion
};

