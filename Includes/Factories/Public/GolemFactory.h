#pragma once

#include "IEntityFactory.h"
#include "GroundEnemy.h"
#include "StraightMoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "Game.h"

/// <summary>
/// Factory that creates GroundEnemy.
/// Gives them three entity components : move, collision and animation components.
/// </summary>
class GolemFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		sptr<GroundEnemy> _groundEnemy = std::make_shared<GroundEnemy>(_pos, 
			Game::GetInstance()->GetTextureManager().GetTexture(GROUND_ENEMY_TEXTURE));

		_groundEnemy->AddComponent<StraightMoveComponent>(_velocity);
		_groundEnemy->AddComponent<AnimationComponent>(GROUND_ENEMY_ANIM_DELAY, GROUND_ENEMY_ANIMATION_PATH.c_str());
		_groundEnemy->AddComponent<CollisionComponent>(ECollisionType::ENEMY, GROUND_ENEMY_ANIMATION_PATH.c_str(), 0b101);
		return _groundEnemy;
	}
};
