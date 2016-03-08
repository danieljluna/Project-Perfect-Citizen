#pragma once

#include "../Engine/renderComponent.h"
#include "Email.h"

///////////////////////////////////////////////////////////////////////
/// @brief Designated render component for the contents of an email
/// @author Alex Vincent 
/// @details Reads from an email, formats the string to be rendered
/// and then renders it
///////////////////////////////////////////////////////////////////////

namespace ppc {

	class emailMessageRenderComponent : public ppc::RenderComponent {
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
		emailMessageRenderComponent(sf::Font& f, Email& email, int x, int y, int size);

		~emailMessageRenderComponent();

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		virtual void recieveMessage(msgType code) override;


	};

}