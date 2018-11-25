/*
  ==============================================================================

    AudioMenu.h
    Created: 24 Nov 2018 7:17:12pm
    Author:  Duncan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AudioMenu    : public Component,
					 public ApplicationCommandTarget,
					 public MenuBarModel
{
public:
	enum CommandIDs
	{
		configureAudio = 1
	};

    AudioMenu();
    ~AudioMenu();

	void paint(Graphics&) override;
    void resized() override;
	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int, const String&) override;
	void getAllCommands(Array<CommandID>& c) override;
	void menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/) override {}
	ApplicationCommandTarget* getNextCommandTarget() override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	bool perform(const InvocationInfo& info) override;
	void openAudioOptionsMenu();

private:
	ApplicationCommandManager commandManager;
	std::unique_ptr<MenuBarComponent> menuBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioMenu)
};
