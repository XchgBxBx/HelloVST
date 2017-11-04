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


	gainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	gainSlider.setRange(0.0, 1.0, 0.01);
	gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 90, 0);
	gainSlider.setPopupDisplayEnabled(true, this);
	gainSlider.setTextValueSuffix(" Gain");
	gainSlider.setValue(0.25);
	gainSlider.addListener(this);

	addAndMakeVisible(&gainSlider);


	frequencySlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	frequencySlider.setRange(50.0, 5000.0, 1.0);
	frequencySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 90, 0);
	frequencySlider.setPopupDisplayEnabled(true, this);
	frequencySlider.setTextValueSuffix(" Hz");
	frequencySlider.setValue(440.0);
	frequencySlider.addListener(this);

	addAndMakeVisible(&frequencySlider);
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
    g.drawFittedText("Gain", 35, 0, 100, 30, Justification::centredLeft, 1);
	g.drawFittedText("Freq", 115, 0, 100, 30, Justification::centredLeft, 1);
}

void HelloVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	gainSlider.setBounds(40, 30, 20, getHeight() - 60);
	frequencySlider.setBounds(120, 30, 20, getHeight() - 60);
}


void HelloVstAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
	if (slider == &gainSlider)
	{
		processor.updateGain(slider->getValue());
	}
	else if (slider == &frequencySlider)
	{
		processor.updateFrequency(slider->getValue());
	}
	
}