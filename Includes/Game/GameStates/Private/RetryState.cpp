#include "RetryState.h"
#include "RetryHUD.h"
#include "Game.h"

RetryState::RetryState() :
	GameState(std::make_unique<RetryHUD>())
{

}

void RetryState::Init()
{
	
}

void RetryState::Update(sf::RenderWindow& _window, const float& _dt)
{
	hud->Update(_dt);
	hud->Draw(_window);
}
