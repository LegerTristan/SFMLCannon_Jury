#include "CannonShootComponent.h"
#include "Game.h"
#include "LevelState.h"

CannonShootComponent::CannonShootComponent(Scancode _fireKey, const float& _loadSpeed) :
	loadSpeed(_loadSpeed),
	minPower(0.0f),
	currentPower(minPower),
	maxPower(10.0f),
	fireKey(_fireKey),
	onLoadUp(std::make_unique<Action<const float&>>(nullptr)),
	onFire(std::make_unique<Action<const float&>>(nullptr))
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.AddKeyEvent(sf::Event::KeyPressed, _fireKey, this, &CannonShootComponent::StartLoad);
	_inputManager.AddKeyEvent(sf::Event::KeyReleased, _fireKey, this, &CannonShootComponent::Fire);
}

CannonShootComponent::CannonShootComponent(Scancode _fireKey, const float& _loadSpeed,
	const float& _minPower, const float& _maxPower) : 
	CannonShootComponent(_fireKey, _loadSpeed)
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

		onLoadUp->Invoke(GetPowerPercentage());
	}
}

void CannonShootComponent::Fire()
{
	onFire->Invoke(currentPower);
	isLoading = false;
	currentPower = minPower;
}

void CannonShootComponent::Disable()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.RemoveKeyEvent(sf::Event::KeyPressed, fireKey, this, &CannonShootComponent::StartLoad);
	_inputManager.RemoveKeyEvent(sf::Event::KeyReleased, fireKey, this, &CannonShootComponent::Fire);
}