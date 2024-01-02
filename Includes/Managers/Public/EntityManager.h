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

/// <summary>
/// Manages all instances of Entity class present in the game.
/// This class works also as a mediator between the pair EntityFactory/ObjectPool of each entity's type 
/// and external class of the entity system.
/// </summary>
class EntityManager
{
public:

#pragma region Constructor/Destructor
	EntityManager();
	~EntityManager() = default;
#pragma endregion

	inline Action<const EEntityType&>& OnEntitySpawned() { return *onEntitySpawned; }
	inline Action<const EEntityType&>& OnEntityDisabled() { return *onEntityDisabled; }

	/// <summary>
	/// Retirieve a disabled entity or create a new one if it is necessary.
	/// Then, set his position and his velocity and call onEntitySpawned delegate.
	/// </summary>
	/// <param name="_entityType">Type of the entity</param>
	/// <param name="_pos">New position of the entity</param>
	/// <param name="_velocity">New velocity of the entity</param>
	/// <returns>An entity that was setup.</returns>
	sptr<Entity> SpawnEntity(EEntityType _entityType, const sf::Vector2f& _pos, const sf::Vector2f& _velocity);

	/// <summary>
	/// Update all entities and give them reference to the game windows.
	/// </summary>
	/// <param name="window">Game window</param>
	void UpdateEntities(sf::RenderWindow& window, const float& dt);

	/// <summary>
	/// Put an entity inside his object pooling and disable it, instantly calling onEntityDisabled delegate.
	/// </summary>
	/// <param name="_entity">Entity to disable</param>
	void DisableEntity(sptr<Entity> _entity);

	void DisableAllEntities();

private:

#pragma region Properties
	/// <summary>
	/// Pair of EntityFactory/ObjectPool for each type of entity, such as GroundEnemy and FloatEnemy.
	/// </summary>
	std::map<EEntityType, std::pair<uptr<IEntityFactory>, uptr<ObjectPool>>> entityManagers;

	/// <summary>
	/// Currently active entities
	/// </summary>
	std::vector<sptr<Entity>> activeEntities;

	/// <summary>
	/// Delegates that are invoked respectively when an entity is spawned, and when an entity is disabled.
	/// </summary>
	uptr<Action<const EEntityType&>> onEntitySpawned,
									 onEntityDisabled;
#pragma endregion

	sptr<Entity> RetrieveFromPool(EEntityType type, const sf::Vector2f& pos, const sf::Vector2f& velocity);

	sptr<Entity> CreateNewEntityFromFactory(EEntityType type, const sf::Vector2f& pos, const sf::Vector2f& velocity);
};

