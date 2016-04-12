#pragma once

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Designated Render Component for a text display
/// @author Alex Vincent
/// @details This is a generic text render component for any item that
/// can be used anywhere. This is meant to be used in conjunction with
/// a TextDisplayBuilder to make non-editable text boxes.
///////////////////////////////////////////////////////////////////////
class TextDisplayRenderComponent : public RenderComponent {
private:
	sf::Text* text_;
	sf::Text* outline_;
	sf::Font font_;
	std::string labelString_;

    static sf::Font defaultFont;
    static bool isLoaded;


public:
    ///////////////////////////////////////////////////////////////////////
    /// @brief Constructor for buttonRenderComponent
    /// @details Uses the default Font (consolas.ttf) and initializes to
    ///     an empty black string at (0,0).
    ///////////////////////////////////////////////////////////////////////
    TextDisplayRenderComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief Constructor for buttonRenderComponent
	/// @param f is the font to be used.
	/// @param c is the color to be used.
	/// @param x is the x position of the font relative to the entity
	/// @param y is the y position of the font relative to the entity
	/// @param s is the font size.
	/// @param f is the string to render.
	///////////////////////////////////////////////////////////////////////
	TextDisplayRenderComponent(sf::Font& f, sf::Color c, float x, float y, unsigned int s, std::string str);

	~TextDisplayRenderComponent();

	sf::Vector2f getTextPosition() const { return text_->getPosition(); }

	std::string getString() const { return text_->getString(); }

	void updateString(std::string str);

	void updatePosition(float x, float y);

	void updateSize(unsigned int s);

    void updateFont(sf::Font f);

    void updateColor(sf::Color c);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};



};