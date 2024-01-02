#pragma once

#include "Enemy.h"

/// <summary>
/// Inherit from Enemy class.
/// Flying enemy that moves straight forward with a floating effect.
/// </summary>
class FloatEnemy : public Enemy
{
public:

#pragma region Constructors / Destructor
	FloatEnemy() = delete;
	FloatEnemy(const sf::Vector2f position, const sf::Texture& enemyTexture);
	~FloatEnemy() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const override { return EEntityType::WRAITH; }
};

