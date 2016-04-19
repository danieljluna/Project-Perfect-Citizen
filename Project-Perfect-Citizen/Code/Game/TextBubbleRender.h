#pragma once

#include "../Engine/renderComponent.h"
#include "TextBubble.h"

namespace ppc {
	class TextBubbleRender: public ppc::RenderComponent {

	private:

		TextBubble* bubble_;

	public:

		TextBubbleRender();

		virtual ~TextBubbleRender();

		void setTextBubble(TextBubble&);

		TextBubble& getTextBubble();

		virtual void draw(sf::RenderTarget&,sf::RenderStates) const override;

		virtual void recieveMessage(msgType code) override;
	};
};