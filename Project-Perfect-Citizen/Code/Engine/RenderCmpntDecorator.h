#pragma once

#include "renderComponent.h"

namespace ppc {
	///////////////////////////////////////////////////////////////////
	///@brief Decorator class for Render Components.
	///@details Decorators for Render Components must inherit from 
	/// this class. Decoratos act as middle-men for the objects they
	/// are decorating. Decorators can decorate other decorators, as 
	/// long as the whole chain points of an actual, non-decorator
	/// object.
	///@author Nader Sleem
	///////////////////////////////////////////////////////////////////
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
		virtual void setEntity(Entity*);
		virtual void recieveMessage(msgType message);
		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const;
	};
};