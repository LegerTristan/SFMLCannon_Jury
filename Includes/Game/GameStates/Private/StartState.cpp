#include "StartState.h"
#include "Game.h"
#include "StartHUD.h"

StartState::StartState() :
	GameState(std::make_unique<StartHUD>())
{
}

void StartState::Init()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;
	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.AddKeyEvent(sf::Event::KeyPressed, START_KEY, this, &StartState::EndState);
	GameState::Init();
}

void StartState::Update(sf::RenderWindow& _window, const float& _dt)
{
	hud->Update(_dt);
	hud->Draw(_window);
}

void StartState::EndState()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;
	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.RemoveKeyEvent(sf::Event::KeyPressed, START_KEY, this, &StartState::EndState);
	GameState::EndState();
	_game->RestartGame();
}
