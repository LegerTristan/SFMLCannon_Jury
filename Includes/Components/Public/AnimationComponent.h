#pragma once

#include <vector>
#include "EntityComponent.h"

/// <summary>
/// Contains UV position and size of the UV rect of a frame of an animation.
/// </summary>
struct AnimationFrame
{
	sf::Vector2i uvRectPos, uvRectSize;
};

/// <summary>
/// Component that create an animation on the sprite of the entity
/// based on JSON passed in constructor's param.
/// </summary>
class AnimationComponent : public EntityComponent
{
public:

#pragma region Constructors/Destructor
	AnimationComponent() = delete;
	AnimationComponent(sptr<Entity> entity, const float& nextAnimDelay, const char* filePath);
	~AnimationComponent() = default;
#pragma endregion

	inline virtual EEntityComponentType GetComponentType() const override { return EEntityComponentType::ANIMATION; }

	/// <summary>
	/// Update a sprite by passing to the next frame.
	/// And when reached the final frame, reset to the first.
	/// </summary>
	void UpdateComponent(const float& dt);

private:

	/// <summary>
	/// Frames of the animation.
	/// </summary>
	std::vector<AnimationFrame> frames;

	/// <summary>
	/// Delay between every frame
	/// </summary>
	float nextAnimDelay;

	/// <summary>
	/// Current elapsed Time since the last update.
	/// </summary>
	float currentAnimTime;

	/// <summary>
	/// Index of the current frame.
	/// </summary>
	unsigned int frameIndex;
};

