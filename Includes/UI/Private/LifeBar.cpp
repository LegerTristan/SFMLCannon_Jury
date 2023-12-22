#include "LifeBar.h"
#include "Game.h"
#include "Player.h"
#include "Utilities.h"

LifeBar::LifeBar(sf::Vector2f _position, const int& _lifeQty) :
	position(_position),
	qtyToDraw(_lifeQty)
{
	// Set heart's texture and sprites of life bar.
	sf::Texture& _texture = Game::GetInstance()->GetTextureManager().GetTexture(HEART_TEXTURE_PATH);

	for (unsigned int i = 0; i < qtyToDraw; ++i)
	{
		sf::Sprite _heart = sf::Sprite();
		_heart.setTexture(_texture);
		_heart.setOrigin(Utilities::GetCenter(_texture));
		_heart.setPosition(sf::Vector2f(position.x + i * SPACE_BETWEEN_LIFE, position.y));
		_heart.setScale(HEART_SPRITE_SCALE);
		hearts.push_back(_heart);
	}
}

void LifeBar::BindToPlayerLife(Player& _player)
{
	_player.OnPlayerLifeDecreased().AddDynamic(this, &LifeBar::UpdateQtyToDraw);
}

void LifeBar::Draw(sf::RenderWindow& _window)
{
	for (size_t i = 0; i < hearts.size() && i < qtyToDraw; ++i)
		_window.draw(hearts[i]);
}