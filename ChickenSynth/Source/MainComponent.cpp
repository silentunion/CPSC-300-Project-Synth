/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible(frequencySlider);
	frequencySlider.setRange(50.0, 5000.0);
	frequencySlider.setSkewFactorFromMidPoint(500.0);
	frequencySlider.setValue(currentFrequency, dontSendNotification);
	frequencySlider.onValueChange = [this] { targetFrequency = frequencySlider.getValue(); };

	addAndMakeVisible(levelSlider);
	levelSlider.setRange(0.0, 0.125);
	levelSlider.setValue((double)currentLevel, dontSendNotification);
	levelSlider.onValueChange = [this] { targetLevel = (float)levelSlider.getValue(); };
    setSize (800, 600);

    setAudioChannels (2, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
	currentSampleRate = sampleRate;
	updateAngleDelta();
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	auto* leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
	auto* rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

	auto localTargetFrequency = targetFrequency;

	if (targetFrequency != currentFrequency)
	{
		auto frequencyIncrement = (targetFrequency - currentFrequency) / bufferToFill.numSamples;

		for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			auto currentSample = (float)std::sin(currentAngle);
			currentFrequency += frequencyIncrement;
			updateAngleDelta();
			currentAngle += angleDelta;
			leftBuffer[sample] = currentSample;
			rightBuffer[sample] = currentSample;
		}

		currentFrequency = localTargetFrequency;
	}
	else
	{
		for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			auto currentSample = (float)std::sin(currentAngle);
			currentAngle += angleDelta;
			leftBuffer[sample] = currentSample;
			rightBuffer[sample] = currentSample;
		}
	}

	auto localTargetLevel = targetLevel;
	bufferToFill.buffer->applyGainRamp(bufferToFill.startSample, bufferToFill.numSamples, currentLevel, localTargetLevel);
	currentLevel = localTargetLevel;
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
	frequencySlider.setBounds(10, 10, getWidth() - 20, 20);
	levelSlider.setBounds(10, 40, getWidth() - 20, 20);
}


