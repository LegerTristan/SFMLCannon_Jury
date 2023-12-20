#pragma once

#include "UpgradeComponent.h"
#include "UpgradeManager.h"
#include "Game.h"

/// <summary>
/// Inherit from UpgradeComponent.
/// Specific type of upgrade component that increase a value of type Y by adding the rank as parameter
/// to a function of the owner.
/// </summary>
/// <typeparam name="T">Owner type.</typeparam>
/// <typeparam name="Y">Type of the value to increase.</typeparam>
template<class T, class Y>
class ScalarUpgradeComponent : public UpgradeComponent
{
	/// <summary>
	/// Event delegate
	/// </summary>
	typedef Y (T::*Function)(float) const;

public:

	// CONSTRUCTOR & DESTRUCTOR

	ScalarUpgradeComponent(T* owner, Function ownerFunction, Y& valueToCompute,
		string name, const char* path, const UpgradeType& type, const unsigned int& maxRank = 5);
	~ScalarUpgradeComponent() = default;

	/// <summary>
	/// Increase the rank of the component and compute the value.
	/// </summary>
	void UpRank() override final;

	/// <summary>
	/// Compute the value to increase with the owner's function and the current rank of the upgrade.
	/// </summary>
	void ComputeValue();

private:

	/// <summary>
	/// Owner of the upgrade.
	/// </summary>
	T* mOwner;

	/// <summary>
	/// Pointer function to a specific function of the owner.
	/// </summary>
	Function mOwnerFunction;

	/// <summary>
	/// Value to increase.
	/// </summary>
	Y& mComputedValue;
};

template<class T, class Y>
inline ScalarUpgradeComponent<T, Y>::ScalarUpgradeComponent(T* _owner, Function _ownerFunction, Y& _valueToCompute,
	string _name, const char* _path, const UpgradeType& _type, const unsigned int& _maxRank) : mComputedValue(_valueToCompute)
{
	mName = _name;
	mTexture = (Game::GetInstance()->GetTextureManager()->GetTexture(_path).get());
	mType = _type;
	mOwner = _owner;
	mOwnerFunction = _ownerFunction;
	mCurrentRank = 0;
	mMaxRank = _maxRank;

	Game::GetInstance()->GetUpgradeManager()->AddUpgrade(this);
}

template<class T, class Y>
inline void ScalarUpgradeComponent<T, Y>::UpRank()
{
	UpgradeComponent::UpRank();
 	ComputeValue();
}

template<class T, class Y>
void ScalarUpgradeComponent<T, Y>::ComputeValue()
{
  	mComputedValue = (mOwner->*mOwnerFunction)(mCurrentRank);
}
