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
<<<<<<< HEAD
#include "Game/mousePressButton.h"
#include "Game/buttonRenderComponent.h"
#include "Game/consoleIconRenderComponent.h"
#include "Game/TreeCommands.h"
#include "Game/animatorComponent.hpp"
#include "Game/textInputKeys.hpp"
#include "Game/createWindow.h"
#include "Game/createIcon.h"
#include "Game/createButton.h"
#include "Game/createDesktop.h"
#include "Game/desktopExtractionComponent.hpp"
#include "Game/expressionistParser.hpp"
#include "Game/PipelineCharacter.h"
#include "Game/Database.h"
#include "Game/BootLoader.hpp"
#include "Game/characterRender.hpp"
#include "Game/interpolateUpdateComponent.hpp"
#include "Game/textLabelComponent.hpp"
=======
>>>>>>> refs/remotes/origin/experimental

#include "Engine/SuspiciousFileHolder.h"

#include "Engine/Audio/AudioQueue.h"

#include "Engine/SetUpDesktops.h"

using namespace ppc;

<<<<<<< HEAD



void setUpLogoDesktop(ppc::Desktop& myDesktop) {
    
    Window* bootWindow = new Window(1800,1000,sf::Color(0,0,0));
    
    Entity badCop;
    
    BadCopRenderComponent* badCopRender = new BadCopRenderComponent(myDesktop.getIconSheet());
    BadCopUpdateComponent* badCopUpdate = new BadCopUpdateComponent(*badCopRender, .1f);
    
    badCop.addComponent(badCopRender);
    badCop.addComponent(badCopUpdate);
    
    bootWindow->addEntity(badCop);
    
    
    myDesktop.addWindow(bootWindow);
}

void setUpBootDesktop(ppc::Desktop& myDesktop) {
    
    Window* bootWindow = new Window(1800,1000,sf::Color(0,0,0));
    
    Entity loading;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    
    
    ppc::textLabelComponent* textLabel = new ppc::textLabelComponent(font,sf::Color::Green, 0,0, 20, " PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n   Beginning File System Initialization \n");
    
    bootLoadingAnimationRender* bootRender = new bootLoadingAnimationRender(myDesktop.getButtonSheet(),*textLabel,7,5);
    
    bootLoadingUpdateComponent* bootUpdate = new bootLoadingUpdateComponent(*bootRender,0.1f);
    
    Entity badCop;
    
    loading.addComponent(bootRender);
    loading.addComponent(bootUpdate);
    loading.addComponent(textLabel);
    bootWindow->addEntity(loading);
    
    
    myDesktop.addWindow(bootWindow);
    
}


void setUpLoginDesktop(ppc::Desktop& myDesktop) {
    
    createLoginDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                       myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}



void setUpEndDesktop(ppc::Desktop& myDesktop) {
    
    Window* endWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity ending;
    
    endingAnimationRender* endRender = new endingAnimationRender(myDesktop.getButtonSheet());
    endAnimationUpdateComponent* endUpdate = new endAnimationUpdateComponent(*endRender, 0.1f);
    
    ending.addComponent(endRender);
    ending.addComponent(endUpdate);
    endWindow->addEntity(ending);
    
    myDesktop.addWindow(endWindow);
}


void setUpPlayerDesktop(ppc::Desktop& myDesktop) {
    createPlayerDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpDummyDesktop(ppc::Desktop& myDesktop) {
    createDummyDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                       myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpTeacherDesktop(ppc::Desktop& myDesktop) {
    createTeacherDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                         myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpArtistDesktop(ppc::Desktop& myDesktop) {
    createArtistDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}

void setUpPoliticianDesktop(ppc::Desktop& myDesktop) {
    createPoliticianDesktop(myDesktop, *myDesktop.getDesktopWindow(),
                            myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
    
}



=======
>>>>>>> refs/remotes/origin/experimental
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
        audiotest.playBgm();
        
        ///////////////////////////////////////////////////////////////////
        
        //// ----------------   PYTHON LOCATION STUFF ---------------- ////
        
        // Run the locator python app
        //system("osascript -e 'tell app \"ppc_location_print\" to open'");
        // -----------------------------------------------------------//
        
        World::setGameScreen(screen);
        World::loadState("PPC.sav");
        std::ifstream desktopFileInput;
        
<<<<<<< HEAD
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
        
        //Testing Report Screen
        //Desktop reportScreen;
        //createReportScreen(reportScreen, World::DE1A);
        //World::setCurrDesktop(reportScreen);
        //World::runCurrDesktop();
        
        //ENd of report screen
        
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
=======
		Desktop mainDesktop;
		World::setCurrDesktop(mainDesktop);
		
		//***For Daniel: Call  this function when you load from the save!***
		//World::setLevel(i,j); where i is the DesktopEnum as an int,
		// and j is the score from the most recent desktop

		while (World::getCurrDesktopEnum() != World::DesktopCount) {
			//Get Current Desktop Level
			World::DesktopList currDesk = World::getCurrDesktopEnum();

			//Load Screen for correct levels
			if((int)currDesk >= 3) World::startLoading();

			//Parse Curr Desktop's .ini
			desktopFileInput.open(World::desktopFileMap_.at(currDesk));
			desktopFileInput >> mainDesktop;
			desktopFileInput.close();

			//Set Up Curr Desktop Level
			World::loaderMap_.at(currDesk)(mainDesktop);

			//Run the Curr Desktop. Get Player's score when it ends
			int deskScore = World::runCurrDesktop();

			//Use Score to determine next level to go to
			World::goToNext(deskScore);
>>>>>>> refs/remotes/origin/experimental
		}

    return EXIT_SUCCESS;
       
    } catch(std::exception e) {
        std::cerr << e.what();
    }
	
    return EXIT_SUCCESS;
}
