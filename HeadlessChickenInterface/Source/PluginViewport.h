/*
  ==============================================================================

    PluginViewport.h
    Created: 24 Nov 2018 6:13:39pm
    Author:  Duncan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginViewComponent.h"

//==============================================================================
/*
*/
class PluginViewport    : public Viewport
{
public:
    PluginViewport(PluginViewComponent * e);
    ~PluginViewport();

    void paint (Graphics&) override;
	void resized() override;

private:
	//PluginListComponent plugins;
	PluginViewComponent * viewer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginViewport)
};
