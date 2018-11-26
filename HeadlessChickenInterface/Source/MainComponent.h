/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginViewport.h"
#include "AudioMenu.h"
#include "SecondaryComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
						public ApplicationCommandTarget
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
	//Component overrides
    void paint (Graphics&) override;
    void resized() override;
	//AudioComponent overrides
	void prepareToPlay(int, double) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	//ApplicationCommandTarget overrides
	ApplicationCommandTarget* getNextCommandTarget() override;
	void getAllCommands(Array<CommandID>& c) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	bool perform(const InvocationInfo& info) override;
	//Class specific functions
	void showAudioDeviceSelector();
	void openAudioOptionsMenu();
	void openPluginBrowser();

private:
    //==============================================================================
    // Your private member variables go here...
	String currentSizeAsString;
	AudioMenu am;
	PluginViewport plugs;
	AudioDeviceSelectorComponent audioSetupComp;

	class InvokedWindow : public DocumentWindow
	{
	public:
		InvokedWindow(AudioDeviceSelectorComponent * s) : DocumentWindow("Configure Audio",
			Desktop::getInstance().getDefaultLookAndFeel()
			.findColour(ResizableWindow::backgroundColourId),
			DocumentWindow::allButtons)
		{
			setUsingNativeTitleBar(false);
			setContentOwned(new SecondaryComponent(s), true);

			centreWithSize(getWidth(), getHeight());
			setResizable(true, true);
			setVisible(true);
		}

		void closeButtonPressed() override
		{
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
			setVisible(false);
		}

		/* Note: Be careful if you override any DocumentWindow methods - the base
		class uses a lot of them, so by overriding you might break its functionality.
		It's best to do all your work in your content component instead, but if
		you really have to override any DocumentWindow methods, make sure your
		subclass also calls the superclass's method.
		*/

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InvokedWindow)
	};

	std::unique_ptr<InvokedWindow> invokedWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
