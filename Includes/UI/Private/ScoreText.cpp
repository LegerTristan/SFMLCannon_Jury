#include "ScoreText.h"
#include "Utilities.h"
#include "Game.h"
#include "ScoreManager.h"

ScoreText::ScoreText(sf::Font& _font, const sf::Color& _color, const sf::Vector2f& _pos, bool _displayPrefix) :
	displayPrefix(_displayPrefix)
{
	setFillColor(_color);
	setCharacterSize(SCORE_CHARACTER_SIZE);
	setOrigin(Utilities::GetCenter(*this));
	setPosition(_pos);
	setFont(_font);

	UpdateText(0);
}

ScoreText::~ScoreText()
{
	if(scoreManager)
		scoreManager->OnScoreUpdated().RemoveDynamic(this, &ScoreText::UpdateText);
}

void ScoreText::Init(sptr<ScoreManager> _scoreManager)
{
	scoreManager = _scoreManager;
	if (scoreManager)
		scoreManager->OnScoreUpdated().AddDynamic(this, &ScoreText::UpdateText);
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
