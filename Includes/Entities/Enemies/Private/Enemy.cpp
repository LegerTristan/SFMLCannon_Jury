#include "Enemy.h"
#include "LevelState.h"
#include "Player.h"


Enemy::Enemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture) :
	Entity(_position, _enemyTexture, DEFAULT_ENEMY_LIFE)
{}

void Enemy::OnCollide(const CollisionComponent& _comp)
{
	onEntityKilled->Invoke(shared_from_this());
}