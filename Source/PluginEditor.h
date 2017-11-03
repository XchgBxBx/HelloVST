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
class HelloVstAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    HelloVstAudioProcessorEditor (HelloVstAudioProcessor&);
    ~HelloVstAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HelloVstAudioProcessor& processor;

	/* THIS IS A SLIDER :)*/
	/*Slider midiVolume;*/

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloVstAudioProcessorEditor)
};
