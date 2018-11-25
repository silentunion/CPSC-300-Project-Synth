/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	//toolbar init
	addAndMakeVisible(am);

	//plugin viewer init
	addAndMakeVisible(plugs);

	//window init
	setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::whitesmoke);
    g.drawText (currentSizeAsString, getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	auto area = getLocalBounds();
	am.setBounds(area.removeFromTop(30));
	currentSizeAsString = String(getWidth()) + " X " + String(getHeight());
	plugs.setBounds(area.removeFromLeft(jmax(80, getLocalBounds().getWidth() / 4)));
}
