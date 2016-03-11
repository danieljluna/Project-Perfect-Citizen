#include "../Engine/debug.h"
#include "createDesktop.h"
#include "desktopExtractionComponent.hpp"
#include "../Game/emailExtraction.hpp"
#include "../Library/json/json.h"
using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {
	
	std::vector<string> firstLsCommand;
	string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(desktopToModify.getNodeState(), firstLsCommand);
	
	//////////////////////////////////////////////
	//// Create the database (really should take a seed)
	/////////////////////////////////////////////

	Database* theDatabase = new Database();
	theDatabase->generateFullDatabase(200);

    Inbox* theInbox = new Inbox();
    
    emailExtraction* inbox = new emailExtraction();
    inbox->parseEmailAsJson("PlayerEmail.json");
    
    //Inbox thnbox;
    for(int i = 0; i < inbox->getSubject().size(); i++){
        Email testEmail1(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
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
	Entity SearchIcon;
	Entity EmailIcon;

	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 425.0f, 110.0f, 0.5f, 0.25f, theInbox);

	spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 225.0f, 0.5f, 0.25f, theInbox);
	spawnDataGraphIcon(DataGraphIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 625.0f, 225.0f, 0.5f, 0.25f, theInbox);

	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 425.0f, 0.5f, 0.25f, theInbox);
	spawnSearchIcon(SearchIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 625.0f, 425.0f, 0.5f, 0.25f, theInbox);
	
	spawnFolderIcon(FolderIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 425.0f, 525.0f, 0.5f, 0.25f, theInbox);
	
	
	
	

	desktopWindowToModify.addEntity(ConsoleIcon);
	desktopWindowToModify.addEntity(FolderIcon);
	desktopWindowToModify.addEntity(DataGraphIcon);
	desktopWindowToModify.addEntity(HardDriveIcon);
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
    Entity EmailIcon;
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 425.0f, 25.0f, 0.4f, 0.25f, theInbox);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 125.0f, 175.0f, 0.4f, 0.25f, theInbox);
	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 525.0f, 200.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 300.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 725.0f, 450.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);
    
}