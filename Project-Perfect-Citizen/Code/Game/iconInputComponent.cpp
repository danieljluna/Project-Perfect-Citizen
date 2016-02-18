#include "iconInputComponent.h"
#include <iostream>
#include <string>
#include <string>

using namespace std;
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

iconInputComponent::iconInputComponent(ppc::Desktop& dT) 
	: theDesktop_(dT) {

}

void iconInputComponent::recieveMessage(msgType msg) {
	// Case: Double Clicked Console Icon
	if (msg.compare(OPEN_THE_CONSOLE) == 0) {
		ppc::WindowInterface* consoleWindow = 
			new ppc::Window(600, 300, sf::Color(51, 50, 161));
		spawnConsole(consoleWindow, consoleWindow->getInputHandler(), 
			theDesktop_.getNodeState(), 300, 400);
		theDesktop_.addWindow(consoleWindow);
	}
	else if (msg.compare(OPEN_THE_FILE) == 0) {
		cout << "DEBUG: Implement and open the file" << endl;
	}
	else if (msg.compare(OPEN_THE_SETTINGS) == 0) {
		cout << "DEBUG: Implement and open the settings" << endl;
	}
	else if (msg.compare(OPEN_THE_CHAT) == 0) {
		cout << "DEBUG: Implement and open the chat" << endl;
	}
	else if (msg.compare(OPEN_THE_SEARCH) == 0) {
		cout << "DEBUG: Implement and open the search" << endl;
	}
	else if (msg.compare(OPEN_THE_PIPELINE) == 0) {
		cout << "DEBUG: Implement and open the pipeline" << endl;
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

