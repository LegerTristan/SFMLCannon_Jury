#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "IDelegate.h"

/// <summary>
/// A component that triggers a delegate at the end of his timer.
/// Allow its owner to do an action through a certain time, and also repeat it if necessary.
/// </summary>
/// <typeparam name="T">Owner class used for the delegate.</typeparam>
template<class TClass>
class TimerComponent
{
public:

#pragma region Constructor/Destructor
	TimerComponent(TClass* _owner, void(TClass::* _ownerFunction)(), const float& _triggerRate, const bool& _repeatTrigger = false) :
		timerDelegate(std::make_unique<MemberDelegate<void, TClass>>(_owner, _ownerFunction)),
		triggerRate(_triggerRate),
		elapsedTime(0.0f),
		repeat(_repeatTrigger),
		isActive(false) {}

	~TimerComponent() = default;
#pragma endregion


#pragma region PublicMethods
	/// <summary>
	/// Start the timeline.
    /// Means that the startTime is assigned at this moment, and the UpdateTimeline method willnow be called.
	/// </summary>
	inline void Start()
	{
		isActive = true;
		elapsedTime = 0.0f;
	}

	/// <summary>
	/// Update the current time of the timeline.
    /// Call HandleEvent method and reset the component if it reachs his duration (if it has one).
	/// </summary>
	void UpdateTimer(const float _dt)
	{
		if (!isActive)
			return;

		elapsedTime += _dt;

		if (elapsedTime >= triggerRate)
		{
			CallEvent();
			Reset();
		}
	}
#pragma endregion

private:

#pragma region PrivateMethods
	/// <summary>
	/// Call the event bind to the timeline component.
	/// </summary>
	void CallEvent() const
	{
		if(timerDelegate)
			timerDelegate->Invoke();
	}

	/// <summary>
	/// Stop the timeline and reset all his members  necessary for the flow.
	/// </summary>
	void Reset()
	{
		elapsedTime = 0.0f;

		if (repeat)
			return;

		isActive = false;
		timerDelegate = nullptr;
	}
#pragma endregion

#pragma region Properties
	/// <summary>
	/// Delegate triggered when the timer reaches its end.
	/// </summary>
	uptr<MemberDelegate<void, TClass>> timerDelegate;

	/// <summary>
	/// Elapsed timer since the start of the timer.
	/// </summary>
	float elapsedTime;
	
	/// <summary>
	/// Time between each delegate's invoke
	/// </summary>
	float triggerRate;

	/// <summary>
	/// Tell if the timer is currently active
	/// </summary>
	bool isActive;
	
	/// <summary>
	/// Tell if the trigger for the event needs to be repeated undefinitely.
	/// </summary>
	bool repeat;
#pragma endregion
};