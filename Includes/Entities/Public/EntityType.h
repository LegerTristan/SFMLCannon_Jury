#pragma once

/// <summary>
/// Type of the entity, each entity has a specific type.
/// </summary>
enum class EEntityType
{
	NONE = -1,

	CANNON_BALL = 0,

	// Enemies type
	GOLEM,
	WRAITH,
	MINOTAUR,
};