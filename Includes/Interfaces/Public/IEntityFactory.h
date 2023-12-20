#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

template<typename T>
using sptr = std::shared_ptr<T>;

class Entity;

class IEntityFactory
{
public:

	IEntityFactory() {};
	~IEntityFactory() {};

	virtual sptr<Entity> CreateEntity(const sf::Vector2f& _pos, const sf::Vector2f& _velocity) = 0;
};