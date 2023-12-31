#include <iostream>
#include <string>
#include "HUD.h"
#include "Constants.h"
#include "Game.h"

HUD::HUD() : 
	levelBackground(sf::Sprite()),
	font(sf::Font())
{
	TextureManager& _textureManager = Game::GetInstance()->GetTextureManager();
	levelBackground.setTexture(_textureManager.GetTexture(LEVEL_BACKGROUND_PATH));

	// Set game's font
	font.loadFromFile(GAME_FONT_PATH);
}

void HUD::Update(const float& _dt)
{
}

void HUD::Draw(sf::RenderWindow& _window) const
{
	_window.draw(levelBackground);
}