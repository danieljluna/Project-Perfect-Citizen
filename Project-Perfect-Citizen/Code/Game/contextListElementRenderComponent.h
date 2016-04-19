#pragma once

#include "../Engine/renderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Sprite;
	class Text;
};

///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for an context list element
/// block in the context menu
/// @author Alex Vincent 
/// @details Consists of a rectangle box, text, and an (optional) sprite
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class contextListElementRenderComponent : public ppc::RenderComponent {
	private:
		///////////////////////////////////////////////////////////////////////
		/// @brief The bounding box containing the contextListElement
		///////////////////////////////////////////////////////////////////////
		sf::RectangleShape contextListElementBox;

		//////////////////////////////////////////////////////////////////////
		/// @brief The sprite holding the text
		///////////////////////////////////////////////////////////////////////
		sf::Sprite* sprite;

		///////////////////////////////////////////////////////////////////////
		/// @brief The drawable text element for the context list element
		///////////////////////////////////////////////////////////////////////
		sf::Text* labelText;

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
		/// @param An integer specifying the box's X position
		/// @param An integer specifying the box's Y position
		/// @param An integer specifying the box's Width
		/// @param An integer specifying the box's Height
		/// @param An integer specifying the text's x position
		/// @param An integer specifying the text's y position
		/// @param An integer specifying the text/font's size
		///////////////////////////////////////////////////////////////////////
		contextListElementRenderComponent(sf::Font f, std::string s, 
			int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

		~contextListElementRenderComponent();

		///////////////////////////////////////////////////////////////////////
		/// @brief Simple getter returning the bounds of the element box
		///////////////////////////////////////////////////////////////////////
		sf::FloatRect getListElementBoxBounds();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(ppc::Event e) override;


	};

}