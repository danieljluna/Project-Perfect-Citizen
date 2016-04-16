#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include "../Engine/event.h"

namespace ppc {


	///////////////////////////////////////////////////////////////////
	///@brief Basic speech text bubble 
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class TextBubble: public sf::Drawable, public sf::Transformable {

	private:
		
		std::queue<std::string, std::list<std::string>> textQueue;

		sf::Text displayText;

		sf::RectangleShape textBox;

		bool drawable;

		void formatLine(std::string&);

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
		///@brief Loads the dialogue text from a file
		///////////////////////////////////////////////////////////////
		bool loadText(std::string filename);

		///////////////////////////////////////////////////////////////
		///@brief Changes the displayed text to the next in the queue.
		///////////////////////////////////////////////////////////////
		void progressText();

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

	};

	///////////////////////////////////////////////////////////////
	///@brief Event function that progresses text.
	///@details Function should be associated with a observer
	/// so when a button is pressed, the dialogue text advances
	/// to the next one.
	///////////////////////////////////////////////////////////////
	bool progressOnText(TextBubble* tb, ppc::Event e) {
		if (tb == nullptr) return true;

		if (e.sfEvent.type == sf::Event::MouseButtonReleased &&
			e.sfEvent.mouseButton.button == sf::Mouse::Left) {
			tb->progressText();
		}
		return true;
	}
	
};