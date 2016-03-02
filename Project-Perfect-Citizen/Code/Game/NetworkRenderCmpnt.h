#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"
#include "../Engine/Network.h"
#include "../Engine/debug.h"

namespace ppc {

	class NetworkRenderComponent : public ppc::RenderComponent {

	private:

		ppc::Network* network_;

	public:

		NetworkRenderComponent() = delete;

		NetworkRenderComponent(ppc::Network&);

		virtual ~NetworkRenderComponent();

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

		virtual void recieveMessage(msgType code) override;
	};
};

