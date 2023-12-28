#include "GroundEnemy.h"
#include "Game.h"
#include "Constants.h"

GroundEnemy::GroundEnemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture,
	const float& _xp)
	: Enemy(_position, _enemyTexture, _xp)
{
	// Set enemy's sprite & settings
	setScale(GROUND_ENEMY_SCALE);
}