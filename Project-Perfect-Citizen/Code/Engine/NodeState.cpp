#include "debug.h"
#include <iostream>
#include "baseFileType.h"
#include "NodeState.h"
#include "World.h"
#include "desktop.h"
#include "SubjectObsvr.h"

ppc::NodeState::NodeState() {

}

ppc::NodeState::NodeState(const NodeState& other) {
	this->root = other.root;
	this->cwd = other.cwd;
	this->workingDirectory = other.workingDirectory;
	this->lastLsNode = other.lastLsNode;
	this->dirString = other.dirString;
    NodeState* globalNodeState = World::getCurrDesktop().getNodeState();
    if ((this != globalNodeState)) {
        onOpen_.addObserver(new SubjectObsvr(globalNodeState->onOpen()));
    }
}

ppc::NodeState::~NodeState() {

}

void ppc::NodeState::popWorking()
{
	this->workingDirectory.pop_back();
}

void ppc::NodeState::pushWorking(std::string filename)
{
	this->workingDirectory.push_back(filename);
}

void ppc::NodeState::printWorking()
{
    std::string pwd = "";
	for (auto iter: this->workingDirectory) {
		if (iter != "/") {
			pwd += (iter + "/");
		}
		else {
			pwd += iter;
		}
		
	}
	std::cout << pwd << std::endl;
}

void ppc::NodeState::setUp()
{
	this->workingDirectory.push_back("/");
	//TODO: FIX MEMORY LEAK! (This one is particularly massive per leak)
	BaseFileType* newRoot = new BaseFileType(ppc::FileType::Directory);
	newRoot->contents["."] = newRoot;
	newRoot->contents[".."] = newRoot;
	this->root = newRoot;
	this->cwd = newRoot;
	this->lastLsNode = newRoot;
     
}

void ppc::NodeState::setCwd(ppc::BaseFileType* newCwd)
{
	this->cwd = newCwd;

    Event ev;
    ev.type = ev.OpenType;
    ev.open.winType = ev.open.Folder;
    ev.open.file = newCwd;
    ev.open.success = true;
    onOpen_.sendEvent(ev);
}


void ppc::NodeState::readFile(const std::string& filename) {
    BaseFileType* file = getCwd()->findElement(filename); 
    std::string fileResourcePath = file->getFileData();
    file->readFile(filename, fileResourcePath);

    Event ev;
    ev.type = ev.OpenType;
    ev.open.winType = ev.open.File;
    ev.open.file = file;
    ev.open.success = true;
    onOpen_.sendEvent(ev);
}

ppc::BaseFileType* ppc::NodeState::getCwd()
{
	return this->cwd;
}

ppc::BaseFileType * ppc::NodeState::getRoot()
{
	return this->root;
}

void ppc::NodeState::moveToRoot()
{
	this->workingDirectory.clear();
	this->workingDirectory.push_back("/");
	this->cwd = this->root;
}

std::vector<std::string> ppc::NodeState::getPwdVector()
{
	return this->workingDirectory;
}

void ppc::NodeState::setLastLsNode(BaseFileType * node)
{
	this->lastLsNode = node;
	this->dirString = node->baseDirString;
}

std::string ppc::NodeState::getDirString()
{
	return this->dirString;
}

