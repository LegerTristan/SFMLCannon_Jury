#pragma once

#include "GameState.h"

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Game state that appears when the user loses.
/// Displays the latest and highest score and proposes him to retry.
/// </summary>
class RetryState : public GameState
{
public:
#pragma region Constructor/Destructor
	RetryState();
	~RetryState() = default;
#pragma endregion

#pragma region GameStateMethods
	/// <summary>
	/// Inherited from GameState
	/// Initializes some widgets to display final score to the user., 
	/// </summary>
	void Init() override final;

	/// <summary>
	/// Main method call in the level loop.
	/// Draw the final score of the player and wait for player to press F for restarting the game.
	/// </summary>
	void Update(sf::RenderWindow& window, const float& dt) override final;

protected:

	virtual void EndState() override final;
#pragma endregion

private:

	/// <summary>
	/// Specific input that the player needs to press in order to restart the game.
	/// </summary>
	const Scancode RETRY_KEY = Scancode::F;
};

