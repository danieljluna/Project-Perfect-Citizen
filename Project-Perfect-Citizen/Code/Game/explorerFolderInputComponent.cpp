#include "../Engine/debug.h"
#include "explorerFolderInputComponent.h"

#include <iostream>
#include <string>

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/World.h"
#include "../Engine/Window.h"
#include "../Engine/desktop.h"

#include "TreeCommands.h"
#include "ContextBuilder.h"
#include "TextBoxInputComponent.h"
#include "createWindow.h"


using namespace ppc;


const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const float DOUBLE_CLICK_TIME = 500.0f;


explorerFolderInputComponent::explorerFolderInputComponent(Desktop& dt, WindowInterface* cW, ppc::InputHandler& ih, NodeState* ns, sf::Image& bS, sf::Image& iS, sf::FloatRect rect, std::string dN) :
	InputComponent(2), theDesktop_(dt), containingWindow_(cW), theFileTree_(ns), buttonSheet_(bS), iconSheet_(iS),buttonRect(rect), directoryName(dN) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	//add an observer to the subject we just added
	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

	hasBeenClicked = false;

		
}

//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)


void ppc::explorerFolderInputComponent::setObservingTextBox(TextBoxInputComponent *tbi)
{
	observingTextBox_ = tbi;
}

TextBoxInputComponent * ppc::explorerFolderInputComponent::getObservingTextBox()
{
	return observingTextBox_;
}

NodeState * ppc::explorerFolderInputComponent::getFolderNodeState()
{
	return theFileTree_;
}

std::string ppc::explorerFolderInputComponent::getFolderName()
{
	return directoryName;
}

Desktop * ppc::explorerFolderInputComponent::getFolderDesktop()
{
	return &theDesktop_;
}

explorerFolderInputComponent::~explorerFolderInputComponent() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void explorerFolderInputComponent::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void explorerFolderInputComponent::setFloatRect(sf::FloatRect rect) {
	buttonRect = rect;
}


bool explorerFolderInputComponent::isCollision(sf::Vector2i mousePos) {
	//Gets the position as a Float Vector
	sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));

	//Returns if point is in foatRect
	return buttonRect.contains(mouseFloatPos);
}


bool explorerFolderInputComponent::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
	if (getEntity() != nullptr) {

		/* Case: Mouse Pressed Event*/
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

				/* Send the mouse down message regardless */
				ppc::Event clickEvent;
				clickEvent.type = Event::EventTypes::ButtonType;
				clickEvent.buttons.state = Event::ButtonsEv::Clicked;
				clickEvent.buttons.activation = Event::ButtonsEv::LeftMouse;
				getEntity()->broadcastMessage(clickEvent);
				onPress_.sendEvent(ev);

				/* Handle Double Click Register */
				mouseTime = mouseClock.getElapsedTime().asMilliseconds();
				if (mouseTime > DOUBLE_CLICK_TIME) {
					mouseClock.restart();
					hasBeenClicked = true;
				}
				else if (mouseTime < DOUBLE_CLICK_TIME && hasBeenClicked) {
					mouseClock.restart();
					changeDirectory(false);
				}
			} 
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.mouseButton.button == sf::Mouse::Right &&
			isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

			/* Begin Building Context List */
			ppc::WindowInterface* ContextMenu = nullptr;
			ContextMenu = new ppc::Window(200, 300, sf::Color(170, 170, 170));
			ContextBuilder builder;
			std::vector<ppc::Entity> listElements;
			float fontSize = 20.0f;
			float fontPadding = 2.0f;

			/* First Element: 'Open' */
			Entity listElement;
			builder.setContainingWindow(ContextMenu);
			builder.setInputHandle(ContextMenu->getInputHandler());
			builder.setLabelFont(World::getFont(World::Consola));
			builder.setLabelMessage("Open");
			builder.setLabelSize((int)fontSize);
			builder.setListElementPosition(0, 0);
			builder.setListElementSize({ ContextMenu->getBounds().width, fontSize + fontPadding });
			createWithEventFunc(builder, listElement, this, ppc::open_folder);
			listElements.push_back(listElement);

			/* Completed: Make the Context Menu at the mouse position*/
			spawnContextMenu(ContextMenu, listElements, ev.mouseButton.x + containingWindow_->getPosition().x,
				ev.mouseButton.y + containingWindow_->getPosition().y);
			theDesktop_.addWindow(ContextMenu);

			}
		else if (ev.mouseButton.button == sf::Mouse::Left) {
			ppc::Event clickEvent;
			clickEvent.type = Event::EventTypes::ButtonType;
			clickEvent.buttons.state = Event::ButtonsEv::Release;
			clickEvent.buttons.activation = Event::ButtonsEv::LeftMouse;
			getEntity()->broadcastMessage(clickEvent);
			}
		}
	}

	return true;
}

void ppc::explorerFolderInputComponent::changeDirectory(bool newWindow)
{
	if (theFileTree_->getCwd()->findElement(directoryName)->isPasswordProtected() &&
		directoryName.compare("..") != 0) {
		
		ppc::WindowInterface* UnlockWindow =
		new ppc::Window(500, 150, sf::Color(170, 170, 170));
        UnlockWindow->setPosition(-100, -100);
		spawnUnlock(UnlockWindow, UnlockWindow->getInputHandler(), buttonSheet_, 250, 250, this);
        //theDesktop_.addWindow(UnlockWindow);
		containingWindow_->createNotifWindow(UnlockWindow);
		return;
	}

	std::vector<std::string> cdCommand;
	std::string cd = "cd";
	cdCommand.push_back(cd);
	cdCommand.push_back(directoryName);
	commandFn newCD = findFunction(cd);
	newCD(*theFileTree_, cdCommand);
	ppc::WindowInterface* explorerWindow =
		new ppc::Window(600, 350, sf::Color(255, 255, 255));
	spawnExplorer(theDesktop_, explorerWindow, explorerWindow->getInputHandler(), theFileTree_, buttonSheet_, iconSheet_, 100, 200);

	if (newWindow) {
		explorerWindow->setPosition(containingWindow_->getPosition().x + 10, containingWindow_->getPosition().y + 10);
	}
	else {
		explorerWindow->setPosition(containingWindow_->getPosition().x, containingWindow_->getPosition().y);
		containingWindow_->close();
	}
	theDesktop_.addWindow(explorerWindow);


}

bool ppc::open_folder(explorerFolderInputComponent* ptr, ppc::Event ev) {
	ptr->changeDirectory(false);
	return true;
}

bool ppc::flag_folder(explorerFolderInputComponent* ptr, ppc::Event ev) {
	std::cout << " flag this folder using the new method " << std::endl;
	return true;
}

bool ppc::unlock_folder(explorerFolderInputComponent* ptr, ppc::Event ev) {

	if (ptr == nullptr) return false;

    Event evOut;
    evOut.type = evOut.OpenType;
    BaseFileType* target = ptr->getFolderNodeState()->getCwd();

    if (target->getFileType() == Directory) {
        evOut.open.winType = evOut.open.Folder;
    } else {
        evOut.open.winType = evOut.open.File;
    }
    evOut.open.file = target->findElement(ptr->getFolderName());

	if (target->findElement(ptr->getFolderName())->
		comparePassword(ptr->getObservingTextBox()->getString())) {	

		/* Unlock the directory */
		std::vector<std::string> unlockCommand;
		std::string unlock = "unlock";
		unlockCommand.push_back(unlock);
		unlockCommand.push_back(ptr->getFolderName());
		unlockCommand.push_back(ptr->getObservingTextBox()->getString());
		commandFn newCommand = findFunction(unlock);
		newCommand(*ptr->getFolderNodeState(), unlockCommand);

		/* Let the user know they successfully unlocked the directory */
		ppc::WindowInterface* success =
			new ppc::Window(500, 150, sf::Color(170, 170, 170));
		spawnSuccessMessage(success, success->getInputHandler(), ptr->getFolderDesktop()->getButtonSheet(),
			250, 250, "Access Granted. \n'" + ptr->getFolderName() + "' is now unlocked.");
		//ptr->getObservingTextBox()->getContainingWindow()->getNotifWindow()->close();
		//ptr->getObservingTextBox()->getContainingWindow()->createNotifWindow(success, true);
		//ptr->getContainingWindow()->createNotifWindow(success, true);
		ptr->getFolderDesktop()->addWindow(success);

		/* Send the event and close the submit wind*/
		evOut.open.success = false;
		ptr->getObservingTextBox()->getContainingWindow()->close();
		
        evOut.open.success = true;
	}
	else {
		ppc::WindowInterface* ErrorMsgWindow =
		new ppc::Window(500, 150, sf::Color(170, 170, 170));
		spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), ptr->getFolderDesktop()->getButtonSheet(),
		250, 250,
			"Error: Password incorrect. \nHint: " + ptr->getFolderNodeState()->getCwd()->findElement(ptr->getFolderName())->getHint(), "Incorrect Password");
		ptr->getFolderDesktop()->addWindow(ErrorMsgWindow);
        evOut.open.success = false;
	}
	
    ptr->getFolderNodeState()->onOpen().sendEvent(evOut);

	return true;
}

