#include "World.h"
#include "desktop.h" //remember to remove this if including in .h
#include "../Game/Quitter.h"

ppc::World::World() {
	screen = nullptr;
}

ppc::World::World(sf::RenderWindow& gameScreen) {
	screen = &gameScreen;
}

ppc::World::World(sf::RenderWindow& gameScreen, ppc::Desktop& d) {
	screen = &gameScreen;
	currDesktop = &d;
}

ppc::World::~World() {
}

void ppc::World::setGameScreen(sf::RenderWindow& gameScreen) {
	screen = &gameScreen;
}

void ppc::World::setCurrDesktop(ppc::Desktop &d) {
	currDesktop = &d;
}

ppc::Desktop* ppc::World::getCurrDesktop() {
	return currDesktop;
}

bool ppc::World::runDesktop(ppc::Desktop &myDesktop) {
	if (screen == nullptr) return false;

	// Go into main game loop
	sf::Clock deltaTime;
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	while (screen->isOpen()) {
		if (quitter) {
			return false;
		}
		//Process sf::events
		sf::Event event;
		while (screen->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen->close();
			} else if (event.type == sf::Event::KeyPressed) {
				//Close
				if ((event.key.code == sf::Keyboard::Period) && (event.key.alt)) {
					return false;
				}
			}

			//Input phase
			myDesktop.registerInput(event);
		}

		sf::Time elapsed = deltaTime.getElapsedTime();
		while (elapsed > framePeriod) {
			screen->clear(sf::Color::Black);
			sf::Time dt = deltaTime.restart();
			myDesktop.update(dt);
			elapsed -= framePeriod;
		}
		myDesktop.refresh();
		screen->draw(myDesktop);
		screen->display();
	}
	return false;
}

bool ppc::World::runCurrDesktop() {
	return runDesktop(*(this->currDesktop));
}

std::ostream& ppc::operator<<(std::ostream& out, const World& world) {
	if (world.currDesktop == nullptr) return out;
	//write to out
	return out;
}

std::istream& ppc::operator>>(std::istream& in, const World& world) {
	if (world.currDesktop != nullptr) {}
	//read from in. ask if we need to make the new Desktop here or not?
	return in;
}