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

#include "../Engine/event.h"

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
	icons.setPosition({ 500.f,300.f });
	icons.setIconType("dataGraphIcon");
	icons.setSpritebyIndicies(0, 4, 1, 2);
	icons.setText("Graph", World::getFont(World::VT323Regular), sf::Color::Black);
	//TODO: ADD FLOPPY FUNC TO CREATE
	icons.create(graphIcon);

	//Email Icon
	Entity emailIcon;
	icons.setPosition({ 350.f,300.f });
	icons.setIconType("emailIcon");
	icons.setSpritebyIndicies(0, 10, 1, 2);
	icons.setText("Emails", World::getFont(World::VT323Regular), sf::Color::Black);
	icons.create(emailIcon);

	

	dt.getDesktopWindow()->addEntity(graphIcon);
	dt.getDesktopWindow()->addEntity(emailIcon);


	Window* floppyWindow = new Window(1000, 300, sf::Color::Transparent);
	floppyWindow->setPosition(0, 0);

	Entity floppyEntity;

	sf::Image floppyImage;
	floppyImage.loadFromFile(resourcePath() + "Floppy_Sheet.png");

	FloppyRenderComponent* floppy = new FloppyRenderComponent(floppyImage);

	FloppyInputComponent* floppyIn = new FloppyInputComponent();

	FloppyUpdateComponent* floppyUpdate = new FloppyUpdateComponent(*floppy, 0.12f);
	floppy->renderPosition({ 0.f, 0.f });
	TextBubble* tb = new TextBubble();
	tb->setPosition(0.f, 0.f);
	TextBubbleRender* tbr = new TextBubbleRender();
	tbr->setTextBubble(*tb);

	floppyEntity.addComponent(floppy);
	floppyEntity.addComponent(floppyIn);
	floppyEntity.addComponent(floppyUpdate);
	floppyEntity.addComponent(tbr);

	ButtonBuilder nextButton;
	nextButton.setInputHandle(floppyWindow->getInputHandler());
	nextButton.setLabelFont(World::getFont(World::Consola));
	nextButton.setLabelMessage("Next");
	nextButton.setLabelSize(11);
	nextButton.setButtonPosition({ 0.f,0.f });
	nextButton.setSize(0.25f);
	nextButton.setSpriteSheet(dt.getButtonSheet());
	createWithEventFunc<FloppyInputComponent>(nextButton, floppyEntity, floppyIn, ppc::incrementFloppyDialog);

	floppyWindow->addEntity(floppyEntity);

	dt.addWindow(floppyWindow);

	ppc::Event ppcEv;
	ppcEv.type = ppc::Event::FloppyType;
	ppcEv.floppy.sequence = 0;
	ppcEv.floppy.frame = 0;
	summonFloppyDialog(floppyIn, ppcEv);
	

}
