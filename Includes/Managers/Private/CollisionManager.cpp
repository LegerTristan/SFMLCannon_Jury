#include "CollisionManager.h"
#include "LevelState.h"
#include "WaveManager.h"
#include "Game.h"
#include "ScoreManager.h"
#include <algorithm>
#include "Utilities.h"

CollisionManager::CollisionManager() :
	physicsCheckRate(PHYSIC_CHECK_RATE),
	physicsTimer(std::make_unique<TimerComponent<CollisionManager>>(this, &CollisionManager::UpdateCollision, physicsCheckRate, true))
{
	if(physicsTimer)
		physicsTimer->Start();
}

void CollisionManager::RegisterCollisionComponent(CollisionComponent* _comp)
{
	if(std::find(collisionComps.begin(), collisionComps.end(), _comp) == collisionComps.end())
		collisionComps.push_back(_comp);
}

void CollisionManager::Update(const float& _dt)
{
	if (physicsTimer)
		physicsTimer->UpdateTimer(_dt);
}

void CollisionManager::UnregisterCollisionComponent(CollisionComponent* _comp)
{
	auto _it = std::find(collisionComps.begin(), collisionComps.end(), _comp);
	if (_it != collisionComps.end())
		collisionComps.erase(_it);
}

void CollisionManager::ClearCollisions()
{
	collisionComps.clear();
}

void CollisionManager::UpdateCollision()
{
 	for (unsigned int i = 0; i < collisionComps.size(); ++i)
	{
		const CollisionComponent* _compA = collisionComps[i];
		for (unsigned int j = i + 1; j < collisionComps.size(); ++j)
		{
			const CollisionComponent* _compB = collisionComps[j];
			if (_compA && _compB)
			{
				_compA->HandleCollision(_compB);
				_compB->HandleCollision(_compA);
			}
		}
	}
}
