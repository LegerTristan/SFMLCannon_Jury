#include "Game.h"
#include "Constants.h"
#include "LevelState.h"
#include "RetryState.h"

Game::Game() : 
    window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cannon"),
    timeManager(std::make_unique<TimeManager>()),
    textureManager(std::make_unique<TextureManager>()),
    inputManager(std::make_unique<InputManager>()),
    collisionManager(std::make_unique<CollisionManager>()),
    scoreManager(std::make_unique<ScoreManager>())
{
}

Game::~Game()
{
    timeManager = nullptr;
    textureManager = nullptr;
    inputManager = nullptr;
    collisionManager = nullptr;
    scoreManager = nullptr;
}

void Game::StartGame()
{
    if (!IsGameValid())
        return;

    RestartGame();
    inputManager->AddEvent(sf::Event::Closed, this, &Game::CloseGame);
    LoopGame();
}

void Game::LoopGame()
{
    while (window.isOpen())
    {
        timeManager->UpdateCurrentTime();
        const float _dt = timeManager->CalculateDeltaTime();

        inputManager->ListenEvents(window);

        collisionManager->Update(_dt);

        window.clear(CLEAR_COLOR);
        UpdateState(_dt);
        window.display();

        timeManager->UpdateLastTime();
    }
}

void Game::AddState(uptr<GameState> _newState)
{
    _newState->OnStateEnded().AddDynamic(this, &Game::RemoveState);
    states.push(std::move(_newState));
}

void Game::UpdateState(const float& _dt)
{
    if (!states.empty())
    {
        uptr<GameState>& _front = states.front();
        if (!_front->IsInit())
            _front->Init();

        _front->Update(window, _dt);
    }
}

void Game::RemoveState()
{
    states.front()->OnStateEnded().RemoveDynamic(this, &Game::RemoveState);
    collisionManager->ClearCollisions();
    states.pop();
}

void Game::CloseGame()
{
    window.close();
}

void Game::RestartGame()
{
    AddState(std::make_unique<LevelState>());
    AddState(std::make_unique<RetryState>());
}
