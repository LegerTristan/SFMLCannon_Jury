#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class UpgradeComponent;

const float BUTTON_CHARACTER_SIZE = 20.0f;							// Character size of button
const float UPGRADE_CHARACTER_SIZE = 16.0f;							// Character size of upgrade texts
const float TEXT_ORIGIN_OFFSET = 100.0f;							// Origin offset for the text

const float ANCHOR_OFFSET_X = 150.0f;								// X offset of the anchor
const float ANCHOR_OFFSET_DSC_Y = 60.0f;							// Y offset of the anchor of descs
const float ANCHOR_OFFSET_SPRITE_Y = 10.0f;							// Y offset of the anchor of sprites

const Vector2f BUTTON_SCALE = Vector2f(1.55f, 0.8f);				// Scale of the button
const Vector2f SPRITE_SCALE = Vector2f(0.4f, 0.4f);					// Upgrade sprites scale

const Color COLOR_HOVERED = Color(255.0f, 255.0f, 255.0f, 255.0f);	// Color to apply when hovered
const Color COLOR_ACTIVE = Color(210.0f, 210.0f, 210.0f, 255.0f);	// Color to apply when actived
const Color COLOR_NORMAL = Color(220.0f, 220.0f, 220.0f, 200.0f);	// Color to apply when button is in normal state

/// <summary>
/// State of a UIButton
/// </summary>
enum class ButtonState
{
	NORMAL = 0,
	HOVERED = 1,
	ACTIVE = 2,
};

/// <summary>
/// A button designed to represent two upgrades, one for the ally, one for the enemy.
/// </summary>
class LevelButtonComponent : public Sprite
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	LevelButtonComponent();
	~LevelButtonComponent() {}

	// SETTERS

	void SetUpgradePair(const pair<UpgradeComponent*, UpgradeComponent*>& pair);
	void SetState(const ButtonState& state) { mState = state; }

	/// <summary>
	/// Set position of the button and add a specific offset to every UI elements of the button
	/// in order to keep a kind of anchor behavior
	/// </summary>
	/// <param name="pos">New position of the button</param>
	void Anchor(const Vector2f& pos);

	/// <summary>
	/// Draw the button and every elements that compose it.
	/// </summary>
	/// <param name="_window">Game window</param>
	void Draw(RenderWindow* _window);

	/// <summary>
	/// Update background color of the button based on its state.
	/// </summary>
	void UpdateDisplay();

	/// <summary>
	/// Increase rank of the two upgrades bind to the button.
	/// </summary>
	void IncreaseUpgradesRank();

private:

	/// <summary>
	/// Pair of upgrades bind to the button.
	/// One is an ally upgrade, the other is an enemy upgrade.
	/// </summary>
	pair<UpgradeComponent*, UpgradeComponent*> mUpgrades;

	// ALLY'S UPGRADES

	/// <summary>
	/// Represents ally's upgrade.
	/// </summary>
	Sprite mAllySprite;

	/// <summary>
	/// Description of ally's upgrade.
	/// </summary>
	Text mAllyDsc;

	// ENEMY'S UPGRADE

	/// <summary>
	/// Represents enemy's upgrade.
	/// </summary>
	Sprite mEnemySprite;

	/// <summary>
	/// Description of enemy's upgrade.
	/// </summary>
	Text mEnemyDsc;

	// Button's display

	/// <summary>
	/// Text plain to display the "AND" between the two upgrades.
	/// </summary>
	Text mButtonAnd;

	/// <summary>
	/// Current state of the button
	/// </summary>
	ButtonState mState = ButtonState::NORMAL;
};

