#include "mousePressButton.h"
#include <iostream>

using namespace std;
const int MOUSE_DOWN_CODE = 200;
const int MOUSE_RELEASED_CODE = 400;

mousePressButton::mousePressButton(ppc::InputHandler& ih, 
	sf::Sprite& s): InputComponent(2), buttonSprt(s), inputHandle(ih){

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	//add an observer to the subject we just added
	if (watch(ih, sf::Event::MouseButtonPressed)) {
		cout << "Mouse Pressed Watched" << endl;
	}
	if (watch(ih, sf::Event::MouseButtonReleased)) {
		cout << "Mouse Released Event Watched" << endl;
	}

}

mousePressButton::~mousePressButton() {
	ignore(inputHandle, sf::Event::MouseButtonPressed);
	ignore(inputHandle, sf::Event::MouseButtonReleased);
}

bool mousePressButton::isCollision(sf::Vector2i mousePos) {
	//cout << "MOUSE X: " << mousePos.x;
	//cout << "   MOUSE Y: " << mousePos.y << endl;
	//NOTE: NEED TO ADD X,Y POS OF WINDOW(TARGET) SPRITE IS IN
	//HARD CODE FOR NOW, BUT EXPLAIN TO EVERYONE LATER
	sf::Vector2f sprtBoxPos = { buttonSprt.getGlobalBounds().left,
		buttonSprt.getGlobalBounds().top };
	//cout << "BOX X: " << sprtBoxPos.x;
	//cout << "   BOX Y: " << sprtBoxPos.y << endl;
	sf::Vector2f sprtBoxDim = { buttonSprt.getGlobalBounds().width,
		buttonSprt.getGlobalBounds().height };
	//cout << "BOX Width: " << sprtBoxDim.x;
	//cout << "   BOX Height: " << sprtBoxDim.y << endl;
	bool result = false;
	if (mousePos.x >= sprtBoxPos.x + 100 &&
			mousePos.x <= sprtBoxPos.x + 100 + sprtBoxDim.x) {
		if (mousePos.y >= sprtBoxPos.y + 100 &&
				mousePos.y <= sprtBoxPos.y + 100 + sprtBoxDim.y) {
			result = true;
		}
	}
	return result;
}

void mousePressButton::registerInput(sf::Event& ev) {
	
	ppc::Entity *parentEntity = getEntity();

	/* Case: Mouse Pressed Event*/
	if (ev.type == sf::Event::MouseButtonPressed) {
		if (ev.mouseButton.button == sf::Mouse::Left &&
			isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
			parentEntity->broadcastMessage(MOUSE_DOWN_CODE);
		}
	}
	/* Case: Mouse Released Event*/
	if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.mouseButton.button == sf::Mouse::Left &&
			isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {
			parentEntity->broadcastMessage(MOUSE_RELEASED_CODE);
		}
	}

}
