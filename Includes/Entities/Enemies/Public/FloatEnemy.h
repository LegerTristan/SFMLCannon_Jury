#pragma once

#include "Enemy.h"

/// <summary>
/// Inherit from Enemy class.
/// It is a special enemy that move with a floating trajectory.
/// Perfect for representing aerial enemy.
/// </summary>
class FloatEnemy : public Enemy
{
public:

#pragma region Constructors / Destructor
	FloatEnemy() = delete;
	FloatEnemy(const sf::Vector2f position, const sf::Texture& enemyTexture,
		const float& xp);
	~FloatEnemy() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const override { return EEntityType::WRAITH; }
};

