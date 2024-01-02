#pragma once

#include "IEntityFactory.h"
#include "CannonBall.h"
#include "ParabolicMoveComponent.h"
#include "CollisionComponent.h"
#include "Utilities.h"

/// <summary>
/// Factory that creates CannonBall.
/// Gives them two entity components : move and collision components.
/// </summary>
class CannonBallFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		sptr<CannonBall> _cannonBall = std::make_shared<CannonBall>(_pos);
		_cannonBall->AddComponent<ParabolicMoveComponent>(_velocity);
		_cannonBall->AddComponent<CollisionComponent>(ECollisionType::BALL, CANNON_BALL_COLLISION_PATH.c_str(), 0b110);
		return _cannonBall;
	}
};

