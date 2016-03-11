#include "../Engine/debug.h"
#include "emailListElementInputComponent.h"
#include <iostream>
#include <string>

using namespace std;
const string MOUSE_DOWN_CODE = "MDC";
const string MOUSE_RELEASED_CODE = "MRC";
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const float DOUBLE_CLICK_TIME = 500.0f;


emailListElementInputComponent::emailListElementInputComponent(ppc::Desktop& dT, ppc::InputHandler& ih,
	ppc::Email eM, sf::Image& bS, sf::FloatRect rect) : InputComponent(2), boxRect(rect), buttonSheet(bS), emailToOpen(eM), theDesktop(dT) {

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed); 
	watch(ih, sf::Event::MouseButtonReleased);

}

emailListElementInputComponent::~emailListElementInputComponent() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void emailListElementInputComponent::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void emailListElementInputComponent::setFloatRect(sf::FloatRect rect) {
	boxRect = rect;
}

bool emailListElementInputComponent::isCollision(sf::Vector2i mousePos) {
	//Gets the position as a Float Vector
	sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));
	return boxRect.contains(mouseFloatPos);
}


bool emailListElementInputComponent::registerInput(sf::Event& ev) {
	if (getEntity() != nullptr) {

		/* Case: Mouse Pressed Event*/
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

				/* Send the mouse down message regardless */
				getEntity()->broadcastMessage(MOUSE_DOWN_CODE);

				/* Handle Double Click Register */
				mouseTime = mouseClock.getElapsedTime().asMilliseconds();
				if (mouseTime > DOUBLE_CLICK_TIME) {
					mouseClock.restart();
				}
				else if (mouseTime < DOUBLE_CLICK_TIME) {
					ppc::WindowInterface* emailWindow =
						new ppc::Window(600, 500, sf::Color(200, 200, 200));
					spawnEmailMessage(emailWindow, emailWindow->getInputHandler(), emailToOpen, buttonSheet, 200, 50);
					theDesktop.addWindow(emailWindow);
					getEntity()->broadcastMessage(MOUSE_DOUBLE_CLICK_CODE);
				}
			}
		}
		/* Case: Mouse Released Event*/
		else if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left &&
				isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
			}
		}
		/* Case: Mouse Moved Event*/
		else if (ev.type == sf::Event::MouseMoved) {
			if (!boxRect.contains(float(ev.mouseMove.x), float(ev.mouseMove.y)) &&
				ev.mouseButton.button == sf::Mouse::Left) {
				cout << "left the button" << endl;
			}
		}
	}

	return true;
}