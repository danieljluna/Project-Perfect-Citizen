#pragma once

#include <SFML/System/Time.hpp>
#include "../Engine/updateComponent.h"

namespace ppc {
	class TextDisplayRenderComponent;

	class TextCharacterUpdate : public UpdateComponent {
	private:

		std::string content_;
		std::string::iterator strItor_;

		TextDisplayRenderComponent* tdrc_;

		sf::Time accumulator_;

		// .5 seconds
		sf::Time displayRate_ = sf::milliseconds(sf::Int32(500.0f));

		bool isEnd;

	public:
		
		TextCharacterUpdate();
		virtual ~TextCharacterUpdate();

		void setTextDisplay(TextDisplayRenderComponent&);
		void setContent(std::string);
		void setDisplayRate(sf::Time);
		bool isEnded() { return isEnd; }
		void update(sf::Time& deltaTime) override;

	};
};