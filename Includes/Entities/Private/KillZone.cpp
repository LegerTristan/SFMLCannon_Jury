#include "KillZone.h"
#include "CollisionComponent.h"

void KillZone::Init(const sf::Vector2f& _size)
{
	AddComponent<CollisionComponent>(ECollisionType::KILL_ZONE, _size, 0b011);
}

void KillZone::OnCollide(const CollisionComponent& _comp)
{
	sptr<Entity> _owner = _comp.GetOwner().lock();

	if(_owner)
		onKillZoneTriggered->Invoke(_owner->GetEntityType());
}
