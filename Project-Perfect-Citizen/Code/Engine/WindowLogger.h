#pragma once

#include "WindowDecorator.h"
#include <iostream>

namespace ppc {

	class WindowLogger : public WindowDecorator {
	private:
		ostream& out_;
		
	protected:

		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;

	public:
		WindowLogger() = delete;
		WindowLogger(WindowInterface& windowPtr, ostream& out);
		virtual ~WindowLogger();

		virtual void addInputComponent(InputComponent* inputcmpnt);
		virtual void addRenderComponent(RenderComponent* rendercmpnt);
		virtual void addUpdateComponent(UpdateComponent* updatecmpnt);
		virtual void addEntity(Entity& entity);

		virtual void update(sf::Time& deltaTime);
		virtual void registerInput(sf::Event&);
		virtual void refresh(sf::RenderStates states = sf::RenderStates());
	};
};



