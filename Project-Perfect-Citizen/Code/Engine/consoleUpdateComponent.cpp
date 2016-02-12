#include "consoleUpdateComponent.h"


const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";

consoleUpdateComponent::consoleUpdateComponent(ppc::NodeState& ns) : fileTree(ns) {
	canParse = false;
}

consoleUpdateComponent::~consoleUpdateComponent() {

}

void consoleUpdateComponent::toggleParsing() {
	canParse = !canParse;
}

void consoleUpdateComponent::executeCommand(string str) {
	toggleParsing();
	lastCommand = str;
}

void consoleUpdateComponent::update(sf::Time& deltaTime) {
	if (canParse) {
		if (lastCommand == "pwd") { fileTree.printWorking(); }
		toggleParsing();
	}
	//fileTree.printWorking();
}