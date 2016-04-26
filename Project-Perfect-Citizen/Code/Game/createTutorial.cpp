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
	icons.setIconType("dataGraphIcon");
	icons.setSpritebyIndicies(0, 4, 1, 2);
	icons.setText("Graph", World::getFont(World::VT323Regular), sf::Color::Black);
	//TODO: ADD FLOPPY FUNC TO CREATE
	icons.create(graphIcon);


	//Email Icon
	Entity emailIcon;
	icons.setPosition({ 250.f,300.f });
	icons.setIconType("emailIcon");
	icons.setSpritebyIndicies(0, 10, 1, 2);
	icons.setText("Emails", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(emailIcon);


	//Help Icon
	Entity helpIcon;
	icons.setPosition({ 550.f,300.f });
	icons.setIconType("helpIcon");
	icons.setSpritebyIndicies(0, 5, 1, 2);
	icons.setText("Help", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(helpIcon);

	dt.getDesktopWindow()->addEntity(graphIcon);
	dt.getDesktopWindow()->addEntity(emailIcon);
	dt.getDesktopWindow()->addEntity(helpIcon);

	//Floppy begins here
	Window* floppyWindow = new Window(1800, 1000, sf::Color::Transparent);

	dt.setFrontTop(floppyWindow);

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

	mousePressButton* mpb = new mousePressButton();
	mpb->setInputHandle(floppyWindow->getInputHandler());
	mpb->setFloatRect(floppyWindow->getBounds());

	frontTopObsvr* frontTopObsv = new frontTopObsvr(dt);

	mpb->onClick().addObserverToBack(frontTopObsv);
	mpb->onDblClick().addObserverToBack(frontTopObsv);
	mpb->onRelease().addObserverToBack(frontTopObsv);
	mpb->onHover().addObserverToBack(frontTopObsv);


	floppyEntity.addComponent(tbr);
	floppyEntity.addComponent(floppy);
	floppyEntity.addComponent(floppyIn);
	floppyEntity.addComponent(floppyUpdate);
	floppyEntity.addComponent(mpb);

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

	ppc::FreeFunctionObserver<mousePressButton>* ffo = new FreeFunctionObserver<mousePressButton>(DisableMPB,
		dynamic_cast<mousePressButton*>(nextButton.getMousePressButton()));
	floppyIn->onSequenceEnd().addObserver(ffo);

	floppyWindow->addEntity(floppyEntity);
	

	ppc::Event ppcEv;
	ppcEv.type = ppc::Event::FloppyType;
	ppcEv.floppy.sequence = 0;
	ppcEv.floppy.frame = 0;
	summonFloppyDialog(floppyIn, ppcEv);

}
