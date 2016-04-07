#ifdef WINDOWS_MARKER
	#define resourcePath() std::string("Resources/")
#else
	#include "ResourcePath.hpp"
#endif

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
	if (currDesktop_ != nullptr) delete currDesktop_;
	if (screen_ != nullptr) delete screen_;
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

void ppc::World::switchDesktop(ppc::Desktop& newDeskop) {
	if (currDesktop_ == nullptr) {
		currDesktop_ = &newDeskop;
	} else {
		delete currDesktop_;
		currDesktop_ = &newDeskop;
	}

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


std::istream& ppc::operator>>(std::istream& in, World& world) {
	std::string line;

	ppc::Desktop* importDesktop = new Desktop();
	Window* bkgndWindow =
		new Window(1800, 1000, sf::Color(0, 0, 0));
	importDesktop->addBkgndWindow(bkgndWindow);

	NodeState* ft = new NodeState();
	ft->setUp();
	importDesktop->setNodeState(*ft);


	while (std::getline(in,line)) {
		size_t pos = line.find_first_of(":");
		std::string key = line.substr(0, pos);
		std::string file = line.substr(pos + 2);
		DEBUGF("wc", key << ": " << file);
//remember to tell everyone to use new for Images, 
//Sprites, etc for Desktop stuff because now Desktop now expects it.
		if (key == "Icons") {
			sf::Image* iconSheet = new sf::Image();
			iconSheet->loadFromFile(resourcePath() + file);
			importDesktop->setIconSheet(*iconSheet);
		} else if (key == "Buttons") {
			sf::Image* buttonSheet = new sf::Image();
			buttonSheet->loadFromFile(resourcePath() + file);
			importDesktop->setButtonSheet(*buttonSheet);
		} else if (key == "Background") {
			sf::Sprite* wallpaper = new sf::Sprite();
			sf::Texture* bkgndTexture = new sf::Texture();
			bkgndTexture->loadFromFile(resourcePath() + file);
			wallpaper->setTexture(*bkgndTexture);
			wallpaper->setScale(0.7f, 0.7f);
			wallpaper->setPosition(0.f, 0.f);
			importDesktop->addBackgroundCmpnt(importDesktop->getDesktopWindow(), *wallpaper);
		} else if (key == "Filetree") {
			desktopExtractionComponent* desktopFiles = 
				new desktopExtractionComponent(*importDesktop->getNodeState());
			Json::Value parsed = 
				desktopFiles->parseDesktopAsJson(resourcePath() + file, "Desktop");
			delete desktopFiles;
		} else if (key == "Emails") {
			Inbox* theInbox = new Inbox();

			emailExtraction inbox;
			inbox.parseEmailAsJson(resourcePath() + file);

			for (unsigned int i = 0; i < inbox.getSubject().size(); i++) {
				Email testEmail1(inbox.getTo().at(i), 
								inbox.getFrom().at(i), 
								inbox.getSubject().at(i), 
								inbox.getBody().at(i), 
								"image.jpg");
				theInbox->addEmailToList(testEmail1);
			}
			importDesktop->setInbox(*theInbox);
		}	
	}

	world.switchDesktop(*importDesktop);

	return in;
}