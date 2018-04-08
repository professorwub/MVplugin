/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultiverbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
	enum
	{
		titleHeight = 40,
		titleWidth = 400,
		logoWidth = 100,
		controlHeight = 50,
		labelWidth = 100,
		sliderWidth = 400,
		margin = 25
	};

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    MultiverbAudioProcessorEditor (MultiverbAudioProcessor&, AudioProcessorValueTreeState&);
    ~MultiverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	AudioProcessorValueTreeState& valueTreeState;

	Label LFrevTimeLabel;
	Slider LFrevTimeSlider;
	ScopedPointer<SliderAttachment> LFrevTimeAttachment;

	Label HFrevTimeLabel;
	Slider HFrevTimeSlider;
	ScopedPointer<SliderAttachment> HFrevTimeAttachment;

	Label roomAreaLabel;
	Slider roomAreaSlider;
	ScopedPointer<SliderAttachment> roomAreaAttachment;

	Label pctRevLabel;
	Slider pctRevSlider;
	ScopedPointer<SliderAttachment> pctRevAttachment;

	Label levelLabel;
	Slider levelSlider;
	ScopedPointer<SliderAttachment> levelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiverbAudioProcessorEditor)
};
