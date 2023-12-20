#include "Enemy.h"
#include "LevelState.h"
#include "Player.h"


Enemy::Enemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture, const float& _xp, 
	const unsigned int& _givenScore) :
	Entity(_position, _enemyTexture, DEFAULT_ENEMY_LIFE),
	xp(_xp),
	givenScore(_givenScore) {}

void Enemy::Enable()
{
	Entity::Enable();
}

void Enemy::KillByPlayer()
{
	//LevelState::GetInstance()->GetPlayer()->IncreaseXP(GetXP());
	//LevelState::GetInstance()->GetScoreManager()->AddScore(GetScore());
}

void Enemy::KillByGame()
{
	//LevelState::GetInstance()->ReduceHP(1);
}

void Enemy::Disable()
{
	Entity::Disable();
}

void Enemy::OnCollide(const CollisionComponent& _comp)
{
	onEntityKilled->Invoke(shared_from_this());
}