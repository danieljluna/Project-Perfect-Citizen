#include "Explorer.h"

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

using namespace ppc;

Explorer::Explorer(WindowInterface*& win, NodeState& ns, sf::Image& bS, sf::Image& iS) : windowToWorkOn_(win), theFileTree_(ns), buttonSheet_(bS), iconSheet_(iS) {

	updateExplorerDisplay();

}

vector<Entity> Explorer::createVectorFrame(vector<string> filenames) {

	sf::Font font;
	font.loadFromFile(resourcePath() + "consola.ttf");

	vector<Entity> explorerFrame;
	for (int i = 0, j = 0 ; i < filenames.size(); ++i) {
			Entity example;
			buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet_, 0, 9, 1, 1);
			IconRender->renderPosition(sf::Vector2f(i * 100, j * 100));

			textLabelComponent* label = new textLabelComponent(font, sf::Color::Black, i * 100, j * 100 + 0.5 * 128, 12, filenames.at(i));
			explorerFolderInputComponent* IconInput = new explorerFolderInputComponent(windowToWorkOn_->getInputHandler(), theFileTree_, IconRender->getSprite()->getGlobalBounds(), filenames.at(i));
			example.addComponent(IconRender);
			example.addComponent(label);
			example.addComponent(IconInput);
			explorerFrame.push_back(example);

	}
	return explorerFrame;
}

void Explorer::renderTopFrame() {
	for (int i = 0; i < explorerHistory_.top().size(); ++i) {
		windowToWorkOn_->addEntity(explorerHistory_.top().at(i));
	}
}

void Explorer::updateExplorerDisplay() {
	std::vector<string> firstLsCommand;
	string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(theFileTree_, firstLsCommand);

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

	explorerHistory_.push(createVectorFrame(files));
	renderTopFrame();
}

