#include "../Engine/debug.h"
#include "iconInputComponent.h"
#include <iostream>
#include <string>

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

iconInputComponent::iconInputComponent(Desktop& dT, Database* dB, sf::Image& bS) 
	: theDesktop_(dT), theDatabase_(dB), buttonSheet_(bS) {

}



void iconInputComponent::recieveMessage(msgType msg) {
	// Case: Double Clicked Console Icon
	if (msg.compare(OPEN_THE_CONSOLE) == 0) {
		WindowInterface* consoleWindow = 
			new Window(600, 500, sf::Color(51, 50, 161));
		spawnConsole(consoleWindow, consoleWindow->getInputHandler(), 
			theDesktop_.getNodeState(), buttonSheet_, 300, 400);
		theDesktop_.addWindow(consoleWindow);
	}
	else if (msg.compare(OPEN_THE_FILE) == 0) {
        ppc::WindowInterface* FileWindow =
            new ppc::Window(500, 500, sf::Color(200, 200, 200));
        ppc:spawnFile(FileWindow, FileWindow->getInputHandler(),
            theDesktop_.getNodeState(), buttonSheet_, 100, 200);
        theDesktop_.addWindow(FileWindow);
	}
	else if (msg.compare(OPEN_THE_SETTINGS) == 0) {
		cout << "DEBUG: Implement and open the settings" << endl;
	}
	else if (msg.compare(OPEN_THE_CHAT) == 0) {
		cout << "DEBUG: Implement and open the chat" << endl;
	}
	else if (msg.compare(OPEN_THE_SEARCH) == 0) {
		WindowInterface* databaseWindow =
			new Window(800, 600, sf::Color(200, 200, 200));
		spawnDatabase(databaseWindow, databaseWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
		theDesktop_.addWindow(databaseWindow);
		


	}
	else if (msg.compare(OPEN_THE_PIPELINE) == 0) {
		cout << "DEBUG: Implement and open the pipeline" << endl;
		ppc::WindowInterface* piplineWindow =
			new ppc::Window(800, 600, sf::Color(200, 200, 200));
		ppc::spawnPipeline(piplineWindow, piplineWindow->getInputHandler(), theDatabase_, buttonSheet_, 100, 200);
		theDesktop_.addWindow(piplineWindow);
	}
	else if (msg.compare(OPEN_THE_HELP) == 0) {
		cout << "DEBUG: Implement and open the help" << endl;
	}
	else if (msg.compare(OPEN_THE_BROWSER) == 0) {
		cout << "DEBUG: Implement and open the browser" << endl;
	}
	else if (msg.compare(OPEN_THE_EXPLORER) == 0) {
		cout << "DEBUG: Implement and open the explorer" << endl;
	}
}

iconInputComponent::~iconInputComponent() {

}

bool iconInputComponent::registerInput(sf::Event& ev) {
	return true;
}

