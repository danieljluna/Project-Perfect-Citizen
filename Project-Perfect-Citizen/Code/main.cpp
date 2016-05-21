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
        
        
        bool BootToTitleCard = false;
        // Create the main sf::window
        sf::RenderWindow screen(World::getVideoMode(), "Project Perfect Citizen");
        
        AudioQueue audiotest(5);
        audiotest.addBgm("SoundTrack_Extraction.ogg");
        audiotest.loopBgm();
        audiotest.playBgm();
        
        ///////////////////////////////////////////////////////////////////
        
        //// ----------------   PYTHON LOCATION STUFF ---------------- ////
        
        // Run the locator python app
        //system("osascript -e 'tell app \"ppc_location_print\" to open'");
        // -----------------------------------------------------------//
        
        World::setGameScreen(screen);
        World::loadState("PPC.sav");
        std::ifstream desktopFileInput;
        
        //Main Loops for each Desktops
        
        //Logo Desktop
        Desktop mainDesktop;
        desktopFileInput.open(resourcePath() + "Engine/bootDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        
        desktopFileInput.close();
        Logger::startTimer("logoDesktop");
        
        World::setCurrDesktop(mainDesktop);
		World::setCurrDesktopEnum(World::DesktopList::DELogo);
        ppc::setUpLogoDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("logoDesktop");
        //End Boot Desktop
        
        //Boot Desktop
        desktopFileInput.open(resourcePath() + "Engine/bootDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        Logger::startTimer("bootDesktop");
        
        World::setCurrDesktop(mainDesktop);
		World::setCurrDesktopEnum(World::DesktopList::DEOpening);
        setUpBootDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("bootDesktop");
        //End Boot Desktop
        
        //Login Desktop
        desktopFileInput.open(resourcePath() + "Engine/loginDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        Logger::startTimer("loginDesktop");
        
        World::setCurrDesktop(mainDesktop);
		World::setCurrDesktopEnum(World::DesktopList::DELogin);
        setUpLoginDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("loginDesktop");
        
        //PE Tutorial Desktop
        World::startLoading();
        
        
        desktopFileInput.open(resourcePath() + "Engine/pipelineTutorial.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("PipeTutorialDesktop");
        
        World::setCurrDesktop(mainDesktop);
        World::setCurrDesktopEnum(World::DesktopList::DE0A);
        createTutorial(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("PipeTutorialDesktop");
        //End PE Tutorial Desktop
        
        
        //DE Tutorial Desktop
        World::startLoading();
        desktopFileInput.open(resourcePath() + "Engine/desktopTutorial.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("DeskTutorialDesktop");
        
        World::setCurrDesktop(mainDesktop);
        World::setCurrDesktopEnum(World::DesktopList::DE0B);
        createDesktopTutorial(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("DeskTutorialDesktop");
        
        //Player Desktop
        World::startLoading();
        desktopFileInput.open(resourcePath() + "Engine/playerDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("playerDesktop");
        
        World::setCurrDesktop(mainDesktop);
        World::setCurrDesktopEnum(World::DesktopList::DEPlayer1);
        setUpPlayerDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("playerDesktop");
        // End Player Desktop      
        
        //Desktop 1 / Teacher Desktop
        World::startLoading();
        desktopFileInput.open(resourcePath() + "Engine/teacherDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        Logger::startTimer("TeacherDesktop");
        
        World::setCurrDesktop(mainDesktop);
        World::setCurrDesktopEnum(World::DesktopList::DE1);
        setUpTeacherDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("TeacherDesktop");
        //End of Target/Teacher Desktop
        
        //Player Desktop (2)
        World::startLoading();
		if (ppc::SuspiciousFileHolder::isGuilty()) {
			desktopFileInput.open(resourcePath() + "Engine/playerDesktop2B.ini", std::ifstream::in);
			World::setCurrDesktopEnum(World::DesktopList::DEPlayer2B);
		} else {
			desktopFileInput.open(resourcePath() + "Engine/playerDesktop2A.ini", std::ifstream::in);
			World::setCurrDesktopEnum(World::DesktopList::DEPlayer2A);
		}
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("playerDesktop2");
        
        World::setCurrDesktop(mainDesktop);
        setUpPlayerDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("playerDesktop2");
        
        
        //Desktop Extraction 2 / (Artist or Politician DE)
        World::startLoading();
        if (ppc::SuspiciousFileHolder::isGuilty()) {
            desktopFileInput.open(resourcePath() + "Engine/politicianDesktop.ini", std::ifstream::in);
            World::setCurrDesktopEnum(World::DesktopList::DE2B);
        } else {
            desktopFileInput.open(resourcePath() + "Engine/artistDesktop.ini", std::ifstream::in);
            World::setCurrDesktopEnum(World::DesktopList::DE2A);
        }
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("DE2Desktop");
        
        World::setCurrDesktop(mainDesktop);
        if (ppc::SuspiciousFileHolder::isGuilty()) {
            setUpPoliticianDesktop(mainDesktop);
        } else {
            setUpArtistDesktop(mainDesktop);
        }
        World::runCurrDesktop();
        
        Logger::endTimer("DE2Desktop");
        //End of Target/Teacher Desktop
        
        //Player Desktop (PE3)
        World::startLoading();
        desktopFileInput.open(resourcePath() + "Engine/playerDesktop3.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        
        Logger::startTimer("playerDesktop3");
        
        World::setCurrDesktop(mainDesktop);
        World::setCurrDesktopEnum(World::DesktopList::DEPlayer3);
        setUpPlayerDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("playerDesktop3");
        
        
        //Desktop Extraction 3 goes here
        
        //Ending Desktop
        desktopFileInput.open(resourcePath() + "Engine/endDesktop.ini", std::ifstream::in);
        desktopFileInput >> mainDesktop;
        desktopFileInput.close();
        Logger::startTimer("endDesktop");
        
        World::setCurrDesktop(mainDesktop);
        setUpEndDesktop(mainDesktop);
        World::runCurrDesktop();
        
        Logger::endTimer("endDesktop");
        
        Logger::exportParcels();
        
        
        
        return EXIT_SUCCESS;
        
    } catch(std::exception e) {
        std::cerr << e.what();
    }

    return EXIT_SUCCESS;

}
