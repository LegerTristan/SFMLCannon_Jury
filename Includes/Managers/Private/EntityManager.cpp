#include "EntityManager.h"
#include "Entity.h"
#include "Utilities.h"
#include "CannonBallFactory.h"
#include "GolemFactory.h"
#include "WraithFactory.h"

EntityManager::EntityManager() :
	onEntitySpawned(std::make_unique<Action<const EEntityType&>>(nullptr)),
	onEntityDisabled(std::make_unique<Action<const EEntityType&>>(nullptr))
{
	entityManagers[EEntityType::CANNON_BALL] = std::make_pair(std::make_unique<CannonBallFactory>(), std::make_unique<ObjectPool>());
	entityManagers[EEntityType::GOLEM] = std::make_pair(std::make_unique<GolemFactory>(), std::make_unique<ObjectPool>());
	entityManagers[EEntityType::WRAITH] = std::make_pair(std::make_unique<WraithFactory>(), std::make_unique<ObjectPool>());
}

void EntityManager::Init()
{
	Game::GetInstance()->GetScoreManager().RegisterEntityManager(*this);
}

sptr<Entity> EntityManager::SpawnEntity(EEntityType _entityType, const sf::Vector2f& _pos, const sf::Vector2f& _velocity)
{
	sptr<Entity> _entity = nullptr;
	auto _itResult = entityManagers.find(_entityType);
	if (_itResult != entityManagers.end())
	{
		_entity = RetrieveFromPool(_entityType, _pos, _velocity);
		_entity = _entity ? _entity : CreateNewEntityFromFactory(_entityType, _pos, _velocity);
	}

	if (_entity)
	{
		activeEntities.push_back(_entity);
		onEntitySpawned->Invoke(_entityType);
	}

	return _entity;
}

sptr<Entity> EntityManager::RetrieveFromPool(EEntityType _type, const sf::Vector2f& _pos, const sf::Vector2f& _velocity)
{
	sptr<Entity> _entity = std::static_pointer_cast<Entity>(entityManagers[_type].second->Retrieve());
	if (_entity)
	{
		std::cout << "Retrieve an entity of type " << (int)_type << " !" << std::endl;
		_entity->setPosition(_pos);
		MoveComponent* _moveComp = _entity->GetComponent<MoveComponent>(EEntityComponentType::MOVE);

		if(_moveComp)
			_moveComp->SetVelocity(_velocity);

		_entity->Enable();
	}

	return _entity;
}

sptr<Entity> EntityManager::CreateNewEntityFromFactory(EEntityType _type, const sf::Vector2f& _pos, const sf::Vector2f& _velocity)
{
	sptr<Entity> _entity = entityManagers[_type].first->CreateEntity(_pos, _velocity);

	if (_entity)
	{
		std::cout << "Create a new entity of type " << (int)_type << " !" <<std::endl;
		_entity->OnEntityKilled().AddDynamic(this, &EntityManager::DisableEntity);
	}

	return _entity;
}

void EntityManager::UpdateEntities(sf::RenderWindow& _window, const float& _dt)
{
	// Update all entities
	for (auto& _entity : activeEntities)
	{
		_entity->Update(_dt);
		_entity->Draw(_window);
	}
}

void EntityManager::DisableEntity(sptr<Entity> _entity)
{
	if (!_entity)
		return;

	const EEntityType& _entityType = _entity->GetEntityType();
	auto _itResult = entityManagers.find(_entityType);
	auto _itEntity = std::find(activeEntities.begin(), activeEntities.end(), _entity);
	if (_itResult == entityManagers.end() || _itEntity == activeEntities.end())
		return;

	_entity->Disable();
	entityManagers[_entityType].second->Put(_entity);
	activeEntities.erase(_itEntity);
	onEntityDisabled->Invoke(_entityType);
}

void EntityManager::DisableAllEntities()
{
	for (auto& _entity : activeEntities)
	{
		_entity->Disable();
	}
}