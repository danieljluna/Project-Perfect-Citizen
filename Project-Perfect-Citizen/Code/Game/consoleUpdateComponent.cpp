#include "../Engine/debug.h"

#include "consoleUpdateComponent.h"
#include "TreeCommands.h"

using namespace ppc;

const std::string MOUSE_DOUBLE_CLICK_CODE = "MDDC";

consoleUpdateComponent::consoleUpdateComponent(ppc::NodeState& ns) 
	: fileTree(ns) {
	canParse = false;
	std::vector<std::string> firstLsCommand;
	std::string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(fileTree, firstLsCommand);
}

consoleUpdateComponent::~consoleUpdateComponent() {

}

void consoleUpdateComponent::toggleParsing() {
	canParse = !canParse;
}

void consoleUpdateComponent::executeCommand(std::vector<std::string> cmd) {
	toggleParsing();
	commandVec = cmd;
}

void consoleUpdateComponent::update(sf::Time& deltaTime) {
	if (canParse) {
		try {
			commandFn commandFunction = findFunction(commandVec.at(0));
			commandFunction(fileTree, commandVec);
			toggleParsing();
			commandVec.clear();
		} catch (std::runtime_error e) {
			toggleParsing();
			commandVec.clear();
			return;
		}
	}
}