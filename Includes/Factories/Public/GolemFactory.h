#pragma once

#include "IEntityFactory.h"
#include "GroundEnemy.h"
#include "StraightMoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "Game.h"

class GolemFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		const char* _jsonPath = Utilities::StringToCharArray(GROUND_ENEMY_ANIMATION_PATH);

		sptr<GroundEnemy> _groundEnemy = std::make_shared<GroundEnemy>(_pos, 
			Game::GetInstance()->GetTextureManager().GetTexture(GROUND_ENEMY_TEXTURE),
			GROUND_ENEMY_XP);

		_groundEnemy->AddComponent<StraightMoveComponent>(_velocity);
		_groundEnemy->AddComponent<AnimationComponent>(GROUND_ENEMY_ANIM_DELAY, _jsonPath);
		_groundEnemy->AddComponent<CollisionComponent>(ECollisionType::ENEMY, _jsonPath, 0b101);
		delete _jsonPath;
		return _groundEnemy;
	}
};
