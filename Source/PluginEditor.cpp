/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HelloVstAudioProcessorEditor::HelloVstAudioProcessorEditor (HelloVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);


	mySlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	mySlider.setRange(0.0, 0.5, 0.01);
	mySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 90, 0);
	mySlider.setPopupDisplayEnabled(true, this);
	mySlider.setTextValueSuffix(" Gain");
	mySlider.setValue(0.25);
	mySlider.addListener(this);

	addAndMakeVisible(&mySlider);
}

HelloVstAudioProcessorEditor::~HelloVstAudioProcessorEditor()
{
}

//==============================================================================
void HelloVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Noise Gain", 15, 0, getWidth(), 30, Justification::centredLeft, 1);
}

void HelloVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	mySlider.setBounds(40, 30, 20, getHeight() - 60);
}


void HelloVstAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
	String message;
	double value = slider->getValue();
	message << "ur new value: " << value;
	processor.gain = value;
	Logger::getCurrentLogger()->writeToLog(message);
}