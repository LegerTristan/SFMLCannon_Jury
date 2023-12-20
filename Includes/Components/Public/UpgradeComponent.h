#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

/// <summary>
/// Type of an upgrade.
/// </summary>
enum class UpgradeType
{
	ALLY = 0,
	ENEMY = 1,
};

/// <summary>
/// Add an upgrade that have a rank, a type, and a name.
/// </summary>
class UpgradeComponent
{
public:

	// DEFAULT CONSTRUCTOR

	UpgradeComponent() = default;
	~UpgradeComponent() = default;

	// GETTERS

	UpgradeType GetType() const;
	string GetName() const;
	Texture* GetTexture() const { return mTexture; }
	bool IsRankMaxed() const;

	/// <summary>
	/// Up the rank of the component by 1.
	/// Clamped by the max rank.
	/// </summary>
	virtual void UpRank();

protected:

	/// <summary>
	/// Name of the upgrade
	/// </summary>
	string mName;

	/// <summary>
	/// Texture of the upgrade, necessary for displaying correct sprite with the description.
	/// </summary>
	Texture* mTexture;

	/// <summary>
	/// Determine if the upgrade will boost the ally or the enemies.
	/// </summary>
	UpgradeType mType = UpgradeType::ALLY;

	/// <summary>
	/// Current rank of the upgrade.
	/// </summary>
	unsigned int mCurrentRank;

	/// <summary>
	/// Max rank of the upgrade.
	/// </summary>
	unsigned int mMaxRank;
};

