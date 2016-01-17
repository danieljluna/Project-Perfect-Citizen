#pragma once

//Update Component 


class UpdateComponent {

private:
	int myTempVar;

public:
	virtual void update(sf::Time deltaTime) = 0; 
};