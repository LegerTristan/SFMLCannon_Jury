#pragma once

#include "MoveComponent.h"

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a parabolic trajectory, used for cannon balls that need to take in account the gravity.
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
	/// Move the entity by applying a parabolic velocity.
	/// </summary>
	virtual void Move(const float& dt) override final;

};

