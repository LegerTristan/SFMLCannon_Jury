#include "TimerText.h"
#include "Utilities.h"

TimerText::TimerText(sf::Font& _font, const sf::Color& _color, const sf::Vector2f& _pos) :
	timeIncrementTimer(std::make_unique<TimerComponent<TimerText>>(this, &TimerText::UpdateText, 1.0f, true)),
	currentGameTime(0)
{
	setFillColor(_color);
	setCharacterSize(HUD_CHARACTER_SIZE);
	setOrigin(Utilities::GetCenter(*this));
	setPosition(_pos - sf::Vector2f(getCharacterSize() / 2, 0.0f));
	setFont(_font);

	UpdateText();
	if (timeIncrementTimer)
		timeIncrementTimer->Start();
}

void TimerText::Update(const float& _dt)
{
	if(timeIncrementTimer)
		timeIncrementTimer->UpdateTimer(_dt);
}

void TimerText::Draw(sf::RenderWindow& _window) const
{
	_window.draw(*this);
}

void TimerText::UpdateText()
{
	currentGameTime++;
	int _minutes = Utilities::ToMinutes(currentGameTime),
		_seconds = Utilities::ToSeconds(currentGameTime);

	const char* _format = FORMAT_CHARACTER_TIMER.c_str();
	char* _buffer = (char*)malloc(sizeof(char) * NUMBER_CHARACTER_TIMER);
	snprintf(_buffer, NUMBER_CHARACTER_TIMER, _format, _minutes, _seconds);

	setString(_buffer);
	free(_buffer);
}
