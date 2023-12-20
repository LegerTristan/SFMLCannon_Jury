#include "Boss.h"

unsigned int Boss::mBonusLife = 0;

Boss::Boss(Vector2f _position)
	: GroundEnemy(_position, BOSS_ENEMY_TEXTURE)
{
	// Set enemy's velocity
	UpdateVelocity(BOSS_VELOCITY);

	// Set enemy's movement component
	mMoveComp = new StraightMoveComponent(this, mVelocity);

	// Set enemy's animation component
	mAnimComp = new AnimationComponent(this, .1f, "Assets/JSON/Minotaur_Walking_1.json");

	// Set enemy's collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::ENEMY, "Assets/JSON/Minotaur_Walking_1.json");

	UpdateXP(BOSS_XP);

	mGivenScore = BOSS_SCORE;
	mLife = DEFAULT_BOSS_LIFE + mBonusLife;
	mBonusLife += 5;
}