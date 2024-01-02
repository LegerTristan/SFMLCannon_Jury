#include "ParabolicMoveComponent.h"
#include "Constants.h"

void ParabolicMoveComponent::Move(const float& _dt)
{
	const float _scaledDT = _dt * TIME_FLOW_SPEED;
	const sptr<Entity> _entity = owner.lock();

	_entity->setPosition(_entity->getPosition() + velocity * _scaledDT);

	// Y axis is inverted so we apply a sum on Y axis instead of a difference for the gravity
	velocity = sf::Vector2f(velocity.x, velocity.y + G * _scaledDT);
}
