#pragma once

#include "MoveComponent.h"

const float DEFAULT_FLOAT_VARIATION = 10.0f;	// Default float variation in floating upgrade
const float FLOAT_VARIATION_SCALAR = 2.5f;		// Scalar for floating variation upgrade.

const float FLOW_SPEED = 4.0f;				// Speed of the flow of time.

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
	/// Move the player along a straight trajectory with a floating like movement on Y axis.
	/// The next formula is used to calculate owner's position :	X = V0.X * t + P0.X
	///																Y = sinf(t) * mFloatVariation + P0.Y
	/// </summary>
	virtual bool Move(const float& dt) override final;

private:

	float floatAmplitude;

	float floatFrequency;

	float elapsedTime;
};

