#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.h"

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Contains mostly widgets that are drawn in a game state.
/// </summary>
class HUD
{

public:

#pragma region Constructor/Destructor
	HUD();
	virtual ~HUD() = default;
#pragma endregion

	/// <summary>
	/// Update all UI elements
	/// </summary>
	/// <param name="dt">Current delta time</param>
	virtual void Update(const float& dt);

	/// <summary>
	/// Draw all UI elements
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Draw(sf::RenderWindow& window) const;

protected:

#pragma region Properties
	/// <summary>
	/// Sprite of the background of the level
	/// </summary>
	sf::Sprite levelBackground;

	/// <summary>
	/// Font of the game
	/// </summary>
	sf::Font font;
#pragma endregion;
};

