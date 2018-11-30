/*
  ==============================================================================

    PluginViewComponent.h
    Created: 28 Nov 2018 7:34:22pm
    Author:  MSi Reece

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PluginViewComponent    : public Component
{
public:
    PluginViewComponent();
    ~PluginViewComponent();

    void paint (Graphics&) override;
    void resized() override;

	void addPlugin(String s);

private:
	OwnedArray<String> plugNames;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginViewComponent)
};
