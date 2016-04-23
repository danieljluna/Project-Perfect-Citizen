#pragma once

#include "../Engine/renderComponent.h"



namespace ppc {

	class TextBubble;
	class Event;

	class TextBubbleRender: public ppc::RenderComponent {

	private:
		bool drawable_;
		TextBubble* bubble_;

	public:

		TextBubbleRender();

		virtual ~TextBubbleRender();

		void setTextBubble(TextBubble&);

		TextBubble& getTextBubble();

		void setDrawable(bool);

		virtual void draw(sf::RenderTarget&,sf::RenderStates) const override;

		virtual void recieveMessage(msgType code) override;

		virtual void recieveMessage(ppc::Event ev) override;
	};
};