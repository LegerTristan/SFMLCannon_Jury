#include "InputRotationComponent.h"
#include "Game.h"
#include "Utilities.h"

InputRotationComponent::InputRotationComponent(sptr<sf::Sprite> _sprite, Scancode _increaseRotKey, Scancode _decreaseRotKey,
	const float& _rotSpeed)
{
	spriteToRotate = _sprite;
	rotationSpeed = _rotSpeed;

	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.BindKeyEvent(sf::Event::KeyPressed, _increaseRotKey, this, &InputRotationComponent::EnableRotationIncreased);
	_inputManager.BindKeyEvent(sf::Event::KeyPressed, _decreaseRotKey, this, &InputRotationComponent::EnableRotationDecreased);

	_inputManager.BindKeyEvent(sf::Event::KeyReleased, _increaseRotKey, this, &InputRotationComponent::DisableRotationIncreased);
	_inputManager.BindKeyEvent(sf::Event::KeyReleased, _decreaseRotKey, this, &InputRotationComponent::DisableRotationDecreased);
}

InputRotationComponent::InputRotationComponent(sptr<sf::Sprite> _sprite, Scancode _increaseRotKey, Scancode _decreaseRotKey,
	const float& _rotSpeed, const float& _minRot, const float& _maxRot) :
	InputRotationComponent(_sprite, _increaseRotKey, _decreaseRotKey, _rotSpeed)
{
	minRotation = _minRot;
	maxRotation = _maxRot;
}

void InputRotationComponent::Update(const float& _dt)
{
	if (!isComponentEnabled || !spriteToRotate)
		return;

	UpdateSpriteRotation(rotationSpeed * _dt, isRotationIncreased);
	UpdateSpriteRotation(-rotationSpeed * _dt, isRotationDecreased);
}

void InputRotationComponent::UpdateSpriteRotation(const float& _scalar, const bool& _condition)
{
	if (!_condition)
		return;
	
	spriteToRotate->rotate(_scalar);
	float _currentRot = spriteToRotate->getRotation();
	spriteToRotate->setRotation(Utilities::Clamp(_currentRot, minRotation, maxRotation));
}