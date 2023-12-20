#include "FloatMoveComponent.h"
#include "Constants.h"

bool FloatMoveComponent::Move(const float& _dt)
{
	const float& _scaledDT = _dt * TIME_FLOW_SPEED;

	const sptr<Entity> _entity = owner.lock();
	_entity->setPosition(_entity->getPosition() + velocity * _scaledDT);
	elapsedTime += _scaledDT;
	velocity = sf::Vector2f(velocity.x, sinf(floatFrequency * elapsedTime) * floatAmplitude);
	return !IsOwnerOutsideScreen();
}