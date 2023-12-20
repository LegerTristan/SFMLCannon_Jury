#pragma once

#include <utility>
#include <type_traits>
#include <memory>

class Entity;

/// <summary>
/// Factory pattern used for create new entities.
/// </summary>
class EntityFactory
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	EntityFactory() = default;
	~EntityFactory() = default;

	/// <summary>
	/// Create new entity of template type T with the given parameters of template type TArgs and variadic
	/// </summary>
	/// <typeparam name="T">Type of the entity</typeparam>
	/// <typeparam name="...TArgs">Variadic template that contains the type of every parameters 
	/// needed to instantiate a new entity</typeparam>
	/// <param name="...args">Variadic parameters of various type needed for instantiate the new entity</param>
	/// <returns></returns>
	template<class T, typename... TArgs>
	inline static std::weak_ptr<Entity> CreateEntity(TArgs ... args)
	{
		static_assert(std::is_base_of<Entity, T>::value, "Type passed in parameters are not an Entity !");

		std::weak_ptr<T> entity(std::make_shared<T>(std::forward<TArgs>(args)...));

		return entity;
	}
};