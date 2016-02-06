#pragma once

#include <SFML/Graphics.hpp>

#include "inputComponent.h"
#include "InputHandler.h"

//An example of the mouse pressing a button.
class mousePressButton: public ppc::InputComponent {
private:

	sf::Sprite& buttonSprt;
	ppc::InputHandler& inputHandle;

	bool isCollision(sf::Vector2i);

public:

	mousePressButton() = delete;
	mousePressButton(ppc::InputHandler& ih, sf::Sprite& s);
	virtual ~mousePressButton();
	virtual void registerInput(sf::Event& ev) override;

};