#include <iostream>
#include "Cannon.h"
#include "Utilities.h"
#include "Game.h"
#include "LevelState.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "Gauge.h"

Cannon::Cannon(wptr<EntityManager> _manager, sf::Vector2f _position)
{
	if (_manager.expired())
		return;

	movingPartSprite = std::make_shared<Sprite>();

	// Set sprite and transform settings for each cannon's part.
	InitSprite(*this, STATIC_PART_PATH, _position);
	InitSprite(*movingPartSprite, MOVING_PART_PATH, _position + MOVING_PART_OFFSET);

	cannonRotComp = std::make_unique<InputRotationComponent>(movingPartSprite, sf::Keyboard::Scancode::Down,
		sf::Keyboard::Scancode::Up, DEFAULT_ROTATION_SPEED, MIN_CANNON_ROTATION, MAX_CANNON_ROTATION);

	cannonShootComp = std::make_unique<CannonShootComponent>(sf::Keyboard::Scancode::Space, DEFAULT_LOAD_SPEED,
		MIN_CANNON_FIRE_POWER, MAX_CANNON_FIRE_POWER);

	if (!cannonShootComp)
		return;

	cannonGauge = std::make_unique<Gauge>(*cannonShootComp, Vector2f(40.0f, 550.0f), false);
	entityManager = _manager.lock();
	cannonShootComp->OnFire().AddDynamic(this, &Cannon::LaunchCannonBall);
}

void Cannon::Update(const float& _dt)
{
	if(!IsCannonValid())
	return;

	cannonRotComp->Update(_dt);
	cannonShootComp->Update(_dt);
}

void Cannon::Draw(RenderWindow& _window)
{
	_window.draw(*movingPartSprite);		// Necessary to draw the cannon in this order
	_window.draw(*this);					// to have the moving part on the right Z index
	cannonGauge->Draw(_window);
}

void Cannon::Disable()
{
	cannonShootComp->Disable();
	cannonRotComp->Disable();
}

void Cannon::InitSprite(Sprite& _sprite, const std::string& _path, const sf::Vector2f& _pos)
{
	const Texture& _temp = Game::GetInstance()->GetTextureManager().GetTexture(_path);
	_sprite.setTexture(_temp, true);

	_sprite.setOrigin(Utilities::GetCenter(_temp));
	_sprite.setPosition(_pos);
	_sprite.setScale(DEFAULT_SCALE);
	_sprite.setRotation(DEFAULT_ANGLE);
}

void Cannon::LaunchCannonBall(const float& _power)
{
	const float _cosPos = cosf((movingPartSprite->getRotation() - ROTATION_OFFSET) * RADIAN_CONVERSION);
	const float _sinPos = sinf((movingPartSprite->getRotation() - ROTATION_OFFSET) * RADIAN_CONVERSION);
	const Vector2f _spawnPoint = movingPartSprite->getPosition() + Vector2f(_cosPos, _sinPos) * DIST_FROM_CANNON;
	sptr<Entity> _entity = entityManager->SpawnEntity(EEntityType::CANNON_BALL, _spawnPoint, 
		Vector2f(_cosPos, _sinPos) * _power);
}
