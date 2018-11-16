/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
	void updateAngleDelta()
	{
		auto cyclesPerSample = frequencySlider.getValue() / currentSampleRate;         // [2]
		angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;                // [3]
	}

private:
    //==============================================================================
    // Your private member variables go here...
	double currentSampleRate = 0.0, currentAngle = 0.0, angleDelta = 0.0;
	double currentFrequency = 500.0, targetFrequency = 500.0;
	float currentLevel = 0.1f, targetLevel = 0.1f;
	Slider frequencySlider;
	Slider levelSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
