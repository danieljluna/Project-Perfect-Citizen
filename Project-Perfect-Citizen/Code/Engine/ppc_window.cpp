#include "ppc_window.h"



using namespace ppc;



ppc::Window::Window(float w, float h)
{
	
	sf::Vector2f vec(w,h);
	setSize(vec);
	setFillColor(sf::Color(0, 200, 0, 255));

}
