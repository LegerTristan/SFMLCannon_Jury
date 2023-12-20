#pragma once

#include <SFML/Graphics.hpp>

template<typename T>
using sptr = std::shared_ptr<T>;

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Component that rotates a Sprite based on two inputs handled by the InputManager.
/// It rotates the sprite smoothly meaning that the rotation is updated every frame while one of the keys is pressed.
/// </summary>
class InputRotationComponent
{
public:
#pragma region Constructors/Destructor
	InputRotationComponent() = delete;
	InputRotationComponent(sptr<sf::Sprite> sprite, Scancode increaseRotKey, Scancode decreaseRotKey,
		const float& rotSpeed);
	InputRotationComponent(sptr<sf::Sprite> sprite, Scancode increaseRotKey, Scancode decreaseRotKey, const float& rotSpeed,
		const float& minRot, const float& maxRot);
#pragma endregion

	void Update(const float& dt);

private:

#pragma region Properties
	sptr<sf::Sprite> spriteToRotate;

	float rotationSpeed = 1.0f,
		minRotation = 0.0f,
		maxRotation = 180.0f;

	bool isRotationIncreased = false,
		 isRotationDecreased = false,
		 isComponentEnabled = true;
#pragma endregion

#pragma region Methods
	inline void EnableRotationIncreased() { isRotationIncreased = true; }
	inline void DisableRotationIncreased() { isRotationIncreased = false; }

	inline void EnableRotationDecreased() { isRotationDecreased = true; }
	inline void DisableRotationDecreased() { isRotationDecreased = false; }

	inline void SetInputEnabled(const bool& _enabled) { isComponentEnabled = _enabled; }

	void UpdateSpriteRotation(const float& _scalar, const bool& _condition);
#pragma endregion
};