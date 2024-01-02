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
	/// Move the entity by applying the velocity, resulting in a straight move.
	/// </summary>
	virtual void Move(const float& dt) override final;

};

