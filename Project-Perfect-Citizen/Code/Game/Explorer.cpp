#include "Explorer.h"

#include <SFML/Graphics/Image.hpp>

#include "../Engine/WindowInterface.h"
#include "../Engine/ScrollBarDeco.h"
#include "../Engine/World.h"

#include "TreeCommands.h"
#include "TextDisplayBuilder.h"
#include "buttonRenderComponent.h"
#include "textLabelComponent.hpp"
#include "explorerFileInputComponent.h"
#include "explorerFolderInputComponent.h"


#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
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

std::vector<Entity> Explorer::createVectorFrame(std::vector<std::string> filenames) {

	sf::Font font;
	font.loadFromFile(resourcePath() + "consola.ttf");

	int padding = 125;
	std::vector<Entity> explorerFrame;
	int numRows = 1;

	for (int i = 0; i != filenames.size(); ++i) {
		if (filenames.at(i).compare(".") == 0) {
			filenames.erase(filenames.begin() + i);
		}
	}

	for (unsigned int i = 0, j = 0, k = 0; i < filenames.size(); ++i, ++k) {
		if (k % 5 == 0 && k != 0) {
			++j;
			numRows++;
			k = 0;
		}
			Entity example;
			/* Case: FILE*/
			if (hasEnding(filenames.at(i), ".txt") || hasEnding(filenames.at(i), ".jpg")) {
				buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet_, 0, 0, 1, 3);
				IconRender->renderPosition(sf::Vector2f(static_cast<float>(k * padding), static_cast<float>(j * padding)));
				textLabelComponent* label = new textLabelComponent(font, sf::Color::Black, float(k * padding), float(j * padding + 0.5 * 128), 10, filenames.at(i));
				explorerFileInputComponent* IconInput = new explorerFileInputComponent(theDesktop_, windowToWorkOn_, windowToWorkOn_->getInputHandler(), 
					theFileTree_, buttonSheet_, IconRender->getSprite()->getGlobalBounds(), filenames.at(i));
				example.addComponent(IconRender);
				example.addComponent(label);
				example.addComponent(IconInput);
			}
			/*else if (hasEnding(filenames.at(i), ".jpg")) {
				// Use a different sprite
			}*/
			/* Case: FOLDER*/
			else {
				buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet_, 0, 9, 1, 1);
				IconRender->renderPosition(sf::Vector2f(static_cast<float>(k * padding), static_cast<float>(j * padding)));
				textLabelComponent* label = new textLabelComponent(font, sf::Color::Black, float(k * padding), float(j * padding + 0.5 * 128), 12, filenames.at(i));
				explorerFolderInputComponent* IconInput = new explorerFolderInputComponent(theDesktop_, windowToWorkOn_, windowToWorkOn_->getInputHandler(),
					theFileTree_, buttonSheet_, iconSheet_, IconRender->getSprite()->getGlobalBounds(), filenames.at(i));
				example.addComponent(IconRender);
				example.addComponent(label);
				example.addComponent(IconInput);
			}
			explorerFrame.push_back(example);

	}
	windowToWorkOn_->setSize(windowToWorkOn_->getSize().x, numRows * 125);
	return explorerFrame;
}

void Explorer::renderTopFrame() {
	for (unsigned int i = 0; i < explorerHistory_.top().size(); ++i) {
		windowToWorkOn_->addEntity(explorerHistory_.top().at(i));
	}
 
}

void Explorer::updateExplorerDisplay() {
	std::vector<std::string> firstLsCommand;
	std::string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(theFileTree_, firstLsCommand);

	std::string rawDirString = theFileTree_.getDirString();
	std::string delimiter = "@";
	size_t pos = 0;
	std::string token;
	std::vector<std::string> files;

	while ((pos = rawDirString.find(delimiter)) != std::string::npos) {
		token = rawDirString.substr(0, pos);
		files.push_back(token);
		rawDirString.erase(0, pos + delimiter.length());
	}

	explorerHistory_.push(createVectorFrame(files));
	renderTopFrame();
}

