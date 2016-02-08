#pragma once

#include "RenderCmpntDecorator.h"

#include <iostream>

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief A decorator for Render Cmpnts that logs data when 
	///functions are called.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class renderCmpntLogger : public renderCmpntDecorator {
	private:

		std::ostream& out_;

	public:

		renderCmpntLogger() = delete;
		renderCmpntLogger(RenderComponent& updatePtr, 
			std::ostream& out);
		virtual ~renderCmpntLogger();

		virtual Entity* getEntity();
		virtual void setEntity(Entity*);
		virtual void recieveMessage(msgType message);
		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const;

	};
};