#include "../Engine/debug.h"
#include "createDesktop.h"
#include "desktopExtractionComponent.hpp"
#include "../Game/emailExtraction.hpp"
#include "../Library/json/json.h"
using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {

	
	//////////////////////////////////////////////
	//// Create the database (really should take a seed)
	/////////////////////////////////////////////

	Database* theDatabase = new Database();
	theDatabase->generateFullDatabase(200);

    Inbox* theInbox = new Inbox();
    Email testEmail1("alex", "brandon", "Long time no see!", "hello there friend!", "image.jpg");
    Email testEmail2("brandon", "alex", "RE: Long time no see!", "hi how are you?", "image2.jpg");
    Email testEmail3("alex", "brandon", "RE: RE: Long time no see!", "great! got to go!", "image3.jpg");
    
    theInbox->addEmailToList(testEmail1);
    theInbox->addEmailToList(testEmail2);
    theInbox->addEmailToList(testEmail3);
    
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

	spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 25.0f, 0.5f, 0.25f, theInbox);
	spawnFolderIcon(FolderIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 110.0f, 0.5f, 0.25f, theInbox);
	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 185.0f, 0.5f, 0.25f, theInbox);
	spawnDataGraphIcon(DataGraphIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 335.0f, 0.5f, 0.25f, theInbox);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 410.0f, 0.5f, 0.25f, theInbox);
	spawnSettingsIcon(SettingsIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 485.0f, 0.5f, 0.25f, theInbox);
	spawnSearchIcon(SearchIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 25.0f, 560.0f, 0.5f, 0.25f, theInbox);

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
    
    Inbox* theInbox = new Inbox();
    
    emailExtraction* inbox = new emailExtraction();
    inbox->parseEmailAsJson("Email1.json");
    
    //Inbox thnbox;
    for(int i = 0; i < inbox->getSubject().size(); i++){
        Email testEmail1(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop1.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 60, sf::Color(128, 128, 128));
    startToolbar->setPosition(0, 750);
    Entity startButton = Entity();
    spawnStartButton(startButton, startToolbar->getInputHandler(), buttonSheet, 0, 0, 0.4f);
    startToolbar->addEntity(startButton);
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
    Entity EmailIcon;
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 25.0f, 0.4f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 100.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 175.0f, 0.4f, 0.25f, theInbox);
    spawnSettingsIcon(SettingsIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 250.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 325.0f, 0.5f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 400.0f, 0.5f, 0.25f, theInbox);
    spawnFolderIcon(APEnglishIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 25.0f, 0.4f, 0.25f, theInbox);
    spawnFolderIcon(ArtGalleryIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 100.0f, 0.4f, 0.25f, theInbox);
    spawnFolderIcon(FilmIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 175.0f, 0.4f, 0.25f, theInbox);
    spawnFolderIcon(LitIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 250.0f, 0.4f, 0.25f, theInbox);
    spawnFolderIcon(PhotosIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 125.0f, 325.0f, 0.4f, 0.25f, theInbox);
    
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
    desktopWindowToModify.addEntity(EmailIcon);
    
}