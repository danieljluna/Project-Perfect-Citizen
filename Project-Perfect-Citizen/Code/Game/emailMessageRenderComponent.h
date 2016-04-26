#pragma once

#include "../Engine/renderComponent.h"
#include "Email.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
    class Sprite;
    class Text;
};

///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for the contents of an email
/// @author Alex Vincent 
/// @details Reads from an email, formats the string to be rendered
/// and then renders it
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class emailMessageRenderComponent : public ppc::RenderComponent {
	private:

		///////////////////////////////////////////////////////////////////////
		/// @brief The bounding box containing the emails contents
		///////////////////////////////////////////////////////////////////////
		sf::RectangleShape emailContentBox;

		///////////////////////////////////////////////////////////////////////
		/// @brief The rendered text for the to, from, subject fields
		///////////////////////////////////////////////////////////////////////
		sf::Text* metaText;

		///////////////////////////////////////////////////////////////////////
		/// @brief The rendered text for the emails contents
		///////////////////////////////////////////////////////////////////////
		sf::Text* contentText;

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
		/// @param The width of the window to create the email in
		/// @param The height of the window to create the email in
		///////////////////////////////////////////////////////////////////////
		emailMessageRenderComponent(sf::Font& f, Email* email, int x, int y, int size,
			int winWidth, int winHeight);

		~emailMessageRenderComponent();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}