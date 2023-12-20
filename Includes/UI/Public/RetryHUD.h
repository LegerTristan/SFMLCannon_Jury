#pragma once

#include "HUD.h"

class RetryHUD : public HUD
{
public:

#pragma region Constructor/Destructor
	RetryHUD();
	~RetryHUD() = default;
#pragma endregion

	virtual void Draw(sf::RenderWindow& window) const override final;

private:

	sf::Text retryText;

	sf::Text scoreText;
};

