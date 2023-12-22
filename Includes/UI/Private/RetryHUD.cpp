#include "RetryHUD.h"
#include "Utilities.h"
#include "Game.h"

RetryHUD::RetryHUD() :
	HUD(),
	retryText(sf::Text()),
	scoreText(ScoreText(font, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3)))
{
	levelBackground.setColor(sf::Color(155, 155, 155, 255));

	retryText.setFillColor(sf::Color::Black);
	retryText.setCharacterSize(HUD_CHARACTER_SIZE);
	retryText.setOrigin(Utilities::GetCenter(retryText));
	retryText.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - retryText.getCharacterSize(), 
		(WINDOW_HEIGHT / 2) - retryText.getCharacterSize()));
	retryText.setFont(font);
	retryText.setString("YOU LOSE !\nPRESS F TO RETRY !");
}

void RetryHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(retryText);
	scoreText.Draw(_window);
}