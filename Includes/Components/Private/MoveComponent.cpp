#include "MoveComponent.h"
#include "Game.h"
#include "Constants.h"

MoveComponent::MoveComponent(sptr<Entity> _entity, sf::Vector2f _velocity) : EntityComponent(_entity), 
	velocity(_velocity) {}

void MoveComponent::UpdateComponent(const float& _dt)
{
	Move(_dt);
}

bool MoveComponent::IsOwnerOutsideScreen() const
{
	const sptr<Entity> _entity = owner.lock();
	return _entity->getPosition().x <= DEFAULT_MIN_BOUNDARY || _entity->getPosition().y >= WINDOW_HEIGHT + PADDING_HEIGHT;
}
