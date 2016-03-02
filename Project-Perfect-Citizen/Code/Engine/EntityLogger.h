#pragma once

#include "EntityDecorator.h"
#include <iostream>

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief A decorator for Entities that logs data when functions  
	/// are called.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class EntityLogger : public EntityDecorator {

	private:

		std::ostream& out_;

	public:

		EntityLogger() = delete;
		EntityLogger(Entity& entityPtr, std::ostream& out);
		virtual ~EntityLogger();

		virtual size_t cmpntCount();
		virtual Component* getComponent(size_t index);
		virtual int getIndex(Component* cmpnt);
		virtual int addComponent(Component* cmpnt);
		virtual void removeComponent(Component* cmpnt);
		virtual void removeComponent(size_t index);
		virtual void broadcastMessage(msgType message);
	};
};