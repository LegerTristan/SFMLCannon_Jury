#pragma once

#include <unordered_map>
#include "EntityType.h"
#include "IDelegate.h"

class EntityManager;
class KillZone;

/// <summary>
/// Handle score of the level.
/// </summary>
class ScoreManager
{
public:

#pragma region Constructor/Destructor
	ScoreManager();
	~ScoreManager() = default;
#pragma endregion

#pragma region Getters
	inline Action<const int&>& OnScoreUpdated() { return *onScoreUpdated; }
#pragma endregion

	void RegisterEntityManager(EntityManager& entityManager);

	void UnregisterEntityManager(EntityManager& entityManager);

	void RegisterKillZone(KillZone& killZone);

	void UnregisterKillZone(KillZone& killZone);

private:

	uptr<Action<const int&>> onScoreUpdated;

	std::unordered_map<EEntityType, int> scorePerEntityType;

	/// <summary>
	/// Previous high score registered in the game.
	/// </summary>
	int highScore;

	/// <summary>
	/// Score made in the current level.
	/// </summary>
	int score;

	void AddScore(const EEntityType& type);

	void DecreaseScore(const EEntityType& type);

	void UpdateScoreBehavior(const EEntityType& type, float scalar = 1);
};

