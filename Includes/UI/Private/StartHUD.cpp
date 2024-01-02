#include "StartHUD.h"
#include "Utilities.h"

StartHUD::StartHUD() :
	HUD(),
	startText(sf::Text()),
	controlsText(sf::Text()),
	goalText(sf::Text()),
	startTextScaleEffect(this, &StartHUD::UpdateStartTextScale, 1.0f, MAX_SCALE_EFFECT, MIN_SCALE_EFFECT, true, true)
{
	levelBackground.setColor(sf::Color(155, 155, 155, 255));

	Utilities::InitText(startText, sf::Vector2f((WINDOW_WIDTH / 3) - startText.getCharacterSize(),
		(WINDOW_HEIGHT / 3) - startText.getCharacterSize()), font);

	Utilities::InitText(controlsText, sf::Vector2f((WINDOW_WIDTH + CONTROLS_X_OFFSET) - controlsText.getCharacterSize(),
		(WINDOW_HEIGHT / 2) - controlsText.getCharacterSize()), font);

	Utilities::InitText(goalText, sf::Vector2f((WINDOW_WIDTH / 5) - goalText.getCharacterSize(),
		GOAL_Y_OFFSET - goalText.getCharacterSize()), font);

	startText.setString("PRESS ENTER TO START THE GAME !");
	controlsText.setString("CONTROLS :\n\tUP/DOWN : ORIENT CANNON\n\tSPACE (MAINTAIN) : LOAD CANNON\n\t SPACE (RELEASED) : FIRE");
	goalText.setString("FEND OFF AS MANY ENEMIES AS YOU CAN WITH YOUR CANNON !");
	startTextScaleEffect.Start();
}

void StartHUD::Update(const float& _dt)
{
	HUD::Update(_dt);
	startTextScaleEffect.Update(_dt);
}

void StartHUD::Draw(sf::RenderWindow& _window) const
{
	HUD::Draw(_window);
	_window.draw(startText);
	_window.draw(controlsText);
	_window.draw(goalText);
}

void StartHUD::UpdateStartTextScale(const float& _uniformScale)
{
	startText.setScale(_uniformScale, _uniformScale);
}