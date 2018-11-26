/*
  ==============================================================================

    SecondaryComponent.h
    Created: 25 Nov 2018 8:34:48pm
    Author:  Duncan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SecondaryComponent    : public Component
{
public:
    SecondaryComponent(AudioDeviceSelectorComponent * selector);
    ~SecondaryComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
	AudioDeviceSelectorComponent * audioSetupComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondaryComponent)
};
