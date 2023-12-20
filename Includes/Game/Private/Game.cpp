#include "Game.h"
#include "Constants.h"

Game::Game() : 
    window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cannon"),
    timeManager(std::make_unique<TimeManager>()),
    textureManager(std::make_unique<TextureManager>()),
    inputManager(std::make_unique<InputManager>()),
    collisionManager(std::make_unique<CollisionManager>())
{
}

void Game::AddState(std::unique_ptr<GameState> _newState)
{
    _newState->Init();
    states.push(std::move(_newState));
}

void Game::LaunchGame()
{
    if (!IsGameValid())
        return;

    inputManager->BindEvent(sf::Event::Closed, this, &Game::CloseGame);
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

void Game::UpdateState(const float& _dt)
{
    if (!states.empty())
        states.top()->Update(window, _dt);
}

void Game::RemoveState()
{
    states.pop();
}

void Game::CloseGame()
{
    window.close();
}
