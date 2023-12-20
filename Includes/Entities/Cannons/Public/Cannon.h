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
/// Inherit from Sprite class of SFMLs graphics lib
/// </summary>
class Cannon : public sf::Sprite
{
	const std::string STATIC_PART_PATH = "Assets/Textures/Cannon_StaticPart.png",
					  MOVING_PART_PATH = "Assets/Textures/Cannon_MovingPart.png";

public:

	// CONSTRUCTOR & DESTRUCTOR

	Cannon() = delete;
	Cannon(wptr<EntityManager> manager, sf::Vector2f position);
	~Cannon() = default;

	// GETTERS & SETTER

	inline wptr<sf::Sprite> GetMovingPartSprite() const { return movingPartSprite; }
	inline bool IsCannonValid() const { return movingPartSprite != nullptr && cannonRotComp != nullptr && 
		cannonShootComp != nullptr && cannonGauge != nullptr;}

	void Update(const float& dt);

	/// <summary>
	/// Update fire power if it is currently charging
	/// Update cannon display as well as his fire power's gauge
	/// </summary>
	/// <param name="window"></param>
	void Draw(sf::RenderWindow& window);

private:

	uptr<InputRotationComponent> cannonRotComp;

	uptr<CannonShootComponent> cannonShootComp;

	uptr<Gauge> cannonGauge;

	/// <summary>
	/// Sprite of moving part of the cannon
	/// </summary>
	sptr<sf::Sprite> movingPartSprite;

	sptr<EntityManager> entityManager;

	void InitSprite(Sprite& sprite, const std::string& path, const sf::Vector2f& pos);

	void LaunchCannonBall(const float& power);
};
