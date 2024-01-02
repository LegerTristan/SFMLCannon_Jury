 #pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Constants.h"

class CannonShootComponent;

/// <summary>
/// A progress bar binded to CannonShootComponent in order to displays the current fire power of the cannon.
/// </summary>
class Gauge
{
public:

#pragma region Constructors/Destructor
	Gauge() = delete;
	Gauge(CannonShootComponent& shootComp, sf::Vector2f position, bool isHorizontal);
	Gauge(CannonShootComponent& shootComp, sf::Vector2f position, sf::Vector2f size, sf::Color gaugeColor, bool isHorizontal);
	~Gauge() = default;
#pragma endregion

	/// <summary>
	/// Draw the gauge on the window
	/// </summary>
	/// <param name="window">Game window</param>
	void Draw(sf::RenderWindow& window) const;

private:

#pragma region Properties
	/// <summary>
	/// Sprite of the empty part of the gauge, its size never change.
	/// </summary>
	sf::RectangleShape gaugeEmptyFill;

	/// <summary>
	/// Sprite of the gauge value, its size is based on the current fill value of the gauge.
	/// </summary>
	sf::RectangleShape gaugeFill;

	/// <summary>
	/// Sprite of the background of the gauge.
	/// </summary>
	sf::RectangleShape gaugeBackground;

	/// <summary>
	/// Position of the gauge
	/// </summary>
	sf::Vector2f position;

	/// <summary>
	/// Size of the gauge
	/// </summary>
	sf::Vector2f size;

	/// <summary>
	/// Is the gauge horizontal or vertical
	/// </summary>
	bool isHorizontal;

	bool isVisible;
#pragma endregion

	/// <summary>
	/// Fill the gauge by updating the size of the gauge value's sprite.
	/// </summary>
	/// <param name="fillValue">New fill value of the gauge</param>
	void Fill(const float& fillValue);

	void ResetGauge(const float& power);
};

