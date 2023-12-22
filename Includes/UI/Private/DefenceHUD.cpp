#include "DefenceHUD.h"
#include "Utilities.h"
#include "Game.h"

DefenceHUD::DefenceHUD() :
	HUD(),
	timeTextTimer(std::make_unique<TimerComponent<DefenceHUD>>(this, &DefenceHUD::UpdateTimerText, 1.0f, true)),
	scoreText(ScoreText(font, sf::Color::Black,
		sf::Vector2f((WINDOW_WIDTH + 250) / 2, HUD_Y_OFFSET), false)),
	currentGameTime(0)
{
	TextureManager& _textureManager = Game::GetInstance()->GetTextureManager();

	// Set sprite's texture and settings
	const sf::Texture& _temp = _textureManager.GetTexture(CLOUD_IMAGE_PATH);
	cloundBackground.setTexture(_temp);
	cloundBackground.setOrigin(Utilities::GetCenter(_temp));
	cloundBackground.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, -HUD_Y_OFFSET));

	// Set timer's text
	timerText = Text();
	timerText.setFillColor(sf::Color::Black);
	timerText.setCharacterSize(HUD_CHARACTER_SIZE);
	timerText.setOrigin(Utilities::GetCenter(timerText));
	timerText.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (timerText.getCharacterSize() / 2), HUD_Y_OFFSET));
	timerText.setFont(font);

	UpdateTimerText();
	if (timeTextTimer)
		timeTextTimer->Start();
}

void DefenceHUD::Update(const float& _dt)
{
	if(timeTextTimer)
		timeTextTimer->UpdateTimer(_dt);
}

void DefenceHUD::UpdateTimerText()
{
	currentGameTime++;
	int _minutes = Utilities::ToMinutes(currentGameTime),
		_seconds = Utilities::ToSeconds(currentGameTime);

	char* _format = (char*)malloc(sizeof(char) * 6);
	snprintf(_format, 6, "%02d:%02d", _minutes, _seconds);

	timerText.setString(_format);
	free(_format);
}

void DefenceHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(cloundBackground);
	_window.draw(timerText);
	scoreText.Draw(_window);
}
