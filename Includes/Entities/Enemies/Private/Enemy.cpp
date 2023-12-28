#include "Enemy.h"
#include "LevelState.h"
#include "Player.h"


Enemy::Enemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture, const float& _xp) :
	Entity(_position, _enemyTexture, DEFAULT_ENEMY_LIFE),
	xp(_xp)
{}

void Enemy::Enable()
{
	Entity::Enable();
}

void Enemy::Disable()
{
	Entity::Disable();
}

void Enemy::OnCollide(const CollisionComponent& _comp)
{
	onEntityKilled->Invoke(shared_from_this());
}