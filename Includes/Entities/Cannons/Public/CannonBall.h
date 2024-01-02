#pragma once

#include "Entity.h"

/// <summary>
/// Inherit from Entity.
/// A cannon ball is a ball that follows a parabolic trajectory.
/// It is destroyed when colliding with an enemy.
/// </summary>
class CannonBall : public Entity
{
public:

#pragma region Constructors/Destructor
	CannonBall() = delete;
	CannonBall(const sf::Vector2f position);
	~CannonBall() = default;
#pragma endregion

#pragma region PublicMethods
	inline virtual EEntityType GetEntityType() const override { return EEntityType::CANNON_BALL; }

	virtual void OnCollide(const CollisionComponent& _comp) override;
#pragma endregion
};

