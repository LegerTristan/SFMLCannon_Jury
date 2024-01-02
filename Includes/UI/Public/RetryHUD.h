#pragma once

#include "HUD.h"
#include "ScoreText.h"

/// <summary>
/// Inherits from HUD.
/// Draw latest and highest score of the player and which key to press in order to restart the game.
/// </summary>
class RetryHUD : public HUD
{
public:

#pragma region Constructor/Destructor
	RetryHUD();
	~RetryHUD() = default;
#pragma endregion

	void Init();

	virtual void Draw(sf::RenderWindow& window) const override final;

private:

#pragma region properties
	/// <summary>
	///  Displays which key to press for retry.
	/// </summary>
	sf::Text retryText;

	/// <summary>
	///  Latest score text
	/// </summary>
	sf::Text scoreText;

	/// <summary>
	///  Highest score text
	/// </summary>
	sf::Text hScoreText;
#pragma endregion
};

