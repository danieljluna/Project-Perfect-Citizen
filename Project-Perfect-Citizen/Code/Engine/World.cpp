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
#include "SetUpDesktops.h"

using namespace ppc;


sf::RenderWindow* World::screen_ = nullptr;
Desktop* World::currDesktop_ = nullptr;
sf::Transform World::worldTransform_;
sf::RectangleShape World::blackBars_[2] = {sf::RectangleShape(), sf::RectangleShape()};

bool World::progToNext_ = true;


std::map<ppc::World::DesktopList, ppc::LevelPacket> World::levelMap_ = {

};

std::map<std::string, World::savGroups> World::saveGroupMap_ = {
    { "Settings",      World::SettingsTag  },
    { "State",         World::StateTag     }
};

World::DesktopList World::currDesktopEnum_ = DELogo;
World::ReportType World::currReportType_ = A;
std::map<World::DesktopList, std::string> World::desktopFileMap_ = {
	{ World::DELogo, resourcePath() + "Engine/bootDesktop.ini" },
	{ World::DEOpening, resourcePath() + "Engine/bootDesktop.ini" },
	{ World::DELogin, resourcePath() + "Engine/loginDesktop.ini" },
	{ World::DE0A, resourcePath() + "Engine/pipelineTutorial.ini" },
	{ World::DE0B, resourcePath() + "Engine/desktopTutorial.ini" },
	{ World::DEPlayer1, resourcePath() + "Engine/playerDesktop.ini" },
	{ World::DE1, resourcePath() + "Engine/teacherDesktop.ini" },
	{ World::DEPlayer2A, resourcePath() + "Engine/playerDesktop2A.ini" },
	{ World::DEPlayer2B, resourcePath() + "Engine/playerDesktop2B.ini" },
	{ World::DE2A, resourcePath() + "Engine/artistDesktop.ini" },
	{ World::DE2B, resourcePath() + "Engine/politicianDesktop.ini" },
	{ World::DEPlayer3A, resourcePath() + "Engine/playerDesktop3.ini" },
	{ World::DEPlayer3B, resourcePath() + "Engine/playerDesktop3.ini" },
	{ World::DE3, resourcePath() + "Engine/hackerDesktop.ini" },
	{ World::DEEnd, resourcePath() + "Engine/endDesktop.ini" },
    { World::DesktopCount, ""}  //Empty pairing of Count to string.
};

std::map<World::DesktopList, World::desktopLoaders> World::loaderMap_ = {
	{World::DELogo, setUpLogoDesktop },
	{ World::DEOpening, setUpBootDesktop },
	{ World::DELogin, setUpLoginDesktop },
	{ World::DE0A, createTutorial },
	{ World::DE0B, createDesktopTutorial },
	{ World::DEPlayer1, setUpPlayerDesktop },
	{ World::DE1, setUpTeacherDesktop },
	{ World::DEPlayer2A, setUpPlayerDesktop },
	{ World::DEPlayer2B, setUpPlayerDesktop },
	{ World::DE2A, setUpArtistDesktop },
	{ World::DE2B, setUpPoliticianDesktop },
	{ World::DEPlayer3A,setUpPlayerDesktop },
	{ World::DEPlayer3B,setUpPlayerDesktop },
	{ World::DE3, setUpHackerDesktop },
	{ World::DEEnd, setUpEndDesktop },
	{ World::DesktopCount, nullptr }  //Empty pairing of Count to nullptr.
};

std::map<World::FontList, sf::Font> World::fontMap_ = {
	{World::FontCount, sf::Font()},
	{World::Consola, sf::Font()},
	{World::Micross, sf::Font()},
	{World::VT323Regular, sf::Font()}
};

std::map <std::pair<World::DesktopList, World::ReportType>, std::string > World::reportListMap_ = {
	{ { DE0B, A }, resourcePath() + "Reports/DummyReportA.txt" },
	{ { DE0B, B }, resourcePath() + "Reports/DummyReportB.txt" },
	{ { DE0B, C }, resourcePath() + "Reports/DummyReportC.txt" },
	{ { DE0B, D }, resourcePath() + "Reports/DummyReportD.txt" },

	{ { DE1, A }, resourcePath() + "Reports/TeacherReportA.txt" },
	{ { DE1, B }, resourcePath() + "Reports/TeacherReportB.txt" },
	{ { DE1, C }, resourcePath() + "Reports/TeacherReportC.txt" },
	{ { DE1, D }, resourcePath() + "Reports/TeacherReportD.txt" },

	{ { DE2A, A }, resourcePath() + "Reports/ArtistReportA.txt" },
	{ { DE2A, B }, resourcePath() + "Reports/ArtistReportB.txt" },
	{ { DE2A, C }, resourcePath() + "Reports/ArtistReportC.txt" },
	{ { DE2A, D }, resourcePath() + "Reports/ArtistReportD.txt" },

	{ { DE2B, A }, resourcePath() + "Reports/PoliticianReportA.txt" },
	{ { DE2B, B }, resourcePath() + "Reports/PoliticianReportB.txt" },
	{ { DE2B, C }, resourcePath() + "Reports/PoliticianReportC.txt" },
	{ { DE2B, D }, resourcePath() + "Reports/PoliticianReportD.txt" },

	{ { DE3, A }, resourcePath() + "Reports/HackerReportA.txt" },
	{ { DE3, B }, resourcePath() + "Reports/HackerReportB.txt" },
	{ { DE3, C }, resourcePath() + "Reports/HackerReportC.txt" },
	{ { DE3, D }, resourcePath() + "Reports/HackerReportD.txt" },

};

std::map <std::pair<World::DesktopList, World::ReportType>, std::string > World::bossEmailMap_ = {
	{ { DEPlayer1, A }, "TutorialResponseA.json" },
	{ { DEPlayer1, B }, "TutorialResponseB.json" },
	{ { DEPlayer1, C }, "TutorialResponseC.json" },
	{ { DEPlayer1, D }, "TutorialResponseD.json" },

	{ { DEPlayer2A, A }, "TeacherResponseA.json" },
	{ { DEPlayer2A, B }, "TeacherResponseB.json" },
	{ { DEPlayer2A, C }, "TeacherResponseC.json" },
	{ { DEPlayer2A, D }, "TeacherResponseD.json" },

	{ { DEPlayer2B, A }, "TeacherResponseA.json" },
	{ { DEPlayer2B, B }, "TeacherResponseB.json" },
	{ { DEPlayer2B, C }, "TeacherResponseC.json" },
	{ { DEPlayer2B, D }, "TeacherResponseD.json" },

	{ { DEPlayer3A, A }, "ArtistResponseA.json" },
	{ { DEPlayer3A, B }, "ArtistResponseB.json" },
	{ { DEPlayer3A, C }, "ArtistResponseC.json" },
	{ { DEPlayer3A, D }, "ArtistResponseD.json" },

	{ { DEPlayer3B, A }, "PoliticianResponseA.json" },
	{ { DEPlayer3B, B }, "PoliticianResponseB.json" },
	{ { DEPlayer3B, C }, "PoliticianResponseC.json" },
	{ { DEPlayer3B, D }, "PoliticianResponseD.json" },


};

bool World::quitter_ = false;

sf::RectangleShape World::tempLoadScreen_ = sf::RectangleShape({ 1000,1000 });
sf::RectangleShape World::tempLoadBar_ = sf::RectangleShape({ 500, 50 });

sf::Image World::loadImage_ = sf::Image();
sf::Texture World::loadTexture_ = sf::Texture();
sf::Sprite World::loadBar_ = sf::Sprite();
sf::Sprite World::loadBarBorder_ = sf::Sprite();
sf::Sprite World::loadingDecal_ = sf::Sprite();
sf::Sprite World::clickToContinue_ = sf::Sprite();

bool World::isLoading_ = false;
bool World::isLoadBarFull_ = false;
Setting World::settings_;

void ppc::World::initLevelMap() {

	LevelPacket levelGameLogo;
	levelGameLogo.pushNext(DEOpening, 1);
	levelMap_.emplace(DELogo, levelGameLogo);

	LevelPacket levelGameOpening;
	levelGameOpening.pushNext(DELogin, 1);
	levelMap_.emplace(DEOpening, levelGameOpening);

	LevelPacket levelLoginScreen;
	levelLoginScreen.pushNext(DE0A, 1);
	levelMap_.emplace(DELogin, levelLoginScreen);

	LevelPacket levelTutorialPipeline;
	levelTutorialPipeline.pushNext(DE0B, 1);
	levelMap_.emplace(DE0A, levelTutorialPipeline);

	LevelPacket levelTutorialExtraction;
	levelTutorialExtraction.pushNext(DEPlayer1, 1);
	levelMap_.emplace(DE0B, levelTutorialExtraction);

	LevelPacket levelPlayer1;
	levelPlayer1.pushNext(DE1, 1);
	levelMap_.emplace(DEPlayer1, levelPlayer1);

	LevelPacket levelOne;
	levelOne.pushNext(DEPlayer2A, 19);
	levelOne.pushNext(DEPlayer2B, 20);
	levelMap_.emplace(DE1, levelOne);

	LevelPacket levelPlayer2A;
	levelPlayer2A.pushNext(DE2A, 19);
	levelMap_.emplace(DEPlayer2A, levelPlayer2A);

	LevelPacket levelPlayer2B;
	levelPlayer2B.pushNext(DE2B, 20);
	levelMap_.emplace(DEPlayer2B, levelPlayer2B);

	LevelPacket level2A;
	level2A.pushNext(DEPlayer3A, 1);
	levelMap_.emplace(DE2A, level2A);

	LevelPacket level2B;
	level2A.pushNext(DEPlayer3B, 1);
	levelMap_.emplace(DE2B, level2B);

	LevelPacket levelPlayer3A;
	LevelPacket levelPlayer3B;
	levelPlayer3A.pushNext(DE3, 1);
	levelPlayer3B.pushNext(DE3, 1);
	levelMap_.emplace(DEPlayer3A, levelPlayer3A);
	levelMap_.emplace(DEPlayer3B, levelPlayer3B);

	LevelPacket levelThree;
	levelThree.pushNext(DEEnd, 1);
	levelMap_.emplace(DE3, levelThree);

	LevelPacket levelEnd;
	levelEnd.pushNext(DesktopCount, 1);
	levelMap_.emplace(DEEnd, levelEnd);

}

void ppc::World::setLevel(int levelEnum, int score) {
	if (levelEnum >= (int)World::DesktopCount) {
		currDesktopEnum_ = DELogo;
		return;
	}

	if (progToNext_) {
		World::DesktopList nextD =
			(DesktopList)levelMap_.at((DesktopList)levelEnum).getNext(score);

		currDesktopEnum_ = nextD;
	} else {
		World::currDesktopEnum_ = (World::DesktopList)levelEnum;
		progToNext_ = true;
	}


}

void ppc::World::goBack() {
	progToNext_ = false;
}

void World::setGameScreen(sf::RenderWindow& gameScreen) {
	screen_ = &gameScreen;
}

sf::VideoMode ppc::World::getVideoMode() {
    sf::VideoMode result;

    result.width = settings_.resolution.x;
    result.height = settings_.resolution.y;

    sf::Vector2f scaleFactorVec;
    scaleFactorVec.x = float(settings_.resolution.x) / 1000;
    scaleFactorVec.y = float(settings_.resolution.y) / 800;

    float scaleFactor = std::min(scaleFactorVec.x,
                                    scaleFactorVec.y);

    worldTransform_ = sf::Transform();

    blackBars_[0].setFillColor({ 0, 0, 0 });
    blackBars_[1].setFillColor({ 0, 0, 0 });
    
    //If we are cramped by width:
    if (scaleFactor == scaleFactorVec.x) {

        float offset = (float(result.height) - 800.0f * scaleFactor) / 2.0f;

        worldTransform_.translate(0, offset);

        blackBars_[0].setPosition(0, 0);
        blackBars_[0].setSize({ float(result.width), offset });
        blackBars_[1].setPosition(0, float(result.height) - offset);
        blackBars_[1].setSize({ float(result.width), offset });

    //Else we are cramped by height:
    } else {

        float offset = (float(result.width) - 1000.0f * scaleFactor) / 2.0f;

        worldTransform_.translate(offset, 0);

        blackBars_[0].setPosition(0, 0);
        blackBars_[0].setSize({ offset, float(result.height) });
        blackBars_[1].setPosition(float(result.width) - offset, 0);
        blackBars_[1].setSize({ offset, float(result.height) });

    }

    worldTransform_.scale(scaleFactor, scaleFactor);


    return result;
}

void World::setCurrDesktop(Desktop &d) {
	currDesktop_ = &d;
}

void ppc::World::setCurrDesktopEnum(DesktopList dl) {
	currDesktopEnum_ = dl;
}

World::DesktopList ppc::World::getCurrDesktopEnum() {
	return currDesktopEnum_;
}

sf::RenderWindow& World::getGameScreen() {
	return *screen_;
}

Desktop& World::getCurrDesktop() {
	return *currDesktop_;
}

void World::runDesktop() {
	if (screen_ == nullptr) return;
	// Go into main game loop
	
    quitter_ = false;
	sf::Clock deltaTime;
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	World::endLoading();
	while (screen_->isOpen() && !quitter_) {
		//Process sf::events
		World::registerInput();

		//Update
		World::update(deltaTime, framePeriod);

		//Draw
        World::drawDesktop();
	}

}

bool World::loadDesktop(DesktopList desk) {
    return loadDesktop(desktopFileMap_.at(desk));
}

int World::runCurrDesktop() {
	runDesktop();
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

std::string ppc::World::getBossEmail() {
	auto i = bossEmailMap_.find({ currDesktopEnum_, currReportType_ });
	if (i != bossEmailMap_.end()) return i->second;
	return "";
}


void ppc::World::initLoadScreen() {
    
    loadImage_.loadFromFile(resourcePath() + "World_Sheet.png");
    loadTexture_.loadFromImage(loadImage_);
    
    clickToContinue_.setTexture(loadTexture_);
    clickToContinue_.setPosition(240.f, 600.f);
    clickToContinue_.setTextureRect({0,5*128, 5*128, 128});
    clickToContinue_.setScale(0.75f, 0.75f);

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
	if (f == 1.0f) isLoadBarFull_ = true;
    else isLoadBarFull_ = false;
    loadBar_.setTextureRect({0, 4*128, static_cast<int>(1024*f),128});
	tempLoadBar_.setSize({ 500.f * f, 50.f });
	drawLoading();
}

void ppc::World::drawLoading() {
    if (isLoading_) {
        sf::RenderStates states;
        states.transform = worldTransform_;
		
        screen_->clear(sf::Color::Black);
        screen_->draw(loadingDecal_, states);
        screen_->draw(loadBarBorder_, states);
        screen_->draw(loadBar_, states);
        if(isLoadBarFull_) screen_->draw(clickToContinue_, states);

        screen_->display();
    }
}

void ppc::World::endLoading() {
	if (isLoading_ == true) {
		sf::Event event;

		while(screen_->pollEvent(event)){
			//HACK: Clear the event queue first,
			// so that events added before the load bar is 
			// full are ignored.
		}  
		while (isLoadBarFull_) {
			screen_->pollEvent(event);
			if (event.type == sf::Event::MouseButtonPressed) {
				isLoading_ = false;
				isLoadBarFull_ = false;
				return;
			}
		}
	}
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

void World::drawDesktop() {
    currDesktop_->refresh();
    sf::RenderStates states;
    states.transform = worldTransform_;
    screen_->draw(*currDesktop_, states);
    screen_->draw(blackBars_[0]);
    screen_->draw(blackBars_[1]);
    
    screen_->display();
}

void ppc::World::registerInput() {
	sf::Event event;
	while (screen_->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			screen_->close();
			throw std::exception();
			// Does not work on Mac v
			//throw std::exception("Screen Closed");
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
					(float)event.mouseButton.x,
					(float)event.mouseButton.y);
			event.mouseButton.x = (int)transformedPoint.x;
			event.mouseButton.y = (int)transformedPoint.y;
		} else if (event.type == sf::Event::MouseMoved) {
			sf::Vector2f transformedPoint =
				worldTransform_.getInverse().transformPoint(
					(float)event.mouseMove.x,
					(float)event.mouseMove.y);
			event.mouseMove.x = (int)transformedPoint.x;
			event.mouseMove.y = (int)transformedPoint.y;
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			sf::Vector2f transformedPoint =
				worldTransform_.getInverse().transformPoint(
					(float)event.mouseWheelScroll.x,
					(float)event.mouseWheelScroll.y);
			event.mouseWheelScroll.x = (int)transformedPoint.x;
			event.mouseWheelScroll.y = (int)transformedPoint.y;
		}

		//Input phase
		currDesktop_->registerInput(event);
	}
}

void ppc::World::update(sf::Clock& deltaTime, sf::Time& framePeriod ) {

	sf::Time elapsed = deltaTime.getElapsedTime();
	while (elapsed > framePeriod) {
		screen_->clear(sf::Color::Black);
		sf::Time dt = deltaTime.restart();
		currDesktop_->update(dt);
		elapsed -= framePeriod;
	}
}
