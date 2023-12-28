#pragma once

#include "MoveComponent.h"

/// <summary>
/// Inherit from Entity class.
/// It is a type of entity which the player needs to destroy before they make him lose his HP.
/// </summary>
class Enemy : public Entity
{
public:

#pragma region Constructors / Destructor
	Enemy() = delete;
	Enemy(const sf::Vector2f position, const sf::Texture& enemyTexture, const float& xp);
	virtual ~Enemy() = default;
#pragma endregion

	// GETTERS

	inline virtual EEntityType GetEntityType() const = 0;
	inline float GetXP() const { return xp; }

	virtual void Enable() override;

	virtual void Disable() override;

protected:

	/// <summary>
	/// Quantity of XP this enemy will give to the player.
	/// </summary>
	float xp;

	virtual void OnCollide(const CollisionComponent& _comp) override;
};