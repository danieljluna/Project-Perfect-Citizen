#pragma once
#include <SFML/Graphics.hpp>

#include "renderComponent.h"
#include "Network.h"

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

