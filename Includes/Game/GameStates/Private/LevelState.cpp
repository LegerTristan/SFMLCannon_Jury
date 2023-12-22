#include <iostream>
#include "LevelState.h"
#include "Game.h"
#include "KillZone.h"
#include "DefenceHUD.h"

LevelState::LevelState() : 
	GameState(std::make_unique<DefenceHUD>()),
	entityManager(std::make_unique<EntityManager>()),
	waveManager(std::make_unique<WaveManager>(entityManager)),
	cannon(std::make_unique<Cannon>(entityManager, Vector2f(CANNON_POS_X, WINDOW_HEIGHT - CANNON_POS_Y))),
	player(std::make_unique<Player>()),
	cannonBallsKillZone(std::make_shared<KillZone>(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT) + CB_KILL_ZONE_OFFSET)),
	enemiesKillZone(std::make_shared<KillZone>(sf::Vector2f(0.0f, WINDOW_HEIGHT / 2) + ENEMIES_KILL_ZONE_OFFSET))
{
}

void LevelState::Init()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;

	cannonBallsKillZone->Init(sf::Vector2f(WINDOW_WIDTH * 2, 0.0f) + CB_KILL_ZONE_EXTENT);
	enemiesKillZone->Init(sf::Vector2f(0.0f, WINDOW_HEIGHT) + ENEMIES_KILL_ZONE_EXTENT);

	player->BindToEnemiesKillZone(*enemiesKillZone);
	player->OnPlayerLose().AddDynamic(this, &LevelState::PreparteEndState);

	_game->GetScoreManager().RegisterKillZone(*enemiesKillZone);
	_game->GetScoreManager().RegisterEntityManager(*entityManager);
	GameState::Init();
}

void LevelState::Update(sf::RenderWindow& _window, const float& _dt)
{
	hud->Update(_dt);
	hud->Draw(_window);

	cannon->Update(_dt);
	cannon->Draw(_window);

	entityManager->UpdateEntities(_window, _dt);

	waveManager->Update(_dt);

	player->Draw(_window);

	cannonBallsKillZone->Draw(_window);
	enemiesKillZone->Draw(_window);

	if (endStateAtNextFrame)
		EndState();
}

void LevelState::EndState()
{
	cannonBallsKillZone->Disable();
	enemiesKillZone->Disable();
	entityManager->DisableAllEntities();
	cannon->Disable();
	GameState::EndState();
}
