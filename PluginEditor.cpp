/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultiverbAudioProcessorEditor::MultiverbAudioProcessorEditor (MultiverbAudioProcessor& parent, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (parent), valueTreeState(vts)
{
	// Create labels
	LFrevTimeLabel.setText("LF Rev Time", dontSendNotification);
	LFrevTimeLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(LFrevTimeLabel);

	HFrevTimeLabel.setText("HF Rev Time", dontSendNotification);
	HFrevTimeLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(HFrevTimeLabel);

	roomAreaLabel.setText("Room Area (sq ft)", dontSendNotification);
	roomAreaLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(roomAreaLabel);

	pctRevLabel.setText("Percent Rev", dontSendNotification);
	pctRevLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(pctRevLabel);

	levelLabel.setText("Level", dontSendNotification);
	levelLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(levelLabel);

	// Create sliders
	LFrevTimeSlider.setTextValueSuffix(" s");
	LFrevTimeSlider.setColour(Slider::trackColourId, Colours::orangered);
	LFrevTimeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	LFrevTimeSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	LFrevTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(LFrevTimeSlider);
	LFrevTimeAttachment = new SliderAttachment(valueTreeState, "LFrevTime", LFrevTimeSlider);

	HFrevTimeSlider.setTextValueSuffix(" s");
	HFrevTimeSlider.setColour(Slider::trackColourId, Colours::orangered);
	HFrevTimeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	HFrevTimeSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	HFrevTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(HFrevTimeSlider);
	HFrevTimeAttachment = new SliderAttachment(valueTreeState, "HFrevTime", HFrevTimeSlider);

	roomAreaSlider.setColour(Slider::trackColourId, Colours::orangered);
	roomAreaSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	roomAreaSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	roomAreaSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(roomAreaSlider);
	roomAreaAttachment = new SliderAttachment(valueTreeState, "roomArea", roomAreaSlider);

	pctRevSlider.setTextValueSuffix(" %");
	pctRevSlider.setColour(Slider::trackColourId, Colours::orangered);
	pctRevSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	pctRevSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	pctRevSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(pctRevSlider);
	pctRevAttachment = new SliderAttachment(valueTreeState, "pctRev", pctRevSlider);

	levelSlider.setTextValueSuffix(" dB");
	levelSlider.setColour(Slider::trackColourId, Colours::orangered);
	levelSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	levelSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	levelSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(levelSlider);
	levelAttachment = new SliderAttachment(valueTreeState, "level", levelSlider);

	int guiHeight = titleHeight + 5 * controlHeight + 2 * margin;
	int guiWidth = labelWidth + sliderWidth + 2 * margin;
    setSize (guiWidth, guiHeight);
}

MultiverbAudioProcessorEditor::~MultiverbAudioProcessorEditor()
{
}

//==============================================================================
void MultiverbAudioProcessorEditor::paint (Graphics& mvgui)
{
	mvgui.fillAll(Colours::burlywood);

	Image logoImage = ImageCache::getFromMemory(BinaryData::logo_png, BinaryData::logo_pngSize);
	
	int x, y;
	x = (getWidth() - titleWidth - logoWidth) / 2;
	y = margin;

	mvgui.drawImageWithin(logoImage, x, y, logoWidth, titleHeight, RectanglePlacement::xLeft);
	x += logoWidth;
	mvgui.setColour(Colours::black);
	mvgui.setFont(24.0f);
	mvgui.drawFittedText("Multiverb Reverb Effect", x, y, titleWidth, titleHeight, Justification::centred, 1);
}

void MultiverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	int x = margin;
	int y = margin + titleHeight;
	LFrevTimeLabel.setBounds(x, y, labelWidth, controlHeight);
	y += controlHeight;
	HFrevTimeLabel.setBounds(x, y, labelWidth, controlHeight);
	y += controlHeight;
	roomAreaLabel.setBounds(x, y, labelWidth, controlHeight);
	y += controlHeight;
	pctRevLabel.setBounds(x, y, labelWidth, controlHeight);
	y += controlHeight;
	levelLabel.setBounds(x, y, labelWidth, controlHeight);
	x += labelWidth;
	y = margin + titleHeight;
	LFrevTimeSlider.setBounds(x, y, sliderWidth, controlHeight);
	y += controlHeight;
	HFrevTimeSlider.setBounds(x, y, sliderWidth, controlHeight);
	y += controlHeight;
	roomAreaSlider.setBounds(x, y, sliderWidth, controlHeight);
	y += controlHeight;
	pctRevSlider.setBounds(x, y, sliderWidth, controlHeight);
	y += controlHeight;
	levelSlider.setBounds(x, y, sliderWidth, controlHeight);
}
