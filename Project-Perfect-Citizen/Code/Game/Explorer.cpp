#include "Explorer.h"

#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

using namespace ppc;

Explorer::Explorer(Desktop& dT, WindowInterface* win, NodeState& ns, sf::Image& bS, sf::Image& iS) : theDesktop_(dT), windowToWorkOn_(win), theFileTree_(ns), buttonSheet_(bS), iconSheet_(iS) {
	updateExplorerDisplay();
}

bool hasEnding(std::string const &fileName, std::string const &extension) {
	if (fileName.length() >= extension.length()) {
		return (0 == fileName.compare(fileName.length() - extension.length(), extension.length(), extension));
	}
	else {
		return false;
	}
}

vector<Entity> Explorer::createVectorFrame(vector<string> filenames) {

	sf::Font font;
	font.loadFromFile(resourcePath() + "consola.ttf");

	int padding = 100;
	vector<Entity> explorerFrame;
	int numRows = 1;
	for (int i = 0, j = 0, k = 0; i < filenames.size(); ++i, ++k) {
		if (filenames.at(i).compare("CP") == 0) cout << "BOOT TO TITLE SCREEN" << endl;
		if (k % 5 == 0 && k != 0) {
			++j;
			numRows++;
			k = 0;
		}
			Entity example;
			/* Case: FILE*/
			if (hasEnding(filenames.at(i), ".txt") || hasEnding(filenames.at(i), ".jpg")) {
				buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet_, 0, 0, 1, 3);
				IconRender->renderPosition(sf::Vector2f(k * padding, j * padding));
				textLabelComponent* label = new textLabelComponent(font, sf::Color::Black, k * padding, j * padding + 0.5 * 128, 10, filenames.at(i));
				explorerFileInputComponent* IconInput = new explorerFileInputComponent(theDesktop_, windowToWorkOn_->getInputHandler(), 
					theFileTree_, buttonSheet_, IconRender->getSprite()->getGlobalBounds(), filenames.at(i));
				example.addComponent(IconRender);
				example.addComponent(label);
				example.addComponent(IconInput);
			}
			/* Case: FOLDER*/
			else {
				buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet_, 0, 9, 1, 1);
				IconRender->renderPosition(sf::Vector2f(k * padding, j * padding));
				textLabelComponent* label = new textLabelComponent(font, sf::Color::Black, k * padding, j * padding + 0.5 * 128, 12, filenames.at(i));
				explorerFolderInputComponent* IconInput = new explorerFolderInputComponent(theDesktop_, windowToWorkOn_, windowToWorkOn_->getInputHandler(),
					theFileTree_, buttonSheet_, iconSheet_, IconRender->getSprite()->getGlobalBounds(), filenames.at(i));
				example.addComponent(IconRender);
				example.addComponent(label);
				example.addComponent(IconInput);
			}
			explorerFrame.push_back(example);

	}
	windowToWorkOn_->setSize(windowToWorkOn_->getSize().x, numRows * 100);
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

