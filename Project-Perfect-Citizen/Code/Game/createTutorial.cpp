#include "../ResourceDef.h"

#include "createTutorial.h"

//#include "../Engine/Engine.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "../Engine/Network.h"
#include "../Engine/event.h"
#include "../Engine/frontTopObserver.h"
#include "../Engine/desktop.h"
#include "../Engine/World.h"
#include "../Engine/Window.h"

#include "IconBuilder.h"
#include "ButtonBuilder.h"
#include "FloppyInputComponent.h"
#include "FloppyRenderComponent.hpp"
#include "FloppyUpdateComponent.hpp"
#include "createButton.h"

#include "TextBubble.h"
#include "TextBubbleRender.h"

#include "mousePressButton.h"

#include "iconInputComponent.h"

#include "TimerUpdateCmpnt.h"

#include "createWindow.h"
#include "startBarRenderComponent.hpp"
#include "startBarUpdateComponent.hpp"

void ppc::createTutorial(Desktop & dt) {
    
    
    ////////////////////////////////////////
    // START BAR / BUTTON
    //////////////////////////////////////
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
    spawnStartButton(startButton, dt, startToolbar->getInputHandler(), dt.getButtonSheet(), 6, 14, 0.35f);
    
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    dt.addWindow(startToolbar);
    
     //////////////////////////////////////

	//Initialize Builder for Icons
	IconBuilder icons;
	icons.setDesktop(dt);
	icons.setInbox(dt.getInbox());
	icons.setButtonSheet(dt.getButtonSheet());
	icons.setAnimSpeed(0.30f);
	icons.setInputHandle(dt.getInputHandler());
	icons.setSize(0.5f);
    
    //Console Icon
    Entity consoleIcon;
    icons.setPosition({ 175.f,375.f });
    icons.setIconType(iconInputComponent::IconType::Console);
    icons.setSpritebyIndicies(0, 8, 1, 1);
    icons.setText("Console", World::getFont(World::VT323Regular), sf::Color::White);
    icons.create(consoleIcon);
    
    //Explorer Icon
    Entity explorerIcon;
    icons.setPosition({ 250.f,475.f });
    icons.setIconType(iconInputComponent::IconType::HardDrive);
    icons.setSpritebyIndicies(0, 7, 1, 1);
    icons.setText("My Files", World::getFont(World::VT323Regular), sf::Color::White);
    icons.create(explorerIcon);

	//Graph Icon
	Entity graphIcon;
	icons.setPosition({ 675.f,375.f });
	icons.setIconType(iconInputComponent::IconType::Pipeline);
	icons.setSpritebyIndicies(0, 4, 1, 2);
	icons.setText("Graph", World::getFont(World::VT323Regular), sf::Color::White);
	icons.create(graphIcon);


	//Email Icon
	Entity emailIcon;
	icons.setPosition({ 425.f,525.f });
	icons.setIconType(iconInputComponent::IconType::Email);
	icons.setSpritebyIndicies(0, 10, 1, 2);
	icons.setText("Emails", World::getFont(World::VT323Regular), sf::Color::White);
	icons.setRenderNotifications(true);
	icons.create(emailIcon);


	//Help Icon
	Entity helpIcon;
	icons.setPosition({ 600.f,475.f });
	icons.setIconType(iconInputComponent::IconType::Help);
	icons.setSpritebyIndicies(0, 5, 1, 2);
	icons.setText("Help", World::getFont(World::VT323Regular), sf::Color::White);
	icons.setRenderNotifications(false);
	icons.create(helpIcon);
    
    dt.getDesktopWindow()->addEntity(consoleIcon);
    dt.getDesktopWindow()->addEntity(explorerIcon);
	dt.getDesktopWindow()->addEntity(graphIcon);
	dt.getDesktopWindow()->addEntity(emailIcon);
	dt.getDesktopWindow()->addEntity(helpIcon);

	////////////////////////////////////////
	// FLOPPY BEGINS HERE
	//////////////////////////////////////
	Window* floppyWindow = new Window(1800, 1000, sf::Color::Transparent);

	Entity floppyEntity;

	sf::Image floppyImage;
	floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");

	FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);
	FloppyInputComponent* floppyIn = new FloppyInputComponent();
	FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);
	floppy->renderPosition({ 780.f, 650.f });
	TextBubble* tb = new TextBubble();
    tb->setPosition(530.f, 660.f);
	TextBubbleRender* tbr = new TextBubbleRender();
	tbr->setTextBubble(*tb);
    tbr->setColor(sf::Color(243,241,206));
	tbr->setRenderable(false);

    TimerUpdateCmpnt* floppyTimer = new TimerUpdateCmpnt();
    floppyTimer->createTimer(sf::Time());
    floppyTimer->pauseTimer(0);

	floppyEntity.addComponent(tbr);
	floppyEntity.addComponent(floppy);
	floppyEntity.addComponent(floppyIn);
	floppyEntity.addComponent(floppyUpdate);
    floppyEntity.addComponent(floppyTimer);

	ButtonBuilder nextButton;
	nextButton.setInputHandle(floppyWindow->getInputHandler());
	nextButton.setLabelFont(World::getFont(World::Consola));
	nextButton.setLabelMessage("Next >");
	nextButton.setLabelSize(12);
    sf::Vector2f tbrPos = {tbr->getTextBubble().getPosition().x,tbr->getTextBubble().getPosition().y};
    nextButton.setButtonPosition({tbrPos.x+70,tbrPos.y+55});
	nextButton.setSize(0.25f);
	nextButton.setIsDisabled(true);
	nextButton.setSpriteSheet(dt.getButtonSheet());
	createWithEventFunc<FloppyInputComponent>(nextButton, floppyEntity, floppyIn, ppc::incrementFloppyDialog);

	buttonRenderComponent* mbr = nextButton.getButtonRenderComponent();
	mousePressButton* mpb = nextButton.getMousePressButton();
	TextDisplayRenderComponent* txt = nextButton.getTextRenderComponent();
	floppyIn->setFloppyButtonInputCmpt(mpb);
	floppyIn->setFloppyButtonRenderCmpt(mbr);
	floppyIn->setFloppyTextRenderCmpt(txt);



	ppc::FreeFunctionObserver<mousePressButton>* ffo = new FreeFunctionObserver<mousePressButton>(ToggleMPB,
		dynamic_cast<mousePressButton*>(nextButton.getMousePressButton()));
	floppyIn->onSequenceEnd().addObserver(ffo);

	floppyWindow->addEntity(floppyEntity);

    dt.setFrontTop(floppyWindow);


    //String Up Floppy------------------------------

    BaseObserver* tempObsvr;

    //Connect Pipeline
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn);
    dynamic_cast<iconInputComponent*>(graphIcon.getComponent(2))->onOpen().addObserver(tempObsvr);

    //Conect FloppyEnd
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn);
    floppyIn->onSequenceEnd().addObserver(tempObsvr);

    //Connect Graph
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    dt.getPlayVec().at(0)->onManip().addObserver(tempObsvr);

    //Connect Graph
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    dt.getPlayVec().at(1)->onManip().addObserver(tempObsvr);

    ////Set up starting Message
    //Event ev;
    //ev.type = ev.FloppyType;
    //ev.floppy.sequence = 0; // Line below crashes on mac - Brandon
    //ev.floppy.frame = 0;
    //summonFloppyDialog(floppyIn, ev);
    //
    
}


void ppc::createDesktopTutorial(Desktop & dt) {
    
    ////////////////////////////////////////
    // START BAR / BUTTON
    //////////////////////////////////////
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
    spawnStartButton(startButton, dt, startToolbar->getInputHandler(), dt.getButtonSheet(), 6, 14, 0.35f);
    
    startToolbar->addEntity(startBar);
    startToolbar->addEntity(startButton);
    dt.addWindow(startToolbar);
    
    //////////////////////////////////////

	//Initialize Builder for Icons
	IconBuilder icons;
	icons.setDesktop(dt);
	icons.setInbox(dt.getInbox());
	icons.setButtonSheet(dt.getButtonSheet());
	icons.setAnimSpeed(0.30f);
	icons.setInputHandle(dt.getInputHandler());
	icons.setSize(0.5f);

	//Folder Icon
	Entity hardDriveIcon;
	icons.setPosition({ 500.f,300.f });
	icons.setIconType(iconInputComponent::IconType::HardDrive);
	icons.setSpritebyIndicies(0, 7, 1, 1);
	icons.setText("My Files", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(hardDriveIcon);


	//Email Icon
	Entity emailIcon;
	icons.setPosition({ 350.f,300.f });
	icons.setIconType(iconInputComponent::IconType::Email);
	icons.setSpritebyIndicies(0, 10, 1, 2);
	icons.setText("Emails", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(emailIcon);

	dt.getDesktopWindow()->addEntity(hardDriveIcon);
	dt.getDesktopWindow()->addEntity(emailIcon);

	////////////////////////////////////////
	// SUSPICIOUS FILES TEST HERE
	//////////////////////////////////////
	WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
	spawnFileTracker(dt, fileTracker, fileTracker->getInputHandler(), 250, 50);
	SuspiciousFileHolder::setWindow(fileTracker);

	dt.addWindow(fileTracker);

	////////////////////////////////////////
	// FLOPPY BEGINS HERE
	//////////////////////////////////////
	Window* floppyWindow = new Window(1800, 1000, sf::Color::Transparent);

    Entity floppyEntity;
    
    sf::Image floppyImage;
    floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");
    
    FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);
    FloppyInputComponent* floppyIn = new FloppyInputComponent();
    FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);
    floppy->renderPosition({ 780.f, 650.f });
    TextBubble* tb = new TextBubble();
    tb->setPosition(530.f, 660.f);
    TextBubbleRender* tbr = new TextBubbleRender();
    tbr->setTextBubble(*tb);
    tbr->setColor(sf::Color(243,241,206));
    tbr->setRenderable(false);
    
    floppyEntity.addComponent(tbr);
    floppyEntity.addComponent(floppy);
    floppyEntity.addComponent(floppyIn);
    floppyEntity.addComponent(floppyUpdate);
    
    ButtonBuilder nextButton;
    nextButton.setInputHandle(floppyWindow->getInputHandler());
    nextButton.setLabelFont(World::getFont(World::Consola));
    nextButton.setLabelMessage("Next >");
    nextButton.setLabelSize(12);
    sf::Vector2f tbrPos = {tbr->getTextBubble().getPosition().x,tbr->getTextBubble().getPosition().y};
    nextButton.setButtonPosition({tbrPos.x+70,tbrPos.y+55});
	nextButton.setSize(0.25f);
	nextButton.setIsDisabled(true);
	nextButton.setSpriteSheet(dt.getButtonSheet());
	createWithEventFunc<FloppyInputComponent>(nextButton, floppyEntity, floppyIn, ppc::incrementFloppyDialog);

	buttonRenderComponent* mbr = nextButton.getButtonRenderComponent();
	mousePressButton* mpb = nextButton.getMousePressButton();
	TextDisplayRenderComponent* txt = nextButton.getTextRenderComponent();
	floppyIn->setFloppyButtonInputCmpt(mpb);
	floppyIn->setFloppyButtonRenderCmpt(mbr);
	floppyIn->setFloppyTextRenderCmpt(txt);

	ppc::FreeFunctionObserver<mousePressButton>* ffo = new FreeFunctionObserver<mousePressButton>(ToggleMPB,
		dynamic_cast<mousePressButton*>(nextButton.getMousePressButton()));
	floppyIn->onSequenceEnd().addObserver(ffo);

	floppyWindow->addEntity(floppyEntity);

	dt.setFrontTop(floppyWindow);




    //String Up Floppy------------------------------

    //Conect FloppyEnd
    BaseObserver* tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn);
    floppyIn->onSequenceEnd().addObserver(tempObsvr);

    //Connect File Icon
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    dynamic_cast<iconInputComponent*>(hardDriveIcon.getComponent(2))->onOpen().addObserver(tempObsvr);

    //Connect Email Icon
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    dynamic_cast<iconInputComponent*>(emailIcon.getComponent(2))->onOpen().addObserver(tempObsvr);

    //Connect NodeState
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    dt.getNodeState()->onOpen().addObserver(tempObsvr);

    //Connect SuspiciousFileHolder
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(enableFloppyDialog, floppyIn);
    SuspiciousFileHolder::onChange.addObserver(tempObsvr);

    //Set up starting Message
    Event ev;
    ev.type = ev.FloppyType;
    ev.floppy.sequence = 0; // Line below crashes on mac - Brandon
	ev.floppy.sequence = FloppyInputComponent::DesktopStart;
	ev.floppy.frame = 0;
    summonFloppyDialog(floppyIn, ev);

}
