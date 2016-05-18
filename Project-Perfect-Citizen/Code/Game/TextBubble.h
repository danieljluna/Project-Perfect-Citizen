#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Basic speech text bubble 
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class TextBubble: public sf::Drawable, public sf::Transformable {

	private:

		//sf::Sprite textBubble;

		sf::ConvexShape rectBubble_;

		std::string currStr_;
        
		sf::Text displayText_;
        
        sf::Vector2f rectPos_;

		//Function used is an altered version of the function found at
		// https://gist.github.com/LiquidHelium/7858095
		// All credit for the creation of this code goes to its creator.
		sf::String wrapText(sf::String string, bool bold);

	public:

		///////////////////////////////////////////////////////////////
		// Ctor
		///////////////////////////////////////////////////////////////
		TextBubble();

		///////////////////////////////////////////////////////////////
		// Dtor
		///////////////////////////////////////////////////////////////
		virtual ~TextBubble();

		///////////////////////////////////////////////////////////////
		///@brief Set the string displayed
		///////////////////////////////////////////////////////////////
		void setText(std::string);
        void setRectPos(sf::Vector2f);

		sf::ConvexShape& getBubble();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};

	///////////////////////////////////////////////////////////////
	///@brief Event function that progresses text.
	///@details Function should be associated with a observer
	/// so when a button is pressed, the dialogue text advances
	/// to the next one.
	///////////////////////////////////////////////////////////////
	//bool advanceOnPress(TextBubble* tb, ppc::Event e);
	
};