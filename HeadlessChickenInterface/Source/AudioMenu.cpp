/*
  ==============================================================================

    AudioMenu.cpp
    Created: 24 Nov 2018 7:17:12pm
    Author:  Duncan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioMenu.h"

//==============================================================================
AudioMenu::AudioMenu()
{
	menuBar.reset(new MenuBarComponent(this));
	addAndMakeVisible(menuBar.get());
	setApplicationCommandManagerToWatch(&commandManager);
	commandManager.registerAllCommandsForTarget(this);

	// this lets the command manager use keypresses that arrive in our window to send out commands
	addKeyListener(commandManager.getKeyMappings());
}

AudioMenu::~AudioMenu()
{
}

void AudioMenu::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId).darker());
}

void AudioMenu::resized()
{
	menuBar->setBounds(getLocalBounds().removeFromTop(LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
}

StringArray AudioMenu::getMenuBarNames()
{
	return { "Config" };
}

PopupMenu AudioMenu::getMenuForIndex(int menuIndex, const String&)
{
	PopupMenu menu;

	if (menuIndex == 0)
	{
		menu.addCommandItem(&commandManager, CommandIDs::configureAudio);
	}

	return menu;
}

ApplicationCommandTarget* AudioMenu::getNextCommandTarget()
{
	return findFirstTargetParentComponent();
}

void AudioMenu::getAllCommands(Array<CommandID>& c)
{
	Array<CommandID> commands{ CommandIDs::configureAudio };
	c.addArray(commands);
}

void AudioMenu::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
		case CommandIDs::configureAudio:
			result.setInfo("Audio Options...", "Open audio settings menu.", "Menu", 0);
			result.addDefaultKeypress('p', ModifierKeys::ctrlModifier);
			break;
		default: break;
	}
}

bool AudioMenu::perform(const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case CommandIDs::configureAudio:
		openAudioOptionsMenu();
		break;
	default:
		return false;
	}

	return true;
}

void AudioMenu::openAudioOptionsMenu()
{
}
