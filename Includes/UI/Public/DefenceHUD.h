#pragma once
#include "HUD.h"
#include "ScoreText.h"
#include "TimerText.h"
#include "TimerComponent.h"

/// <summary>
/// Inherits from HUD.
/// Contains level state HUD such as life bar, elapsedTime since the start or also current score.
/// </summary>
class DefenceHUD : public HUD
{
public:

#pragma region Constructor/Destructor
	DefenceHUD();
	~DefenceHUD() = default;
#pragma endregion

	inline ScoreText& GetScoreText() { return scoreText; }

	virtual void Update(const float& dt) override final;

	virtual void Draw(sf::RenderWindow& window) const override final;

protected:

	/// <summary>
	/// Background for the game's UI elements.
	/// </summary>
	sf::Sprite cloudBackground;

	TimerText timerText;

	ScoreText scoreText;
};

