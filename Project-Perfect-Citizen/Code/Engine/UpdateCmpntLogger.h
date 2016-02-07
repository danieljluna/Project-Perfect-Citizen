#pragma once

#include "UpdateCmpntDecorator.h"
#include <iostream>

namespace ppc {
	class updateCmpntLogger: public updateCmpntDecorator {
	private:

		std::ostream& out_;

	public:

		updateCmpntLogger() = delete;
		updateCmpntLogger(UpdateComponent& updatePtr, 
			std::ostream& out);

		virtual ~updateCmpntLogger();

		virtual Entity* getEntity();
		virtual void recieveMessage(msgType message);
		virtual void update(sf::Time& deltaTime);
	};
};