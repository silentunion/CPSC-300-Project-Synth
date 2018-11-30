/*
  ==============================================================================

    SecondaryComponent.cpp
    Created: 25 Nov 2018 8:34:48pm
    Author:  Duncan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondaryComponent.h"

//==============================================================================
SecondaryComponent::SecondaryComponent(AudioDeviceSelectorComponent * selector)
{
	audioSetupComp = selector;

	addAndMakeVisible(audioSetupComp);

	setSize(400, 400);
}

SecondaryComponent::~SecondaryComponent()
{
}

void SecondaryComponent::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
}


void SecondaryComponent::resized()
{
	audioSetupComp->setBounds(getLocalBounds());
}
