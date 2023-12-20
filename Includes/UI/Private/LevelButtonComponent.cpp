#include "LevelButtonComponent.h"
#include "HUD.h"
#include "UpgradeComponent.h"
#include "Constants.h"
#include "Game.h"

LevelButtonComponent::LevelButtonComponent()
{
	// Set background's texture and sprite
	Texture* temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Button_Background.png").get();
	setTexture(*temp);
	setOrigin(temp->getSize().x / 2, temp->getSize().y / 2);
	setScale(BUTTON_SCALE);

	// Set button's text
	mButtonAnd.setFont(*HUD::GetGameFont());
	mButtonAnd.setString("AND");
	mButtonAnd.setCharacterSize(BUTTON_CHARACTER_SIZE);
	mButtonAnd.setOrigin(BUTTON_CHARACTER_SIZE, mButtonAnd.getCharacterSize() / 2);
	mButtonAnd.setFillColor(Color::Black);



	// Set ally's sprite and texture

	temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Up_Cannon_LoadSpeed.png").get();
	mAllySprite.setTexture(*temp);
	mAllySprite.setOrigin(temp->getSize().x / 2, temp->getSize().y / 2);
	mAllySprite.setScale(SPRITE_SCALE);

	// Set ally's desc
	mAllyDsc.setFont(*HUD::GetGameFont());
	mAllyDsc.setString("Fire load increase !");
	mAllyDsc.setCharacterSize(UPGRADE_CHARACTER_SIZE);
	mAllyDsc.setOrigin(TEXT_ORIGIN_OFFSET, mAllyDsc.getCharacterSize() / 2);
	mAllyDsc.setFillColor(Color::Black);


	// Set enemy's sprite and texture

	temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Up_Enemy_Speed.png").get();
	mEnemySprite.setTexture(*temp);
	mEnemySprite.setOrigin(temp->getSize().x / 2, temp->getSize().y / 2);
	mEnemySprite.setScale(SPRITE_SCALE);

	// Set enemy's desc
	mEnemyDsc.setFont(*HUD::GetGameFont());
	mEnemyDsc.setString("Fire load increase !");
	mEnemyDsc.setCharacterSize(UPGRADE_CHARACTER_SIZE);
	mEnemyDsc.setOrigin(TEXT_ORIGIN_OFFSET, mEnemyDsc.getCharacterSize() / 2);
	mEnemyDsc.setFillColor(Color::Black);
}

void LevelButtonComponent::SetUpgradePair(const pair<UpgradeComponent*, UpgradeComponent*>& _pair)
{
	mUpgrades = _pair;

	mAllyDsc.setString(mUpgrades.first->GetName());
	mEnemyDsc.setString(mUpgrades.second->GetName());

	mAllySprite.setTexture(*_pair.first->GetTexture());
	mEnemySprite.setTexture(*_pair.second->GetTexture());
}

void LevelButtonComponent::Anchor(const Vector2f& _pos)
{
	setPosition(_pos);
	mButtonAnd.setPosition(Vector2f(_pos.x, _pos.y));

	// Place ally's upgrade displays
	mAllyDsc.setPosition(Vector2f(_pos.x - ANCHOR_OFFSET_X, _pos.y - ANCHOR_OFFSET_DSC_Y));
	mAllySprite.setPosition(Vector2f(_pos.x - ANCHOR_OFFSET_X, _pos.y + ANCHOR_OFFSET_SPRITE_Y));

	// Place enemy's upgrade displays
	mEnemyDsc.setPosition(Vector2f(_pos.x + ANCHOR_OFFSET_X, _pos.y - ANCHOR_OFFSET_DSC_Y));
	mEnemySprite.setPosition(Vector2f(_pos.x + ANCHOR_OFFSET_X, _pos.y + ANCHOR_OFFSET_SPRITE_Y));
}

void LevelButtonComponent::Draw(RenderWindow* _window)
{
	_window->draw(*this);
	_window->draw(mButtonAnd);

	// Draw ally's displays
	_window->draw(mAllySprite);
	_window->draw(mAllyDsc);

	// Draw enemy's displays
	_window->draw(mEnemySprite);
	_window->draw(mEnemyDsc);
}

void LevelButtonComponent::UpdateDisplay()
{
	switch (mState)
	{
	case ButtonState::HOVERED:
		setColor(COLOR_HOVERED);
		break;
	case ButtonState::ACTIVE:
		setColor(COLOR_ACTIVE);
		break;
	default:
		setColor(COLOR_NORMAL);
		break;
	}
}

void LevelButtonComponent::IncreaseUpgradesRank()
{
	mUpgrades.first->UpRank();
	mUpgrades.second->UpRank();
}
