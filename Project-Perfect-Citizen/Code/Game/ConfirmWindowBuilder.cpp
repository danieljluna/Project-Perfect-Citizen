#include "ConfirmWindowBuilder.h"

#include "../Engine/WindowInterface.h"
#include "../Engine/BorderDecorator.h"
#include "../Engine/World.h"
#include "../Engine/desktop.h"
#include "../Engine/SuspiciousFileHolder.h"
#include "../Engine/Window.h"

#include "explorerFileInputComponent.h"
#include "ReportScreenObsvr.h"
#include "createButton.h"
#include "createWindow.h"
#include "ButtonBuilder.h"
#include "errorMessageRenderComponent.h"


using namespace ppc;

ppc::ConfirmWindowBuilder::ConfirmWindowBuilder()
{
	posX = 0;
	posY = 0;

	spriteSheet = nullptr;
	inputHandle = nullptr;

	windowCaption = "Confirm?";
	confirmMessage = "";
	confirmButtonMessage = "";
	cancelButtonMessage = "";

	messageFontSize = 12;

	messageFont = sf::Font();
	buttonFont = sf::Font();
}

ppc::ConfirmWindowBuilder::~ConfirmWindowBuilder()
{
}

void ppc::ConfirmWindowBuilder::setPosition(sf::Vector2f pos)
{
	posX = pos.x;
	posY = pos.y;
}

void ppc::ConfirmWindowBuilder::setWindowCaption(std::string msg)
{
	windowCaption = msg;
}

void ppc::ConfirmWindowBuilder::setConfirmMessage(std::string msg)
{
	confirmMessage = msg;
}

void ppc::ConfirmWindowBuilder::setConfirmButtonLabel(std::string conlabl)
{
	confirmButtonMessage = conlabl;
}

void ppc::ConfirmWindowBuilder::setCancelButtonLabel(std::string canlabl)
{
	cancelButtonMessage = canlabl;
}

void ppc::ConfirmWindowBuilder::setMessageFont(sf::Font mf)
{
	messageFont = mf;
}

void ppc::ConfirmWindowBuilder::setMessageFontSize(int s)
{
	messageFontSize = s;
}

void ppc::ConfirmWindowBuilder::setButtonLabelFont(sf::Font f)
{
	buttonFont = f;
}

void ppc::ConfirmWindowBuilder::setSpriteSheet(sf::Image & s)
{
	spriteSheet = &s;
}

ppc::mousePressButton * ppc::ConfirmWindowBuilder::getConfirmButtonMPB()
{
	return confirmBtnIC;
}

ppc::mousePressButton * ppc::ConfirmWindowBuilder::getCancelButtonMPB()
{
	return cancelBtnIC;
}

void ppc::ConfirmWindowBuilder::create(WindowInterface*& win)
{
	
	errorMessageRenderComponent* eMRC = new errorMessageRenderComponent(messageFont, confirmMessage,
		win->getSize().x / 3, win->getSize().y / 3, messageFontSize);

	/////////////////////////////////////////
	/////// ENTITIES
	///////////////////////////////////////
	Entity alertIcon;
	float alertScale = 0.5f;
	float alertWidth = 128.0;
	float windowWidth = static_cast<float>(win->getSize().x);
	float windowHeight = static_cast<float>(win->getSize().y);
	float alertX = windowWidth - ((alertWidth * alertScale) + (3 * (windowWidth / 4)));
	float alertY = (windowHeight - (alertWidth * alertScale)) / 3;
	float buttonScale = 0.25f;
	float buttonX = ((windowWidth - (alertWidth * buttonScale)) / 2);
	float buttonY = (2 * (windowHeight / 3));
	spawnAlertIcon(alertIcon, win->getInputHandler(), *spriteSheet, alertX, alertY, 0.5f);

	float newWindowWidth = ((windowWidth)-(eMRC->getText()->getLocalBounds().width - windowWidth));

	Entity errorMessageDisplayBox;
	errorMessageDisplayBox.addComponent(eMRC);

	// Confirm Button
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(buttonX, buttonY));
	builder.setInputHandle(win->getInputHandler());
	builder.setSize(0.25f);
	builder.setSpritesByIndicies(0, 2, 2, 1);
	builder.setSpriteSheet(*spriteSheet);
	builder.setLabelMessage(confirmButtonMessage);
	builder.setLabelFont(buttonFont);
	builder.setLabelSize(12);
	Entity ent;
	builder.create(ent);
	confirmBtnIC = builder.getMousePressButton();

	// Cancel Button
	builder.setButtonPosition(sf::Vector2f(buttonX+100, buttonY));
	builder.setLabelMessage(cancelButtonMessage);
	Entity ent2;
	createWithEventFunc(builder, ent2, win, close_window);


	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	win->addEntity(errorMessageDisplayBox);
	win->addEntity(alertIcon);
	win->addEntity(ent);
	win->addEntity(ent2);
	win->setPosition(posX, posY);
	win = new BorderDecorator(*win);
	dynamic_cast<BorderDecorator*>(win)->addButton(*spriteSheet, closeWindow);
	dynamic_cast<BorderDecorator*>(win)->setCaption(windowCaption);

}


bool ppc::ConfirmSubmitFiles(ppc::Desktop * ptr, ppc::Event ev)
{
	/* Check to make sure player has flagged three files */
	WindowInterface* submitResponse = new Window(400, 150, sf::Color(170, 170, 170));

	if (SuspiciousFileHolder::getBftVector().size() < 3) {
		spawnErrorMessage(submitResponse, submitResponse->getInputHandler(), 
			ptr->getButtonSheet(), 300, 150, "Error: The DCPS requires at least 3 flagged files", "Insufficient Files Flagged");
		ptr->addWindow(submitResponse);
	}
	
	else {
		ConfirmWindowBuilder builder;
		// Buttons //
		builder.setButtonLabelFont(World::getFont(World::Consola));
		builder.setCancelButtonLabel("CANCEL");
		builder.setConfirmButtonLabel("CONFIRM");
		builder.setConfirmMessage("Are you sure you want to\n submit these files?");
		builder.setMessageFont(World::getFont(World::Consola));
		builder.setMessageFontSize(12);
		builder.setPosition(sf::Vector2f({ 300.0f, 300.0f }));
		builder.setSpriteSheet(ptr->getButtonSheet());
		builder.setWindowCaption("Submission Confirmation");
		createWithEventFunc(builder, submitResponse, ptr, ppc::submitFiles);

		SuspiciousFileHolder::onChange.addObserver(new ReportScreenObsvr(*ptr));

		ptr->addWindow(submitResponse);
	}
	return true;
}
