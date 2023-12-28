#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "IDelegate.h"

/// <summary>
/// A component that have is own timeline.
/// Allow is owner to do an action through a certain time, repeat it, or juste get the current time of this timeline.
/// The timeline flow is a float
/// </summary>
/// <typeparam name="T">Owner class that we need in order to call an event of this class through the component.</typeparam>
template<class TClass>
class TimerComponent
{
public:

	TimerComponent(TClass* _owner, void(TClass::* _ownerFunction)(), const float& _triggerRate, const bool& _repeatTrigger = false) :
		timerDelegate(std::make_unique<MemberDelegate<void, TClass>>(_owner, _ownerFunction)),
		triggerRate(_triggerRate),
		currentTriggerTime(0.0f),
		repeat(_repeatTrigger),
		isActive(false) {}

	~TimerComponent() = default;

	/// <summary>
	/// Start the timeline.
    /// Means that the startTime is assigned at this moment, and the UpdateTimeline method willnow be called.
	/// </summary>
	inline void Start()
	{
		isActive = true;
		currentTriggerTime = 0.0f;
	}

	/// <summary>
	/// Update the current time of the timeline.
    /// Call HandleEvent method and reset the component if it reachs his duration (if it has one).
	/// </summary>
	void UpdateTimer(const float _dt)
	{
		if (!isActive)
			return;

		currentTriggerTime += _dt;

		if (currentTriggerTime >= triggerRate)
		{
			CallEvent();
			Reset();
		}
	}

private:

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
		currentTriggerTime = 0.0f;

		if (repeat)
			return;

		isActive = false;
		timerDelegate = nullptr;
	}

	uptr<MemberDelegate<void, TClass>> timerDelegate;

	/// <summary>
	/// Time when the event needs to be called
	/// </summary>
	float currentTriggerTime;
	
	/// <summary>
	/// Use with repeat trigger boolean, interval of time betwwen two call of event.
	/// </summary>
	float triggerRate;

	/// <summary>
	/// Tell if the timeline is currently active
	/// </summary>
	bool isActive;
	
	/// <summary>
	/// Tell if the trigger for the event needs to be repeated until a possible end.
	/// </summary>
	bool repeat;
};