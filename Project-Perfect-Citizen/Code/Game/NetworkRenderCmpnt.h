#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"
#include "../Engine/Network.h"
#include "../Engine/debug.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Render Component for Networks
	///@details Allows a given network graph to be drawn on the screen
	/// or window
	///////////////////////////////////////////////////////////////////
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

