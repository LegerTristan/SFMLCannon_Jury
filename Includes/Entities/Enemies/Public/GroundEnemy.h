#pragma once

#include "Enemy.h"

/// <summary>
/// Inherit from Enemy class.
/// Earthly enemy that moves straight forward.
/// </summary>
class GroundEnemy : public Enemy
{
public:

#pragma region Constructors/Destructor
	GroundEnemy() = delete;
	GroundEnemy(const sf::Vector2f position, const sf::Texture& enemyTexture);
	~GroundEnemy() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const override { return EEntityType::GOLEM; }
};

