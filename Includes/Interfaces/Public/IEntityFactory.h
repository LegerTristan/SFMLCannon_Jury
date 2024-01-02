#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

template<typename T>
using sptr = std::shared_ptr<T>;

class Entity;

/// <summary>
/// Interface class that implements the AbstractFactory pattern.
/// Give a method to create a new entity with a position and a velocity passed in parameters.
/// </summary>
class IEntityFactory
{
public:

	IEntityFactory() = default;
	virtual ~IEntityFactory() = default;

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) = 0;
};