#pragma once

#include "renderComponent.h"

namespace ppc {
	class renderCmpntDecorator : public RenderComponent {
	private:

		RenderComponent* rCmpntHandle_;

	protected:

		RenderComponent* getDecoTarget() const {
			return rCmpntHandle_;
		}

	public:

		renderCmpntDecorator() = delete;
		renderCmpntDecorator(RenderComponent& updatePtr);
		virtual ~renderCmpntDecorator();

		virtual Entity* getEntity();
		virtual void recieveMessage(msgType message);
		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const;
	};
};