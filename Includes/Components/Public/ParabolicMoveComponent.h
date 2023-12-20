#pragma once

#include "MoveComponent.h"

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a parabolic trajectory, usefull for balls that need to take in account the gravity.
/// </summary>
class ParabolicMoveComponent : public MoveComponent
{
public:
#pragma region Constructors/Destructors
	ParabolicMoveComponent() = delete;
	ParabolicMoveComponent(sptr<Entity> _entity, sf::Vector2f _velocity) : MoveComponent(_entity, _velocity) {}
	~ParabolicMoveComponent() = default;
#pragma endregion

protected:

	/// <summary>
	/// Move the player along a parabolic trajectory
	/// The parabolic trajectory use the next formula to calculate owner's position :	X = V0.X * t + P0.X
	///																					Y = (g / 2) * t² + V0.Y * t + P0.Y
	/// Fact : That is g / 2 cause of the Y axis which is inverted.
	/// </summary>
	virtual bool Move(const float& dt) override final;

};

