#pragma once

#include <SFML/System/Time.hpp>
#include "../Engine/updateComponent.h"

namespace ppc {
	class TextDisplayRenderComponent;

	class TextCharacterUpdate : public UpdateComponent {
	private:

		std::string content_;

		TextDisplayRenderComponent* tdrc_;

		sf::Time accumulator_;

		const sf::Time totalTime_ ;

		bool isEnd;

	public:
		
		TextCharacterUpdate();
		virtual ~TextCharacterUpdate();

		void setTextDisplay(TextDisplayRenderComponent&);
		void setContent(std::string);

		void update(sf::Time& deltaTime) override;

	};
};