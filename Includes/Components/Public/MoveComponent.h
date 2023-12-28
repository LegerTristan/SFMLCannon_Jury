#pragma once

#include "EntityComponent.h"
#include "Entity.h"

/// <summary>
/// Component that allows is Owner to move based on a velocity passed in constructor
/// Move method needs to be override.
/// </summary>
class MoveComponent : public EntityComponent
{
public:

#pragma region Constructors/Destructors
	MoveComponent() = delete;
	MoveComponent(sptr<Entity> entity, sf::Vector2f velocity);
	virtual ~MoveComponent() = default;
#pragma endregion 
	
	inline virtual EEntityComponentType GetComponentType() const override { return EEntityComponentType::MOVE; }
	inline void SetVelocity(const sf::Vector2f& _velocity) { velocity = _velocity; }

	virtual void UpdateComponent(const float& dt) override;

protected:

	/// <summary>
	/// Velocity of the component and so the Owner.
	/// </summary>
	sf::Vector2f velocity;

#pragma region Methods
	/// <summary>
	/// Virtual pure method to move the owner along a predifined type of Movement
	/// </summary>
	virtual void Move(const float& dt) = 0;
#pragma endregion
};

