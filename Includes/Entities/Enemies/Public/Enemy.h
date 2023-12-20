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
	Enemy(const sf::Vector2f position, const sf::Texture& enemyTexture, const float& xp, const unsigned int& givenScore);
	virtual ~Enemy() = default;
#pragma endregion

	// GETTERS

	inline virtual EEntityType GetEntityType() const = 0;
	inline float GetXP() const { return xp; }
	inline unsigned int GetScore() const { return givenScore; }

	virtual void Enable() override;

	/// <summary>
	/// Give XP to player and score for scoreManager and call Die() function.
	/// </summary>
	virtual void KillByPlayer();

	/// <summary>
	/// Reduce player's life by 1 and call Die() function.
	/// </summary>
	virtual void KillByGame();

	virtual void Disable() override;

protected:

	/// <summary>
	/// Quantity of XP this enemy will give to the player.
	/// </summary>
	float xp;

	/// <summary>
	/// Quantity of score this enemy will give to the player.
	/// </summary>
	unsigned int givenScore;

	virtual void OnCollide(const CollisionComponent& _comp) override;
};