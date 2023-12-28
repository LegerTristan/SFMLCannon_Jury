#pragma once

#include <SFML/Graphics.hpp>
#include "TimerComponent.h"

class TimerText : public sf::Text
{
public:

	TimerText() = delete;
	TimerText(sf::Font& font, const sf::Color& color, const sf::Vector2f& pos);
	~TimerText() = default;

	/// <summary>
	/// Update text for the game timer
	/// </summary>
	/// <param name="currentTime">Current delta time of the game</param>
	void Update(const float& dt);

	void Draw(sf::RenderWindow& window) const;

private:

	/// <summary>
	/// Timeline Component that handles appearance of the wave
	/// </summary>
	uptr<TimerComponent<TimerText>> timeIncrementTimer;

	int currentGameTime;

	void UpdateText();
};