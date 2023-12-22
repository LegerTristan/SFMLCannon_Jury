#pragma once

#include "HUD.h"
#include "ScoreText.h"

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

	ScoreText scoreText;

	void UpdateScoreText(const unsigned int& _score);
};

