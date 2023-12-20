#pragma once

#include "IEntityFactory.h"
#include "CannonBall.h"
#include "ParabolicMoveComponent.h"
#include "CollisionComponent.h"
#include "Utilities.h"

class CannonBallFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		const char* _jsonPath = Utilities::StringToCharArray(CANNON_BALL_COLLISION_PATH);

		sptr<CannonBall> _cannonBall = std::make_shared<CannonBall>(_pos);
		_cannonBall->AddComponent<ParabolicMoveComponent>(_velocity);
		_cannonBall->AddComponent<CollisionComponent>(ECollisionType::BALL, _jsonPath, 0b110);
		delete _jsonPath;
		return _cannonBall;
	}
};

