#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// A component that have is own timeline.
/// Allow is owner to do an action through a certain time, repeat it, or juste get the current time of this timeline.
/// The timeline flow is a float
/// </summary>
/// <typeparam name="T">Owner class that we need in order to call an event of this class through the component.</typeparam>
template<class T>
class TimerComponent
{
public:
	/// <summary>
	/// Event delegate
	/// </summary>
	typedef void (T::* Function)();

	TimerComponent(T* _owner, Function _ownerFunction, const float& _triggerRate, const bool& _repeatTrigger = false) :
		owner(_owner),
		ownerFunction(_ownerFunction),
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
	void UpdateTimeline(const float _dt)
	{
		if (!isActive)
			return;

		currentTriggerTime += _dt;

		if (currentTriggerTime >= triggerRate)
		{
			HandleEvent();
			Reset();
		}
	}

private:

    /// <summary>
    /// Check if it can cal the event and if it needs to repeat it or not.
    /// </summary>
	void HandleEvent()
	{
		if (owner && ownerFunction)
			CallEvent();
	}

	/// <summary>
	/// Call the event bind to the timeline component.
	/// </summary>
	void CallEvent() const
	{
		(owner->*ownerFunction)();
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
		owner = nullptr;
		ownerFunction = nullptr;
	}

	/// <summary>
	/// Owner of the component.
	/// Necessary for calling the event with the mOwnerFunction member
	/// </summary>
	T* owner;

	/// <summary>
	/// Function of the owner that will be called when the event trigger will be passed.
	/// </summary>
	Function ownerFunction;

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