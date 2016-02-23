#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"


///////////////////////////////////////////////////////////////////////
/// @brief Designated Input Component for a generic window 'X' button
/// @author Alex Vincent & Nader Sleem
/// @details The mousePressedButton is a basic packaged subclass
///     extension of InputComponent, make specifically to handle
///     all generic "X" button related sfml event parts. 
///		Stick this onto an entity to give it this functionality.
///////////////////////////////////////////////////////////////////////


class mousePressButton: public ppc::InputComponent {
private:

	sf::Sprite& buttonSprt;
	ppc::InputHandler& inputHandle;
	std::string isBeingPressed;
	sf::Clock mouseClock;
    sf::Int32 mouseTime;
	bool isCollision(sf::Vector2i);

public:

	mousePressButton() = delete;
	mousePressButton(ppc::InputHandler& ih, sf::Sprite& s, std::string isBeingPressed);
	virtual ~mousePressButton();
	virtual bool registerInput(sf::Event& ev) override;

};