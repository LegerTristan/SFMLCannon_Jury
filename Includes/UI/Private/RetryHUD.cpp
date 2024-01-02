#include "RetryHUD.h"
#include "Utilities.h"
#include "Game.h"

RetryHUD::RetryHUD() :
	HUD(),
	retryText(sf::Text()),
	scoreText(sf::Text()),
	hScoreText(sf::Text())
{
	levelBackground.setColor(sf::Color(155, 155, 155, 255));

	Utilities::InitText(retryText, sf::Vector2f((WINDOW_WIDTH / 2) - retryText.getCharacterSize(),
		(WINDOW_HEIGHT / 2) - retryText.getCharacterSize()), font);

	Utilities::InitText(scoreText, sf::Vector2f((WINDOW_WIDTH / 2) - scoreText.getCharacterSize(),
		(WINDOW_HEIGHT / 3) - scoreText.getCharacterSize()), font);

	Utilities::InitText(hScoreText, sf::Vector2f((WINDOW_WIDTH / 2) - hScoreText.getCharacterSize(),
		(WINDOW_HEIGHT / 4) - hScoreText.getCharacterSize()), font);

	retryText.setString("YOU LOSE !\nPRESS F TO RETRY !");
}

void RetryHUD::Init()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	int _highScore = _game->GetIOManager().Read<int>(SCORE_SAVE_VALUE_NAME); 
	scoreText.setString("FINAL SCORE : " + std::to_string(_game->GetLatestScore()));
	hScoreText.setString("HIGHEST SCORE : " + std::to_string(_highScore));
}

void RetryHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(retryText);
	_window.draw(scoreText);
	_window.draw(hScoreText);
}