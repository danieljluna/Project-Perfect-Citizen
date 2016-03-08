#include "../Engine/debug.h"
#include "mousePressButton.h"
#include <iostream>
#include <string>
#include "../Engine/FreeFunctionObserver.h"

using namespace ppc;
const std::string MOUSE_DOWN_CODE = "MDC";
const std::string MOUSE_RELEASED_CODE = "MRC";
const std::string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const std::string OPEN_THE_CONSOLE = "OTC";
const std::string OPEN_THE_FILE = "OTF";
const std::string OPEN_THE_SETTINGS = "OTS";
const std::string OPEN_THE_CHAT = "OTCH";
const std::string OPEN_THE_SEARCH = "OTSER";
const std::string OPEN_THE_PIPELINE = "OTP";
const std::string OPEN_THE_HELP = "OTH";
const std::string OPEN_THE_BROWSER = "OTB";
const std::string OPEN_THE_EXPLORER = "OTE";

const float DOUBLE_CLICK_TIME = 500.0f;

mousePressButton::mousePressButton() : 
	InputComponent(2), buttonRect() {

}


mousePressButton::mousePressButton(ppc::InputHandler& ih, 
	sf::FloatRect rect, std::string iBP) : 
	InputComponent(2), buttonRect(rect), isBeingPressed(iBP){

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);
	 
	//add an observer to the subject we just added
	if (watch(ih, sf::Event::MouseButtonPressed)) {
		//cout << "Mouse Pressed Watched" << endl;
	}
	if (watch(ih, sf::Event::MouseButtonReleased)) {
		//cout << "Mouse Released Event Watched" << endl;
	}
}

void mousePressButton::clearObservers()
{
	for (size_t i = 0; i < observerCount_; ++i) {
		delete observerArray_[i];
	}
}


//void mousePressButton::addFunctionObserver(bool(*fnToAdd)(sf::Event &ev), mousePressButton* mpb, unsigned int placeToInsert)


mousePressButton::~mousePressButton() {

	//ignore(inputHandle, sf::Event::MouseButtonPressed);
	//ignore(inputHandle, sf::Event::MouseButtonReleased);
}

void mousePressButton::setInputHandle(ppc::InputHandler& ih) {

	ih.addHandle(sf::Event::MouseButtonPressed);
	ih.addHandle(sf::Event::MouseButtonReleased);

	watch(ih, sf::Event::MouseButtonPressed);
	watch(ih, sf::Event::MouseButtonReleased);

}

void mousePressButton::setFloatRect(sf::FloatRect rect) {
	buttonRect = rect;
}

void mousePressButton::setIsBeingPressed(std::string iBP) {
	isBeingPressed = iBP;
}


bool mousePressButton::isCollision(sf::Vector2i mousePos) {
    //Gets the position as a Float Vector
    sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));
	//cout << "MOUSE X, Y: " << mousePos.x << ",  " << mousePos.y << endl;
	//cout << "ButtonRect LEFT, TOP: " << buttonRect.left << ",  "<< buttonRect.top << endl;

    //Returns if point is in foatRect
    return buttonRect.contains(mouseFloatPos);
}


bool mousePressButton::registerInput(sf::Event& ev) {
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
                } else if (mouseTime < DOUBLE_CLICK_TIME) {
					if (isBeingPressed == "folderIcon") {
						getEntity()->broadcastMessage(OPEN_THE_FILE);
					}
					else if (isBeingPressed == "settingsIcon") {
						getEntity()->broadcastMessage(OPEN_THE_SETTINGS);
					}
					else if (isBeingPressed == "chatIcon") {
						getEntity()->broadcastMessage(OPEN_THE_CHAT);
					}
					else if (isBeingPressed == "searchIcon") {
						getEntity()->broadcastMessage(OPEN_THE_SEARCH);
					}
					else if (isBeingPressed == "dataGraphIcon") {
						getEntity()->broadcastMessage(OPEN_THE_PIPELINE);
					}
					else if (isBeingPressed == "helpIcon") {
						getEntity()->broadcastMessage(OPEN_THE_HELP);
					}
					else if (isBeingPressed == "browserIcon") {
						getEntity()->broadcastMessage(OPEN_THE_BROWSER);
					}
					else if (isBeingPressed == "hardDriveIcon") {
						getEntity()->broadcastMessage(OPEN_THE_EXPLORER);
					}
					else if (isBeingPressed == "consoleIcon") {
						getEntity()->broadcastMessage(OPEN_THE_CONSOLE);
					}
                    //cout << "Double clicked on an entity with MPB!" << endl;
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
				if (isBeingPressed == "localCloseButton") {
				}
            }
        }
    }

    return true;
}


