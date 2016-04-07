#include "../Engine/debug.h"
#include "explorerFileInputComponent.h"
#include <iostream>
#include <string>

#include "../Engine/FreeFunctionObserver.h"
#include "../Engine/BaseFileType.h"

using namespace ppc;


const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const float DOUBLE_CLICK_TIME = 500.0f;


explorerFileInputComponent::explorerFileInputComponent(Desktop& dt, ppc::InputHandler& ih, NodeState& ns, sf::Image& bS, sf::FloatRect rect, std::string fN) :
	InputComponent(2), theDesktop_(dt), theFileTree_(ns), buttonSheet_(bS), buttonRect(rect), fileName(fN) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	//add an observer to the subject we just added
	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void explorerFileInputComponent::clearObservers()
{
	for (size_t i = 0; i < observerCount_; ++i) {
		delete observerArray_[i];
	}
}


//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)


explorerFileInputComponent::~explorerFileInputComponent() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void explorerFileInputComponent::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void explorerFileInputComponent::setFloatRect(sf::FloatRect rect) {
	buttonRect = rect;
}


bool explorerFileInputComponent::isCollision(sf::Vector2i mousePos) {
	//Gets the position as a Float Vector
	sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));

	//Returns if point is in foatRect
	return buttonRect.contains(mouseFloatPos);
}


bool explorerFileInputComponent::registerInput(sf::Event ev) {
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
				}
				else if (mouseTime < DOUBLE_CLICK_TIME) {
					std::string fileResourcePath = theFileTree_.getCwd()->findElement(fileName)->getFileData();
					theFileTree_.getCwd()->findElement(fileName)->readFile(theDesktop_, buttonSheet_, fileResourcePath);
				}
			}
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {

		}
	}

	return true;
}