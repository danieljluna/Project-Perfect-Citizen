#include "mousePressButton.h"
#include <iostream>
#include <string>

using namespace std;
const string MOUSE_DOWN_CODE = "MDC";
const string MOUSE_RELEASED_CODE = "MRC";
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";
const string OPEN_THE_CONSOLE = "OTC";
const string OPEN_THE_FILE = "OTF";
const string OPEN_THE_SETTINGS = "OTS";
const string OPEN_THE_CHAT = "OTCH";
const string OPEN_THE_SEARCH = "OTSER";
const string OPEN_THE_PIPELINE = "OTP";
const string OPEN_THE_HELP = "OTH";
const string OPEN_THE_BROWSER = "OTB";
const string OPEN_THE_EXPLORER = "OTE";

const float DOUBLE_CLICK_TIME = 500.0f;

mousePressButton::mousePressButton(ppc::InputHandler& ih, 
	sf::Sprite& s, std::string iBP): 
	InputComponent(2), buttonSprt(s), inputHandle(ih), isBeingPressed(iBP){

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

mousePressButton::~mousePressButton() {
	ignore(inputHandle, sf::Event::MouseButtonPressed);
	ignore(inputHandle, sf::Event::MouseButtonReleased);
}

bool mousePressButton::isCollision(sf::Vector2i mousePos) {
    //Gets the position as a Float Vector
    sf::Vector2f mouseFloatPos(float(mousePos.x), float(mousePos.y));
    //Gets the FloatRect of the Sprite
    sf::FloatRect checkArea = buttonSprt.getGlobalBounds();

    //Returns if point is in foatRect
    return checkArea.contains(mouseFloatPos);
}


bool mousePressButton::registerInput(sf::Event& ev) {
    if (getEntity() != nullptr) {

        /* Case: Mouse Pressed Event*/
        if (ev.type == sf::Event::MouseButtonPressed) {
            if (ev.mouseButton.button == sf::Mouse::Left &&
                isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

                /* Send the mouse down message regardless */
                getEntity()->broadcastMessage(MOUSE_DOWN_CODE);
				cout << "mouse downed on a mpb item" << endl;

                /* Handle Double Click Register */
                mouseTime = mouseClock.getElapsedTime().asMilliseconds();
                if (mouseTime > DOUBLE_CLICK_TIME) {
                    mouseClock.restart();
                } else if (mouseTime < DOUBLE_CLICK_TIME) {
					if (isBeingPressed == "folderIcon") {
						getEntity()->broadcastMessage(OPEN_THE_FILE);
						cout << "double clicked a file folder" << endl;
					}
					else if (isBeingPressed == "settingsIcon") {
						getEntity()->broadcastMessage(OPEN_THE_SETTINGS);
						cout << "double clicked settings" << endl;
					}
					else if (isBeingPressed == "chatIcon") {
						getEntity()->broadcastMessage(OPEN_THE_CHAT);
						cout << "double clicked chat" << endl;
					}
					else if (isBeingPressed == "searchIcon") {
						getEntity()->broadcastMessage(OPEN_THE_SEARCH);
						cout << "double clicked search" << endl;	
					}
					else if (isBeingPressed == "dataGraphIcon") {
						getEntity()->broadcastMessage(OPEN_THE_PIPELINE);
						cout << "double clicked datagraph" << endl;
					}
					else if (isBeingPressed == "helpIcon") {
						getEntity()->broadcastMessage(OPEN_THE_HELP);
						cout << "double clicked help" << endl;
					}
					else if (isBeingPressed == "browserIcon") {
						getEntity()->broadcastMessage(OPEN_THE_BROWSER);
						cout << "double clicked browser" << endl;
					}
					else if (isBeingPressed == "hardDriveIcon") {
						getEntity()->broadcastMessage(OPEN_THE_EXPLORER);
						cout << "double clicked hard drive" << endl;
					}
					else if (isBeingPressed == "consoleIcon") {
						getEntity()->broadcastMessage(OPEN_THE_CONSOLE);
						cout << "double clicked console" << endl;
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
            }
        }
    }

    return true;
}
