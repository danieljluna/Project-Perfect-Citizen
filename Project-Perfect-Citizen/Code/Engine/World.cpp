
#include <fstream>
#include <string>
#include "World.h"
#include "desktop.h"
#include "Window.h"
#include "NodeState.h"
#include "../Game/desktopExtractionComponent.hpp"
#include "../Game/Quitter.h"
#include "../Game/Inbox.h"
#include "../Game/Email.h"
#include "../Game/emailExtraction.hpp"
#include "../Library/json/json.h"
#include "debug.h"

using namespace ppc;

sf::RenderWindow* World::screen_ = nullptr;
Desktop* World::currDesktop_ = nullptr;
std::map<World::DesktopList, std::string> World::desktopFileMap = {
    {World::Count, ""}  //Empty pairing of Count to string.
};
bool World::quitter = false;


void World::setGameScreen(sf::RenderWindow& gameScreen) {
	screen_ = &gameScreen;
}

void World::setCurrDesktop(Desktop &d) {
	currDesktop_ = &d;
}

sf::RenderWindow& World::getGameScreen() {
	return *screen_;
}

Desktop& World::getCurrDesktop() {
	return *currDesktop_;
}

bool World::runDesktop(Desktop &myDesktop) {
	if (screen_ == nullptr) return false;
	// Go into main game loop

    quitter = false;

	sf::Clock deltaTime;
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	while (screen_->isOpen() && !quitter) {
		//Process sf::events
		sf::Event event;
		while (screen_->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen_->close();
			} else if (event.type == sf::Event::KeyPressed) {
				//Close
				if ((event.key.code == sf::Keyboard::Period) && (event.key.alt)) {
                    quitDesktop();
				}
			}

			//Input phase
			myDesktop.registerInput(event);
		}

		sf::Time elapsed = deltaTime.getElapsedTime();
		while (elapsed > framePeriod) {
			screen_->clear(sf::Color::Black);
			sf::Time dt = deltaTime.restart();
			myDesktop.update(dt);
			elapsed -= framePeriod;
		}
		myDesktop.refresh();
		screen_->draw(myDesktop);
		screen_->display();
	}
	return false;
}

bool World::loadDesktop(DesktopList desk) {
    return loadDesktop(desktopFileMap.at(desk));
}

bool World::runCurrDesktop() {
	return runDesktop(*currDesktop_);
}


void World::quitDesktop() {
    quitter = true;
}


bool World::loadDesktop(std::string filename) {
    std::ifstream in(filename);

    bool result = false;

    if (in.is_open()) {
        if (currDesktop_ != nullptr) {
            delete currDesktop_;
            currDesktop_ = nullptr;
        }

        currDesktop_ = new Desktop();
        in >> *currDesktop_;

        result = true;
    }

    return result;
}
