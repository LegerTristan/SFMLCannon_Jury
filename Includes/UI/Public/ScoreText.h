#pragma once

#include <SFML/Graphics.hpp>

class ScoreText : sf::Text
{
public:

	ScoreText() = delete;
	ScoreText(sf::Font& font, const sf::Color& color, const sf::Vector2f& pos, bool displayPrefix = true);
	~ScoreText();

	void Draw(sf::RenderWindow& window) const;

	void UpdateText(const int& score);

private:

	bool displayPrefix = true;
};

