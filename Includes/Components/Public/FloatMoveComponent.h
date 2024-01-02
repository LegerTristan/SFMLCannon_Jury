#pragma once

#include "MoveComponent.h"

/// <summary>
/// Inherited from MoveComponent.
/// Allows owner to move in a straight trajectory with a floating like movement on Y axis.
/// </summary>
class FloatMoveComponent : public MoveComponent
{
public:

#pragma region Constructors/Destructor
	FloatMoveComponent() = delete;
	FloatMoveComponent(sptr<Entity> _entity, sf::Vector2f _velocity, const float& _floatAmplitude, 
		const float& _floatFrequency) :
		MoveComponent(_entity, _velocity), floatAmplitude(_floatAmplitude), floatFrequency(_floatFrequency), elapsedTime(0.0f) {}
	~FloatMoveComponent() = default;
#pragma endregion

	/// <summary>
	/// Move the entity by applying the velocity with an oscillation on Y axis to simulate a float movement.
	/// </summary>
	virtual void Move(const float& dt) override final;

private:

#pragma region Properties
	float floatAmplitude;

	float floatFrequency;

	float elapsedTime;
#pragma endregion
};

