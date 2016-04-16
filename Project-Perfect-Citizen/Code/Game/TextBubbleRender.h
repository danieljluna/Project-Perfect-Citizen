#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"


namespace ppc {

	class TextBubble;

	class TextBubbleRender: public ppc::RenderComponent {

	private:

		TextBubble* textBubble_;

	public:

		TextBubbleRender();

		virtual ~TextBubbleRender();

		void setTextBubble(TextBubble&);

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

		virtual void recieveMessage(msgType code) override;

	};
};