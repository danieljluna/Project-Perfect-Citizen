#pragma once

#include "Entity.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Decorator class for Entities.
	///@details Decorators for Entities must inherit from this class.
	/// Decoratos act as middle-men for the objects they
	/// are decorating. Decorators can decorate other decorators, as 
	/// long as the whole chain points of an actual, non-decoraor
	/// object.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
	class EntityDecorator : public Entity {

	private:
		Entity* entityHandle_;

	protected:
		Entity* getDecoTarget() const { return entityHandle_; }

	public:

		EntityDecorator() = delete;
		EntityDecorator(Entity& entityPtr);
		virtual ~EntityDecorator();

		virtual size_t cmpntCount();
		virtual Component* getComponent(size_t index);
		virtual int getIndex(Component* cmpnt);
		virtual int addComponent(Component* cmpnt);
		virtual void removeComponent(Component* cmpnt);
		virtual void removeComponent(size_t index);
		virtual void broadcastMessage(msgType message);

	};
};