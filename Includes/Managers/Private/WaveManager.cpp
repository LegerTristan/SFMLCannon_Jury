#include <iostream>
#include "WaveManager.h"
#include "LevelState.h"
#include "EntityManager.h"
#include "Game.h"
#include "ScalarUpgradeComponent.h"


WaveManager::WaveManager(sptr<EntityManager> _entityManager) :
	enemiesSpawnTimeline(std::make_unique<TimerComponent<WaveManager>>(this, &WaveManager::SpawnEnemyBehavior, ENEMY_SPAWN_RATE, true)),
	entityManager(_entityManager),
	maxEnemyNbr(ENEMY_MAX_NBR_START),
	currentEnemyNbr(0)
{
	if (!_entityManager)
		return;
	enemiesSpawnTimeline->Start();
	_entityManager->OnEntitySpawned().AddDynamic(this, &WaveManager::IncreaseEnemyNbrBehavior);
	_entityManager->OnEntityDisabled().AddDynamic(this, &WaveManager::DecreaseEnemyNbrBehavior);
}

void WaveManager::Update(const float& _dt)
{
	enemiesSpawnTimeline->UpdateTimer(_dt);
}

inline void WaveManager::IncreaseEnemyNbrBehavior(const EEntityType& _type)
{
	if (_type <= EEntityType::CANNON_BALL)
		return;

	currentEnemyNbr++;
}

inline void WaveManager::DecreaseEnemyNbrBehavior(const EEntityType& _type)
{
	if (_type <= EEntityType::CANNON_BALL)
		return;

	currentEnemyNbr--;
}

void WaveManager::SpawnEnemyBehavior()
{
	if (currentEnemyNbr >= maxEnemyNbr)
		return;

	sptr<Entity> _entity = nullptr;
	if(rand() % 2 == 0)
		_entity = entityManager->SpawnEntity(EEntityType::WRAITH, GetFloatEnemyRandomSpawnPosition(), FLOAT_ENEMY_VELOCITY);
	else
		_entity = entityManager->SpawnEntity(EEntityType::GOLEM, GetGroundEnemyRandomSpawnPosition(), GROUND_ENEMY_VELOCITY);
}
