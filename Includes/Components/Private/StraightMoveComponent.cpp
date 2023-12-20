#include "StraightMoveComponent.h"
#include "Constants.h"

bool StraightMoveComponent::Move(const float& _dt)
{
	const float& _scaledDT = _dt * TIME_FLOW_SPEED;
	const sptr<Entity> _entity = owner.lock();
	_entity->setPosition(_entity->getPosition() + velocity * _scaledDT);

	return !IsOwnerOutsideScreen();
}
