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
