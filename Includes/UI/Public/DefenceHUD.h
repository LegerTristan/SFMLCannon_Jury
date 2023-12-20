#pragma once
#include "HUD.h"

class DefenceHUD : public HUD
{
public:

	DefenceHUD();
	~DefenceHUD() = default;

	/// <summary>
	/// Update text for the game timer
	/// </summary>
	/// <param name="currentTime">Current time of the game</param>
	virtual void Update(const float& dt) override final;

	void UpdateTimerText();

	/// <summary>
	/// Draw all UI elements
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Draw(sf::RenderWindow& window) const override final;

protected:

	/// <summary>
	/// Background for the game's UI elements.
	/// </summary>
	sf::Sprite cloundBackground;

	/// <summary>
	/// Text for displaying the timer
	/// </summary>
	sf::Text timerText;
};
