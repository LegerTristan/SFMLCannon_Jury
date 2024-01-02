#pragma once

#include "GameState.h"

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Game state that appears at the start of the game, mostly used as a main menu state.
/// Displays controls and game goal.
/// </summary>
class StartState : public GameState
{
public:
#pragma region Constructor/Destructor
	StartState();
	~StartState() = default;
#pragma endregion

#pragma region GameStateMethods
	void Init() override final;

	void Update(sf::RenderWindow & window, const float& dt) override final;

protected:

	virtual void EndState() override final;
#pragma endregion

private:

	/// <summary>
	/// Specific input that the player needs to press in order to start the game.
	/// </summary>
	const Scancode START_KEY = Scancode::Enter;
};

