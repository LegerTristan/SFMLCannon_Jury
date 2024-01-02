#pragma once

#include <SFML/Graphics.hpp>

class ScoreManager;

template<typename T>
using sptr = std::shared_ptr<T>;

/// <summary>
/// Text that displays the current score of the player.
/// </summary>
class ScoreText : sf::Text
{
public:

#pragma region Constructors/Destructor
	ScoreText() = delete;
	ScoreText(sf::Font& font, const sf::Color& color, const sf::Vector2f& pos, bool displayPrefix = true);
	~ScoreText();
#pragma endregion

#pragma region Methods
	/// <summary>
	/// Inits bindings with ScoreManager instance and keeps a reference to it.
	/// </summary>
	/// <param name="scoreManager">Instance of ScoreManager to bind to.</param>
	void Init(sptr<ScoreManager> scoreManager);

	void Draw(sf::RenderWindow& window) const;
#pragma endregion

private:

#pragma region Properties
	/// <summary>
	/// Keeps a reference on the ScoreManager in order to handles binding with the OnScoreUpdated delegate.
	/// </summary>
	sptr<ScoreManager> scoreManager;

	bool displayPrefix = true;
#pragma endregion

	/// <summary>
	/// Displays the new score on the text.
	/// </summary>
	/// <param name="score">New score to display</param>
	void UpdateText(const int& score);
};

