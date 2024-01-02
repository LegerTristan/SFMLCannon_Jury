#pragma once

#include <string>
#include "EntityComponent.h"
#include "IDelegate.h"

/// <summary>
/// Type of the collision component.
/// Used to separate ball's collision from enemy's collision.
/// Works as a collision matrix.
/// </summary>
enum class ECollisionType
{
	BALL = 1,
	ENEMY = 2,
	KILL_ZONE = 4,
};

/// <summary>
/// Inherit from Component.
/// Gives a collision behavior to the entity.
/// </summary>
class CollisionComponent : public EntityComponent
{
public:

#pragma region Constructors/Destructor
	CollisionComponent() = delete;
	CollisionComponent(sptr<Entity> entity, const ECollisionType& type, const char* hitBoxPath, const char collisionMask);
	CollisionComponent(sptr<Entity> entity, const ECollisionType& type, const sf::Vector2f& size, const char collisionMask);
	~CollisionComponent() = default;
#pragma endregion

	inline Action<const CollisionComponent&>& OnCollide() const { return *onCollide; }
	inline virtual EEntityComponentType GetComponentType() const override { return EEntityComponentType::COLLISION; }

#pragma region PublicMethods
	virtual void UpdateComponent(const float& dt) override final;

	virtual void DrawComponent(sf::RenderWindow& _window) override final;

	void UpdateHitBoxPosition();

	/// <summary>
	/// Check if this component collide with another CollisionComponent passed in parameter.
	/// </summary>
	/// <param name="otherCollision">The other CollisionComponent to check if it collide with</param>
	void HandleCollision(const CollisionComponent* otherCollision) const;

	inline bool operator==(const CollisionComponent& _otherCollision) const
	{
		const sf::RectangleShape _otherHitbox = _otherCollision.hitBox;
		return collisionMask == _otherCollision.collisionMask && collisionType == _otherCollision.collisionType &&
			hitBox.getPosition() == _otherHitbox.getPosition() && hitBox.getSize() == _otherHitbox.getSize();
	}
#pragma endregion

private:

#pragma region Properties
	uptr<Action<const CollisionComponent&>> onCollide;

	/// <summary>
	/// Tag of the collision component
	/// </summary>
	ECollisionType collisionType;

	/// <summary>
	/// HitBox of the collision component
	/// </summary>
	sf::RectangleShape hitBox;

	const char collisionMask;
#pragma endregion

#pragma region PrivateMethods
	/// <summary>
	/// Call BindToCollisionManager and bind to owner's notifiers in order to handle binding logic.
	/// </summary>
	void InitBindings();

	void BindToCollisionManager();

	void UnbindFromCollisionManager(sptr<Entity> _owner);
#pragma endregion
};

