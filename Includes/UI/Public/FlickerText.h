#pragma once

#include <SFML/Graphics.hpp>
#include "TimelineComponent.h"

using namespace sf;

const float FLICKERING_SPEED = 1.0f;						// Speed of the flickering timeline component.
const float FLICKERING_DURATION = 2.0f;						// Duration of the flickering
const float FLICKERING_INTERVALS = 0.19f;					// Default flickering intervals of the game.

/// <summary>
/// Inherit from Text of SFML graphics lib.
/// A text that flicker sometime when his TimelineComponent is called.
/// </summary>
class FlickerText : public Text
{
public:

	// CONSTRUCTORS & DESTRUCTOR

	FlickerText() = default;
	FlickerText(const char* text);
	~FlickerText() { delete mFlickerTimeline; }

	// GETTER

	TimelineComponent<FlickerText>* GetFlickerTimeline() const;

	/// <summary>
	/// Display text if it is not display or inversely
	/// </summary>
	void Flicker();

private:

	/// <summary>
	/// Controls the flickering effect flow
	/// </summary>
	TimelineComponent<FlickerText>* mFlickerTimeline;

	/// <summary>
	/// Text to display with the flickering effect
	/// </summary>
	const char* mText;

	/// <summary>
	/// Check if the text is currently displaying or not.
	/// </summary>
	bool mIsTextDisplay = false;
};

