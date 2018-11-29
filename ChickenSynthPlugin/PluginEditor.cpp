/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChickenSynthPluginAudioProcessorEditor::ChickenSynthPluginAudioProcessorEditor (ChickenSynthPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
	keyboard(processor.keystate, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	volSlider.setRange(0.0f, 127.0f, 1.0f);
	volSlider.setValue(127.0f);
	volSlider.setSliderStyle(Slider::LinearHorizontal);
	volSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volSlider.setPopupDisplayEnabled(true, false, this);
	volSlider.setTextValueSuffix(" Volume");
	addAndMakeVisible(volSlider);
	volSlider.addListener(this);
	addAndMakeVisible(keyboard);
	processor.keystate.addListener(&processor);
    setSize(800, 300);
}

ChickenSynthPluginAudioProcessorEditor::~ChickenSynthPluginAudioProcessorEditor()
{
}

//==============================================================================
void ChickenSynthPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Volume", 40, 30, getWidth()/4, 20, Justification::centred, 1);
}

void ChickenSynthPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	volSlider.setBounds(40, 60, getWidth()/4, 20);
	keyboard.setBounds(0, 3*getHeight()/4, getWidth(), getHeight()/4);
}

void ChickenSynthPluginAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.volume = volSlider.getValue();
}
