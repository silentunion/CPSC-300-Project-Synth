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
		false, // treat channels as stereo pairs
		false), // hide advanced options
	am(&pList),
	browser(13, File(), nullptr, nullptr),
	graph(new AudioProcessorGraph()),
	gEditor(graph.get()),
	plugs(&gEditor)
{
	//keyboard init
	keyboardComp.reset(new MidiKeyboardComponent(keyState, MidiKeyboardComponent::horizontalKeyboard));
	addAndMakeVisible(keyboardComp.get());
	
	//audio init
	graph->enableAllBuses();
	player.setProcessor(graph.get());
	deviceManager.addAudioCallback(&player);
	auto midi = keyboardComp->getName();
	deviceManager.setMidiInputEnabled(midi, true);
	deviceManager.addMidiInputCallback(midi, &player);
	setAudioChannels(2, 2);

	pManager.addDefaultFormats();

	//toolbar init
	addAndMakeVisible(am);

	//plugin viewer init
	addAndMakeVisible(plugs);

	//window init
	setSize (600, 400);
}

MainComponent::~MainComponent()
{
	player.setProcessor(nullptr);
	deviceManager.removeAudioCallback(&player);

	auto midi = keyboardComp->getName();
	deviceManager.setMidiInputEnabled(midi, false);
	deviceManager.removeMidiInputCallback(midi, &player);

	shutdownAudio();
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
	keyboardComp->setBounds(area.removeFromBottom(jmax(60, area.getHeight() / 8)));
	plugs.setBounds(area.removeFromLeft(jmax(80, area.getWidth() / 4)));
	
}

void MainComponent::prepareToPlay(int, double)
{
	//graph->setPlayConfigDetails();
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {}

void MainComponent::releaseResources() 
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
	FileChooserDialogBox dialogBox("Load new plugin-in",
		"",
		browser,
		true,
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId),
		nullptr);

	dialogBox.show();

	//pList.scanAndAddFile(browser.getSelectedFile().getFullPathName(), true, , pManager.getFormat());

}

/*
Adapted from Brett G Porter: 
https://artandlogic.com/2013/02/developing-audio-applications-with-juce-part-1/
On Nov. 26 2018
*/
void MainComponent::resetAudioGraph()
{
	graph->clear();

	auto inputNode  = graph->addNode(
		new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode)
	);
	auto outputNode = graph->addNode(
		new AudioProcessorGraph::AudioGraphIOProcessor(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode)
	);

	graph->addConnection({ {inputNode->nodeID, 0}, {outputNode->nodeID, 1} });
}
