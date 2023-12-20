#pragma once

#include <vector>

#include "GameState.h"

using namespace std;

class UpgradeComponent;
class UIGridComponent;
class LevelButtonComponent;

const Vector2f MOUSE_RECT_SIZE = Vector2f(1.0f, 1.0f);				// Size of the rect of the mouse
const Vector2f UPGRADE_BACKGROUND_SCALE = Vector2f(1.1f, 1.0f);		// Scale of background upgrade

const float LVLUP_CHARACTER_SIZE = 20.0f;							// Character size of level up text
const float LVLUP_TEXT_OFFSET_X = 100.0f;							// X offset of level up text

const unsigned int DEFAULT_UPGRADE_PAIR_NBR = 3;					// Default number of upgrade pair

/// <summary>
/// Menu of the upgrades where the player choose a new upgrade for him and for his enemies.
/// </summary>
class UpgradeState : public GameState
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	UpgradeState(const vector<pair<UpgradeComponent*, UpgradeComponent*>>& upgradePairs);
	~UpgradeState();

	/// <summary>
	/// Inherited from GameState
	/// Initialize the upgrade's background sprite
	/// </summary>
	void InitFeatures() override final;

	/// <summary>
	/// Draw the upgrade menu, with all buttons to choose an upgrade.
	/// </summary>
	/// <param name="window"></param>
	void Update(RenderWindow* window) override final;

	/// <summary>
	/// Update mouse position and handle clicks
	/// </summary>
	/// <param name="window">Game window</param>
	/// <returns></returns>
	bool UpdateMouse(RenderWindow* window);

	/// <summary>
	/// Set the ally upgarde, and the enemy upgrade for a specific button.
	/// </summary>
	/// <param name="upgradePair">Pair of an ally upgrade, and an enemy upgrade.</param>
	/// <param name="index">Index of the button.</param>
	void SetLevelButtonUpgrades(const pair<UpgradeComponent*, UpgradeComponent*>& upgradePairs, const unsigned int& index);

private:

	/// <summary>
	/// Position of the mouse in the window
	/// </summary>
	Vector2i mMousePos;

	/// <summary>
	/// Vector of the buttons displays for choosing an upgrade.
	/// </summary>
	vector<LevelButtonComponent*> mButtons;

	/// <summary>
	/// A grid component for ordering buttons properly.
	/// </summary>
	UIGridComponent* mGrid;

	/// <summary>
	/// Sprite of the background
	/// </summary>
	Sprite mBackgroundSprite;

	/// <summary>
	/// Text to display that the player has leveled up and has to choose an upgrade.
	/// </summary>
	Text mLevelUpText;
};

