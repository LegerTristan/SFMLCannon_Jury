#include "KillZone.h"
#include "CollisionComponent.h"

KillZone::KillZone(const sf::Vector2f _position) : 
	Entity(_position, 0),
	onKillZoneTriggered(std::make_unique<Action<const EEntityType&>>(nullptr))
{
	sf::Texture _text = sf::Texture();
	_text.create(10, 10);
	setTexture(_text);
}

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
