#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"
#include "../Engine/NodeState.h"


namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Render Component for an Text Input Box
	/// @author Michael Lowe / Alex Vincent
	/// @details write this later
	///////////////////////////////////////////////////////////////////////
	class textInputRenderComponent : public ppc::RenderComponent {
	private:
		ppc::NodeState fileTree_;
		sf::Sprite* sprite;
		sf::Text* text;
		sf::Font font;
		std::string str;
		int textSize_;

	public:

		textInputRenderComponent(ppc::NodeState fT, sf::Font& f, int x, int y, int size);

		~textInputRenderComponent();

		sf::Sprite* getSprite() const { return sprite; }

		////////////////////////////////////////////////////////////////////
		/// @brief updateString recieves a string from an input component to
		///        display.
		/// @param s is the string recieved from the input component
		////////////////////////////////////////////////////////////////////
		void updateString(std::string s);

		void updatePrompt(std::string s);

		////////////////////////////////////////////////////////////////////
		/// @brief Updates the console prompt position in the window based
		/// on the amount of current lines
		/// @param integer specifying the width of the displayed lines. 
		/// This is usually Text->getLocalBounds().height
		/// @param How much down you want the prompt to render from the last
		/// outputted line.
		////////////////////////////////////////////////////////////////////
		void updatePosition(float textDisplayHeight, float offset);

		sf::Text* getText();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;

	};

};