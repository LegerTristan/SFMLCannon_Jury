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

#pragma region PublicMethods
	void RegisterCollisionComponent(CollisionComponent* _comp);

	void Update(const float& dt);

	void UnregisterCollisionComponent(CollisionComponent* _comp);

	/// <summary>
	/// Clear collision components vector.
	/// </summary>
	void ClearCollisions();
#pragma endregion
private:

#pragma region Properties
	/// <summary>
	/// Timer that handles collision refresh at a custom rate.
	/// </summary>
	uptr<TimerComponent<CollisionManager>> collisionTimer;

	/// <summary>
	/// Vector of collision components currently presents in the level.
	/// </summary>
	std::vector<CollisionComponent*> collisionComps;

	/// <summary>
	/// Rate of checking collisions. Used for reducing potential lags.
	/// </summary>
	float physicsCheckRate;
#pragma endregion

	/// <summary>
	/// Update all collision components of the game.
	/// </summary>
	void UpdateCollision();
};

