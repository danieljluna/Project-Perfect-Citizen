#pragma once

#include "UpdateCmpntDecorator.h"
#include <iostream>

namespace sf {
    class Time;
};

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief A decorator for Update Cmpnts that logs data when 
	///functions are called.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class updateCmpntLogger: public updateCmpntDecorator {
	private:

		std::ostream& out_;

	public:

		updateCmpntLogger() = delete;
		updateCmpntLogger(UpdateComponent& updatePtr, 
			std::ostream& out);

		virtual ~updateCmpntLogger();

		virtual Entity* getEntity();
		virtual void setEntity(Entity*);
		virtual void recieveMessage(msgType message);
		virtual void update(sf::Time& deltaTime);
	};
};