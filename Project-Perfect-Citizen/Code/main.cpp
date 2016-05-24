//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif
///////////////////////////////////////////////////////////
#include <fstream>
#include <string>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

		// Create the main sf::window
		sf::RenderWindow screen(World::getVideoMode(), "Project Perfect Citizen");

		AudioQueue audiotest(5);
		audiotest.addBgm("SoundTrack_Extraction.ogg");
		audiotest.loopBgm();
		//audiotest.playBgm();

		///////////////////////////////////////////////////////////////////

		//// ----------------   PYTHON LOCATION STUFF ---------------- ////

		// Run the locator python app
		//system("osascript -e 'tell app \"ppc_location_print\" to open'");
		// -----------------------------------------------------------//

		World::setGameScreen(screen);
		World::loadState("PPC.sav");
		std::ifstream desktopFileInput;

		Desktop mainDesktop;
		World::setCurrDesktop(mainDesktop);

		while (World::getCurrDesktopEnum() != World::DesktopCount) {
			//Get Current Desktop Level
			World::DesktopList currDesk = World::getCurrDesktopEnum();

			//Load Screen for correct levels
			if ((int)currDesk >= 3) World::startLoading();

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

		return EXIT_SUCCESS;

	}
	catch (std::exception e) {
		std::cerr << e.what();
	}

	return EXIT_SUCCESS;
}
