#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "ComponentType.h"

class Entity;

template<typename T>
using sptr = std::shared_ptr<T>;

template<typename T>
using wptr = std::weak_ptr<T>;

/// <summary>
/// A class that needs an entity in order to work.
/// Add a specific behavior to an entity.
/// </summary>
class EntityComponent
{
public:
#pragma region Constructors/Destructors
	EntityComponent() = delete;
	EntityComponent(wptr<Entity> _entity) : owner(_entity) {}
	virtual ~EntityComponent() = default;
#pragma endregion

	inline virtual EEntityComponentType GetComponentType() const = 0;
	inline wptr<Entity> GetOwner() const { return owner; }

	inline virtual void UpdateComponent(const float& dt) {}

	inline virtual void DrawComponent(sf::RenderWindow& _window) {}

protected:

	/// <summary>
	/// Owner of the component
	/// </summary>
	wptr<Entity> owner;
};

