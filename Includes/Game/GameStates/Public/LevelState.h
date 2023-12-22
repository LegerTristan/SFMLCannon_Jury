#pragma once

#include <vector>
#include "GameState.h"
#include "EntityManager.h"
#include "Cannon.h"
#include "Player.h"
#include "WaveManager.h"

class KillZone;

/// <summary>
/// Game class that handle all the necessary elements in order to make the game playable.
/// All of his features is divided between managers and entities, except the management of the entities.
/// </summary>
class LevelState : public GameState
{
public:
#pragma region Constructor/Destructor
	LevelState();
	~LevelState() = default;
#pragma endregion

	/// <summary>
	/// Inherited from GameState
	/// Initialize the time speed upgrade of wave manager and also the player, and the cannon.
	/// Finally, initialize the level's background sprite, 
	/// </summary>
	void Init() override final;

	/// <summary>
	/// Main method call in the level loop.
	/// Call all update methods of his managers and his entities.
	/// Also draw the level background.
	/// </summary>
	void Update(sf::RenderWindow& window, const float& dt) override final;

protected:

	virtual void EndState() override final;

private:

#pragma region Properties

	/// <summary>
	/// Vector of Entity, it contains all the entities of the current game.
	/// </summary>
	sptr<EntityManager> entityManager;

	/// <summary>
	/// Wave manager that handle all the features based on the wave appearance and the current spawn of enemy.
	/// </summary>
	uptr<WaveManager> waveManager;

	/// <summary>
	/// Contains all members variables that are binded to the player such as XP.
	/// </summary>
	uptr<Player> player;

	/// <summary>
	/// Cannon that the player control in order to launch cannonball.
	/// </summary>
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

	bool endStateAtNextFrame = false;
#pragma endregion

	inline void PreparteEndState() { endStateAtNextFrame = true; }
};

