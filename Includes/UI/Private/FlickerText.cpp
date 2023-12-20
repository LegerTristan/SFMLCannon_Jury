#include "FlickerText.h"
#include "TimelineComponent.h"

FlickerText::FlickerText(const char* _text)
{
	mText = _text;
	mFlickerTimeline = new TimelineComponent<FlickerText>(this, &FlickerText::Flicker, FLICKERING_INTERVALS,
		FLICKERING_SPEED, true, FLICKERING_DURATION);
}

TimelineComponent<FlickerText>* FlickerText::GetFlickerTimeline() const
{
	return mFlickerTimeline;
}

void FlickerText::Flicker()
{
	if (mIsTextDisplay)
		setString("");
	else
		setString(mText);

	mIsTextDisplay = !mIsTextDisplay;
}
