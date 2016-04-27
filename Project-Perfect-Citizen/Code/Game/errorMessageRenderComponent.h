#pragma once

#include "../Engine/renderComponent.h"

#include <SFML/Graphics/Font.hpp>


namespace sf {
    class Sprite;
    class Text;
};


///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for the contents of an error msg
/// @author Alex Vincent 
/// @details Displays the error message icon and custom message
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class errorMessageRenderComponent : public ppc::RenderComponent {
	private:
		sf::Sprite* sprite;
		sf::Text* text;
		sf::Font font;
		static const int size = 128;


	public:

		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor
		/// @param The font of the text to be rendered
		/// @param The email to read the contents of
		/// @param The x position of the rendered text
		/// @param The y position of the rendered text
		/// @param The font size of the text
		///////////////////////////////////////////////////////////////////////
		errorMessageRenderComponent(sf::Font& f, std::string msg, int x, int y, int size);

		~errorMessageRenderComponent();

		sf::Text* getText();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}