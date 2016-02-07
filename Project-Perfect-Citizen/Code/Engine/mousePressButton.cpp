#include "mousePressButton.h"
#include <iostream>
using namespace std;

mousePressButton::mousePressButton(ppc::InputHandler& ih, 
	sf::Sprite& s): InputComponent(1), buttonSprt(s), inputHandle(ih){

	//add a new subject that is tied to the event
	ih.addHandle(sf::Event::MouseButtonReleased);
	//add an observer to the subject we just added
	if (watch(ih, sf::Event::MouseButtonReleased)) {
		cout << "Event watched" << endl;
	}

}

mousePressButton::~mousePressButton() {
	ignore(inputHandle, sf::Event::MouseButtonReleased);
}

bool mousePressButton::isCollision(sf::Vector2i mousePos) {
	cout << "MOUSE X: " << mousePos.x;
	cout << "   MOUSE Y: " << mousePos.y << endl;
	//NOTE: NEED TO ADD X,Y POS OF WINDOW(TARGET) SPRITE IS IN
	//HARD CODE FOR NOW, BUT EXPLAIN TO EVERYONE LATER
	sf::Vector2f sprtBoxPos = { buttonSprt.getGlobalBounds().left,
		buttonSprt.getGlobalBounds().top };
	cout << "BOX X: " << sprtBoxPos.x;
	cout << "   BOX Y: " << sprtBoxPos.y << endl;
	sf::Vector2f sprtBoxDim = { buttonSprt.getGlobalBounds().width,
		buttonSprt.getGlobalBounds().height };
	cout << "BOX Width: " << sprtBoxDim.x;
	cout << "   BOX Height: " << sprtBoxDim.y << endl;
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


bool mousePressButton::registerInput(sf::Event& ev) {
	
	if (ev.type == sf::Event::MouseButtonReleased) {

		if (ev.mouseButton.button == sf::Mouse::Left &&
			isCollision({ ev.mouseButton.x ,ev.mouseButton.y })) {

			std::cout << "the left button was pressed" << std::endl;

		}
	}

    return true;
}
