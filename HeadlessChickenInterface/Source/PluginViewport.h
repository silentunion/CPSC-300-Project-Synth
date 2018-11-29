/*
  ==============================================================================

    PluginViewport.h
    Created: 24 Nov 2018 6:13:39pm
    Author:  Duncan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PluginViewport    : public Viewport
{
public:
    PluginViewport(GenericAudioProcessorEditor * e);
    ~PluginViewport();

    void paint (Graphics&) override;
	void resized() override;

private:
	//PluginListComponent plugins;
	GenericAudioProcessorEditor * editor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginViewport)
};
