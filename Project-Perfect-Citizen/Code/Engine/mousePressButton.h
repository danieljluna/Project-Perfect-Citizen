#pragma once

#include <SFML/Graphics.hpp>

#include "inputComponent.h"
#include "InputHandler.h"


class mousePressButton: public ppc::InputComponent {
private:

	sf::Sprite& buttonSprt;
	ppc::InputHandler& inputHandle;

	bool isCollision(sf::Vector2i);

public:

	mousePressButton() = delete;
	mousePressButton(ppc::InputHandler& ih, sf::Sprite& s);
	~mousePressButton();
	virtual bool registerInput(sf::Event& ev) override;

};