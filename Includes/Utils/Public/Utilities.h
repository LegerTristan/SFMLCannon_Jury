#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

/// <summary>
/// Contains some utility function that are static and can be used anywhere
/// </summary>
class Utilities
{
public:

	Utilities() = delete;
	Utilities(const Utilities& _u) = delete;
	~Utilities() = delete;

#pragma region Maths
	/// <summary>
	/// Template function that takes a value, a min and a max.
	/// Clamp the value between the min and the max.
	/// </summary>
	/// <typeparam name="T">Type of the value, min and max</typeparam>
	/// <param name="value">Value to clamp</param>
	/// <param name="min">Minimum value</param>
	/// <param name="max">Maximum value</param>
	/// <returns>Return the value clamped between the min and the max</returns>
	template<typename T>
	inline static T Clamp(const T& _value, const T& _min, const T& _max)
	{
		if (_value < _min)
			return _min;
		if (_value > _max)
			return _max;

		return _value;
	}

	/// <summary>
	/// Compute a linear interpolation between a min and a max.
	/// </summary>
	/// <typeparam name="T">Type of the values used in the linear interpolation</typeparam>
	/// <param name="_min">Min value of the linear interpolation</param>
	/// <param name="_max">Max value of the linear interpolation</param>
	/// <param name="_alpha">Value between 0 and 1 that handles the result's variation.</param>
	/// <returns>The linear interpolation result</returns>
	template<typename T>
	inline static T Lerp(const T& _min, const T& _max, const T& _alpha)
	{
		return _min + (_max - _min) * _alpha;
	}
#pragma endregion

#pragma region SFML UI

	/// <summary>
	/// Initializes a text by setting common values such as position and color.
	/// </summary>
	/// <param name="_text">Text to initializes.</param>
	/// <param name="_pos">Position of the text</param>
	/// <param name="_font">Font to apply on the text</param>
	inline static void InitText(sf::Text& _text, const sf::Vector2f& _pos, const sf::Font& _font)
	{
		_text.setFillColor(sf::Color::Black);
		_text.setCharacterSize(HUD_CHARACTER_SIZE);
		_text.setOrigin(Utilities::GetCenter(_text));
		_text.setPosition(_pos);
		_text.setFont(_font);
	}

	/// <summary>
	/// Get the center of a texture
	/// </summary>
	/// <param name="_texture">Texture to get the center.</param>
	/// <returns>Center of the texture</returns>
	inline static sf::Vector2f GetCenter(const sf::Texture& _texture)
	{
		return sf::Vector2f(_texture.getSize().x / 2.0f, _texture.getSize().y / 2.0f);
	}

	/// <summary>
	/// Get the center of a text
	/// </summary>
	/// <param name="_texture">Text to get the center.</param>
	/// <returns>Center of the text</returns>
	inline static sf::Vector2f GetCenter(const sf::Text& _text)
	{
		return sf::Vector2f(_text.getCharacterSize() / 2.0f, _text.getCharacterSize() / 2.0f);
	}
#pragma endregion

#pragma region TimeManagement
	/// <summary>
	/// Convert a time into minutes.
	/// </summary>
	/// <param name="_time">Time to convert</param>
	/// <returns>Given time as minutes.</returns>
	inline static int ToMinutes(const int& _time)
	{
		return _time / MINUTES_PER_HOUR;
	}

	/// <summary>
	/// Convert a time into seconds.
	/// </summary>
	/// <param name="_time">Time to convert</param>
	/// <returns>Given time as seconds.</returns>
	inline static int ToSeconds(const int& _time)
	{
		return _time % SECONDS_PER_MINUTE;
	}
#pragma endregion
};