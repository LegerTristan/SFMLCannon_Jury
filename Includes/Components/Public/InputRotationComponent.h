#pragma once

#include <SFML/Graphics.hpp>

template<typename T>
using sptr = std::shared_ptr<T>;

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Component that rotates a Sprite based on two inputs handled by the InputManager.
/// It rotates the sprite smoothly meaning that the rotation is updated every frame while one of the keys is pressed.
/// Component can be disabled through Disable method.
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
	~InputRotationComponent() = default;
#pragma endregion

	void Update(const float& dt);

	void Disable();

private:

#pragma region Properties
	sptr<sf::Sprite> spriteToRotate;

	/// <summary>
	/// Up keys and down keys used respectively for up rotation and down rotation
	/// </summary>
	Scancode rotKeyUp,
			 rotKeyDown;

	float rotationSpeed,
		  minRotation,
		  maxRotation;

	bool isRotationIncreased = false,
		 isRotationDecreased = false,
		 isComponentEnabled = true;
#pragma endregion

#pragma region PrivateMethods
	inline void EnableRotationIncreased() { isRotationIncreased = true; }
	inline void DisableRotationIncreased() { isRotationIncreased = false; }

	inline void EnableRotationDecreased() { isRotationDecreased = true; }
	inline void DisableRotationDecreased() { isRotationDecreased = false; }

	inline void SetInputEnabled(const bool& _enabled) { isComponentEnabled = _enabled; }

	void UpdateSpriteRotation(const float& _scalar, const bool& _condition);
#pragma endregion
};