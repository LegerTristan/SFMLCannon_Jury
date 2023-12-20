#include "FloatEnemy.h"
#include "Game.h"
#include "Constants.h"

FloatEnemy::FloatEnemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture,
	const float& _xp, const unsigned int& _givenScore)
	: Enemy(_position, _enemyTexture, _xp, _givenScore)
{
	// Set enemy's sprite & settings
	setScale(FLOAT_ENEMY_SCALE);
}
