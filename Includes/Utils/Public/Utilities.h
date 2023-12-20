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
#pragma endregion

#pragma region SFML UI
	inline static sf::Vector2f GetCenter(const sf::Texture& _texture)
	{
		return sf::Vector2f(_texture.getSize().x / 2.0f, _texture.getSize().y / 2.0f);
	}

	inline static sf::Vector2f GetCenter(const sf::Text& _text)
	{
		return sf::Vector2f(_text.getCharacterSize() / 2.0f, _text.getCharacterSize() / 2.0f);
	}
#pragma endregion

#pragma region TimeManagement
	inline static int ToMinutes(const int& _time)
	{
		return _time / MINUTES_PER_HOUR;
	}

	inline static int ToSeconds(const int& _time)
	{
		return _time % SECONDS_PER_MINUTE;
	}
#pragma endregion

#pragma region String

	inline static char* StringToCharArray(const std::string& _string)
	{
		char* _charArray = new char[_string.length() + 1];
		strcpy_s(_charArray, _string.length() + 1, _string.c_str());

		return _charArray;
	}
#pragma endregion

//#pragma region Containers
//	template<typename TItem>
//	inline static bool Contains(const std::vector<TItem&>& _items, const TItem& _searched)
//	{
//		for(auto& _item : _items)
//			if(_item == _searched)
//				return true;
//
//		return false;
//	}
//#pragma endregion
};