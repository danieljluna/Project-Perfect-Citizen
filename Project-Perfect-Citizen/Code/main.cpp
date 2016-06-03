

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

#ifdef WINDOWS_MARKER

#include <windows.h>

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

#else

int main(int argc, char** argv) {

#endif


    try {

		World::initLevelMap();
		World::initFontMap();
		World::initLoadScreen();
		World::initAddressMap();

		ppc::World::getAudio().addBgm("SoundTrack_Pipeline.ogg");
		ppc::World::getAudio().loopBgm();
		ppc::World::getAudio().playBgm();
		int buzzSound = ppc::World::getAudio().addSound("buzz", "Randomize36.wav");

		ppc::World::getAudio().readySound(buzzSound);
		ppc::World::getAudio().popAndPlay();

		World::loadState("PPC.sav");
		std::ifstream desktopFileInput;

		while (World::getCurrDesktopEnum() != World::DesktopCount) {
			Desktop mainDesktop;
			World::setCurrDesktop(mainDesktop);

			//Get Current Desktop Level
			World::DesktopList currDesk = World::getCurrDesktopEnum();

			//Load Screen for correct levels
			if ((int)currDesk >= 3 && (int)currDesk != (int)World::DEEnd1) World::startLoading();

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

	}
	catch (std::exception e) {
		std::cerr << e.what();
	}

    	if (World::getCurrDesktopEnum() > World::DELogin) {
        	World::saveState("PPC.sav");
   	}
	
	World::cleanWorld();

	return EXIT_SUCCESS;
}


