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
/// @brief Designated render component for an email block in the inbox 
/// @author Alex Vincent 
/// @details Consists of a box, text, and an email sprite
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class emailListElementRenderComponent : public ppc::RenderComponent {
	private:
		///////////////////////////////////////////////////////////////////////
		/// @brief The bounding box containing the emailListElement
		///////////////////////////////////////////////////////////////////////
		sf::RectangleShape emailListElementBox;

		///////////////////////////////////////////////////////////////////////
		/// @brief The sprite holding the text
		///////////////////////////////////////////////////////////////////////
		sf::Sprite* sprite;

		///////////////////////////////////////////////////////////////////////
		/// @brief The drawable text element for the subject line
		///////////////////////////////////////////////////////////////////////
		sf::Text* subjectText;

		///////////////////////////////////////////////////////////////////////
		/// @brief The drawable text element for the sender
		///////////////////////////////////////////////////////////////////////
		sf::Text* fromText;

		///////////////////////////////////////////////////////////////////////
		/// @brief The font of the drawable text element
		///////////////////////////////////////////////////////////////////////
		sf::Font font;
		static const int size = 128;
		int indent = 10;

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief The font of the drawable text element
		/// @param The reference to the drawable font
		/// @param A reference to the email to display
		/// @param An integer specifying the box's X position
		/// @param An integer specifying the box's Y position
		/// @param An integer specifying the box's Width
		/// @param An integer specifying the box's Height
		/// @param An integer specifying the text's x position
		/// @param An integer specifying the text's y position
		/// @param An integer specifying the text/font's size
		///////////////////////////////////////////////////////////////////////
		emailListElementRenderComponent(sf::Font& f, Email& email,
			int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

		~emailListElementRenderComponent();

		///////////////////////////////////////////////////////////////////////
		/// @brief Simple getter returning the bounds of the element box
		///////////////////////////////////////////////////////////////////////
		sf::FloatRect getListElementBoxBounds();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}