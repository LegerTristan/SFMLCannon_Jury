#include <iostream>
#include <string>
#include "HUD.h"
#include "Constants.h"
#include "Game.h"

sf::Font* HUD::font = nullptr;

HUD::HUD()
{
	TextureManager& _textureManager = Game::GetInstance()->GetTextureManager();

	levelBackground.setTexture(_textureManager.GetTexture(BACKGROUND_FONT_PATH));

	// Set game's font
	font = new sf::Font();
	font->loadFromFile(GAME_FONT_PATH);
}

HUD::~HUD()
{
	if (!font)
		return;

	delete font;
	font = nullptr;
}

void HUD::Update(const float& _dt)
{
}

void HUD::Draw(sf::RenderWindow& _window) const
{
	_window.draw(levelBackground);
}