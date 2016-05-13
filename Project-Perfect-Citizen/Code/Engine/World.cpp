#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include <fstream>

#include "World.h"
#include "desktop.h"

#include "debug.h"
#include "desktop.h"

using namespace ppc;


sf::RenderWindow* World::screen_ = nullptr;
Desktop* World::currDesktop_ = nullptr;
std::map<std::string, World::savGroups> World::saveGroupMap_ = {
    { "Settings]",      World::SettingsTag  },
    { "[State]",        World::StateTag     }
};

std::map<World::DesktopList, std::string> World::desktopFileMap_ = {

    {World::DesktopCount, ""}  //Empty pairing of Count to string.
};

std::map<World::FontList, sf::Font> World::fontMap_ = {
	{World::FontCount, sf::Font()},
	{World::Consola, sf::Font()},
	{World::Micross, sf::Font()},
	{World::VT323Regular, sf::Font()}
};

std::map<World::ReportList, std::string> World::reportListMap_ = {
	{World::DE1A, resourcePath() + "Reports/sampleReport.txt"}
};

bool World::quitter_ = false;

sf::RectangleShape World::tempLoadScreen_ = sf::RectangleShape({ 1000,1000 });
sf::RectangleShape World::tempLoadBar_ = sf::RectangleShape({ 500, 50 });

sf::Image World::loadImage_ = sf::Image();
sf::Texture World::loadTexture_ = sf::Texture();
sf::Sprite World::loadBar_ = sf::Sprite();
sf::Sprite World::loadBarBorder_ = sf::Sprite();
sf::Sprite World::loadingDecal_ = sf::Sprite();

bool World::isLoading_ = false;

Setting World::settings_;

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

    quitter_ = false;

	sf::Clock deltaTime;
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	World::endLoading();
	while (screen_->isOpen() && !quitter_) {
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
    return loadDesktop(desktopFileMap_.at(desk));
}

bool World::runCurrDesktop() {
	return runDesktop(*currDesktop_);
}


void World::quitDesktop() {
    quitter_ = true;
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

void ppc::World::initFontMap() {
	fontMap_.at(World::Consola).loadFromFile(resourcePath() + "consola.ttf");
	fontMap_.at(World::Micross).loadFromFile(resourcePath() + "micross.ttf");
	fontMap_.at(World::VT323Regular).loadFromFile(resourcePath() + "VT323-Regular.ttf");

}

sf::Font& ppc::World::getFont(FontList f) {
	
	return fontMap_.at(f);

}

std::string ppc::World::getReportFile(ReportList rl) {
	return reportListMap_.at(rl);
}


void ppc::World::initLoadScreen() {
    
    loadImage_.loadFromFile(resourcePath() + "World_Sheet.png");
    loadTexture_.loadFromImage(loadImage_);

    loadBar_.setTexture(loadTexture_);
    loadBar_.setPosition(100.f, 500.f);
    loadBar_.setScale(1.f, 1.f);
    loadBar_.setTextureRect({0,4*128, 0, 128});
    loadBar_.setScale(0.75f,0.75f);
    
    
    loadBarBorder_.setTexture(loadTexture_);
    loadBarBorder_.setPosition(100.f, 500.f);
    loadBarBorder_.setScale(1.f, 1.f);
    loadBarBorder_.setTextureRect({0,3*128, 8*128, 128});
    loadBarBorder_.setScale(0.75f,0.75f);
    
    loadingDecal_.setTexture(loadTexture_);
    loadingDecal_.setTextureRect({0,0, 6*128, 3*128});
    loadingDecal_.setPosition(150, 100);

	tempLoadScreen_.setPosition(0.f, 0.f);
	tempLoadScreen_.setFillColor(sf::Color::Black);

	tempLoadBar_.setPosition(225.f, 500.f);
	tempLoadBar_.setFillColor(sf::Color::Red);
	tempLoadBar_.setOutlineColor(sf::Color::Black);
	tempLoadBar_.setOutlineThickness(5.f);

	tempLoadBar_.setSize({ 0.f, 50.f });
}

void ppc::World::startLoading() {
	isLoading_ = true;
	drawLoading();
}

void ppc::World::setLoading(float f) {
	if (f > 1.f || f < 0.f) f = 1.f;
    loadBar_.setTextureRect({0, 4*128, static_cast<int>(1024*f),128});
	tempLoadBar_.setSize({ 500.f * f, 50.f });
	drawLoading();
}

void ppc::World::drawLoading() {
	if (isLoading_ == false) return;
	screen_->clear(sf::Color::Black);
	//screen_->draw(tempLoadScreen_);
	//screen_->draw(tempLoadBar_);
    screen_->draw(loadingDecal_);
    screen_->draw(loadBarBorder_);
    screen_->draw(loadBar_);
	screen_->display();
}

void ppc::World::endLoading() {

	isLoading_ = false;
}


void ppc::World::loadState(std::string filename) {
    filename = resourcePath() + "Saves/" + filename;

    std::ifstream file(filename);

    file >> settings_;

    file.close();
}


void ppc::World::saveState(std::string filename) {
    filename = resourcePath() + "Saves/" + filename;

    std::ofstream file(filename);

    for (auto& mapPair: saveGroupMap_) {
        //Output grouping Tag
        file << '[' << mapPair.first << ']' << std::endl;

        //Output appropriate info
        switch (mapPair.second) {
        case SettingsTag:
            file << settings_ << std::endl << std::endl;
            break;
        case StateTag:
        default:
            break;
        }
    }
    file << settings_;

    file.close();
}
