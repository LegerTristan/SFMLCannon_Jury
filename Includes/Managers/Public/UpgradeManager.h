#pragma once

#include <vector>

class UpgradeComponent;

using namespace std;

/// <summary>
/// Manager of all elements in relation with upgrades.
/// </summary>
class UpgradeManager
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	UpgradeManager() = default;
	~UpgradeManager();
	
	// GETTER

	bool IsWaitingForUpgrade() const;

	/// <summary>
	/// Add an upgrade to the vector of his specific type.
	/// </summary>
	/// <param name="upgrade">The new upgrade to add</param>
	void AddUpgrade(UpgradeComponent* upgrade);

	/// <summary>
	/// Remove an upgrade from the vector of his specific type.
	/// </summary>
	/// <param name="upgrade">Upgrade to remove</param>
	void RemoveUpgrade(UpgradeComponent* upgrade);

	/// <summary>
	/// Return a number of random pairs of upgrade components in a vector.
	/// </summary>
	/// <param name="pairNbr">Number of random pair needed.</param>
	/// <returns>Returns a vector of pair of upgrade components</returns>
	vector<pair<UpgradeComponent*, UpgradeComponent*>> GetRandomUpgradePairs(const unsigned int& pairNbr);

private:

	/// <summary>
	/// Vector of upgrades of a specific type : ally or enemy upgrades.
	/// </summary>
	vector<UpgradeComponent*> mAllyUpgrades, mEnemyUpgrades;

	/// <summary>
	/// Has the player level up and wait to choose a new upgrade
	/// </summary>
	bool mUpgradeWaiting = false;
};

