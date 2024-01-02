#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "IDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Contains shoot logic of the cannon.
/// Bind an input to the InputManager in order to load and fire the ball.
/// </summary>
class CannonShootComponent
{
public:
#pragma region Constructors/Destructor
	CannonShootComponent() = delete;
	CannonShootComponent(Scancode fireKey, const float& loadSpeed);
	CannonShootComponent(Scancode fireKey, const float& loadSpeed, const float& minPower, const float& maxPower);
	~CannonShootComponent() = default;
#pragma endregion

	inline Action<const float&>& OnLoadUp() { return *onLoadUp; }
	inline Action<const float&>& OnFire() { return *onFire; }

	void Update(const float& dt);

	void Disable();

private:

#pragma region Properties
	/// <summary>
	/// Delegate triggered when the cannon is loading up.
	/// </summary>
	uptr<Action<const float&>> onLoadUp;

	/// <summary>
	/// Delegate triggered when the cannon fires.
	/// </summary>
	uptr<Action<const float&>> onFire;

	Scancode fireKey;

	float loadSpeed,
		  minPower,
		  maxPower;

	/// <summary>
	/// Current load power of the cannon.
	/// Clamped between min and maxPower.
	/// </summary>
	float currentPower;

	bool isLoading = false,
		 isComponentEnabled = true;
#pragma endregion

#pragma region PrivateMethods
	inline float GetPowerPercentage() const { return (currentPower - minPower) / (maxPower - minPower); }

	inline void StartLoad() { isLoading = true; }

	void Fire();
#pragma endregion
};

