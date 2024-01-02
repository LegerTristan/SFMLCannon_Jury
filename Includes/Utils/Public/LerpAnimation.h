#pragma once

#include <cmath>
#include <iostream>
#include "IDelegate.h"
#include "Utilities.h"

/// <summary>
/// Utils class that handles an animation logic through a linear interpolation of a value.
/// Uses a delegate to call a method of a specific class that uses this lerp value.
/// </summary>
/// <typeparam name="TClass">Method's class to bind to the delegate.</typeparam>
template<class TClass>
class LerpAnimation
{
public:

#pragma region Constructor/Destructor
	LerpAnimation(TClass* _owner, void(TClass::* _ownerFunction)(const float&), const float& _duration, 
		const float& _max, const float& _min = 0.0f, const bool& _repeat = false,
		const bool& _shouldReverseAtEnd = false) :
		lerpAnimDelegate(std::make_unique<MemberDelegate<void, TClass, const float&>>(_owner, _ownerFunction)),
		duration(_duration),
		maxValue(_max),
		minValue(_min),
		currentProgress(0.0f),
		repeat(_repeat),
		shouldReverseAtEnd(_shouldReverseAtEnd),
		inRevert(false),
		isActive(false) {}

	~LerpAnimation() = default;
#pragma endregion

#pragma region PublicMethods
	inline void Start(const float& _duration = -1.0f)
	{
		duration = _duration <= 0.0f ? duration : _duration;
		if (duration <= 0.0f)
			return;

		isActive = true;
	}

	inline void Update(const float _dt)
	{
		if (!isActive)
			return;

		UpdateCurrentProgress(_dt);
		CallEvent(Utilities::Lerp(minValue, maxValue, Utilities::Clamp(currentProgress / duration, 0.0f, 1.0f)));

		if (inRevert ? currentProgress <= 0 : currentProgress >= duration)
			Reset();
	}
#pragma endregion

private:

#pragma region PrivateMethods
	inline void UpdateCurrentProgress(const float _dt)
	{
		if (inRevert)
		{
			currentProgress -= _dt;
			currentProgress = currentProgress < 0.0f ? 0.0f : currentProgress;
		}
		else
		{
			currentProgress += _dt;
			currentProgress = currentProgress > duration ? duration : currentProgress;
		}
	}

	inline void CallEvent(const float& _lerpValue) const
	{
		if (lerpAnimDelegate)
			lerpAnimDelegate->Invoke(_lerpValue);
	}

	inline void Reset()
	{
		if (shouldReverseAtEnd && !inRevert)
		{
			inRevert = true;
			return;
		}

		currentProgress = 0.0f;
		if (repeat)
		{
			inRevert = false;
			return;
		}

		isActive = false;
		lerpAnimDelegate = nullptr;
	}
#pragma endregion

#pragma region Properties
	/// <summary>
	/// Delegate invoked every time UpdateCurrentProgress method is called, passes current lerp value in parameters.
	/// </summary>
	uptr<MemberDelegate<void, TClass, const float&>> lerpAnimDelegate;

	/// <summary>
	/// Duration of the animation
	/// </summary>
	float duration;

	float currentProgress;

	float minValue, maxValue;

	/// <summary>
	/// Does the animation should repeat undefinitely
	/// </summary>
	bool repeat;

	/// <summary>
	/// Does the animation needs to play reverse at the end
	/// </summary>
	bool shouldReverseAtEnd;

	/// <summary>
	/// Is the animation currrently played reverse
	/// </summary>
	bool inRevert;

	bool isActive;
#pragma endregion
};