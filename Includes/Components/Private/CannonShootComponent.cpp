#include "CannonShootComponent.h"
#include "Game.h"
#include "LevelState.h"

CannonShootComponent::CannonShootComponent(Scancode _fireKey, const float& _loadSpeed)
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.BindKeyEvent(sf::Event::KeyPressed, _fireKey, this, &CannonShootComponent::StartLoad);
	_inputManager.BindKeyEvent(sf::Event::KeyReleased, _fireKey, this, &CannonShootComponent::Fire);
	loadSpeed = _loadSpeed;
	currentPower = minPower;
	onLoadUp = std::make_unique<Action<const float&>>(nullptr);
	onFire = std::make_unique<Action<const float&>>(nullptr);
}

CannonShootComponent::CannonShootComponent(Scancode _fireKey, const float& _loadSpeed,
	const float& _minPower, const float& _maxPower) : CannonShootComponent(_fireKey, _loadSpeed)
{
	minPower = _minPower;
	maxPower = _maxPower;
	currentPower = minPower;
}

void CannonShootComponent::Update(const float& _dt)
{
	if (!isComponentEnabled)
		return;

	if (isLoading)
	{
 		currentPower += loadSpeed * _dt;
		currentPower = currentPower > maxPower ? maxPower : currentPower;
		if (currentPower == maxPower)
			int i = 10;

		onLoadUp->Invoke(GetPowerPercentage());
	}
}

void CannonShootComponent::Fire()
{
	onFire->Invoke(currentPower);
	isLoading = false;
	currentPower = minPower;
}