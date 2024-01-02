#pragma once

#include "Entity.h"

/// <summary>
/// Entity that adds a collision component at initialization and triggers a delegate when it collides with any type 
/// of collisions
/// </summary>
class KillZone : public Entity
{
public:

#pragma region Constructor/Destructor
	KillZone(const sf::Vector2f _position);
	~KillZone() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const { return EEntityType::NONE; }
	inline Action<const EEntityType&>& OnKillZoneTriggered() { return *onKillZoneTriggered; }

	void Init(const sf::Vector2f& _size);

protected:

	virtual void OnCollide(const CollisionComponent& comp) override;

	/// <summary>
	/// Delegate invoked when something collides with the KillZone.
	/// Give the type of entity that triggers the collision.
	/// </summary>
	uptr<Action<const EEntityType&>> onKillZoneTriggered;
};