/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : 
	audioSetupComp(
		deviceManager, //Device Manager
		0,     // minimum input channels
		256,   // maximum input channels
		0,     // minimum output channels
		256,   // maximum output channels
		true, // ability to select midi inputs
		true, // ability to select midi output device
		true, // treat channels as stereo pairs
		false), // hide advanced options
	am(&audioSetupComp)
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

void MainComponent::prepareToPlay(int, double) {}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {}

void MainComponent::releaseResources() {}

void MainComponent::showAudioDeviceSelector()
{
	
}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
	Array<CommandID> commands{ AudioMenu::configureAudio, AudioMenu::addPlugin };
	c.addArray(commands);
}

ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	return &am;
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
	case AudioMenu::configureAudio:
		result.setInfo("Audio Options...", "Open audio settings menu.", "Menu", 0);
		result.addDefaultKeypress('p', ModifierKeys::ctrlModifier);
		break;
	case AudioMenu::addPlugin:
		result.setInfo("Add New Plugin...", "Open file browser for vst plugin", "Browser", 0);
		result.addDefaultKeypress('a', ModifierKeys::ctrlModifier);
		break;
	default: break;
	}
}


bool MainComponent::perform(const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case AudioMenu::configureAudio:
		openAudioOptionsMenu();
		break;
	case AudioMenu::addPlugin:
		openPluginBrowser();
		break;
	default:
		return false;
	}

	return true;
}

void MainComponent::openAudioOptionsMenu()
{
	invokedWindow.reset(new InvokedWindow(&audioSetupComp));
}

void MainComponent::openPluginBrowser()
{
	
}
