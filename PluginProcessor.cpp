/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultiverbAudioProcessor::MultiverbAudioProcessor()
     : parameters(*this, nullptr)
{
	parameters.createAndAddParameter("LFrevTime", "Low Frequency Reverb Time", String(),
		NormalisableRange<float>(1.0f, 5.0f, 0.1f), 3.0f, nullptr, nullptr);
	parameters.createAndAddParameter("HFrevTime", "High Frequency Reverb Time", String(),
		NormalisableRange<float>(1.0f, 5.0f, 0.1f), 2.0f, nullptr, nullptr);
	parameters.createAndAddParameter("roomArea", "Room Area", String(),
		NormalisableRange<float>(1000.0f, 10000.0f, 100.0f), 3000.0f, nullptr, nullptr);
	parameters.createAndAddParameter("pctRev", "Percent Reverb", String(),
		NormalisableRange<float>(0.0f, 100.0f, 1.0f), 50.0f, nullptr, nullptr);
	parameters.createAndAddParameter("level", "Level", String(),
		NormalisableRange<float>(-20.0f, 10.0f, 0.1f), 0.0f, nullptr, nullptr);

	parameters.state = ValueTree(Identifier("MVtreeState"));

	lfRevTimeParam = parameters.getRawParameterValue("LFrevTime");
	hfRevTimeParam = parameters.getRawParameterValue("HFrevTime");
	roomAreaParam = parameters.getRawParameterValue("roomArea");
	pctRevParam = parameters.getRawParameterValue("pctRev");
	levelParam = parameters.getRawParameterValue("level");
}

MultiverbAudioProcessor::~MultiverbAudioProcessor()
{
}

//==============================================================================
const String MultiverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultiverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultiverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultiverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultiverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultiverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultiverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultiverbAudioProcessor::setCurrentProgram (int index)
{
}

const String MultiverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultiverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MultiverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	oldlfRevTime = *lfRevTimeParam;
	oldhfRevTime = *hfRevTimeParam;
	oldroomArea = *roomAreaParam;
	mvReverb.pctRev = *pctRevParam / 100.0; // convert from percentage
	mvReverb.level = pow(10.0f, *levelParam / 20.0); // convert from dB

	mvReverb.Update(oldlfRevTime, oldhfRevTime, oldroomArea, getSampleRate()); // set derived parameters
}

void MultiverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultiverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultiverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear excess output channels, if necessary
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	// Simple parameters
	mvReverb.pctRev = *pctRevParam / 100.0f;
	mvReverb.level = pow(10.0f, *levelParam / 20.0f);

	// Check whether update needed
	if (*lfRevTimeParam != oldlfRevTime || *hfRevTimeParam != oldhfRevTime || *roomAreaParam != oldroomArea)
	{
		oldlfRevTime = *lfRevTimeParam;
		oldhfRevTime = *hfRevTimeParam;
		oldroomArea = *roomAreaParam;
		mvReverb.Update(oldlfRevTime, oldhfRevTime, oldroomArea, getSampleRate());
	}

	// Process block of samples
	float * leftSamples = buffer.getWritePointer(0);
	float * rightSamples = buffer.getWritePointer(1);
	mvReverb.Process(leftSamples, rightSamples, buffer.getNumSamples());
}

//==============================================================================
bool MultiverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultiverbAudioProcessor::createEditor()
{
    return new MultiverbAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void MultiverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void MultiverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiverbAudioProcessor();
}
