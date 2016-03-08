#pragma once

#include "../Engine/renderComponent.h"
#include "Email.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for an email block in the inbox 
/// @author Alex Vincent 
/// @details Consists of a box, text, and an email sprite
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class emailMessageRenderComponent : public ppc::RenderComponent {
	private:
		sf::Sprite* sprite;
		sf::Text* text;
		sf::Font font;
		static const int size = 128;

	public:
		emailMessageRenderComponent(sf::Font& f, Email& email, int x, int y, int size);

		~emailMessageRenderComponent();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}