#include <iostream>
#include <crtdbg.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "TextureManager.h"

#define _CRTDBG_MAP_ALLOC

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(3485);

    Game* _game = Game::GetInstance();

    if (!_game->IsGameValid())
        return -1;

    _game->StartGame();
    delete _game;

    return 0;
}