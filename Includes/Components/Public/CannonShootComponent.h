#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "IDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

using Scancode = sf::Keyboard::Scan::Scancode;

class CannonShootComponent
{
public:
	CannonShootComponent() = delete;
	CannonShootComponent(Scancode fireKey, const float& loadSpeed);
	CannonShootComponent(Scancode fireKey, const float& loadSpeed, const float& minPower, const float& maxPower);
	~CannonShootComponent() = default;

	inline Action<const float&>& OnLoadUp() { return *onLoadUp; }
	inline Action<const float&>& OnFire() { return *onFire; }

	void Update(const float& dt);

	void Disable();

private:

	uptr<Action<const float&>> onLoadUp;
	uptr<Action<const float&>> onFire;

	Scancode fireKey;

	float loadSpeed,
		  minPower,
		  maxPower;

	float currentPower;

	bool isLoading = false,
		 isComponentEnabled = true;

	inline float GetPowerPercentage() const { return (currentPower - minPower) / (maxPower - minPower); }

	inline void StartLoad() { isLoading = true; }

	void Fire();
};

