#include "UpgradeState.h"
#include "HUD.h"
#include "UpgradeComponent.h"
#include "UIGridComponent.h"
#include "LevelButtonComponent.h"
#include "Constants.h"
#include "Game.h"

UpgradeState::UpgradeState(const vector<pair<UpgradeComponent*, UpgradeComponent*>>& _upgradePairs)
{
	// Set background's texture and sprite
	Texture* temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Up_Background.png").get();
	mBackgroundSprite.setTexture(*temp);
	mBackgroundSprite.setOrigin(static_cast<float>(temp->getSize().x / 2),
		static_cast<float>(temp->getSize().y / 2));
	mBackgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mBackgroundSprite.setScale(UPGRADE_BACKGROUND_SCALE);

	// Set level up's text
	mLevelUpText.setFont(*HUD::GetGameFont());
	mLevelUpText.setString("\t\t\tLevel Up !\nChoose an upgrade !");
	mLevelUpText.setCharacterSize(LVLUP_CHARACTER_SIZE);
	mLevelUpText.setOrigin(0, 0);
	mLevelUpText.setPosition((WINDOW_WIDTH / 2 - LVLUP_TEXT_OFFSET_X), (WINDOW_HEIGHT / 16));
	mLevelUpText.setFillColor(Color::Black);

	LevelButtonComponent* newBtn;
	// Setup buttons
	for (unsigned int i = 0; i < DEFAULT_UPGRADE_PAIR_NBR; ++i)
	{
		newBtn = new LevelButtonComponent();
		newBtn->SetUpgradePair(_upgradePairs[i]);
		mButtons.push_back(newBtn);
	}

	mGrid = new UIGridComponent(mButtons, Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4), 1, 200.0f, 300.0f);
}

UpgradeState::~UpgradeState()
{
	delete mGrid;

	for (LevelButtonComponent* btn : mButtons)
	{
		if (btn)
		{
			delete btn;
			btn = nullptr;
		}
	}
}

void UpgradeState::InitFeatures()
{
	mLevelBackground.setTexture(*Game::GetInstance()->GetTextureManager()->
		GetTexture("Assets/Textures/Cannon_Background.png").get());
}

void UpgradeState::Update(RenderWindow* _window)
{
	bool result = UpdateMouse(_window);

	_window->draw(mLevelBackground);
	_window->draw(mBackgroundSprite);
	_window->draw(mLevelUpText);

	for (LevelButtonComponent* btn : mButtons)
	{
		btn->UpdateDisplay();
		btn->Draw(_window);
	}

	if (result)
		Game::GetInstance()->UpdateUpgradeMenu(false);
}

bool UpgradeState::UpdateMouse(RenderWindow* _window)
{
	mMousePos = Mouse::getPosition(*_window);

	for (LevelButtonComponent* btn : mButtons)
	{
		if (btn->getGlobalBounds().intersects(FloatRect(mMousePos.x, mMousePos.y, MOUSE_RECT_SIZE.x, MOUSE_RECT_SIZE.y)))
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				btn->SetState(ButtonState::ACTIVE);
				btn->IncreaseUpgradesRank();
				return true;
			}
			else
				btn->SetState(ButtonState::HOVERED);
		}
		else
			btn->SetState(ButtonState::NORMAL);
	}

	return false;
}

void UpgradeState::SetLevelButtonUpgrades(const pair<UpgradeComponent*, UpgradeComponent*>& _upgradePair,
	const unsigned int& _index)
{
	if (_index < mButtons.size())
	{
		mButtons[_index]->SetUpgradePair(_upgradePair);
	}
}
