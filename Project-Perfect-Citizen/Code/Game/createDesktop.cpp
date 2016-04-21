#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createDesktop.h"

#include "createWindow.h"

#include <iostream>
#include <fstream>

#include "../Engine/Engine.h"

#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "textInputRenderComponent.hpp"
#include "spriteRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "createIcon.h"
#include "createButton.h"
#include "Database.h"
#include "TextBoxBuilder.h"
#include "desktopExtractionComponent.hpp"
#include "CharacterRender.hpp"
#include "emailExtraction.hpp"
#include "TreeCommands.h"

#include "FloppyUpdateComponent.hpp"
#include "FloppyRenderComponent.hpp"
#include "FloppyInputComponent.h"
#include "TextBubble.h"
#include "TextBubbleRender.h"
#include "ButtonBuilder.h"

#include "notifcationRenderComponent.h"


#include "../Library/json/json.h"

using namespace ppc;

void createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {
	
	std::vector<std::string> firstLsCommand;
	std::string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(*desktopToModify.getNodeState(), firstLsCommand);
	
	//////////////////////////////////////////////
	//// Create the database (really should take a seed)
	/////////////////////////////////////////////
    
    sf::Image floppyImage;
    floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");

	//TODO: FIX MEMORY LEAK
    Database* theDatabase = new Database();
	theDatabase->generateFullDatabase(200);

    //TODO: FIX MEMORY LEAK
    Inbox* theInbox = new Inbox();

    emailExtraction inbox;// = new emailExtraction();
    inbox.parseEmailAsJson("PlayerEmail.json");
    

    for(unsigned int i = 0; i < inbox.getSubject().size(); i++){
        Email testEmail1(inbox.getTo().at(i), inbox.getFrom().at(i), inbox.getSubject().at(i), inbox.getBody().at(i), inbox.getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
	//////////////////////////////////////////////
	//// Create the start menu
	/////////////////////////////////////////////
	ppc::WindowInterface* startToolbar =
		new ppc::Window(1000, 200, sf::Color(195, 195, 195,0));
	startToolbar->setPosition(0, 735);
    
    Entity startBar;
    spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    
    
    FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);
    
    FloppyInputComponent* floppyIn = new FloppyInputComponent();
    
    FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);

	TextBubble* tb = new TextBubble();
	tb->setPosition(90.f, 0);
	TextBubbleRender* tbr = new TextBubbleRender();
	tbr->setTextBubble(*tb);
 
    startBar.addComponent(bar);
    startBar.addComponent(floppy);
    startBar.addComponent(floppyIn);
    startBar.addComponent(floppyUpdate);
	startBar.addComponent(tbr);

	ButtonBuilder nextButton;
	nextButton.setInputHandle(startToolbar->getInputHandler());
	nextButton.setLabelFont(World::getFont(World::Consola));
	nextButton.setLabelMessage("Next");
	nextButton.setLabelSize(11);
	nextButton.setButtonPosition({ 50.f,0.f });
	nextButton.setSize(0.25f);
	nextButton.setSpriteSheet(desktopToModify.getButtonSheet());
	createWithEventFunc<FloppyInputComponent>(nextButton, startBar, floppyIn, ppc::incrementFloppyDialog);

    
	Entity startButton;
	spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    
    Entity startButton2;
    spawnStartButton2(startButton, desktopToModify, floppyIn, startToolbar->getInputHandler(), buttonSheet, 300, 14, 0.35f);
    
    
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    startToolbar->addEntity(startButton2);
	desktopToModify.addWindow(startToolbar);

	////////////////////////////////
	///// ICONS ON PLAYER DESKTOP
	////////////////////////////////
	Entity ConsoleIcon;
	Entity DataGraphIcon;
	Entity HardDriveIcon;
	Entity SearchIcon;
	Entity EmailIcon;

	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 425.0f, 525.0f, 0.5f, 0.30f, theInbox);
	spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 175.0f, 375.0f, 0.5f, 0.30f, theInbox);
	spawnDataGraphIcon(DataGraphIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 675.0f, 375.0f, 0.5f, 0.30f, theInbox);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 250.0f, 475.0f, 0.5f, 0.30f, theInbox);
	spawnHelpIcon(SearchIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 600.0f, 475.0f, 0.5f, 0.30f, theInbox);

    //Add Desktop Icon Floppy Triggers
    iconInputComponent* graphIconInput = dynamic_cast<iconInputComponent*>(DataGraphIcon.getComponent(2));
    graphIconInput->onOpen().addObserver(new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn));
    
    desktopWindowToModify.addEntity(ConsoleIcon);
	desktopWindowToModify.addEntity(DataGraphIcon);
	desktopWindowToModify.addEntity(HardDriveIcon);
	desktopWindowToModify.addEntity(SearchIcon);
	desktopWindowToModify.addEntity(EmailIcon);

	sf::Event ev;
	ev.type = sf::Event::EventType::Closed;
	ppc::Event ppcEvent(ev);
	ppcEvent.type = ppc::Event::EventTypes::NotificationType;
	ppcEvent.notification.count = 1;
	//theInbox->getInboxSubject().getObserverHead()->eventHandler(ppcEvent);
	//notiRenderComp->getNotiObserver().eventHandler(ppcEvent);

}

void createTeacherDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
    //////////////////////////////////////////////
    //// Create the database (really should take a seed)
    /////////////////////////////////////////////
    //TODO: FIX MEMORY LEAK
    Database* theDatabase = new Database();
    theDatabase->generateFullDatabase(0);
    
    //TODO: FIX MEMORY LEAK
    Inbox* theInbox = new Inbox();
    
    //TODO: FIX MEMORY LEAK
    emailExtraction* inbox = new emailExtraction();
    inbox->parseEmailAsJson("Email1.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email testEmail1(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(*desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop1.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    Entity startBar;
    spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    startBar.addComponent(bar);
    
    Entity startButton;
    spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    startToolbar->addEntity(startBar);
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