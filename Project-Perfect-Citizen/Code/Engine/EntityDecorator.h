#pragma once

#include "Entity.h"

namespace ppc {

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