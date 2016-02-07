#pragma once

#include <SFML/Graphics.hpp>

#include "inputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "subject.h"


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
	sf::Clock mouseClock;
	float mouseTime;
	bool isCollision(sf::Vector2i);

public:

	mousePressButton() = delete;


	mousePressButton(ppc::InputHandler& ih, sf::Sprite& s);
	virtual ~mousePressButton();
	virtual void registerInput(sf::Event& ev) override;

};