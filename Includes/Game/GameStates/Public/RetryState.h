#pragma once

#include "GameState.h"

class RetryState : public GameState
{
public:
	RetryState();
	~RetryState() = default;

	/// <summary>
	/// Inherited from GameState
	/// Iniyializes some widgets to display final score to the user., 
	/// </summary>
	void Init() override final;

	/// <summary>
	/// Main method call in the level loop.
	/// Draw the final score of the player and wait for player to press F for restarting the game.
	/// </summary>
	void Update(sf::RenderWindow& window, const float& dt) override final;
};

