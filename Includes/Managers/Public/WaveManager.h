#pragma once

#include "TimerComponent.h"
#include "Constants.h"
#include "EntityManager.h"

/// <summary>
/// Handles enemy appearance rate and maximum number at the same time.
/// Defines also their spawn position.
/// </summary>
class WaveManager
{
public:

#pragma region Constructors/Destructor
	WaveManager() = delete;
	WaveManager(sptr<EntityManager> entityManager);
	~WaveManager() = default;
#pragma endregion

	void Update(const float& dt);

private:

#pragma region Properties
	/// <summary>
	/// Timer Component that handles appearance of the enemies
	/// </summary>
	uptr<TimerComponent<WaveManager>> enemiesSpawnTimeline;
	
	/// <summary>
	/// Reference to the EntityManager in order to call SpawnEntity for enemies entity type. 
	/// </summary>
	sptr<EntityManager> entityManager;

	/// <summary>
	/// Total enemy max number at the same time.
	/// </summary>
	unsigned int maxEnemyNbr;

	/// <summary>
	/// Curent enemies number present in the level.
	/// </summary>
	unsigned int currentEnemyNbr;
#pragma endregion

#pragma region PrivateMethods
	inline sf::Vector2f GetFloatEnemyRandomSpawnPosition()
	{
		return sf::Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X,
			(rand() % (int)SPAWN_FLOAT_ENEMY_OFFSET_Y_RANGE) + SPAWN_FLOAT_ENEMY_OFFSET_Y_MIN);
	}

	inline sf::Vector2f GetGroundEnemyRandomSpawnPosition()
	{
		return sf::Vector2f(WINDOW_WIDTH + SPAWN_ENEMY_OFFSET_X, WINDOW_HEIGHT - SPAWN_GROUND_ENEMY_OFFSET_Y);
	}

	/// <summary>
	/// Increment current enemies number present in the level.
	/// </summary>
	inline void IncreaseEnemyNbrBehavior(const EEntityType& type);

	/// <summary>
	/// Decrement current enemies number present in the level.
	/// </summary>
	inline void DecreaseEnemyNbrBehavior(const EEntityType& type);

	/// <summary>
	/// Spawn a new random enemy
	/// </summary>
	void SpawnEnemyBehavior();
#pragma endregion
};

