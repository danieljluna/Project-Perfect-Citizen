#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "TextBubble.h"
#include "../Engine/debug.h"

namespace ppc {
	class TextBubbleRender: public ppc::RenderComponent {

	private:

		TextBubble* textBubble;

	public:

		TextBubbleRender();

		virtual ~TextBubbleRender();

		void setTextBubble(TextBubble&);

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

		virtual void recieveMessage(msgType code) override;

	};
};