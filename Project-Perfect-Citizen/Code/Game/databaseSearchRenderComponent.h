#pragma once

#include <iostream>
#include <string>

//#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

#include "../Engine/renderComponent.h"

namespace sf {
	class Sprite;
	class Text;
};

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Render Component for the database search box
	/// @author Alex Vincent
	/// @details TO-DO
	///////////////////////////////////////////////////////////////////////
	class databaseSearchRenderComponent : public ppc::RenderComponent {
	private:
		sf::Sprite* sprite;
		sf::Text* text;
		sf::Font font;
		std::string str;
		static const int size = 128;

	public:

		databaseSearchRenderComponent(sf::Font& f, int x, int y, int size);

		~databaseSearchRenderComponent();

		////////////////////////////////////////////////////////////////////
		/// @brief updateString recieves a string from an input component to
		///        display.
		/// @param s is the string recieved from the input component
		////////////////////////////////////////////////////////////////////
		void updateString(std::string s);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;

	};

};