#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a text display
/// @author Alex Vincent
/// @details This is a generic text render component for any item that
/// can be used anywhere. This is meant to be used in conjunction with
/// a TextDisplayBuilder to make non-editable text boxes.
///////////////////////////////////////////////////////////////////////
class TextDisplayRenderComponent : public ppc::RenderComponent {
private:
	sf::Text* text;
	sf::Font font;
	string labelString;


public:
	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for buttonRenderComponent
	/// @param f is the font to be used.
	/// @param x is the x position of the font relative to the entity
	/// @param y is the y position of the font relative to the entity
	///////////////////////////////////////////////////////////////////////
	TextDisplayRenderComponent(sf::Font& f, sf::Color c, float x, float y, int s, string str);

	~TextDisplayRenderComponent();

	sf::Vector2f getTextPosition() const { return text->getPosition(); }

	string getString() const { return text->getString(); }

	void updateString(string str);

	void updatePosition(float x, float y);

	void updateSize(int s);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};