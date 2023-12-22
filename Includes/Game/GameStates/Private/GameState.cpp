#include "GameState.h"

void GameState::EndState()
{
	if(onStateEnded)
		onStateEnded->Invoke();
}
