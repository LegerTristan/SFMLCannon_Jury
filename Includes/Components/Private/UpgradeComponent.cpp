#include "UpgradeComponent.h"
#include "Game.h"
#include "UpgradeManager.h"

UpgradeType UpgradeComponent::GetType() const
{
    return mType;
}

string UpgradeComponent::GetName() const
{
	return mName;
}

bool UpgradeComponent::IsRankMaxed() const
{
	return mMaxRank <= mCurrentRank;
}

void UpgradeComponent::UpRank()
{
	mCurrentRank ++;

	if (mCurrentRank >= mMaxRank)
	{
		mCurrentRank = mMaxRank;
		Game::GetInstance()->GetUpgradeManager()->RemoveUpgrade(this);
	}
}