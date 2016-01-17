#pragma once

#include "Component.h"

//Update Component 


class UpdateComponent : public ppc::Component {

private:
	int myTempVar;

public:
	virtual void update(sf::Time deltaTime) = 0; 
};
