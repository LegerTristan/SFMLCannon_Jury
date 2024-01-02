#pragma once

#include <SFML/Graphics.hpp>
#include "InputRotationComponent.h"
#include "CannonShootComponent.h"
#include "Constants.h"
#include "CannonBall.h"

class Gauge;
class EntityManager;

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using wptr = std::weak_ptr<T>;

/// <summary>
/// A cannon is a launcher of a CannonBalls, it aims and charges to shoot a CannonBall.
/// It is controlled by the player via inputs.
/// Inherit from Sprite class of SFML graphics lib
/// </summary>
class Cannon : public sf::Sprite
{
public:

#pragma region Constructor/Destructor
	Cannon() = delete;
	Cannon(wptr<EntityManager> manager, sf::Vector2f position);
	~Cannon() = default;
#pragma endregion
	
	inline bool IsCannonValid() const { return movingPartSprite != nullptr && cannonRotComp != nullptr && 
		cannonShootComp != nullptr && cannonGauge != nullptr;}

	void Update(const float& dt);

	void Draw(sf::RenderWindow& window);

	void Disable();

private:

#pragma region Properties
	uptr<InputRotationComponent> cannonRotComp;

	uptr<CannonShootComponent> cannonShootComp;

	/// <summary>
	/// Represents the shoot component's load power in the UI
	/// </summary>
	uptr<Gauge> cannonGauge;

	/// <summary>
	/// Sprite of moving part of the cannon
	/// </summary>
	sptr<sf::Sprite> movingPartSprite;

	/// <summary>
	/// Keeps a reference to the entityMaanger in order to call it for creating a new cannon ball.
	/// </summary>
	sptr<EntityManager> entityManager;
#pragma endregion

	void InitSprite(Sprite& sprite, const std::string& path, const sf::Vector2f& pos);

	/// <summary>
	/// Calls when the shoort componentt's onFire delegate is invoked.
	/// Computes the initial position and velocity of the cannon ball, and give it to the entityManager
	/// in order to spawn the entity.
	/// </summary>
	/// <param name="power">Fire power of the shoot</param>
	void LaunchCannonBall(const float& power);
};
