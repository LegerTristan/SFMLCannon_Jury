#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Player;

/// <summary>
/// UI class that represents player's life.
/// </summary>
class LifeBar
{
public:

#pragma region Constructors/Destructor
	LifeBar() = delete;
	LifeBar(sf::Vector2f position, const int& lifeQty);
	~LifeBar() = default;
#pragma endregion

	void BindToPlayerLife(Player& _player);

	/// <summary>
	/// Draw all heart sprites
	/// </summary>
	/// <param name="window">Game window</param>
	void Draw(sf::RenderWindow& window);

private:

	/// <summary>
	/// Sprites used to represent life points of the player
	/// </summary>
	std::vector<sf::Sprite> hearts;

	/// <summary>
	/// Position of the sprite.
	/// </summary>
	sf::Vector2f position;

	unsigned int qtyToDraw = 0;

	inline void UpdateQtyToDraw(const unsigned int& _qtyToDraw) { qtyToDraw = _qtyToDraw;  }
};

