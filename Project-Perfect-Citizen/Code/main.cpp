

#include "ResourceDef.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Engine/Engine.h"

#include "Engine/SuspiciousFileHolder.h"

#include "Engine/Audio/AudioQueue.h"

#include "Engine/SetUpDesktops.h"


using namespace ppc;

int main(int argc, char** argv) {
    try {

		DBG_INIT();
		//Scans Debug Flags
		Debug::scanOpts(argc, argv);
		DEBUGF("ac", argc);

		World::initLevelMap();
		World::initFontMap();
		World::initLoadScreen();
		World::initAddressMap();

		AudioQueue audiotest(5);
		audiotest.addBgm("SoundTrack_Pipeline.ogg");
		audiotest.loopBgm();
		audiotest.playBgm();

		World::loadState("PPC.sav");
		//World::setCurrDesktopEnum(World::DE3A);
		std::ifstream desktopFileInput;
		while (World::getCurrDesktopEnum() != World::DesktopCount) {
			Desktop mainDesktop;
			World::setCurrDesktop(mainDesktop);

			//Get Current Desktop Level
			World::DesktopList currDesk = World::getCurrDesktopEnum();

			//Load Screen for correct levels
			if ((int)currDesk >= 3 && (int)currDesk != (int)World::DE3B) World::startLoading();

			//Parse Curr Desktop's .ini
			desktopFileInput.open(World::desktopFileMap_.at(currDesk));
			desktopFileInput >> mainDesktop;
			desktopFileInput.close();

			//Set Up Curr Desktop Level
			World::loaderMap_.at(currDesk)(mainDesktop);

			//Run the Curr Desktop. Get Player's score when it ends
			int deskScore = World::runCurrDesktop();

			//Have this here in case currDesktopEnum changed during the Desktop
			currDesk = World::getCurrDesktopEnum();

			//Use Score to determine next level to go to
			World::setLevel(currDesk, deskScore);
		}
		World::cleanWorld();
		return EXIT_SUCCESS;

	}
	catch (std::exception e) {
		std::cerr << e.what();

		World::cleanWorld();
	}

	return EXIT_SUCCESS;
}


