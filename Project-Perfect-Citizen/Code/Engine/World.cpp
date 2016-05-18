#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include <fstream>

#include "World.h"
#include "desktop.h"

#include "debug.h"
#include "../Engine/SuspiciousFileHolder.h"

using namespace ppc;


sf::RenderWindow* World::screen_ = nullptr;
Desktop* World::currDesktop_ = nullptr;
sf::Transform World::worldTransform_;

std::map<ppc::World::DesktopList, ppc::LevelPacket> World::levelMap_ = {

};

std::map<std::string, World::savGroups> World::saveGroupMap_ = {
    { "Settings",      World::SettingsTag  },
    { "State",         World::StateTag     }
};

World::DesktopList World::currDesktopEnum_ = DE0;
World::ReportType World::currReportType_ = A;
std::map<World::DesktopList, std::string> World::desktopFileMap_ = {
	{World::DE0, ""},
    {World::DesktopCount, ""}  //Empty pairing of Count to string.
};

std::map<World::FontList, sf::Font> World::fontMap_ = {
	{World::FontCount, sf::Font()},
	{World::Consola, sf::Font()},
	{World::Micross, sf::Font()},
	{World::VT323Regular, sf::Font()}
};

std::map <std::pair<World::DesktopList, World::ReportType>, std::string > World::reportListMap_ = {
	{ { DE0, A }, resourcePath() + "Reports/DummyReportA.txt" },
	{ { DE0, B }, resourcePath() + "Reports/DummyReportB.txt" },
	{ { DE0, C }, resourcePath() + "Reports/DummyReportC.txt" },
	{ { DE0, D }, resourcePath() + "Reports/DummyReportD.txt" },

	{ { DE1, A }, resourcePath() + "Reports/TeacherReportA.txt" },
	{ { DE1, B }, resourcePath() + "Reports/TeacherReportB.txt" },
	{ { DE1, C }, resourcePath() + "Reports/TeacherReportC.txt" },
	{ { DE1, D }, resourcePath() + "Reports/TeacherReportD.txt" },

	{ { DE2A, A }, resourcePath() + "Reports/ArtistReportA.txt" },
	{ { DE2A, B }, resourcePath() + "Reports/ArtistReportB.txt" },
	{ { DE2A, C }, resourcePath() + "Reports/ArtistReportC.txt" },
	{ { DE2A, D }, resourcePath() + "Reports/ArtistReportD.txt" },

	{ { DE2B, A }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE2B, B }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE2B, C }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE2B, D }, resourcePath() + "Reports/sampleReport.txt" },

	{ { DE3, A }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE3, B }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE3, C }, resourcePath() + "Reports/sampleReport.txt" },
	{ { DE3, D }, resourcePath() + "Reports/sampleReport.txt" },

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

void ppc::World::initLevelMap() {

	LevelPacket levelZero;
	levelZero.push(DEPlayer, 1);
	levelMap_.emplace(DE0, levelZero);

	LevelPacket levelPlayer;
	levelPlayer.push(DE1, 1);
	levelMap_.emplace(DEPlayer, levelPlayer);

	LevelPacket levelOne;
	levelOne.push(DE2A, 19);
	levelOne.push(DE2B, 20);
	levelMap_.emplace(DE1, levelOne);

	LevelPacket levelTwo;
	levelTwo.push(DE3, 1);
	levelMap_.emplace(DE2A, levelTwo);
	levelMap_.emplace(DE2B, levelTwo);

	LevelPacket levelThree;
	levelMap_.emplace(DE3, levelThree);

}

void World::setGameScreen(sf::RenderWindow& gameScreen) {
	screen_ = &gameScreen;
}

sf::VideoMode ppc::World::getVideoMode() {
    sf::VideoMode result;

    if (settings_.fullscreen) {

        result.width = settings_.resolution.x;
        result.height = settings_.resolution.y;

        sf::Vector2f scaleFactor;
        scaleFactor.x = float(settings_.resolution.x) / 1000;
        scaleFactor.y = float(settings_.resolution.y) / 800;

        worldTransform_ = sf::Transform();
        worldTransform_.scale(scaleFactor);

        
    } else {

        result.width = settings_.resolution.x;
        result.height = settings_.resolution.y;

        sf::Vector2f scaleFactor;
        scaleFactor.x = float(settings_.resolution.x) / 1000;
        scaleFactor.y = float(settings_.resolution.y) / 800;

        worldTransform_ = sf::Transform();
        worldTransform_.scale(scaleFactor);

    }

    return result;
}

void World::setCurrDesktop(Desktop &d) {
	currDesktop_ = &d;
}

void ppc::World::setCurrDesktopEnum(DesktopList dl) {
	currDesktopEnum_ = dl;
}

sf::RenderWindow& World::getGameScreen() {
	return *screen_;
}

Desktop& World::getCurrDesktop() {
	return *currDesktop_;
}

void World::runDesktop(Desktop &myDesktop) {
	if (screen_ == nullptr) return;
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
                throw std::exception("Screen Closed");
			} else if (event.type == sf::Event::KeyPressed) {
				//Close
				if ((event.key.code == sf::Keyboard::Period) && (event.key.alt)) {
                    quitDesktop();
                } else if (event.key.code == sf::Keyboard::F5) {
                    settings_.fullscreen = !settings_.fullscreen;
                    manifestSettings();
                }
            } else if ((event.type == sf::Event::MouseButtonPressed) ||
                (event.type == sf::Event::MouseButtonReleased)) {
                
                sf::Vector2f transformedPoint = 
                    worldTransform_.getInverse().transformPoint(
                                event.mouseButton.x,
                                event.mouseButton.y);
                event.mouseButton.x = transformedPoint.x;
                event.mouseButton.y = transformedPoint.y;
            } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f transformedPoint =
                    worldTransform_.getInverse().transformPoint(
                        event.mouseMove.x,
                        event.mouseMove.y);
                event.mouseMove.x = transformedPoint.x;
                event.mouseMove.y = transformedPoint.y;
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                sf::Vector2f transformedPoint =
                    worldTransform_.getInverse().transformPoint(
                        event.mouseWheelScroll.x,
                        event.mouseWheelScroll.y);
                event.mouseWheelScroll.x = transformedPoint.x;
                event.mouseWheelScroll.y = transformedPoint.y;
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
        sf::RenderStates states;
        states.transform = worldTransform_;
		screen_->draw(myDesktop, states);
		screen_->display();
	}

}

bool World::loadDesktop(DesktopList desk) {
    return loadDesktop(desktopFileMap_.at(desk));
}

int World::runCurrDesktop() {
	runDesktop(*currDesktop_);
	return SuspiciousFileHolder::getFinalScore();
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

World::ReportType ppc::World::getCurrReportType() {
	return currReportType_;
}

void ppc::World::setCurrReportType(ReportType rt) {
	currReportType_ = rt;
}

sf::Font& ppc::World::getFont(FontList f) {
	
	return fontMap_.at(f);

}

std::string ppc::World::getReportFile() {
	auto i = reportListMap_.find({ currDesktopEnum_, currReportType_ });
	if (i != reportListMap_.end()) return i->second;
	return "";
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
    if (isLoading_) {
        sf::RenderStates states;
        states.transform = worldTransform_;


        screen_->clear(sf::Color::Black);
        //screen_->draw(tempLoadScreen_);
        //screen_->draw(tempLoadBar_);
        screen_->draw(loadingDecal_, states);
        screen_->draw(loadBarBorder_, states);
        screen_->draw(loadBar_, states);
        screen_->display();
    }
}

void ppc::World::endLoading() {

	isLoading_ = false;
}


void ppc::World::setSettings(Setting settings) {
    settings_ = settings;
    manifestSettings();
}


Setting ppc::World::getSettings() {
    return settings_;
}


void ppc::World::loadState(std::string filename) {
    filename = resourcePath() + "Saves/" + filename;

    std::ifstream file(filename);

    std::string line;

    while (file) {
        std::getline(file, line);

        //Trim Comments
        size_t tempIndex = line.find('#');
        if (tempIndex != std::string::npos) {
            line = line.substr(0, tempIndex);
        }

        //Trim whitespace
        tempIndex = line.find_first_not_of(" \t");
        if (tempIndex == std::string::npos) continue;
        line = line.substr(tempIndex,
                           line.find_last_not_of(" \t"));

        //Enforce Bracket Tagging
        if (line.front() != '[') continue;
        line = line.substr(1, line.find(']'));

        //Find Tag
        auto mapIt = saveGroupMap_.find(line);
        if (mapIt == saveGroupMap_.end()) {
            //Output error
            DEBUGF("wl", filename << ": Bad Group Tag: " << line);
        } else {
            //Handle Tag
            switch (mapIt->second) {
            case SettingsTag:
                file >> settings_;
                manifestSettings();
                break;
            case StateTag:
            default:
                break;
            }
        }
    }

    file.close();
}


void ppc::World::saveState(std::string filename) {
    filename = resourcePath() + "Saves/" + filename;

    std::ofstream file(filename);

    while (file) {
        for (auto& mapPair : saveGroupMap_) {
            //Output grouping Tag
            file << '[' << mapPair.first << ']' << std::endl;

            //Output appropriate info
            switch (mapPair.second) {
            case SettingsTag:
                file << settings_;
                break;
            case StateTag:
            default:
                break;
            }
            file << std::endl;
        }
    }

    file.close();
}


void ppc::World::manifestSettings() {
    if (screen_ != nullptr) {
        unsigned int flags = sf::Style::Default;
        if (settings_.fullscreen) {
            flags = flags | sf::Style::Fullscreen;
        }
        screen_->create(getVideoMode(), "Project Perfect Citizen", flags);
    }
}


