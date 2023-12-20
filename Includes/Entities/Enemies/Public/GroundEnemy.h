#pragma once

#include "Enemy.h"

/// <summary>
/// Inherit from Enemy class.
/// It is a special enemy that move with a straight trajectory.
/// Perfect for representing ground enemy.
/// </summary>
class GroundEnemy : public Enemy
{
public:

#pragma region Constructors/Destructor
	GroundEnemy() = delete;
	GroundEnemy(const sf::Vector2f position, const sf::Texture& enemyTexture, 
		const float& xp, const unsigned int& givenScore);
	~GroundEnemy() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const override { return EEntityType::GOLEM; }
};

