#include <iostream>
#include <crtdbg.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "LevelState.h"
#include "RetryState.h"
#include "TextureManager.h"

#define _CRTDBG_MAP_ALLOC

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Game* _game = Game::GetInstance();

    if (!_game->IsGameValid())
        return -1;

    _game->AddState(std::make_unique<RetryState>());
    _game->AddState(std::make_unique<LevelState>());
    _game->LaunchGame();

    delete _game;

    return 0;
}