#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.h"

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Contains UI elements that is bind to the game such as timer, wave flicker text.
/// </summary>
class HUD
{

public:

#pragma region Constructor/Destructor
	HUD();
	virtual ~HUD();
#pragma endregion

	/// <summary>
	/// Update text for the game timer
	/// </summary>
	/// <param name="currentTime">Current delta time</param>
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
	static sf::Font* font;
#pragma endregion;
};

