#pragma once

#include <SFML/Graphics.hpp>
#include "HUD.h"
#include "IDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// A Game state is a particular state of the game.
/// Similar to a specific window of the game such as the level window or the menu window.
/// </summary>
class GameState
{
public:

#pragma region Constructors/Destructor
	GameState() = delete;
	GameState(uptr<HUD> _hud) : hud(std::move(_hud)) , onStateEnded(std::make_unique<Action<>>(nullptr)) {}
	virtual ~GameState() = default;
#pragma endregion

	inline Action<>& OnStateEnded() { return *onStateEnded; }
	inline bool IsInit() const { return isInit; }

#pragma region Methods

	/// <summary>
	/// Init features that is needed for the good work of the state.
	/// </summary>
	virtual void Init() { isInit = true; }

	/// <summary>
	/// Update the state, this method needs to be called in a loop
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Update(sf::RenderWindow& window, const float& dt) = 0;
#pragma endregion

protected:

#pragma region Properties
	/// <summary>
	/// Delegate invoked when the state reaches its end.
	/// </summary>
	uptr<Action<>> onStateEnded;

	/// <summary>
	/// Current HUD of the state that contains mostly all widgets to draw on the window.
	/// </summary>
	uptr<HUD> hud;

	bool isInit = false;
#pragma endregion

	virtual void EndState();
};

