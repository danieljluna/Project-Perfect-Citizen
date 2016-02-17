#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/renderComponent.h"


class WindowBkgndRenderCmpnt: public ppc::RenderComponent {
	
private:

	sf::Sprite* sprt;


public:

	WindowBkgndRenderCmpnt() = delete;
	WindowBkgndRenderCmpnt(sf::Sprite&);
	virtual ~WindowBkgndRenderCmpnt();

	virtual void draw(sf::RenderTarget& target, 
		sf::RenderStates states) const override;

	virtual void recieveMessage(msgType code) override;
};

