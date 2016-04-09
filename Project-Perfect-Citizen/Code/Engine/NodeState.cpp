#include "debug.h"
#include <iostream>
#include "baseFileType.h"
#include "NodeState.h"

ppc::NodeState::NodeState() {

}

ppc::NodeState::NodeState(const NodeState& other) {
	this->root = other.root;
	this->cwd = other.cwd;
	this->workingDirectory = other.workingDirectory;
	this->lastLsNode = other.lastLsNode;
	this->dirString = other.dirString;
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
	for (auto& iter: this->workingDirectory) {
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

