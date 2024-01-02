#pragma once

#include <SFML/Graphics.hpp>
#include "TimerComponent.h"

/// <summary>
/// Text that displays elapsed time since the start of the game.
/// </summary>
class TimerText : public sf::Text
{
public:

#pragma region Constructors/Destructor
	TimerText() = delete;
	TimerText(sf::Font& font, const sf::Color& color, const sf::Vector2f& pos);
	~TimerText() = default;
#pragma endregion

	/// <summary>
	/// Update text for the game timer
	/// </summary>
	/// <param name="currentTime">Current delta time of the game</param>
	void Update(const float& dt);

	void Draw(sf::RenderWindow& window) const;

private:

#pragma region Properties
	/// <summary>
	/// Timeline Component that handles appearance of the wave
	/// </summary>
	uptr<TimerComponent<TimerText>> timeIncrementTimer;

	int currentGameTime;
#pragma endregion

	void UpdateText();
};