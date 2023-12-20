#pragma once

#include "Entity.h"

class KillZone : public Entity
{
public:

#pragma region Constructor/Destructor
	KillZone(const sf::Vector2f _position) : Entity(_position, 0), 
		onKillZoneTriggered(std::make_unique<Action<>>(nullptr))
	{
		sf::Texture _text = sf::Texture();
		_text.create(10, 10);
		setTexture(_text);
	}

	~KillZone() = default;
#pragma endregion

	inline virtual EEntityType GetEntityType() const { return EEntityType::NONE; }
	inline Action<>& OnKillZoneTriggered() { return *onKillZoneTriggered; }

	void Init(const sf::Vector2f& _size);

protected:

	virtual void OnCollide(const CollisionComponent& comp) override;

	uptr<Action<>> onKillZoneTriggered;
};