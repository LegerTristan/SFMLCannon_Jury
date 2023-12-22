#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "EntityType.h"
#include "IEntityFactory.h"
#include "ObjectPool.h"
#include "IDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;

class Entity;

class EntityManager
{
public:

#pragma region Constructor/Destructor
	EntityManager();
	~EntityManager() = default;
#pragma endregion

	inline Action<const EEntityType&>& OnEntitySpawned() { return *onEntitySpawned; }
	inline Action<const EEntityType&>& OnEntityDisabled() { return *onEntityDisabled; }

	void Init();

	sptr<Entity> SpawnEntity(EEntityType _entityType, const sf::Vector2f& _pos, const sf::Vector2f& _velocity);

	/// <summary>
	/// Update all entities and give them reference to the game windows.
	/// </summary>
	/// <param name="window">Game window</param>
	void UpdateEntities(sf::RenderWindow& window, const float& dt);

	void DisableEntity(sptr<Entity> _entity);

	void DisableAllEntities();

private:

	std::map<EEntityType, std::pair<uptr<IEntityFactory>, uptr<ObjectPool>>> entityManagers;

	std::vector<sptr<Entity>> activeEntities;

	uptr<Action<const EEntityType&>> onEntitySpawned,
									 onEntityDisabled;

	sptr<Entity> RetrieveFromPool(EEntityType type, const sf::Vector2f& pos, const sf::Vector2f& velocity);

	sptr<Entity> CreateNewEntityFromFactory(EEntityType type, const sf::Vector2f& pos, const sf::Vector2f& velocity);
};

