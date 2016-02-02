#include "TestObserver.h"

void TestObserver::eventHandler(sf::Event event)
{
	if (event.type != sf::Event::EventType::MouseMoved){
		return;
	}
	cout << "the x value is " << event.mouseMove.x << endl;
	cout << "the y value is " << event.mouseMove.y << endl;
}
