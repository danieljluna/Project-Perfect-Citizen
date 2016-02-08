#pragma once

#include "updateComponent.h"

namespace ppc {
	class updateCmpntDecorator: public UpdateComponent {
	private:

		UpdateComponent* uCmpntHandle_;

	protected:

		UpdateComponent* getDecoTarget() const { 
			return uCmpntHandle_; 
		}

	public:

		updateCmpntDecorator() = delete;
		updateCmpntDecorator(UpdateComponent& updatePtr);
		virtual ~updateCmpntDecorator();

		virtual Entity* getEntity();
		virtual void setEntity(Entity*);
		virtual void recieveMessage(msgType message);
		virtual void update(sf::Time& deltaTime);

	};
};