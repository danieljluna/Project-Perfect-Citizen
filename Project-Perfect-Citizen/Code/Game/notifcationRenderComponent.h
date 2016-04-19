#pragma once
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"

namespace ppc {

	class notificationRenderComponent : public ppc::RenderComponent {
	private:
		sf::CircleShape badge_;
		sf::Text notificationText_;
	public:
		notificationRenderComponent();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	};
};