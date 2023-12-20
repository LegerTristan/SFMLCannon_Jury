#include <string>

#include "ScoreManager.h"
#include "HUD.h"
#include "Constants.h"

using namespace std;

ScoreManager::ScoreManager()
{
	mHighScore = mScore = 0;

	mScoreText.setCharacterSize(24);
	mScoreText.setFillColor(Color::Black);
	mScoreText.setOrigin(32, mScoreText.getCharacterSize() / 2);
	mScoreText.setPosition(WINDOW_WIDTH / 2 + SCORE_TEXT_POS.x, SCORE_TEXT_POS.y);
	mScoreText.setFont(*HUD::GetGameFont());
	mScoreText.setString(to_string(mScore) + "pts");
}

void ScoreManager::AddScore(const unsigned int& _toAdd)
{
	mScore += _toAdd;
	mScoreText.setString(to_string(mScore) + "pts");
}

void ScoreManager::DisplayFinalScore()
{
	mScoreText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mScoreText.setCharacterSize(TEXT_CHARACTER_SIZE);
	mScoreText.setString("Score : " + to_string(mScore) + "pts\n Press F to restart");
	mScoreText.setOrigin(100, mScoreText.getCharacterSize() / 2);
}

void ScoreManager::DrawScore(RenderWindow* _window) const
{
	_window->draw(mScoreText);
}
