
#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createDesktop.h"


#include <iostream>
#include <fstream>

//#include "../Engine/Engine.h"
#include "../Engine/World.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "../Engine/desktop.h"
#include "../Engine/Window.h"

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
#include "createWindow.h"
#include "FloppyUpdateComponent.hpp"
#include "FloppyRenderComponent.hpp"
#include "FloppyInputComponent.h"
#include "TextBubble.h"
#include "TextBubbleRender.h"
#include "ButtonBuilder.h"
#include "IconBuilder.h"
#include "spriteRenderComponent.hpp"
#include "startBarRenderComponent.hpp"
#include "startBarUpdateComponent.hpp"
#include "Email.h"

#include "notifcationRenderComponent.h"
#include "flaggedFileInputComponent.h"


#include "../Library/json/json.h"

using namespace ppc;

void ppc::createLoginDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {

    Entity title;

    spriteRenderComponent* titleRender = new spriteRenderComponent(desktopToModify.getButtonSheet(), 0 ,7, 6, 1);
    titleRender->setRenderPosition({100, 200});
    
    title.addComponent(titleRender);

    WindowInterface* loginPrompt = new Window(480, 150, sf::Color(170, 170, 170));
    loginPrompt->setPosition(static_cast<float>(World::getGameScreen().getSize().x/2)-(loginPrompt->getSize().x/2), 
		                     static_cast<float>(World::getGameScreen().getSize().y/2));

    spawnLoginPrompt(loginPrompt, loginPrompt->getInputHandler(), buttonSheet, 400, 500);

    desktopToModify.addWindow(loginPrompt);
    desktopToModify.getDesktopWindow()->addEntity(title);

// loginWindow->addEntity(title);

}


void ppc::createPlayerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {
	
	std::vector<std::string> firstLsCommand;
	std::string ls = "ls";
	firstLsCommand.push_back(ls);
	commandFn firstLs = findFunction(ls);
	firstLs(*desktopToModify.getNodeState(), firstLsCommand);
	    
    sf::Image floppyImage;
    floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");

	//TODO: FIX MEMORY LEAK
    Database* theDatabase = new Database();
	//theDatabase->generateFullDatabase(200);

    //TODO: FIX MEMORY LEAK
	Inbox* theInbox = &desktopToModify.getInbox();

    emailExtraction inbox;// = new emailExtraction();
    inbox.parseEmailAsJson("PlayerEmail.json");
    

    for(unsigned int i = 0; i < inbox.getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox.getTo().at(i), inbox.getFrom().at(i), inbox.getSubject().at(i), inbox.getBody().at(i), inbox.getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
	//////////////////////////////////////////////
	//// Create the start menu
	/////////////////////////////////////////////
	ppc::WindowInterface* startToolbar =
		new ppc::Window(1000, 200, sf::Color(195, 195, 195,0));
	startToolbar->setPosition(0, 735);
    
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    
    startBarRender->renderPosition({0,4});
    
    startBarUpdateComponent* startBarUpdate = new startBarUpdateComponent(*startBarRender);
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);

    FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);
    FloppyInputComponent* floppyIn = new FloppyInputComponent();
    FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);
	TextBubble* tb = new TextBubble();

	Entity startButton;
	spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
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
    
    desktopWindowToModify.addEntity(ConsoleIcon);
	desktopWindowToModify.addEntity(DataGraphIcon);
	desktopWindowToModify.addEntity(HardDriveIcon);
	desktopWindowToModify.addEntity(SearchIcon);
	desktopWindowToModify.addEntity(EmailIcon);

}

void ppc::createTeacherDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
    //////////////////////////////////////////////
    //// Create the database (really should take a seed)
    /////////////////////////////////////////////
    //TODO: FIX MEMORY LEAK
    Database* theDatabase = new Database();
    //theDatabase->generateFullDatabase(0);
    
    //TODO: FIX MEMORY LEAK
    Inbox* theInbox = new Inbox();
    
    //TODO: FIX MEMORY LEAK
    emailExtraction* inbox = new emailExtraction();
    inbox->parseEmailAsJson("Email1.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
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
    
    //Entity startBar;
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBar.addComponent(startBarRender);
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    //startBar.addComponent(bar);
    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 350.0f, 400.0f, 0.4f, 0.25f, theInbox);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 125.0f, 175.0f, 0.4f, 0.25f, theInbox);
	spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 525.0f, 200.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 300.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 600.0f, 500.0f, 0.5f, 0.25f, theInbox);


	IconBuilder builder;
	builder.setDesktop(desktopToModify);
	builder.setInbox(desktopToModify.getInbox());
	builder.setButtonSheet(desktopToModify.getButtonSheet());
	builder.setAnimSpeed(0.30f);
	builder.setInputHandle(desktopToModify.getInputHandler());
	builder.setSize(0.5f);

	// Create teacher desktop folders/files
	Entity BlueBirdFile;
	builder.setPosition({ 750.0f, 350.0f });
	builder.setIconType(iconInputComponent::IconType::File);
	builder.setSpritebyIndicies(0, 0, 1, 3);
	builder.setText("Bluebird_by_Charles_Bukowski.txt", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(BlueBirdFile);
	desktopWindowToModify.addEntity(BlueBirdFile);

	Entity SisyphusFile;
	builder.setPosition({ 50.0f, 500.0f });
	builder.setIconType(iconInputComponent::IconType::File);
	builder.setSpritebyIndicies(0, 0, 1, 3);
	builder.setText("Myth_of_Sisyphus_by_Albert_Camus.txt", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(SisyphusFile);
	desktopWindowToModify.addEntity(SisyphusFile);

    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);
    
	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
	desktopToModify.addWindow(fileTracker);
	ppc::SuspiciousFileHolder::setWindow(fileTracker);

}

void ppc::createDummyDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
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
    inbox->parseEmailAsJson("Email0.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(*desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop0.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    //Entity startBar;
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    //startBar.addComponent(bar);
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBar.addComponent(startBarRender);
    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 125.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 600.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 325.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 425.0f, 600.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);

	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
	desktopToModify.addWindow(fileTracker);
	ppc::SuspiciousFileHolder::setWindow(fileTracker);
    
}

void ppc::createArtistDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
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
    inbox->parseEmailAsJson("Email2.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(*desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop2.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    //Entity startBar;
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    //startBar.addComponent(bar);
    
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBar.addComponent(startBarRender);
    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 125.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 225.0f, 600.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 325.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 425.0f, 600.0f, 0.5f, 0.25f, theInbox);

	IconBuilder builder;
	builder.setDesktop(desktopToModify);
	builder.setInbox(desktopToModify.getInbox());
	builder.setButtonSheet(desktopToModify.getButtonSheet());
	builder.setAnimSpeed(0.30f);
	builder.setInputHandle(desktopToModify.getInputHandler());
	builder.setSize(0.5f);

	// Create teacher desktop folders/files
	/*Entity folder1;
	builder.setPosition({ 200.0f, 100.0f });
	builder.setIconType(iconInputComponent::IconType::Folder);
	builder.setSpritebyIndicies(0, 9, 1, 1);
	builder.setText("Note_to_Voyeur", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(folder1);
	desktopWindowToModify.addEntity(folder1);

	Entity folder2;
	builder.setPosition({ 400.0f, 100.0f });
	builder.setText("Projects", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(folder2);
	desktopWindowToModify.addEntity(folder2);*/

	Entity file1;
	builder.setPosition({ 600.0f, 100.0f });
	builder.setIconType(iconInputComponent::IconType::File);
	builder.setSpritebyIndicies(0, 0, 1, 3);
	builder.setText("BankPark_Print.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file1);
	desktopWindowToModify.addEntity(file1);

	Entity file2;
	builder.setPosition({ 300.0f, 200.0f });
	builder.setText("blueprints_1.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file2);
	desktopWindowToModify.addEntity(file2);

	Entity file3;
	builder.setPosition({ 500.0f, 200.0f });
	builder.setText("Blueprints_2.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file3);
	desktopWindowToModify.addEntity(file3);

	Entity file4;
	builder.setPosition({ 200.0f, 300.0f });
	builder.setText("Dancers_at_the_Barre.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file4);
	desktopWindowToModify.addEntity(file4);

	Entity file5;
	builder.setPosition({ 400.0f, 300.0f });
	builder.setText("dc_fed_board5.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file5);
	desktopWindowToModify.addEntity(file5);

	Entity file6;
	builder.setPosition({ 600.0f, 300.0f });
	builder.setText("Old_Mission_Unit_4.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file6);
	desktopWindowToModify.addEntity(file6);

	Entity file7;
	builder.setPosition({ 300.0f, 400.0f });
	builder.setText("plans_print.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file7);
	desktopWindowToModify.addEntity(file7);

	Entity file8;
	builder.setPosition({ 500.0f, 400.0f });
	builder.setText("wtcblueprints3.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file8);
	desktopWindowToModify.addEntity(file8);

	Entity file9;
	builder.setPosition({ 200.0f, 500.0f });
	builder.setText("calmness.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file9);
	desktopWindowToModify.addEntity(file9);

	Entity file10;
	builder.setPosition({ 400.0f, 500.0f });
	builder.setText("shiver.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file10);
	desktopWindowToModify.addEntity(file10);

	Entity file11;
	builder.setPosition({ 600.0f, 500.0f });
	builder.setText("TRANQUILITY.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file11);
	desktopWindowToModify.addEntity(file11);

	Entity file12;
	builder.setPosition({ 600.0f, 600.0f });
	builder.setText("optimism.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file12);
	desktopWindowToModify.addEntity(file12);

    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);

	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
	desktopToModify.addWindow(fileTracker);
	ppc::SuspiciousFileHolder::setWindow(fileTracker);
    
}

void ppc::createPoliticianDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
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
    inbox->parseEmailAsJson("Email3.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(*desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("Desktop3.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
   // Entity startBar;
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    //startBar.addComponent(bar);
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBar.addComponent(startBarRender);
    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 25.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 125.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 225.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 325.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 425.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);

	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
	desktopToModify.addWindow(fileTracker);
	ppc::SuspiciousFileHolder::setWindow(fileTracker);
	
    
}

void ppc::createTrailerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
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
    inbox->parseEmailAsJson("TrailerEmail.json");
    
    for(unsigned int i = 0; i < inbox->getSubject().size(); i++){
        Email* testEmail1 = new Email(inbox->getTo().at(i), inbox->getFrom().at(i), inbox->getSubject().at(i), inbox->getBody().at(i), inbox->getVisible().at(i), "image.jpg");
        theInbox->addEmailToList(testEmail1);
    }
    
    //////////////////////////////////////////////
    //// Script to create file tree
    /////////////////////////////////////////////
    desktopExtractionComponent* teacherFiles = new desktopExtractionComponent(*desktopToModify.getNodeState());
    Json::Value parsed = teacherFiles->parseDesktopAsJson("TrailerDesktop.json", "Desktop");
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    //Entity startBar;
    //spriteRenderComponent* bar = new spriteRenderComponent(buttonSheet, 7,7,startToolbar->getBounds().width,1);
    //startBar.addComponent(bar);
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBar.addComponent(startBarRender);
    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, *theDatabase, iconSheet,  buttonSheet, 25.0f, 25.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 125.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 225.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 325.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, *theDatabase, iconSheet, buttonSheet, 25.0f, 425.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(ChatIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);
    
}