#include "Gauge.h"
#include "CannonShootComponent.h"

Gauge::Gauge(CannonShootComponent& _shootComp, sf::Vector2f _position, bool _isHorizontal) :
	gaugeEmptyFill(sf::RectangleShape()),
	gaugeFill(sf::RectangleShape()),
	gaugeBackground(sf::RectangleShape()),
	position(_position),
	size(sf::Vector2f(GAUGE_WIDTH, GAUGE_HEIGHT)),
	isHorizontal(_isHorizontal),
	isVisible(false)
{
	gaugeBackground.setPosition(_position);
	gaugeEmptyFill.setPosition(_position + TO_CENTER);

	gaugeFill.setFillColor(sf::Color::Red);
	gaugeBackground.setFillColor(sf::Color::Black);

	gaugeBackground.setSize(sf::Vector2f(size.x, size.y) + BACKGROUND_MARGIN);
	gaugeEmptyFill.setSize({ size.x, size.y });

	isHorizontal ? gaugeFill.setSize({ 0.0f, size.y }) : gaugeFill.setSize({ size.x, 0.0f });
	isHorizontal ? gaugeFill.setPosition(_position + TO_CENTER) : gaugeFill.setPosition(_position + VERTICAL_OFFSET);

	_shootComp.OnLoadUp().AddDynamic(this, &Gauge::Fill);
	_shootComp.OnFire().AddDynamic(this, &Gauge::ResetGauge);
}

Gauge::Gauge(CannonShootComponent& _shootComp, sf::Vector2f _position, sf::Vector2f _size, sf::Color _gaugeColor, bool _isHorizontal) :
	Gauge(_shootComp, _position, _isHorizontal)
{
	size = { _size.x, _size.y };
	gaugeFill.setFillColor(_gaugeColor);
}

void Gauge::Draw(sf::RenderWindow& _window) const
{
	if (!isVisible)
		return;

	_window.draw(gaugeBackground);
	_window.draw(gaugeEmptyFill);
	_window.draw(gaugeFill);
}

void Gauge::Fill(const float& _fillValue)
{
	const sf::Vector2f _newSize = isHorizontal ? sf::Vector2f(_fillValue * size.x, size.y) : sf::Vector2f(size.x, -_fillValue * size.y);

	gaugeFill.setSize(_newSize);
	isVisible = true;
}

void Gauge::ResetGauge(const float& power)
{
	Fill(0.0f);
	isVisible = false;
}
