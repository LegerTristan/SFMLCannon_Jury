#include "Entity.h"
#include "LevelState.h"
#include "EntityManager.h"
#include "Utilities.h"
#include "CollisionComponent.h"

Entity::Entity(const sf::Vector2f _position, const short& _life) :
	life(_life),
	onEntityKilled(std::make_unique<Action<sptr<Entity>>>(nullptr)),
	onEntityEnabled(std::make_unique<Action<>>(nullptr)),
	isEnable(true)
{
	// Set only entity's position
	setPosition(_position);
}

Entity::Entity(const sf::Vector2f _position, const sf::Texture& _texture, const short& _life) :
	life(_life),
	onEntityKilled(std::make_unique<Action<sptr<Entity>>>(nullptr)),
	onEntityEnabled(std::make_unique<Action<>>(nullptr)),
	isEnable(true)
{
	// Set entity's sprite & settings
	setTexture(_texture, true);
	setOrigin(Utilities::GetCenter(_texture));
	setPosition(_position);
}

void Entity::Enable()
{
	isEnable = true;
	onEntityEnabled->Invoke();
}

void Entity::Update(const float& _dt)
{
	if (!isEnable)
		return;

	for (auto& _component : components)
		_component.second->UpdateComponent(_dt);
}

void Entity::Draw(sf::RenderWindow& _window)
{
	if (!isEnable)
		return;

	_window.draw(*this);
	for (auto& _component : components)
		_component.second->DrawComponent(_window);
}

void Entity::OnCollide(const CollisionComponent& _comp)
{

}

void Entity::Disable()
{
	isEnable = false;
}

void Entity::DecrementLife()
{
	life--;
}