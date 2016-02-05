#include "NodeState.h"

void ppc::NodeState::popWorking()
{
	this->workingDirectory.pop_back();
}

void ppc::NodeState::pushWorking(string filename)
{
	this->workingDirectory.push_back(filename);
}

void ppc::NodeState::printWorking()
{
	string pwd = "";
	for (auto& iter: this->workingDirectory) {
		pwd += (iter + " ");
	}
}

void ppc::NodeState::setUp()
{
	this->workingDirectory.push_back("/");
	BaseFileType* newRoot = new BaseFileType();
	newRoot->contents["."] = newRoot;
	newRoot->contents[".."] = newRoot;
	this->root = newRoot;
	this->cwd = newRoot;
}

ppc::BaseFileType* ppc::NodeState::getCwd()
{
	return this->cwd;
}

ppc::BaseFileType * ppc::NodeState::getRoot()
{
	return this->root;
}
