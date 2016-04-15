#include "../Engine/debug.h"
#include "explorerFolderInputComponent.h"
#include <iostream>
#include <string>

#include "../Engine/FreeFunctionObserver.h"
#include "TreeCommands.h"

using namespace ppc;


const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const float DOUBLE_CLICK_TIME = 500.0f;


explorerFolderInputComponent::explorerFolderInputComponent(Desktop& dt, WindowInterface* cW, ppc::InputHandler& ih, NodeState& ns, sf::Image& bS, sf::Image& iS, sf::FloatRect rect, std::string dN) :
	InputComponent(2), theDesktop_(dt), containingWindow_(cW), theFileTree_(ns), buttonSheet_(bS), iconSheet_(iS),buttonRect(rect), directoryName(dN) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	//add an observer to the subject we just added
	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

	hasBeenClicked = false;

		
}

void explorerFolderInputComponent::clearObservers()
{
	for (size_t i = 0; i < observerCount_; ++i) {
		delete observerArray_[i];
	}
}


//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)


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


bool explorerFolderInputComponent::registerInput(sf::Event ev) {
	if (getEntity() != nullptr) {

		/* Case: Mouse Pressed Event*/
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

				/* Send the mouse down message regardless */
				getEntity()->broadcastMessage(MOUSE_DOWN_CODE);
				onPress_.sendEvent(ev);

				/* Handle Double Click Register */
				mouseTime = mouseClock.getElapsedTime().asMilliseconds();
				if (mouseTime > DOUBLE_CLICK_TIME) {
					mouseClock.restart();
					hasBeenClicked = true;
				}
				else if (mouseTime < DOUBLE_CLICK_TIME && hasBeenClicked) {
					mouseClock.restart();

					if (theFileTree_.getCwd()->findElement(directoryName)->isPasswordProtected() &&
						directoryName.compare("..") != 0) {
						ppc::WindowInterface* ErrorMsgWindow =
							new ppc::Window(500, 150, sf::Color(170, 170, 170));
						spawnErrorMessage(ErrorMsgWindow, ErrorMsgWindow->getInputHandler(), buttonSheet_, 
							250,
							250,
							"Error: " + directoryName + " is protected." );
						theDesktop_.addWindow(ErrorMsgWindow);
						return true;
					}

					std::vector<string> cdCommand;
					string cd = "cd";
					cdCommand.push_back(cd);
					cdCommand.push_back(directoryName);
					commandFn newCD = findFunction(cd);
					newCD(theFileTree_, cdCommand);
					ppc::WindowInterface* explorerWindow =
						new ppc::Window(600, 350, sf::Color(255, 255, 255));
					spawnExplorer(theDesktop_, explorerWindow, explorerWindow->getInputHandler(), theFileTree_, buttonSheet_, iconSheet_, 100, 200);

					explorerWindow->setPosition(containingWindow_->getPosition().x, containingWindow_->getPosition().y);
					theDesktop_.addWindow(explorerWindow);
                    containingWindow_->close();

				}
			} 
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {
			
		}
	}

	return true;
}