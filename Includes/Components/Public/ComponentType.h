#pragma once

/// <summary>
/// Entity component's type.
/// </summary>
enum class EEntityComponentType
{
	MOVE = 1,	// Component that edit the current position of the entity.
	COLLISION,	// Component that gives a collision behavior to the entity.
	ANIMATION,	// Component used for enabling an animation logic on the entity.
};