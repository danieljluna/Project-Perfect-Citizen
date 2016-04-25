#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>
#include <string>
#include "../Engine/desktop.h"
#include "../Game/emailExtraction.hpp"
#include "../Engine/Audio/AudioQueue.h"


using namespace ppc;
const string MOUSE_DOWN_CODE = "MDC";
const string MOUSE_RELEASED_CODE = "MRC";
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const string OPEN_THE_CONSOLE = "OTC";
const string OPEN_THE_FILE = "OTF";
const string OPEN_THE_SETTINGS = "OTS";
const string OPEN_THE_CHAT = "OTCH";
const string OPEN_THE_SEARCH = "OTSER";
const string OPEN_THE_PIPELINE = "OTP";
const string OPEN_THE_HELP = "OTH";
const string OPEN_THE_BROWSER = "OTB";
const string OPEN_THE_EXPLORER = "OTE";
const string OPEN_THE_EMAIL = "OTEM";

iconInputComponent::iconInputComponent(Desktop& dT, Database* dB, Inbox& ib, sf::Image& bS, sf::Image& iS)
	: theDesktop_(dT), theDatabase_(dB), theInbox_(ib), buttonSheet_(bS), iconSheet_(iS), que(5) {
        

}



void iconInputComponent::recieveMessage(msgType msg) {
	// Case: Double Clicked Console Icon
	if (msg.compare(OPEN_THE_CONSOLE) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			WindowInterface* consoleWindow =
				new Window(500, 2000, sf::Color(0, 0, 0));
			spawnConsole(theDesktop_, consoleWindow, consoleWindow->getInputHandler(),
				*theDesktop_.getNodeState(), buttonSheet_, 200, 200);
			theDesktop_.addWindow(consoleWindow);
			openedWindow = consoleWindow;
		}
		
	}
	else if (msg.compare(OPEN_THE_FILE) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* FileWindow =
				new ppc::Window(500, 500, sf::Color(255, 255, 255));
			spawnFile(FileWindow, FileWindow->getInputHandler(),
				*theDesktop_.getNodeState(), buttonSheet_, 100, 200, "CHANGE_ME.JPG", "DesktopContent/Desktop1/3-29-12-184.jpg");
			theDesktop_.addWindow(FileWindow);
			openedWindow = FileWindow;
		}
	}
	else if (msg.compare(OPEN_THE_SETTINGS) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* ErrorMsgWindow =
				new ppc::Window(500, 150, sf::Color(170, 170, 170));
			spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
			theDesktop_.addWindow(ErrorMsgWindow);
			openedWindow = ErrorMsgWindow;
		}
	}
	else if (msg.compare(OPEN_THE_CHAT) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* ErrorMsgWindow =
				new ppc::Window(500, 150, sf::Color(170, 170, 170));
			spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Error: Invalid permissions level.");
			theDesktop_.addWindow(ErrorMsgWindow);
			openedWindow = ErrorMsgWindow;
		}
	}
	else if (msg.compare(OPEN_THE_SEARCH) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			WindowInterface* databaseWindow =
				new Window(800, 600, sf::Color(200, 200, 200));
			spawnDatabase(databaseWindow, databaseWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
			theDesktop_.addWindow(databaseWindow);
			openedWindow = databaseWindow;
		}
	}
	else if (msg.compare(OPEN_THE_PIPELINE) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* piplineWindow =
				new ppc::Window(800, 600, sf::Color(200, 200, 200));
			ppc::spawnPipeline(piplineWindow, piplineWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
			theDesktop_.addWindow(piplineWindow);
			openedWindow = piplineWindow;
            Event ev;
            ev.type = Event::FloppyType;
            ev.floppy.frame = 0;
            ev.floppy.sequence = 0;
            onOpen_.sendEvent(ev);
		}
	}
    else if (msg.compare(OPEN_THE_HELP) == 0) {
         ppc::WindowInterface* helpWindow =
         new ppc::Window(600, 700, sf::Color(200,200,200));
         spawnHelp(helpWindow, helpWindow->getInputHandler(), buttonSheet_, 100, 100);
         theDesktop_.addWindow(helpWindow);
         openedWindow = helpWindow;
     }
	else if (msg.compare(OPEN_THE_BROWSER) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* ErrorMsgWindow =
				new ppc::Window(500, 150, sf::Color(170, 170, 170));
			spawnPromptMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 100, 200, "Prompt: please enter password");
            que.addSound("prompt", "Notification_Prompt.wav");
            que.playSound(0);
            que.popAndPlay();
			theDesktop_.addWindow(ErrorMsgWindow);
			openedWindow = ErrorMsgWindow;
		}
	}
	else if (msg.compare(OPEN_THE_EXPLORER) == 0) {
		//if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			//theDesktop_.focusWindow(openedWindow);
		//}
		//else {
			ppc::WindowInterface* explorerWindow =
				new ppc::Window(600, 350, sf::Color(255, 255, 255));
			spawnExplorer(theDesktop_, explorerWindow, explorerWindow->getInputHandler(), *theDesktop_.getNodeState(), buttonSheet_, iconSheet_, 100, 200);
			theDesktop_.addWindow(explorerWindow);
			openedWindow = explorerWindow;
		//}
	}
	else if (msg.compare(OPEN_THE_EMAIL) == 0) {
		if (openedWindow != nullptr && theDesktop_.isWindow(openedWindow)) {
			theDesktop_.focusWindow(openedWindow);
		}
		else {
			ppc::WindowInterface* inboxWindow =
				new ppc::Window(600, 400, sf::Color(200, 200, 200));
			ppc::spawnInbox(theDesktop_, inboxWindow, inboxWindow->getInputHandler(), buttonSheet_, 100, 200, theDesktop_.getInbox());
			theDesktop_.addWindow(inboxWindow);
			openedWindow = inboxWindow;
		}
	}
}

void ppc::iconInputComponent::recieveMessage(ppc::Event ev) {
	switch (ev.type) {
	case Event::EventTypes::ButtonType:

		if (ev.buttons.isReleased) cout << "isReleased was true";
		else cout << "isReleased was false";

		if (ev.buttons.isRight) cout << "isRight was true";
		else cout << "isRight was false";

		if (ev.buttons.isReleased && ev.buttons.isRight) {

			std::vector<std::string> elementNames;
			std::vector<bool(*)(Desktop*, Event ev)> elementFunctions;
			elementNames.push_back("Open");
			ppc::WindowInterface* ContextMenu = nullptr;

			if (ev.buttons.openEmail) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openHelp == true) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openPipeline) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openBrowser) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openChat) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openFolder) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openSearch) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openSettings) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openConsole) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			else if (ev.buttons.openHarddrive) {
				ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
				elementFunctions.push_back(&(ppc::make_icon_window));
				spawnContextMenu(theDesktop_, ContextMenu, ContextMenu->getInputHandler(), elementNames,
					elementFunctions, ev.buttons.mouseX, ev.buttons.mouseY);
			}
			theDesktop_.addWindow(ContextMenu);
		}
		break;
	default:
		break;
	}
}


iconInputComponent::~iconInputComponent() {

}

bool iconInputComponent::registerInput(sf::Event ev) {
	return true;
}

bool ppc::make_icon_window(Desktop* ptr, ppc::Event ev) {
	cout << " open the corresponding window " << endl;
	return true;
}
