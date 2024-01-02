#include "DefenceHUD.h"
#include "Utilities.h"
#include "Game.h"

DefenceHUD::DefenceHUD() :
	HUD(),
	timerText(font, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, HUD_Y_OFFSET)),
	scoreText(font, sf::Color::Black,
		sf::Vector2f((WINDOW_WIDTH + 250) / 2, HUD_Y_OFFSET), false)
{
	TextureManager& _textureManager = Game::GetInstance()->GetTextureManager();

	// Set sprite's texture and settings
	const sf::Texture& _temp = _textureManager.GetTexture(CLOUD_IMAGE_PATH);
	cloudBackground.setTexture(_temp);
	cloudBackground.setOrigin(Utilities::GetCenter(_temp));
	cloudBackground.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, -HUD_Y_OFFSET));
}

void DefenceHUD::Update(const float& _dt)
{
	timerText.Update(_dt);
}

void DefenceHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(cloudBackground);
	_window.draw(timerText);
	scoreText.Draw(_window);
	timerText.Draw(_window);
}
