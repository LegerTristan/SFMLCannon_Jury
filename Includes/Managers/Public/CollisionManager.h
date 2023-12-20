#pragma once

#include <vector>
#include "CollisionComponent.h"
#include "TimerComponent.h"

/// <summary>
/// Manager that handle all things in connection with collisions.
/// </summary>
class CollisionManager
{
public:

#pragma region Constructor/Destructor
	CollisionManager();
	~CollisionManager() = default;
#pragma endregion

	void RegisterCollisionComponent(CollisionComponent* _comp);

	void Update(const float& dt);

	void UnregisterCollisionComponent(CollisionComponent* _comp);

	void ClearCollisions();

private:

	uptr<TimerComponent<CollisionManager>> physicsTimer;

	std::vector<CollisionComponent*> collisionComps;

	/// <summary>
	/// Rate of checking collisions. Used for reducing potential lags.
	/// </summary>
	float physicsCheckRate;

	/// <summary>
	/// Update all collision components of the game.
	/// </summary>
	void UpdateCollision();
};

