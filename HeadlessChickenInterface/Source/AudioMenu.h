/*
  ==============================================================================

    AudioMenu.h
    Created: 24 Nov 2018 7:17:12pm
    Author:  Duncan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondaryComponent.h"

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
		configureAudio = 1,
		addPlugin
	};

    AudioMenu(AudioDeviceSelectorComponent * s);
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
	void openPluginBrowser();

private:
	ApplicationCommandManager commandManager;
	std::unique_ptr<MenuBarComponent> menuBar;
	AudioDeviceSelectorComponent * selector;
	Colour currentColour;

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
			JUCEApplication::getInstance()->systemRequestedQuit();
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioMenu)
};
