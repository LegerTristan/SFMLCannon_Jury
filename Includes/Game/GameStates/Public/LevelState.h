#pragma once

#include <vector>
#include "GameState.h"
#include "EntityManager.h"
#include "Cannon.h"
#include "ScoreManager.h"
#include "Player.h"
#include "WaveManager.h"

class KillZone;

/// <summary>
/// Game state that handles the level part of the game.
/// </summary>
class LevelState : public GameState
{
public:
#pragma region Constructor/Destructor
	LevelState();
	~LevelState() = default;
#pragma endregion

#pragma region GameStateMethods
	/// <summary>
	/// Inherited from GameState
	/// Initializes the kill zones and all necessary bindings between managers;
	/// </summary>
	void Init() override final;

	/// <summary>
	/// Main method call in the level loop.
	/// Call all Update and Draw methods of his managers.
	/// </summary>
	void Update(sf::RenderWindow& window, const float& dt) override final;

protected:

	/// <summary>
	/// Disable all managers and make unregisters if necessary.
	/// </summary>
	virtual void EndState() override final;
#pragma endregion

private:

#pragma region Properties

	sptr<EntityManager> entityManager;

	uptr<WaveManager> waveManager;

	uptr<Player> player;

	sptr<ScoreManager> scoreManager;

	sptr<Cannon> cannon;

#pragma region KillZones
	/// <summary>
	/// Rectangle shape that triggers when a cannon ball collide with it.
	/// Used for killing them.
	/// </summary>
	sptr<KillZone> cannonBallsKillZone;

	/// <summary>
	/// Rectangle shape that triggers when an enemy collide with it.
	/// Used for killing them.
	/// </summary>
	sptr<KillZone> enemiesKillZone;
#pragma endregion

	/// <summary>
	/// Condition to fulfilled to triggers EndState at the end of the next frame.
	/// </summary>
	bool endStateAtNextFrame = false;
#pragma endregion

	inline void PreparteEndState() { endStateAtNextFrame = true; }
};

