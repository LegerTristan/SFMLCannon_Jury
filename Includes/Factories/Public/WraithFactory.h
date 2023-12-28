#pragma once

#include "IEntityFactory.h"
#include "FloatEnemy.h"
#include "FloatMoveComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

class WraithFactory : public IEntityFactory
{
public:

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) override
	{
		const char* _jsonPath = Utilities::StringToCharArray(FLOAT_ENEMY_ANIMATION_PATH);

		sptr<FloatEnemy> _floatEnemy = std::make_shared<FloatEnemy>(_pos,
			Game::GetInstance()->GetTextureManager().GetTexture(FLOAT_ENEMY_TEXTURE_PATH),
			FLOAT_ENEMY_XP);

		_floatEnemy->AddComponent<FloatMoveComponent>(_velocity, DEFAULT_FLOAT_ENEMY_AMPLITUDE, DEFAULT_FLOAT_ENEMY_FREQUENCY);
		_floatEnemy->AddComponent<AnimationComponent>(FLOAT_ENEMY_ANIM_DELAY, _jsonPath);
		_floatEnemy->AddComponent<CollisionComponent>(ECollisionType::ENEMY, _jsonPath, 0b101);
		delete _jsonPath;
		return _floatEnemy;
	}
};