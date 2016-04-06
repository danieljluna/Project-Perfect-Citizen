#include "World.h"
#include "desktop.h" 
#include "../Game/Quitter.h"

ppc::World::World() {
	screen_ = nullptr;
	currDesktop_ = nullptr;
}

ppc::World::World(sf::RenderWindow& gameScreen) {
	screen_ = &gameScreen;
}

ppc::World::World(sf::RenderWindow& gameScreen, ppc::Desktop& d) {
	screen_ = &gameScreen;
	currDesktop_ = &d;
}

ppc::World::~World() {
}

void ppc::World::setGameScreen(sf::RenderWindow& gameScreen) {
	screen_ = &gameScreen;
}

void ppc::World::setCurrDesktop(ppc::Desktop &d) {
	currDesktop_ = &d;
}

sf::RenderWindow * ppc::World::getGameScreen() {
	return screen_;
}

ppc::Desktop* ppc::World::getCurrDesktop() {
	return currDesktop_;
}

bool ppc::World::runDesktop(ppc::Desktop &myDesktop) {
	if (screen_ == nullptr) return false;

	// Go into main game loop
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
                    quitSection();
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

bool ppc::World::runCurrDesktop() {
	return runDesktop(*(this->currDesktop_));
}

std::istream& ppc::operator>>(std::istream& in, const World& world) {
	if (world.currDesktop_ == nullptr) {
		


	} else if (world.currDesktop_ != nullptr) {



	}


	return in;
}