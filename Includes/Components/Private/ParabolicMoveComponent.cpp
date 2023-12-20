#include "ParabolicMoveComponent.h"
#include "Constants.h"

bool ParabolicMoveComponent::Move(const float& _dt)
{
	const float& _scaledDT = _dt * TIME_FLOW_SPEED;
	const sptr<Entity> _entity = owner.lock();

	_entity->setPosition(_entity->getPosition() + velocity * _scaledDT);
	velocity = sf::Vector2f(velocity.x, velocity.y + G * _scaledDT);
	return !IsOwnerOutsideScreen();
}
