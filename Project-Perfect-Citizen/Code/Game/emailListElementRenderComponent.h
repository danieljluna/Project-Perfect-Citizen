#pragma once

#include "../Engine/renderComponent.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for an email block in the inbox 
/// @author Alex Vincent 
/// @details Consists of a box, text, and an email sprite
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class emailListElementRenderComponent : public ppc::RenderComponent {
	private:
		sf::RectangleShape emailListElementBox;
		sf::Sprite* sprite;
		sf::Text* text;
		sf::Font font;
		static const int size = 128;

	public:
		emailListElementRenderComponent(sf::Font& f, std::string subjectLine,
			int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size);

		~emailListElementRenderComponent();

		sf::FloatRect getListElementBoxBounds();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}