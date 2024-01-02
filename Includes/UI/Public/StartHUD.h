#pragma once

#include "HUD.h"
#include "LerpAnimation.h"

/// <summary>
/// Inherits from HUD.
/// Contains informations about game goal, controls and which key to press to start the game.
/// </summary>
class StartHUD : public HUD
{
public:

#pragma region Constructor/Destructor
	StartHUD();
	~StartHUD() = default;
#pragma endregion

	virtual void Update(const float& dt) override final;

	virtual void Draw(sf::RenderWindow & window) const override final;

private:

#pragma region Properties
	/// <summary>
	/// Informs the user how to start the game.
	/// </summary>
	sf::Text startText;

	sf::Text controlsText;

	/// <summary>
	/// Explain the goal of the game.
	/// </summary>
	sf::Text goalText;

	/// <summary>
	/// Lerp animation effect that make the startText scale vary.
	/// </summary>
	LerpAnimation<StartHUD> startTextScaleEffect;
#pragma endregion

	void UpdateStartTextScale(const float& _uniformScale);
};

