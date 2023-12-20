#pragma once

#include <stack>
#include "TimeManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "GameState.h"
#include "Singleton.h"
#include "CollisionManager.h"
//class UpgradeManager;

using namespace sf;

const Color CLEAR_COLOR = Color(240, 240, 240, 255);	// Background color when window clear method is called.

/// <summary>
/// Main class. Handle GameState and update the last one that will be displayed on screen.
/// Contains also a TimeManager and TextureManager to handle elements that is necessary in every state.
/// </summary>
class Game : public Singleton<Game>, public std::enable_shared_from_this<Game>
{
public:

#pragma region Constructor/Destructor
	Game();
	virtual ~Game() = default;
#pragma endregion

#pragma region Getters
	inline const TimeManager& GetTimeManager() const { return *timeManager; }
	inline TextureManager& GetTextureManager() const { return *textureManager; }
	inline InputManager& GetInputManager() const { return *inputManager; }
	inline CollisionManager& GetCollisionManager() const { return *collisionManager; }
#pragma endregion

#pragma region PublicMethods
	inline bool IsGameValid() const { return timeManager != nullptr && textureManager != nullptr 
		&& inputManager != nullptr; }

	/// <summary>
	/// Add a new state to the stack of states in the game and init state's features.
	/// </summary>
	/// <param name="newState">New state to add in the game</param>
	void AddState(uptr<GameState> newState);

	/// <summary>
	/// Call the method Update(RenderWindow* window) of the last state in the stack
	/// </summary>
	void UpdateState(const float& dt);

	/// <summary>
	/// Remove the last state in the stack
	/// </summary>
	void RemoveState();

	/// <summary>
	/// Main loop of the program.
	/// While the window is open, the game continues.
	/// </summary>
	void LaunchGame();
#pragma endregion

private:

#pragma region Properties
	/// <summary>
	/// Stack of GameStates
	/// </summary>
	std::stack<uptr<GameState>> states;

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

	uptr<InputManager> inputManager;

	uptr<CollisionManager> collisionManager;
#pragma endregion
	
#pragma region PrivateMethods
	void LoopGame();

	void CloseGame();
#pragma endregion
};
