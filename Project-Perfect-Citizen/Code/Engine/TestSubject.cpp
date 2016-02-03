#include "TestSubject.h"
void TestSubject::testEventSituation()
{
	int arbitraryInt = 5;
	double arbitraryDouble = 3.14;

	sf::Event exampleRenderEvent;
	exampleRenderEvent.type = sf::Event::EventType::MouseMoved;
	this->sendEvent(exampleRenderEvent);
}
