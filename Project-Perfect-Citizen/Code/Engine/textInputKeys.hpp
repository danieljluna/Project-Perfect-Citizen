#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "inputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "subject.h"
#include "textInputRenderComponent.hpp"
#include "consoleUpdateComponent.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a generic window 'X' button
/// @author Michael Lowe
/// @details Input Component to handle TextEnter events from
///          the keyboard. This will mainly be used in combination
///          with a text input box render component.
///////////////////////////////////////////////////////////////////////
class consoleUpdateComponent;

class textInputKeys: public ppc::InputComponent {
private:
    
    sf::Sprite& textBoxSprt;
    textInputRenderComponent& textBox;
    ppc::InputHandler& inputHandle;
	consoleUpdateComponent& cup;
    sf::Clock mouseClock;
    std::string str;
    float mouseTime;
    bool isCollision(sf::Vector2i);
    
public:
    
    textInputKeys() = delete;
    
    ///////////////////////////////////////////////////////////////////////
    /// @brief Constructor for textInputKeys
    /// @param ih is the input handler
    /// @param s is the render component where the text will be drawn
    ///////////////////////////////////////////////////////////////////////
    textInputKeys(ppc::InputHandler& ih, sf::Sprite& s, textInputRenderComponent &r, consoleUpdateComponent& c);
    virtual ~textInputKeys();
    virtual bool registerInput(sf::Event& ev) override;
    
};