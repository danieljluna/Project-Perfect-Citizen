#include "consoleUpdateComponent.h"
#include "TreeCommands.h"


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
    string delimiter = " ";
    size_t last = 0;
    size_t next = 0;
    string token;
    while ((next = lastCommand.find(delimiter, last)) != string::npos) {
        token = lastCommand.substr(last, next-last);
        commandVec.push_back(token);
        last = next + 1;
    }
    
   /* size_t pos = 0;
    string token;
    while ((pos = lastCommand.find(delimiter)) != std::string::npos) {
        token = lastCommand.substr(0, pos);
        cout << token << endl;
        commandVec.push_back(token);
        lastCommand.erase(0, pos + delimiter.length());
    }*/
}

void consoleUpdateComponent::update(sf::Time& deltaTime) {
	if (canParse) {
        commandFn makeFunction = findFunction(commandVec.at(0));
        makeFunction(fileTree, commandVec);
        
		//if (commandVec.at(0) == "pwd") { fileTree.printWorking(); }
        toggleParsing();
        commandVec.clear();
	}
	//fileTree.printWorking();
}