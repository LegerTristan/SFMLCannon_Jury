#pragma once

#pragma once
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <string>

template<typename T>
using uptr = std::unique_ptr<T>;

class TextureManager
{

private:
	std::unordered_map<std::string, uptr<sf::Texture>> textures;

public:

	sf::Texture& GetTexture(const std::string& _filename);
};