#include "TestObserver.h"

using namespace ppc;

void TestObserver::eventHandler(sf::Event event)
{
	if (event.type != sf::Event::EventType::MouseMoved){
		return;
	}
	std::cout << "the x value is " << event.mouseMove.x << std::endl;
	std::cout << "the y value is " << event.mouseMove.y << std::endl;
}
