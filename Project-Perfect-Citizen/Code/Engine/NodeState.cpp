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
	BaseFileType* newRoot = new BaseFileType(ppc::FileType::Directory);
	newRoot->contents["."] = newRoot;
	newRoot->contents[".."] = newRoot;
	this->root = newRoot;
	this->cwd = newRoot;
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
