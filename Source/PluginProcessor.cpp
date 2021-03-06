/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HelloVstAudioProcessor::HelloVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	currentAngle = 0.0f;
	currentSampleRate = 0.0f;
	angleDelta = 0.0f;
	frequency = 0.0f;
}

HelloVstAudioProcessor::~HelloVstAudioProcessor()
{
}

//==============================================================================
const String HelloVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double HelloVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloVstAudioProcessor::setCurrentProgram (int index)
{
}

const String HelloVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HelloVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	currentSampleRate = sampleRate;
	updateAngleDelta();
}

void HelloVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HelloVstAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	//===================================================================
	// Midi Processing
	//===================================================================

	MidiMessage message;
	int time;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(message, time);)
	{
		if (message.isController())
		{
			receiveMidiCC(message);
		}
	}

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


	//===================================================================
	// Audio Processing
	//===================================================================

	float* channelData = buffer.getWritePointer(0);

	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		const float currentSample = (float)std::sin(currentAngle);
		currentAngle += angleDelta;

		channelData[i] = currentSample * gain;
	}

	// copy first channel buffer to other channels
	for(int channel = 1; channel < totalNumOutputChannels; ++channel)
		buffer.copyFrom(channel, 0, channelData, buffer.getNumSamples());
}

//==============================================================================
bool HelloVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HelloVstAudioProcessor::createEditor()
{
    return new HelloVstAudioProcessorEditor (*this);
}

//==============================================================================
void HelloVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HelloVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void HelloVstAudioProcessor::updateGain(float value)
{
	gain = value;
}

void HelloVstAudioProcessor::updateFrequency(float value)
{
	if (currentSampleRate > 0.0)
	{
		frequency = value;
		updateAngleDelta();
	}
}

void HelloVstAudioProcessor::receiveMidiCC(MidiMessage message)
{
	int cc = message.getControllerNumber();
	int value = message.getControllerValue();

	if (cc == 7) // Volume CC
	{
		const MessageManagerLock mmlock;

		auto editor = static_cast<HelloVstAudioProcessorEditor*>(getActiveEditor());

		editor->gainSlider.setValue(value / 127.0f);
		editor->gainSlider.repaint();
	}
	else if (cc == 10) // Pan CC
	{
		const MessageManagerLock mmlock;

		auto editor = static_cast<HelloVstAudioProcessorEditor*>(getActiveEditor());

		editor->frequencySlider.setValue((value / 127.0f * 5000.0f) + 50.0f);
		editor->frequencySlider.repaint();
	}
}

void HelloVstAudioProcessor::updateAngleDelta()
{
	const double cyclesperSample = frequency / currentSampleRate;
	angleDelta = cyclesperSample * 2.0 * double_Pi;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloVstAudioProcessor();
}
