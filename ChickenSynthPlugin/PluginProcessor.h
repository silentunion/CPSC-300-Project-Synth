/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class ChickenSynthPluginAudioProcessor  : public AudioProcessor,
										  public MidiKeyboardStateListener
{
public:
    //==============================================================================
    ChickenSynthPluginAudioProcessor();
    ~ChickenSynthPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	void updateAngleDelta()
	{
		auto cyclesPerSample = m.getMidiNoteInHertz(m.getNoteNumber()) / currentSampleRate;
		angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
	}

	float volume;
	MidiKeyboardState keystate;
private:
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    //==============================================================================
	double currentSampleRate = 0.0, currentAngle = 0.0, angleDelta = 0.0;
	MidiMessage m;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChickenSynthPluginAudioProcessor)
};
