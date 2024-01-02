#pragma once

#include "LifeBar.h"
#include "Gauge.h"
#include "IDelegate.h"
#include "EntityType.h"

class KillZone;

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Contains all the informations tied to the player.
/// </summary>
class Player 
{
public:

#pragma region Constructor/Destructor
	Player();
	~Player() = default;
#pragma endregion

#pragma region Getters
	inline Action<const unsigned int&>& OnPlayerLifeDecreased() { return *onPlayerLifeDecreased; }
	inline Action<>& OnPlayerLose() { return *onPlayerLose; }
	inline LifeBar& GetLifeBar() const { return *lifeBar; }
#pragma endregion

	/// <summary>
	/// Draw player's informations on the screen.
	/// </summary>
	/// <param name="window">Game window</param>
	void Draw(sf::RenderWindow& window);

	/// <summary>
	/// Bind to enemies kill zone in order to decrement player life when a enemy reaches this killzone.
	/// </summary>
	/// <param name="_killZone">Killzone to bind</param>
	void BindToEnemiesKillZone(KillZone& _killZone);

private:

#pragma region Properties
	/// <summary>
	/// Delegate invoked when DecrementLife method is called, meaning that the player loses life.
	/// </summary>
	uptr<Action<const unsigned int&>> onPlayerLifeDecreased;

	/// <summary>
	/// Delegate invoked when player's life is <= 0.
	/// </summary>
	uptr<Action<>> onPlayerLose;

	/// <summary>
	/// Player's lifebar
	/// </summary>
	uptr<LifeBar> lifeBar;

	/// <summary>
	/// Current player's life
	/// </summary>
	unsigned int life;
#pragma endregion

	void DecrementHP(const EEntityType& type);
};

