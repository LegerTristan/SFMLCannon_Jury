#pragma once
#include "MoveComponent.h"

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a straight trajectory.
/// </summary>
class StraightMoveComponent : public MoveComponent
{
public:

#pragma region Constructors/Destructor
	StraightMoveComponent() = delete;
	StraightMoveComponent(sptr<Entity> _entity, sf::Vector2f _velocity) : MoveComponent(_entity, _velocity) {}
	~StraightMoveComponent() override = default;
#pragma endregion

	/// <summary>
	/// Move the player along a straight trajectory
	/// The next formula is used to calculate owner's position :	X = V0.X * t + P0.X
	///																Y = V0.Y * t + P0.Y
	/// </summary>
	virtual bool Move(const float& dt) override final;

};

