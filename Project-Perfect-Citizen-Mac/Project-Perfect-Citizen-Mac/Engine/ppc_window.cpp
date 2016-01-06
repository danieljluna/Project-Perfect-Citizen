#include "ppc_window.h"



using namespace ppc;



bool ppc::Window::intersectsMouse(sf::Vector2i &mouse_position)
{
	if (mouse_position.x <= getPosition().x + getSize().x && mouse_position.x >= getPosition().x && 
		mouse_position.y <= getPosition().y + getSize().y && mouse_position.y >= getPosition().y)
		return true;

	return false;
}

ppc::Window::Window(float w, float h, float x, float y)
{
	
	sf::Vector2f sVec(w,h);
	sf::Vector2f pVec(x, y);
	setSize(sVec);
	setPosition(pVec);
	setFillColor(sf::Color(100, 100, 100, 255));

}
