#include "TextureManager.h"
#include <iostream>

sf::Texture& TextureManager::GetTexture(const std::string& _filePath)
{
    auto _iter = textures.find(_filePath);
    if (_iter != textures.end())
        return *_iter->second;
     
    std::unique_ptr<sf::Texture> _newTexture = std::make_unique<sf::Texture>();
    if (_newTexture->loadFromFile(_filePath))
    {
        auto& _refTexture = *_newTexture;
        textures[_filePath] = std::move(_newTexture);
        return _refTexture;
    }
    else
        throw std::runtime_error("Texture failed to load : " + _filePath);
}