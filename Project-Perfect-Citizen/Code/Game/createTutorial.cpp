#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createTutorial.h"

#include "../Engine/Engine.h"
#include "IconBuilder.h"
#include "ButtonBuilder.h"

#include "../Game/FloppyInputComponent.h"
#include "../Game/FloppyRenderComponent.hpp"
#include "../Game/FloppyUpdateComponent.hpp"

#include "../Game/TextBubble.h"
#include "../Game/TextBubbleRender.h"

#include "../Game/mousePressButton.h"

#include "../Engine/event.h"
#include "../Engine/frontTopObserver.h"

#include "iconInputComponent.h"

void ppc::createTutorial(Desktop & dt) {

	//Initialize Builder for Icons
	IconBuilder icons;
	icons.setDesktop(dt);
	icons.setInbox(dt.getInbox());
	icons.setButtonSheet(dt.getButtonSheet());
	icons.setAnimSpeed(0.30f);
	icons.setInputHandle(dt.getInputHandler());
	icons.setSize(0.5f);

	//Graph Icon
	Entity graphIcon;
	icons.setPosition({ 400.f,300.f });
	icons.setIconType(iconInputComponent::IconType::Pipeline);
	icons.setSpritebyIndicies(0, 4, 1, 2);
	icons.setText("Graph", World::getFont(World::VT323Regular), sf::Color::Black);
	//TODO: ADD FLOPPY FUNC TO CREATE
	icons.create(graphIcon);


	//Email Icon
	Entity emailIcon;
	icons.setPosition({ 250.f,300.f });
	icons.setIconType(iconInputComponent::IconType::Email);
	icons.setSpritebyIndicies(0, 10, 1, 2);
	icons.setText("Emails", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(emailIcon);


	//Help Icon
	Entity helpIcon;
	icons.setPosition({ 550.f,300.f });
	icons.setIconType(iconInputComponent::IconType::Help);
	icons.setSpritebyIndicies(0, 5, 1, 2);
	icons.setText("Help", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(helpIcon);

	dt.getDesktopWindow()->addEntity(graphIcon);
	dt.getDesktopWindow()->addEntity(emailIcon);
	dt.getDesktopWindow()->addEntity(helpIcon);

	//Floppy begins here
	Window* floppyWindow = new Window(1800, 1000, sf::Color::Transparent);

	Entity floppyEntity;

	sf::Image floppyImage;
	floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");

	FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);
	FloppyInputComponent* floppyIn = new FloppyInputComponent();
	FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);
	floppy->renderPosition({ 400.f, 0.f });

	TextBubble* tb = new TextBubble();
	tb->setPosition(0.f, 0.f);
	TextBubbleRender* tbr = new TextBubbleRender();
	tbr->setTextBubble(*tb);
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
	nextButton.setButtonPosition({ 70.f,100.f });
	nextButton.setSize(0.25f);
	nextButton.setIsDisabled(true);
	nextButton.setSpriteSheet(dt.getButtonSheet());
	createWithEventFunc<FloppyInputComponent>(nextButton, floppyEntity, floppyIn, ppc::incrementFloppyDialog);

	ppc::FreeFunctionObserver<mousePressButton>* ffo = new FreeFunctionObserver<mousePressButton>(ToggleMPB,
		dynamic_cast<mousePressButton*>(nextButton.getMousePressButton()));
	floppyIn->onSequenceEnd().addObserver(ffo);

	floppyWindow->addEntity(floppyEntity);

    dt.setFrontTop(floppyWindow);


    //String Up Floppy------------------------------

    //Connect Pipeline
    BaseObserver* tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn);
    dynamic_cast<iconInputComponent*>(graphIcon.getComponent(2))->onOpen().addObserver(tempObsvr);

    //Conect FloppyEnd
    tempObsvr = new FreeFunctionObserver<FloppyInputComponent>(summonFloppyDialog, floppyIn);
    floppyIn->onSequenceEnd().addObserver(tempObsvr);

}