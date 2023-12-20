#pragma once

#include "GroundEnemy.h"

const string BOSS_ENEMY_TEXTURE = "Assets/Textures/Minotaur_Walking_1.png";	// Path of the Boss texture
const Vector2f BOSS_VELOCITY = Vector2f(-8.0f, 0.0f);						// Default velocity of the boss
const float BOSS_XP = 50.0f;												// Given XP when the boss died
const unsigned int BOSS_SCORE = 100;										// Given score when the boss died
const int DEFAULT_BOSS_LIFE = 10.0f;										// Default life of a Boss.

/// <summary>
/// Inherited from GroundEnemy
/// A boss is a GroundEnemy with a lot a of HP and which give a lot of Xp.
/// </summary>
class Boss : public GroundEnemy
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	Boss(Vector2f position);
	~Boss() {}

private:

	/// <summary>
	/// Bonus life applied to the boss in function of how many boss the player has defeated.
	/// </summary>
	static unsigned int mBonusLife;
};

