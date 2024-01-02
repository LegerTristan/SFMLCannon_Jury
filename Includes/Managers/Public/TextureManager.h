#pragma once

#pragma once
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <string>

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Contains all textures that was at least loaded once.
/// Improves access to textures by saving them in a map.
/// </summary>
class TextureManager
{
public:

	/// <summary>
	/// Get a texture in the map if it is found, else load it from its path and save it.
	/// If the texture still doesn't exist (or is unreachable), then return a runtime error exception.
	/// </summary>
	/// <param name="filePath">Path of the texture to load</param>
	/// <returns>The texture loaded.</returns>
	sf::Texture& GetTexture(const std::string& filePath);

private:
	std::unordered_map<std::string, uptr<sf::Texture>> textures;
};