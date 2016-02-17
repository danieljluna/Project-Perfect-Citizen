#pragma once

#include <SFML/Graphics.hpp>

#include "renderComponent.h"


class windowBkgndRenderCmpnt: public ppc::RenderComponent {
	
private:

	sf::Sprite* sprt;


public:

	windowBkgndRenderCmpnt() = delete;
	windowBkgndRenderCmpnt(sf::Sprite&);
	virtual ~windowBkgndRenderCmpnt();

	virtual void draw(sf::RenderTarget& target, 
		sf::RenderStates states) const override;

	virtual void recieveMessage(msgType code) override;
};

