
#include "../ResourceDef.h"

#include "createDesktop.h"


#include <iostream>
#include <fstream>

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
#include "TextDisplayBuilder.h"
#include "notifcationRenderComponent.h"
#include "flaggedFileInputComponent.h"
#include "TextCharacterUpdate.h"
#include "ReportScreenInput.h"
#include "ReportEndObsvr.h"
#include "TextDisplayRenderComponent.h"
#include "../Library/json/json.h"

using namespace ppc;

void ppc::createLoginDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet) {

    Entity title;

    spriteRenderComponent* titleRender = new spriteRenderComponent(desktopToModify.getButtonSheet(), 0 ,7, 6, 1);
    titleRender->setRenderPosition({100, 200});
    
    title.addComponent(titleRender);

    WindowInterface* loginPrompt = new Window(480, 150, sf::Color(170, 170, 170));
    loginPrompt->setPosition(static_cast<float>(250),
		                     static_cast<float>(400));

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


    Database theDatabase;


	Inbox* theInbox = &desktopToModify.getInbox();

    
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

	spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 425.0f, 525.0f, 0.5f, 0.30f, theInbox);
	spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 175.0f, 375.0f, 0.5f, 0.30f, theInbox);
	spawnDataGraphIcon(DataGraphIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 675.0f, 375.0f, 0.5f, 0.30f, theInbox);
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 250.0f, 475.0f, 0.5f, 0.30f, theInbox);
	spawnHelpIcon(SearchIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 600.0f, 475.0f, 0.5f, 0.30f, theInbox);
    
    desktopWindowToModify.addEntity(ConsoleIcon);
	desktopWindowToModify.addEntity(DataGraphIcon);
	desktopWindowToModify.addEntity(HardDriveIcon);
	desktopWindowToModify.addEntity(SearchIcon);
	desktopWindowToModify.addEntity(EmailIcon);

}

void ppc::createTeacherDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
	World::getAudio().stopAllSounds();
	World::getAudio().addBgm("SoundTrack_Extraction.ogg");
	World::getAudio().loopBgm();
	World::getAudio().playBgm();
    Database theDatabase;

    Inbox* theInbox = &desktopToModify.getInbox();
   
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
    
    startBarUpdateComponent* startBarUpdate = new startBarUpdateComponent(*startBarRender);
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);
    
    Entity startButton;
    spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    desktopToModify.addWindow(startToolbar);

    
    ////////////////////////////////
    ///// ICONS ON TEACHER DESKTOP
    ////////////////////////////////
    Entity ChatIcon;
    Entity HardDriveIcon;
    Entity SettingsIcon;
    Entity ConsoleIcon;
    Entity EmailIcon;
    
	spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 125.0f, 175.0f, 0.4f, 0.25f, theInbox);
	spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 525.0f, 200.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 225.0f, 300.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 600.0f, 500.0f, 0.5f, 0.25f, theInbox);


	IconBuilder builder;
	builder.setDesktop(desktopToModify);
	builder.setInbox(desktopToModify.getInbox());
	builder.setButtonSheet(desktopToModify.getButtonSheet());
	builder.setAnimSpeed(0.30f);
	builder.setInputHandle(desktopToModify.getInputHandler());
	builder.setSize(0.5f);

	// Create teacher desktop folders/files
	/*Entity BlueBirdFile;
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
	desktopWindowToModify.addEntity(SisyphusFile);*/

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
    

    Database theDatabase;

    Inbox* theInbox = &desktopToModify.getInbox();
   
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
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);

    
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
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, theDatabase, iconSheet,  buttonSheet, 25.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 125.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 225.0f, 600.0f, 0.5f, 0.25f, theInbox);
    spawnChatIcon(ChatIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 325.0f, 600.0f, 0.4f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 425.0f, 600.0f, 0.5f, 0.25f, theInbox);
    
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
  
	World::getAudio().stopAllSounds();
	World::getAudio().addBgm("SoundTrack_Extraction.ogg");
	World::getAudio().loopBgm();
	World::getAudio().playBgm();
	Database theDatabase;

	Inbox* theInbox = &desktopToModify.getInbox();
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBarUpdateComponent* startBarUpdate = new startBarUpdateComponent(*startBarRender);
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);
    
    Entity startButton;
    spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    desktopToModify.addWindow(startToolbar);
    
    
    ////////////////////////////////
    ///// ICONS ON TEACHER DESKTOP
    ////////////////////////////////
    Entity HardDriveIcon;
    Entity SettingsIcon;
    Entity ConsoleIcon;
    Entity EmailIcon;
    
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 100.0f, 200.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 500.0f, 600.0f, 0.5f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 100.0f, 400.0f, 0.5f, 0.25f, theInbox);

	IconBuilder builder;
	builder.setDesktop(desktopToModify);
	builder.setInbox(desktopToModify.getInbox());
	builder.setButtonSheet(desktopToModify.getButtonSheet());
	builder.setAnimSpeed(0.30f);
	builder.setInputHandle(desktopToModify.getInputHandler());
	builder.setSize(0.5f);

	Entity file1;
	builder.setPosition({ 700.0f, 400.0f });
	builder.setIconType(iconInputComponent::IconType::File);
	builder.setSpritebyIndicies(0, 14, 1, 0);
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
	builder.setPosition({ 300.0f, 600.0f });
	builder.setText("optimism.jpg", World::getFont(World::VT323Regular), sf::Color::White);
	builder.create(file12);
	desktopWindowToModify.addEntity(file12);

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
	World::getAudio().stopAllSounds();
	World::getAudio().addBgm("SoundTrack_Extraction.ogg");
	World::getAudio().loopBgm();
	World::getAudio().playBgm();
	Database theDatabase;

	Inbox* theInbox = &desktopToModify.getInbox();

    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBarUpdateComponent* startBarUpdate = new startBarUpdateComponent(*startBarRender);
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);
    
    Entity startButton;
    spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    desktopToModify.addWindow(startToolbar);
    
    
    ////////////////////////////////
    ///// ICONS ON TEACHER DESKTOP
    ////////////////////////////////
    Entity BrowserIcon;
    Entity HardDriveIcon;
    Entity SettingsIcon;
    Entity ConsoleIcon;
    Entity EmailIcon;
    
    spawnBrowserIcon(BrowserIcon, desktopToModify, ih, theDatabase, iconSheet,  buttonSheet, 25.0f, 25.0f, 0.4f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 25.0f, 125.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 25.0f, 225.0f, 0.5f, 0.25f, theInbox);
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 25.0f, 325.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(BrowserIcon);
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(SettingsIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);

	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
	desktopToModify.addWindow(fileTracker);
	ppc::SuspiciousFileHolder::setWindow(fileTracker);
	
    
}

void ppc::createHackerDesktop(Desktop& desktopToModify, WindowInterface& desktopWindowToModify, InputHandler& ih, sf::Image& iconSheet, sf::Image& buttonSheet ) {
    
    Database theDatabase;
    
    Inbox* theInbox = &desktopToModify.getInbox();
    
    //////////////////////////////////////////////
    //// Create the start menu
    /////////////////////////////////////////////
    ppc::WindowInterface* startToolbar =
    new ppc::Window(1000, 75, sf::Color(195, 195, 195,0));
    startToolbar->setPosition(0, 735);
    
    Entity startBar;
    startBarRenderComponent* startBarRender = new startBarRenderComponent(World::getFont(ppc::World::FontList::Consola));
    startBarRender->renderPosition({0,4});
    startBarUpdateComponent* startBarUpdate = new startBarUpdateComponent(*startBarRender);
    startBar.addComponent(startBarRender);
    startBar.addComponent(startBarUpdate);
    
    Entity startButton;
    spawnStartButton(startButton, desktopToModify, startToolbar->getInputHandler(), buttonSheet, 6, 14, 0.35f);
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    desktopToModify.addWindow(startToolbar);
    
    
    ////////////////////////////////
    ///// ICONS ON TEACHER DESKTOP
    ////////////////////////////////
    IconBuilder builder;
    builder.setDesktop(desktopToModify);
    builder.setInbox(desktopToModify.getInbox());
    builder.setButtonSheet(desktopToModify.getButtonSheet());
    builder.setAnimSpeed(0.30f);
    builder.setInputHandle(desktopToModify.getInputHandler());
    builder.setSize(0.5f);
    
    Entity Resonation_1;
    builder.setPosition({ 650.0f, 400.0f });
    builder.setIconType(iconInputComponent::IconType::File);
    builder.setSpritebyIndicies(0, 0, 1, 3);
    builder.setText("READ_ME_1.txt", World::getFont(World::VT323Regular), sf::Color::White);
    builder.create(Resonation_1);
    desktopWindowToModify.addEntity(Resonation_1);
    
    Entity HardDriveIcon;
    Entity ConsoleIcon;
    Entity EmailIcon;
    
    spawnConsoleIcon(ConsoleIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 200.0f, 400.0f, 0.5f, 0.25f, theInbox);
    spawnHardDriveIcon(HardDriveIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 325.0f, 520.0f, 0.4f, 0.25f, theInbox);
    spawnEmailIcon(EmailIcon, desktopToModify, ih, theDatabase, iconSheet, buttonSheet, 525.0f, 520.0f, 0.5f, 0.25f, theInbox);
    
    desktopWindowToModify.addEntity(HardDriveIcon);
    desktopWindowToModify.addEntity(ConsoleIcon);
    desktopWindowToModify.addEntity(EmailIcon);
    
    WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
    spawnFileTracker(desktopToModify, fileTracker, fileTracker->getInputHandler(), 250, 50);
    desktopToModify.addWindow(fileTracker);
    ppc::SuspiciousFileHolder::setWindow(fileTracker);
}

//depricated
//void ppc::createPostHackerDesktop(Desktop& desktopToModify) {
//	ppc::Window* endScreen = new Window(1800, 1000);
//
//	Entity endEntity;
//
//	std::ifstream endFile(resourcePath() + "Reports/DE3B.txt");
//
//	std::string content((std::istreambuf_iterator<char>(endFile)),
//		(std::istreambuf_iterator<char>()));
//
//	TextDisplayBuilder reportText;
//	reportText.setColor(sf::Color::Red);
//	reportText.setFont(World::getFont(World::FontList::Consola));
//	reportText.setPosition({ 100,100 });
//	reportText.setSize(25);
//	reportText.setString("");
//
//	reportText.create(endEntity);
//
//	TextCharacterUpdate* tcu = new TextCharacterUpdate();
//	ReportEndObsvr* reO = new ReportEndObsvr(*endScreen);
//	reO->setPos(400.f, 700.f);
//	tcu->onAnimEnd().addObserver(reO);
//
//	TextDisplayRenderComponent* tdrc = dynamic_cast<TextDisplayRenderComponent*>(endEntity.getComponent(0));
//	tcu->setTextDisplay(*tdrc);
//	tcu->setContent(content);
//	tcu->setDisplayRate(sf::milliseconds(sf::Int32(30.0f)));
//
//	ReportScreenInput* rsi = new ReportScreenInput(endScreen->getInputHandler());
//	rsi->setTextCharacterUpdate(*tcu);
//
//
//	endEntity.addComponent(tcu);
//	endEntity.addComponent(rsi);
//
//	endScreen->addEntity(endEntity);
//
//	desktopToModify.setFrontTop(endScreen, false);
//}
