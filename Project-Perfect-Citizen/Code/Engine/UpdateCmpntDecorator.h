#pragma once

#include "updateComponent.h"

namespace sf {
    class Time;
};

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Decorator class for Update Components.
	///@details Decorators for Update Components must inherit from 
	/// this class. Decoratos act as middle-men for the objects they
	/// are decorating. Decorators can decorate other decorators, as 
	/// long as the whole chain points of an actual, non-decorator
	/// object.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
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