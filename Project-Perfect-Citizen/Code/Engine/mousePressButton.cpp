#include "mousePressButton.h"
#include <iostream>
#include <string>

using namespace std;
const string MOUSE_DOWN_CODE = "MDC";
const string MOUSE_RELEASED_CODE = "MRC";
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";

const float DOUBLE_CLICK_TIME = 500;

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
	sf::Vector2f sprtBoxPos = { buttonSprt.getGlobalBounds().left ,
		buttonSprt.getGlobalBounds().top };
	//cout << "BOX X: " << sprtBoxPos.x;
	//cout << "   BOX Y: " << sprtBoxPos.y << endl;
	sf::Vector2f sprtBoxDim = { buttonSprt.getGlobalBounds().width,
		buttonSprt.getGlobalBounds().height };
	//cout << "BOX Width: " << sprtBoxDim.x;
	//cout << "   BOX Height: " << sprtBoxDim.y << endl;

	bool result = false;
	if (mousePos.x >= sprtBoxPos.x  &&
			mousePos.x <= sprtBoxPos.x + sprtBoxDim.x) {
		if (mousePos.y >= sprtBoxPos.y &&
				mousePos.y <= sprtBoxPos.y + sprtBoxDim.y) {
			result = true;
		}
	}
	return result;
}


bool mousePressButton::registerInput(sf::Event& ev) {
    if (getEntity() != nullptr) {

        /* Case: Mouse Pressed Event*/
        if (ev.type == sf::Event::MouseButtonPressed) {
            if (ev.mouseButton.button == sf::Mouse::Left &&
                isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

                /* Send the mouse down message regardless */
                getEntity()->broadcastMessage(MOUSE_DOWN_CODE);
				cout << "Clicked on an entity with MPB" << endl;

                /* Handle Double Click Register */
                mouseTime = mouseClock.getElapsedTime().asMilliseconds();
                if (mouseTime > DOUBLE_CLICK_TIME) {
                    mouseClock.restart();
                } else if (mouseTime < DOUBLE_CLICK_TIME) {
                    /* Send the d/c message only if clicked with 500 ms*/
                    cout << "Double clicked on an entity with MPB!" << endl;
                    getEntity()->broadcastMessage(
                            MOUSE_DOUBLE_CLICK_CODE);
                }
            }
        }
        /* Case: Mouse Released Event*/
        else if (ev.type == sf::Event::MouseButtonReleased) {
            if (ev.mouseButton.button == sf::Mouse::Left &&
                isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

                /* Send the mouse release message regardless*/
                getEntity()->broadcastMessage(MOUSE_RELEASED_CODE);
            }
        }
    }

    return true;
}
