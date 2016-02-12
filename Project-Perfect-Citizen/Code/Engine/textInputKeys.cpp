#include "textInputKeys.hpp"
#include <iostream>
#include <string>

using namespace std;
const string TEXT_KEY_INPUT = "TKI";


const float DOUBLE_CLICK_TIME = 500;

textInputKeys::textInputKeys(ppc::InputHandler& ih,
                             sf::Sprite& s ,
                             textInputRenderComponent& r):
                             InputComponent(2), textBoxSprt(s),
                             textBox(r), inputHandle(ih){


    ih.addHandle(sf::Event::TextEntered);
    ih.addHandle(sf::Event::KeyPressed);
    
    if (watch(ih, sf::Event::TextEntered)) {
        cout << "Text Entered Watched" << endl;
    }
    
    if (watch(ih, sf::Event::KeyPressed)) {
        cout << "Key Pressed Watched" << endl;
    }
    
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
            if (ev.text.unicode < 128) {
                str.push_back((char)ev.text.unicode);
                std::cout << str << std::endl;
                textBox.updateString(str);
            }
        } else if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::BackSpace && (str.size()!=0)) {
                // First pop_back() deletes the 'backspace' character
                if (str.size() > 1) str.pop_back();
                // Second pop_back() deletes the last character
                str.pop_back();
                textBox.updateString(str);
                std::cout << str << std::endl;
            }
        }
    }
    return true;
}
