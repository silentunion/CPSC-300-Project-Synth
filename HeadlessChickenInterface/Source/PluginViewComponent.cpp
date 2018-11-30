/*
  ==============================================================================

    PluginViewComponent.cpp
    Created: 28 Nov 2018 7:34:22pm
    Author:  MSi Reece

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginViewComponent.h"

//==============================================================================
PluginViewComponent::PluginViewComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PluginViewComponent::~PluginViewComponent()
{
}

void PluginViewComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
	for (String * s : plugNames)
    g.drawText (*s, getLocalBounds().removeFromTop(15),
                Justification::centred, true);  
}

void PluginViewComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void PluginViewComponent::addPlugin(String s)
{
	plugNames.add(&s);
}
