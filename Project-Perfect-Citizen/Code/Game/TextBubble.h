#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <queue>

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

		TextBubble();

		virtual ~TextBubble();

		bool loadText(std::string filename);

		void progressText();

		friend bool advanceOnPress(TextBubble* tb, sf::Event e);

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

	};

	bool advanceOnPress(TextBubble* tb, sf::Event e) {
		//TODO
	}

};