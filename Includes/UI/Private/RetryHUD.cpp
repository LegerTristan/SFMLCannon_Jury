#include "RetryHUD.h"
#include "Utilities.h"

RetryHUD::RetryHUD() :
	HUD(),
	retryText(sf::Text()),
	scoreText(sf::Text())
{
	levelBackground.setColor(sf::Color(155, 155, 155, 255));

	retryText.setFillColor(sf::Color::Black);
	retryText.setCharacterSize(HUD_CHARACTER_SIZE);
	retryText.setOrigin(Utilities::GetCenter(retryText));
	retryText.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - retryText.getCharacterSize(), 
		(WINDOW_HEIGHT / 2) - retryText.getCharacterSize()));
	retryText.setFont(*font);
	retryText.setString("YOU LOSE !\nPRESS F TO RETRY !");


	scoreText.setFillColor(sf::Color::Black);
	scoreText.setCharacterSize(SCORE_CHARACTER_SIZE);
	scoreText.setOrigin(Utilities::GetCenter(scoreText));
	scoreText.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - scoreText.getCharacterSize(),
		(WINDOW_HEIGHT / 3) - scoreText.getCharacterSize()));
	scoreText.setFont(*font);
	scoreText.setString("SCORE : ");
}

void RetryHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(retryText);
	_window.draw(scoreText);
}
