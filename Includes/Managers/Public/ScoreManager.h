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
	~ScoreManager() =  default;
#pragma endregion

#pragma region Getters
	inline Action<const int&>& OnScoreUpdated() { return *onScoreUpdated; }
#pragma endregion

#pragma region PublicMethods
	/// <summary>
	/// Register EntityManager in order to know when an entity is killed.
	/// </summary>
	/// <param name="entityManager">EntityManager to bind to.</param>
	void RegisterEntityManager(EntityManager& entityManager);

	void UnregisterEntityManager(EntityManager& entityManager);

	/// <summary>
	/// Register enemy's kill zone in order to know when an enemy reaches the left border of the screen.
	/// </summary>
	/// <param name="entityManager">Enemy's kill zone to bind to.</param>
	void RegisterKillZone(KillZone& killZone);

	void UnregisterKillZone(KillZone& killZone);

	/// <summary>
	/// Save current score in an external file if it is > to current high score.
	/// </summary>
	void SaveScoreBehavior();
#pragma endregion

private:

#pragma region Properties
	/// <summary>
	/// Delegate invoked when the score is updated through UpdateScoreBehavior.
	/// </summary>
	uptr<Action<const int&>> onScoreUpdated;

	/// <summary>
	/// Stock all score gained when defeating a type of entity.
	/// </summary>
	std::unordered_map<EEntityType, int> scorePerEntityType;

	/// <summary>
	/// Previous high score registered in the game.
	/// </summary>
	int highScore;

	/// <summary>
	/// Score made in the current level.
	/// </summary>
	int score;
#pragma endregion

#pragma region PrivateMethods
	/// <summary>
	/// Call UpdateScoreBehavior with scalar to 1.
	/// </summary>
	/// <param name="type">Type of the entity killed</param>
	void AddScore(const EEntityType& type);

	/// <summary>
	/// Call UpdateScoreBehavior with scalar to -1.
	/// </summary>
	/// <param name="type">Type of the entity killed</param>
	void DecreaseScore(const EEntityType& type);

	/// <summary>
	/// Update the current score if the entity killed provides a score.
	/// The gained score is multiplied with a scalar (default value is 1)
	/// </summary>
	/// <param name="type">Type of the entity killed</param>
	/// <param name="scalar">Modifier to apply to the gained score.</param>
	void UpdateScoreBehavior(const EEntityType& type, float scalar = 1);
#pragma endregion
};

