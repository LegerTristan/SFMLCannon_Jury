#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "EntityType.h"
#include "EntityComponent.h"
#include "IDelegate.h"
#include "IPoolItem.h"

class CollisionComponent;

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Inherit from Sprite of SFML graphics lib.
/// It is a Sprite that can have some entity components, giving them some specific feature such as moving, colliding etc.
/// </summary>
class Entity : public sf::Sprite, public std::enable_shared_from_this<Entity>, public IPoolItem
{
public:

#pragma region Constructors/Destructor
	Entity() = delete;
	Entity(const sf::Vector2f position, const short& life);
	Entity(const sf::Vector2f position, const sf::Texture& texture, const short& life);
	virtual ~Entity() = default;
#pragma endregion

#pragma region Getters
	inline Action<>& OnEntityEnabled() { return *onEntityEnabled; }
	inline Action<sptr<Entity>>& OnEntityKilled() { return *onEntityKilled; }
	inline virtual EEntityType GetEntityType() const = 0;
	inline bool IsAlive() const { return life > 0; }
#pragma endregion

#pragma region Methods

	/// <summary>
	/// Add a new EntityComponent on the components map.
	/// Passed in parameters all parameters necessary to instantiate the new entity component. 
	/// </summary>
	/// <typeparam name="TEntityComponent">Type of the new entity component to add.</typeparam>
	/// <typeparam name="...Params">Parameters type for the constructor of the new entity component.</typeparam>
	/// <param name="..._params">Parameters needed to instantiate the new entity component.</param>
	template<class TEntityComponent, typename... Params>
	inline void AddComponent(Params... _params)
	{
		static_assert(std::is_base_of<EntityComponent, TEntityComponent>::value, 
			"Type passed in template is not an EntityComponent !");

		uptr<TEntityComponent> _comp = std::make_unique<TEntityComponent>(shared_from_this(), _params...);
		components[_comp->GetComponentType()] = std::move(_comp);
	}

	/// <summary>
	/// Get an entity component on the entity.
	/// </summary>
	/// <typeparam name="TEntityComponent">Conversion to apply in order to get the right type.</typeparam>
	/// <param name="_type">Type of the EntityComponent needed.</param>
	/// <returns>The entity component if it exists, else nullptr</returns>
	template<class TEntityComponent>
	inline TEntityComponent* GetComponent(EEntityComponentType _type)
	{
		auto _itResult = components.find(_type);
			if (_itResult != components.end())
				return static_cast<TEntityComponent*>(components[_type].get());

		return nullptr;
	}

	virtual void Enable() override;

	/// <summary>
	/// Virtual pure method use for updating the entity in the current frame.
	/// </summary>
	/// <param name="_dt">Current delta time.</param>
	virtual void Update(const float& _dt);

	/// <summary>
	/// Virtual pure method use for drawing the entity and his children.
	/// </summary>
	/// <param name="window">Game window</param>
	virtual void Draw(sf::RenderWindow& window);

	/// <summary>
	/// Called when a collision component is present on the entity and when it collides with something.
	/// </summary>
	/// <param name="comp">The collision component with which the collision occurred</param>
	virtual void OnCollide(const CollisionComponent& comp);

	virtual void Disable() override;

	/// <summary>
	/// Decrease current life of the entity by 1.
	/// </summary>
	void DecrementLife();
#pragma endregion

protected:

#pragma region Properties
	/// <summary>
	/// Map of entity components present on the entity.
	/// </summary>
	std::unordered_map<EEntityComponentType, uptr<EntityComponent>> components;

	/// <summary>
	/// Delegate invoked when the entity is enabled.
	/// </summary>
	uptr<Action<>> onEntityEnabled;

	/// <summary>
	/// Delegate invoked when the entity is killed meaning that life is <= 0.
	/// </summary>
	uptr<Action<sptr<Entity>>> onEntityKilled;

	/// <summary>
	/// Current life of the entity
	/// </summary>
	short life;

	bool isEnable;
#pragma endregion
};

