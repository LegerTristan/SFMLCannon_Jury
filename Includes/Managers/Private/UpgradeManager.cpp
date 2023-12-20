#include "UpgradeManager.h"
#include "UpgradeComponent.h"
#include "UpgradeState.h"
#include "Game.h"

using namespace std;

UpgradeManager::~UpgradeManager()
{
	for (unsigned int i = 0; i < mAllyUpgrades.size(); ++i)
	{
		if (mAllyUpgrades[i])
		{
			delete mAllyUpgrades[i];
			mAllyUpgrades[i] = nullptr;
		}
	}

	for (unsigned int i = 0; i < mEnemyUpgrades.size(); ++i)
	{
		if (mEnemyUpgrades[i])
		{
			delete mEnemyUpgrades[i];
			mEnemyUpgrades[i] = nullptr;
		}
	}
}

bool UpgradeManager::IsWaitingForUpgrade() const
{
	return mUpgradeWaiting;
}

void UpgradeManager::AddUpgrade(UpgradeComponent* _upgrade)
{
	if (_upgrade->GetType() == UpgradeType::ALLY)
		UpgradeManager::mAllyUpgrades.push_back(_upgrade);
	else
		UpgradeManager::mEnemyUpgrades.push_back(_upgrade);
}

void UpgradeManager::RemoveUpgrade(UpgradeComponent* _upgrade)
{
	if (_upgrade->GetType() == UpgradeType::ALLY)
	{
		auto allyIt = find(mAllyUpgrades.begin(), mAllyUpgrades.end(), _upgrade);
		mAllyUpgrades.erase(allyIt);
	}
	else
	{
		auto enemyIt = find(mEnemyUpgrades.begin(), mEnemyUpgrades.end(), _upgrade);
		mEnemyUpgrades.erase(enemyIt);
	}
}

vector<pair<UpgradeComponent*, UpgradeComponent*>> UpgradeManager::GetRandomUpgradePairs(const unsigned int& _pairNbr)
{
	vector<pair<UpgradeComponent*, UpgradeComponent*>> pairs;
	int randomAlly = 0, randomEnemy = 0;

	for (unsigned int i = 0; i < _pairNbr; ++i)
	{
		randomAlly = rand() % mAllyUpgrades.size();
		randomEnemy = rand() % mEnemyUpgrades.size();
		pairs.push_back(pair<UpgradeComponent*, UpgradeComponent*>(mAllyUpgrades[randomAlly], mEnemyUpgrades[randomEnemy]));
	}

	return pairs;
}