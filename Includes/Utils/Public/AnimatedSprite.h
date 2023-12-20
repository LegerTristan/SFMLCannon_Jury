#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();	// Need to add another constructor
	~AnimatedSprite() {}

	void UpdateAnimSprite();

private:
	Texture mAnimatedTexture;
	Vector2i mSliceRect, mLengthAnim, mCurrentSpriteAnim;
	float mNextAnimDelay, mCurrentAnimTime;
};

