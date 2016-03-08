#include "../Engine/debug.h"
#include "createDesktop.h"
#include "desktopExtractionComponent.hpp"
#include "../Game/emailExtraction.hpp"
#include "../Library/json/json.h"
using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {

	
	//////////////////////////////////////////////
	//// Create the database (really should take a seed)
	/////////////////////////////////////////////

	Database* theDatabase = new Database();
	theDatabase->generateFullDatabase(200);

	
	//////////////////////////////////////////////
	//// Create the start menu
	/////////////////////////////////////////////
	ppc::WindowInterface* startToolbar =
		new ppc::Window(1000, 60, sf::Color(128, 128, 128));
	startToolbar->setPosition(0, 750);
	Entity startButton;
	spawnStartButton(startButton, startToolbar->getInputHandler(), buttonSheet, 0, 0, 0.4f);
	startToolbar->addEntity(startButton);
	desktopToModify.addWindow(startToolbar);


	////////////////////////////////
	///// ICONS ON PLAYER DESKTOP
	////////////////////////////////
	Entity ConsoleIcon;
	Entity FolderIcon;
	Entity DataGraphIcon;
	Entity HardDriveIcon;
	Entity SettingsIcon;
	Entity SearchIcon;
	Entity EmailIcon;

	spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 25.0f, 0.5f, 0.25f);
	spawnFolderIcon(FolderIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 110.0f, 0.5f, 0.25f);
	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 185.0f, 0.5f, 0.25f);
	spawnDataGraphIcon(DataGraphIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 335.0f, 0.5f, 0.25f);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 410.0f, 0.5f, 0.25f);
	spawnSettingsIcon(SettingsIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 485.0f, 0.5f, 0.25f);
	spawnSearchIcon(SearchIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 25.0f, 560.0f, 0.5f, 0.25f);

	desktopWindowToModify.addEntity(ConsoleIcon);
	desktopWindowToModify.addEntity(FolderIcon);
	desktopWindowToModify.addEntity(DataGraphIcon);
	desktopWindowToModify.addEntity(HardDriveIcon);
	desktopWindowToModify.addEntity(SettingsIcon);
	desktopWindowToModify.addEntity(SearchIcon);
	desktopWindowToModify.addEntity(EmailIcon);

}

void createTeacherDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
    
    //////////////////////////////////////////////
    //// Create the database (really should take a seed)
    /////////////////////////////////////////////
    Database* theDatabase = new Database();
    theDatabase->generateFullDatabase(0);
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop1.json", "Desktop");
    
    emailExtraction* inbox = new emailExtraction();
    inbox->parseEmailAsJson("Email1.json");
    std::cout << inbox->checkSizeOfAll();
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 60, sf::Color(128, 128, 128));
    startToolbar->setPosition(0, 750);
    Entity* startButton = new Entity();
    spawnStartButton(*startButton, startToolbar->getInputHandler(), buttonSheet, 0, 0, 0.4f);
    startToolbar->addEntity(*startButton);
    desktopToModify.addWindow(startToolbar);
    
    ////////////////////////////////
    ///// ICONS ON TEACHER DESKTOP
    ////////////////////////////////
    Entity BrowserIcon;
    Entity ChatIcon;
    Entity HardDriveIcon;
    Entity SettingsIcon;
    Entity ConsoleIcon;
    Entity APEnglishIcon;
    Entity ArtGalleryIcon;
	Entity FilmIcon;
    Entity LitIcon;
    Entity PhotosIcon;
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 25.0f, 0.4f, 0.25f);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 100.0f, 0.4f, 0.25f);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 175.0f, 0.4f, 0.25f);
    spawnSettingsIcon(SettingsIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 250.0f, 0.4f, 0.25f);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 325.0f, 0.5f, 0.25f);
    spawnFolderIcon(APEnglishIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 25.0f, 0.4f, 0.25f);
    spawnFolderIcon(ArtGalleryIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 100.0f, 0.4f, 0.25f);
    spawnFolderIcon(FilmIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 175.0f, 0.4f, 0.25f);
    spawnFolderIcon(LitIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 250.0f, 0.4f, 0.25f);
    spawnFolderIcon(PhotosIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 325.0f, 0.4f, 0.25f);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(APEnglishIcon);
    desktopWindowToModify.addEntity(ArtGalleryIcon);
    desktopWindowToModify.addEntity(FilmIcon);
    desktopWindowToModify.addEntity(LitIcon);
    desktopWindowToModify.addEntity(PhotosIcon);
    
}