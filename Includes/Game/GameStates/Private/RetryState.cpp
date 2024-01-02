#include "RetryState.h"
#include "RetryHUD.h"
#include "Game.h"

RetryState::RetryState() :
	GameState(std::make_unique<RetryHUD>())
{

}

void RetryState::Init()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;
	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.AddKeyEvent(sf::Event::KeyPressed, RETRY_KEY, this, &RetryState::EndState);
	static_cast<RetryHUD*>(hud.get())->Init();
	GameState::Init();
}

void RetryState::Update(sf::RenderWindow& _window, const float& _dt)
{
	hud->Update(_dt);
	hud->Draw(_window);
}

void RetryState::EndState()
{
	Game* _game = Game::GetInstance();

	if (!_game)
		return;
	InputManager& _inputManager = _game->GetInputManager();
	_inputManager.RemoveKeyEvent(sf::Event::KeyPressed, RETRY_KEY, this, &RetryState::EndState);
	GameState::EndState();
	_game->RestartGame();
}
