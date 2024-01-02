#pragma once

#include <queue>
#include "TimeManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "GameState.h"
#include "Singleton.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "IOManager.h"

using namespace sf;

/// <summary>
/// Main class. Handle GameStates and update the first one on the queue.
/// Contains also some managers that are more specific to the game instead of a state.
/// </summary>
class Game : public Singleton<Game>
{
public:

#pragma region Constructor/Destructor
	Game();
	virtual ~Game();
#pragma endregion

#pragma region Getters
	inline const TimeManager& GetTimeManager() const { return *timeManager; }
	inline TextureManager& GetTextureManager() const { return *textureManager; }
	inline InputManager& GetInputManager() const { return *inputManager; }
	inline CollisionManager& GetCollisionManager() const { return *collisionManager; }
	inline IOManager& GetIOManager() const { return *ioManager; }
	inline int GetLatestScore() const { return latestScore; }
	inline void SetLatestScore(const int& _score) { latestScore = _score; }
#pragma endregion

#pragma region PublicMethods
	inline bool IsGameValid() const { return timeManager != nullptr && textureManager != nullptr 
		&& inputManager != nullptr && collisionManager != nullptr && ioManager != nullptr; }

	/// <summary>
	/// Add a new state to the queue of states in the game and bind OnStateEnd to game's RemoveState method.
	/// </summary>
	/// <param name="newState">New state to add in the game</param>
	void AddState(uptr<GameState> newState);

	/// <summary>
	/// Call the Update method of the front state in the queue
	/// </summary>
	void UpdateState(const float& dt);

	/// <summary>
	/// Remove the front state in the queue.
	/// </summary>
	void RemoveState();

	/// <summary>
	/// Main loop of the program.
	/// While the window is open, the game continues.
	/// </summary>
	void StartGame();

	void RestartGame();
#pragma endregion

private:

#pragma region Properties
	/// <summary>
	/// Queue of GameStates
	/// </summary>
	std::queue<uptr<GameState>> states;

	/// <summary>
	/// Window of the game
	/// </summary>
	RenderWindow window;

	/// <summary>
	/// Handle every elements bind to the time
	/// </summary>
	uptr<TimeManager> timeManager;

	/// <summary>
	/// Contains all the textures that was load at least one time.
	/// </summary>
	uptr<TextureManager> textureManager;

	/// <summary>
	/// Handles input logics and bindings to any events
	/// </summary>
	uptr<InputManager> inputManager;

	/// <summary>
	/// Handles collisions in the game.
	/// </summary>
	uptr<CollisionManager> collisionManager;

	/// <summary>
	/// Handles I/O manipulations in the game.
	/// </summary>
	uptr<IOManager> ioManager;

	/// <summary>
	/// Stock the latest score made in the level.
	/// </summary>
	int latestScore;
#pragma endregion
	
#pragma region PrivateMethods
	void LoopGame();

	void CloseGame();
#pragma endregion
};
