#pragma once

#include "IEntityFactory.h"
#include "FloatEnemy.h"
#include "FloatMoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

/// <summary>
/// Factory that creates FloatEnemy.
/// Gives them three entity components : move, collision and animation components.
/// </summary>
class WraithFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		sptr<FloatEnemy> _floatEnemy = std::make_shared<FloatEnemy>(_pos,
			Game::GetInstance()->GetTextureManager().GetTexture(FLOAT_ENEMY_TEXTURE_PATH));

		_floatEnemy->AddComponent<FloatMoveComponent>(_velocity, DEFAULT_FLOAT_ENEMY_AMPLITUDE, DEFAULT_FLOAT_ENEMY_FREQUENCY);
		_floatEnemy->AddComponent<AnimationComponent>(FLOAT_ENEMY_ANIM_DELAY, FLOAT_ENEMY_ANIMATION_PATH.c_str());
		_floatEnemy->AddComponent<CollisionComponent>(ECollisionType::ENEMY, FLOAT_ENEMY_ANIMATION_PATH.c_str(), 0b101);
		return _floatEnemy;
	}
};