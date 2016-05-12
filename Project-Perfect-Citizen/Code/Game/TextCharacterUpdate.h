#pragma once

#include <SFML/System/Clock.hpp>
#include "../Engine/updateComponent.h"

namespace ppc {
	class TextDisplayRenderComponent;

	class TextCharacterUpdate : public UpdateComponent {
	private:

		std::string content_;

		TextDisplayRenderComponent* tdrc_;

		sf::Time elapsedTime_;
		sf::Clock timer_;

		bool isEnd;

	public:
		
		TextCharacterUpdate();
		virtual ~TextCharacterUpdate();

		void setTextDisplay(TextDisplayRenderComponent&);
		void setContent(std::string);

		void update(sf::Time& deltaTime) override;

	};
};