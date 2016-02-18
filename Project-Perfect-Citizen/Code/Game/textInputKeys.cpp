#include "textInputKeys.hpp"
#include <iostream>
#include <string>

using namespace std;
const string TEXT_KEY_INPUT = "TKI";

const float DOUBLE_CLICK_TIME = 500;

textInputKeys::textInputKeys(ppc::InputHandler& ih, sf::Sprite& s, 
	textInputRenderComponent& r, textOutputRenderComponent& r2,
	consoleUpdateComponent& c) : InputComponent(2), textBoxSprt(s), 
	textBox(r), textDisplay(r2), inputHandle(ih), cup(c){


    ih.addHandle(sf::Event::TextEntered);
    ih.addHandle(sf::Event::KeyPressed);
    
    if (watch(ih, sf::Event::TextEntered)) {
        cout << "Text Entered Watched" << endl;
    }
    
    if (watch(ih, sf::Event::KeyPressed)) {
        cout << "Key Pressed Watched" << endl;
    }

	str.push_back((char)'>');
	str.push_back((char)' ');
	textBox.updateString(str);
    
}

textInputKeys::~textInputKeys() {
    ignore(inputHandle, sf::Event::TextEntered);
    ignore(inputHandle, sf::Event::KeyPressed);
}

bool textInputKeys::isCollision(sf::Vector2i mousePos) {
    sf::Vector2f sprtBoxPos = { textBoxSprt.getGlobalBounds().left ,
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
    }
    
    // textBoxSprt.setSelected(true);
    
    return result;
}

bool textInputKeys::registerInput(sf::Event& ev) {
    if (getEntity() != nullptr) {
        if (ev.type == sf::Event::TextEntered){
			/* Ignore CNTRL, BS, ENTR/LF, CR */
            if (ev.text.unicode < 128 && ev.text.unicode != 8 && 
				ev.text.unicode != 10 && ev.text.unicode != 13) {
                str.push_back((char)ev.text.unicode);
                textBox.updateString(str);
            }
        } else if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::BackSpace && 
				(str.size()>2)) {
                str.pop_back();
                textBox.updateString(str);
			}
			else if (ev.key.code == sf::Keyboard::Return && 
				(str.size() != 0)) {
				/* Copy/send the command*/
				std::string cmd;
				for (int i = 2; i<str.size(); ++i) { 
					cmd.push_back(str.at(i)); 
				}
				cmd += " ";

				std::vector<string> commandVec;
				string delimiter = " ";
				size_t last = 0;
				size_t next = 0;
				string token;
				while ((next = cmd.find(delimiter, last)) != 
											string::npos) {
					token = cmd.substr(last, next - last);
					commandVec.push_back(token);
					last = next + 1;
				}

				cup.executeCommand(commandVec);

				/* Reset the command line - keeping the prompt */
				str.erase(2, str.length());
				textBox.updateString(str);

				/* Display the result */;
				textDisplay.updateString(commandVec);
			}
        }
    }
    return true;
}
