#include "TextBoxInputComponent.h"
#include "TextBoxRenderComponent.h"
#include "../Engine/InputHandler.h"


using namespace ppc;
const string TEXT_KEY_INPUT = "TKI";
const float DOUBLE_CLICK_TIME = 500;

TextBoxInputComponent::TextBoxInputComponent(InputHandler& ih, TextBoxRenderComponent &r): inputHandle(ih), textBox(r) {

	ih.addHandle(sf::Event::TextEntered);
	ih.addHandle(sf::Event::KeyPressed);

	watch(ih, sf::Event::TextEntered);
	watch(ih, sf::Event::KeyPressed);

	str.push_back((char)'> ');
	textBox.updateString(str);

}

TextBoxInputComponent::~TextBoxInputComponent() {
	ignore(inputHandle, sf::Event::TextEntered);
	ignore(inputHandle, sf::Event::KeyPressed);
}

bool TextBoxInputComponent::isCollision(sf::Vector2i mousePos) {

	// Temporarily removing collisions on Text Inputs.
	// May not be necessary to have them

	/* sf::Vector2f sprtBoxPos = { textBoxSprt.getGlobalBounds().left ,
	textBoxSprt.getGlobalBounds().top };

	sf::Vector2f sprtBoxDim = { textBoxSprt.getGlobalBounds().width,
	textBoxSprt.getGlobalBounds().height };

	bool result = false;
	if (mousePos.x >= sprtBoxPos.x  &&
	mousePos.x <= sprtBoxPos.x + sprtBoxDim.x) {
	if (mousePos.y >= sprtBoxPos.y &&
	mousePos.y <= sprtBoxPos.y + sprtBoxDim.y) {
	result = true;
	}
	}*/

	// textBoxSprt.setSelected(true);

	return true;
}

string TextBoxInputComponent::getString() {
	return str;
}

bool TextBoxInputComponent::registerInput(sf::Event& ev) {
	if (getEntity() != nullptr) {
		if (ev.type == sf::Event::TextEntered) {
			/* Ignore CNTRL, BS, ENTR/LF, CR */
			if (ev.text.unicode < 128 && ev.text.unicode != 8 &&
				ev.text.unicode != 10 && ev.text.unicode != 13) {
				str.push_back((char)ev.text.unicode);
				textBox.updateString(str);
			}
		}
		else if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::BackSpace &&
				(str.size()>2)) {
				str.pop_back();
				textBox.updateString(str);
			}
			else if (ev.key.code == sf::Keyboard::Return &&
				(str.size() != 0)) {
				
				// DO A FUNCTION HERE

				/* Reset the command line - keeping the prompt */
				str.erase(2, str.length());
				textBox.updateString(str);
			}
		}
	}
	return true;
}