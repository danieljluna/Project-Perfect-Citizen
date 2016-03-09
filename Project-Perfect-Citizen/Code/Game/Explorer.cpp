#include "Explorer.h"

using namespace ppc;

Explorer::Explorer(WindowInterface*& win, NodeState& ns, sf::Image& bS) : windowToWorkOn_(win), theFileTree_(ns), buttonSheet_(bS) {

	std::vector<string> firstLsCommand;
	string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(ns, firstLsCommand);

	string rawDirString = theFileTree_.getDirString();
	string delimiter = "@";
	size_t pos = 0;
	string token;
	vector<string> files;

	while ((pos = rawDirString.find(delimiter)) != string::npos) {
		token = rawDirString.substr(0, pos);
		files.push_back(token);
		rawDirString.erase(0, pos + delimiter.length());
	}

	for (auto iter = files.begin() +2 ; iter != files.end(); ++iter)
		cout <<  " > " << *iter << " < "<< endl;

	explorerHistory_.push(createVectorFrame());
	renderTopFrame();

}

vector<Entity> Explorer::createVectorFrame() {

	vector<Entity> explorerFrame;

	for (int i = 0 ; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			Entity example;
			spawnBlankLargeButton(example, windowToWorkOn_->getInputHandler(), buttonSheet_, i*100, j*100, 0.25f);
			explorerFrame.push_back(example);
		}
	}
	return explorerFrame;
}

void Explorer::renderTopFrame() {
	for (int i = 0; i < explorerHistory_.top().size(); ++i) {
		windowToWorkOn_->addEntity(explorerHistory_.top().at(i));
	}
}

