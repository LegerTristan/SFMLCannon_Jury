#pragma once

#include "LifeBar.h"
#include "Gauge.h"
#include "IDelegate.h"

class KillZone;

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Contains all the informations tied to the player such as HP, level, and current upgrades.
/// </summary>
class Player 
{
public:

#pragma region Constructor/Destructor
	Player();
	~Player() = default;
#pragma endregion

	inline Action<const int&>& OnPlayerLifeDecreased() { return *onPlayerLifeDecreased; }
	inline Action<>& OnPlayerLose() { return *onPlayerLose; }
	inline LifeBar& GetLifeBar() const { return *lifeBar; }

	/// <summary>
	/// Draw player's informations on the screen like lifebar, level gauge etc.
	/// </summary>
	/// <param name="window">Game window</param>
	void Draw(sf::RenderWindow& window);

	void BindToEnemiesKillZone(KillZone& _killZone);

private:

	uptr<Action<const int&>> onPlayerLifeDecreased;

	uptr<Action<>> onPlayerLose;

	/// <summary>
	/// Player's lifebar
	/// </summary>
	uptr<LifeBar> lifeBar;

	/// <summary>
	/// Current player's life
	/// </summary>
	int life;

	void DecrementHP();
};

