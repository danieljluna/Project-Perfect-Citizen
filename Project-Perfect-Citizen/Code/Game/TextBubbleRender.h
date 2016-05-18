#pragma once

#include "../Engine/renderComponent.h"
#include <SFML/Graphics.hpp>


namespace ppc {

	class TextBubble;
	class Event;

	class TextBubbleRender: public ppc::RenderComponent {

	private:
		bool drawable_;
		TextBubble* bubble_;
		bool renderable_;
        sf::Color bubbleColor_;

	public:

		TextBubbleRender();

		virtual ~TextBubbleRender();

		void setTextBubble(TextBubble&);
        
        void setColor(sf::Color);

		TextBubble& getTextBubble();


		void setRenderable(bool);

		virtual void draw(sf::RenderTarget&,sf::RenderStates) const override;

		virtual void recieveMessage(msgType code) override;

		virtual void recieveMessage(ppc::Event ev) override;
	};
};