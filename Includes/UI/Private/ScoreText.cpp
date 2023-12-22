#include "ScoreText.h"
#include "Utilities.h"
#include "Game.h"

ScoreText::ScoreText(sf::Font& _font, const sf::Color& _color, const sf::Vector2f& _pos, bool _displayPrefix) :
	displayPrefix(_displayPrefix)
{
	setFillColor(_color);
	setCharacterSize(SCORE_CHARACTER_SIZE);
	setOrigin(Utilities::GetCenter(*this));
	setPosition(_pos);
	setFont(_font);

	UpdateText(0);
	Game::GetInstance()->GetScoreManager().OnScoreUpdated().AddDynamic(this, &ScoreText::UpdateText);
}

ScoreText::~ScoreText()
{
	Game* _game = Game::GetInstance();

	if(_game && _game->IsGameValid())
		_game->GetScoreManager().OnScoreUpdated().RemoveDynamic(this, &ScoreText::UpdateText);
}

void ScoreText::Draw(sf::RenderWindow& _window) const
{
	_window.draw(*this);
}

void ScoreText::UpdateText(const int& _score)
{
	const char* _prefix = displayPrefix ? "SCORE : " : "";
	setString(_prefix + std::to_string(_score) + "pts");
}
