#include "FloatEnemy.h"
#include "Game.h"
#include "Constants.h"

FloatEnemy::FloatEnemy(const sf::Vector2f _position, const sf::Texture& _enemyTexture)
	: Enemy(_position, _enemyTexture)
{
	// Set enemy's sprite & settings
	setScale(FLOAT_ENEMY_SCALE);
}
