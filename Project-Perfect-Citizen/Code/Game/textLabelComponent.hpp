//
//  textLabelComponent.hpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/3/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifndef textLabelComponent_hpp
#define textLabelComponent_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Label Render Component for a text label
	/// @author Michael Lowe
	/// @details The buttonRenderComponent is a basic packaged subclass
	///     extension of RenderComponent, make specifically to handle
	///     all generic "X" button related drawing/animating parts that
	///     also broadcast and recieve messages from an input handler.
	///		Stick this onto an entity to give it this functionality.
	///////////////////////////////////////////////////////////////////////
	class textLabelComponent : public ppc::RenderComponent {
	private:
		sf::Text* text;
		sf::Text* outline;
		sf::Font font;
		std::string labelString;


	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @param f is the font to be used.
		/// @param x is the x position of the font relative to the entity
		/// @param y is the y position of the font relative to the entity
		///////////////////////////////////////////////////////////////////////
		textLabelComponent(sf::Font& f, sf::Color c, float x, float y, int s, std::string str);

		~textLabelComponent();

		sf::Vector2f getTextPosition() const { return text->getPosition(); }

		std::string getString() const { return text->getString(); }

		void updateLabelString(std::string str);
		void updateLabelPosition(float x, float y);
		void updateLabelSize(int s);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	};

};

#endif /* textLabelComponent_hpp */
