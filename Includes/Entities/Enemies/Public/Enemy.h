#pragma once

#include "MoveComponent.h"

/// <summary>
/// Inherit from Entity class.
/// It is a type of entity which the player needs to destroy before they make him lose his HP.
/// </summary>
class Enemy : public Entity
{
public:

#pragma region Constructors / Destructor
	Enemy() = delete;
	Enemy(const sf::Vector2f position, const sf::Texture& enemyTexture);
	virtual ~Enemy() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const = 0;

protected:

	virtual void OnCollide(const CollisionComponent& _comp) override;
};