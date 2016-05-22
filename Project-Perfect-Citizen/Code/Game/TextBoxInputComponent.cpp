#include "TextBoxInputComponent.h"

#include "TextBoxRenderComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/FreeFunctionObserver.h"


using namespace ppc;

const std::string TEXT_KEY_INPUT = "TKI";
const float DOUBLE_CLICK_TIME = 500;

TextBoxInputComponent::TextBoxInputComponent(InputHandler& ih, TextBoxRenderComponent &r, unsigned int l ) : inputHandle(ih), 
textBox(r), max_chars(l) {

	ih.addHandle(sf::Event::TextEntered);
	ih.addHandle(sf::Event::KeyPressed);

	watch(ih, sf::Event::TextEntered);
	watch(ih, sf::Event::KeyPressed);

	textBox.updateLabelString(str);

}

void ppc::TextBoxInputComponent::setContainingWindow(WindowInterface* win)
{
	containingWindow = win;
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


std::string TextBoxInputComponent::getString() {
	//str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

void ppc::TextBoxInputComponent::setLimit(int l)
{
	max_chars = l;
}

WindowInterface * ppc::TextBoxInputComponent::getContainingWindow()
{
	return containingWindow;
}

bool TextBoxInputComponent::registerInput(Event ppcEv) {
    sf::Event ev(ppcEv);
	if (getEntity() != nullptr) {
		if (ev.type == sf::Event::TextEntered) {
			/* Ignore CNTRL, BS, ENTR/LF, CR */
			if (ev.text.unicode < 128 && ev.text.unicode != 8 &&
				ev.text.unicode != 10 && ev.text.unicode != 13 &&
				str.length() < max_chars) {
				str.push_back((char)ev.text.unicode);
				textBox.updateLabelString(str);
			}
			else if (ev.text.unicode == 8 && str.size() > 0) {
				str.pop_back();
				textBox.updateLabelString(str);
			}
			else if ((ev.text.unicode == 10 || ev.text.unicode == 13) && str.size() > 0) {
				onSubmit_.sendEvent(ppcEv);
			}
		}
	}
	return true;
}