#pragma once

#include "TimerComponent.h"
#include "Constants.h"
#include "EntityManager.h"

/// <summary>
/// Manager that handle all things in connection with the spawn of enemies such as mas spawn, or waves.
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
	/// Timeline Component that handles appearance of the wave
	/// </summary>
	uptr<TimerComponent<WaveManager>> enemiesSpawnTimeline;
	
	/// <summary>
	/// Manager of the entities
	/// </summary>
	sptr<EntityManager> entityManager;

	/// <summary>
	/// Total enemy max number at the same time. This member is not modified by the flow of time.
	/// </summary>
	unsigned int enemyMaxNbr;

	/// <summary>
	/// Current enemy max number at the same time. This member is modified by the flow of time.
	/// </summary>
	unsigned int enemyMaxNbrIncrement;

	/// <summary>
	/// Curent enemies number present if the level.
	/// </summary>
	unsigned int currentEnemiesNbr;
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

