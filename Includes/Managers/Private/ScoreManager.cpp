#include "ScoreManager.h"
#include "Game.h"
#include "HUD.h"
#include "Constants.h"
#include "EntityManager.h"
#include "KillZone.h"

ScoreManager::ScoreManager() :
	scorePerEntityType(
		{
			{EEntityType::GOLEM, GROUND_ENEMY_SCORE},
			{EEntityType::WRAITH, FLOAT_ENEMY_SCORE}
		}
	),
	onScoreUpdated(std::make_unique<Action<const int&>>(nullptr)),
	highScore(Game::GetInstance()->GetIOManager().Read<int>(SCORE_SAVE_VALUE_NAME)),
	score(0)
{}

void ScoreManager::RegisterEntityManager(EntityManager& _entityManager)
{
	_entityManager.OnEntityDisabled().AddDynamic(this, &ScoreManager::AddScore);
}

void ScoreManager::UnregisterEntityManager(EntityManager& _entityManager)
{
	_entityManager.OnEntityDisabled().RemoveDynamic(this, &ScoreManager::AddScore);
}

void ScoreManager::RegisterKillZone(KillZone& _killZone)
{
	_killZone.OnKillZoneTriggered().AddDynamic(this, &ScoreManager::DecreaseScore);
}

void ScoreManager::UnregisterKillZone(KillZone& _killZone)
{
	_killZone.OnKillZoneTriggered().RemoveDynamic(this, &ScoreManager::DecreaseScore);
}

void ScoreManager::SaveScoreBehavior()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

 	if(score > highScore)
		_game->GetIOManager().Save(score, SCORE_SAVE_VALUE_NAME);

	_game->SetLatestScore(score);
}

void ScoreManager::UpdateScoreBehavior(const EEntityType& _type, float _scalar)
{
	auto _itResult = scorePerEntityType.find(_type);
	if (_itResult == scorePerEntityType.end())
		return;

	score += scorePerEntityType[_type] * _scalar;
	onScoreUpdated->Invoke(score);
}

void ScoreManager::AddScore(const EEntityType& _type)
{
	UpdateScoreBehavior(_type);
}

void ScoreManager::DecreaseScore(const EEntityType& _type)
{
	UpdateScoreBehavior(_type, -1);
}